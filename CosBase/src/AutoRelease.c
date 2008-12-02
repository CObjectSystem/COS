/*
 o---------------------------------------------------------------------o
 |
 | COS Autorelease pool
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: AutoRelease.c,v 1.26 2008/12/02 17:32:21 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdlib.h>
#include <string.h>

/* NOTE-CONF: AutoRelease storage size
 * Init specifies the number of initial slots allocated for
 * autoreleased objects. Rate specifies the rate at which this storage
 * must grow (e.g. 2.0 means double the size each time it is
 * full). Warn specifies the thresthold for warning about the number of
 * objects autoreleased in a single pool (during expansion only).
 */
#define COS_AUTORELEASE_INIT 500
#define COS_AUTORELEASE_RATE 1.8
#define COS_AUTORELEASE_WARN 1000000 // 0 = *never*

// private class
defclass(AutoRelease,Object)
  struct AutoRelease *prv;
  OBJ *stk;
  OBJ *top;
  OBJ *end;
  OBJ  tmp;
  OBJ _stk[16];
endclass

makclass(AutoRelease,Object);

// -----

STATIC_ASSERT(COS_AUTORELEASE_RATE_must_be_greater_than_3_div_2,
              COS_AUTORELEASE_RATE >= 1.5);
STATIC_ASSERT(COS_AUTORELEASE_INIT_must_be_greater_than_100,
              COS_AUTORELEASE_INIT >= 100);
STATIC_ASSERT(COS_AUTORELEASE_WARN_is_too_small,
              COS_AUTORELEASE_WARN >= 10000);

/* NOTE-INFO: AutoRelease and threads
 * This code assumes the creation of a new pool for each new thread
 */

static struct AutoRelease _pool0; // sentinel

#if COS_TLS || !COS_POSIX // -----------------------------

static __thread struct AutoRelease *_pool = &_pool0;

static inline struct AutoRelease*
pool_get(void)
{
  return _pool;
}

static inline void
pool_set(struct AutoRelease *pool)
{
  _pool = pool;
}

static void
_pool_init(void)
{
}

#else // COS_POSIX && !COS_TLS ---------------------------

static pthread_key_t _pool_key;

static inline void
pool_set(struct AutoRelease *pool)
{
	test_assert( pthread_setspecific(_pool_key, pool) == 0 );
}

static inline struct AutoRelease*
pool_get(void)
{
	struct AutoRelease *pool = pthread_getspecific(_pool_key);
	if (pool) return pool;
	 
	pool_set(&_pool0);
	return &_pool0;
}

static void
_pool_deinit(void *pool_)
{
  struct AutoRelease *pool = pool_;
	
  while (pool->prv != &_pool0)
	  pool = pool->prv;

  grelease((OBJ)pool);
}

static void
_pool_init(void)
{
	test_assert( pthread_key_create(&_pool_key, _pool_deinit) == 0 );
}

#endif // ------------------------------------------------

static void
enlarge(struct AutoRelease* p)
{
  useclass(ExBadAlloc);
  U32 size = p->top - p->stk;
  U32 new_size;
  OBJ *stk;

  if (p->stk == p->_stk) {
    new_size = COS_AUTORELEASE_INIT;
    stk = malloc(sizeof *stk * new_size);
    if (stk) {
      *stk = 0;
      memcpy(stk+1, p->stk, sizeof *stk * size);
    }
  } else {
    new_size = size * COS_AUTORELEASE_RATE;
    stk = realloc(p->stk-1, sizeof *stk * new_size);
    if (size >= COS_AUTORELEASE_WARN)
      cos_debug("pool at %p hold %u autoreleased objects", (void*)p, size);
  }
  
  if (!stk) THROW(ExBadAlloc);

  p->stk = stk + 1;
  p->top = stk + 1 + size;
  p->end = stk + new_size;
}

static inline void
clear(struct AutoRelease *p)
{
  if (p->tmp)
    grelease(p->tmp), p->tmp = 0;

  while (p->top-- > p->stk)
    if (*p->top) grelease(*p->top);
}

static inline OBJ
push(OBJ obj)
{
  struct AutoRelease *pool = pool_get();

  if (pool->top == pool->end)
    pool->tmp = obj, enlarge(pool), pool->tmp = 0;

  return *pool->top++ = obj;
}

static inline OBJ
pop_or_retain(struct Any *obj)
{
  struct AutoRelease *pool = pool_get();

  if (*--pool->top != (OBJ)obj)
    ++pool->top, ++obj->rc;

  return (OBJ)obj;
}

static inline OBJ
pop_and_release(struct Any *obj)
{
  struct AutoRelease *pool = pool_get();

  if (*(pool->top-1) == (OBJ)obj)
    return gdealloc(gdeinit(*--pool->top)), Nil;

  return (OBJ)obj;
}

// -----

defmethod(OBJ, ginit, AutoRelease)
  self->stk = self->_stk;
  self->top = self->_stk;
  self->end = self->_stk + COS_ARRLEN(self->_stk);
  self->prv = pool_get();
  self->tmp = 0;
  pool_set(self);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, AutoRelease)
  struct AutoRelease *pool;

  // safer to release pool(s) above self first
  while ((pool = pool_get()) != self)
    grelease((OBJ)pool);

  // ensure transitivity when grelease sends gautoRelease
  pool_set(self->prv);

  // release autoreleased objects
  clear(self);

  // free stack
  if (self->stk != self->_stk)
    free(self->stk-1);

  retmethod(_1);
endmethod

// -----

defmethod(void, ginitialize, pmAutoRelease)
  if (!_pool0.prv) {
    // cos_trace("ginitialize(pmAutoRelease)");
    _pool0.Object.Any.id = cos_class_id(classref(AutoRelease));
    _pool0.Object.Any.rc = COS_RC_STATIC;
    _pool0.prv = &_pool0;
	  _pool_init();
    ginit((void*)&_pool0);
  }
endmethod

defmethod(void, gdeinitialize, pmAutoRelease)
  if (_pool0.prv) {
    // cos_trace("gdeinitialize(pmAutoRelease)");
    gdeinit((void*)&_pool0);
    _pool0.prv = 0;
  }
endmethod

// -----

defmethod(OBJ, gretain, AutoRelease)
  useclass(ExBadMessage);
  THROW( gnewWithStr(ExBadMessage, "AutoRelease pool cannot be retained") );
  COS_UNUSED(RETVAL);
endmethod

defmethod(OBJ, gautoRelease, AutoRelease)
  useclass(ExBadMessage);
  THROW( gnewWithStr(ExBadMessage, "AutoRelease pool cannot be autoreleased") );
  COS_UNUSED(RETVAL);
endmethod

// ----- ownership

defmethod(OBJ, gretain, Any)
  useclass(ExBadValue);

  if (self->rc > COS_RC_UNIT)
    retmethod(++self->rc, _1);

  if (self->rc == COS_RC_UNIT)
    retmethod(pop_or_retain(self));

  if (self->rc == COS_RC_STATIC)
    retmethod(_1);

  if (self->rc == COS_RC_AUTO)
    retmethod(gclone(_1));

  // self->rc < COS_RC_STATIC
  THROW( gnewWithStr(ExBadValue, "invalid reference counting") );
endmethod

defmethod(OBJ, grelease, Any)
  useclass(ExBadValue);

  if (self->rc > COS_RC_UNIT)
    retmethod(--self->rc, _1);

  if (self->rc == COS_RC_STATIC)
    retmethod(_1);

  if (self->rc == COS_RC_UNIT)
    retmethod(gdealloc(gdeinit(_1)), Nil);

  // self->rc == COS_RC_AUTO || self->rc < COS_RC_STATIC
  THROW( gnewWithStr(ExBadValue, "invalid reference counting") );
endmethod

defmethod(OBJ, gdiscard, Any)
  if (self->rc == COS_RC_UNIT)
    retmethod(pop_and_release(self));

  retmethod(_1);
endmethod

defmethod(OBJ, gautoRelease, Any)
  useclass(ExBadValue);

  if (self->rc >= COS_RC_UNIT)
    retmethod(push(_1));
	
  if (self->rc == COS_RC_STATIC)
    retmethod(_1);

  if (self->rc == COS_RC_AUTO)
    retmethod(push(gclone(_1)));

  // self->rc < COS_RC_STATIC
  THROW( gnewWithStr(ExBadValue, "invalid reference counting") );
endmethod

// -----

defmethod(U32, gsize, AutoRelease)
  retmethod(self->top - self->stk);
endmethod

/*
 * ----------------------------------------------------------------------------
 *  Debug Functions
 * ----------------------------------------------------------------------------
 */

#include <cos/debug.h>

void
cos_autorelease_showStack(FILE *fp)
{
  struct AutoRelease *pool = pool_get();
  OBJ *top = pool->top;
  U32 i;

  if (!fp) fp = stderr;

  for (i=0; top-- > pool->stk; i++)
    fprintf(fp, "AutoRelease[%4u] = %-25s (%4u refs)\n",
            i, gclassName(*top), gretainCount(*top));
}

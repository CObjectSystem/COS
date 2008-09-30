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
 | $Id: AutoRelease.c,v 1.6 2008/09/30 08:18:23 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/access.h>
#include <cos/gen/value.h>

#include <stdlib.h>
#include <string.h>

/* NOTE-INFO: AutoRelease and threads
 * This code assumes the creation of a new pool for each new thread
 */

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
  OBJ *stk;
  OBJ *top;
  OBJ *end;
  OBJ  prv;
  OBJ  tmp;
  OBJ _stk[16];
endclass

makclass(AutoRelease,Object);

static struct AutoRelease _pool0; // sentinel

// -----

STATIC_ASSERT(COS_AUTORELEASE_RATE_must_be_greater_than_3_div_2,
              COS_AUTORELEASE_RATE >= 1.5);
STATIC_ASSERT(COS_AUTORELEASE_INIT_must_be_greater_than_100,
              COS_AUTORELEASE_INIT >= 100);
STATIC_ASSERT(COS_AUTORELEASE_INIT_is_too_small,
              COS_AUTORELEASE_INIT >= COS_ARRLEN(_pool0._stk)*2);
STATIC_ASSERT(COS_AUTORELEASE_WARN_is_too_small,
              COS_AUTORELEASE_WARN >= 1000);

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

#else // COS_POSIX ---------------------------------------

#include <pthread.h>

static pthread_key_t  _pool_key;
static pthread_once_t _pool_once = PTHREAD_ONCE_INIT;

static void
_pool_init(void)
{
	 test_assert( pthread_key_create(&_pool_key, (void(*)(void*))gdeinit) == 0 );
	 test_assert( pthread_setspecific(_pool_key, &_pool0) == 0 );
}

static inline struct AutoRelease*
pool_get(void)
{
   test_assert( pthread_once(&_pool_once, _pool_init) == 0 );
	 return pthread_getspecific(_pool_key);
}

static inline void
pool_set(struct AutoRelease *pool)
{
   test_assert( pthread_once(&_pool_once, _pool_init) == 0 );
	 test_assert( pthread_setspecific(_pool_key, pool) == 0 );
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
    if (stk) memcpy(stk, p->stk, sizeof *stk * size);
  } else {
    new_size = size * COS_AUTORELEASE_RATE;
    stk = realloc(p->stk, sizeof *stk * new_size);
    if (size >= COS_AUTORELEASE_WARN)
      cos_trace("pool at %p hold %u autoreleased objects", (void*)p, size);
  }
  
  if (!stk) THROW(ExBadAlloc);

  p->stk = stk;
  p->top = stk + size;
  p->end = stk + new_size;
}

static inline void
push(struct AutoRelease* p, OBJ obj)
{
  if (p->top == p->end)
    p->tmp = obj, enlarge(p), p->tmp = NIL;

  *p->top++ = obj;
}

static inline void
clear(struct AutoRelease *p)
{
  if (p->tmp)
    grelease(p->tmp), p->tmp = NIL;

  while (p->top-- > p->stk)
    grelease(*p->top);
}

// -----

defmethod(OBJ, ginit, AutoRelease)
  self->stk = self->_stk;
  self->top = self->_stk;
  self->end = self->_stk + COS_ARRLEN(self->_stk);
  self->prv = (OBJ)pool_get();
  self->tmp = NIL;
  pool_set(self);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, AutoRelease)
  struct AutoRelease *pool;

  // safer to release pool(s) above self first
  while ((pool = pool_get()) != self)
    grelease((OBJ)pool);

  // ensure transitivity when grelease sends gautoRelease
  pool_set(STATIC_CAST(struct AutoRelease*, self->prv));

  // release autoreleased objects
  clear(self);

  // free stack
  if (self->stk != self->_stk)
    free(self->stk);

  retmethod(_1);
endmethod

// -----

defmethod(void, ginitialize, pmAutoRelease)
  if (!_pool0.prv) {
    // cos_trace("ginitialize(pmAutoRelease)");
    _pool0.Object.Any.id = COS_CLS_NAME(AutoRelease).Behavior.id;
    _pool0.Object.Any.rc = COS_RC_STATIC;
    ginit((OBJ)(void*)&_pool0);
  }
endmethod

defmethod(void, gdeinitialize, pmAutoRelease)
  if (_pool0.prv) {
    // cos_trace("gdeinitialize(pmAutoRelease)");
    gdeinit((OBJ)(void*)&_pool0);
    _pool0.prv = NIL;
  }
endmethod

// -----

defmethod(OBJ, gretain, AutoRelease)
  useclass(ExBadMessage);
  THROW( gnewWithStr(ExBadMessage, "invalid message gretain(AutoRelease)") );
  COS_UNUSED(RETVAL);
endmethod

defmethod(OBJ, gautoRelease, AutoRelease)
  useclass(ExBadMessage);
  THROW( gnewWithStr(ExBadMessage, "invalid message gautoRelease(AutoRelease)") );
  COS_UNUSED(RETVAL);
endmethod

// -----

defmethod(OBJ, gautoRelease, Any)
  OBJ obj = _1;

  switch (self->rc) {
  case COS_RC_STATIC: break;
  case COS_RC_AUTO  : obj = gclone(obj);
  default           : push(pool_get(), obj);
  }
  retmethod(obj);
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

#include <cos/cos/debug.h>

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

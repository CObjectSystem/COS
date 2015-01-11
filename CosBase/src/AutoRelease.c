/**
 * C Object System
 * COS Autorelease pool
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
#define COS_AUTORELEASE_RATE 1618     // golden ratio * 1000
#define COS_AUTORELEASE_WARN 10000000 // 0 = *never*

// private class
defclass(AutoRelease)
  struct AutoRelease *prv;
  OBJ *stk;
  OBJ *top;
  OBJ *end;
  OBJ  tmp;
  OBJ _stk[16];
endclass

makclass(AutoRelease);

// -----

useclass(ExBadValue, ExBadAlloc, ExBadMessage);

// -----

STATIC_ASSERT(COS_AUTORELEASE_RATE_must_be_greater_than_3_div_2,
              COS_AUTORELEASE_RATE >= 1500);
STATIC_ASSERT(COS_AUTORELEASE_INIT_must_be_greater_than_100,
              COS_AUTORELEASE_INIT >= 100);
STATIC_ASSERT(COS_AUTORELEASE_WARN_is_too_small,
              COS_AUTORELEASE_WARN >= 10000);

/* NOTE-INFO: AutoRelease and threads
 * This code assumes the creation of a new pool for each new thread
 */

static struct AutoRelease _pool0; // sentinel

#if defined(_OPENMP) || COS_HAS_TLS || !COS_HAS_POSIX // --------------------

static __thread struct AutoRelease *_pool = &_pool0;
#ifdef _OPENMP
#pragma omp threadprivate(_pool)
#endif

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

#else // !defined(_OPENMP) && !COS_HAS_TLS && COS_HAS_POSIX -----------------

static pthread_key_t _pool_key;

static void
pool_set(struct AutoRelease *pool)
{
	ensure( pthread_setspecific(_pool_key, pool) == 0 );
}

static cos_inline struct AutoRelease*
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
	ensure( pthread_key_create(&_pool_key, _pool_deinit) == 0 );
}

#endif // ------------------------------------------------

static void
enlarge(struct AutoRelease* p)
{
  U32 size = p->top - p->stk;
  U32 new_size;
  OBJ *stk;

  if (p->stk == p->_stk) {
    new_size = COS_AUTORELEASE_INIT;
    stk = malloc(sizeof *stk * new_size);
    if (stk) memcpy(stk, p->stk, sizeof *stk * size);
  } else {
    new_size = size * (COS_AUTORELEASE_RATE/1000.0);
    stk = realloc(p->stk, sizeof *stk * new_size);
    if (size >= COS_AUTORELEASE_WARN)
      cos_debug("pool at %p hold %u autoreleased objects", (void*)p, size);
  }
  
  if (!stk) THROW(ExBadAlloc);

  p->stk = stk;
  p->top = stk + size;
  p->end = stk + new_size;
}

static cos_inline void
clear(struct AutoRelease *p)
{
  if (p->tmp)
    grelease(p->tmp), p->tmp = 0;

  while (p->top-- > p->stk)
    grelease(*p->top);
}

static cos_inline OBJ
push(OBJ obj)
{
  struct AutoRelease *pool = pool_get();

  if (pool->top == pool->end)
    pool->tmp = obj, enlarge(pool), pool->tmp = 0;

  return *pool->top++ = obj;
}

// ----- Any ownership

defmethod(OBJ, gretain, Any)
  if (cos_object_rc(_1) >= COS_RC_UNIT)
    retmethod( cos_object_incRc(_1) );

  if (cos_object_rc(_1) == COS_RC_AUTO)
    retmethod( gcopy(_1) );

  if (cos_object_rc(_1) == COS_RC_STATIC)
    retmethod(_1);

  // cos_object_rc(_1) < COS_RC_STATIC
  THROW( gnewWithStr(ExBadValue, "invalid reference counting") );
endmethod

defmethod(OBJ, gautoRelease, Any)
  if (cos_object_rc(_1) >= COS_RC_UNIT)
    retmethod( push(_1) );

  if (cos_object_rc(_1) == COS_RC_AUTO)
    retmethod( push(gcopy(_1)) );

  if (cos_object_rc(_1) == COS_RC_STATIC)
    retmethod(_1);

  // cos_object_rc(_1) < COS_RC_STATIC
  THROW( gnewWithStr(ExBadValue, "invalid reference counting") );
endmethod

defmethod(void, grelease, Any)
  if (cos_object_rc(_1) > COS_RC_UNIT)
    cos_object_decRc(_1);
  
  else
  if (cos_object_rc(_1) == COS_RC_UNIT) // take care of cyclic dependencies
    gdealloc(gdeinit(cos_object_setRc(_1, COS_RC_STATIC)));

  else
  if (cos_object_rc(_1) < COS_RC_STATIC) // insensitive to STATIC and AUTO
    THROW( gnewWithStr(ExBadValue, "invalid reference counting") );
endmethod

// ----- Class ownership (always static)

defmethod(OBJ, gretain, Class)
  retmethod(_1);
endmethod

defmethod(OBJ, gautoRelease, Class)
  retmethod(_1);
endmethod

defmethod(void, grelease, Class)
endmethod

// ----- AutoRelease ownership

defmethod(OBJ, gretain, AutoRelease)
  THROW( gnewWithStr(ExBadMessage, "AutoRelease pool cannot be retained") );
  COS_UNUSED(_ret);
endmethod

defmethod(OBJ, gautoRelease, AutoRelease)
  COS_UNUSED(_ret); // insensitive, already chained
endmethod

defmethod(void, grelease, AutoRelease)
  cos_trace("destroying pool at %p [%u objects]", (void*)_1, gsize(_1));
  gdealloc(gdeinit(_1)); // cannot be auto, static or retained
endmethod

// -----

defmethod(U32, gsize, AutoRelease)
  retmethod(self->top - self->stk);
endmethod

// -----

defmethod(OBJ, ginit, AutoRelease)
  cos_object_setRc(_1, COS_RC_AUTO); // AutoRelease pools are "linked" to the stack
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

  // safer to release pool(s) above self
  while ((pool = pool_get()) != self)
    grelease((OBJ)pool);

  // release autoReleased objects
  clear(self);

  // free stack
  if (self->stk != self->_stk)
    free(self->stk), self->stk = 0;

  // remove from top
  pool_set(self->prv);

  retmethod(_1);
endmethod

// -----

defmethod(void, ginitialize, pmAutoRelease)
  if (!_pool0.prv) {
    OBJ pool = (OBJ)(void*)&_pool0;
    // cos_trace("ginitialize(pmAutoRelease)");
    cos_object_setId(pool, cos_class_id(classref(AutoRelease)));
    cos_object_setRc(pool, COS_RC_STATIC);
    
    _pool0.prv = &_pool0;
    _pool_init();
    
    ginit((OBJ)(void*)&_pool0);
  }
endmethod

defmethod(void, gdeinitialize, pmAutoRelease)
  if (_pool0.prv) {
    OBJ pool = (OBJ)(void*)&_pool0;
    // cos_trace("gdeinitialize(pmAutoRelease)");
    gdeinit(pool);
    
    _pool0.prv = 0;
  }
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

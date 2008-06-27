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
 | $Id: AutoRelease.c,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/access.h>
#include <cos/gen/value.h>

#undef NDEBUG

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* NOTE-CONF: AutoRelease storage size
 * Init specifies the number of initial slots allocated for
 * autoreleased objects. Rate specifies the rate at which this storage
 * must grow (e.g. 2.0 means double the size each time it is
 * full). Warn specifies the thresthold for warning about the number of
 * objects autoreleased in a single pool (during expansion only).
 */
#define COS_AUTORELEASE_INIT 500
#define COS_AUTORELEASE_RATE 1.8
#define COS_AUTORELEASE_WARN 500000 // 0 = *never*

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

// -----

/* NOTE-INFO: AutoRelease and threads
   This code assumes a new pool creation for each new thread
 */
static struct AutoRelease pool0; // sentinel
static __thread struct AutoRelease *pool = &pool0;

// -----

#define ARR_LEN(a) (sizeof (a) / sizeof *(a))

STATIC_ASSERT(COS_AUTORELEASE_RATE_must_be_greater_than_3_div_2,
              COS_AUTORELEASE_RATE >= 1.5);
STATIC_ASSERT(COS_AUTORELEASE_INIT_must_be_greater_than_100,
              COS_AUTORELEASE_INIT >= 100);
STATIC_ASSERT(COS_AUTORELEASE_INIT_is_too_small,
              COS_AUTORELEASE_INIT >= ARR_LEN(pool0._stk)*2);
STATIC_ASSERT(COS_AUTORELEASE_WARN_is_too_small,
              COS_AUTORELEASE_WARN >= 1000);

// -----

static void
enlarge(struct AutoRelease* p)
{
  useclass(ExBadAlloc);
  size_t size = p->top - p->stk;
  size_t new_size;
  OBJ *stk;

  if (p->stk == p->_stk) {
    new_size = COS_AUTORELEASE_INIT;
    stk = malloc(sizeof *stk * new_size);
    if (stk) memcpy(stk, p->stk, sizeof *stk * size);
  } else {
    assert( p->stk );
    new_size = size * COS_AUTORELEASE_RATE;
    stk = realloc(p->stk, sizeof *stk * new_size);
    if (size >= COS_AUTORELEASE_WARN)
      cos_trace("pool at %p hold %u autoreleased objects", (void*)p, (U32)size);
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
  self->end = self->_stk + ARR_LEN(self->_stk);
  self->prv = (OBJ)pool;
  self->tmp = NIL;
  pool = self;
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, AutoRelease)

  // safer to release pool(s) above self first
  while (pool != self)
    grelease((OBJ)pool);

  // ensure transitivity when gRelease sends gAutoRelease
  pool = STATIC_CAST(struct AutoRelease*, pool->prv);

  // release autoreleased objects
  clear(self);

  // free stack
  if (self->stk != self->_stk)
    free(self->stk);

  retmethod(_1);
endmethod

// -----

defmethod(void, ginitialize, pmAutoRelease)
  if (!pool0.prv) {
    // cos_trace("ginitialize(pmAutoRelease)");
    pool0.Object.Any.id = COS_CLS_NAME(AutoRelease).Behavior.id;
    pool0.Object.Any.rc = COS_RC_STATIC;
    ginit((OBJ)(void*)&pool0);
  }
endmethod

defmethod(void, gdeinitialize, pmAutoRelease)
  if (pool0.prv) {
    // cos_trace("gdeinitialize(pmAutoRelease)");
    gdeinit((OBJ)(void*)&pool0);
    pool0.prv = NIL;
  }
endmethod

// -----

defmethod(OBJ, gretain, AutoRelease)
  useclass(ExBadMessage);
  cos_trace("invalid message gretain(AutoRelease)");
  THROW(ExBadMessage);
  COS_UNUSED(_ret);
endmethod

defmethod(OBJ, gautoRelease, AutoRelease)
  useclass(ExBadMessage);
  cos_trace("invalid message gautoRelease(AutoRelease)");
  THROW(ExBadMessage);
  COS_UNUSED(_ret);
endmethod

// -----

defmethod(OBJ, gautoRelease, Any)
  OBJ obj = _1;

  switch (self->rc) {
  case COS_RC_STATIC: break;
  case COS_RC_AUTO  : obj = gclone(obj);
  default           : push(pool,obj);
  }
  retmethod(obj);
endmethod

// -----

defmethod(size_t, gsize, AutoRelease)
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
  OBJ *top = pool->top;
  U32 i;

  if (!fp) fp = stderr;

  for (i=0; top-- > pool->stk; i++)
    fprintf(fp, "AutoRelease[%4u] = %-25s (%4u refs)\n",
            i, gclassName(*top), gretainCount(*top));
}

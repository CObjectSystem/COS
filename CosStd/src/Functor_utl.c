/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Function Expression)
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
 | $Id: Functor_utl.c,v 1.13 2010/01/11 14:22:11 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>

#include "Functor_utl.h"

#include <assert.h>
#include <string.h>

// -----

useclass(ExBadAlloc);

// -----

static inline U32
getFunIdx(OBJ arg) // unsafe, use with isIdx()
{
  return STATIC_CAST(struct FunArg*, arg)->idx;
}

static inline OBJ
getFunVar(OBJ arg) // unsafe, use with isVar()
{
  return STATIC_CAST(struct FunVar*, arg)->var;
}

static inline OBJ
getFunFun(OBJ arg) // unsafe
{
  return STATIC_CAST(struct FunLzy*, arg)->fun;
}

static inline U32
getFunCnt(OBJ arg) // unsafe
{
  return STATIC_CAST(struct FunLzy*, arg)->cnt;
}

static inline U32
getFunMsk(OBJ arg) // unsafe
{
  return STATIC_CAST(struct Functor*, arg)->msk;
}

static inline OBJ
getFunExpr(OBJ arg) // unsafe
{
  return STATIC_CAST(struct ExpressionSurrogate*, arg)->expr;
}

static inline U32
getFunPar(OBJ arg, OBJ *var)
{
  U32 cnt = 0;
  
  do {
    cnt += getFunCnt(arg);
    arg  = getFunFun(arg);
  } while (cos_object_isa(arg, classref(FunLzy)));

  *var = arg;

  return cnt;
}

// -----

static inline void
setPar(U32 *msk, U32 par)
{
  *msk = (*msk & ~PAR_MASK) | par;
}

static inline void
setFunPar(OBJ arg, OBJ var, U32 cnt)
{
  struct FunLzy* lzy = STATIC_CAST(struct FunLzy*, arg);
  
  lzy->fun = var;
  lzy->cnt = cnt;
}

// -----

void
Functor_setMask(U32 *msk, U32 i, OBJ *arg)
{
  test_assert( i < 10, "HOF/HOM with 9+ OBJects arguments");

  // argument (null)
  if (!*arg) {
    setArg(msk, i);
    return;  
  }

  // expression surrogate (remove it before processing)
  while (cos_object_isa(*arg, classref(ExpressionSurrogate)))
    *arg = getFunExpr(*arg);

  // environment index (placeholder)
  if (cos_object_isa(*arg, classref(FunArg))) {
    setIdx(msk, i);
    *arg = (OBJ)(size_t)getFunIdx(*arg);
    return;
  }

  // environment key (placeholder)
  if (cos_object_isa(*arg, classref(FunVar))) {
    setVar(msk, i);
    *arg = getFunVar(*arg);
    return;
  }

  // lazy expression (placeholder)
  if (cos_object_isa(*arg, classref(FunLzy))) {
    OBJ var = Nil;
    U32 cnt = getFunPar(*arg, &var);

    if (cos_object_isKindOf(var, classref(PlaceHolder))) {
      setFunPar(*arg, var, cnt);
      U32 par = cnt*PAR_UNIT;
      if (par > *msk) setPar(msk, par);
    } else { // lazyness is idempotent for non-placeholder
      setArg(msk, i);
      *arg = var;
    }
    return;
  }
  
  // functor
  if (cos_object_isKindOf(*arg, classref(Functor))) {
    U32 par = getPar(getFunMsk(*arg));
    if (par > *msk + PAR_UNIT) setPar(msk, par - PAR_UNIT);
    return;
  }
       
  // argument (free variable)
  setArg(msk, i);
}

// -----

void*
Functor_cloneArgs(SEL sel, char *_arg)
{
  assert(_arg); // sanity check

  char *arg = 0;
  U32   narg = COS_GEN_NARG(sel);
  
  arg = malloc(sel->argsize);
  if (!arg) THROW(ExBadAlloc);

  if (COS_GEN_OARG(sel)) {  // only OBJects optimization
    OBJ *dst = (OBJ*) arg;
    OBJ *src = (OBJ*)_arg;

    for (U32 i = 0; i < narg; i++)
      if (getIdx(src[i]) >= 9)
        dst[i] = gretain(src[i]);
      else
        dst[i] = src[i];    // placeholder index or null
  }
  else {                    // some/all aren't OBJects
    memcpy(arg, _arg, sel->argsize);

    for (U32 i = 0; i < narg; i++)
      if ( cos_arginfo_isObject(sel->arginfo+i) ) {
        OBJ *obj = (OBJ*)(arg + sel->arginfo[i].offset);
        
        if (getIdx(*obj) >= 9)
          *obj = gretain(*obj);
      }
  }

  return arg;
}

// -----

void
Functor_deleteArgs(SEL sel, char *arg)
{
  assert(arg); // sanity check

  U32 narg = COS_GEN_NARG(sel);

  if (COS_GEN_OARG(sel)) {  // only OBJects optimization
    OBJ *obj = (OBJ*)arg;
    
    for (U32 i = 0; i < narg; i++)
      if (getIdx(obj[i]) >= 9)
        grelease(obj[i]);
  }
  else {                    // some/all aren't OBJects
    for (U32 i = 0; i < narg; i++)
      if ( cos_arginfo_isObject(sel->arginfo+i) ) {
        OBJ *obj = (OBJ*)(arg + sel->arginfo[i].offset);
        
        if (getIdx(*obj) >= 9)
          grelease(*obj);
      }
  }
  
  free(arg);
}


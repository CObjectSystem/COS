/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Functor Expression)
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
 | $Id: Functor_fun.c,v 1.14 2010/01/10 14:51:49 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include "Functor.h"
#include "Functor_utl.h"

// ----- type compatibility with functions

STATIC_ASSERT(functor1_to_function1_compatibility,
              COS_FIELD_COMPATIBILITY(Function1,FunExpr1,fct));

STATIC_ASSERT(functor2_to_function2_compatibility,
              COS_FIELD_COMPATIBILITY(Function2,FunExpr2,fct));

STATIC_ASSERT(functor3_to_function3_compatibility,
              COS_FIELD_COMPATIBILITY(Function3,FunExpr3,fct));

STATIC_ASSERT(functor4_to_function4_compatibility,
              COS_FIELD_COMPATIBILITY(Function4,FunExpr4,fct));

STATIC_ASSERT(functor5_to_function5_compatibility,
              COS_FIELD_COMPATIBILITY(Function5,FunExpr5,fct));

STATIC_ASSERT(functor6_to_function6_compatibility,
              COS_FIELD_COMPATIBILITY(Function6,FunExpr6,fct));

STATIC_ASSERT(functor7_to_function7_compatibility,
              COS_FIELD_COMPATIBILITY(Function7,FunExpr7,fct));

STATIC_ASSERT(functor8_to_function8_compatibility,
              COS_FIELD_COMPATIBILITY(Function8,FunExpr8,fct));

STATIC_ASSERT(functor9_to_function9_compatibility,
              COS_FIELD_COMPATIBILITY(Function9,FunExpr9,fct));

// ----- utils

enum { FUN_ISEXPR, FUN_ISCLOSED, FUN_ISFUNC };

static inline int
getFunType(U32 msk, OBJ arg[], U32 n)
{
  U32 i, narg = 0;
  
  for (i = 0; i < n; i++) {
    if (isArg(msk, i)) ++narg;

    else
    if (!isIdx(msk, i) || i - narg != getIdx(arg[i]))
      break;
  }
       
  return i == n ? (!narg ? FUN_ISFUNC : FUN_ISCLOSED) : FUN_ISEXPR;
}

// ----- initializer

dclclass(SFunExpr1, SFunExpr2, SFunExpr3, SFunExpr4);

#undef  DEFFUNC
#define DEFFUNC(N) \
\
struct Functor* COS_PP_CAT(FunExpr_init,N) \
(struct COS_PP_CAT(FunExpr,N) *fun, STR file, int line) \
{ \
  U32 *msk = &fun->FunExpr.Functor.msk; \
\
  for (U32 i = 0; i < N; i++) \
    Functor_setMask(msk, i, fun->arg+i, file, line); \
\
  switch(getFunType(*msk, fun->arg, N)) { \
  case FUN_ISFUNC: \
    fun->FunExpr.Functor.Expression.Object.id = \
      cos_class_id(classref(COS_PP_CAT(Function,N))); break; \
\
  COS_PP_IF(COS_PP_GT(N,4))(, \
  case FUN_ISCLOSED: \
    fun->FunExpr.Functor.Expression.Object.id = \
      cos_class_id(classref(COS_PP_CAT(SFunExpr,N))); break; \
  ) \
  COS_PP_IF(COS_PP_GT(N,5))(, \
  case FUN_ISEXPR: \
    if (getPar(*msk)) \
      fun->FunExpr.Functor.Expression.Object.id = \
        cos_class_id(classref(COS_PP_CAT(PFunExpr,N))); break; \
  ) \
  } \
\
  return &fun->FunExpr.Functor; \
}

DEFFUNC(1)
DEFFUNC(2)
DEFFUNC(3)
DEFFUNC(4)
DEFFUNC(5)
DEFFUNC(6)
DEFFUNC(7)
DEFFUNC(8)
DEFFUNC(9)

// ----- ctors

// TODO ??

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(FunExpr,N), COS_PP_CAT(FunExpr,N)) \
  U32 msk = self2->FunExpr.Functor.msk; \
\
  self->FunExpr.Functor.msk = msk; \
  self->FunExpr.str = self2->FunExpr.str; \
  self->fct = self2->fct; \
\
  for (int i = 0; i < N; i++) \
    self->arg[i] = isIdx(msk, i) ? self2->arg[i] : gretain(self2->arg[i]); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)
DEFMETHOD(6)
DEFMETHOD(7)
DEFMETHOD(8)
DEFMETHOD(9)

// ----- dtors

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, gdeinit, COS_PP_CAT(FunExpr,N)) \
  U32 msk = self->FunExpr.Functor.msk; \
\
  for (int i = 0; i < N; i++) \
    if (!isIdx(msk, i)) \
      grelease(self->arg[i]); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)
DEFMETHOD(6)
DEFMETHOD(7)
DEFMETHOD(8)
DEFMETHOD(9)

// ----- dtor (default)

defmethod(OBJ, gdeinit, FunExpr)
  retmethod(_1);
endmethod

// ----- str

defmethod(STR, gstr, FunExpr)
  retmethod(self->str);
endmethod

// ----- eval (stack-like environment)

defmethod(OBJ, gevalEnv, FunExpr1, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN1 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);

  retmethod( fct(arg0) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr1, Array) // partial evaluation
  U32  msk = self->FunExpr1.FunExpr.Functor.msk;
  FUN1 fct = self->FunExpr1.fct;
  OBJ *arg = self->FunExpr1.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);

  retmethod( gautoDelete(aFun(fct, arg0)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr2, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN2 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);

  retmethod( fct(arg0, arg1) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr2, Array) // partial evaluation
  U32  msk = self->FunExpr2.FunExpr.Functor.msk;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *arg = self->FunExpr2.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);

  retmethod( gautoDelete(aFun(fct, arg0, arg1)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr3, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN3 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);

  retmethod( fct(arg0, arg1, arg2) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr3, Array) // partial evaluation
  U32  msk = self->FunExpr3.FunExpr.Functor.msk;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *arg = self->FunExpr3.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);

  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr4, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN4 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  
  retmethod( fct(arg0, arg1, arg2, arg3) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr4, Array) // partial evaluation
  U32  msk = self->FunExpr4.FunExpr.Functor.msk;
  FUN4 fct = self->FunExpr4.fct;
  OBJ *arg = self->FunExpr4.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr5, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN5 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(4, msk, arg[4], var, size, _2);

  retmethod( fct(arg0, arg1, arg2, arg3, arg4) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr5, Array)
  U32  msk = self->FunExpr5.FunExpr.Functor.msk;
  FUN5 fct = self->FunExpr5.fct;
  OBJ *arg = self->FunExpr5.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(4, msk, arg[4], var, size, _2);
  
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr6, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN6 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(4, msk, arg[4], var, size, _2);
  OBJ arg5 = getArg(5, msk, arg[5], var, size, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4, arg5)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr7, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN7 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(4, msk, arg[4], var, size, _2);
  OBJ arg5 = getArg(5, msk, arg[5], var, size, _2);
  OBJ arg6 = getArg(6, msk, arg[6], var, size, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4, arg5, arg6)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr8, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN8 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(4, msk, arg[4], var, size, _2);
  OBJ arg5 = getArg(5, msk, arg[5], var, size, _2);
  OBJ arg6 = getArg(6, msk, arg[6], var, size, _2);
  OBJ arg7 = getArg(7, msk, arg[7], var, size, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr9, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN9 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(1, msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(2, msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(3, msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(4, msk, arg[4], var, size, _2);
  OBJ arg5 = getArg(5, msk, arg[5], var, size, _2);
  OBJ arg6 = getArg(6, msk, arg[6], var, size, _2);
  OBJ arg7 = getArg(7, msk, arg[7], var, size, _2);
  OBJ arg8 = getArg(8, msk, arg[8], var, size, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) );

  // partial evaluation
  retmethod(gautoDelete(aFun(fct,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)));
endmethod

// ----- eval (generic environment)

defmethod(OBJ, gevalEnv, FunExpr1, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN1 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);

  retmethod( fct(arg0) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr1, Container) // partial evaluation
  U32  msk = self->FunExpr1.FunExpr.Functor.msk;
  FUN1 fct = self->FunExpr1.fct;
  OBJ *arg = self->FunExpr1.arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);

  retmethod( gautoDelete(aFun(fct, arg0)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr2, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN2 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);

  retmethod( fct(arg0, arg1) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr2, Container) // partial evaluation
  U32  msk = self->FunExpr2.FunExpr.Functor.msk;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *arg = self->FunExpr2.arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);

  retmethod( gautoDelete(aFun(fct, arg0, arg1)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr3, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN3 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);

  retmethod( fct(arg0, arg1, arg2) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr3, Container) // partial evaluation
  U32  msk = self->FunExpr3.FunExpr.Functor.msk;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *arg = self->FunExpr3.arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);

  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr4, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN4 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);

  retmethod( fct(arg0, arg1, arg2, arg3) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr4, Container) // partial evaluation
  U32  msk = self->FunExpr4.FunExpr.Functor.msk;
  FUN4 fct = self->FunExpr4.fct;
  OBJ *arg = self->FunExpr4.arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);

  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr5, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN5 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);
  OBJ arg4 = getArgVar(4, msk, arg[4], _2);

  retmethod( fct(arg0, arg1, arg2, arg3, arg4) );
endmethod

defmethod(OBJ, gevalEnv, PFunExpr5, Container) // partial evaluation
  U32  msk = self->FunExpr5.FunExpr.Functor.msk;
  FUN5 fct = self->FunExpr5.fct;
  OBJ *arg = self->FunExpr5.arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);
  OBJ arg4 = getArgVar(4, msk, arg[4], _2);

  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr6, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN6 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);
  OBJ arg4 = getArgVar(4, msk, arg[4], _2);
  OBJ arg5 = getArgVar(5, msk, arg[5], _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4, arg5)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr7, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN7 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);
  OBJ arg4 = getArgVar(4, msk, arg[4], _2);
  OBJ arg5 = getArgVar(5, msk, arg[5], _2);
  OBJ arg6 = getArgVar(6, msk, arg[6], _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4, arg5, arg6)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr8, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN8 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);
  OBJ arg4 = getArgVar(4, msk, arg[4], _2);
  OBJ arg5 = getArgVar(5, msk, arg[5], _2);
  OBJ arg6 = getArgVar(6, msk, arg[6], _2);
  OBJ arg7 = getArgVar(7, msk, arg[7], _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr9, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN9 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg[0], _2);
  OBJ arg1 = getArgVar(1, msk, arg[1], _2);
  OBJ arg2 = getArgVar(2, msk, arg[2], _2);
  OBJ arg3 = getArgVar(3, msk, arg[3], _2);
  OBJ arg4 = getArgVar(4, msk, arg[4], _2);
  OBJ arg5 = getArgVar(5, msk, arg[5], _2);
  OBJ arg6 = getArgVar(6, msk, arg[6], _2);
  OBJ arg7 = getArgVar(7, msk, arg[7], _2);
  OBJ arg8 = getArgVar(8, msk, arg[8], _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) );

  // partial evaluation
  retmethod(gautoDelete(aFun(fct,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)));
endmethod


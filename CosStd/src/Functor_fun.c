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
 | $Id: Functor_fun.c,v 1.7 2010/01/07 14:53:52 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

#include "Functor_utl.h"

// -----

makclass(FunExpr , Functor);
makclass(FunExpr1, FunExpr);
makclass(FunExpr2, FunExpr);
makclass(FunExpr3, FunExpr);
makclass(FunExpr4, FunExpr);
makclass(FunExpr5, FunExpr);
makclass(FunExpr6, FunExpr);
makclass(FunExpr7, FunExpr);
makclass(FunExpr8, FunExpr);
makclass(FunExpr9, FunExpr);

// ----- partially evaluated functor

defclass(FunPart1, FunExpr1) endclass
defclass(FunPart2, FunExpr2) endclass
defclass(FunPart3, FunExpr3) endclass
defclass(FunPart4, FunExpr4) endclass

makclass(FunPart1, FunExpr1);
makclass(FunPart2, FunExpr2);
makclass(FunPart3, FunExpr3);
makclass(FunPart4, FunExpr4);

// ----- initializer

dclclass(Functor1, Functor2, Functor3, Functor4);

#undef  DEFFUNC
#define DEFFUNC(N) \
\
struct Functor* COS_PP_CAT(FunExpr_init,N) \
(struct COS_PP_CAT(FunExpr,N) *fun, STR file, int line) \
{ \
  fun->FunExpr.Functor.msk = Functor_getMask(fun->arg, N, file, line); \
\
  switch(getFunType(fun->FunExpr.Functor.msk, fun->arg, N)) { \
  case FUN_ISFUNC: \
    fun->FunExpr.Functor.Expression.Object.id = \
      cos_class_id(classref(COS_PP_CAT(Function,N))); break; \
\
  COS_PP_IF(COS_PP_GT(N,4))(, \
  case FUN_ISCLOSED: \
    fun->FunExpr.Functor.Expression.Object.id = \
      cos_class_id(classref(COS_PP_CAT(Functor,N))); break; \
\
  case FUN_ISEXPR: \
    if (getPar(fun->FunExpr.Functor.msk)) \
      fun->FunExpr.Functor.Expression.Object.id = \
        cos_class_id(classref(COS_PP_CAT(FunPart,N))); break; \
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

// TODO ?

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(FunExpr,N), COS_PP_CAT(FunExpr,N)) \
  self->FunExpr.Functor.msk = self2->FunExpr.Functor.msk; \
  self->FunExpr.str = self2->FunExpr.str; \
  self->fct = self2->fct; \
\
  for (int i = 0; i < N; i++) \
    self->arg[i] = isIdx(self2->FunExpr.Functor.msk, i) \
                   ? self2->arg[i] : gretain(self2->arg[i]); \
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
  for (int i = 0; i < N; i++) \
    if (!isIdx(self->FunExpr.Functor.msk, i)) \
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

// ----- eval (stack-like environment)

defmethod(OBJ, gevalEnv, FunExpr1, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN1 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);

  retmethod( fct(arg0) );
endmethod

defmethod(OBJ, gevalEnv, FunPart1, Array)
  U32  msk = self->FunExpr1.FunExpr.Functor.msk;
  FUN1 fct = self->FunExpr1.fct;
  OBJ *arg = self->FunExpr1.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr2, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN2 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);

  retmethod( fct(arg0, arg1) );
endmethod

defmethod(OBJ, gevalEnv, FunPart2, Array)
  U32  msk = self->FunExpr2.FunExpr.Functor.msk;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *arg = self->FunExpr2.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr3, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN3 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);

  retmethod( fct(arg0, arg1, arg2) );
endmethod

defmethod(OBJ, gevalEnv, FunPart3, Array)
  U32  msk = self->FunExpr3.FunExpr.Functor.msk;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *arg = self->FunExpr3.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr4, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN4 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  
  retmethod( fct(arg0, arg1, arg2, arg3) );
endmethod

defmethod(OBJ, gevalEnv, FunPart4, Array)
  U32  msk = self->FunExpr4.FunExpr.Functor.msk;
  FUN4 fct = self->FunExpr4.fct;
  OBJ *arg = self->FunExpr4.arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  
  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr5, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN5 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr6, Array)
  U32  msk = self->FunExpr.Functor.msk;
  FUN6 fct = self->fct;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);
  OBJ arg5 = getArg(5, msk, arg, var, size, _2);

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

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);
  OBJ arg5 = getArg(5, msk, arg, var, size, _2);
  OBJ arg6 = getArg(6, msk, arg, var, size, _2);

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

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);
  OBJ arg5 = getArg(5, msk, arg, var, size, _2);
  OBJ arg6 = getArg(6, msk, arg, var, size, _2);
  OBJ arg7 = getArg(7, msk, arg, var, size, _2);

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

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);
  OBJ arg5 = getArg(5, msk, arg, var, size, _2);
  OBJ arg6 = getArg(6, msk, arg, var, size, _2);
  OBJ arg7 = getArg(7, msk, arg, var, size, _2);
  OBJ arg8 = getArg(8, msk, arg, var, size, _2);

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

  OBJ arg0 = getArgVar(0, msk, arg, _2);

  retmethod( fct(arg0) );
endmethod

defmethod(OBJ, gevalEnv, FunPart1, Container)
  U32  msk = self->FunExpr1.FunExpr.Functor.msk;
  FUN1 fct = self->FunExpr1.fct;
  OBJ *arg = self->FunExpr1.arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr2, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN2 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);

  retmethod( fct(arg0, arg1) );
endmethod

defmethod(OBJ, gevalEnv, FunPart2, Container)
  U32  msk = self->FunExpr2.FunExpr.Functor.msk;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *arg = self->FunExpr2.arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr3, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN3 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);

  retmethod( fct(arg0, arg1, arg2) );
endmethod

defmethod(OBJ, gevalEnv, FunPart3, Container)
  U32  msk = self->FunExpr3.FunExpr.Functor.msk;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *arg = self->FunExpr3.arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr4, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN4 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);

  retmethod( fct(arg0, arg1, arg2, arg3) );
endmethod

defmethod(OBJ, gevalEnv, FunPart4, Container)
  U32  msk = self->FunExpr4.FunExpr.Functor.msk;
  FUN4 fct = self->FunExpr4.fct;
  OBJ *arg = self->FunExpr4.arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr5, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN5 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);
  OBJ arg4 = getArgVar(4, msk, arg, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr6, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN6 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);
  OBJ arg4 = getArgVar(4, msk, arg, _2);
  OBJ arg5 = getArgVar(5, msk, arg, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4, arg5)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr7, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN7 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);
  OBJ arg4 = getArgVar(4, msk, arg, _2);
  OBJ arg5 = getArgVar(5, msk, arg, _2);
  OBJ arg6 = getArgVar(6, msk, arg, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct, arg0, arg1, arg2, arg3, arg4, arg5, arg6)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr8, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN8 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);
  OBJ arg4 = getArgVar(4, msk, arg, _2);
  OBJ arg5 = getArgVar(5, msk, arg, _2);
  OBJ arg6 = getArgVar(6, msk, arg, _2);
  OBJ arg7 = getArgVar(7, msk, arg, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) );

  // partial evaluation
  retmethod( gautoDelete(aFun(fct,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7)) );
endmethod

defmethod(OBJ, gevalEnv, FunExpr9, Container)
  U32  msk = self->FunExpr.Functor.msk;
  FUN9 fct = self->fct;
  OBJ *arg = self->arg;

  OBJ arg0 = getArgVar(0, msk, arg, _2);
  OBJ arg1 = getArgVar(1, msk, arg, _2);
  OBJ arg2 = getArgVar(2, msk, arg, _2);
  OBJ arg3 = getArgVar(3, msk, arg, _2);
  OBJ arg4 = getArgVar(4, msk, arg, _2);
  OBJ arg5 = getArgVar(5, msk, arg, _2);
  OBJ arg6 = getArgVar(6, msk, arg, _2);
  OBJ arg7 = getArgVar(7, msk, arg, _2);
  OBJ arg8 = getArgVar(8, msk, arg, _2);

  if (!getPar(msk))
    retmethod( fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) );

  // partial evaluation
  retmethod(gautoDelete(aFun(fct,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)));
endmethod


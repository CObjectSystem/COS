/**
 * C Object System
 * COS FunExpr (High Order Function)
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

#include <cos/Functor.h>

#include <cos/gen/object.h>
#include <cos/gen/functor.h>
#include <cos/gen/value.h>

// ----- initializer

#undef  DEFFUNC
#define DEFFUNC(N) \
\
struct Functor* COS_PP_CAT(FunExpr_init,N) \
(struct COS_PP_CAT(FunExpr,N) *fun) \
{ \
  struct FunArg *arg; \
\
  for (int i = 0; i < N; i++) { \
    if ( (arg = cast(FunArg, fun->arg[i].obj)) ) { \
      fun->arg[i].idx = arg->idx; \
      if (arg->idx < fun->FunExpr.max) \
        fun->FunExpr.max = arg->idx; \
      continue; \
    } \
    \
    fun->FunExpr.msk |= 1u << i; \
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

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, COS_PP_CAT(ginitWithFun,N), pmFunctor, (COS_PP_CAT(FUN,N))fct, (OBJ*)arg) \
  OBJ fun = aFun(fct, COS_PP_SEQ(COS_PP_MAP(COS_PP_TAKE(N,(COS_PP_NUMSEQ_N())),DEFARG))); \
  retmethod( gcopy(fun) ); \
endmethod

#undef  DEFARG
#define DEFARG(i) arg[i-1]

defmethod(OBJ, ginitWithFun0, pmFunctor, (FUN0)fct)
  retmethod( gcopy(aFun(fct)) );
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

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(FunExpr,N), COS_PP_CAT(FunExpr,N)) \
  self->FunExpr.str = self2->FunExpr.str; \
  self->FunExpr.msk = self2->FunExpr.msk; \
  self->FunExpr.max = self2->FunExpr.max; \
  self->fct = self2->fct; \
\
  for (int i = 0; i < N; i++) \
    if (self->FunExpr.msk & (1u << i)) \
      self->arg[i].obj = gretain(self2->arg[i].obj); \
    else \
      self->arg[i].idx = self2->arg[i].idx; \
\
  retmethod(_1); \
endmethod

defmethod(OBJ, ginitWith, FunExpr0, FunExpr0)
  self->FunExpr.str = self2->FunExpr.str;
  self->FunExpr.msk = self2->FunExpr.msk;
  self->FunExpr.max = self2->FunExpr.max;
  self->fct = self2->fct;

  retmethod(_1);
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
    if (self->FunExpr.msk & (1u << i)) \
      grelease(self->arg[i].obj); \
\
  retmethod(_1); \
endmethod

defmethod(OBJ, gdeinit, FunExpr0)
  retmethod(_1);
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

// ----- str

defmethod(STR, gstr, FunExpr)
  retmethod(self->str);
endmethod

// --------------------------------------------------------
// ---- eval

// ----- 0

defmethod(OBJ, gevalFun, FunExpr0)
  retmethod( self->fct() );
endmethod

// ----- 1

defmethod(OBJ, gevalFun, FunExpr1)
  switch(self->FunExpr.msk) {
    case 1: cos_object_setId(_1, cos_class_id(classref(FunExpr11))); break;
    case 0: cos_object_setId(_1, cos_class_id(classref(FunExpr12))); break;
    default : ensure(0, "invalid FunExpr1 mask");
  }

  forward_message(_1);
endmethod

defmethod(OBJ, gevalFun, FunExpr11)
  union cos_functor_arg *arg = self->FunExpr1.arg;
  FUN1 fct = self->FunExpr1.fct;

  retmethod( fct(arg[0].obj) );                                       // msk = 1
endmethod

defmethod(OBJ, gevalFun, FunExpr12)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr1.arg;
  FUN1 fct = self->FunExpr1.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr1.FunExpr.max)
    retmethod( fct(var[arg[0].idx]) );                                // msk = 0

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];

    retmethod( gautoRelease(aFun(fct, arg0)) );
  }
endmethod

// ----- 2

defmethod(OBJ, gevalFun, FunExpr2)
  switch(self->FunExpr.msk) {
    case 3: cos_object_setId(_1, cos_class_id(classref(FunExpr21))); break;
    case 2: cos_object_setId(_1, cos_class_id(classref(FunExpr22))); break;
    case 1: cos_object_setId(_1, cos_class_id(classref(FunExpr23))); break;
    case 0: cos_object_setId(_1, cos_class_id(classref(FunExpr24))); break;
    default : ensure(0, "invalid FunExpr2 mask");
  }

  forward_message(_1);
endmethod

defmethod(OBJ, gevalFun, FunExpr21)
  union cos_functor_arg *arg = self->FunExpr2.arg;
  FUN2 fct = self->FunExpr2.fct;

  retmethod( fct(arg[0].obj, arg[1].obj) );                           // msk = 3
endmethod

defmethod(OBJ, gevalFun, FunExpr22)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr2.arg;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr2.FunExpr.max)
    retmethod( fct(var[arg[0].idx], arg[1].obj) );                    // msk = 2

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];

    retmethod( gautoRelease(aFun(fct, arg0, arg[1].obj)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr23)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr2.arg;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr2.FunExpr.max)
    retmethod( fct(arg[0].obj, var[arg[1].idx]) );                    // msk = 1

  else { // partial evaluation
    OBJ arg1 = arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];

    retmethod( gautoRelease(aFun(fct, arg[0].obj, arg1)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr24)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr2.arg;
  FUN2 fct = self->FunExpr2.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr2.FunExpr.max)
    retmethod( fct(var[arg[0].idx], var[arg[1].idx]) );               // msk = 0

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];

    retmethod( gautoRelease(aFun(fct, arg0, arg1)) );
  }
endmethod

// ----- 3

defmethod(OBJ, gevalFun, FunExpr3)
  switch(self->FunExpr.msk) {
    case 7: cos_object_setId(_1, cos_class_id(classref(FunExpr31))); break;
    case 6: cos_object_setId(_1, cos_class_id(classref(FunExpr32))); break;
    case 5: cos_object_setId(_1, cos_class_id(classref(FunExpr33))); break;
    case 4: cos_object_setId(_1, cos_class_id(classref(FunExpr34))); break;
    case 3: cos_object_setId(_1, cos_class_id(classref(FunExpr35))); break;
    case 2: cos_object_setId(_1, cos_class_id(classref(FunExpr36))); break;
    case 1: cos_object_setId(_1, cos_class_id(classref(FunExpr37))); break;
    case 0: cos_object_setId(_1, cos_class_id(classref(FunExpr38))); break;
    default  : ensure(0, "invalid FunExpr3 mask");
  }

  forward_message(_1);
endmethod

defmethod(OBJ, gevalFun, FunExpr31)
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;

  retmethod( fct(arg[0].obj, arg[1].obj, arg[2].obj) );               // msk = 7
endmethod

defmethod(OBJ, gevalFun, FunExpr32)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(var[arg[0].idx], arg[1].obj, arg[2].obj) );        // msk = 6

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];

    retmethod( gautoRelease(aFun(fct, arg0, arg[1].obj, arg[2].obj)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr33)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(arg[0].obj, var[arg[1].idx], arg[2].obj) );        // msk = 5

  else { // partial evaluation
    OBJ arg1 = arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];

    retmethod( gautoRelease(aFun(fct, arg[0].obj, arg1, arg[2].obj)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr34)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(var[arg[0].idx], var[arg[1].idx], arg[2].obj) );   // msk = 4

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];

    retmethod( gautoRelease(aFun(fct, arg0, arg1, arg[2].obj)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr35)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(arg[0].obj, arg[1].obj, var[arg[2].idx]) );        // msk = 3

  else { // partial evaluation
    OBJ arg2 = arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];

    retmethod( gautoRelease(aFun(fct, arg[0].obj, arg[1].obj, arg2)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr36)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(var[arg[0].idx], arg[1].obj, var[arg[2].idx]) );   // msk = 2

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg2 = arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];

    retmethod( gautoRelease(aFun(fct, arg0, arg[1].obj, arg2)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr37)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(arg[0].obj, var[arg[1].idx], var[arg[2].idx]) );   // msk = 1

  else { // partial evaluation
    OBJ arg1 = arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];

    retmethod( gautoRelease(aFun(fct, arg[0].obj, arg1, arg2)) );
  }
endmethod

defmethod(OBJ, gevalFun, FunExpr38)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->FunExpr3.arg;
  FUN3 fct = self->FunExpr3.fct;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr3.FunExpr.max)
    retmethod( fct(var[arg[0].idx], var[arg[1].idx], var[arg[2].idx]) ); // msk = 0

  else { // partial evaluation
    OBJ arg0 = arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];

    retmethod( gautoRelease(aFun(fct, arg0, arg1, arg2)) );
  }
endmethod

// ----- 4

defmethod(OBJ, gevalFun, FunExpr4)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->arg;
  U32  msk = self->FunExpr.msk;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr.max) {
    OBJ arg0 = msk & 1 ? arg[0].obj : var[arg[0].idx];
    OBJ arg1 = msk & 2 ? arg[1].obj : var[arg[1].idx];
    OBJ arg2 = msk & 4 ? arg[2].obj : var[arg[2].idx];
    OBJ arg3 = msk & 8 ? arg[3].obj : var[arg[3].idx];
  
    retmethod( self->fct(arg0, arg1, arg2, arg3) );

  } else { // partial evaluation
    OBJ arg0 = msk & 1 ? arg[0].obj : arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = msk & 2 ? arg[1].obj : arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = msk & 4 ? arg[2].obj : arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];
    OBJ arg3 = msk & 8 ? arg[3].obj : arg[3].idx < narg ? aFunArg(arg[3].idx-narg) : var[arg[3].idx];

    retmethod( gautoRelease(aFun(self->fct, arg0, arg1, arg2, arg3)) );
  }
endmethod

// ----- 5

defmethod(OBJ, gevalFun, FunExpr5)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->arg;
  U32  msk = self->FunExpr.msk;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr.max) {
    OBJ arg0 = msk &   1 ? arg[0].obj : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : var[arg[4].idx];
  
    retmethod( self->fct(arg0, arg1, arg2, arg3, arg4) );

  } else { // partial evaluation
    OBJ arg0 = msk &   1 ? arg[0].obj : arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : arg[3].idx < narg ? aFunArg(arg[3].idx-narg) : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : arg[4].idx < narg ? aFunArg(arg[4].idx-narg) : var[arg[4].idx];

    retmethod( gautoRelease(aFun(self->fct, arg0, arg1, arg2, arg3, arg4)) );
  }
endmethod

// ----- 6

defmethod(OBJ, gevalFun, FunExpr6)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->arg;
  U32  msk = self->FunExpr.msk;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr.max) {
    OBJ arg0 = msk &   1 ? arg[0].obj : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : var[arg[5].idx];
  
    retmethod( self->fct(arg0, arg1, arg2, arg3, arg4, arg5) );

  } else { // partial evaluation
    OBJ arg0 = msk &   1 ? arg[0].obj : arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : arg[3].idx < narg ? aFunArg(arg[3].idx-narg) : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : arg[4].idx < narg ? aFunArg(arg[4].idx-narg) : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : arg[5].idx < narg ? aFunArg(arg[5].idx-narg) : var[arg[5].idx];

    retmethod( gautoRelease(aFun(self->fct, arg0, arg1, arg2, arg3, arg4, arg5)) );
  }
endmethod

// ----- 7

defmethod(OBJ, gevalFun, FunExpr7)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->arg;
  U32  msk = self->FunExpr.msk;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr.max) {
    OBJ arg0 = msk &   1 ? arg[0].obj : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : var[arg[5].idx];
    OBJ arg6 = msk &  64 ? arg[6].obj : var[arg[6].idx];
  
    retmethod( self->fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6) );

  } else { // partial evaluation
    OBJ arg0 = msk &   1 ? arg[0].obj : arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : arg[3].idx < narg ? aFunArg(arg[3].idx-narg) : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : arg[4].idx < narg ? aFunArg(arg[4].idx-narg) : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : arg[5].idx < narg ? aFunArg(arg[5].idx-narg) : var[arg[5].idx];
    OBJ arg6 = msk &  64 ? arg[6].obj : arg[6].idx < narg ? aFunArg(arg[6].idx-narg) : var[arg[6].idx];

    retmethod( gautoRelease(aFun(self->fct, arg0, arg1, arg2, arg3, arg4, arg5, arg6)) );
  }
endmethod

// ----- 8

defmethod(OBJ, gevalFun, FunExpr8)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->arg;
  U32  msk = self->FunExpr.msk;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr.max) {
    OBJ arg0 = msk &   1 ? arg[0].obj : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : var[arg[5].idx];
    OBJ arg6 = msk &  64 ? arg[6].obj : var[arg[6].idx];
    OBJ arg7 = msk & 128 ? arg[7].obj : var[arg[7].idx];
  
    retmethod( self->fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) );

  } else { // partial evaluation
    OBJ arg0 = msk &   1 ? arg[0].obj : arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : arg[3].idx < narg ? aFunArg(arg[3].idx-narg) : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : arg[4].idx < narg ? aFunArg(arg[4].idx-narg) : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : arg[5].idx < narg ? aFunArg(arg[5].idx-narg) : var[arg[5].idx];
    OBJ arg6 = msk &  64 ? arg[6].obj : arg[6].idx < narg ? aFunArg(arg[6].idx-narg) : var[arg[6].idx];
    OBJ arg7 = msk & 128 ? arg[7].obj : arg[7].idx < narg ? aFunArg(arg[7].idx-narg) : var[arg[7].idx];

    retmethod( gautoRelease(aFun(self->fct, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) );
  }
endmethod

// ----- 9

defmethod(OBJ, gevalFun, FunExpr9)
  struct cos_functor_context *cxt = cos_functor_context();
  union cos_functor_arg *arg = self->arg;
  U32  msk = self->FunExpr.msk;
  OBJ *var = cxt->top;
  I32 narg = cxt->stk - cxt->top;

  if (narg <= self->FunExpr.max) {
    OBJ arg0 = msk &   1 ? arg[0].obj : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : var[arg[5].idx];
    OBJ arg6 = msk &  64 ? arg[6].obj : var[arg[6].idx];
    OBJ arg7 = msk & 128 ? arg[7].obj : var[arg[7].idx];
    OBJ arg8 = msk & 256 ? arg[8].obj : var[arg[8].idx];
  
    retmethod( self->fct(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) );

  } else { // partial evaluation
    OBJ arg0 = msk &   1 ? arg[0].obj : arg[0].idx < narg ? aFunArg(arg[0].idx-narg) : var[arg[0].idx];
    OBJ arg1 = msk &   2 ? arg[1].obj : arg[1].idx < narg ? aFunArg(arg[1].idx-narg) : var[arg[1].idx];
    OBJ arg2 = msk &   4 ? arg[2].obj : arg[2].idx < narg ? aFunArg(arg[2].idx-narg) : var[arg[2].idx];
    OBJ arg3 = msk &   8 ? arg[3].obj : arg[3].idx < narg ? aFunArg(arg[3].idx-narg) : var[arg[3].idx];
    OBJ arg4 = msk &  16 ? arg[4].obj : arg[4].idx < narg ? aFunArg(arg[4].idx-narg) : var[arg[4].idx];
    OBJ arg5 = msk &  32 ? arg[5].obj : arg[5].idx < narg ? aFunArg(arg[5].idx-narg) : var[arg[5].idx];
    OBJ arg6 = msk &  64 ? arg[6].obj : arg[6].idx < narg ? aFunArg(arg[6].idx-narg) : var[arg[6].idx];
    OBJ arg7 = msk & 128 ? arg[7].obj : arg[7].idx < narg ? aFunArg(arg[7].idx-narg) : var[arg[7].idx];
    OBJ arg8 = msk & 256 ? arg[8].obj : arg[8].idx < narg ? aFunArg(arg[8].idx-narg) : var[arg[8].idx];

    retmethod( gautoRelease(aFun(self->fct, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)) );
  }
endmethod


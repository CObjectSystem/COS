/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Method Expression)
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
 | $Id: Functor_mth.c,v 1.3 2009/12/30 01:00:45 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/message.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <assert.h>
#include <string.h>

#include "Functor_utl.h"

// ----- Functor method

defclass(MthExpr, Functor)
endclass

defclass(MthExpr1, MthExpr)
  SEL   sel;
  U32   msk;
  I32   ary;
  OBJ   arg[1];
  void *args;
endclass

defclass(MthExpr2, MthExpr)
  SEL   sel;
  U32   msk;
  I32   ary;
  OBJ   arg[2];
  void *args;
endclass

defclass(MthExpr3, MthExpr)
  SEL   sel;
  U32   msk;
  I32   ary;
  OBJ   arg[3];
  void *args;
endclass

defclass(MthExpr4, MthExpr)
  SEL   sel;
  U32   msk;
  I32   ary;
  OBJ   arg[4];
  void *args;
endclass

defclass(MthExpr5, MthExpr)
  SEL   sel;
  U32   msk;
  I32   ary;
  OBJ   arg[5];
  void *args;
endclass

makclass(MthExpr , Functor);
makclass(MthExpr1, MthExpr);
makclass(MthExpr2, MthExpr);
makclass(MthExpr3, MthExpr);
makclass(MthExpr4, MthExpr);
makclass(MthExpr5, MthExpr);

useclass(ExBadAlloc);

// ----- helper

#define aMthExpr(...) ( (OBJ)atMthExpr(__VA_ARGS__) )

#define atMthExpr(S,A,...) \
  atMthExprN(COS_PP_NARG(__VA_ARGS__), S, A, __VA_ARGS__)

#define atMthExprN(N,S,A,...) \
  COS_PP_CAT(MthExpr_init,N)( &(struct COS_PP_CAT(MthExpr,N)) { \
    {{ cos_object_auto(COS_PP_CAT(MthExpr,N)) }}, \
    S, 0, -1, {__VA_ARGS__}, A }, __FILE__, __LINE__)

// ----- utils

static void*
cloneArgs(SEL sel, char *_args)
{
  U32   size = sel->argsize;
  char *args = 0;
  
  // generic has monomorphic arguments
  if (size) {
    U32 narg = COS_GEN_NARG(sel) - COS_GEN_RNK(sel);
    
    // sanity check
    assert(args);
    assert(narg);
  
    args = malloc(size);
    if (!args) THROW(ExBadAlloc);
    
    // all arguments are OBJects
    if (COS_GEN_OARG(sel)) {
      OBJ *dst = (OBJ*)   args;
      OBJ *src = (OBJ*)  _args;
      OBJ *end = (OBJ*) (_args + size);
      
      // sanity check
      assert(size >= narg*sizeof(OBJ));
      
      while (src < end) {
        *dst++ = *src ? gretain(*src) : 0;
         src++;
      }
    }
    
    // some/all arguments aren't OBJect
    else {
      // sanity check
      assert(sel->arginfo[0].offset == 0);
      
      memcpy(args, _args, size);
    
      for (U32 idx = 0; idx < narg; idx++)
        if (!sel->arginfo[idx].size) { // convention for objects
          OBJ *obj = (OBJ*) (args + sel->arginfo[idx].offset);
          if (*obj) *obj = gretain(*obj);
        }
    }
  }

  return args;
}

static void
deleteArgs(SEL sel, char *args)
{
  U32 size = sel->argsize;
  
  // generic has monomorphic arguments
  if (size) {
    U32 narg = COS_GEN_NARG(sel) - COS_GEN_RNK(sel);
    
    // sanity check
    assert(args);
    assert(narg);

    // all arguments are OBJects
    if (COS_GEN_OARG(sel)) {
      OBJ *obj = (OBJ*)  args;
      OBJ *end = (OBJ*) (args + size);
      
      // sanity check
      assert(size >= narg*sizeof(OBJ));
      
      while (obj < end) {
        if (*obj) grelease(*obj);
        ++obj;
      }
    }

    // some/all arguments aren't OBJect
    else {
      // sanity check
      assert(sel->arginfo[0].offset == 0);
      
      for (U32 idx = 0; idx < narg; idx++)
        if (!sel->arginfo[idx].size) { // convention for objects
          OBJ *obj = (OBJ*) (args + sel->arginfo[idx].offset);
          if (*obj) grelease(*obj);
        }
    }
    
    free(args);
  }
}

// ----- initializer

#undef  DEFFUNC
#define DEFFUNC(N) \
\
static struct Functor* COS_PP_CAT(MthExpr_init,N) \
(struct COS_PP_CAT(MthExpr,N) *fun, STR file, int line) \
{ \
  test_assert(COS_GEN_ORET(fun->sel), "invalid method expression, " \
                                      "returned value must be an object"); \
  test_assert(!COS_GEN_VARG(fun->sel),"invalid method expression, " \
                                      "variadic generic not supported"); \
\
  fun->msk = Functor_getMask(fun->arg, N, file, line); \
\
  return &fun->MthExpr.Functor; \
}

DEFFUNC(1)
DEFFUNC(2)
DEFFUNC(3)
DEFFUNC(4)
DEFFUNC(5)

// ----- ctors

// TODO

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(MthExpr,N), COS_PP_CAT(MthExpr,N)) \
  self->sel  = self2->sel; \
  self->msk  = self2->msk; \
  self->ary  = self2->ary; \
  self->args = 0; \
\
  for (int i = 0; i < N; i++) \
    self->arg[i] = isIdx(self->msk, i) ? self2->arg[i] : gretain(self2->arg[i]); \
\
  self->args = cloneArgs(self2->sel, self2->args); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ----- dtors

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, gdeinit, COS_PP_CAT(MthExpr,N)) \
  for (int i = 0; i < N; i++) \
    if (!isIdx(self->msk, i)) grelease(self->arg[i]); \
\
  deleteArgs(self->sel, self->args); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ----- arity

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(I32, garity, COS_PP_CAT(MthExpr,N)) \
  if (self->ary == -1) \
    self->ary = Functor_getArity(self->arg, N, self->msk); \
\
  retmethod(self->ary); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ----- name

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(STR, gstr, COS_PP_CAT(MthExpr,N)) \
  retmethod(self->sel->str); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ---- eval (stack-like environment)

defmethod(OBJ, gevalEnv, MthExpr1, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);

  IMP1 mth = cos_method_fastLookup1(sel, aid0);

  mth(sel, arg0, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr2, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);

  IMP2 mth = cos_method_fastLookup2(sel, aid0, aid1);

  mth(sel, arg0, arg1, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr3, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);

  IMP3 mth = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  mth(sel, arg0, arg1, arg2, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr4, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);

  IMP4 mth = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  mth(sel, arg0, arg1, arg2, arg3, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr5, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  U32 aid4 = cos_object_id(arg4);

  IMP5 mth = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  mth(sel, arg0, arg1, arg2, arg3, arg4, self->args, _ret);
endmethod

// ---- eval (generic environement)

defmethod(OBJ, gevalEnv, MthExpr1, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);

  IMP1 mth = cos_method_fastLookup1(sel, aid0);

  mth(sel, arg0, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr2, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);

  IMP2 mth = cos_method_fastLookup2(sel, aid0, aid1);

  mth(sel, arg0, arg1, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr3, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);
  OBJ arg2 = getVar(2, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);

  IMP3 mth = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  mth(sel, arg0, arg1, arg2, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr4, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);
  OBJ arg2 = getVar(2, msk, arg, _2);
  OBJ arg3 = getVar(3, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);

  IMP4 mth = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  mth(sel, arg0, arg1, arg2, arg3, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr5, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);
  OBJ arg2 = getVar(2, msk, arg, _2);
  OBJ arg3 = getVar(3, msk, arg, _2);
  OBJ arg4 = getVar(4, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  U32 aid4 = cos_object_id(arg4);

  IMP5 mth = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  mth(sel, arg0, arg1, arg2, arg3, arg4, self->args, _ret);
endmethod

// ---- unrecognizedMessage (ctors)

// ---- 1

defmethod(void, gunrecognizedMessage1, Functor)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1));
endmethod

// ---- 2

defmethod(void, gunrecognizedMessage2, Functor, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

defmethod(void, gunrecognizedMessage2, Object, Functor)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

// ---- 3

defmethod(void, gunrecognizedMessage3, Functor, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, Object, Functor, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Functor)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

// ---- 4

defmethod(void, gunrecognizedMessage4, Functor, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, Functor, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Functor, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Functor)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

// ---- 5

defmethod(void, gunrecognizedMessage5, Functor, Object, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Functor, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Functor, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Functor, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Functor)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod


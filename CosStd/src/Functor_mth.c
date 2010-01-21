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
 | $Id: Functor_mth.c,v 1.21 2010/01/21 14:52:54 ldeniau Exp $
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

#include "Functor.h"
#include "Functor_utl.h"

// ----- type compatibility with messages

STATIC_ASSERT(method1_to_message1_compatibility,
              COS_FIELD_COMPATIBILITY(Message1,MthExpr1,arg));

STATIC_ASSERT(method2_to_message2_compatibility,
              COS_FIELD_COMPATIBILITY(Message2,MthExpr2,arg));

STATIC_ASSERT(method3_to_message3_compatibility,
              COS_FIELD_COMPATIBILITY(Message3,MthExpr3,arg));

STATIC_ASSERT(method4_to_message4_compatibility,
              COS_FIELD_COMPATIBILITY(Message4,MthExpr4,arg));

STATIC_ASSERT(method5_to_message5_compatibility,
              COS_FIELD_COMPATIBILITY(Message5,MthExpr5,arg));

// ----- automatic ctor (private)

#define aMthExpr(...) ( (OBJ)atMthExpr(__VA_ARGS__) )

#define atMthExpr(S,A,...) \
  atMthExprN(COS_PP_NARG(__VA_ARGS__), S, A, __VA_ARGS__)

#define atMthExprN(N,S,A,...) \
  COS_PP_CAT(MthExpr_init,N)( &(struct COS_PP_CAT(MthExpr,N)) { \
    {{{ cos_object_auto(COS_PP_CAT(MthExpr,N)) }, 0 }, S }, A, \
    {__VA_ARGS__}, \
    { COS_PP_DUP(COS_PP_SUB(8,N), 0,) 0 }, \
    { COS_PP_DUP(COS_PP_SUB(8,N), 0,) 0 }, \
    { COS_PP_DUP(COS_PP_SUB(N,1), 0,) 0 }, 0, 0 })

// ----- utils

static U32
getOffs(SEL sel, U16 off[], U8 idx[], U8 pos[])
{
  U32 nrcv = COS_GEN_RNK (sel);
  U32 narg = COS_GEN_NARG(sel);
  U32 noff = 9-nrcv;
  U32 i, j;

  if (!sel->argsize) {  // only receivers
    for (i = 0; i < nrcv; i++)
      pos[i] = i;

    return 0;
  }

  assert(sel->rcvinfo); // sanity check
  assert(sel->arginfo); // sanity check
  
  for (i = 0; i < nrcv; i++)
    pos[i] = sel->rcvinfo[i].objidx;

  for (i = j = 0; i < narg && j < noff; i++)
    if ( cos_arginfo_isObject(sel->arginfo+i) ) {
      off[j] = sel->arginfo[i].offset;
      idx[j] = sel->arginfo[i].objidx;
      j++;
    }

  return j;
}

static COS_ALWAYS_INLINE U32
optArgs(U16 off[], U8 idx[], I32 noff, U32 msk)
{
  I32 i = 0, j = noff-1;

  while (i < j)
    if (!isArg(msk, idx[i]))
      i++; // expr
    else { // swap
      U16 toff = off[j]; off[j] = off[i]; off[i] = toff;
      U8  tidx = idx[j]; idx[j] = idx[i]; idx[i] = tidx;
      j--;
    }
    
  return i;
}

enum { MTH_ISEXPR, MTH_ISCLOSED, MTH_ISMESS };

static COS_ALWAYS_INLINE int
getMthType(U32 msk, OBJ arg[], U8 pos[], U32 n, U32 nexp)
{
  if (nexp) return MTH_ISEXPR;

  U32 i, narg = 0;
  
  for (i = 0; i < n; i++) {
    if (isArg(msk, pos[i])) ++narg;

    else
    if (!isIdx(msk, pos[i]) || i - narg != getIdx(arg[i]))
      break;
  }
       
  return i == n ? (!narg ? MTH_ISMESS : MTH_ISCLOSED) : MTH_ISEXPR;
}

// ----- initializer

#undef  DEFFUNC
#define DEFFUNC(N) \
\
static struct Functor* COS_PP_CAT(MthExpr_init,N) \
(struct COS_PP_CAT(MthExpr,N) *mth) \
{ \
  U32 *msk = &mth->MthExpr.Functor.msk; \
  SEL  sel =  mth->MthExpr.sel; \
\
  test_assert(COS_GEN_ORET(sel), \
              "invalid method expression, returned value must be an object"); \
  test_assert(!COS_GEN_VARG(sel), \
              "invalid method expression, variadic generic not supported"); \
\
  mth->noff = getOffs(sel, mth->off, mth->idx, mth->pos); \
\
  for (U32 i = 0; i < N; i++) \
    Functor_setMask(msk, mth->pos[i], mth->rcv+i); \
\
  if (mth->noff) { \
    for (U32 i = 0; i < mth->noff; i++) \
      Functor_setMask(msk, mth->idx[i], (OBJ*)(mth->arg+mth->off[i])); \
\
    mth->nexp = optArgs(mth->off, mth->idx, mth->noff, *msk); \
  } \
\
  switch(getMthType(*msk, mth->rcv, mth->pos, N, mth->nexp)) { \
  case MTH_ISMESS: \
    cos_object_setId((OBJ)mth, cos_class_id(classref(COS_PP_CAT(Message,N)))); \
    break; \
\
  COS_PP_IF(COS_PP_GT(N,4))(, \
  case MTH_ISCLOSED: \
    cos_object_setId((OBJ)mth, cos_class_id(classref(COS_PP_CAT(SMthExpr,N))));\
    break; \
  ) \
  case MTH_ISEXPR: \
    if (getPar(*msk))\
      cos_object_setId((OBJ)mth,cos_class_id(classref(COS_PP_CAT(PMthExpr,N))));\
    break; \
  } \
\
  return &mth->MthExpr.Functor; \
}

DEFFUNC(1)
DEFFUNC(2)
DEFFUNC(3)
DEFFUNC(4)
DEFFUNC(5)

// ----- constructor

defalias (OBJ, (ginitWithMth)gnewWithMth, pmFunctor, (SEL)sel, (OBJ*)rcv, (void*)arg);
defmethod(OBJ,  ginitWithMth            , pmFunctor, (SEL)sel, (OBJ*)rcv, (void*)arg)
  OBJ mth = Nil;

  switch(COS_GEN_RNK(sel)) {
  case 1: mth = aMthExpr(sel,arg,rcv[0]); break;
  case 2: mth = aMthExpr(sel,arg,rcv[0],rcv[1]); break;
  case 3: mth = aMthExpr(sel,arg,rcv[0],rcv[1],rcv[2]); break;
  case 4: mth = aMthExpr(sel,arg,rcv[0],rcv[1],rcv[2],rcv[3]); break;
  case 5: mth = aMthExpr(sel,arg,rcv[0],rcv[1],rcv[2],rcv[3],rcv[4]); break;
  }

  retmethod( gclone(mth) );
endmethod

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(MthExpr,N), COS_PP_CAT(MthExpr,N)) \
  U32 msk = self2->MthExpr.Functor.msk; \
  SEL sel = self2->MthExpr.sel; \
\
  self->MthExpr.Functor.msk = msk; \
  self->MthExpr.sel = sel; \
  self->arg = 0; \
\
  for (U32 i = 0; i < N; i++) \
    self->rcv[i] = isIdx(msk, self2->pos[i]) \
      ? self2->rcv[i] : gretain(self2->rcv[i]); \
\
  if (self2->arg) \
    self->arg = Functor_cloneArgs(sel, self2->arg); \
\
  memcpy(self->off, self2->off, \
         sizeof *self - offsetof(struct COS_PP_CAT(MthExpr,N), off)); \
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
  U32 msk = self->MthExpr.Functor.msk; \
  SEL sel = self->MthExpr.sel; \
\
  for (int i = 0; i < N; i++) \
    if (!isIdx(msk, self->pos[i])) grelease(self->rcv[i]); \
\
  if (self->arg) \
    Functor_deleteArgs(sel, self->arg); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ----- str

defmethod(STR, gstr, MthExpr)
  retmethod(self->sel->str);
endmethod

// ---- eval (stack-like environment with full evaluation)

#define CALL_METHOD(...) \
  do { \
    if (!mth->nexp) \
      imp(sel, __VA_ARGS__, mth->arg, _ret); \
    else { \
      MAKE_ARG_COPY; \
      imp(sel, __VA_ARGS__, arg, _ret); \
    } \
  } while(0)

#define RETURN_METHOD(...) \
  do { \
    if (!mth->arg) \
      retmethod( gautoDelete(aMthExpr(sel, 0, __VA_ARGS__)) ); \
    else { \
      MAKE_ARG_COPY; \
      retmethod( gautoDelete(aMthExpr(sel, (void*)arg, __VA_ARGS__)) ); \
    } \
  } while(0)

#define MAKE_ARG_COPY \
  struct cos_mem_alignment arg[sel->argsize/sizeof(struct cos_mem_alignment)+1];\
  memcpy(arg, mth->arg, sel->argsize); \
  for (U32 i = mth->nexp; i-- ;) \
    GETOFFS(mth->idx[i], msk, (OBJ*)((char*)arg+mth->off[i]), var, size, _2)

#define GETOFFS(...) getArgOff(__VA_ARGS__)

defmethod(OBJ, gevalEnv, MthExpr1, Array)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  IMP1 imp = cos_method_fastLookup1(sel, aid0);

  struct MthExpr1 *mth = self;

  CALL_METHOD(arg0);
endmethod

defmethod(OBJ, gevalEnv, MthExpr2, Array)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = self;

  CALL_METHOD(arg0, arg1);
endmethod

defmethod(OBJ, gevalEnv, MthExpr3, Array)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(idx[2], msk, arg[2], var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);
  
  struct MthExpr3 *mth = self;

  CALL_METHOD(arg0, arg1, arg2);
endmethod

defmethod(OBJ, gevalEnv, MthExpr4, Array)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(idx[2], msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(idx[3], msk, arg[3], var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = self;

  CALL_METHOD(arg0, arg1, arg2, arg3);
endmethod

defmethod(OBJ, gevalEnv, MthExpr5, Array)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(idx[2], msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(idx[3], msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(idx[4], msk, arg[4], var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  U32 aid4 = cos_object_id(arg4);
  IMP5 imp = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  struct MthExpr5 *mth = self;

  CALL_METHOD(arg0, arg1, arg2, arg3, arg4);
endmethod

// ---- eval (stack-like environment with partial evaluation)

defmethod(OBJ, gevalEnv, PMthExpr1, Array)
  U32  msk = self->MthExpr1.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr1.MthExpr.sel;
  OBJ *arg = self->MthExpr1.rcv;
  U8  *idx = self->MthExpr1.pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);

  struct MthExpr1 *mth = &self->MthExpr1;

  RETURN_METHOD(arg0);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr2, Array)
  U32  msk = self->MthExpr2.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr2.MthExpr.sel;
  OBJ *arg = self->MthExpr2.rcv;
  U8  *idx = self->MthExpr2.pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);

  struct MthExpr2 *mth = &self->MthExpr2;

  RETURN_METHOD(arg0,arg1);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr3, Array)
  U32  msk = self->MthExpr3.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr3.MthExpr.sel;
  OBJ *arg = self->MthExpr3.rcv;
  U8  *idx = self->MthExpr3.pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(idx[2], msk, arg[2], var, size, _2);

  struct MthExpr3 *mth = &self->MthExpr3;

  RETURN_METHOD(arg0,arg1,arg2);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr4, Array)
  U32  msk = self->MthExpr4.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr4.MthExpr.sel;
  OBJ *arg = self->MthExpr4.rcv;
  U8  *idx = self->MthExpr4.pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(idx[2], msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(idx[3], msk, arg[3], var, size, _2);

  struct MthExpr4 *mth = &self->MthExpr4;

  RETURN_METHOD(arg0,arg1,arg2,arg3);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr5, Array)
  U32  msk = self->MthExpr5.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr5.MthExpr.sel;
  OBJ *arg = self->MthExpr5.rcv;
  U8  *idx = self->MthExpr5.pos;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(idx[0], msk, arg[0], var, size, _2);
  OBJ arg1 = getArg(idx[1], msk, arg[1], var, size, _2);
  OBJ arg2 = getArg(idx[2], msk, arg[2], var, size, _2);
  OBJ arg3 = getArg(idx[3], msk, arg[3], var, size, _2);
  OBJ arg4 = getArg(idx[4], msk, arg[4], var, size, _2);

  struct MthExpr5 *mth = &self->MthExpr5;

  RETURN_METHOD(arg0,arg1,arg2,arg3,arg4);
endmethod

// ---- eval (generic environement with full evaluation)

#undef  GETOFFS
#define GETOFFS(a,b,c,d,e,f) getArgVarOff(a,b,c,f)

defmethod(OBJ, gevalEnv, MthExpr1, Collection)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);

  U32 aid0 = cos_object_id(arg0);
  IMP1 imp = cos_method_fastLookup1(sel, aid0);

  struct MthExpr1 *mth = self;

  CALL_METHOD(arg0);
endmethod

defmethod(OBJ, gevalEnv, MthExpr2, Collection)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = self;

  CALL_METHOD(arg0, arg1);
endmethod

defmethod(OBJ, gevalEnv, MthExpr3, Collection)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);
  OBJ arg2 = getArgVar(idx[2], msk, arg[2], _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = self;

  CALL_METHOD(arg0, arg1, arg2);
endmethod

defmethod(OBJ, gevalEnv, MthExpr4, Collection)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);
  OBJ arg2 = getArgVar(idx[2], msk, arg[2], _2);
  OBJ arg3 = getArgVar(idx[3], msk, arg[3], _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = self;

  CALL_METHOD(arg0, arg1, arg2, arg3);
endmethod

defmethod(OBJ, gevalEnv, MthExpr5, Collection)
  U32  msk = self->MthExpr.Functor.msk;
  SEL  sel = self->MthExpr.sel;
  OBJ *arg = self->rcv;
  U8  *idx = self->pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);
  OBJ arg2 = getArgVar(idx[2], msk, arg[2], _2);
  OBJ arg3 = getArgVar(idx[3], msk, arg[3], _2);
  OBJ arg4 = getArgVar(idx[4], msk, arg[4], _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  U32 aid4 = cos_object_id(arg4);
  IMP5 imp = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  struct MthExpr5 *mth = self;

  CALL_METHOD(arg0, arg1, arg2, arg3, arg4);
endmethod

// ---- eval (generic environement with partial evaluation)

defmethod(OBJ, gevalEnv, PMthExpr1, Collection)
  U32  msk = self->MthExpr1.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr1.MthExpr.sel;
  OBJ *arg = self->MthExpr1.rcv;
  U8  *idx = self->MthExpr1.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);

  struct MthExpr1 *mth = &self->MthExpr1;

  RETURN_METHOD(arg0);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr2, Collection)
  U32  msk = self->MthExpr2.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr2.MthExpr.sel;
  OBJ *arg = self->MthExpr2.rcv;
  U8  *idx = self->MthExpr2.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);

  struct MthExpr2 *mth = &self->MthExpr2;

  RETURN_METHOD(arg0,arg1);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr3, Collection)
  U32  msk = self->MthExpr3.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr3.MthExpr.sel;
  OBJ *arg = self->MthExpr3.rcv;
  U8  *idx = self->MthExpr3.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);
  OBJ arg2 = getArgVar(idx[2], msk, arg[2], _2);

  struct MthExpr3 *mth = &self->MthExpr3;

  RETURN_METHOD(arg0,arg1,arg2);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr4, Collection)
  U32  msk = self->MthExpr4.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr4.MthExpr.sel;
  OBJ *arg = self->MthExpr4.rcv;
  U8  *idx = self->MthExpr4.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);
  OBJ arg2 = getArgVar(idx[2], msk, arg[2], _2);
  OBJ arg3 = getArgVar(idx[3], msk, arg[3], _2);

  struct MthExpr4 *mth = &self->MthExpr4;

  RETURN_METHOD(arg0,arg1,arg2,arg3);
endmethod

defmethod(OBJ, gevalEnv, PMthExpr5, Collection)
  U32  msk = self->MthExpr5.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr5.MthExpr.sel;
  OBJ *arg = self->MthExpr5.rcv;
  U8  *idx = self->MthExpr5.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);
  OBJ arg2 = getArgVar(idx[2], msk, arg[2], _2);
  OBJ arg3 = getArgVar(idx[3], msk, arg[3], _2);
  OBJ arg4 = getArgVar(idx[4], msk, arg[4], _2);

  struct MthExpr5 *mth = &self->MthExpr5;

  RETURN_METHOD(arg0,arg1,arg2,arg3,arg4);
endmethod

// ---- unrecognizedMessage (Expression ctors)

// ---- 1

defmethod(void, gunrecognizedMessage1, Expression)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1));
endmethod

// ---- 2

defmethod(void, gunrecognizedMessage2, Expression, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

defmethod(void, gunrecognizedMessage2, Object, Expression)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

// ---- 3

defmethod(void, gunrecognizedMessage3, Expression, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, Object, Expression, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Expression)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

// ---- 4

defmethod(void, gunrecognizedMessage4, Expression, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, Expression, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Expression, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Expression)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

// ---- 5

defmethod(void, gunrecognizedMessage5, Expression, Object, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Expression, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Expression, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Expression, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Expression)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

// ---- unrecognizedMessage (ExpressionSurrogate ctors)

#define ES ExpressionSurrogate

// ---- 1

defmethod(void, gunrecognizedMessage1, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1));
endmethod

// ---- 2

defmethod(void, gunrecognizedMessage2, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

defmethod(void, gunrecognizedMessage2, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

defmethod(void, gunrecognizedMessage2, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2));
endmethod

// ---- 3

defmethod(void, gunrecognizedMessage3, ES, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, Object, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, ES, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, ES, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, Object, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

defmethod(void, gunrecognizedMessage3, ES, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3));
endmethod

// ---- 4

defmethod(void, gunrecognizedMessage4, ES, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, ES, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, ES, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, Object, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, ES, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, ES, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, Object, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, ES, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, ES, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, Object, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, Object, ES, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

defmethod(void, gunrecognizedMessage4, ES, ES, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4));
endmethod

// ---- 5

defmethod(void, gunrecognizedMessage5, ES, Object, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, Object, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, ES, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, ES, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, ES, Object, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, Object, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, Object, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, Object, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, ES, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, ES, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, ES, ES, Object)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, Object, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, Object, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, Object, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, ES, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, ES, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, ES, Object, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, Object, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, Object, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, Object, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, Object, ES, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, Object, ES, ES, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod

defmethod(void, gunrecognizedMessage5, ES, ES, ES, ES, ES)
  *(OBJ*)_ret = gautoDelete(aMthExpr(_sel, _arg, _1, _2, _3, _4, _5));
endmethod



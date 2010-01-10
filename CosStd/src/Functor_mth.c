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
 | $Id: Functor_mth.c,v 1.8 2010/01/10 01:11:42 ldeniau Exp $
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

defclass(MthExpr1, MthExpr)
  char *arg;    // arguments
  OBJ   rcv[1]; // receivers
  U16   off[8]; // arguments OBJects offsets
  U8    idx[8]; // arguments OBJects indexes
  U8    pos[1]; // receivers indexes as OBJects 
  U8    noff;   // number of arguments offsets
  U8    nexp;   // number of arguments expressions
endclass

defclass(MthExpr2, MthExpr)
  char *arg;
  OBJ   rcv[2];
  U16   off[7];
  U8    idx[7];
  U8    pos[2];
  U8    noff;
  U8    nexp;
endclass

defclass(MthExpr3, MthExpr)
  char *arg;
  OBJ   rcv[3];
  U16   off[6];
  U8    idx[6];
  U8    pos[3];
  U8    noff;
  U8    nexp;
endclass

defclass(MthExpr4, MthExpr)
  char *arg;
  OBJ   rcv[4];
  U16   off[5];
  U8    idx[5];
  U8    pos[4];
  U8    noff;
  U8    nexp;
endclass

defclass(MthExpr5, MthExpr)
  char *arg;
  OBJ   rcv[5];
  U16   off[4];
  U8    idx[4];
  U8    pos[5];
  U8    noff;
  U8    nexp;
endclass

makclass(MthExpr , Functor);
makclass(MthExpr1, MthExpr);
makclass(MthExpr2, MthExpr);
makclass(MthExpr3, MthExpr);
makclass(MthExpr4, MthExpr);
makclass(MthExpr5, MthExpr);

// ----- partially evaluated method

defclass(MthPart1, MthExpr1) endclass
defclass(MthPart2, MthExpr2) endclass
defclass(MthPart3, MthExpr3) endclass
defclass(MthPart4, MthExpr4) endclass
defclass(MthPart5, MthExpr5) endclass

makclass(MthPart1, MthExpr1);
makclass(MthPart2, MthExpr2);
makclass(MthPart3, MthExpr3);
makclass(MthPart4, MthExpr4);
makclass(MthPart5, MthExpr5);

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
    { COS_PP_DUP(COS_PP_SUB(N,1), 0,) 0 }, \
    0, 0 }, __FILE__, __LINE__)

// ----- utils

static U32
getOffs(SEL sel, U16 off[], U8 idx[], U8 pos[])
{
  U32 nrcv = COS_GEN_RNK (sel);
  U32 narg = COS_GEN_NARG(sel);
  U32 noff = 9-nrcv;
  U32 ircv = 0;
  U32 iarg = 0;
  U32 ioff = 0;
  U32 iobj = 0;

  if (!sel->argsize) {      // only receivers
    while (ircv < nrcv)
      pos[ircv] = ircv, ircv++;
  }
  else
  if (COS_GEN_OARG(sel)) {  // only OBJects
    assert(sel->rcvinfo);   // sanity check

    while ( !(ircv > nrcv && iarg > narg) ) {
      // receiver
      if (ircv < nrcv && ircv+iarg == sel->rcvinfo[ircv].index) {
        pos[ircv] = iobj;
        ircv++, iobj++;
        continue;
      }

      // argument (OBJect)
      if (ioff < noff) {
        off[ioff] = iarg * sizeof(OBJ);
        idx[ioff] = iobj;
        ioff++;
      }
      iarg++, iobj++;
    }
  }
  else {                  // some aren't OBJects
    assert(sel->rcvinfo); // sanity check
    assert(sel->arginfo); // sanity check

    while ( !(ircv > nrcv && iarg > narg) ) {
      // receiver
      if (ircv < nrcv && ircv+iarg == sel->rcvinfo[ircv].index) {
        pos[ircv] = iobj;
        ircv++, iobj++;
        continue;
      }

      // argument (OBJect)
      if (!sel->arginfo[iarg].size) {
        if (ioff < noff) {
          off[ioff] = sel->arginfo[iarg].offset;
          idx[ioff] = iobj;
          ioff++;
        }
        iobj++;
      }
      iarg++;
    }
  }

  return ioff;
}

static inline U32
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

// ----- initializer

#undef  DEFFUNC
#define DEFFUNC(N) \
\
static struct Functor* COS_PP_CAT(MthExpr_init,N) \
(struct COS_PP_CAT(MthExpr,N) *mth, STR file, int line) \
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
    Functor_setMask(msk, mth->pos[i], mth->rcv+i, file, line); \
\
  if (mth->noff) { \
    if (COS_GEN_OARG(sel)) \
      for (U32 i = 0; i < mth->noff; i++) \
        Functor_setMask(msk, mth->idx[i], (OBJ*)mth->arg+i, file, line); \
    else \
      for (U32 i = 0; i < mth->noff; i++) \
        Functor_setMask(msk, mth->idx[i], (OBJ*)(mth->arg+mth->off[i]), file, line); \
\
    mth->nexp = optArgs(mth->off, mth->idx, mth->noff, *msk); \
  } \
\
  if (getPar(*msk)) \
    mth->MthExpr.Functor.Expression.Object.id = \
      cos_class_id(classref(COS_PP_CAT(MthPart,N))); \
\
  return &mth->MthExpr.Functor; \
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
  U32 msk = self2->MthExpr.Functor.msk; \
  SEL sel = self2->MthExpr.sel; \
\
  self->MthExpr.Functor.msk = msk; \
  self->MthExpr.sel = sel; \
  self->arg = 0; \
\
  for (U32 i = 0; i < N; i++) \
    self->rcv[i] = \
      isIdx(msk, self2->pos[i]) ? self2->rcv[i] : gretain(self2->rcv[i]); \
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
    if (!isIdx(msk, self->pos[i])) \
      grelease(self->rcv[i]); \
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
    if (!mth->arg) \
      imp(sel, __VA_ARGS__,   0, _ret); \
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
  cos_alignment_t arg[sel->argsize/sizeof(cos_alignment_t)+1]; \
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

defmethod(OBJ, gevalEnv, MthPart1, Array)
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

defmethod(OBJ, gevalEnv, MthPart2, Array)
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

defmethod(OBJ, gevalEnv, MthPart3, Array)
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

defmethod(OBJ, gevalEnv, MthPart4, Array)
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

defmethod(OBJ, gevalEnv, MthPart5, Array)
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

defmethod(OBJ, gevalEnv, MthExpr1, Container)
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

defmethod(OBJ, gevalEnv, MthExpr2, Container)
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

defmethod(OBJ, gevalEnv, MthExpr3, Container)
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

defmethod(OBJ, gevalEnv, MthExpr4, Container)
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

defmethod(OBJ, gevalEnv, MthExpr5, Container)
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

defmethod(OBJ, gevalEnv, MthPart1, Container)
  U32  msk = self->MthExpr1.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr1.MthExpr.sel;
  OBJ *arg = self->MthExpr1.rcv;
  U8  *idx = self->MthExpr1.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);

  struct MthExpr1 *mth = &self->MthExpr1;

  RETURN_METHOD(arg0);
endmethod

defmethod(OBJ, gevalEnv, MthPart2, Container)
  U32  msk = self->MthExpr2.MthExpr.Functor.msk;
  SEL  sel = self->MthExpr2.MthExpr.sel;
  OBJ *arg = self->MthExpr2.rcv;
  U8  *idx = self->MthExpr2.pos;

  OBJ arg0 = getArgVar(idx[0], msk, arg[0], _2);
  OBJ arg1 = getArgVar(idx[1], msk, arg[1], _2);

  struct MthExpr2 *mth = &self->MthExpr2;

  RETURN_METHOD(arg0,arg1);
endmethod

defmethod(OBJ, gevalEnv, MthPart3, Container)
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

defmethod(OBJ, gevalEnv, MthPart4, Container)
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

defmethod(OBJ, gevalEnv, MthPart5, Container)
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

// ---- unrecognizedMessage (ctors)

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


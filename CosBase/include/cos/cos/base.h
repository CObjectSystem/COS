#ifndef COS_COS_BASE_H
#define COS_COS_BASE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS basics (macros)
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
 | $Id: base.h,v 1.3 2008/10/15 19:18:06 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/base.h>"
#endif

#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_NO
#define COS_DISABLE_YES
#define COS_DISABLE_STATIC_CAST
#define COS_DISABLE_STATIC_ASSERT
#endif

#ifndef COS_DISABLE_NO
#define NO COS_NO
#endif

#ifndef COS_DISABLE_YES
#define YES COS_YES
#endif

#ifndef COS_DISABLE_STATIC_CAST
#define STATIC_CAST(typename,value) COS_STATIC_CAST(typename,value)
#endif

#ifndef COS_DISABLE_STATIC_ASSERT
#define STATIC_ASSERT(tag,cond) COS_STATIC_ASSERT(tag,cond)
#endif

/***********************************************************
 * Implementation
 */

// common constants
#define COS_NO  0
#define COS_YES 1

// convert value (C cast)
#define COS_STATIC_CAST(typename,value) \
        ((typename)(value))

// compile time assert (not perfect...)
#define COS_STATIC_ASSERT(tag,cond) \
        enum { COS_PP_CAT(STATIC_ASSERT__,tag) = 1/(cond) }

// type alignment (not perfect...)
#define COS_TYPE_ALIGNMENT(T) \
        offsetof(struct { char c; T t; },t)

// type layout compatibility (not perfect...)
#define COS_TYPE_COMPATIBILITY(T1,T2) \
        (COS_TYPE_ALIGNMENT(T1) == COS_TYPE_ALIGNMENT(T2) && \
         sizeof(T1) == sizeof(T2))

// struct field layout compatibility (not perfect...)
#define COS_FIELD_COMPATIBILITY(S1,S2,F) \
        (offsetof(struct S1,F) == offsetof(struct S2,F) && \
         sizeof(((struct S1*)0)->F) == sizeof(((struct S2*)0)->F))

// symbols names
#define COS_CLS_NAME(NAME)    COS_PP_CAT(cos_c_  ,NAME)
#define COS_MCL_NAME(NAME)    COS_PP_CAT(cos_c_m ,NAME)
#define COS_PCL_NAME(NAME)    COS_PP_CAT(cos_c_pm,NAME)
#define COS_GEN_NAME(NAME)    COS_PP_CAT(cos_g_  ,NAME)
#define COS_NXT_NAME(NAME)    COS_PP_CAT(cos_n_  ,NAME)
#define COS_LNK_NAME(NAME,C)  COS_PP_CAT(cos_l_  ,COS_SUB_NAME(NAME,C))
#define COS_MTH_NAME(NAME,CS) COS_PP_CAT(cos_m_  ,COS_SYM_NAME(NAME,CS))
#define COS_FCT_NAME(NAME,CS) COS_PP_CAT(cos_f_  ,COS_SYM_NAME(NAME,CS))

// symbols infos
#define COS_CLS_RANK(NAME)    COS_PP_CAT(cos_k_  ,NAME)
#define COS_MCL_RANK(NAME)    COS_PP_CAT(cos_k_m ,NAME)
#define COS_PCL_RANK(NAME)    COS_PP_CAT(cos_k_pm,NAME)
#define COS_GEN_TYPE(NAME)    COS_PP_CAT(cos_G_  ,NAME)
#define COS_NXT_TYPE(NAME)    COS_PP_CAT(cos_N_  ,NAME)

// generics arguments type
#define COS_ARG_TYPE(NAME)    COS_PP_CAT(NAME,_arg_t)

// behavior max ranks
#define COS_CLS_RNKMAX  31
#define COS_GEN_RNKMAX  5
#define COS_MTH_RNKMAX  128

// behavior ids
#define COS_ID_RNK(id)  ((U32)(id) >> COS_ID_RNKSHT)
#define COS_ID_URK(id)  ((U32)(id) |  COS_ID_TAGMSK)
#define COS_ID_TAG(id)  ((U32)(id) &  COS_ID_TAGMSK)
#define COS_ID_TAGMSK   ((U32)0x07FFFFFF) // 2^(32-5)-1
#define COS_ID_RNKSHT   27                // 32 - 5

// reference counting
#define COS_RC_AUTO     ((U32) 0)
#define COS_RC_UNIT     ((U32) 1)
#define COS_RC_LAST     ((U32)-2)
#define COS_RC_STATIC   ((U32)-1)

// mangled names: <sym-name>_<cls1-name>[_..._<cls5-name>]
#define COS_SYM_NAME(NAME,CS) \
        COS_PP_CAT3(NAME,__,COS_PP_CAT(COS_SYM_NAME_,COS_PP_NARG CS) CS)
#define COS_SYM_NAME_1(C1) \
        C1
#define COS_SYM_NAME_2(C1,C2) \
        COS_PP_CAT3(C1,__,C2)
#define COS_SYM_NAME_3(C1,C2,C3) \
        COS_PP_CAT3(COS_SYM_NAME_2(C1,C2),__,C3)
#define COS_SYM_NAME_4(C1,C2,C3,C4) \
        COS_PP_CAT3(COS_SYM_NAME_3(C1,C2,C3),__,C4)
#define COS_SYM_NAME_5(C1,C2,C3,C4,C5) \
        COS_PP_CAT3(COS_SYM_NAME_4(C1,C2,C3,C4),__,C5)

// mangled names: <spr_name>__isSuperOf__<cls_name>
#define COS_SUB_NAME(NAME,C) \
        COS_PP_CAT3(C,__isSuperOf__,NAME)

// declaration parsing: name OR (name)alias -> <name> | <alias | name>
#define COS_DCL_GNAME(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PP_SWAP((COS_PP_PART a),COS_PP_ARG1),a)
#define COS_DCL_LNAME(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PP_EAT a,a)

// parameters parsing: (type)name -> <type name> | <type> | <name>
#define COS_PRM_DECL(a) \
        COS_PP_SWAP((COS_PP_PART a),COS_PP_PAIR)
#define COS_PRM_TYPE(a) \
        COS_PP_SWAP((COS_PP_PART a),COS_PP_ARG1)
#define COS_PRM_NAME(a) \
        COS_PP_EAT a
#define COS_PRM_IDX(a,b) \
        COS_PP_IF(COS_PP_ISTUPLE(b))(a,COS_PP_INCR(a))

// signature generators
#define COS_SIG_GEN(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_TYPE(a),OBJ_as_SEL)
#define COS_SIG_GENF(a,n) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_DECL(a),OBJ COS_PP_CAT(_,n))
#define COS_SIG_NXT(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_TYPE(a),void*)
#define COS_SIG_NXTF(a,n) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_DECL(a),void* COS_PP_CAT(_,n))
#define COS_SIG_NXTM(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_TYPE(a),struct a*)

// selector-list generators
#define COS_SEL_DECL(N) /* */ COS_PP_TAKE(N, \
        (OBJ const _1, OBJ const _2, OBJ const _3, OBJ const _4, OBJ const _5) )
#define COS_SEL_TYPE(N) /* */ COS_PP_TAKE(N, \
        (OBJ, OBJ, OBJ, OBJ, OBJ) )
#define COS_SEL_NAME(N) /* */ COS_PP_TAKE(N, \
        (_1, _2, _3, _4, _5) )
#define COS_SEL_ID(N)   /* */ COS_PP_TAKE(N, \
        (cos_any_id(_1), cos_any_id(_2), cos_any_id(_3), cos_any_id(_4), \
         cos_any_id(_5)) )
#define COS_SLF_TYPE(N) /* */ COS_PP_TAKE(N, \
        (_cos_mth_slf1, _cos_mth_slf2, _cos_mth_slf3, _cos_mth_slf4, _cos_mth_slf5) )
#define COS_SLF_DECL(N) /* */ COS_PP_TAKE(N, \
        (_cos_mth_slf1 self1 = (COS_UNUSED(self1),(_cos_mth_slf1)_1);, \
         _cos_mth_slf2 self2 = (COS_UNUSED(self2),(_cos_mth_slf2)_2);, \
         _cos_mth_slf3 self3 = (COS_UNUSED(self3),(_cos_mth_slf3)_3);, \
         _cos_mth_slf4 self4 = (COS_UNUSED(self4),(_cos_mth_slf4)_4);, \
         _cos_mth_slf5 self5 = (COS_UNUSED(self5),(_cos_mth_slf5)_5);) )

// token identification: OBJ, void, va_list and gunrecognizedMessage{1..5}
#define COS_TOK_ISOBJ(a) \
        COS_PP_IF(COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_OBJ_ ,a))) \
          (COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_OBJF_ ,a)()),0)
#define COS_TOK_ISVOID(a) \
        COS_PP_IF(COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_VOID_,a))) \
          (COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_VOIDF_,a)()),0)
#define COS_TOK_ISVALIST(a) \
        COS_PP_IF(COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_VALIST_,a))) \
          (COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_VALISTF_,a)()),0)

#define COS_TOK_OBJ_OBJ           ()
#define COS_TOK_OBJF_OBJ()        ()
#define COS_TOK_VOID_void         ()
#define COS_TOK_VOIDF_void()      ()
#define COS_TOK_VALIST_va_list    ()
#define COS_TOK_VALISTF_va_list() ()

#define COS_TOK_ISGUM(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_GUM_,a))

#define COS_TOK_GUM_gunrecognizedMessage1 ()
#define COS_TOK_GUM_gunrecognizedMessage2 ()
#define COS_TOK_GUM_gunrecognizedMessage3 ()
#define COS_TOK_GUM_gunrecognizedMessage4 ()
#define COS_TOK_GUM_gunrecognizedMessage5 ()

// unused identifier
#define COS_UNUSED(...) \
        (COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),COS_UNUSED_1)))
#define COS_UNUSED_1(NAME) (void)(NAME)

// scope end (;)
#define COS_SCP_END \
        extern int cos_scp_end_

#endif // COS_COS_BASE_H

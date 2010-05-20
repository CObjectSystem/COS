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
 | $Id: base.h,v 1.31 2010/05/20 15:48:16 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/base.h>"
#endif

#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_NO
#define COS_DISABLE_YES
#define COS_DISABLE_STATIC_ASSERT
#define COS_DISABLE_STATIC_CAST
#define COS_DISABLE_objcast
#define COS_DISABLE_dyncast
#define COS_DISABLE_chkcast
#endif

#ifndef COS_DISABLE_NO
#define NO COS_NO
#endif

#ifndef COS_DISABLE_YES
#define YES COS_YES
#endif

#ifndef COS_DISABLE_STATIC_ASSERT
#define STATIC_ASSERT(tag,cond) COS_STATIC_ASSERT(tag,cond)
#endif

#ifndef COS_DISABLE_STATIC_CAST
#define STATIC_CAST(typename,value) COS_STATIC_CAST(typename,value)
#endif

#ifndef COS_DISABLE_objcast
#define objcast(class,object) COS_OBJECT_CAST(class,object)
#endif

#ifndef COS_DISABLE_dyncast
#define dyncast(class,object) COS_OBJECT_DCAST(class,object)
#endif

#ifndef COS_DISABLE_chkcast
#define chkcast(class,object) COS_OBJECT_SCAST(class,object)
#endif

/***********************************************************
 * Implementation
 */

// common constants
#define COS_NO  0
#define COS_YES 1

// logger message levels
#define COS_LOGMSG_TRALL 0
#define COS_LOGMSG_TRACE 1
#define COS_LOGMSG_DEBUG 2
#define COS_LOGMSG_INFO  3
#define COS_LOGMSG_WARN  4
#define COS_LOGMSG_ERROR 5
#define COS_LOGMSG_ABORT 6

// convert value (C cast)
#define COS_STATIC_CAST(type,value) ((type) (value))
        
// convert object (COS cast)
#define COS_OBJECT_CAST(cls,obj) \
((struct cls*) cos_object_cast(obj,classref(cls),__FUNC__,__FILE__,__LINE__))

// convert object (COS downcast)
#define COS_OBJECT_DCAST(cls,obj) \
((struct cls*) cos_object_dcast(obj,classref(cls),__FUNC__,__FILE__,__LINE__))

// convert value (static cast in release mode, dynamic cast in debug mode)
#define COS_OBJECT_SCAST(cls,obj) \
COS_PP_IFNDEF(COS_DEBUG) ( COS_STATIC_CAST(struct cls*, obj), \
                           COS_OBJECT_DCAST(cls, obj) )

// compile time assert
#define COS_STATIC_ASSERT(tag,cond) \
        enum { COS_PP_CAT(COS_ERROR__,tag) = 1/(cond) }

// type alignment
#define COS_TYPE_ALIGNMENT(T) \
        offsetof(struct { char c; T t; },t)

// type layout compatibility (not perfect...)
#define COS_TYPE_COMPATIBILITY(T1,T2) \
        (COS_TYPE_ALIGNMENT(T1) == COS_TYPE_ALIGNMENT(T2) && \
         sizeof(T1) == sizeof(T2))

// struct field layout alignment
#define COS_FIELD_ALIGNMENT(S1,S2,F) \
        (offsetof(struct S1,F) == offsetof(struct S2,F))

// struct field layout compatibility (not perfect...)
#define COS_FIELD_COMPATIBILITY(S1,S2,F) \
        (COS_FIELD_ALIGNMENT(S1,S2,F) && \
         sizeof(((struct S1*)0)->F) == sizeof(((struct S2*)0)->F))

// array size
#define COS_ARRLEN(a) \
        (sizeof (a) / sizeof *(a))

// symbols names
#define COS_CLS_NAME(NAME)    COS_PP_CAT(cos_c_  ,NAME)
#define COS_MCL_NAME(NAME)    COS_PP_CAT(cos_c_m ,NAME)
#define COS_PCL_NAME(NAME)    COS_PP_CAT(cos_c_pm,NAME)
#define COS_DOC_NAME(NAME)    COS_PP_CAT(cos_d_  ,NAME)
#define COS_GEN_NAME(NAME)    COS_PP_CAT(cos_g_  ,NAME)
#define COS_NXT_NAME(NAME)    COS_PP_CAT(cos_n_  ,NAME)
#define COS_LNK_NAME(NAME,C)  COS_PP_CAT(cos_l_  ,COS_SUB_NAME(NAME,C))
#define COS_MTH_NAME(NAME,CS) COS_PP_CAT(cos_m_  ,COS_SYM_NAME(NAME,CS))
#define COS_FCT_NAME(NAME,CS) COS_PP_CAT(cos_f_  ,COS_SYM_NAME(NAME,CS))

// symbol for method specialization predicates
#define COS_CLS_MSPE(NAME)    COS_PP_CAT(cos_s_  ,NAME)
#define COS_MCL_MSPE(NAME)    COS_PP_CAT(cos_s_m ,NAME)
#define COS_PCL_MSPE(NAME)    COS_PP_CAT(cos_s_pm,NAME)

// symbols infos
#define COS_CLS_RANK(NAME)    COS_PP_CAT(cos_k_  ,NAME)
#define COS_MCL_RANK(NAME)    COS_PP_CAT(cos_k_m ,NAME)
#define COS_PCL_RANK(NAME)    COS_PP_CAT(cos_k_pm,NAME)
#define COS_GEN_TYPE(NAME)    COS_PP_CAT(cos_G_  ,NAME)
#define COS_NXT_TYPE(NAME)    COS_PP_CAT(cos_N_  ,NAME)

// property names
#define COS_PRP_NAME(NAME)    COS_PP_CAT(P_      ,NAME)
#define COS_MPR_NAME(NAME)    COS_PP_CAT(mP_     ,NAME)
#define COS_PPR_NAME(NAME)    COS_PP_CAT(pmP_    ,NAME)

// generics return, arguments and receivers type and info
#define COS_RET_TYPE(NAME)    COS_PP_CAT(NAME,_ret_t)
#define COS_ARG_TYPE(NAME)    COS_PP_CAT(NAME,_arg_t)
#define COS_RCV_TYPE(NAME)    COS_PP_CAT(NAME,_rcv_t)
#define COS_ARG_INFO(NAME)    COS_PP_CAT(NAME,_arg_i)
#define COS_RCV_INFO(NAME)    COS_PP_CAT(NAME,_rcv_i)

// symbols location
#define COS_CLS_FILE(NAME)    COS_PP_CAT(NAME,_file_i)
#define COS_CLS_LINE(NAME)    COS_PP_CAT(NAME,_line_i)
#define COS_GEN_FILE(NAME)    COS_PP_CAT(NAME,_file_i)
#define COS_GEN_LINE(NAME)    COS_PP_CAT(NAME,_line_i)

// behavior max ranks
#define COS_CLS_RNKMAX  31
#define COS_GEN_RNKMAX  5
#define COS_MTH_RNKMAX  128

// behavior ids
#define COS_ID_RNK(id)  ((U32)(id) >> COS_ID_RNKSHT)
#define COS_ID_URK(id)  ((U32)(id) |  COS_ID_TAGMSK)
#define COS_ID_TAG(id)  ((U32)(id) &  COS_ID_TAGMSK)
#define COS_ID_TAGMSK   ((U32)0x07FFFFFF) // 2^(32-5)-1
#define COS_ID_RNKSHT   27                //    32-5
#define COS_ID_TENMEGA  ((U32)0xDDE54F81)
#define COS_ID_INVALID  ((U32)0xDEADC0DE)

// reference counting
#define COS_RC_STATIC   ((I32)-1)
#define COS_RC_AUTO     ((I32) 0)
#define COS_RC_UNIT     ((I32) 1)
#define COS_RC_INVALID  ((I32)0xDEADC0DE)

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

// declaration of property name: (class)property
#define COS_DCL_PNAME(a) \
        (COS_PRP_NAME(COS_DCL_GNAME(a)))COS_DCL_LNAME(a)

// declaration of generic name: (class)generic
#define COS_DCL_GCLASS(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a)) \
          (COS_PP_SWAP((COS_PP_PART a),COS_PP_ARG1),Generic)

// declaration of property name: (super-property)property
#define COS_DCL_PCLASS(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a)) \
          (COS_PRP_NAME(COS_PP_SWAP((COS_PP_PART a),COS_PP_ARG1)),Property)

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
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_TYPE(a),OBJ_as_RCV)
#define COS_SIG_GENF(a,n) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_DECL(a),OBJ COS_PP_CAT(_,n))
#define COS_SIG_NXT(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_TYPE(a),void*)
#define COS_SIG_NXTF(a,n) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_DECL(a),void* COS_PP_CAT(_,n))
#define COS_SIG_NXTM(a) \
        COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_TYPE(a),COS_RCV_TYPE(a)*)

// selector-list generators
#define COS_SEL_DECL(N) /* */ COS_PP_TAKE(N, \
        (OBJ const _1, OBJ const _2, OBJ const _3, OBJ const _4, OBJ const _5))
#define COS_SEL_TYPE(N) /* */ COS_PP_TAKE(N, \
        (OBJ, OBJ, OBJ, OBJ, OBJ) )
#define COS_SEL_NAME(N) /* */ COS_PP_TAKE(N, \
        (_1, _2, _3, _4, _5) )
#define COS_SEL_ID(N)   /* */ COS_PP_TAKE(N, \
        (cos_object_id(_1), cos_object_id(_2), cos_object_id(_3), \
         cos_object_id(_4), cos_object_id(_5)) )

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
#define COS_TOK_ISNIL(a) COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_NIL_,a))
#define COS_TOK_ISGEN(a) COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_GEN_,a))
#define COS_TOK_ISPRP(a) COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_PRP_,a))
#define COS_TOK_ISGUM(a) COS_PP_ISTUPLE(COS_PP_CAT_(COS_TOK_GUM_,a))

#define COS_TOK_NIL_Nil           ()
#define COS_TOK_GEN_Generic       ()
#define COS_TOK_PRP_Property      ()
#define COS_TOK_OBJ_OBJ           ()
#define COS_TOK_OBJF_OBJ()        ()
#define COS_TOK_VOID_void         ()
#define COS_TOK_VOIDF_void()      ()
#define COS_TOK_VALIST_va_list    ()
#define COS_TOK_VALISTF_va_list() ()

#define COS_TOK_GUM_gunrecognizedMessage1 ()
#define COS_TOK_GUM_gunrecognizedMessage2 ()
#define COS_TOK_GUM_gunrecognizedMessage3 ()
#define COS_TOK_GUM_gunrecognizedMessage4 ()
#define COS_TOK_GUM_gunrecognizedMessage5 ()

// unused identifier
#define COS_UNUSED(...) \
        COS_PP_SEPWITH(COS_PP_MAP((__VA_ARGS__),COS_UNUSED_1),;)
#define COS_UNUSED_1(NAME) (void)(NAME)

// scope end (;)
#define COS_SCP_END \
        extern int cos_scp_end_

#endif // COS_COS_BASE_H

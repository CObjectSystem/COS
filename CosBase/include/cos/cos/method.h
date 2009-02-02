#ifndef COS_COS_METHOD_H
#define COS_COS_METHOD_H

/*
 o---------------------------------------------------------------------o
 |
 | COS method (macros)
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
 | $Id: method.h,v 1.20 2009/02/02 09:30:52 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/method.h>"
#endif

/* NOTE-USER: definition and instantiation

   method-definition:
     defmethod( generic-specifier )
       method-statement
     endmethod

   method-statement:
     statement
     statement-with-contract

   next-method-declaration:
     defnext( generic-specifier );

   where in the context of methods:
     - the param-name_opt in param-decl can be omitted for unused argument.
     - the last param-decl must be (va_list)va for variadic generics.

   examples:
     defmethod(OBJ, gclone   , Object)                        .. endmethod
     defmethod(OBJ, ggetAt   , Array, Range)                  .. endmethod
     defmethod(OBJ, ggetAtIdx, Array, (U32)idx)               .. endmethod
     defmethod(OBJ, gprint   , Stream, String)                .. endmethod
     defmethod(OBJ, vprintFmt, Stream, (STR)fmt, (va_list)va) .. endmethod
*/

/* NOTE-USER: tracing defmethod

   - defmethod can be traced both when entering and exiting using
     #define COS_METHOD_TRACE // enable  trace
     #undef  COS_METHOD_TRACE // disable trace
     if the method was compiled with COS_LOGMSG_LEVEL <= COS_LOGMSG_DEBUG
   - the function pointer cos_method_trace (see cos/cos/cosapi.h) will be
     called only if the cos_logmsg_level == COS_LOGMSG_TRACE at runtime.
   - COS_METHOD_TRACE is automatically defined if
     COS_LOGMSG_LEVEL <= COS_LOGMSG_DEBUG
*/

/* method keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_defmethod
#define COS_DISABLE_endmethod
#define COS_DISABLE_retmethod
#define COS_DISABLE_defnext
#define COS_DISABLE_next_method
#define COS_DISABLE_next_method_p
#define COS_DISABLE_forward_message
#define COS_DISABLE_RETVAL
#endif

#ifndef COS_DISABLE_defmethod
#define defmethod(...) COS_MTH_DEF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_endmethod
#define endmethod COS_MTH_END
#endif

#ifndef COS_DISABLE_retmethod
#define retmethod(...) COS_MTH_RET(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_defnext
#define defnext(...) COS_MTH_DEFN(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_next_method
#define next_method(...) COS_MTH_NXT(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_next_method_p
#define next_method_p COS_MTH_NXT_P
#endif

#ifndef COS_DISABLE_forward_message
#define forward_message(...) COS_MTH_FWD(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_RETVAL
#define RETVAL COS_MTH_RETVAL
#endif

/***********************************************************
 * Implementation
 */

/* method definition and instantiation
 */
#define COS_MTH_DEF(  RET,NAME,...) \
        COS_MTH_DEF_0(RET, \
          COS_DCL_GNAME(NAME),COS_DCL_LNAME(NAME), \
          (__VA_ARGS__), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISNTUPLE), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISTUPLE ), \
          COS_PP_ISTUPLE(NAME))

#define COS_MTH_DEF_0(RET,NAME,TAG,PS,CS,AS,T) \
        COS_MTH_DEF_1(RET,NAME,TAG,PS,CS,AS, \
          COS_PP_LEN(CS), \
          COS_PP_ISTUPLE(COS_PP_SEQ(AS)), \
          COS_PP_NOT(COS_TOK_ISVOID(RET)), T)

#define COS_MTH_DEF_1(RET,NAME,TAG,PS,CS,AS,C,A,R,T) \
COS_MTH_MSPECHK(    NAME,TAG,   CS,         T) \
COS_MTH_RANKCHK(    NAME,TAG,   CS,   C,    T) \
COS_MTH_NAMECHK(    NAME,TAG,   CS,         T) \
COS_MTH_TYPECHK(RET,NAME,    PS,CS           ) \
COS_MTH_COMPMAK(    NAME,TAG,   CS,   C,    T) \
COS_MTH_FUNCDEF(RET,NAME,TAG,PS,CS,AS,C,A,R,T) \
COS_CTR_BEGCTR

#define COS_MTH_END   \
  COS_PP_IFDEF(COS_METHOD_TRACE)(COS_MTH_TRC_LOC,/* no trace */) \
  COS_CTR_ENDCTR      \
  goto _cos_mth_fini; \
}

/* next_method definition
 */
#define COS_MTH_DEFN(  RET,NAME,...) \
        COS_MTH_DEFN_0(RET,NAME,(__VA_ARGS__), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISNTUPLE) )

#define COS_MTH_DEFN_0(RET,NAME,PS,CS) \
/* next_method definition */ \
COS_MTH_NEXTDEF(RET,NAME,TAG,PS,CS,COS_PP_LEN(CS),0) \
/* next_method classes */ \
static struct Class* const _cos_mth_nxt_cls[] = \
  { COS_PP_SEQ(COS_PP_MAP(CS,COS_CLS_REF_1))}

/*
 * Low-level implementation
 */

// method specialization check
#define COS_MTH_MSPECHK(NAME,TAG,CS,T) \
  COS_STATIC_ASSERT( \
    COS_PP_CAT(COS_MTH_MNAME(COS_SYM_NAME(NAME,CS),TAG,T), \
      __method_cannot_be_specialized_for_class_predicate_INSTANCE), \
    COS_PP_SEPWITH(COS_PP_MAP(CS,COS_CLS_MSPE),&&));

// method rank check
#define COS_MTH_RANKCHK(NAME,TAG,CS,C,T) \
COS_PP_IF(COS_PP_GE(C,5))( \
  COS_STATIC_ASSERT( \
    COS_PP_CAT3(COS_MTH_MNAME(COS_SYM_NAME(NAME,CS),TAG,T), \
                __method_rank_greater_than_,COS_MTH_RNKMAX), \
    COS_PP_SEPWITH(COS_PP_MAP(CS,COS_CLS_RANK),+) < COS_MTH_RNKMAX); \
,/* always true */)

// method name check
#define COS_MTH_NAMECHK(NAME,TAG,CS,T) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(COS_MTH_MNAME(COS_SYM_NAME(NAME,CS),TAG,T), \
             __name_is_longer_than_256_chars), \
  sizeof(COS_PP_STR(COS_SYM_NAME(NAME,CS))) <= 256);

// method type check
#define COS_MTH_TYPECHK(RET,NAME,PS,CS) \
extern COS_GEN_TYPE(NAME) \
  COS_PP_CAT(COS_SYM_NAME(NAME,CS),__invalid_defmethod_vs_defgeneric); \
extern RET (* \
  COS_PP_CAT(COS_SYM_NAME(NAME,CS),__invalid_defmethod_vs_defgeneric) ) \
                                            COS_PP_MAP(PS,COS_SIG_GEN);

// component intantiation (see cos/cos/coscls.h)
#define COS_MTH_COMPMAK(NAME,TAG,CS,C,T) \
static void COS_MTH_MNAME(COS_FCT_NAME(NAME,CS),TAG,T) \
(SEL _sel, COS_PP_SEQ(COS_SEL_TYPE(C)), void* _arg, void* _ret); \
 \
struct COS_PP_CAT(Method,C) COS_MTH_MNAME(COS_MTH_NAME(NAME,CS),TAG,T) = { \
   /* encode tag into rc */ \
  {{{ 0, cos_tag_method }}, \
   /* reference to generic */ \
   &COS_GEN_NAME(NAME), \
   /* method rank */ \
   COS_MTH_INFO(COS_PP_SEQ(COS_PP_MAP(CS,COS_CLS_RANK)),0,0,0,0,0), \
   /* around method rank */ \
   T }, \
   /* reference to function */ \
   COS_MTH_MNAME(COS_FCT_NAME(NAME,CS),TAG,T), \
   /* references to classes of specialization */ \
   { COS_PP_SEQ(COS_PP_MAP(CS,COS_CLS_REF_1)) } \
};

// method definition
#define COS_MTH_FUNCDEF(RET,NAME,TAG,PS,CS,AS,C,A,R,T) \
static void COS_MTH_MNAME(COS_FCT_NAME(NAME,CS),TAG,T) \
(SEL const restrict _sel, COS_PP_SEQ(COS_SEL_DECL(C)), \
   void* const restrict _arg, void* const restrict _ret) \
{ \
  /* return and arguments type */ \
  typedef COS_RET_TYPE(NAME)* const restrict _cos_mth_ret; \
  typedef COS_ARG_TYPE(NAME)* const restrict _cos_mth_arg; \
  /* selfs types (i.e. _cos_mth_slfn) */ \
  COS_PP_SEP(COS_PP_MAP2(CS,COS_MTH_SLF_TYP(C),COS_MTH_SLF_DEF)) \
  /* next_method definition */ \
  COS_MTH_NEXTDEF(RET,NAME,TAG,PS,CS,C,T) \
  /* next_method classes */ \
  struct Class* const* const restrict _cos_mth_nxt_cls = \
    COS_MTH_MNAME(COS_MTH_NAME(NAME,CS),TAG,T).cls; \
  /* selfs variables */ \
  _cos_mth_slf1* const restrict self = (_cos_mth_slf1*)_1; \
  COS_PP_SEP(COS_MTH_SLF_INI(C)) \
  /* contract variable */ \
  COS_CTR_DCL \
  /* trace variables (if requested) */ \
  COS_PP_IFDEF(COS_METHOD_TRACE)( \
  const struct Method* const restrict _mth = \
    (struct Method*)&COS_MTH_MNAME(COS_MTH_NAME(NAME,CS),TAG,T); \
  OBJ _cos_mth_objs[C]; \
  int _cos_mth_line;,/* no trace */) \
  /* arguments variables initialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEP(COS_PP_MAP(AS,COS_MTH_ARG)),/* no arg */) \
  /* trace entering the method (if requested) */ \
  COS_PP_IFDEF(COS_METHOD_TRACE)(COS_MTH_TRC(1,C),/* no trace */) \
  goto _cos_mth_body; \
  /* exit point */ \
  _cos_mth_fini: \
  /* arguments variables deinitialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEP(COS_PP_MAP(AS,COS_MTH_DEARG)),/* no arg */) \
  /* check invariant (if requested) */ \
  COS_CTR_INVARIANT(C) \
  /* trace exiting the method (if requested) */ \
  COS_PP_IFDEF(COS_METHOD_TRACE)(COS_MTH_TRC(0,C),/* no trace */) \
  return; \
  /* avoid compiler warning for unused identifiers */ \
  COS_PP_IF(R)(/* use ret */,COS_UNUSED(_ret);) \
  COS_UNUSED(_sel,_arg,self,next_method, \
    _cos_mth_nxt_sel,_cos_mth_nxt_rnk,_cos_mth_nxt_rnd,\
    _cos_mth_nxt_cls,_cos_mth_nxt_p); \
  /* method user code */ \
  _cos_mth_body:

// next_method definition
#define COS_MTH_NEXTDEF(RET,NAME,TAG,PS,CS,C,T) \
  /* next_method type */ \
  typedef void (*const _cos_mth_nxt) COS_PP_MAP(PS,COS_SIG_NXTM); \
  /* next_method type (direct case) */ \
  typedef void (*const _cos_mth_nxt_d) \
    (SEL,COS_PP_SEQ(COS_PP_MAP(PS,COS_SIG_NXTM)),void*,void*); \
  /* next_method_p type */ \
  typedef COS_PP_CAT(IMP,C) _cos_mth_nxt_t; \
  /* direct or indirect call */ \
  enum { _cos_mth_nxt_ind = !COS_TOK_ISGUM(NAME) }; \
  /* next_method pointer */ \
  static _cos_mth_nxt_t _cos_mth_nxt_p = (_cos_mth_nxt_t)COS_YES; \
  /* next_method selector */ \
  SEL const _cos_mth_nxt_sel = &COS_GEN_NAME(NAME); \
  /* next_method method rank */ \
  U32 const _cos_mth_nxt_rnk = \
    COS_MTH_INFO(COS_PP_SEQ(COS_PP_MAP(CS,COS_CLS_RANK)),0,0,0,0,0); \
  /* next_method around rank */ \
  U32 _cos_mth_nxt_rnd = \
    COS_PP_IF(T)(COS_MTH_MNAME(COS_MTH_NAME(NAME,CS),TAG,T).Method.arnd,0); \
  /* generic next_method pointer */ \
  void (*const next_method) (COS_PP_SEQ(COS_PP_MAP(PS,COS_SIG_NXT)), \
                             SEL, RET*, _cos_mth_nxt_t) = COS_NXT_NAME(NAME);

// selfs
#define COS_MTH_SLF_DEF(C,T) \
  typedef struct C T;

// argument initialization
#define COS_MTH_ARG(a) \
  COS_PP_IF(COS_PP_ISBLANK(COS_PRM_NAME(a)))(/* unused */, \
  COS_PRM_TYPE(a) COS_PRM_NAME(a) /* declaration */ \
  COS_PP_IF(COS_TOK_ISVALIST(COS_PRM_TYPE(a)))( /* va_list */ \
    ; va_copy(COS_PRM_NAME(a),((_cos_mth_arg)_arg)->COS_PRM_NAME(a)), \
    =                         ((_cos_mth_arg)_arg)->COS_PRM_NAME(a) ); )

// argument deinitialization
#define COS_MTH_DEARG(a) \
  COS_PP_IF(COS_PP_ISBLANK(COS_PRM_NAME(a)))(/* unused */, \
  COS_PP_IF(COS_TOK_ISVALIST(COS_PRM_TYPE(a)))( \
    va_end(COS_PRM_NAME(a));, /* not va_list */) )

// retmethod
#define COS_MTH_RET(...) \
  do { \
    COS_PP_IF(COS_PP_NOARG(__VA_ARGS__))(,COS_MTH_RETVAL = (__VA_ARGS__);) \
    COS_PP_IFDEF(COS_METHOD_TRACE)(_cos_mth_line = __LINE__;,/* no trace */) \
    goto _cos_ctr_end; \
  } while(0)

#define COS_MTH_RETVAL (*(_cos_mth_ret)_ret)

// next_method
#define COS_MTH_NXT(...) \
  /* compile-time check: next_method arguments */ \
  (0 ? ((_cos_mth_nxt)next_method)(__VA_ARGS__) : \
  ( COS_MTH_NXT_INIT, _cos_mth_nxt_ind ? \
  /* indirect invocation */ \
   next_method(__VA_ARGS__,_sel,_ret,_cos_mth_nxt_p) : \
  /* direct invocation */ \
   ((_cos_mth_nxt_d)_cos_mth_nxt_p)(_sel,__VA_ARGS__,_arg,_ret)))

#define COS_MTH_NXT_P \
  /* next_method check */ \
  ( COS_MTH_NXT_INIT, _cos_mth_nxt_p != 0 )

#define COS_MTH_NXT_INIT \
  /* next_method initialization */ \
  (_cos_mth_nxt_p != (_cos_mth_nxt_t)COS_YES ? (void)0 : \
   cos_method_nextInit((FUNC*)(void*)&_cos_mth_nxt_p, \
      _cos_mth_nxt_sel,_cos_mth_nxt_rnk,_cos_mth_nxt_rnd,_cos_mth_nxt_cls))

// forward_message
#define COS_MTH_FWD(...) \
  COS_MTH_FWDN(COS_PP_NARG(__VA_ARGS__),__VA_ARGS__)

#define COS_MTH_FWDN(N,...) \
  do { \
    /* local copy */ \
    COS_PP_SEPWITH( \
      COS_PP_MAP2(COS_MTH_FWD_INI(N),(__VA_ARGS__),COS_PP_PAIR),;); \
    /* method lookup */ \
    COS_PP_CAT(cos_method_fastLookup,N) \
    /* lookup selectors */ \
    (_sel,COS_PP_SEQ(COS_PP_MAP(COS_MTH_FWD_USE(N),cos_any_id))) \
    /* method invocation */ \
    (_sel,COS_PP_SEQ(COS_MTH_FWD_USE(N)),_arg,_ret); \
  } while (0)

// method trace
#if COS_LOGMSG <= COS_LOGMSG_DEBUG
#define COS_METHOD_TRACE
#endif

#define COS_MTH_TRC(E,C) \
  if (cos_logmsg_level_ == COS_LOGMSG_TRACE) { \
    COS_PP_IF(E)(COS_MTH_OBJ_INI(C);,) \
    cos_method_trace(__FILE__, COS_PP_IF(E)(__LINE__,_cos_mth_line), \
                     E, _mth, _cos_mth_objs); \
  }

#define COS_MTH_TRC_LOC \
  if (COS_CONTRACT < COS_CONTRACT_POST || _cos_ctr_st != cos_tag_post) \
    _cos_mth_line = __LINE__;

// method info encoding and decoding
#define COS_MTH_INFO(...) \
  COS_MTH_INFO_0(__VA_ARGS__)

#define COS_MTH_INFO_0(C1,C2,C3,C4,C5,...) \
  ((U32)((C1)+(C2)+(C3)+(C4)+(C5)) << 25 | \
   (U32) (C1)                      << 20 | \
   (U32)      (C2)                 << 15 | \
   (U32)           (C3)            << 10 | \
   (U32)                (C4)       <<  5 | \
   (U32)                     (C5))

#define COS_MTH_RNK(mth) ((mth)->info >> 25 & 0x7F)
#define COS_MTH_RK1(mth) ((mth)->info >> 20 & 0x1F)
#define COS_MTH_RK2(mth) ((mth)->info >> 15 & 0x1F)
#define COS_MTH_RK3(mth) ((mth)->info >> 10 & 0x1F)
#define COS_MTH_RK4(mth) ((mth)->info >>  5 & 0x1F)
#define COS_MTH_RK5(mth) ((mth)->info       & 0x1F)

// method mangled names
#define COS_MTH_MNAME(NAME,TAG,T) \
  COS_PP_IF(T)(COS_PP_CAT3(NAME,COS_PP_CAT3(__a,__LINE__,_),TAG),NAME)
                           
// some constant tuples
#define COS_MTH_SLF_TYP(N) \
  COS_PP_TAKE(N, (_cos_mth_slf1, \
                  _cos_mth_slf2, \
                  _cos_mth_slf3, \
                  _cos_mth_slf4, \
                  _cos_mth_slf5) )

#define COS_MTH_SLF_INI(N) \
  COS_PP_TAKE(N, \
(_cos_mth_slf1* const restrict self1 = (COS_UNUSED(self1),(_cos_mth_slf1*)_1);, \
 _cos_mth_slf2* const restrict self2 = (COS_UNUSED(self2),(_cos_mth_slf2*)_2);, \
 _cos_mth_slf3* const restrict self3 = (COS_UNUSED(self3),(_cos_mth_slf3*)_3);, \
 _cos_mth_slf4* const restrict self4 = (COS_UNUSED(self4),(_cos_mth_slf4*)_4);, \
 _cos_mth_slf5* const restrict self5 = (COS_UNUSED(self5),(_cos_mth_slf5*)_5);) )

#define COS_MTH_FWD_INI(N) \
  COS_PP_TAKE(N, (OBJ _cos_mth_fwd_1 =, \
                  OBJ _cos_mth_fwd_2 =, \
                  OBJ _cos_mth_fwd_3 =, \
                  OBJ _cos_mth_fwd_4 =, \
                  OBJ _cos_mth_fwd_5 =) )

#define COS_MTH_FWD_USE(N) \
  COS_PP_TAKE(N, (_cos_mth_fwd_1, \
                  _cos_mth_fwd_2, \
                  _cos_mth_fwd_3, \
                  _cos_mth_fwd_4, \
                  _cos_mth_fwd_5) )

#define COS_MTH_OBJ_INI(N) \
  COS_PP_TAKE(N, (_cos_mth_objs[0]=_1, \
                  _cos_mth_objs[1]=_2, \
                  _cos_mth_objs[2]=_3, \
                  _cos_mth_objs[3]=_4, \
                  _cos_mth_objs[4]=_5) )

#endif // COS_COS_METHOD_H

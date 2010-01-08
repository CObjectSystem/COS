#ifndef COS_COS_GENERIC_H
#define COS_COS_GENERIC_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generic (macros)
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
 | $Id: generic.h,v 1.28 2010/01/08 18:07:42 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/generic.h>"
#endif

/* NOTE-USER: generic declaration, definition and instantiation

   generic-reference:
     genericref( generic-name-list )

   generic-declaration:
     usegeneric( generic-decl-list );

   generic-decl-list:
     generic-decl
     generic-decl-list , generic-decl

   generic-decl:
     generic-name
     ( generic-name ) local-name

   generic-definition:
     defgeneric( generic-specifier );

   generic-instantiation:
     makgeneric( generic-specifier );

   generic-variadic-definition:
     defgenericv( generic-specifier , ... );

   generic-variadic-instantiation:
     makgenericv( generic-specifier , ... );

   generic-specifier:
     return-type , generic-def , param-list

   generic-def:
     generic-name
     ( class-name ) generic-name

   param-list:
     param-decl
     param-list , param-decl

   param-decl:
     class-name
     ( param-type ) param-name

   {return,param}-type:
     type-name                                      // C99 6.7.6

   {generic,param}-name:
     identifier                                     // C99 6.4.2.1

   - the class-name_opt in param-decl is discarded and can be replaced by
     anything.

   - makgeneric is optional if you use the makefiles provided by COS.

   examples:
     usegeneric(ga,gb,(gc)gfoo);  // declare generics ga, gb, and gc as gfoo

     defgeneric(OBJ, gclone   , _1);                         // rank 1
     defgeneric(OBJ, ggetAt   , _1, _2);                     // rank 2
     defgeneric(OBJ, ggetAt   , _1, at);                     // rank 2
     defgeneric(OBJ, ggetAtIdx, _1, (U32)idx);               // rank 1
     defgeneric(OBJ, gprint   , stream, _2);                 // rank 2
     
     defgeneric(OBJ, (Operator)gadd, _1, _2);                // rank 2

     defgenericv(OBJ, vprintFmt, stream, (STR)fmt, ...);     // rank 1

     makgeneric(OBJ, gprint, _1, _2); // instantiate generic gprint (in .c file)
     makgeneric(OBJ, (Operator)gadd, _1, _2); // gadd is an instance of Operator
*/

/* generic keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_genericref
#define COS_DISABLE_usegeneric
#define COS_DISABLE_defgeneric
#define COS_DISABLE_makgeneric
#define COS_DISABLE_defgenericv
#define COS_DISABLE_makgenericv
#endif

#ifndef COS_DISABLE_genericref
#define genericref(...) COS_GEN_REF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_usegeneric
#define usegeneric(...) COS_GEN_USE(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_defgeneric
#define defgeneric(...) COS_GEN_DEF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_makgeneric
#define makgeneric(...) COS_GEN_MAK(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_defgenericv
#define defgenericv(...) COS_GEN_DEFV(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_makgenericv
#define makgenericv(...) COS_GEN_MAKV(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation
 */

/* NOTE-INFO: Conventions
   PS = all-parameters
   CS = class-parameters (selectors)
   AS = arg-parameters (non-selectors)
   IS = class-indexes
   C  = number of class-parameters
   A  = number of arguments > 0   (bool)
   O  = all arguments are objects (bool)
   R  = return-type is not void   (bool)
*/

/* generic reference
 */
#define COS_GEN_REF(...) \
        COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),COS_GEN_REF_1))

#define COS_GEN_REF_1(NAME) \
        (&COS_GEN_NAME(NAME))

/* generic declaration
 */
#define COS_GEN_USE(...) \
        COS_PP_SEPWITH(COS_PP_MAP((__VA_ARGS__),COS_GEN_USE_0),;)

#define COS_GEN_USE_0(NAME) \
        COS_GEN_USE_1(COS_DCL_GNAME(NAME),COS_DCL_LNAME(NAME))

#define COS_GEN_USE_1(GNAME,LNAME) \
        extern struct Generic COS_GEN_NAME(GNAME); \
        static OBJ const LNAME = (void*)COS_GEN_REF_1(GNAME)

/* generic definition
 */
#define COS_GEN_DEF(  RET,NAME,...) \
        COS_GEN_DEF_0(RET,COS_DCL_LNAME(NAME),(__VA_ARGS__), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISNTUPLE), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISTUPLE ) )

#define COS_GEN_DEF_0(RET,NAME,PS,CS,AS) \
        COS_GEN_DEF_1(RET,NAME,PS,   AS, \
          COS_PP_DROP(1,COS_PP_SCANL(PS,0,COS_PRM_IDX)), \
          COS_PP_LEN(CS), \
          COS_PP_ISTUPLE(COS_PP_SEQ(AS)), \
          COS_PP_NOT(COS_TOK_ISVOID(RET)) )

#define COS_GEN_DEF_1(RET,NAME,PS,AS,IS,C,A,R) \
extern struct Generic COS_GEN_NAME(NAME); \
COS_GEN_TYPEDEF(RET,NAME,PS,AS,   C,A    ) \
COS_GEN_FUNCDEF(RET,NAME,PS,AS,IS,C,A,R  ) \
COS_GEN_NEXTDEF(RET,NAME,PS,AS,IS,C,A,R,0) \
COS_SCP_END

/* generic instantiation
 */
#define COS_GEN_MAK(  RET,NAME,...) \
        COS_GEN_MAK_0(RET,COS_DCL_LNAME(NAME),COS_DCL_GCLASS(NAME), \
          (__VA_ARGS__), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISNTUPLE), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISTUPLE ) )

#define COS_GEN_MAK_0(RET,NAME,CLS,PS,CS,AS) \
        COS_GEN_MAK_1(RET,NAME,CLS,PS,AS,COS_PP_LEN(CS), \
          COS_PP_ISTUPLE(COS_PP_SEQ(AS)), \
          COS_PP_FOLDL(COS_PP_MAP(PS,COS_GEN_OBJ),COS_YES,COS_PP_AND), \
          COS_PP_NOT(COS_TOK_ISVOID(RET)))

#define COS_GEN_MAK_1(RET,NAME,CLS,PS,AS,C,A,O,R) \
COS_GEN_TYPECHK(RET,NAME,    PS                  ) \
COS_GEN_GCLSCHK(    NAME,CLS                     ) \
COS_GEN_RANKCHK(    NAME,          C             ) \
COS_GEN_NAMECHK(    NAME                         ) \
COS_GEN_SIZECHK(    NAME,            A,  R       ) \
COS_GEN_COMPMAK(RET,NAME,CLS,PS,AS,C,A,O,R,COS_NO)

/* variadic generic definition
 */
#define COS_GEN_DEFV(  RET,NAME,...) \
        COS_GEN_DEFV_0(RET,COS_DCL_LNAME(NAME), \
          (COS_PP_SEQ(COS_PP_RDROP(1,(__VA_ARGS__))),(...)), \
          (COS_PP_SEQ(COS_PP_RDROP(1,(__VA_ARGS__))),(va_list)va) )

#define COS_GEN_DEFV_0(RET,NAME,VPS,PS) \
        COS_GEN_DEFV_1(RET,NAME,VPS,PS, \
          COS_PP_FILTER(PS,COS_PP_ISNTUPLE), \
          COS_PP_FILTER(PS,COS_PP_ISTUPLE ) )

#define COS_GEN_DEFV_1(RET,NAME,VPS,PS,CS,AS) \
        COS_GEN_DEFV_2(RET,NAME,VPS,PS,   AS, \
          COS_PP_DROP(1,COS_PP_SCANL(PS,0,COS_PRM_IDX)), \
          COS_PP_LEN(CS), \
          COS_PP_ISTUPLE(COS_PP_SEQ(AS)), \
          COS_PP_NOT(COS_TOK_ISVOID(RET)) )

#define COS_GEN_DEFV_2(RET,NAME,VPS,PS,AS,IS,C,A,R) \
extern struct Generic COS_GEN_NAME(NAME); \
COS_GEN_TYPEDEF(RET,NAME,    PS,AS,   C,A    ) \
COS_GEN_FUNCDCL(RET,NAME,VPS,PS   ,IS,C      ) \
COS_SCP_END

/* variadic generic instantiation
 */
#define COS_GEN_MAKV(  RET,NAME,...) \
        COS_GEN_MAKV_0(RET,COS_DCL_LNAME(NAME),COS_DCL_GCLASS(NAME), \
          (COS_PP_SEQ(COS_PP_RDROP(1,(__VA_ARGS__))),(...)), \
          (COS_PP_SEQ(COS_PP_RDROP(1,(__VA_ARGS__))),(va_list)va) )

#define COS_GEN_MAKV_0(RET,NAME,CLS,VPS,PS) \
        COS_GEN_MAKV_1(RET,NAME,CLS,VPS,PS, \
          COS_PP_FILTER(PS,COS_PP_ISNTUPLE), \
          COS_PP_FILTER(PS,COS_PP_ISTUPLE ) )

#define COS_GEN_MAKV_1(RET,NAME,CLS,VPS,PS,CS,AS) \
        COS_GEN_MAKV_2(RET,NAME,CLS,VPS,PS,   AS, \
          COS_PP_DROP(1,COS_PP_SCANL(PS,0,COS_PRM_IDX)), \
          COS_PP_LEN(CS), \
          COS_PP_GE(COS_PP_LEN(AS),2), \
          COS_PP_FOLDL(COS_PP_MAP(PS,COS_GEN_OBJ),COS_YES,COS_PP_AND), \
          COS_PP_NOT(COS_TOK_ISVOID(RET)) )

#define COS_GEN_MAKV_2(RET,NAME,CLS,VPS,PS,AS,IS,C,A,O,R) \
COS_GEN_TYPECHK(RET,NAME,    PS                      ) \
COS_GEN_GCLSCHK(    NAME,CLS                         ) \
COS_GEN_RANKCHK(    NAME,             C              ) \
COS_GEN_NAMECHK(    NAME                             ) \
COS_GEN_SIZECHK(    NAME,               A,  R        ) \
COS_GEN_VFUNDEF(RET,NAME,   VPS,AS,IS,C,A,  R        ) \
COS_GEN_NEXTDEF(RET,NAME,    PS,AS,IS,C,A,  R,COS_YES) \
COS_GEN_COMPMAK(RET,NAME,CLS,PS,AS,   C,A,O,R,COS_YES)

/*
 * Low-level implementation
 */

// type definition
#define COS_GEN_TYPEDEF(RET,NAME,PS,AS,C,A) \
typedef RET  (*COS_GEN_TYPE(NAME)) COS_PP_MAP(PS,COS_SIG_GEN); \
typedef RET COS_RET_TYPE(NAME); \
typedef COS_PP_IF(A)( \
  struct { COS_PP_SEPWITH(COS_PP_MAP(AS,COS_PRM_DECL),;); }, \
  void ) COS_ARG_TYPE(NAME);

// generic type check
#define COS_GEN_TYPECHK(RET,NAME,PS) \
extern COS_GEN_TYPE(NAME) \
  COS_PP_CAT(NAME,__invalid_makgeneric_vs_defgeneric); \
extern RET (* \
  COS_PP_CAT(NAME,__invalid_makgeneric_vs_defgeneric) ) \
                            COS_PP_MAP(PS,COS_SIG_GEN);

// generic class check
#define COS_GEN_GCLSCHK(NAME,CLS) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__generic_class_must_derive_from_Generic), \
  COS_CLS_MSPE(CLS) & 4);

// generic rank check
#define COS_GEN_RANKCHK(NAME,C) \
COS_STATIC_ASSERT( \
  COS_PP_CAT3(NAME,__generic_rank_greater_than_,COS_GEN_RNKMAX), \
  C <= COS_GEN_RNKMAX);

// generic name check
#define COS_GEN_NAMECHK(NAME) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__name_is_longer_than_64_chars), \
  sizeof(COS_PP_STR(NAME)) <= 64);

// generic arg size check
#define COS_GEN_SIZECHK(NAME,A,R) \
COS_PP_IF(A)(COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__generic_arguments_size_greater_than_64Kb), \
    sizeof(COS_ARG_TYPE(NAME)) < (1u << 16) );,) \
COS_PP_IF(R)(COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__generic_return_value_size_greater_than_64Kb), \
    sizeof(COS_RET_TYPE(NAME))+1 < (1u << 16) );,)

//  generic function declaration
#define COS_GEN_FUNCDCL(RET,NAME,VPS,PS,IS,C) \
extern RET              (NAME)  COS_PP_MAP2(VPS,IS,COS_SIG_GENF); \
extern void COS_NXT_NAME(NAME) (COS_PP_SEQ(COS_PP_MAP2(PS,IS,COS_SIG_NXTF)), \
                                SEL _sel, RET* _ret, COS_PP_CAT(IMP,C) _nxt);

// generic function definition
#define COS_GEN_FUNCDEF(RET,NAME,PS,AS,IS,C,A,R) \
static COS_ALWAYS_INLINE \
RET (NAME) COS_PP_MAP2(PS,IS,COS_SIG_GENF) \
{ \
  /* local result and arguments (if any) */ \
  COS_PP_IF(R)(RET _ret;,/* no ret */) \
  COS_PP_IF(A)(COS_ARG_TYPE(NAME) _arg;,/* no arg */) \
  /* arguments initialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEQ(COS_PP_MAP(AS,COS_ARG_INI));,/* no arg */) \
  /* method lookup */ \
  COS_PP_CAT3(cos_method_, \
    COS_PP_IF(COS_PP_GE(COS_FAST_MESSAGE,C))(fastLookup,lookup),C) \
  /* lookup selectors */ \
  (&COS_GEN_NAME(NAME),COS_PP_SEQ(COS_SEL_ID(C))) \
  /* method invocation */ \
  (&COS_GEN_NAME(NAME),COS_PP_SEQ(COS_SEL_NAME(C)), \
   COS_PP_IF(A)(&_arg,0),COS_PP_IF(R)(&_ret,0)); \
  /* arguments deinitialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEP(COS_PP_MAP(AS,COS_ARG_DEINI)),/* no arg */) \
  /* return result */ \
  COS_PP_IF(R)(return _ret;,/* no ret */) \
  /* for C89 mode */ \
  COS_UNUSED(NAME); \
}

// variadic generic function definition
#define COS_GEN_VFUNDEF(RET,NAME,PS,AS,IS,C,A,R) \
RET (NAME) COS_PP_MAP2(PS,IS,COS_SIG_GENF) \
{ \
  /* local result and arguments (if any) */ \
  COS_PP_IF(R)(RET _ret;,/* no ret */) \
  COS_ARG_TYPE(NAME) _arg; \
  /* arguments initialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEQ(COS_PP_MAP(COS_PP_RDROP(1,AS),COS_ARG_INI));,/* no arg */) \
  /* va_list initialization */ \
  va_start(_arg.va,COS_ARG_VINI(PS,IS)); \
  /* method lookup */ \
  COS_PP_CAT(cos_method_fastLookup,C) \
  /* lookup selectors */ \
  (&COS_GEN_NAME(NAME),COS_PP_SEQ(COS_SEL_ID(C))) \
  /* method invocation */ \
  (&COS_GEN_NAME(NAME),COS_PP_SEQ(COS_SEL_NAME(C)), \
   &_arg,COS_PP_IF(R)(&_ret,0)); \
  /* arguments deinitialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEP(COS_PP_MAP(COS_PP_RDROP(1,AS),COS_ARG_DEINI)),/* no arg */) \
  /* va_list deinitialization */ \
  va_end(_arg.va); \
  /* return result */ \
  COS_PP_IF(R)(return _ret;,/* no ret */) \
}

// generic next function definition
#define COS_GEN_NEXTDEF(RET,NAME,PS,AS,IS,C,A,R,V) \
COS_PP_IF(V)(,static COS_ALWAYS_INLINE) \
void COS_NXT_NAME(NAME) (COS_PP_SEQ(COS_PP_MAP2(PS,IS,COS_SIG_NXTF)), \
                         SEL _sel, RET* _ret, COS_PP_CAT(IMP,C) _nxt) \
{ \
  /* local arguments (if any) */ \
  COS_PP_IF(A)(COS_ARG_TYPE(NAME) _arg;,/* no arg */) \
  /* arguments initialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEQ(COS_PP_MAP(AS,COS_ARG_INI));,/* no arg */) \
  /* method invocation */ \
  _nxt(_sel,COS_PP_SEQ(COS_SEL_NAME(C)),COS_PP_IF(A)(&_arg,0),_ret); \
  /* arguments deinitialization (if any) */ \
  COS_PP_IF(A)(COS_PP_SEP(COS_PP_MAP(AS,COS_ARG_DEINI)),/* no arg */) \
  /* for C89 mode */ \
  COS_UNUSED(COS_NXT_NAME(NAME)); \
}

// component instantiation (see cos/cos/coscls.h)
#define COS_GEN_COMPMAK(RET,NAME,CLS,PS,AS,C,A,O,R,V) \
\
COS_PP_IF(A)( \
static struct cos_generic_rcvinfo COS_RCV_INFO(NAME)[] = { \
  COS_GEN_RCV(PS) \
};,/* no args */) \
\
COS_PP_IF(COS_PP_AND(A,COS_PP_NOT(O)))( \
static struct cos_generic_arginfo COS_ARG_INFO(NAME)[] = { \
  COS_GEN_ARG(AS,(COS_PP_DUPSEQ(COS_PP_LEN(AS),COS_ARG_TYPE(NAME)))) \
};,/* no args or all OBJ */) \
\
struct Generic COS_GEN_NAME(NAME) = { \
  /* encode rank into id (temporally) and tag into rc */ \
  {{ (U32)C << COS_ID_RNKSHT, cos_tag_generic }, \
  /* id must be zero (init) */ \
   0 }, \
  /* index for array of methods */ \
  0, \
  /* name (STR) */ \
  COS_PP_STR(NAME) "\0" \
  /* signature (STR) */ \
  COS_PP_SEPWITH(COS_PP_MAP(((RET),COS_PP_SEQ(PS)),COS_GEN_STR),"\0"), \
  /* link to generic class */ \
  (void*)&COS_CLS_NAME(CLS), \
  /* receivers info, 0 if no monomorphic arguments */ \
  COS_PP_IF(A)(COS_RCV_INFO(NAME),0), \
  /* arguments info, 0 if all objects, sizeof OBJ = 0 */ \
  COS_PP_IF(COS_PP_AND(A,COS_PP_NOT(O)))(COS_ARG_INFO(NAME),0), \
  /* size of monomorphic arguments struct */ \
  COS_PP_IF(A)(sizeof(COS_ARG_TYPE(NAME)),0), \
  /* size of returned value, sizeof OBJ = 0, void = -1 */ \
  COS_PP_IF(R)(COS_PP_IF(COS_TOK_ISOBJ(RET))(0,sizeof(COS_RET_TYPE(NAME))),-1), \
  /* cryptic information */ \
  COS_GEN_INFO(0,A*COS_PP_LEN(AS),O,COS_GEN_RET(RET),V) \
}

// argument initialization
#define COS_ARG_INI(a) \
  COS_PP_IF(COS_TOK_ISVALIST(COS_PRM_TYPE(a)))( \
  va_copy(_arg.COS_PRM_NAME(a), COS_PRM_NAME(a)), \
          _arg.COS_PRM_NAME(a)= COS_PRM_NAME(a))

// argument deinitialization
#define COS_ARG_DEINI(a) \
  COS_PP_IF(COS_TOK_ISVALIST(COS_PRM_TYPE(a)))( \
    va_end(_arg.COS_PRM_NAME(a));,/* not va_list */)

// va_list initialization
#define COS_ARG_VINI(PS,IS) \
  COS_ARG_VINI_0(COS_PP_LAST(COS_PP_RDROP(1,PS)), \
                 COS_PP_LAST(COS_PP_RDROP(1,IS)))
#define COS_ARG_VINI_0(a,n) \
  COS_PP_IF(COS_PP_ISTUPLE(a))(COS_PRM_NAME(a),COS_PP_CAT(_,n))

// signature encoding into a string
#define COS_GEN_STR(a) \
  COS_PP_IF(COS_PP_ISTUPLE(a))( \
    COS_PP_IF(COS_PP_OR(COS_TOK_ISVOID(COS_PRM_TYPE(a)), \
                        COS_TOK_ISOBJ (COS_PRM_TYPE(a)))) \
      ( ""/* void or OBJ */, COS_PP_STR(COS_PRM_TYPE(a)) ), "@"/* receiver */)

// receivers infos
#define COS_GEN_RCV(PS) \
  COS_PP_SEQ(COS_PP_MAP(COS_PP_FILTER( \
    COS_PP_MAP2(PS,(COS_PP_NUMSEQ_N()),COS_GEN_RCVI), COS_PP_ISNZERO), \
       COS_GEN_RCVI_))

#define COS_GEN_RCVI(p,i) \
  COS_PP_IF(COS_PP_ISTUPLE(p))(0,i)

#define COS_GEN_RCVI_(i) { i }

// arguments infos
#define COS_GEN_ARG(AS,TS) \
  COS_PP_SEQ(COS_PP_MAP2(AS,TS,COS_GEN_ARGI))

#define COS_GEN_ARGI(a,t) \
  { COS_PP_IF(COS_TOK_ISOBJ(COS_PRM_TYPE(a)))(0,sizeof(COS_PRM_TYPE(a))), \
    offsetof(t, COS_PRM_NAME(a)) }

#define COS_GEN_ISOBJ(gen)  ((gen)->retsize == (U16) 0)
#define COS_GEN_ISVOID(gen) ((gen)->retsize == (U16)-1)

// param-type is OBJ
#define COS_GEN_OBJ(a) \
  COS_PP_IF(COS_PP_ISTUPLE(a))(COS_TOK_ISOBJ(COS_PRM_TYPE(a)),COS_YES)

// return-type is void or OBJ
#define COS_GEN_RET(RET) \
  COS_PP_IF(COS_TOK_ISVOID(RET))(1, \
  COS_PP_IF(COS_TOK_ISOBJ (RET))(2,0))

/* generic id getters
 */
#define COS_GEN_RNK(gen) ((gen)->Behavior.id >> COS_ID_RNKSHT)
#define COS_GEN_TAG(gen) ((gen)->Behavior.id &  COS_ID_TAGMSK)

/* generic info encoding and decoding
 */
#define COS_GEN_INFO(nmth,narg,oarg,rett,varg) \
  ((((U32)(rett) & 3)   << 30) | \
   (((U32)(varg) & 1)   << 29) | \
   (((U32)(oarg) & 1)   << 28) | \
   (((U32)(narg) & 077) << 22) | \
    ((U32)(nmth) & COS_GEN_MTHMSK))

#define COS_GEN_ORET(gen)  ((gen)->info & ((U32)1 << 31)) // ret is OBJ   {0,>0}
#define COS_GEN_VRET(gen)  ((gen)->info & ((U32)1 << 30)) // ret is void  {0,>0}
#define COS_GEN_VARG(gen)  ((gen)->info & ((U32)1 << 29)) // is variadic  {0,>0}
#define COS_GEN_OARG(gen)  ((gen)->info & ((U32)1 << 28)) // args are OBJ {0,>0}
#define COS_GEN_NARG(gen) (((gen)->info >> 22) & 077    ) // num args    {0..63}
#define COS_GEN_NMTH(gen)  ((gen)->info & COS_GEN_MTHMSK) // num mths {0..4194303}

#define COS_GEN_MTHSHT  22
#define COS_GEN_MTHMSK (((U32)1<<22)-1)

#endif // COS_COS_GENERIC_H

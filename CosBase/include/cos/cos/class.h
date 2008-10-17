#ifndef COS_COS_CLASS_H
#define COS_COS_CLASS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS class (macros)
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
 | $Id: class.h,v 1.6 2008/10/17 18:12:19 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/class.h>"
#endif

/* NOTE-USER: class declaration, definition and instantiation

   class-reference:
     classref( class-name-list )

   class-declaration:
     useclass( class-decl-list );

   class-decl-list:
     class-decl
     class-decl-list , class-decl

   class-decl:
     class-name
     ( class-name ) local-name

   class-definition:
     defclass( class-specifier )
       struct-declaration-list                       // C99 6.7.2.1
     endclass

   class-instantiation:
     makclass( class-specifier );

   class-specifier:
     class-name , superclass-name
     class-name , _                                  // root class

   {class,superclass,local}-name:
     identifier                                      // C99 6.4.2.1

   examples:
     useclass(A,B,(C)Foo);               // declare classes A, B, and C as Foo

     defclass(A,Object) .. endclass      // class A derives from Object
     defclass(B,A)      .. endclass      // class B derives from class A
     defclass(R,_)      .. endclass      // class R is a root class (uncommon)

     makclass(B,A);                      // instantiate class B (in .c files)
*/

/* class keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_classref
#define COS_DISABLE_useclass
#define COS_DISABLE_defclass
#define COS_DISABLE_endclass
#define COS_DISABLE_makclass
#endif

#ifndef COS_DISABLE_classref
#define classref(...) COS_CLS_REF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_useclass
#define useclass(...) COS_CLS_USE(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_defclass
#define defclass(...) COS_CLS_DEF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_endclass
#define endclass COS_CLS_END
#endif

#ifndef COS_DISABLE_makclass
#define makclass(...) COS_CLS_MAK(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation
 */

/* class reference
 */
#define COS_CLS_REF(...) \
        COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),COS_CLS_REF_1))

#define COS_CLS_REF_1(NAME) \
        (&COS_CLS_NAME(NAME))

/* class declaration
 */
#define COS_CLS_USE(...) \
        COS_PP_SEPWITH(COS_PP_MAP((__VA_ARGS__),COS_CLS_USE_0),;)

#define COS_CLS_USE_0(NAME) \
        COS_CLS_USE_1(COS_DCL_GNAME(NAME),COS_DCL_LNAME(NAME))

#define COS_CLS_USE_1(GNAME,LNAME) \
        extern struct Class COS_CLS_NAME(GNAME); \
        static OBJ const LNAME = (void*)COS_CLS_REF_1(GNAME)

/* class definition
 */
#define COS_CLS_DEF(...) \
        COS_PP_CAT_NARG(COS_CLS_DEF_,__VA_ARGS__)(__VA_ARGS__)
        
#define COS_CLS_DEF_1(NAME) \
        COS_CLS_DEF_2(NAME,Object)

#define COS_CLS_DEF_2(NAME,SUPER) \
        COS_PP_IF(COS_CLS_ISROOT(SUPER)) \
          (COS_CLS_DEF_R(NAME),COS_CLS_DEF_N(NAME,SUPER))

#define COS_CLS_DEF_R(NAME) \
        COS_CLS_DEF_DCL(NAME); \
        enum { COS_CLS_RANK(NAME) = 0, \
               COS_MCL_RANK(NAME) = 4, /* 1+rankOf Class */ \
               COS_PCL_RANK(NAME) = 1+COS_MCL_RANK(NAME) }; \
        struct NAME {

#define COS_CLS_DEF_N(NAME,SUPER) \
        COS_CLS_DEF_DCL(NAME); \
        enum { COS_CLS_RANK(NAME) = 1+COS_CLS_RANK(SUPER), \
               COS_MCL_RANK(NAME) = 1+COS_MCL_RANK(SUPER), \
               COS_PCL_RANK(NAME) = 1+COS_MCL_RANK(NAME) }; \
        struct NAME { \
          struct SUPER SUPER;

#define COS_CLS_DEF_DCL(NAME) \
        extern struct Class COS_CLS_NAME(NAME); \
        extern struct Class COS_MCL_NAME(NAME); \
        extern struct Class COS_PCL_NAME(NAME); \
        struct COS_PP_CAT( m,NAME); /* ADT */ \
        struct COS_PP_CAT(pm,NAME)  /* ADT */

#define COS_CLS_END };

/* class instantiation
 */
#define COS_CLS_MAK(...) \
        COS_PP_CAT_NARG(COS_CLS_MAK_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CLS_MAK_1(NAME) \
        COS_CLS_MAK_2(NAME,Object)

#define COS_CLS_MAK_2(NAME,SUPER) \
        COS_PP_IF(COS_CLS_ISROOT(SUPER)) \
          (COS_CLS_MAK_R(NAME),COS_CLS_MAK_N(NAME,SUPER))

#define COS_CLS_MAK_R(NAME) \
COS_CLS_NAMECHK(NAME) \
COS_CLS_SIZECHK(NAME) \
COS_CLS_ROOTCHK(NAME) \
COS_CLS_COMPMAK(NAME,0,&COS_CLS_NAME(Class))

#define COS_CLS_MAK_N(NAME,SUPER) \
COS_CLS_NAMECHK(NAME) \
COS_CLS_SIZECHK(NAME) \
COS_CLS_RANKCHK(NAME) \
COS_CLS_SUPRCHK(NAME,SUPER) \
COS_CLS_SUPRLNK(NAME,SUPER) \
COS_CLS_COMPMAK(NAME,&COS_CLS_NAME(SUPER),&COS_MCL_NAME(SUPER))

/*
 * Low-level implementation
 */

// components instantiation (see cos/cos/coscls.h)
#define COS_CLS_COMPMAK(NAME,SUPER_REF,META_SUPER_REF) \
struct Class COS_MCL_NAME(NAME) = { /* metaclass */ \
  /* Any.id must be zero (init), encode tag into Any.rc */ \
  {{{ 0, cos_tag_mclass }}, \
  /* encode rank into id */ \
   (U32)COS_MCL_RANK(NAME) << COS_ID_RNKSHT }, \
  sizeof(struct Class), \
  /* classes' names share the same string (STR) */ \
  0, \
  /* metaclass derives from super metaclass */ \
  META_SUPER_REF \
}; \
struct Class COS_PCL_NAME(NAME) = { /* property metaclass */ \
  /* Any.id must be zero (init), encode tag into Any.rc */ \
  {{{ 0, cos_tag_pclass }}, \
  /* encode rank into id */ \
   (U32)COS_PCL_RANK(NAME) << COS_ID_RNKSHT }, \
  sizeof(struct Class), \
  /* classes' names share the same string (STR) */ \
  "pm" COS_PP_STR(NAME), \
  /* property metaclass derives from metaclass */ \
  &COS_MCL_NAME(NAME) \
}; \
struct Class COS_CLS_NAME(NAME) = { /* class */ \
  /* Any.id must be zero (init), encode tag into Any.rc */ \
  {{{ 0, cos_tag_class }}, \
  /* encode rank into id */ \
   (U32)COS_CLS_RANK(NAME) << COS_ID_RNKSHT }, \
  /* instances size */ \
  sizeof(struct NAME), \
  /* hack: pre-init link to property metaclasses */ \
  COS_STATIC_CAST(STR, (void*)&COS_PCL_NAME(NAME)), \
  /* class derives from super class */ \
  SUPER_REF \
}

// class super-class link
#define COS_CLS_SUPRLNK(NAME,SUPER) \
char COS_LNK_NAME(NAME,SUPER);

// class name check
#define COS_CLS_NAMECHK(NAME) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__name_is_longer_than_64_chars), \
  sizeof(COS_PP_STR(NAME)) <= 64);

// class size check
#define COS_CLS_SIZECHK(NAME) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__size_is_greater_than_4294967295_chars), \
  sizeof(struct NAME) <= 4294967295);

// class rank check
#define COS_CLS_RANKCHK(NAME) \
COS_STATIC_ASSERT( \
  COS_PP_CAT3(NAME,__class_rank_greater_than_,COS_CLS_RNKMAX), \
  COS_PCL_RANK(NAME) <= COS_CLS_RNKMAX);

// root class check
#define COS_CLS_ROOTCHK(NAME) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__invalid_makclass_vs_defclass), \
  COS_CLS_RANK(NAME) == 0);

// super class check
#define COS_CLS_SUPRCHK(NAME,SUPER) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(NAME,__invalid_makclass_vs_defclass), \
  offsetof(struct NAME,SUPER) == 0);

/* root class identification
 */
#define COS_CLS_ISROOT(NAME) \
  COS_PP_ISTUPLE(COS_PP_CAT_(COS_CLS_TOKEN_,NAME))
#define COS_CLS_TOKEN__ ()

/* class id getters
 */
#define COS_CLS_RNK(cls) ((cls)->Behavior.id >> COS_ID_RNKSHT)
#define COS_CLS_TAG(cls) ((cls)->Behavior.id &  COS_ID_TAGMSK)

#endif // COS_COS_CLASS_H

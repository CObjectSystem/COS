#ifndef COS_COS_ALIAS_H
#define COS_COS_ALIAS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS alias (macros)
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
 | $Id: alias.h,v 1.6 2010/01/31 12:03:53 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/alias.h>"
#endif

/* NOTE-USER: alias definition

   alias-definition:
     defalias( alias-specifier );

   alias-specifier:
     return-type , ( generic-name ) alias-generic-name , param-list

   alias-generic-name:
     identifier                                     // C99 6.4.2.1

   where in the context of alias the same rules applied as for methods,
   except that class definition visibility is not required.

   examples:
     defgeneric(OBJ, gput , _1, _2);
     defgeneric(OBJ, gget , _1);
     defgeneric(OBJ, gdrop, _1);

     defgeneric(OBJ, gpush, _1, _2);
     defgeneric(OBJ, gtop , _1);
     defgeneric(OBJ, gpop , _1);

     defmethod(OBJ, gput , Stack, Object) .. endmethod
     defmethod(OBJ, gtop , Stack)         .. endmethod
     defmethod(OBJ, gdrop, Stack)         .. endmethod

     defalias(OBJ, (gput )gpush, Stack, Object);
     defalias(OBJ, (gget )gtop , Stack);
     defalias(OBJ, (gdrop)gpop , Stack);
*/

/* alias keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_defalias
#endif

#ifndef COS_DISABLE_defalias
#define defalias(...) COS_ALS_DEF(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation
 */

/* alias definition and instantiation
 */
#define COS_ALS_DEF(  RET,NAME,...) \
        COS_ALS_DEF_0(RET,NAME,(__VA_ARGS__), \
          COS_PP_FILTER((__VA_ARGS__),COS_PP_ISNTUPLE) )

#define COS_ALS_DEF_0(RET,NAME,PS,CS) \
        COS_ALS_DEF_1(RET,COS_DCL_GNAME(NAME),COS_DCL_LNAME(NAME), \
                      PS,CS,COS_PP_LEN(CS))

#define COS_ALS_DEF_1(RET,NAME,ALIAS,PS,CS,C) \
COS_ALS_TYPECHK(RET,NAME,ALIAS,PS,CS  ) \
COS_ALS_NAMECHK(         ALIAS,   CS  ) \
COS_ALS_COMPMAK(    NAME,ALIAS,   CS,C)

/*
 * Low-level implementation
 */

// alias type comparison
#define COS_ALS_TYPECHK(RET,NAME,ALIAS,PS,CS) \
extern COS_GEN_TYPE(ALIAS) \
  COS_PP_CAT(COS_SYM_NAME(NAME,CS),__invalid_defalias_vs_defgeneric); \
extern COS_GEN_TYPE(NAME) \
  COS_PP_CAT(COS_SYM_NAME(NAME,CS),__invalid_defalias_vs_defgeneric); \
extern RET (* \
  COS_PP_CAT(COS_SYM_NAME(NAME,CS),__invalid_defalias_vs_defgeneric)) \
                                          COS_PP_MAP(PS,COS_SIG_GEN);

// alias name check
#define COS_ALS_NAMECHK(NAME,CS) \
COS_STATIC_ASSERT( \
  COS_PP_CAT(COS_SYM_NAME(NAME,CS),__name_is_longer_than_256_chars), \
  sizeof(COS_PP_STR(COS_SYM_NAME(NAME,CS))) <= 256);

// alias intantiation (see cos/cos/coscls.h)
#define COS_ALS_COMPMAK(NAME,ALIAS,CS,C) \
COS_PP_SEP(COS_PP_MAP(CS,COS_ALS_CLS)) \
extern struct COS_PP_CAT(Method,C) COS_MTH_NAME(NAME,CS); \
struct COS_PP_CAT(Method,C) COS_MTH_NAME(ALIAS,CS) = { \
   /* encode tag into rc */ \
  {{ 0, cos_tag_alias }, \
   /* location */ \
   __FILE__, __LINE__, \
   /* reference to generic */ \
   &COS_GEN_NAME(ALIAS), \
   /* method rank */ \
   0, \
   /* around method rank */ \
   0 }, \
   /* reference to function */ \
   0, \
   /* hack: reference to method aliased */ \
   { COS_STATIC_CAST(struct Class*, (void*)&COS_MTH_NAME(NAME,CS)) \
     COS_PP_IF(COS_PP_LT(C,2))(, \
       ,COS_PP_SEQ(COS_PP_MAP(COS_PP_DROP(1,CS),COS_CLS_REF_1))) } \
}

#define COS_ALS_CLS(NAME) \
  extern struct Class COS_CLS_NAME(NAME);

#endif // COS_COS_ALIAS_H

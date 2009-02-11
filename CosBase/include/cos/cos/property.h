#ifndef COS_COS_PROPERTY_H
#define COS_COS_PROPERTY_H

/*
 o---------------------------------------------------------------------o
 |
 | COS property (macros)
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
 | $Id: property.h,v 1.6 2009/02/11 11:48:33 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/property.h>"
#endif

/* NOTE-USER: property declaration, definition and instantiation

   property-reference:
     propertyref( property-name-list )

   property-declaration:
     useproperty( property-decl-list );

   property-decl-list:
     property-decl
     property-decl-list , property-decl

   property-decl:
     property-name
     ( property-name ) local-name

   property-definition:
     defproperty( property-name );

   property-instantiation:
     makproperty( property-name );

   {property,local}-name:
     identifier                                      // C99 6.4.2.1

   - properties are predicate classes deriving from the class Property
     the name of the property class is built from the name of the property
     prefixed by 'P_'.

   - makproperty are optional if you use the makefiles provided by COS
     (as for makgeneric)

   examples:
     useproperty(firstname, (fullname)name); // declare properties (classes)

     defproperty(firstname);   // define      property firstname (class P_firstname)
     makproperty(firstname);   // instantiate property firstname (in .c files)
*/

/* NOTE-USER: class-property definition

   class-property-definition:
     defproperty( class-name, property-specifier );
     defproperty( class-name, property-specifier, read-action );
     defproperty( class-name, property-specifier, read-action, write-action );
     
   property-specifier:
     property-name
     ( attribute-name ) property-name

   {read,write}-action:
     function-name
     empty-action
     
   empty-action:
                                                     // nothing
                                                     
   {action,attribute,function}-name:
     identifier                                      // C99 6.4.2.1

   examples:
     defproperty(Person, name);             // read-write property-attribute name
     defproperty(Person, name, );           // read-only  property-attribute name
     defproperty(Person, (name)fullname);   // property fullname   for attribute name
     defproperty(Person, (name)familyname); // property familyname for attribute name

     // read-only property-attribute size using I32toOBJ for boxing
     defproperty(Array, size, I32toOBJ);           

     // read-write property-attribute age using message gint for unboxing
     defproperty(Person, age, I32toOBJ, gint);

     // hand-written read-write property size
     defmethod(OBJ, ggetAt, Array, pmP_size)
       retmethod( gautoRelease(aInt(self->size)) );
     endmethod

     defmethod(void, gputAt, Array, Any, pmP_size)
       self->size = gint(_2);
     endmethod

     defmethod(void, gputAt, Array, Int, pmP_size) // faster specialization
       self->size = self2->value;
     endmethod

     // hand-written read-only property fullname with dynamically built attribute
     defmethod(OBJ, ggetAt, Person, pmP_fullname)
       retmethod( gautoRelease(gcat(self->firstname, self->lastname)) );
     endmethod
*/

/* property keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_propertyref
#define COS_DISABLE_useproperty
#define COS_DISABLE_defproperty
#define COS_DISABLE_makproperty
#endif

#ifndef COS_DISABLE_propertyref
#define propertyref(...) COS_PRP_REF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_useproperty
#define useproperty(...) COS_PRP_USE(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_defproperty
#define defproperty(...) COS_PRP_DEF(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_makproperty
#define makproperty(P) COS_PRP_MAK(P)
#endif

/***********************************************************
 * Implementation
 */

/* property reference
 */
#define COS_PRP_REF(...) \
        COS_CLS_REF(COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),COS_PRP_NAME)))

/* property declaration
 */
#define COS_PRP_USE(...) \
        COS_CLS_USE(COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),COS_DCL_PNAME)))

/* property definition
 */
#define COS_PRP_DEF(...) \
        COS_PP_CAT_NARG(COS_PRP_DEF_,__VA_ARGS__)(__VA_ARGS__) \
        COS_SCP_END
        
#define COS_PRP_DEF_1(NAME) \
        COS_CLS_DEF_2(COS_PRP_NAME(NAME),Property) \
        COS_CLS_END

#define COS_PRP_DEF_2(NAME,PROP) \
        COS_PRP_DEF_GET(NAME,COS_DCL_LNAME(PROP),COS_DCL_GNAME(PROP),) \
        COS_PRP_DEF_PUT(NAME,COS_DCL_LNAME(PROP),COS_DCL_GNAME(PROP))

#define COS_PRP_DEF_3(NAME,PROP,BOX) \
        COS_PRP_DEF_GET(NAME,COS_DCL_LNAME(PROP),COS_DCL_GNAME(PROP),BOX)

#define COS_PRP_DEF_4(NAME,PROP,BOX,UNBOX) \
        COS_PRP_DEF_GET(NAME,COS_DCL_LNAME(PROP),COS_DCL_GNAME(PROP),BOX  ) \
        COS_PRP_DEF_SET(NAME,COS_DCL_LNAME(PROP),COS_DCL_GNAME(PROP),UNBOX)

#define COS_PRP_DEF_GET(NAME,PROP,ATTR,BOX) \
   COS_MTH_DEF(OBJ, ggetAt, NAME, COS_PPR_NAME(PROP)) \
     COS_MTH_RET(BOX(self->ATTR)); \
   COS_MTH_END

#define COS_PRP_DEF_SET(NAME,PROP,ATTR,UNBOX) \
   COS_MTH_DEF(void, gputAt, NAME, Any, COS_PPR_NAME(PROP)) \
     UNBOX(&self->ATTR, _2); \
   COS_MTH_END

#define COS_PRP_DEF_PUT(NAME,PROP,ATTR) \
   COS_MTH_DEF(void, gputAt, NAME, Any, COS_PPR_NAME(PROP)) \
     OBJ old = self->ATTR; \
     self->ATTR = gretain(_2); \
     grelease(old); \
   COS_MTH_END

/* property instantiation
 */
#define COS_PRP_MAK(NAME) \
        COS_CLS_MAK_2(COS_PRP_NAME(NAME),Property)

#endif // COS_COS_PROPERTY_H

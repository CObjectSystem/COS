#ifndef COS_PROPERTY_H
#define COS_PROPERTY_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Property
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
 | $Id: Property.h,v 1.1 2009/01/23 15:12:28 ldeniau Exp $
 |
*/

#include <cos/Nil.h>

/* NOTE-USER: Property

   Property is the root class of all properties. Properties are classes
   deriving from the class Property with name prefixed by P_. Using the
   property 'name' is equivalent to use the class 'P_name'.
   
   Properties are useful for KVC (Key-Value Coding) which allow to use
   any object as an associative collection, as well as for serialization,
   attribute introspection and scripting.
*/

defclass(Property,Nil)
endclass

// class-property define getters/setters

#ifndef COS_GEN_OBJECT_H
#include <cos/gen/object.h>
#endif

#ifndef COS_GEN_ACCESSOR_H
#include <cos/gen/accessor.h>
#endif

#endif // COS_PROPERTY_H

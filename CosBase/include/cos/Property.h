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
 | $Id: Property.h,v 1.5 2010/05/20 15:48:13 ldeniau Exp $
 |
*/

#include <cos/Nil.h>

#ifndef COS_GEN_ACCESSOR_H
#include <cos/gen/accessor.h>
#endif

/* NOTE-USER: Property

   Property is the "root" class of all properties. Properties are classes
   deriving from the class Property usually with name prefixed by P_.
   Using the property 'name' is equivalent to use the class 'P_name'.
   
   Properties are useful for KVC (Key-Value Coding) which allows to use
   any object as an associative collection, as well as for serialization,
   attributes introspection and scripting.
*/

defclass(Property, Nil)
endclass

#endif // COS_PROPERTY_H

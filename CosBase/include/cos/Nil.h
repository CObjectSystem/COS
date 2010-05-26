#ifndef COS_NIL_H
#define COS_NIL_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Nil (root class)
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
 | $Id: Nil.h,v 1.8 2010/05/26 22:46:29 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: Nil behavior

   Nil and classes deriving from Nil cannot have instance, also called
   class-objects from which properties and predicates derive.
   
   Use Nil (instead of 0) if you mean "no-object".
   Remember, message cannot be sent to (OBJ)0, but it can to Nil.
   
   Use Null (instead of Nil or 0) if you mean "no-data" object.
*/

defclass(Nil, _)
endclass

#endif // COS_NIL_H

#ifndef COS_VALUE_H
#define COS_VALUE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Value
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
 | $Id: Value.h,v 1.3 2008/10/21 15:43:42 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

/* Values subclasses:

<- Value
   <- Size        (1-5 dim)

   <- Index       (1-5 dim)
   <- Point       (1-5 dim)

   <- Range       (1-5 dim)
   <- Slice       (1-5 dim)
   <- Sequence    (1-5 dim)

   <- Pointer     (void*)
      <- AutoPointer

   <- Number
      <- Integral
         <- Int
            <- Char
            <- Short
         <- Long
      <- Floating
         <- Float
         <- Complex
*/

defclass(Value)
endclass

#endif // COS_VALUE_H

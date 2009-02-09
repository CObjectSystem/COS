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
 | $Id: Value.h,v 1.6 2009/02/09 13:20:44 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

/* Values subclasses:

<- Value
   <- Number
      <- Integral
         <- Int
            <- Char
            <- Short
         <- Long
      <- Floating
         <- Float
         <- Complex

   <- Range  (1-5 dim)
   <- Slice  (1-5 dim)
*/

defclass(Value)
endclass

/* NOTE-USER: indexing policy
   - starts at zero
     (index 0 is the first element)
   - negative indexe starts from the end
     (index -1 is the last element)
*/
static inline U32
index_abs(I32 index, U32 size) {
  return index + (index < 0) * size;
}

#endif // COS_VALUE_H


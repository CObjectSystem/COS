#ifndef COS_GEN_SEQUENCE_H
#define COS_GEN_SEQUENCE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for sequences
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau*cern.ch
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
 | $Id: sequence.h,v 1.1 2009/07/02 13:20:27 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// constructors
defgeneric(OBJ, ginitWithRng1, _1, (I32)end);
defgeneric(OBJ, ginitWithRng2, _1, (I32)start, (I32)end);
defgeneric(OBJ, ginitWithRng3, _1, (I32)start, (I32)end, (I32)stride);

defgeneric(OBJ, ginitWithSlc1, _1, (U32)size);
defgeneric(OBJ, ginitWithSlc2, _1, (I32)start, (U32)size);
defgeneric(OBJ, ginitWithSlc3, _1, (I32)start, (U32)size, (I32)stride);

// ----- inliners -----

static always_inline OBJ
gnewWithRng1(OBJ _1, I32 end) {
  return ginitWithRng1(galloc(_1), end);
}

static always_inline OBJ
gnewWithRng2(OBJ _1, I32 start, I32 end) {
  return ginitWithRng2(galloc(_1), start, end);
}

static always_inline OBJ
gnewWithRng3(OBJ _1, I32 start, I32 end, I32 stride) {
  return ginitWithRng3(galloc(_1), start, end, stride);
}

static always_inline OBJ
gnewWithSlc1(OBJ _1, U32 size) {
  return ginitWithSlc1(galloc(_1), size);
}

static always_inline OBJ
gnewWithSlc2(OBJ _1, I32 start, U32 size) {
  return ginitWithSlc2(galloc(_1), start, size);
}

static always_inline OBJ
gnewWithSlc3(OBJ _1, I32 start, U32 size, I32 stride) {
  return ginitWithSlc3(galloc(_1), start, size, stride);
}

#endif // COS_GEN_CONTAINER_H

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
 | $Id: sequence.h,v 1.6 2009/09/03 23:21:42 ldeniau Exp $
 |
*/

#include <cos/Slice.h>

// slice
defgeneric(struct Slice, gslice, _1);

// new
defgeneric(OBJ, gnewSlc1, _1, (U32)size);
defgeneric(OBJ, gnewSlc2, _1, (I32)start, (U32)size);
defgeneric(OBJ, gnewSlc3, _1, (I32)start, (U32)size, (I32)stride);

defgeneric(OBJ, gnewRng1, _1, (I32)end);
defgeneric(OBJ, gnewRng2, _1, (I32)start, (I32)end);
defgeneric(OBJ, gnewRng3, _1, (I32)start, (I32)end, (I32)stride);

defgeneric(OBJ, gnewXRng1, _1, (F64)end);
defgeneric(OBJ, gnewXRng2, _1, (F64)start, (F64)end);
defgeneric(OBJ, gnewXRng3, _1, (F64)start, (F64)end, (F64)stride);

#endif // COS_GEN_CONTAINER_H

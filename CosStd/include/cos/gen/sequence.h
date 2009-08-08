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
 | $Id: sequence.h,v 1.4 2009/08/08 16:36:09 ldeniau Exp $
 |
*/

#include <cos/Slice.h>

/* NOTE-USER: includes of generics
   One can find hereafter a trick to avoid multiple definition of generics when
   the instance generation is left to the COS makefiles (e.g automatic makgeneric).
*/

#ifndef COS_NOCOS
#include <cos/gen/object.h>
#endif

// sequence
defgeneric(struct Range, grange, _1);
defgeneric(struct Slice, gslice, _1);

// new
defgeneric(OBJ, gnewWithRng1, _1, (I32)end);
defgeneric(OBJ, gnewWithRng2, _1, (I32)start, (I32)end);
defgeneric(OBJ, gnewWithRng3, _1, (I32)start, (I32)end, (I32)stride);

defgeneric(OBJ, gnewWithSlc1, _1, (U32)size);
defgeneric(OBJ, gnewWithSlc2, _1, (I32)start, (U32)size);
defgeneric(OBJ, gnewWithSlc3, _1, (I32)start, (U32)size, (I32)stride);

// constructors
defgeneric(OBJ, ginitWithRng1, _1, (I32)end);
defgeneric(OBJ, ginitWithRng2, _1, (I32)start, (I32)end);
defgeneric(OBJ, ginitWithRng3, _1, (I32)start, (I32)end, (I32)stride);

defgeneric(OBJ, ginitWithSlc1, _1, (U32)size);
defgeneric(OBJ, ginitWithSlc2, _1, (I32)start, (U32)size);
defgeneric(OBJ, ginitWithSlc3, _1, (I32)start, (U32)size, (I32)stride);

#endif // COS_GEN_CONTAINER_H

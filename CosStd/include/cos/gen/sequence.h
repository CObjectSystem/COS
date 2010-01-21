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
 | $Id: sequence.h,v 1.7 2010/01/21 14:12:36 ldeniau Exp $
 |
*/

#include <cos/XRange.h>

// value getters
defgeneric(struct Slice , gslice , _1);
defgeneric(struct Range , grange , _1);
defgeneric(struct XRange, gxrange, _1);

// new (no 'init' for final classes)
defgeneric(OBJ, gnewSlc , _1, (I32)start, (U32)size, (I32)stride);
defgeneric(OBJ, gnewRng , _1, (I32)start, (I32)end , (I32)stride);
defgeneric(OBJ, gnewXRng, _1, (F64)start, (F64)end , (F64)stride);

#endif // COS_GEN_SEQUENCE_H

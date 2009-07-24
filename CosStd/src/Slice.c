/*
 o---------------------------------------------------------------------o
 |
 | COS Slice
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
 | $Id: Slice.c,v 1.5 2009/07/24 12:36:27 ldeniau Exp $
 |
*/

#include <cos/Slice.h>

#include <cos/gen/object.h>
#include <cos/gen/sequence.h>

makclass(Slice, Value);

// ----- constructors

defmethod(OBJ, ginitWithSlc1, Slice, (U32)size)
  retmethod( (OBJ)Slice_init(self, 0, size, 1) );
endmethod

defmethod(OBJ, ginitWithSlc2, Slice, (I32)start, (U32)size)
  retmethod( (OBJ)Slice_init(self, start, size, 1));
endmethod

defmethod(OBJ, ginitWithSlc3, Slice, (I32)start, (U32)size, (I32)stride)
  retmethod( (OBJ)Slice_init(self,start, size, stride) );
endmethod

// ----- copy

defmethod(OBJ, ginitWith, Slice, Slice)
  retmethod( (OBJ)Slice_copy(self1, self2) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Slice, Slice)
  retmethod( Slice_isEqual(self1, self2) ? True : False );
endmethod


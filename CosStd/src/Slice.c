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
 | $Id: Slice.c,v 1.4 2009/06/30 07:59:35 ldeniau Exp $
 |
*/

#include <cos/Slice.h>

#include <cos/gen/object.h>
#include <cos/gen/sequence.h>

makclass(Slice, Value);

// ----- constructors

defmethod(OBJ, ginitWithSlc1, Object, (U32)size)
  retmethod( ginitWithSlc3(_1, 0, size, 1) );
endmethod

defmethod(OBJ, ginitWithSlc2, Object, (I32)start, (U32)size)
  retmethod( ginitWithSlc3(_1, start, size, 1) );
endmethod

defmethod(OBJ, ginitWithSlc3, Slice, (I32)start, (U32)size, (I32)stride)
  self->start  = start;
  self->size   = size;
  self->stride = stride;

  retmethod(_1);
endmethod

// ----- copy

defmethod(OBJ, ginitWith, Slice, Slice)
  self1->start  = self2->start;
  self1->size   = self2->size;
  self1->stride = self2->stride;

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Slice, Slice)
  retmethod( Slice_isEqual(self1, self2) ? True : False );
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS Range
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
 | $Id: Range.c,v 1.5 2009/07/02 13:20:27 ldeniau Exp $
 |
*/

#include <cos/Range.h>

#include <cos/gen/object.h>
#include <cos/gen/sequence.h>

makclass(Range, Value);

// ----- constructors

defmethod(OBJ, ginitWithRng1, Object, (I32)end)
  retmethod( ginitWithRng3(_1, 0, end, 1) );
endmethod

defmethod(OBJ, ginitWithRng2, Object, (I32)start, (I32)end)
  retmethod( ginitWithRng3(_1, start, end, 1) );
endmethod

defmethod(OBJ, ginitWithRng3, Range, (I32)start, (I32)end, (I32)stride)
  self->start  = start;
  self->end    = end;
  self->stride = stride;

  retmethod(_1);
endmethod

// ----- copy

defmethod(OBJ, ginitWith, Range, Range)
  self1->start  = self2->start;
  self1->end    = self2->end;
  self1->stride = self2->stride;

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Range, Range)
  retmethod( Range_isEqual(self1, self2) ? True : False );
endmethod


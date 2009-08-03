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
 | $Id: Range.c,v 1.7 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Range.h>

#include <cos/gen/compare.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>

makclass(Range, Value);

// ----- constructors

defmethod(OBJ, ginitWithRng1, Range, (I32)end)
  retmethod( (OBJ)Range_init(self, 0, end, 1) );
endmethod

defmethod(OBJ, ginitWithRng2, Range, (I32)start, (I32)end)
  retmethod( (OBJ)Range_init(self, start, end, 1) );
endmethod

defmethod(OBJ, ginitWithRng3, Range, (I32)start, (I32)end, (I32)stride)
  retmethod( (OBJ)Range_init(self, start, end, stride) );
endmethod

// ----- copy

defmethod(OBJ, ginitWith, Range, Range)
  retmethod( (OBJ)Range_copy(self1, self2) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Range, Range)
  retmethod( Range_isEqual(self1, self2) ? True : False );
endmethod


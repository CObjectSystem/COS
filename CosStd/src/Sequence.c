/*
 o---------------------------------------------------------------------o
 |
 | COS Sequence
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
 | $Id: Sequence.c,v 1.11 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

makclass(Sequence     , Container);
makclass(ValueSequence, Sequence );

// -----

defmethod(OBJ, ginitWith2, mSequence, Sequence, Range)
  struct Range range = Range_normalize(self3,gsize(_2));
  struct Slice slice = Slice_fromRange(&range);
  retmethod( ginitWith2(_1,_2,(OBJ)&slice) );  
endmethod

defmethod(OBJ, ginitWith2, mView, Sequence, Range)
  struct Range range = Range_normalize(self3,gsize(_2));
  struct Slice slice = Slice_fromRange(&range);
  retmethod( ginitWith2(_1,_2,(OBJ)&slice) );
endmethod

defmethod(OBJ, ggetAt, Sequence, Range)
  struct Range range = Range_normalize(self2,gsize(_1));
  struct Slice slice = Slice_fromRange(&range);
  retmethod( ggetAt(_1,(OBJ)&slice) );
endmethod

defmethod(void, gputAt, Sequence, Range, Sequence)
  struct Range range = Range_normalize(self2,gsize(_1));
  struct Slice slice = Slice_fromRange(&range);
  gputAt(_1,(OBJ)&slice,_3);
endmethod


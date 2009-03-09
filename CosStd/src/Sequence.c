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
 | $Id: Sequence.c,v 1.8 2009/03/09 16:54:01 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

makclass(Sequence     , Container);
makclass(ValueSequence, Sequence );

// -----

defmethod(OBJ, ginitWith2, mSequence, Sequence, Range)
  OBJ slice = (OBJ)Slice_fromRange(atSlice(0,0), self3, gsize(_2));
  retmethod( ginitWith2(_1,_2,slice) );  
endmethod

defmethod(OBJ, ginitWith2, pmView, Sequence, Range)
  OBJ slice = (OBJ)Slice_fromRange(atSlice(0,0), self3, gsize(_2));
  retmethod( ginitWith2(_1,_2,slice) );
endmethod

defmethod(OBJ, ggetAt, Sequence, Range)
  OBJ slice = (OBJ)Slice_fromRange(atSlice(0,0), self2, gsize(_1));
  retmethod( ggetAt(_1,slice) );
endmethod

defmethod(void, gputAt, Sequence, Range, Sequence)
  OBJ slice = (OBJ)Slice_fromRange(atSlice(0,0), self2, gsize(_1));
  gputAt(_1,slice,_3);
endmethod


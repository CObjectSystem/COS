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
 | $Id: Slice.c,v 1.9 2009/09/02 19:34:57 ldeniau Exp $
 |
*/

#include <cos/Slice.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/IntVector.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

makclass(Slice, ValueSequence);

// ----- new

defmethod(OBJ, gnewWithSlc1, pmSlice, (U32)size)
  retmethod( ginitWithSlc1(galloc(_1), size) );
endmethod

defmethod(OBJ, gnewWithSlc2, pmSlice, (I32)start, (U32)size)
  retmethod( ginitWithSlc2(galloc(_1), start, size) );
endmethod

defmethod(OBJ, gnewWithSlc3, pmSlice, (I32)start, (U32)size, (I32)stride)
  retmethod( ginitWithSlc3(galloc(_1), start, size, stride) );
endmethod

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
  retmethod( (OBJ)Slice_copy(self, self2) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Slice, Slice)
  retmethod( Slice_isEqual(self, self2) ? True : False );
endmethod

// ----- sequence

defmethod(OBJ, gmap, Functor, Slice)
  struct IntVector* vec = IntVector_alloc(Slice_size(self2));
  OBJ _vec = (OBJ)vec; PRT(_vec);

  I32 *dst   = vec->value;
  U32  dst_n = vec->size;
  U32  i;

  for (i = 0; i < dst_n; i++)
    dst[i] = gint( geval1(_1, aInt(Slice_eval(self2,i))) );

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap, IntFunction1, Slice)
  struct IntVector* vec = IntVector_alloc(Slice_size(self2));
  OBJ _vec = (OBJ)vec; PRT(_vec);

  I32    *dst   = vec->value;
  U32     dst_n = vec->size;
  I32FCT1 fct   = self1->fct;
  U32     i;

  for (i = 0; i < dst_n; i++)
    dst[i] = fct(Slice_eval(self2,i));

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod


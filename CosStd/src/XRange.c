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
 | $Id: XRange.c,v 1.2 2009/09/02 19:34:57 ldeniau Exp $
 |
*/

#include <cos/XRange.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/FltVector.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

makclass(XRange, ValueSequence);

// ----- new

defmethod(OBJ, gnewWithXRng1, pmXRange, (F64)end)
  retmethod( ginitWithXRng1(galloc(_1), end) );
endmethod

defmethod(OBJ, gnewWithXRng2, pmXRange, (F64)start, (F64)end)
  retmethod( ginitWithXRng2(galloc(_1), start, end) );
endmethod

defmethod(OBJ, gnewWithXRng3, pmXRange, (F64)start, (F64)end, (F64)stride)
  retmethod( ginitWithXRng3(galloc(_1), start, end, stride) );
endmethod

// ----- constructors

defmethod(OBJ, ginitWithXRng1, XRange, (F64)end)
  retmethod( (OBJ)XRange_init(self, 0, end, 1) );
endmethod

defmethod(OBJ, ginitWithXRng2, XRange, (F64)start, (F64)end)
  retmethod( (OBJ)XRange_init(self, start, end, 1) );
endmethod

defmethod(OBJ, ginitWithXRng3, XRange, (F64)start, (F64)end, (F64)stride)
  retmethod( (OBJ)XRange_init(self, start, end, stride) );
endmethod

// ----- copy

defmethod(OBJ, ginitWith, XRange, XRange)
  retmethod( (OBJ)XRange_copy(self, self2) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, XRange, XRange)
  retmethod( XRange_isEqual(self, self2) ? True : False );
endmethod

// ----- sequence

defmethod(OBJ, gmap, Functor, XRange)
  struct FltVector* vec = FltVector_alloc(XRange_size(self2));
  OBJ _vec = (OBJ)vec; PRT(_vec);

  F64 *dst   = vec->value;
  U32  dst_n = vec->size;
  U32  i;

  for (i = 0; i < dst_n; i++)
    dst[i] = gflt( geval1(_1, aFloat(XRange_eval(self2,i))) );

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap, FltFunction1, XRange)
  struct FltVector* vec = FltVector_alloc(XRange_size(self2));
  OBJ _vec = (OBJ)vec; PRT(_vec);

  F64    *dst   = vec->value;
  U32     dst_n = vec->size;
  F64FCT1 fct   = self1->fct;
  U32     i;

  for (i = 0; i < dst_n; i++)
    dst[i] = fct(XRange_eval(self2,i));

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod


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
 | $Id: XRange.c,v 1.10 2010/01/03 12:28:56 ldeniau Exp $
 |
*/

#include <cos/XRange.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/FltVector.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// -----

makclass(XRange, ValueSequence);

// -----

useclass(XRange);

// ----- low-level functions

BOOL
XRange_isEqual(const struct XRange *r1, const struct XRange *r2)
{
  return float_equal(r1->start , r2->start)
      && float_equal(r1->end   , r2->end)
      && float_equal(r1->stride, r2->stride);
}

// ----- new

defmethod(OBJ, gnewXRng1, pmXRange, (F64)end)
  retmethod( (OBJ)XRange_init((void*)galloc(_1), 0, end, 1) );
endmethod

defmethod(OBJ, gnewXRng2, pmXRange, (F64)start, (F64)end)
  retmethod( (OBJ)XRange_init((void*)galloc(_1), start, end, 1) );
endmethod

defmethod(OBJ, gnewXRng3, pmXRange, (F64)start, (F64)end, (F64)stride)
  retmethod( (OBJ)XRange_init((void*)galloc(_1), start, end, stride) );
endmethod

// ----- clone

defmethod(OBJ, gclone, XRange)
  retmethod( (OBJ)XRange_copy((void*)galloc(XRange), self) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, XRange, XRange)
  retmethod( XRange_isEqual(self, self2) ? True : False );
endmethod

// ----- size

#define size(rng) gautoDelete(aInt(XRange_size(rng)))
defproperty(XRange, ()size, size);
#undef  size

defmethod(U32, gsize, XRange)
  retmethod(XRange_size(self));
endmethod

// ----- foreach

defmethod(void, gforeach, XRange, Functor)
  U32 size = XRange_size(self);
  
  for (U32 i = 0; i < size; i++)
    geval(_2, aFloat(XRange_eval(self,i)));
endmethod

defmethod(void, gforeach, XRange, FltFunction1)
  U32 size = XRange_size(self);
  F64FCT1 fct = self2->fct;

  for (U32 i = 0; i < size; i++)
    fct(XRange_eval(self,i));
endmethod

// ----- map

defmethod(OBJ, gmap, Functor, XRange)
  U32 size = XRange_size(self2);
  struct FltVector* vec = FltVector_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  U32 *dst_n = &vec->size;
  F64 *dst   = vec->value;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = gflt( geval1(_1, aFloat(XRange_eval(self2,i))) ), ++*dst_n;

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap, FltFunction1, XRange)
  U32 size = XRange_size(self2);
  struct FltVector* vec = FltVector_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  U32 *dst_n  = &vec->size;
  F64 *dst    = vec->value;
  F64FCT1 fct = self->fct;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = fct(XRange_eval(self2,i)), ++*dst_n;

  retmethod(_vec);
endmethod


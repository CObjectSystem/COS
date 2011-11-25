/**
 * C Object System
 * COS Range
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/XRange.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/FltVector.h>

#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/range.h>
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

defmethod(OBJ, gnewXRng, pmXRange, (F64)start, (F64)end, (F64)stride)
  retmethod( (OBJ)XRange_init((void*)galloc(_1), start, end, stride) );
endmethod

// ----- copy/clone

defalias (OBJ, (gcopy)gclone, XRange);
defmethod(OBJ,  gcopy       , XRange)
  retmethod( (OBJ)XRange_copy((void*)galloc(XRange), self) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, XRange, XRange)
  retmethod( XRange_isEqual(self, self2) ? True : False );
endmethod

// ----- size

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
  OBJ _vec = gautoRelease( (OBJ)vec );

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
  OBJ _vec = gautoRelease( (OBJ)vec );

  U32 *dst_n  = &vec->size;
  F64 *dst    = vec->value;
  F64FCT1 fct = self->fct;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = fct(XRange_eval(self2,i)), ++*dst_n;

  retmethod(_vec);
endmethod


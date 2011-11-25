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

#include <cos/Range.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/IntVector.h>

#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/range.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

makclass(Range, ValueSequence);

// -----

useclass(Range);

// ----- new

defmethod(OBJ, gnewRng, pmRange, (I32)start, (I32)end, (I32)stride)
  retmethod( (OBJ)Range_init((void*)galloc(_1), start, end, stride) );
endmethod

// ----- clone

defalias (OBJ, (gcopy)gclone, Range);
defmethod(OBJ,  gcopy       , Range)
  retmethod( (OBJ)Range_copy((void*)galloc(Range), self) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Range, Range)
  retmethod( Range_isEqual(self, self2) ? True : False );
endmethod

// ----- size

defmethod(U32, gsize, Range)
  retmethod(Range_size(self));
endmethod

// ----- foreach

defmethod(void, gforeach, Range, Functor)
  U32 size = Range_size(self);
  
  for (U32 i = 0; i < size; i++)
    geval(_2, aInt(Range_eval(self,i)));
endmethod

defmethod(void, gforeach, Range, IntFunction1)
  U32 size = Range_size(self);
  I32FCT1 fct = self2->fct;

  for (U32 i = 0; i < size; i++)
    fct(Range_eval(self,i));
endmethod

// ----- map

defmethod(OBJ, gmap, Functor, Range)
  U32 size = Range_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoRelease( (OBJ)vec );

  U32 *dst_n = &vec->size;
  I32 *dst   = vec->value;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = gint( geval1(_1, aInt(Range_eval(self2,i))) ), ++*dst_n;

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap, IntFunction1, Range)
  U32 size = Range_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoRelease( (OBJ)vec );

  U32 *dst_n  = &vec->size;
  I32 *dst    = vec->value;
  I32FCT1 fct = self1->fct;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = fct(Range_eval(self2,i)), ++*dst_n;

  retmethod(_vec);
endmethod


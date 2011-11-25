/**
 * C Object System
 * COS Slice
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

#include <cos/Slice.h>
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
// #include <cos/prp/sequence.h>

makclass(Slice, ValueSequence);

// -----

useclass(Slice);

// ----- new

defmethod(OBJ, gnewSlc, pmSlice, (I32)start, (U32)size, (I32)stride)
  retmethod( (OBJ)Slice_init((struct Slice*)galloc(_1), start, size, stride) );
endmethod

// ----- copy/clone

defalias (OBJ, (gcopy)gclone, Slice);
defmethod(OBJ,  gcopy       , Slice)
  retmethod( (OBJ)Slice_copy((struct Slice*)galloc(Slice), self) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Slice, Slice)
  retmethod( Slice_isEqual(self, self2) ? True : False );
endmethod

// ----- size

defmethod(U32, gsize, Slice)
  retmethod(self->size);
endmethod

// ----- foreach

defmethod(void, gforeach, Slice, Functor)
  U32 size = Slice_size(self);
  
  for (U32 i = 0; i < size; i++)
    geval(_2, aInt(Slice_eval(self,i)));
endmethod

defmethod(void, gforeach, Slice, IntFunction1)
  U32 size = Slice_size(self);
  I32FCT1 fct = self2->fct;

  for (U32 i = 0; i < size; i++)
    fct(Slice_eval(self,i));
endmethod

// ----- map

defmethod(OBJ, gmap, Functor, Slice)
  U32 size = Slice_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoRelease( (OBJ)vec );

  U32 *dst_n = &vec->size;
  I32 *dst   = vec->value;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = gint( geval1(_1, aInt(Slice_eval(self2,i))) ), ++*dst_n;

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap, IntFunction1, Slice)
  U32 size = Slice_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoRelease( (OBJ)vec );

  U32 *dst_n  = &vec->size;
  I32 *dst    = vec->value;
  I32FCT1 fct = self1->fct;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = fct(Slice_eval(self2,i)), ++*dst_n;

   retmethod(_vec);
endmethod


/**
 * C Object System
 * COS Array - Array view
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

#include <cos/Array.h>
#include <cos/Number.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/collection.h>
#include <cos/gen/sequence.h>
#include <cos/gen/object.h>

// -----

makclass(ArrayView, Array);
makclass(ArraySubView, ArrayView);

// -----

useclass(ArrayView, ArraySubView, ExBadRange);

// ----- initializer (weaker than constructors: no retain)

defmethod(OBJ, ginitWith2, ArrayView, Array, Slice) // array view
  if ( Slice_first(self3) < self2->size && Slice_last(self3) < self2->size) {
    self->ref = 0;
    THROW( gnewWithStr(ExBadRange, "slice out of range") );
  }

  self->Array.object = Slice_start (self3)*self2->stride + self2->object;
  self->Array.size   = Slice_size  (self3);
  self->Array.stride = Slice_stride(self3)*self2->stride;
  self->ref          = _2; // no retain!

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, ArrayView, Array, Range) // array view
  OBJ slc = (OBJ)Slice_fromRange(atSlice(0), self3, &self2->size);
  
  retmethod( ginitWith2(_1, _2, slc) );
endmethod

defmethod(OBJ, ginitWith2, ArraySubView, Array, Slice) // array subview
  if ( Slice_first(self3) < self2->size && Slice_last(self3) < self2->size) {
    self->ArrayView.ref = 0;
    THROW( gnewWithStr(ExBadRange, "slice out of range") );
  }

  self->ArrayView.Array.object = Slice_start (self3) + self2->object;
  self->ArrayView.Array.size   = Slice_size  (self3);
  self->ArrayView.Array.stride = Slice_stride(self3);
  self->ArrayView.ref          = _2; // no retain!

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, ArraySubView, Array, Range) // array subview
  OBJ slc = (OBJ)Slice_fromRange(atSlice(0), self3, &self2->size);
  
  retmethod( ginitWith2(_1, _2, slc) );
endmethod

// ----- view constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mView, Array, Slice) // array view
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArrayView);    PRT(avw);

  ginitWith2(avw, arr, _3);

  UNPRT(arr);
  retmethod(avw);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Range);
defmethod(OBJ,  ginitWith2          , mView, Array, Range) // array view
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArrayView);    PRT(avw);

  ginitWith2(avw, arr, _3);

  UNPRT(arr);
  retmethod(avw);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Slice) // array subview
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArraySubView); PRT(avw);

  ginitWith2(avw, arr, _3);

  UNPRT(arr);
  retmethod(avw);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Range);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Range) // array subview
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArraySubView); PRT(avw);

  ginitWith2(avw, arr, _3);
  
  UNPRT(arr);
  retmethod(avw);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayView)
  if (self->ref)
    grelease(self->ref), self->ref = 0;
    
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayView, (STR)file, (int)line)
  struct Array *arr = dyncast(Array, self->ref);

  ensure( arr, "array view points to something not an array", file, line);
  ensure( !dyncast(ArrayDyn, self->ref) || cos_object_rc(_1) == COS_RC_AUTO,
               "array view points to a dynamic array", file, line);

  I32 start  = (arr->object - self->Array.object)/arr->stride;
  U32 size   = self->Array.size;
  I32 stride = self->Array.stride/arr->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  ensure( first < arr->size && last < arr->size,
               "array view is out of range", file, line);

  if (next_method_p)
    next_method(self, file, line);
endmethod


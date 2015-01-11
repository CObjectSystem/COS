/**
 * C Object System
 * COS Array - block array
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
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/XRange.h>

#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/init.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include "Array_utl.h"

// -----

makclass(Array, Sequence);
makclass(ArrayBlk, Array);

makclass(Array0, ArrayBlk);
makclass(Array1, ArrayBlk);
makclass(Array2, ArrayBlk);
makclass(Array3, ArrayBlk);
makclass(Array4, ArrayBlk);
makclass(Array5, ArrayBlk);
makclass(Array6, ArrayBlk);
makclass(Array7, ArrayBlk);
makclass(Array8, ArrayBlk);
makclass(Array9, ArrayBlk);
makclass(ArrayN, ArrayBlk);

// -----

useclass(Array, Int, Float, ExOverflow);

// --- getters

defmethod(OBJ, gisEmpty, Array)
  retmethod(self->size ? False : True);
endmethod

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(I32, gstride, Array)
  retmethod(self->stride);
endmethod

defmethod(OBJ*, gobjPtr, Array)
  retmethod(self->object);
endmethod

defmethod(OBJ, gclass, Array)
  retmethod(Array);     // class cluster: hide implementation details
endmethod

// --- transformers

defmethod(OBJ, gadjust, Array)
  retmethod(_1);
endmethod

// --- alloc

struct Array*
Array_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[] = {
    classref(Array0, Array1, Array2, Array3, Array4,
             Array5, Array6, Array7, Array8, Array9,
             ArrayN)
  };

  size_t extra = size * sizeof(OBJ);

  // check for overflow
  if (extra/sizeof(OBJ) < size)
    THROW(gnewWithStr(ExOverflow, "size is too large"));

  OBJ _cls = (OBJ)cls[size > N ? N : size];
  OBJ _arr = gallocWithSize(_cls, extra);

  struct ArrayN *arrn = CAST(struct ArrayN*, _arr);
  struct Array  *arr  = &arrn->ArrayBlk.Array;

  arr->object = arrn->_object;
  arr->size   = 0;
  arr->stride = 1;

  return arr;
}

// ----- allocator

defmethod(OBJ, galloc, pmArray) // lazy alloc
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, Array)
  U32 *val_n = &self->size;
  OBJ *val   = self->object;
  OBJ *end   = val + *val_n;

  while (val != end)
    grelease(*--end), --*val_n;

  retmethod(_1);
endmethod

// ----- constructors

defalias (OBJ, (ginitWith)gnewWith, pmArray, Array);
defmethod(OBJ,  ginitWith         , pmArray, Array) // copy
  struct Array* cpy = Array_alloc(self2->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  arr_copy(cpy->object, 1, &cpy->size, self2->object, self2->stride, self2->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Slice);
defmethod(OBJ,  ginitWith         , pmArray, Slice) // Int sequence
  U32 size = Slice_size(self2);
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < size; i++) {
    arr->object[i] = ginitWithInt(galloc(Int), Slice_eval(self2,i));
    arr->size++;
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Range);
defmethod(OBJ,  ginitWith         , pmArray, Range) // Int sequence
  U32 size = Range_size(self2);
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < size; i++) {
    arr->object[i] = ginitWithInt(galloc(Int), Range_eval(self2,i));
    arr->size++;
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, XRange);
defmethod(OBJ,  ginitWith         , pmArray, XRange) // Float sequence
  U32 size = XRange_size(self2);
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < size; i++) {
    arr->object[i] = ginitWithFlt(galloc(Float), XRange_eval(self2,i));
    arr->size++;
  }
  
  if (size) { // avoid overshoot
    F64 end = XRange_eval(self2, size-1);

    if ((XRange_stride(self2) > 0 && end > XRange_end(self2)) ||
        (XRange_stride(self2) < 0 && end < XRange_end(self2)))
      ginitWithFlt(arr->object[size-1], XRange_end(self2));
  }
  
  UNPRT(_arr);
  retmethod(_arr);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Int, Object);
defmethod(OBJ,  ginitWith2          , pmArray, Int, Object) // element
PRE
  ensure(self2->value >= 0, "negative array size");

BODY
  U32 size = self2->value;
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  U32 *dst_n = &arr->size;
  OBJ *dst   = arr->object;
  OBJ *end   = dst + size;

  while (dst != end)
    *dst++ = gretain(_3), ++*dst_n;

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Int, Functor);
defmethod(OBJ,  ginitWith2          , pmArray, Int, Functor) // generator
PRE
  ensure(self2->value >= 0, "negative array size");

BODY
  U32 size = self2->value;
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  U32 *dst_n = &arr->size;
  OBJ *dst   = arr->object;
  OBJ *end   = dst + size;

  while (dst != end)
    *dst++ = gretain(geval(_3)), ++*dst_n;

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Array, Slice);
defmethod(OBJ,  ginitWith2          , pmArray, Array, Slice) // sub array
PRE
  ensure( Slice_first(self3) < self2->size &&
               Slice_last (self3) < self2->size, "slice out of range" );
               
BODY
  U32 size = Slice_size(self3);
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  I32 start  = Slice_start (self3)*self2->stride;
  I32 stride = Slice_stride(self3)*self2->stride;

  arr_copy(arr->object, 1, &arr->size, self2->object+start, stride, size);

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Array, Range);
defmethod(OBJ,  ginitWith2          , pmArray, Array, Range) // sub array
  struct Slice* slc = Slice_fromRange(atSlice(0), self3, &self2->size);

  retmethod( ginitWith2(_1,_2,(OBJ)slc) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Array, IntVector);
defmethod(OBJ,  ginitWith2          , pmArray, Array, IntVector) // random sequence
  U32 size = self3->size;
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  U32  val_n = self2->size;
  I32  val_s = self2->stride;
  OBJ *val   = self2->object;
  I32  idx_s = self3->stride;
  I32 *idx   = self3->value;
  U32 *dst_n = &arr->size;
  OBJ *dst   = arr->object;
  OBJ *end   = dst + size;

  while (dst != end) {
    U32 i = Range_index(*idx, val_n);
    ensure( i < val_n, "index out of range" );
    *dst++ = gretain(val[i*val_s]), ++*dst_n;
    idx += idx_s;
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

// ----- copy, clone, swap, assign

defmethod(OBJ, gcopy, Array) // copy
  struct Array* cpy = Array_alloc(self->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  arr_copy(cpy->object, 1, &cpy->size, self->object, self->stride, self->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defmethod(OBJ, gclone, Array) // clone
  struct Array* cpy = Array_alloc(self->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  arr_clone(cpy->object, 1, &cpy->size, self->object, self->stride, self->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defmethod(OBJ, gswap, Array, Array) // swap
PRE
  ensure( self->size >= self2->size, "incompatible array size" );

BODY
  arr_swap(self->object, self->stride, self2->object, self2->stride, self2->size);

  retmethod(_1);
endmethod

defmethod(OBJ, gassign, Array, Array) // assign
PRE
  ensure( self->size >= self2->size, "incompatible array size" );

BODY
  arr_assign(self->object, self->stride, self2->object, self2->stride, self2->size);

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, Array, (STR)file, (int)line)
  U32  size  = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;
  OBJ *end   = val + val_s*size;

  while (val != end && *val)
    val += val_s;

  ensure( val == end, "array contains null elements", file, line);
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Array view
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
 | $Id: Array_vw.c,v 1.1 2009/08/14 21:47:55 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/object.h>

// -----

makclass(ArrayView, Array);

// -----

useclass(ExBadAlloc);
useclass(Array, ArrayView);

// ----- initializer

struct Array*
ArrayView_init(struct ArrayView *arrv, struct Array *arr, struct Slice *slc)
{
  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < arr->size &&
               last  < arr->size, "slice out of range" );

  struct Array* avw = &arrv->Array;

  avw->object = Slice_start (slc)*arr->stride + arr->object;
  avw->size   = Slice_size  (slc);
  avw->stride = Slice_stride(slc)*arr->stride;
  arrv->array = arr;

  return avw;
}

// ----- constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mView, Array, Slice) // array view
  retmethod( ginitWith2(galloc(ArrayView),_2,_3) );
endmethod

defmethod(OBJ, ginitWith2, ArrayView, Array, Slice)
  test_assert( !cos_object_isa(_2, classref(ArrayDyn))
            && !cos_object_isa(_2, classref(ArrayLazy   )),
               "Array views accept only non-Dyn arrays" );

  ArrayView_init(self, self2, self3);

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayView)
  if (self->array)              // take care of protection cases
    grelease( (OBJ)self->array );
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf((OBJ)self->array, classref(Array)),
               "ArrayView points to something not an array", func, file, line);

  test_assert( !cos_object_isa((OBJ)self->array, classref(ArrayDyn)),
               "ArrayView points to a dynamic array", func, file, line);

  test_assert( !cos_object_isa((OBJ)self->array, classref(ArrayLazy)),
               "ArrayView points to a lazy array", func, file, line);

  struct Array *arr = STATIC_CAST(struct Array*, self->array);

  I32 start  = (arr->object - self->Array.object)/arr->stride;
  U32 size   = self->Array.size;
  I32 stride = self->Array.stride/arr->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < self->array->size && last < self->array->size,
               "ArrayView is out of range", func, file, line);

  next_method(self, func, file, line);
endmethod


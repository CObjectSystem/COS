/*
 o---------------------------------------------------------------------o
 |
 | COS Array - invariants
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
 | $Id: Array_inv.c,v 1.1 2009/08/08 16:36:09 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Slice.h>
#include <cos/gen/object.h>

defmethod(void, ginvariant, Array, (STR)func, (STR)file, (int)line)
  OBJ *obj   = self->object;
  OBJ *end   = self->object + self->size*self->stride;
  I32  obj_s = self->stride;

  while (obj != end && *obj)
    obj += obj_s;

  test_assert( obj == end,
               "Array contains null elements", func, file, line);
endmethod

defmethod(void, ginvariant, ArrayDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->capacity >= self->ArrayAdj.Array.size,
               "ArrayDyn has capacity < size", func, file, line);

  next_method(self, func, file, line);
endmethod

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


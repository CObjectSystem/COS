/*
 o---------------------------------------------------------------------o
 |
 | COS Array - dynamic array
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
 | $Id: Array_dyn.c,v 1.8 2009/07/24 12:36:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>

#include <cos/gen/object.h>
#include <cos/gen/container.h>

#include <stdlib.h>
#include <string.h>

// -----

#define ARRAY_MIN_SIZE    16
#define ARRAY_GROWTH_RATE 1.618034 // golden ratio

useclass(Array, ExBadAlloc);

// ----- helpers (alloc and deinit are in Array.c)

void
ArrayDynamic_adjust(struct ArrayDynamic *arrd)
{
  struct ArrayDynamicN *arrn = &arrd->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  // move data to storage base
  if (arr->object != arrn->_object)
    arr->object = memmove(arrn->_object, arr->object, arr->size * sizeof *arrn->_object);

  // shrink storage
  if (arr->size != arrd->capacity) {
    OBJ *_object = realloc(arrn->_object, arr->size * sizeof *arrn->_object);
    if (!_object) THROW(ExBadAlloc);

    arr ->object   = _object;
    arrn->_object  = _object;
    arrd->capacity = arr->size;
  }
}

void
ArrayDynamic_enlarge(struct ArrayDynamic *arrd, F64 factor)
{
  enum { N = ARRAY_MIN_SIZE };

  if (factor <= 1.0) return;

  struct ArrayDynamicN *arrn = &arrd->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  ptrdiff_t offset = arr->object - arrn->_object;

  U32   size   = arrd->capacity < N ? N : arrd->capacity * factor;
  OBJ *_object = realloc(arrn->_object, size * sizeof *arrn->_object);
  if (!_object) THROW(ExBadAlloc);

  arr ->object   = _object + offset;
  arrn->_object  = _object;
  arrd->capacity = size;
}

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, ArrayDynamic)
  ArrayDynamic_adjust(self);

  test_assert( cos_object_changeClass(_1, classref(ArrayDynamicN)),
               "unable to change dynamic array to fixed size array" );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, ArrayDynamic)
  struct ArrayDynamicN *arrn = &self->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  OBJ *obj = arr->object;
  OBJ *end = arr->object + arr->size;

  while (obj != end)
    grelease(*obj++);

  arr->object = arrn->_object;
  arr->size   = 0;
endmethod

// ----- getters, setters

defalias (OBJ, (gget)glast, ArrayDynamic);
defalias (OBJ, (gget)gtop , ArrayDynamic);
defmethod(OBJ,  gget      , ArrayDynamic)
  struct Array *arr = &self->ArrayDynamicN.Array;

  retmethod( arr->size ? arr->object[arr->size-1] : Nil );
endmethod

defalias (void, (gput)gappend, ArrayDynamic, Object);
defalias (void, (gput)gpush  , ArrayDynamic, Object);
defmethod(void,  gput        , ArrayDynamic, Object)
  struct Array *arr = &self->ArrayDynamicN.Array;

  if (arr->size == self->capacity)
    ArrayDynamic_enlarge(self, ARRAY_GROWTH_RATE);
    
  arr->object[arr->size++] = gretain(_2);
endmethod

defalias (void, (gdrop)gpop, ArrayDynamic);
defmethod(void,  gdrop     , ArrayDynamic)
  struct Array *arr = &self->ArrayDynamicN.Array;

  if (arr->size)
    grelease(arr->object[--arr->size]);
endmethod

// ----- prepend, append

#if 0 // NOTE-TODO

defmethod(void, gprepend, ArrayDynamic, Object)
  // TODO, enlarge capacity if needed, move data by size diff
endmethod

defmethod(void, gprepend, ArrayDynamic, Array)
  struct Array *arr = &self->ArrayDynamicN.Array;

  if (self->capacity - arr->size < self2->size) {
    F64 factor = 1.0;

    do
      factor *= ARRAY_GROWTH_RATE;
    while (self->capacity*factor - arr->size < self2->size);

    ArrayDynamic_enlarge(self, factor);
  }

  memcpy(arr->object+ self2->size,
         arr->object, self2->size * sizeof *arr->object);

  OBJ *obj = arr  ->object;
  OBJ *src = self2->object;
  OBJ *end = self2->object+self2->size;

  while (src < end)
    *obj++ = gretain(*src++);

  arr->size += self2->size;
endmethod

defmethod(void, gappend, ArrayDynamic, Array)
  struct Array *arr = &self->ArrayDynamicN.Array;

  if (self->capacity - arr->size < self2->size) {
    F64 factor = 1.0;

    do
      factor *= ARRAY_GROWTH_RATE;
    while (self->capacity*factor - arr->size < self2->size);

    ArrayDynamic_enlarge(self, factor);
  }

  OBJ *obj = arr  ->object+arr->size;
  OBJ *src = self2->object;
  OBJ *end = self2->object+self2->size;

  while (src < end)
    *obj++ = gretain(*src++);

  arr->size += self2->size;
endmethod

#endif

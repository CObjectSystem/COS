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
 | $Id: Array_dyn.c,v 1.9 2009/07/24 20:49:58 ldeniau Exp $
 |
*/

#include <cos/Array.h>

#include <cos/gen/object.h>
#include <cos/gen/container.h>

#include <stdlib.h>
#include <string.h>

// -----

#define ARRAY_MIN_SIZE    10
#define ARRAY_GROWTH_RATE 1.618034 // golden ratio

STATIC_ASSERT(array_min_size_is_too_small   , ARRAY_MIN_SIZE    >= 4  );
STATIC_ASSERT(array_growth_rate_is_too_small, ARRAY_GROWTH_RATE >= 1.5);

useclass(Array, ExBadAlloc);

// ----- memory management (alloc and deinit are in Array.c)

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
  if (factor <= 1.0) return;

  struct ArrayDynamicN *arrn = &arrd->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  ptrdiff_t offset = arr->object - arrn->_object;

  U32 capacity = (arrd->capacity < ARRAY_MIN_SIZE ? ARRAY_MIN_SIZE : arrd->capacity)*factor;
  OBJ *_object = realloc(arrn->_object, capacity*sizeof *arrn->_object);
  if (!_object) THROW(ExBadAlloc);

  arr ->object   = _object + offset;
  arrn->_object  = _object;
  arrd->capacity = capacity;
}

void
ArrayDynamic_enlargeFront(struct ArrayDynamic *arrd, F64 factor)
{
  if (factor <= 1.0) return;

  struct ArrayDynamicN *arrn = &arrd->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  ptrdiff_t offset = arr->object - arrn->_object;

  U32 old_capacity = arrd->capacity;

  ArrayDynamic_enlarge(arrd, factor);
  arr->object = arrn->_object + (arrd->capacity - old_capacity);
  memmove(arr->object, arrn->_object + offset, arr->size*sizeof *arr->object);
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

  OBJ *obj = arr->object + arr->size;
  OBJ *end = arr->object;

  while (obj != end) {
    grelease(*--obj);
    arr->size--;
  }
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
    
  arr->object[arr->size] = gretain(_2);
  arr->size++;
endmethod

defalias (void, (gdrop)gpop, ArrayDynamic);
defmethod(void,  gdrop     , ArrayDynamic)
  struct Array *arr = &self->ArrayDynamicN.Array;

  if (arr->size)
    grelease(arr->object[--arr->size]);
endmethod

// ----- prepend, append

defmethod(void, gprepend, ArrayDynamic, Object)
  struct ArrayDynamicN *arrn = &self->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  if (arr->object == arrn->_object)
    ArrayDynamic_enlargeFront(self, ARRAY_GROWTH_RATE);

  arr->object[-1] = gretain(_2);
  arr->object--;
  arr->size++;
endmethod

defmethod(void, gprepend, ArrayDynamic, Array)
  struct ArrayDynamicN *arrn = &self->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  if (arr->object - arrn->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = (self->capacity < ARRAY_MIN_SIZE ? ARRAY_MIN_SIZE : self->capacity);

    do
      factor *= ARRAY_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    ArrayDynamic_enlargeFront(self, factor);
  }

  OBJ *src   = self2->object;
  I32  src_s = self2->stride;
  OBJ *end   = self2->object + self2->size*self2->stride;

  while (src != end) {
    arr->object[-1] = gretain(*src);
    arr->object--;
    arr->size++;
    src += src_s;
  }
endmethod

defmethod(void, gappend, ArrayDynamic, Array)
  struct ArrayDynamicN *arrn = &self->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  if (arr->object - arrn->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = (self->capacity < ARRAY_MIN_SIZE ? ARRAY_MIN_SIZE : self->capacity);

    do
      factor *= ARRAY_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    ArrayDynamic_enlarge(self, factor);
  }

  OBJ *dst   = arr->object;
  OBJ *src   = self2->object;
  I32  src_s = self2->stride;
  OBJ *end   = self2->object + self2->size*self2->stride;

  while (src != end) {
    dst[arr->size] = gretain(*src);
    arr->size++;
    src += src_s;
  }
endmethod


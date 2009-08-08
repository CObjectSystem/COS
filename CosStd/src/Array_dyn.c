/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Dyn array
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
 | $Id: Array_dyn.c,v 1.10 2009/08/08 16:36:09 ldeniau Exp $
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
ArrayDyn_adjust(struct ArrayDyn *arrd)
{
  struct ArrayAdj *arra = &arrd->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  // move data to storage base
  if (arr->object != arra->_object)
    arr->object = memmove(arra->_object, arr->object, arr->size * sizeof *arra->_object);

  // shrink storage
  if (arr->size != arrd->capacity) {
    OBJ *_object = realloc(arra->_object, arr->size * sizeof *arra->_object);
    if (!_object) THROW(ExBadAlloc);

    arr ->object   = _object;
    arra->_object  = _object;
    arrd->capacity = arr->size;
  }
}

void
ArrayDyn_enlarge(struct ArrayDyn *arrd, F64 factor)
{
  if (factor <= 1.0) return;

  struct ArrayAdj *arra = &arrd->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  ptrdiff_t offset = arr->object - arra->_object;

  U32 capacity = (arrd->capacity < ARRAY_MIN_SIZE ? ARRAY_MIN_SIZE : arrd->capacity)*factor;
  OBJ *_object = realloc(arra->_object, capacity*sizeof *arra->_object);
  if (!_object) THROW(ExBadAlloc);

  arr ->object   = _object + offset;
  arra->_object  = _object;
  arrd->capacity = capacity;
}

void
ArrayDyn_enlargeFront(struct ArrayDyn *arrd, F64 factor)
{
  if (factor <= 1.0) return;

  struct ArrayAdj *arra = &arrd->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  ptrdiff_t offset = arr->object - arra->_object;

  U32 old_capacity = arrd->capacity;

  ArrayDyn_enlarge(arrd, factor);
  arr->object = arra->_object + (arrd->capacity - old_capacity);
  memmove(arr->object, arra->_object + offset, arr->size*sizeof *arr->object);
}

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, ArrayDyn)
  ArrayDyn_adjust(self);

  test_assert( cos_object_changeClass(_1, classref(ArrayAdj)),
               "unable to change Dyn array to fixed size array" );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, ArrayDyn)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  OBJ *obj = arr->object + arr->size;
  OBJ *end = arr->object;

  while (obj != end) {
    grelease(*--obj);
    arr->size--;
  }
endmethod

// ----- getters, setters

defalias (OBJ, (gget)glast, ArrayDyn);
defalias (OBJ, (gget)gtop , ArrayDyn);
defmethod(OBJ,  gget      , ArrayDyn)
  struct Array *arr = &self->ArrayAdj.Array;

  retmethod( arr->size ? arr->object[arr->size-1] : Nil );
endmethod

defalias (void, (gput)gappend, ArrayDyn, Object);
defalias (void, (gput)gpush  , ArrayDyn, Object);
defmethod(void,  gput        , ArrayDyn, Object)
  struct Array *arr = &self->ArrayAdj.Array;

  if (arr->size == self->capacity)
    ArrayDyn_enlarge(self, ARRAY_GROWTH_RATE);
    
  arr->object[arr->size] = gretain(_2);
  arr->size++;
endmethod

defalias (void, (gdrop)gpop, ArrayDyn);
defmethod(void,  gdrop     , ArrayDyn)
  struct Array *arr = &self->ArrayAdj.Array;

  if (arr->size)
    grelease(arr->object[--arr->size]);
endmethod

// ----- prepend, append

defmethod(void, gprepend, ArrayDyn, Object)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  if (arr->object == arra->_object)
    ArrayDyn_enlargeFront(self, ARRAY_GROWTH_RATE);

  arr->object[-1] = gretain(_2);
  arr->object--;
  arr->size++;
endmethod

defmethod(void, gprepend, ArrayDyn, Array)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  if (arr->object - arra->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = (self->capacity < ARRAY_MIN_SIZE ? ARRAY_MIN_SIZE : self->capacity);

    do
      factor *= ARRAY_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    ArrayDyn_enlargeFront(self, factor);
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

defmethod(void, gappend, ArrayDyn, Array)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  if (arr->object - arra->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = (self->capacity < ARRAY_MIN_SIZE ? ARRAY_MIN_SIZE : self->capacity);

    do
      factor *= ARRAY_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    ArrayDyn_enlarge(self, factor);
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


/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Dynamic array
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
 | $Id: Array_dyn.c,v 1.13 2009/08/14 21:47:55 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/container.h>

#include <stdlib.h>
#include <string.h>

// -----

makclass(ArrayAdj, Array);
makclass(ArrayDyn, ArrayAdj);

// -----

#define ARRAY_GROWTH_RATE 1.618034 // golden ratio

STATIC_ASSERT(array_growth_rate_is_too_small, ARRAY_GROWTH_RATE >= 1.5);

useclass(Array, ArrayDyn, ExBadAlloc);

// ----- constructors

defalias (OBJ, (ginit)gnew, pmArray);
defmethod(OBJ,  ginit     , pmArray) // Dyn array
  retmethod( ginit(galloc(ArrayDyn)) );
endmethod

defmethod(OBJ, ginit, ArrayDyn)
  retmethod( ginitWith(_1,aInt(0)) );
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Int);
defmethod(OBJ,  ginitWith         , pmArray, Int) // Dyn array with capacity
  retmethod( ginitWith(galloc(ArrayDyn),_2) );
endmethod

defmethod(OBJ, ginitWith, ArrayDyn, Int)
  enum { MIN_SIZE = 1024 };
  I32 capacity = self2->value;
  test_assert(capacity >= 0, "negative array capacity");
  if (capacity < MIN_SIZE) capacity = MIN_SIZE;

  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  arr->object = malloc(capacity * sizeof *arr->object);
  if (!arr->object) THROW(ExBadAlloc);

  arr->size      = 0;
  arr->stride    = 1;
  arra->_object  = arr->object;
  self->capacity = capacity;

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayAdj)
  if (self->_object)            // take care of protection cases
    free(self->_object);
  next_method(self);
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->capacity >= self->ArrayAdj.Array.size,
               "ArrayDyn has capacity < size", func, file, line);

  next_method(self, func, file, line);
endmethod

// ----- memory management

defmethod(void, genlarge, ArrayDyn, Float)
  F64 factor   = self2->value;
  U32 capacity = self->capacity;

  if (factor > 1.0)
    genlarge(_1, aInt(capacity * (factor-1)));
  else if (factor < 1.0)
    genlarge(_1, aInt(capacity * (1-factor)));
endmethod

defmethod(void, genlarge, ArrayDyn, Int)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;
  U32          capacity = self->capacity;
  ptrdiff_t      offset = arr->object - arra->_object;
  BOOL            front = self2->value < 0;
  I32             addon = front ? -self2->value : self2->value;
  
  if (addon > 0) {
    U32 capacity = self->capacity + addon;
    OBJ *_object = realloc(arra->_object, capacity*sizeof *arra->_object);
    if (!_object) THROW(ExBadAlloc);

    arr ->object   = _object + offset;
    arra->_object  = _object;
    self->capacity = capacity;
  }
  if (front) { // move data to book the new space front
    arr->object = arra->_object + (self->capacity - capacity);
    memmove(arr->object, arra->_object + offset, arr->size*sizeof *arr->object);
  }
endmethod

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, ArrayDyn)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  // move data to storage base
  if (arr->object != arra->_object)
    arr->object = memmove(arra->_object, arr->object, arr->size * sizeof *arra->_object);

  // shrink storage
  if (arr->size != self->capacity) {
    OBJ *_object = realloc(arra->_object, arr->size * sizeof *arra->_object);
    if (!_object) THROW(ExBadAlloc);

    arr ->object   = _object;
    arra->_object  = _object;
    self->capacity = arr->size;
  }

  test_assert( cos_object_changeClass(_1, classref(ArrayAdj)),
               "unable to change Dyn array to fixed size array" );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, ArrayDyn)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  OBJ *obj = arr->object + arr->size;
  OBJ *end = arr->object;

  while (obj != end)
    grelease(*--obj), *obj = 0;

  arr->size = 0;
endmethod

// ----- getters, setters

defalias (void, (gput)gappend, ArrayDyn, Object);
defalias (void, (gput)gpush  , ArrayDyn, Object);
defmethod(void,  gput        , ArrayDyn, Object)
  struct Array *arr = &self->ArrayAdj.Array;

  if (arr->size == self->capacity)
    genlarge(_1, aFloat(ARRAY_GROWTH_RATE));
    
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
    genlarge(_1, aFloat(-ARRAY_GROWTH_RATE));

  arr->object[-1] = gretain(_2);
  arr->object--;
  arr->size++;
endmethod

defmethod(void, gprepend, ArrayDyn, Array)
  struct ArrayAdj *arra = &self->ArrayAdj;
  struct Array    *arr  = &arra->Array;

  if (arr->object - arra->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = self->capacity;

    do
      factor *= ARRAY_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    genlarge(_1, aFloat(-factor));
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
    U32 capacity = self->capacity;

    do
      factor *= ARRAY_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    genlarge(_1, aFloat(factor));
  }

  OBJ *src   = self2->object;
  I32  src_s = self2->stride;
  OBJ *end   = self2->object + self2->size*self2->stride;

  while (src != end) {
    arr->object[arr->size] = gretain(*src);
    arr->size++;
    src += src_s;
  }
endmethod


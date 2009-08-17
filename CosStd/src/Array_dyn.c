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
 | $Id: Array_dyn.c,v 1.14 2009/08/17 12:57:13 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/container.h>

#include <stdlib.h>
#include <string.h>

// -----

makclass(ArrayFix, Array);
makclass(ArrayDyn, ArrayFix);

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

  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  arr->object = malloc(capacity * sizeof *arr->object);
  if (!arr->object) THROW(ExBadAlloc);

  arr->size      = 0;
  arr->stride    = 1;
  arrf->_object  = arr->object;
  arrf->_cls     = 0;
  arrf->capacity = capacity;

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayFix)
  if (self->_object)            // take care of protection cases
    free(self->_object);
  next_method(self);
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->ArrayFix.capacity >= self->ArrayFix.Array.size,
               "dynamic array has capacity < size", func, file, line);

  next_method(self, func, file, line);
endmethod

// ----- memory management

defmethod(void, genlarge, ArrayDyn, Float)
  F64 factor   = self2->value;
  U32 capacity = self->ArrayFix.capacity;

  if (factor > 1.0)
    genlarge(_1, aInt(capacity * (factor-1)));
  else if (factor < 1.0)
    genlarge(_1, aInt(capacity * (1-factor)));
endmethod

defmethod(void, genlarge, ArrayDyn, Int)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;
  U32     capacity = arrf->capacity;
  ptrdiff_t offset = arr->object - arrf->_object;
  BOOL       front = self2->value < 0;
  I32        addon = front ? -self2->value : self2->value;
  
  if (addon > 0) {
    U32 capacity = arrf->capacity + addon;
    OBJ *_object = realloc(arrf->_object, capacity*sizeof *arrf->_object);
    if (!_object) THROW(ExBadAlloc);

    arr ->object   = _object + offset;
    arrf->_object  = _object;
    arrf->capacity = capacity;
  }
  if (front) { // move data to book the new space front
    arr->object = arrf->_object + (arrf->capacity - capacity);
    memmove(arr->object, arrf->_object + offset, arr->size*sizeof *arr->object);
  }
endmethod

// ----- fix/unfix

defmethod(void, gfix, ArrayDyn)
  PRE
    test_assert(!self->ArrayFix._cls, "corrupted dynamic array");

  BODY
    self->ArrayFix._cls = cos_object_id(_1);
    self->ArrayFix.Array.Sequence.Container.Object.id = classref(ArrayFix)->Behavior.id;
endmethod

defmethod(void, gunfix, ArrayFix)
  PRE
    test_assert(self->_cls, "corrupted dynamic array (already unfixed?)");

  BODY
    self->Array.Sequence.Container.Object.id = self->_cls;
    self->_cls = 0;
endmethod

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, ArrayDyn)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  // move data to storage base
  if (arr->object != arrf->_object)
    arr->object = memmove(arrf->_object, arr->object, arr->size * sizeof *arrf->_object);

  // shrink storage
  if (arr->size != arrf->capacity) {
    OBJ *_object = realloc(arrf->_object, arr->size * sizeof *arrf->_object);
    if (!_object) THROW(ExBadAlloc);

    arr ->object   = _object;
    arrf->_object  = _object;
    arrf->capacity = arr->size;
  }

  test_assert( cos_object_changeClass(_1, classref(ArrayFix)),
               "unable to change dynamic array to fixed size array" );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, ArrayDyn)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

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
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arr->size == arrf->capacity)
    genlarge(_1, aFloat(ARRAY_GROWTH_RATE));
    
  arr->object[arr->size] = gretain(_2);
  arr->size++;
endmethod

defalias (void, (gdrop)gpop, ArrayDyn);
defmethod(void,  gdrop     , ArrayDyn)
  struct Array *arr = &self->ArrayFix.Array;

  if (arr->size)
    grelease(arr->object[--arr->size]);
endmethod

// ----- prepend, append

defmethod(void, gprepend, ArrayDyn, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arr->object == arrf->_object)
    genlarge(_1, aFloat(-ARRAY_GROWTH_RATE));

  arr->object[-1] = gretain(_2);
  arr->object--;
  arr->size++;
endmethod

defmethod(void, gprepend, ArrayDyn, Array)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arr->object - arrf->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = arrf->capacity;

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
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arr->object - arrf->_object < self2->size) {
    F64 factor = 1.0;
    U32 capacity = arrf->capacity;

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


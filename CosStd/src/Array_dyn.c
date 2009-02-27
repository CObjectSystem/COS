/*
 o---------------------------------------------------------------------o
 |
 | COS Array - accessors
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
 | $Id: Array_dyn.c,v 1.7 2009/02/27 20:14:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>

#include <cos/gen/object.h>
#include <cos/gen/container.h>

#include <stdlib.h>
#include <string.h>

// -----

#define ARRAY_GROWTH_RATE 1.618034 // golden ratio

useclass(Array, ExBadAlloc);

// ----- helpers

void
ArrayDynamic_adjust(struct ArrayDynamic *dyna)
{
  struct ArrayDynamicN *dynn = &dyna->ArrayDynamicN;
  struct Array         * arr = &dynn->Array;

  if (arr->object != dynn->base)
    arr->object = memmove(dynn->base, arr->object, arr->size * sizeof *dynn->base);

  if (arr->size != dyna->capacity) {
    OBJ *base = realloc(dynn->base, arr->size * sizeof *dynn->base);

    if (!base) return;

    arr ->object   = base;
    dynn->base     = base;
    dyna->capacity = arr->size;
  }
}

void
ArrayDynamic_enlarge(struct ArrayDynamic *dyna, F64 factor)
{
  enum { N = 10 };
  
  if (factor <= 1.0) return;

  struct ArrayDynamicN *dynn = &dyna->ArrayDynamicN;
  struct Array         * arr = &dynn->Array;

  ptrdiff_t offset = arr->object - dynn->base;

  U32  size = dyna->capacity < N ? N : dyna->capacity * factor;
  OBJ *base = realloc(dynn->base, size * sizeof *dynn->base);

  if (!base) THROW(ExBadAlloc);

  arr ->object   = base + offset;
  dynn->base     = base;
  dyna->capacity = size;
}

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, ArrayDynamic)
  ArrayDynamic_adjust(self);

  test_assert( cos_object_changeClass(_1, classref(ArrayDynamicN)),
               "unable to change dynamic array to fixed size array" );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, ArrayDynamic)
  struct ArrayDynamicN *dynn = &self->ArrayDynamicN;
  struct Array         *arr  = &dynn->Array;

  OBJ *obj = arr->object;
  OBJ *end = arr->object+arr->size;

  while (obj < end)
    grelease(*obj++);

  arr->object = dynn->base;
  arr->size   = 0;
endmethod

// ----- getters, setters

defalias (OBJ, (gget)gtop, ArrayDynamic);
defmethod(OBJ,  gget     , ArrayDynamic)
  struct Array *arr = &self->ArrayDynamicN.Array;

  retmethod( arr->size ? arr->object[arr->size-1] : 0 );
endmethod

defalias (void, (gput)gpush, ArrayDynamic, Object);
defmethod(void,  gput      , ArrayDynamic, Object)
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



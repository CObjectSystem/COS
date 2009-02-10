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
 | $Id: Array_dyn.c,v 1.2 2009/02/10 16:57:09 ldeniau Exp $
 |
*/

#include <cos/Array.h>

#include <cos/gen/object.h>
#include <cos/gen/container.h>

// -----

#define ARRAY_GROWTH_RATE 1.618034 // golden ratio

useclass(Array);

// ----- removing

defalias (void, (gdrop)gpop   , DynamicArray);
defalias (void, (gdrop)gremove, DynamicArray);
defmethod(void,  gdrop        , DynamicArray)
  struct Array *arr = &self->DynamicArrayN.Array;

  if (arr->size) grelease(arr->object[--arr->size]);
endmethod

// ----- getting

defalias (OBJ, (gget)gtop , DynamicArray);
defmethod(OBJ,  gget      , DynamicArray)
  struct Array *arr = &self->DynamicArrayN.Array;

  retmethod( arr->size ? arr->object[arr->size-1] : 0 );
endmethod

// ----- adding

defalias (void, (gput)gappend, DynamicArray, Any);
defalias (void, (gput)gpush  , DynamicArray, Any);
defmethod(void,  gput        , DynamicArray, Any)
  struct Array *arr = &self->DynamicArrayN.Array;

  if (arr->size == self->capacity)
    DynamicArray_enlarge(self, ARRAY_GROWTH_RATE);
    
  arr->object[arr->size++] = gretain(_2);
endmethod

defmethod(void, gappend, DynamicArray, Array)
  struct Array *arr = &self->DynamicArrayN.Array;

  if (self->capacity - arr->size < self2->size) {
    F64 size = arr->size;

    do
      size *= ARRAY_GROWTH_RATE;
    while (self->capacity - size < self2->size);

    DynamicArray_enlarge(self, size);
  }

  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+self2->size;
  OBJ *src = self2->object;

  while (obj < end)
    *obj++ = gretain(*src++);

  arr->size += self2->size;
endmethod


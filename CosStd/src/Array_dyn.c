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
 | $Id: Array_dyn.c,v 1.1 2009/02/10 13:04:50 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Array.h>
#include <cos/Value.h>
#include <cos/Slice.h>
#include <cos/Number.h>
#include <cos/Vector.h>
#include <cos/Functor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/gen/init.h>

#include <stdlib.h>

// -----

useclass(Array);

// ----- accessors

defalias (void, (gput)gappend, DynamicArray, Any);
defalias (void, (gput)gpush  , DynamicArray, Any);
defmethod(void,  gput        , DynamicArray, Any)
  struct DynamicArrayN *dynn = &self->DynamicArrayN;
  struct Array         *arr  = &dynn->Array;

  if (arr->size == self->capacity)
    DynamicArray_enlarge(self, 1.8);
    
  arr->object[arr->size++] = gretain(_2);
endmethod

defalias (OBJ, (gget)glast, DynamicArray);
defalias (OBJ, (gget)gtop , DynamicArray);
defmethod(OBJ,  gget      , DynamicArray)
  struct Array *arr = &self->DynamicArrayN.Array;
  
  retmethod( arr->size ? arr->object[arr->size-1] : 0 );
endmethod

defalias (void, (gdrop)gpop, DynamicArray);
defmethod(void,  gdrop     , DynamicArray)
  struct DynamicArrayN *dynn = &self->DynamicArrayN;
  struct Array         *arr  = &dynn->Array;

  if (arr->size)
    grelease(arr->object[--arr->size]);
endmethod

defmethod(void, gappend, DynamicArray, Array)
  struct DynamicArrayN *dynn = &self->DynamicArrayN;
  struct Array         *arr  = &dynn->Array;

  if (self->capacity - arr->size < self2->size) { // enlarge first
    FLOAT size = arr->size;

    do size *= 1.8;
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


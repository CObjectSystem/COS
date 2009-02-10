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
 | $Id: Array_acc.c,v 1.1 2009/02/10 13:04:50 ldeniau Exp $
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

// ----- setters

defmethod(void, gputAt, Array, Any, Int)
  U32 i = index_abs(self3->value, self->size);
  test_assert( i < self->size, "index out of range" );

  OBJ *obj = self->object+i;
  OBJ  old = *obj;
  *obj = gretain(_2);
  grelease(old);
endmethod

defmethod(void, gputAt, Array, Array, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self->size);

  gputAt(_1,_2,slice);
endmethod

defmethod(void, gputAt, Array, Array, Slice1)
  test_assert( self3->start < self->size && Slice1_last(self3) < self->size,
               "slice out of range" );

  OBJ *obj = self1->object+self3->start;
  OBJ *src = self2->object;
  OBJ *end = self2->object+self2->size;
  I32 step = self3->stride;

  for (; src < end; src++, obj += step) {
    OBJ old = *obj;
    *obj = gretain(*src);
    grelease(old);
  }
endmethod

defmethod(void, gputAt, Array, Array, IntVector)
  test_assert( self2->size >= self3->size,
               "incompatible array sizes" );

  OBJ *obj = self1->object;
  OBJ *src = self2->object;
  U32 size = self1->size;
  I32 *idx = self3->value;
  I32 *end = self3->value+self3->size;

  for(; idx < end; idx++, src++) {
    U32 i = index_abs(*idx, size);
    test_assert( i < size, "index out of range" );
    OBJ old = obj[i];
    obj[i] = gretain(*src);
    grelease(old);
  }
endmethod

// ----- getters

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, ggetAt, Array, Int)
  U32 i = index_abs(self2->value, self->size);
  test_assert( i < self->size, "index out of range" );

  retmethod( self->object[i] );
endmethod

defmethod(OBJ, ggetAt, Array, Range1)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, Slice1)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod


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
 | $Id: Array_acc.c,v 1.4 2009/02/27 20:14:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Slice.h>

#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

useclass(Array);

// ----- setters

defmethod(void, gputAt, Array, Object, Int)
  U32 i = index_abs(self3->value, self->size);
  test_assert( i < self->size, "index out of range" );

  OBJ *obj = self->object + i * self->stride;
  OBJ  old = *obj;
  *obj = gretain(_2);
  grelease(old);
endmethod

defmethod(void, gputAt, Array, Array, Slice)
  test_assert( Slice_first(self3) < self->size
            && Slice_last (self3) < self->size, "slice out of range" );

  I32  obj_s = self1->stride;
  OBJ *obj   = self1->object + obj_s * self3->start;

  I32  src_s = self2->stride;
  OBJ *src   = self2->object;
  OBJ *end   = self2->object + src_s * self2->size;

  I32  slc_s = self3->stride;

  while (src < end) {
    OBJ old = *obj;
    *obj = gretain(*src);
    grelease(old);

    obj += obj_s * slc_s;
    src += src_s;
  }
endmethod

defmethod(void, gputAt, Array, Array, IntVector)
  test_assert( self2->size >= self3->size, "incompatible array sizes" );

  I32  obj_s = self1->stride;
  OBJ *obj   = self1->object;
  U32 size   = self1->size;

  I32  src_s = self2->stride;
  OBJ *src   = self2->object;

  I32  idx_s = self3->stride;
  I32 *idx   = self3->value;
  I32 *end   = self3->value + idx_s * self3->size;

  while (idx < end) {
    U32 i = index_abs(*idx, size);
    test_assert( i < size, "index out of range" );

    OBJ old = obj[i * obj_s];
    obj[i * obj_s] = gretain(*src);
    grelease(old);

    src += src_s;
    idx += idx_s;
  }
endmethod

// ----- getters

defmethod(OBJ, gfirst, Array)
  retmethod( self->size ? self->object[0] : Nil );
endmethod

defmethod(OBJ, glast, Array)
  retmethod( self->size ? self->object[self->size-1] : Nil );
endmethod

defmethod(OBJ, ggetAt, Array, Int)
  U32 i = index_abs(self2->value, self->size);
  retmethod( i < self->size ? self->object[i] : Nil);
endmethod

defmethod(OBJ, ggetAt, Array, Slice)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod


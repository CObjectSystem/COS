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
 | $Id: Array_acc.c,v 1.5 2009/07/24 12:36:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Slice.h>

#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

useclass(Array);

// ----- getters (index, slice, intvector)

defmethod(OBJ, ggetAt, Array, Int)
  U32 i = Range_index(self2->value, self->size);
  test_assert( i < self->size, "index out of range" );
  retmethod( self->object[i*self->stride] );
endmethod

defmethod(OBJ, ggetAt, Array, Slice)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

// ---

defmethod(OBJ, gfirst, Array)
  retmethod( self->size ? self->object[0] : Nil );
endmethod

defmethod(OBJ, glast, Array)
  retmethod( self->size ? self->object[(self->size-1)*self->stride] : Nil );
endmethod

// ----- setters (index, slice, intvector)

defmethod(void, gputAt, Array, Int, Object)
  U32 i = Range_index(self2->value, self->size);
  test_assert( i < self->size, "index out of range" );

  OBJ *dst = self->object + i*self->stride;
  OBJ  old = *dst;
  *dst = gretain(_3);
  grelease(old);
endmethod

defmethod(void, gputAt, Array, Slice, Array)
  U32 first  = Slice_first (self2);
  U32 last   = Slice_last  (self2);
  U32 start  = Slice_first (self2)*self1->stride;
  I32 stride = Slice_stride(self2)*self1->stride;

  test_assert( first < self1->size &&
               last  < self1->size, "slice out of range" );

  test_assert( self1->size < self3->size, "Source array is too small" );

  OBJ *dst   = self1->object + start;
  I32  dst_s = stride;
  OBJ *src   = self3->object;
  I32  src_s = self3->stride;
  OBJ *end   = self3->object + self3->size*self3->stride;

  while (src != end) {
    OBJ old = *dst;
    *dst = gretain(*src);
    grelease(old);
    src += src_s;
    dst += dst_s;
  }
endmethod

defmethod(void, gputAt, Array, IntVector, Array)
  test_assert( self2->size <= self3->size, "incompatible array sizes" );

  OBJ *dst   = self1->object;
  U32  dst_z = self1->size;
  I32  dst_s = self1->stride;
  I32 *idx   = self2->value;
  I32  idx_s = self2->stride;
  OBJ *src   = self3->object;
  I32  src_s = self3->stride;
  OBJ *end   = self3->object + self3->size*self3->stride;

  while (src != end) {
    U32 i = Range_index(*idx, dst_z);
    test_assert( i < dst_z, "index out of range" );
    OBJ old = dst[i*dst_s];
    dst[i*dst_s] = gretain(*src);
    grelease(old);
    src += src_s;
    idx += idx_s;
  }
endmethod


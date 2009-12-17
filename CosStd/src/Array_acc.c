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
 | $Id: Array_acc.c,v 1.13 2009/12/17 14:08:57 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/accessor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>

#include "Array_utl.h"

// -----

useclass(Array);

// ----- first, last

defmethod(OBJ, gfirst, Array)
  retmethod( self->size ? self->object[0] : Nil );
endmethod

defmethod(OBJ, glast, Array)
  retmethod( self->size ? self->object[(self->size-1)*self->stride] : Nil );
endmethod

// ----- getters (index, slice, range, intvector)

defmethod(OBJ, ggetAt, Array, Int)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);

    retmethod( self->object[i*self->stride] );
endmethod

defmethod(OBJ, ggetAt, Array, Slice)
  retmethod( gautoDelete(gnewWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, Range)
  retmethod( gautoDelete(gnewWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoDelete(gnewWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, Array)
  retmethod( gmap(aFun(ggetAt, _1, 0), _2) );
endmethod

// ----- object setters (index, slice, range, intvector)

defmethod(OBJ, gputAt, Array, Int, Object)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
 
    OBJ *dst = self->object + i*self->stride;
    assign(dst, _3);
    
    retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Slice, Object)
  PRE
    test_assert( Slice_first(self2) < self->size &&
                 Slice_last (self2) < self->size, "slice out of range" );
  POST
  BODY
    U32  dst_n = Slice_size  (self2);
    I32  dst_s = Slice_stride(self2)*self->stride;
    OBJ *dst   = Slice_start (self2)*self->stride + self->object;
    OBJ *end   = dst + dst_s*dst_n;

    while (dst != end) {
      assign(dst, _3);
      dst += dst_s;
    }
    
    retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Range, Object)
  struct Range range = Range_normalize(self2,self->size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod( gputAt(_1,(OBJ)&slice,_3) );
endmethod

defmethod(OBJ, gputAt, Array, IntVector, Object)
  PRE POST BODY
    U32  dst_n = self->size;
    I32  dst_s = self->stride;
    OBJ *dst   = self->object;
    U32  idx_n = self2->size;
    I32  idx_s = self2->stride;
    I32 *idx   = self2->value;
    I32 *end   = idx + idx_s*idx_n;

    while (idx != end) {
      U32 i = Range_index(*idx, dst_n);
      test_assert( i < dst_n, "index out of range" );
      assign(dst + i*dst_s, _3);
      idx += idx_s;
    }
    
    retmethod(_1);
endmethod

// ----- array setters (slice, range, intvector)

defmethod(OBJ, gputAt, Array, Slice, Array)
  PRE
    test_assert( Slice_first(self2) < self->size &&
                 Slice_last (self2) < self->size, "slice out of range" );
    test_assert( Slice_size (self2) <= self3->size, "source array is too small" );
  POST    
  BODY
    U32  dst_n = Slice_size  (self2);
    I32  dst_s = Slice_stride(self2)*self->stride;
    OBJ *dst   = Slice_start (self2)*self->stride + self->object;
    I32  src_s = self3->stride;
    OBJ *src   = self3->object;
    OBJ *end   = dst + dst_s*dst_n;

    while (dst != end) {
      assign(dst, *src);
      src += src_s;
      dst += dst_s;
    }
    
    retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, IntVector, Array)
  PRE
    test_assert( self2->size <= self3->size, "source array is too small" );
  POST
  BODY
    U32  dst_n = self->size;
    I32  dst_s = self->stride;
    OBJ *dst   = self->object;
    U32  idx_n = self2->size;
    I32  idx_s = self2->stride;
    I32 *idx   = self2->value;
    I32  src_s = self3->stride;
    OBJ *src   = self3->object;
    I32 *end   = idx + idx_s*idx_n;

    while (idx != end) {
      U32 i = Range_index(*idx, dst_n);
      test_assert( i < dst_n, "index out of range" );
      assign(dst + i*dst_s, *src);
      src += src_s;
      idx += idx_s;
    }
    
    retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, Array)
  PRE
    test_assert( self2->size <= self3->size, "source array is too small" );
  POST
  BODY
    retmethod( gmap2(aFun(gputAt, _1, 0, 0), _2, _3) );
endmethod


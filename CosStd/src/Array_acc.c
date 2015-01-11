/**
 * C Object System
 * COS Array - accessors
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Range.h>

#include <cos/gen/accessor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/collection.h>
#include <cos/gen/sequence.h>
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

defmethod(OBJ, ggetAtIdx, Array, (I32)idx)
  U32 i = Range_index(idx, self->size);
  
  ensure( i < self->size, "index out of range" );

  retmethod( self->object[i*self->stride] );
endmethod

defmethod(OBJ, ggetAt, Array, Int)
  U32 i = Range_index(self2->value, self->size);

  ensure( i < self->size, "index out of range" );

  retmethod( self->object[i*self->stride] );
endmethod

defmethod(OBJ, ggetAt, Array, Slice)
  retmethod( gautoRelease(gnewWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, Range)
  retmethod( gautoRelease(gnewWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoRelease(gnewWith2(Array,_1,_2)) );
endmethod

// move to collection?
defmethod(OBJ, ggetAt, Array, Array)
  retmethod( gmap(aFun(ggetAt, _1, __1), _2) );
endmethod

// ----- object setters (index, slice, range, intvector)

defmethod(OBJ, gputAtIdx, Array, (I32)idx, Object)
  U32 i = Range_index(idx, self->size);
  
  ensure( i < self->size, "index out of range" );

  OBJ *dst = self->object + i*self->stride;
  assign(dst, _2);
    
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Int, Object)
  U32 i = Range_index(self2->value, self->size);
  
  ensure( i < self->size, "index out of range" );

  OBJ *dst = self->object + i*self->stride;
  assign(dst, _3);
    
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Slice, Object)
PRE
  ensure( Slice_first(self2) < self->size &&
               Slice_last (self2) < self->size, "slice out of range" );
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

// move to sequence?
defmethod(OBJ, gputAt, Array, Range, Object)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->size);
  
  retmethod( gputAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, gputAt, Array, IntVector, Object)
  U32  dst_n = self->size;
  I32  dst_s = self->stride;
  OBJ *dst   = self->object;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *idx   = self2->value;
  I32 *end   = idx + idx_s*idx_n;

  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    ensure( i < dst_n, "index out of range" );
    assign(dst + i*dst_s, _3);
    idx += idx_s;
  }
  
  retmethod(_1);
endmethod

// move to collection?
defmethod(OBJ, gputAt, Array, Array, Object)
  gforeach(_2, aFun(gputAt, _1, __1, _3));
  retmethod(_1);
endmethod

// ----- array setters (slice, range, intvector)

defmethod(OBJ, gputAt, Array, Slice, Array)
PRE
  ensure( Slice_first(self2) < self->size &&
               Slice_last (self2) < self->size, "slice out of range" );
  ensure( Slice_size (self2) <= self3->size, "source array is too small" );

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

// move to sequence?
defmethod(OBJ, gputAt, Array, Range, Array)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->size);
  
  retmethod( gputAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, gputAt, Array, IntVector, Array)
PRE
  ensure( self2->size <= self3->size, "source array is too small" );

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
    ensure( i < dst_n, "index out of range" );
    assign(dst + i*dst_s, *src);
    src += src_s;
    idx += idx_s;
  }
  
  retmethod(_1);
endmethod

// move to collection?
defmethod(OBJ, gputAt, Array, Array, Array)
PRE
  ensure( self2->size <= self3->size, "source array is too small" );

BODY
  gforeach2(_2, _3, aFun(gputAt, _1, __1, __2));
  retmethod(_1); 
endmethod


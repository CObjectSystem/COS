/**
 * C Object System
 * COS String - accessors
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
#include <cos/IntVector.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/Slice.h>
#include <cos/String.h>

#include <cos/gen/accessor.h>
#include <cos/gen/collection.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

// -----

useclass(String);

// --- first, last

defmethod(OBJ, gfirst, String)
  retmethod( self->size ? gautoRelease(aChar(self->value[0])) : Nil );
endmethod

defmethod(OBJ,  glast, String)
  retmethod( self->size
           ? gautoRelease(aChar(self->value[self->size-1]))
           : Nil );
endmethod

// ----- getters (index, slice, range, intvector)

defmethod(I32, gchrAt, String, Int)
  U32 i = Range_index(self2->value, self->size);

  ensure( i < self->size, "index out of range" );

  retmethod( self->value[i] );
endmethod

defmethod(OBJ, ggetAtIdx, String, (I32)idx)
  U32 i = Range_index(idx, self->size);
  
  ensure( i < self->size, "index out of range" );

  retmethod( gautoRelease(aChar(self->value[i])) );
endmethod

defmethod(OBJ, ggetAt, String, Int)
  U32 i = Range_index(self2->value, self->size);
  
  ensure( i < self->size, "index out of range" );

  retmethod( gautoRelease(aChar(self->value[i])) );
endmethod

defmethod(OBJ, ggetAt, String, Slice)
  retmethod( gautoRelease(gnewWith2(String,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, String, Range)
  retmethod( gautoRelease(gnewWith2(String,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, String, IntVector)
  retmethod( gautoRelease(gnewWith2(String,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, String, Array)
  retmethod( gmap(aFun(ggetAt, _1, __1), _2) );
endmethod

// ----- object setters (index, slice, range, intvector)

defmethod(OBJ, gputAtIdx, String, (I32)idx, Object)
  U32 i = Range_index(idx, self->size);
  
  ensure( i < self->size, "index out of range" );

  self->value[i] = (U32)gchr(_2);
    
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, String, Int, Object)
  U32 i = Range_index(self2->value, self->size);

  ensure( i < self->size, "index out of range" );

  self->value[i] = (U32)gchr(_3);
    
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, String, Int, Char)
  U32 i = Range_index(self2->value, self->size);

  ensure( i < self->size, "index out of range" );

  self->value[i] = self3->Int.value;
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, String, Slice, Object)
PRE
  ensure( Slice_first(self2) < self->size &&
               Slice_last (self2) < self->size, "slice out of range" );

BODY
  U32 dst_n = Slice_size  (self2);
  I32 dst_s = Slice_stride(self2);
  U8* dst   = Slice_start (self2) + self->value;
  U8* end   = dst + dst_n;
  U8  val   = (U32)gchr(_3);

  while (dst != end) {
    *dst = val;
    dst += dst_s;
  }
  
  retmethod(_1);
endmethod

// move to sequence?
defmethod(OBJ, gputAt, String, Range, Object)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->size);

  retmethod( gputAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, gputAt, String, IntVector, Object)
  U32  dst_n = self->size;
  U8*  dst   = self->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *idx   = self2->value;
  I32 *end   = idx + idx_s*idx_n;
  U8   val   = (U32)gchr(_3);

  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    ensure( i < dst_n, "index out of range" );
    dst[i] = val;
    idx += idx_s;
  }
  
  retmethod(_1);
endmethod

// move to collection?
defmethod(OBJ, gputAt, String, Array, Object)
  gforeach(_2, aFun(gputAt, _1, __1, _3));
  retmethod(_1);
endmethod

// ----- string setters (slice, range, intvector)

defmethod(OBJ, gputAt, String, Slice, String)
PRE
  ensure( Slice_first(self2) < self->size &&
               Slice_last (self2) < self->size, "slice out of range" );
  ensure( Slice_size (self2) <= self3->size, "source string is too small" );

BODY
  U32 dst_n = Slice_size  (self2);
  I32 dst_s = Slice_stride(self2);
  U8* dst   = Slice_start (self2) + self->value;
  U8* src   = self3->value;
  U8* end   = dst + dst_n;

  while (dst != end) {
    *dst = *src++;
    dst += dst_s;
  }
  
  retmethod(_1);
endmethod

// move to sequence?
defmethod(OBJ, gputAt, String, Range, Array)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->size);
  
  retmethod( gputAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, gputAt, String, IntVector, String)
PRE
  ensure( self2->size <= self3->size, "source string is too small" );

BODY
  U32  dst_n = self->size;
  U8*  dst   = self->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *idx   = self2->value;
  U8*  src   = self3->value;
  I32 *end   = idx + idx_s*idx_n;

  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    ensure( i < dst_n, "index out of range" );
    dst[i] = *src++;
    idx += idx_s;
  }
  
  retmethod(_1);
endmethod

// move to collection?
defmethod(OBJ, gputAt, String, Array, Array)
PRE
  ensure( self2->size <= self3->size, "source array is too small" );

BODY
  gforeach2(_2, _3, aFun(gputAt, _1, __1, __2));
  retmethod(_1); 
endmethod


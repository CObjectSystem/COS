/**
 * C Object System
 * COS Vector template - accessors
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

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// --- first, last

defmethod(OBJ, glast, T)
  retmethod( self->size
           ? gautoRelease(VALOBJ(self->value[(self->size-1)*self->stride]))
           : Nil );
endmethod

defmethod(OBJ, gfirst, T)
  retmethod( self->size ? gautoRelease(VALOBJ(self->value[0])) : Nil );
endmethod

// ----- getters (index, slice, range, intvector)

defmethod(OBJ, ggetAtIdx, T, (I32)idx)
  U32 i = Range_index(idx, self->size);
  ensure( i < self->size, "index out of range" );

  retmethod( gautoRelease(VALOBJ(self->value[i*self->stride])) );
endmethod

defmethod(OBJ, ggetAt, T, Int)
  U32 i = Range_index(self2->value, self->size);
  ensure( i < self->size, "index out of range" );

  retmethod( gautoRelease(VALOBJ(self->value[i*self->stride])) );
endmethod

defmethod(OBJ, ggetAt, T, Slice)
  retmethod( gautoRelease(gnewWith2(T,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, T, Range)
  retmethod( gautoRelease(gnewWith2(T,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, T, IntVector)
  retmethod( gautoRelease(gnewWith2(T,_1,_2)) );
endmethod

// ----- object setters (index, slice, range, intvector)

defmethod(OBJ, gputAtIdx, T, (I32)idx, Object)
  U32 i = Range_index(idx, self->size);
  ensure( i < self->size, "index out of range" );

  VAL  val = TOVAL(_2);
  VAL *dst = self->value + i*self->stride;
  
  *dst = val;
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, T, Int, Object)
  U32 i = Range_index(self2->value, self->size);
  ensure( i < self->size, "index out of range" );

  VAL  val = TOVAL(_3);
  VAL *dst = self->value + i*self->stride;
  
  *dst = val;
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, T, Slice, Object)
  PRE
    ensure( Slice_first(self2) < self->size &&
                 Slice_last (self2) < self->size, "slice out of range" );

  BODY
    U32  dst_n = Slice_size  (self2);
    I32  dst_s = Slice_stride(self2)*self->stride;
    VAL *dst   = Slice_start (self2)*self->stride + self->value;
    VAL *end   = dst + dst_s*dst_n;
    VAL  val   = TOVAL(_3);

    while (dst != end) {
      *dst = val;
      dst += dst_s;
    }
    
    retmethod(_1);
endmethod

defmethod(OBJ, gputAt, T, Range, Object)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->size);
  
  retmethod( gputAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, gputAt, T, IntVector, Object)
  U32  dst_n = self->size;
  I32  dst_s = self->stride;
  VAL *dst   = self->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *idx   = self2->value;
  I32 *end   = idx + idx_s*idx_n;
  VAL  val   = TOVAL(_3);

  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    ensure( i < dst_n, "index out of range" );
    dst[i*dst_s] = val;
    idx += idx_s;
  }

  retmethod(_1);
endmethod

// ----- array setters (slice, range, intvector)

defmethod(OBJ, gputAt, T, Slice, T)
  PRE
    ensure( Slice_first(self2) < self->size &&
                 Slice_last (self2) < self->size, "slice out of range" );
    ensure( Slice_size (self2) <= self3->size, "source " TS " is too small" );

  BODY
    U32  dst_n = Slice_size  (self2);
    I32  dst_s = Slice_stride(self2)*self->stride;
    VAL *dst   = Slice_start (self2)*self->stride + self->value;
    I32  src_s = self3->stride;
    VAL *src   = self3->value;
    VAL *end   = dst + dst_s*dst_n;

    while (dst != end) {
      *dst = *src;
      src += src_s;
      dst += dst_s;
    }
    
    retmethod(_1);
endmethod

defmethod(OBJ, gputAt, T, IntVector, T)
  PRE
    ensure( self2->size <= self3->size, "source " TS " is too small" );

  BODY
    U32  dst_n = self->size;
    I32  dst_s = self->stride;
    VAL *dst   = self->value;
    U32  idx_n = self2->size;
    I32  idx_s = self2->stride;
    I32 *idx   = self2->value;
    I32  src_s = self3->stride;
    VAL *src   = self3->value;
    I32 *end   = idx + idx_s*idx_n;

    while (idx != end) {
      U32 i = Range_index(*idx, dst_n);
      ensure( i < dst_n, "index out of range" );
      dst[i*dst_s] = *src;
      src += src_s;
      idx += idx_s;
    }
    
    retmethod(_1);
endmethod

// ----- value getters

#if defined(CHRVECTOR_ONLY)
defalias(I32, (gintAt)gchrAt, T, Int);
#endif

#if defined(CHRVECTOR_ONLY) || defined(SHTVECTOR_ONLY)
defalias(I32, (gintAt)gshtAt, T, Int);
#endif

#if defined(CHRVECTOR_ONLY) || defined(SHTVECTOR_ONLY) || \
    defined(INTVECTOR_ONLY)

defmethod(I32, gintAt, T, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    retmethod( self->value[i*self->stride] );
endmethod

#endif

#if defined(CHRVECTOR_ONLY) || defined(SHTVECTOR_ONLY) || \
    defined(INTVECTOR_ONLY) || defined(LNGVECTOR_ONLY)

defmethod(I64, glngAt, T, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);

    retmethod( self->value[i*self->stride] );
endmethod

#endif

#if defined(CHRVECTOR_ONLY) || defined(SHTVECTOR_ONLY) || \
    defined(INTVECTOR_ONLY) || defined(LNGVECTOR_ONLY) || \
    defined(FLTVECTOR_ONLY)

defmethod(F64, gfltAt, T, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    retmethod( self->value[i*self->stride] );
endmethod

#endif

#if defined(CHRVECTOR_ONLY) || defined(SHTVECTOR_ONLY) || \
    defined(INTVECTOR_ONLY) || defined(LNGVECTOR_ONLY) || \
    defined(FLTVECTOR_ONLY) || defined(CPXVECTOR_ONLY)

defmethod(C64, gcpxAt, T, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    retmethod( self->value[i*self->stride] );
endmethod


#endif

// ----- value setters

#if defined(CHRVECTOR_ONLY) || defined(SHTVECTOR_ONLY) || \
    defined(INTVECTOR_ONLY) || defined(LNGVECTOR_ONLY) || \
    defined(FLTVECTOR_ONLY) || defined(CPXVECTOR_ONLY)

defmethod(OBJ, gputAt, T, Int, Char)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    self->value[i*self->stride] = self3->Int.value;
        
    retmethod(_1);
endmethod

#endif

#if defined(SHTVECTOR_ONLY) || defined(INTVECTOR_ONLY) || \
    defined(LNGVECTOR_ONLY) || defined(FLTVECTOR_ONLY) || \
    defined(CPXVECTOR_ONLY)

defmethod(OBJ, gputAt, T, Int, Short)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    self->value[i*self->stride] = self3->Int.value;
    
    retmethod(_1);
endmethod

#endif

#if defined(INTVECTOR_ONLY) || defined(LNGVECTOR_ONLY) || \
    defined(FLTVECTOR_ONLY) || defined(CPXVECTOR_ONLY)

defmethod(OBJ, gputAt, T, Int, Int)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    self->value[i*self->stride] = self3->value;
    
    retmethod(_1);
endmethod

#endif

#if defined(LNGVECTOR_ONLY) || defined(FLTVECTOR_ONLY) || \
    defined(CPXVECTOR_ONLY)

defmethod(OBJ, gputAt, T, Int, Long)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    self->value[i*self->stride] = self3->value;
    
    retmethod(_1);
endmethod

#endif

#if defined(FLTVECTOR_ONLY) || defined(CPXVECTOR_ONLY)

defmethod(OBJ, gputAt, T, Int, Float)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    self->value[i*self->stride] = self3->value;
    
    retmethod(_1);
endmethod

#endif

#if defined(CPXVECTOR_ONLY)

defmethod(OBJ, gputAt, T, Int, Complex)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    ensure( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->size);
      
    self->value[i*self->stride] = self3->value;
    
    retmethod(_1);
endmethod

#endif


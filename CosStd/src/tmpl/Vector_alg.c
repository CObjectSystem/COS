/**
 * C Object System
 * COS Vector template - algorithms not using functor
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

// ----- equality

defmethod(OBJ, gisEqual, T, T)
  if (self == self2)
    retmethod(True);

  if (self->size != self2->size)
    retmethod(False);

  U32  size   = self->size;
  I32  val_s  = self->stride;
  VAL *val    = self->value;
  I32  val2_s = self2->stride;
  VAL *val2   = self2->value;
  VAL *end    = val + val_s*size;
  
  while (val != end) {
    if (!EQUAL(*val,*val2))
      retmethod(False);
    val  += val_s;
    val2 += val2_s;
  }

  retmethod(True);
endmethod

// ----- in place

defmethod(OBJ, greverse, T)
  if (self->size < 2)
    retmethod(_1);

  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->value;
  VAL *end   = val + val_s*(size-1);

  if (val_s > 0)
    while (val < end) {
      swap(val, end);
      val += val_s;
      end -= val_s;
    }
  else
    while (val > end) {
      swap(val, end);
      val += val_s;
      end -= val_s;
    }

  retmethod(_1);
endmethod

defmethod(OBJ, gpermute, T, IntVector)
  PRE
    ensure( self->size == self2->size, "incompatible " TS " sizes" );

  BODY
    if (self->size < 2)
      retmethod(_1);

    U32  size  = self->size;
    I32  val_s = self->stride;
    VAL *val   = self->value;
    I32  idx_s = self2->stride;
    I32 *idx   = self2->value;

    CARRAY_CREATE(VAL,buf,size); // VAL buf[size];
    CARRAY_CREATE(U8 ,flg,size); // U8  flg[size];

    memset(flg,1,size);

    VAL *cur, *end = buf + size;
    U32  i = 0;

    // permute
    for (cur = buf; cur != end; cur++) {
      i = Range_index(*idx, size);
      if ( !(i < size && flg[i]) ) break;
      *cur = val[i*val_s], flg[i] = 0;
       idx += idx_s;
    }

    if (cur == end) {
      // copy back
      for (cur = buf; cur != end; cur++)
        *val = *cur, val += val_s;

      CARRAY_DESTROY(buf);
      CARRAY_DESTROY(flg);
    } else {
      // rollback (error)
      BOOL iiir = i < size; // last index-is-in-range flag

      while (cur != buf) {
        idx -= idx_s;
        i = Range_index(*idx, size);
        val[i*val_s] = *--cur;
      }

      CARRAY_DESTROY(buf);
      CARRAY_DESTROY(flg);
      ensure( iiir, "index out of range" );
      ensure(    0, "invalid cyclic permutation" );
    }

    retmethod(_1);
endmethod

// ----- repeat

defmethod(OBJ, grepeat, TE, Int)
  retmethod(gautoRelease( gnewWith2(T,_2,_1) ));
endmethod

// ----- zip, zip3, zip4

defmethod(OBJ, gzip, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
  struct T* vec = T_alloc(2*size);

  I32  src_s  = self->stride;
  VAL *src    = self->value; 
  I32  src2_s = self2->stride;
  VAL *src2   = self2->value;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->value;
  VAL *end    = dst + 2*size;

  while (dst != end) {
    *dst++ = *src , ++*dst_n, src  += src_s;
    *dst++ = *src2, ++*dst_n, src2 += src2_s;
  }

  retmethod(gautoRelease( (OBJ)vec ));
endmethod

defmethod(OBJ, gzip3, T, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
  struct T* vec = T_alloc(3*size);

  I32  src_s  = self->stride;
  VAL *src    = self->value; 
  I32  src2_s = self2->stride;
  VAL *src2   = self2->value;
  I32  src3_s = self3->stride;
  VAL *src3   = self3->value;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->value;
  VAL *end    = dst + 3*size;

  while (dst != end) {
    *dst++ = *src , ++*dst_n, src  += src_s;
    *dst++ = *src2, ++*dst_n, src2 += src2_s;
    *dst++ = *src3, ++*dst_n, src3 += src3_s;
  }

  retmethod(gautoRelease( (OBJ)vec ));
endmethod

defmethod(OBJ, gzip4, T, T, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
      size = self4->size < size ? self4->size : size;
  struct T* vec = T_alloc(4*size);

  I32  src_s  = self->stride;
  VAL *src    = self->value; 
  I32  src2_s = self2->stride;
  VAL *src2   = self2->value;
  I32  src3_s = self3->stride;
  VAL *src3   = self3->value;
  I32  src4_s = self4->stride;
  VAL *src4   = self4->value;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->value;
  VAL *end    = dst + 4*size;

  while (dst != end) {
    *dst++ = *src , ++*dst_n, src  += src_s;
    *dst++ = *src2, ++*dst_n, src2 += src2_s;
    *dst++ = *src3, ++*dst_n, src3 += src3_s;
    *dst++ = *src4, ++*dst_n, src4 += src4_s;
  }

  retmethod(gautoRelease( (OBJ)vec ));
endmethod

/*
defmethod(OBJ, gzip5, T, T, T, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  struct T* vec = T_alloc(5*size);
 
  I32  src_s  = self->stride;
  VAL *src    = self->value; 
  I32  src2_s = self2->stride;
  VAL *src2   = self2->value;
  I32  src3_s = self3->stride;
  VAL *src3   = self3->value;
  I32  src4_s = self4->stride;
  VAL *src4   = self4->value;
  I32  src5_s = self5->stride;
  VAL *src5   = self5->value;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->value;
  VAL *end    = dst + 5*size;

  while (dst != end) {
    *dst++ = *src , ++*dst_n, src  += src_s;
    *dst++ = *src2, ++*dst_n, src2 += src2_s;
    *dst++ = *src3, ++*dst_n, src3 += src3_s;
    *dst++ = *src4, ++*dst_n, src4 += src4_s;
    *dst++ = *src5, ++*dst_n, src5 += src5_s;
  }

  retmethod(gautoRelease( (OBJ)vec ));
endmethod
*/

// ----- concat, concat3, concat4

defmethod(OBJ, gconcat, T, T)
  U32 size = self->size + self2->size;
  struct T *vec = T_alloc(size);

  VAL *dst = vec->value;

  dst = copy(dst,&vec->size,self ->value,self ->stride,self ->size);
        copy(dst,&vec->size,self2->value,self2->stride,self2->size);

  retmethod(gautoRelease( (OBJ)vec ));
endmethod

defmethod(OBJ, gconcat3, T, T, T)
  U32 size = self->size + self2->size + self3->size;
  struct T *vec = T_alloc(size);

  VAL *dst = vec->value;

  dst = copy(dst,&vec->size,self ->value,self ->stride,self ->size);
  dst = copy(dst,&vec->size,self2->value,self2->stride,self2->size);
        copy(dst,&vec->size,self3->value,self3->stride,self3->size);

  retmethod(gautoRelease( (OBJ)vec ));
endmethod

defmethod(OBJ, gconcat4, T, T, T, T)
  U32 size = self->size + self2->size + self3->size + self4->size;
  struct T *vec = T_alloc(size);

  VAL *dst = vec->value;

  dst = copy(dst,&vec->size,self ->value,self ->stride,self ->size);
  dst = copy(dst,&vec->size,self2->value,self2->stride,self2->size);
  dst = copy(dst,&vec->size,self3->value,self3->stride,self3->size);
        copy(dst,&vec->size,self4->value,self4->stride,self4->size);

  retmethod(gautoRelease( (OBJ)vec ));
endmethod

/*
defmethod(OBJ, gconcat5, T, T, T, T, T)
  U32 size = self->size + self2->size + self3->size + self4->size + self5->size;
  struct T *vec = T_alloc(size);

  VAL *dst = vec->value;

  dst = copy(dst,&vec->size,self ->value,self ->stride,self ->size);
  dst = copy(dst,&vec->size,self2->value,self2->stride,self2->size);
  dst = copy(dst,&vec->size,self3->value,self3->stride,self3->size);
  dst = copy(dst,&vec->size,self4->value,self4->stride,self4->size);
        copy(dst,&vec->size,self5->value,self5->stride,self5->size);

  retmethod(gautoRelease( (OBJ)vec ));
endmethod
*/

// ----- search (object)

static VAL*
findVal(VAL *val, U32 val_n, I32 val_s, VAL _2)
{
  if (!val_n) return 0;

  VAL *end = val + val_s*val_n;

  while (val != end) {
    if (EQUAL(*val, _2))
      return val;
    val += val_s;
  }

  return 0;  
}

defmethod(OBJ, gfind, T, Object)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->value;

  VAL *p = findVal(val,val_n,val_s,TOVAL(_2));

  retmethod( p ? gautoRelease(VALOBJ(*p)) : Nil );
endmethod

defmethod(OBJ, gifind, T, Object)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->value;

  VAL *p = findVal(val,val_n,val_s,TOVAL(_2));

  retmethod(p ? gautoRelease( aInt((p-val)/val_s) ) : Nil);
endmethod

// ----- search (array)

// -- KnuthMorrisPratt (linear)

static VAL*
KnuthMorrisPratt(VAL *val, U32 val_n, I32 val_s, VAL *pat, I32 pat_n, I32 pat_s)
{
  CARRAY_CREATE(I32,kmpNext,pat_n);

  { // preprocessing
    I32 i = 0, j = kmpNext[0] = -1;

    while (i < pat_n) {
      while (j > -1 && !EQUAL(pat[i*pat_s],pat[j*pat_s]))
        j = kmpNext[j];
      i++;
      j++;
      if (EQUAL(pat[i*pat_s],pat[j*pat_s]))
        kmpNext[i] = kmpNext[j];
      else
        kmpNext[i] = j;
    }
  }
 
  { // searching
    I32 i = 0;
    U32 j = 0;

    while (j < val_n) {
      while (i > -1 && !EQUAL(pat[i*pat_s],val[j*val_s]))
        i = kmpNext[i];
      i++;
      j++;
      if (i >= pat_n) { // found
        CARRAY_DESTROY(kmpNext);
        return val + (j - i)*val_s;
      }
    }
  }

  CARRAY_DESTROY(kmpNext);
  return 0; // not found
}

// -- find front-end

static VAL*
findSub(VAL *val, U32 val_n, I32 val_s, VAL *pat, U32 pat_n, I32 pat_s)
{
  // empty pattern
  if (!pat_n) return val;

  // subvector is too short
  if (val_n < pat_n) return 0;

  // find first
  VAL *p = findVal(val, val_n-pat_n+1, val_s, *pat);
  if (!p) return 0;

  // single object pattern
  if (pat_n == 1) return p;

  // linear search
  return KnuthMorrisPratt(p, val_n-(p-val)/val_s, val_s, pat, pat_n, pat_s);
}

// -- find methods

defmethod(U32, gindexOf, T, T)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->value;

  VAL *p = findSub(val,val_n,val_s,self2->value,self2->size,self2->stride);
  retmethod(p ? (p-val)/val_s : -1);
endmethod

defmethod(OBJ, gfind, T, T)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->value;

  VAL *p = findSub(val,val_n,val_s,self2->value,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ avw = aTView(self, atSlice((p-val)/val_s,self2->size,val_s) );
  retmethod(gautoRelease( avw ));
endmethod

defmethod(OBJ, gifind, T, T)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->value;

  VAL *p = findSub(val,val_n,val_s,self2->value,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ slc = aSlice((p-val)/val_s,self2->size,val_s);
  retmethod(gautoRelease( slc ));  
endmethod


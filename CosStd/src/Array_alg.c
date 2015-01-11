/**
 * C Object System
 * COS Array - algorithms not using functor
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

#include <cos/gen/algorithm.h>
#include <cos/gen/array.h>
#include <cos/gen/collection.h>
#include <cos/gen/sequence.h>
#include <cos/gen/range.h>
#include <cos/gen/relop.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/carray.h>

#include "Array_utl.h"

#include <string.h>

useclass(Array, View, Slice);

// ----- equality

defmethod(OBJ, gisEqual, Array, Array)
  if (self == self2)
    retmethod(True);

  if (self->size != self2->size)
    retmethod(False);

  U32  val_n  = self->size;
  I32  val_s  = self->stride;
  OBJ *val    = self->object;
  I32  val2_s = self2->stride;
  OBJ *val2   = self2->object;
  OBJ *end    = val + val_s*val_n;
  
  while (val != end) {
    if (gisEqual(*val,*val2) != True)
      retmethod(False);
      
    val  += val_s;
    val2 += val2_s;
  }

  retmethod(True);
endmethod

// ----- comparison

defmethod(OBJ, gcompare, Array, Array)
  useclass(Equal);
  
  if (self == self2)
    retmethod(Equal);

  U32  val_n  = self->size;
  I32  val_s  = self->stride;
  OBJ *val    = self->object;
  I32  val2_s = self2->stride;
  OBJ *val2   = self2->object;
  OBJ *end    = val + val_s*val_n;
  OBJ  res;

  while (val != end) {
    if ((res = gcompare(*val,*val2)) != Equal)
      retmethod(res);
      
    val  += val_s;
    val2 += val2_s;
  }

  retmethod(Equal);
endmethod

// ----- in place

static cos_inline void
swap(OBJ *val1, OBJ *val2)
{
  OBJ tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

defmethod(OBJ, greverse, Array)
  if (self->size < 2)
    retmethod(_1);

  U32  val_n = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;
  OBJ *end   = val + val_s*(val_n-1);

  if (val_s > 0)
    while (val < end) {
      swap(val,end);
      val += val_s;
      end -= val_s;
    }
  else
    while (val > end) {
      swap(val,end);
      val += val_s;
      end -= val_s;
    }
    
  retmethod(_1);
endmethod

defmethod(OBJ, gpermute, Array, IntVector)
  PRE
    ensure( self->size == self2->size, "incompatible array sizes" );

  BODY
    if (self->size < 2)
      retmethod(_1);

    U32  size  = self->size;
    I32  val_s = self->stride;
    OBJ *val   = self->object;
    I32  idx_s = self2->stride;
    I32 *idx   = self2->value;

    CARRAY_CREATE(OBJ,buf,size); // OBJ buf[size];
    CARRAY_CREATE(U8 ,flg,size); // U8  flg[size];

    memset(flg,1,size);

    OBJ *cur, *end = buf + size;
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

defmethod(OBJ, grepeat, Object, Int)
  retmethod(gautoRelease( gnewWith2(Array,_2,_1) ));
endmethod

// ----- zip, zip3, zip4, zipn

defmethod(OBJ, gzip, Array, Array)
  U32 size = self->size < self2->size ? self->size : self2->size;
  struct Array* arr = Array_alloc(2*size);
  OBJ _arr = gautoRelease( (OBJ)arr );

  I32  src_s  = self->stride;
  OBJ *src    = self->object; 
  I32  src2_s = self2->stride;
  OBJ *src2   = self2->object;
  U32 *dst_n  = &arr->size;
  OBJ *dst    = arr->object;
  OBJ *end    = dst + 2*size;

  while (dst != end) {
    *dst++ = gretain(*src ), ++*dst_n, src  += src_s;
    *dst++ = gretain(*src2), ++*dst_n, src2 += src2_s;
  }

  retmethod(_arr);
endmethod

defmethod(OBJ, gzip3, Array, Array, Array)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
  struct Array* arr = Array_alloc(3*size);
  OBJ _arr = gautoRelease( (OBJ)arr );

  I32  src_s  = self->stride;
  OBJ *src    = self->object; 
  I32  src2_s = self2->stride;
  OBJ *src2   = self2->object;
  I32  src3_s = self3->stride;
  OBJ *src3   = self3->object;
  U32 *dst_n  = &arr->size;
  OBJ *dst    = arr->object;
  OBJ *end    = dst + 3*size;

  while (dst != end) {
    *dst++ = gretain(*src ), ++*dst_n, src  += src_s;
    *dst++ = gretain(*src2), ++*dst_n, src2 += src2_s;
    *dst++ = gretain(*src3), ++*dst_n, src3 += src3_s;
  }

  retmethod(_arr);
endmethod

defmethod(OBJ, gzip4, Array, Array, Array, Array)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
      size = self4->size < size ? self4->size : size;
  struct Array* arr = Array_alloc(4*size);
  OBJ _arr = gautoRelease( (OBJ)arr );

  I32  src_s  = self->stride;
  OBJ *src    = self->object; 
  I32  src2_s = self2->stride;
  OBJ *src2   = self2->object;
  I32  src3_s = self3->stride;
  OBJ *src3   = self3->object;
  I32  src4_s = self4->stride;
  OBJ *src4   = self4->object;
  U32 *dst_n  = &arr->size;
  OBJ *dst    = arr->object;
  OBJ *end    = dst + 4*size;

  while (dst != end) {
    *dst++ = gretain(*src ), ++*dst_n, src  += src_s;
    *dst++ = gretain(*src2), ++*dst_n, src2 += src2_s;
    *dst++ = gretain(*src3), ++*dst_n, src3 += src3_s;
    *dst++ = gretain(*src4), ++*dst_n, src4 += src4_s;
  }

  retmethod(_arr);
endmethod

/*
defmethod(OBJ, gzip5, Array, Array, Array, Array, Array)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  struct Array* arr = Array_alloc(5*size);
  OBJ _arr = gautoRelease( (OBJ)arr );

  I32  src_s  = self->stride;
  OBJ *src    = self->object; 
  I32  src2_s = self2->stride;
  OBJ *src2   = self2->object;
  I32  src3_s = self3->stride;
  OBJ *src3   = self3->object;
  I32  src4_s = self4->stride;
  OBJ *src4   = self4->object;
  I32  src5_s = self5->stride;
  OBJ *src5   = self5->object;
  U32 *dst_n  = &arr->size;
  OBJ *dst    = arr->object;
  OBJ *end    = dst + 5*size;

  while (dst != end) {
    *dst++ = gretain(*src ), ++*dst_n, src  += src_s;
    *dst++ = gretain(*src2), ++*dst_n, src2 += src2_s;
    *dst++ = gretain(*src3), ++*dst_n, src3 += src3_s;
    *dst++ = gretain(*src4), ++*dst_n, src4 += src4_s;
    *dst++ = gretain(*src5), ++*dst_n, src5 += src5_s;
  }

  retmethod(_arr);
endmethod
*/

defmethod(OBJ, gzipn, Array)
  U32  src_n = self->size;
  I32  src_s = self->stride;
  OBJ *src   = self->object;
  OBJ *end   = src + src_s*src_n;
  U32  max_size = 0;

  // compute max of sizes
  while (src != end) {
    ensure( dyncast(Array, *src),
                 "invalid array element (should be an Array)" );
    U32 size = gsize(*src);
    if (size < max_size) max_size = size;
    src += src_s;
  }

  // intersperse arrays
  struct Array* arr = Array_alloc(max_size * src_n);
  OBJ _arr = gautoRelease( (OBJ)arr );
  OBJ *dst = arr->object;
       src = self->object;
       
  while (src != end) {
    struct Array* arr = dbgcast(Array, *src);
    arr_copy(dst, src_n, &arr->size, arr->object, arr->stride, arr->size);
    src += src_s;
    dst += 1;
  }

  retmethod(_arr);
endmethod

// ----- concat, concat3, concat4, concatn

defmethod(OBJ, gconcat, Array, Array)
  U32 size = self->size + self2->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = gautoRelease( (OBJ)arr );
  OBJ *dst = arr->object;

  dst = arr_copy(dst,1,&arr->size,self ->object,self ->stride,self ->size);
        arr_copy(dst,1,&arr->size,self2->object,self2->stride,self2->size);

  retmethod(_arr);
endmethod

defmethod(OBJ, gconcat3, Array, Array, Array)
  U32 size = self->size + self2->size + self3->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = gautoRelease( (OBJ)arr );
  OBJ *dst = arr->object;

  dst = arr_copy(dst,1,&arr->size,self ->object,self ->stride,self ->size);
  dst = arr_copy(dst,1,&arr->size,self2->object,self2->stride,self2->size);
        arr_copy(dst,1,&arr->size,self3->object,self3->stride,self3->size);

  retmethod(_arr);
endmethod

defmethod(OBJ, gconcat4, Array, Array, Array, Array)
  U32 size = self->size + self2->size + self3->size + self4->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = gautoRelease( (OBJ)arr );
  OBJ *dst = arr->object;

  dst = arr_copy(dst,1,&arr->size,self ->object,self ->stride,self ->size);
  dst = arr_copy(dst,1,&arr->size,self2->object,self2->stride,self2->size);
  dst = arr_copy(dst,1,&arr->size,self3->object,self3->stride,self3->size);
        arr_copy(dst,1,&arr->size,self4->object,self4->stride,self4->size);

  retmethod(_arr);
endmethod

/*
defmethod(OBJ, gconcat5, Array, Array, Array, Array, Array)
  U32 size = self->size + self2->size + self3->size + self4->size + self5->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = gautoRelease( (OBJ)arr );

  OBJ *dst = arr->object;

  dst = arr_copy(dst,1,&arr->size,self ->object,self ->stride,self ->size);
  dst = arr_copy(dst,1,&arr->size,self2->object,self2->stride,self2->size);
  dst = arr_copy(dst,1,&arr->size,self3->object,self3->stride,self3->size);
  dst = arr_copy(dst,1,&arr->size,self4->object,self4->stride,self4->size);
        arr_copy(dst,1,&arr->size,self5->object,self5->stride,self5->size);

  retmethod(_arr);
endmethod
*/

// move to sequence?
defmethod(OBJ, gconcatn, Array)
  U32  size  = self->size;
  I32  src_s = self->stride;
  OBJ *src   = self->object;
  OBJ *end   = src + size*src_s;
  U32  ssize = 0;
  BOOL all_array = YES;

  // compute sum of sizes
  while (src != end) {
    if (!dyncast(Array, *src))
      all_array = NO;
    ssize += gsize(*src);
    src += src_s;
  }

  if (ssize == 0)
    retmethod(Nil);

  if (all_array) {
    // concatenate arrays
    struct Array* arr = Array_alloc(ssize);
    OBJ _arr = gautoRelease( (OBJ)arr );
    OBJ *dst = arr->object;
         src = self->object;
    
    while(src != end) {
      struct Array* self2 = dbgcast(Array, *src);
      dst = arr_copy(dst,1,&arr->size,self2->object,self2->stride,self2->size);
      src += src_s;
    }

    retmethod(_arr);
  }
  else {
    OBJ cls = gclass(*self->object);
    OBJ res = gautoRelease(gnewWith(cls, aInt(ssize)));

    src = self->object;
    while(src != end) {
      gappend(res, *src);
      src += src_s;
    }

    retmethod(res);
  }
endmethod

// ----- search (object)

static OBJ*
findVal(OBJ *val, U32 val_n, I32 val_s, OBJ _2)
{
  if (!val_n) return 0;

  OBJ *end = val + val_s*val_n;

  while (val != end) {
    if (gisEqual(_2, *val) == True)
      return val;
    val += val_s;
  }

  return 0;  
}

defmethod(OBJ, gfind, Array, Object)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;

  OBJ *p = findVal(val, val_n, val_s, _2);

  retmethod( p ? *p : Nil );  
endmethod

defmethod(OBJ, gifind, Array, Object)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;

  OBJ *p = findVal(val, val_n, val_s, _2);

  retmethod(p ? gautoRelease( aInt((p-val)/val_s) ) : Nil);
endmethod

// ----- search (array)

// -- KnuthMorrisPratt (linear)

static OBJ*
KnuthMorrisPratt(OBJ *val, U32 val_n, I32 val_s, OBJ *pat, I32 pat_n, I32 pat_s)
{
  CARRAY_CREATE(I32,kmpNext,pat_n);

  { // preprocessing
    I32 i = 0, j = kmpNext[0] = -1;

    while (i < pat_n) {
      while (j > -1 && gisEqual(pat[i*pat_s],pat[j*pat_s]) == False)
        j = kmpNext[j];
      i++;
      j++;
      if (gisEqual(pat[i*pat_s],pat[j*pat_s]) == True)
        kmpNext[i] = kmpNext[j];
      else
        kmpNext[i] = j;
    }
  }
 
  { // searching
    I32 i = 0;
    U32 j = 0;

    while (j < val_n) {
      while (i > -1 && gisEqual(pat[i*pat_s],val[j*val_s]) == False)
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

static OBJ*
findSub(OBJ *val, U32 val_n, I32 val_s, OBJ *pat, U32 pat_n, I32 pat_s)
{
  // empty pattern
  if (!pat_n) return val;

  // subarray is too short
  if (val_n < pat_n) return 0;

  // find first
  OBJ *p = findVal(val, val_n-pat_n+1, val_s, *pat);
  if (!p) return 0;

  // single object pattern
  if (pat_n == 1) return p;

  // linear search
  return KnuthMorrisPratt(p, val_n-(p-val)/val_s, val_s, pat, pat_n, pat_s);
}

// -- find methods

defmethod(U32, gindexOf, Array, Array)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;

  OBJ *p = findSub(val,val_n,val_s,self2->object,self2->size,self2->stride);
  retmethod(p ? (p-val)/val_s : -1);
endmethod

defmethod(OBJ, gfind, Array, Array)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;

  OBJ *p = findSub(val,val_n,val_s,self2->object,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ avw = gnewWith2(View, _1, aSlice((p-val)/val_s, self2->size, val_s));
  retmethod(gautoRelease( avw ));
endmethod

defmethod(OBJ, gifind, Array, Array)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;

  OBJ *p = findSub(val,val_n,val_s,self2->object,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ slc = gnewSlc(Slice, (p-val)/val_s, self2->size, val_s);
  retmethod(gautoRelease( slc ));  
endmethod


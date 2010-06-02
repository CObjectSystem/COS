/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Dynamic array
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
 | $Id: Array_dyn.c,v 1.23 2010/06/02 22:47:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Range.h>

#include <cos/gen/collection.h>
#include <cos/gen/sequence.h>
#include <cos/gen/object.h>

#include <cos/carray.h>

#include "Array_utl.h"

#include <string.h>

// -----

makclass(ArrayFix,Array);
makclass(ArrayDyn,ArrayFix);

// -----

useclass(ArrayDyn, ExBadAlloc, ExOverflow);

// -----

#ifndef ARRAY_GROWTH_RATE
#define ARRAY_GROWTH_RATE SEQUENCE_GROWTH_RATE
#endif

#ifndef ARRAY_MINSIZE
#define ARRAY_MINSIZE 1024
#endif

STATIC_ASSERT(array_growth_rate_is_too_small , ARRAY_GROWTH_RATE >= 1.5);
STATIC_ASSERT(array_minimun_size_is_too_small, ARRAY_MINSIZE     >= 256);

// ----- getter

defmethod(U32, gcapacity, ArrayDyn)
  retmethod(self->capacity);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayFix)
  next_method(self);

  if (self->_object) { // take care of protection cases
    free(self->_object);
    self->Array.object = 0;
    self->_object      = 0;
  }

  retmethod(_1);
endmethod

// ----- constructors

defalias (OBJ, (ginit)gnew, pmArray);
defmethod(OBJ,  ginit     , pmArray) // Dynamic array
  retmethod( ginit(galloc(ArrayDyn)) );
endmethod

defmethod(OBJ, ginit, ArrayDyn)
  self->ArrayFix.Array.size   = 0;
  self->ArrayFix.Array.stride = 1;
  self->ArrayFix.Array.object = 0;
  self->ArrayFix._object      = 0;
  self->capacity              = 0;

  retmethod(_1);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Int);
defmethod(OBJ,  ginitWith         , pmArray, Int) // Dynamic array with capacity
  retmethod(ginitWith(galloc(ArrayDyn),_2));
endmethod

defmethod(OBJ, ginitWith, ArrayDyn, Int)
  PRT(_1);
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;
  U32          capacity = self2->value;
  size_t           size = capacity * sizeof *arr->object;

  if (size/sizeof *arr->object < capacity)
    THROW(gnewWithStr(ExOverflow, "capacity is too large"));

  arrf->_object = malloc(size);

  if (!arrf->_object && size)
    THROW(ExBadAlloc);

  arr->size      = 0;
  arr->stride    = 1;
  arr->object    = arrf->_object;
  self->capacity = capacity;

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->capacity >= self->ArrayFix.Array.size,
               "dynamic array has capacity < size", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod

// ----- memory management

static U32
resize(U32 capacity, U32 extra)
{
  U32 size = capacity + extra;
  U32 last = U32_MAX/ARRAY_GROWTH_RATE;

  // overflow
  if (capacity > U32_MAX-extra)
    THROW(gnewWithStr(ExOverflow, "extra size is too large"));

  // starting point
  if (capacity < ARRAY_MINSIZE)
    capacity = ARRAY_MINSIZE;
  
  // growth rate
  while (capacity < size && capacity < last)
    capacity *= ARRAY_GROWTH_RATE;

  // round last growth
  if (capacity < size)
    capacity = size;

  return capacity;
}

defmethod(OBJ, genlarge, ArrayDyn, Int) // negative size means enlarge front
  if (self2->value) {
    struct ArrayFix* arrf = &self->ArrayFix;
    struct Array*    arr  = &arrf->Array;
    
    ptrdiff_t offset = arr->object - arrf->_object;
    BOOL       front = self2->value < 0;
    U32        extra = front ? -self2->value : self2->value;
    U32     capacity = resize(self->capacity, extra);
    size_t      size = capacity * sizeof *arrf->_object;
    
    if (size/sizeof *arrf->_object < capacity)
      THROW(gnewWithStr(ExOverflow, "extra size is too large"));
    
    OBJ *_object = realloc(arrf->_object, size);
    
    if (!_object && size)
      THROW(ExBadAlloc);

    arr->object = front ? // move data to book the new space front
        memmove(_object + offset + (capacity - self->capacity),
                _object + offset, arr->size * sizeof *_object) :
                _object + offset; // restore offset

    arrf->_object  = _object;
    self->capacity = capacity;
  }  
  retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, ArrayDyn)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;
  size_t           size = arr->size * sizeof *arr->object;

  // move data to base
  if (arr->object != arrf->_object)
    arr->object = memmove(arrf->_object, arr->object, size);

  // shrink storage
  if (arr->size != self->capacity) {
    OBJ *_object = realloc(arrf->_object, size);

    if (!_object && size)
      THROW(ExBadAlloc);

    arr -> object  = _object;
    arrf->_object  = _object;
    self->capacity = arr->size;
  }

  BOOL ch_cls = cos_object_changeClass(_1, classref(ArrayFix));
  test_assert( ch_cls, "unable to change from dynamic to fixed size array" );
  retmethod(_1);
endmethod

// ----- clear (size -> 0)

defmethod(OBJ, gclear, ArrayDyn)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  U32 *val_n = &arr->size;
  OBJ *val   = arr->object;
  OBJ *end   = val + *val_n;

  while (val != end)
    grelease(*--end), --*val_n;
  
  retmethod(_1);
endmethod

// ----- popFront, popBack, drop

defmethod(OBJ, gpopFront, ArrayDyn)
  struct Array *arr = &self->ArrayFix.Array;

  if (arr->size--)
    grelease(*arr->object++);
      
  retmethod(_1);
endmethod

defmethod(OBJ, gpopBack, ArrayDyn)
  struct Array *arr = &self->ArrayFix.Array;

  if (arr->size--)
    grelease(arr->object[arr->size]);
      
  retmethod(_1);
endmethod

defmethod(OBJ, gdrop, ArrayDyn, Int)
  struct Array *arr = &self->ArrayFix.Array;
  BOOL         back = self2->value < 0;
  U32           cnt = back ? -self2->value : self2->value+1;

  if (cnt > arr->size)
    cnt = arr->size;

  if (back)
    while (cnt--)
      grelease(arr->object[--arr->size]);
  else
    while (cnt--)
      arr->size--, grelease(*arr->object++);
      
  retmethod(_1);
endmethod

// ----- prepend, append object

defmethod(OBJ, gprepend, ArrayDyn, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arr->object == arrf->_object)
    genlarge(_1, aInt(-1));

  arr->object[-1] = gretain(_2), arr->object--, arr->size++;

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, ArrayDyn, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arr->object + arr->size == arrf->_object + self->capacity)
    genlarge(_1, aInt(1));
    
  arr->object[arr->size++] = gretain(_2);
  
  retmethod(_1);
endmethod

// ----- prepend, append array

defmethod(OBJ, gprepend, ArrayDyn, Array)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arrf->_object > arrf->_object + self2->size)
    THROW(gnewWithStr(ExOverflow, "size is too large"));

  if (arr->object < arrf->_object + self2->size)
    genlarge(_1, aInt(-self2->size));

  OBJ *src   = self2->object;
  U32  src_n = self2->size;
  I32  src_s = self2->stride;
  OBJ *end   = src + src_n*src_s;

  while (src != end) {
    arr->object[-1] = gretain(*src), arr->object--, arr->size++;
    src += src_s;
  }
  
  retmethod(_1);
endmethod

defmethod(OBJ, gappend, ArrayDyn, Array)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  if (arrf->_object > arrf->_object + self2->size)
    THROW(gnewWithStr(ExOverflow, "size is too large"));

  if (arr->object + arr->size + self2->size > arrf->_object + self->capacity)
    genlarge(_1, aInt(self2->size));

  U32  src_n = self2->size;
  I32  src_s = self2->stride;
  OBJ *src   = self2->object;
  OBJ *end   = src + src_s*src_n;

  while (src != end) {
    arr->object[arr->size++] = gretain(*src), arr->size++;
    src += src_s;
  }

  retmethod(_1);
endmethod

/* TODO: unchecked code (certainly buggy)
*/

// --- insertAt object (index, slice, range, intvector)

static BOOL
prepareRandomInsert(struct Array *arr, struct IntVector *self2)
{
  U32  dst_n = arr->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  U32  fst   = dst_n;
  U32  lst   = 0;

  TMPARRAY_CREATE(U8,flg,dst_n);
  memset(flg,0,dst_n);

  // mark insertion slots
  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    if (i >= dst_n) break;
    if (i < fst) fst = i;
    if (i > lst) lst = i;
    flg[i] = 1;
    idx += idx_s;
  }
  
  // range error
  if (idx != end) {
    TMPARRAY_DESTROY(flg);
    return NO;
  }

  // shift post data to the end
  OBJ *dst = lst + arr->object;
  memmove(dst+idx_n, dst, (arr->size - (dst-arr->object))*sizeof *dst);
  arr->size += idx_n;

  // prepare insertion slots (start from the end)
  {
    OBJ *end = fst + arr->object;
    U8  *slt = lst + flg;
    U32  sht = idx_n;

    for (; dst != end; --dst, --slt)
      if (*slt)
        sht--;
      else
        dst[sht] = *dst;
  }
  
  TMPARRAY_DESTROY(flg);
  return YES;
}

defmethod(OBJ, ginsertAt, ArrayDyn, Int, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  U32 i = Range_index(self2->value, arr->size);
  test_assert( i <= arr->size, "index out of range" );

  if (arr->size == self->capacity)
    genlarge(_1, aInt(1));

  OBJ *dst = arr->object+i;

  memmove(dst+1, dst, (arr->size-i) * sizeof *dst);
  arr->size++, *dst = Nil, *dst = gretain(_3);

  retmethod(_1);
endmethod

defmethod(OBJ, ginsertAt, ArrayDyn, Slice, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  test_assert( Slice_first(self2) <= arr->size &&
               Slice_last (self2) <= arr->size, "slice out of range" );
 
  OBJ *dst;
  I32  dst_s;
  U32  dst_n = Slice_size(self2);

  if (arr->size + dst_n > self->capacity)
    genlarge(_1, aInt(dst_n));

  // always start from the end (reverse fill with positive stride)
  if (Slice_stride(self2) > 0) {
    dst   =  Slice_last  (self2) + arr->object;
    dst_s =  Slice_stride(self2);
  } else {
    dst   =  Slice_first (self2) + arr->object;
    dst_s = -Slice_stride(self2);
  }

  // shift post data to the end
  memmove(dst+dst_n, dst, (arr->size - (dst-arr->object)) * sizeof *dst);
  arr->size += dst_n;

  OBJ *end = dst - dst_s*dst_n;
  OBJ *nxt = dst - dst_s;
  U32  sht = dst_n;

  // double level fill-move
  while (dst != end) {
    assign(dst+sht, _3);

    for (dst--; dst != nxt; dst--)
      dst[sht] = *dst;

    nxt -= dst_s;
    sht -= 1; 
  }
  
  retmethod(_1);
endmethod

// move to sequence?
defmethod(OBJ, ginsertAt, ArrayDyn, Range, Object)
  U32            size = self->ArrayFix.Array.size;
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &size);
  
  retmethod( ginsertAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, ginsertAt, ArrayDyn, IntVector, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  // enlarge
  if (arr->size + self2->size > self->capacity)
    genlarge(_1, aInt(self2->size));

  test_assert( prepareRandomInsert(arr,self2), "index out of range" );

  // insert data
  OBJ *dst   = arr->object;
  U32  dst_n = arr->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  
  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    dst[i] = gretain(_3);
    idx += idx_s;
  }

  retmethod(_1);
endmethod

// --- insertAt object (slice, range, intvector)

defmethod(OBJ, ginsertAt, ArrayDyn, Slice, Array)
  PRE
    test_assert( Slice_first(self2) <= self->ArrayFix.Array.size &&
                 Slice_last (self2) <= self->ArrayFix.Array.size, "slice out of range" );
    test_assert( Slice_size (self2) <= self3->size, "source array is too small" );
 
  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    OBJ *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    if (arr->size + dst_n > self->capacity)
      genlarge(_1, aInt(dst_n));

    // always start from the end (reverse fill with positive stride)
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_last  (self2) + arr->object;
      dst_s =  Slice_stride(self2);    
    } else {
      dst   =  Slice_first (self2) + arr->object;
      dst_s = -Slice_stride(self2);
    }

    // shift post data to the end
    memmove(dst+dst_n, dst, (arr->size - (dst-arr->object))*sizeof *dst);
    arr->size += dst_n;

    OBJ *end   = dst - dst_s*dst_n;
    OBJ *nxt   = dst - dst_s;
    OBJ *src   = (self3->size-1)*self3->stride + self3->object;
    I32  src_s =  self3->stride;
    U32  sht   = dst_n;

    while (dst != end) {
      assign(dst+sht,*src);
 
      for (dst--; dst != nxt; dst--)
        dst[sht] = *dst;

      src -= src_s;
      nxt -= dst_s;
      sht -= 1; 
    }
        
    retmethod(_1);
endmethod

// move to sequence? (doublet with _3 as Object)
defmethod(OBJ, ginsertAt, ArrayDyn, Range, Array)
  U32            size = self->ArrayFix.Array.size;
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &size);
  
  retmethod( ginsertAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, ginsertAt, ArrayDyn, IntVector, Array)
  PRE
    test_assert( self2->size <= self3->size, "source array is too small" );

  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    // enlarge
    if (arr->size + self2->size > self->capacity)
      genlarge(_1, aInt(self2->size));

    test_assert( prepareRandomInsert(arr,self2), "index out of range" );

    // insert data
    OBJ *dst   = arr->object;
    U32  dst_n = arr->size;
    I32 *idx   = self2->value;
    U32  idx_n = self2->size;
    I32  idx_s = self2->stride;
    OBJ *src   = self3->object;
    I32  src_s = self3->stride;
    I32 *end   = idx + idx_n*idx_s;
    
    while (idx != end) {
      U32 i = Range_index(*idx, dst_n);
      dst[i] = gretain(*src);
      src += src_s;
      idx += idx_s;
    }
        
    retmethod(_1);
endmethod

defmethod(OBJ, gremoveAt, ArrayDyn, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->ArrayFix.Array.size);
    test_assert( i <= self->ArrayFix.Array.size, "index out of range" );
 
  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->ArrayFix.Array.size);
 
    OBJ *dst = arr->object+i;

    arr->size--;
    grelease(*dst);
    memmove(dst, dst+1, (arr->size-i)*sizeof *dst);
        
    retmethod(_1);
endmethod

defmethod(OBJ, gremoveAt, ArrayDyn, Slice)
  PRE
    test_assert( Slice_first(self2) <= self->ArrayFix.Array.size &&
                 Slice_last (self2) <= self->ArrayFix.Array.size, "slice out of range" );
 
  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    OBJ *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    // always start from the beginning
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_first (self2) + arr->object;
      dst_s =  Slice_stride(self2);
    } else {
      dst   =  Slice_last  (self2) + arr->object;
      dst_s = -Slice_stride(self2);
    }

    OBJ *end = dst + dst_s*dst_n;
    OBJ *nxt = dst + dst_s;
    U32  sht = 1;

    // double level clear-move
    while (dst != end) {
      grelease(*dst);
 
      for (; dst != nxt; dst++)
        *dst = dst[sht];

      nxt += dst_s;
      sht += 1; 
    }

    // shift post data to the beginning
    memmove(dst, dst+dst_n, (arr->size - (dst-arr->object))*sizeof *dst);
    arr->size -= dst_n;
        
    retmethod(_1);
endmethod

// move to sequence?
defmethod(OBJ, gremoveAt, ArrayDyn, Range)
  U32           size  = self->ArrayFix.Array.size;
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &size);
          
  retmethod( gremoveAt(_1,(OBJ)slice) );
endmethod

defmethod(OBJ, gremoveAt, ArrayDyn, IntVector)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  OBJ *dst   = arr->object;
  U32  dst_n = arr->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  U32  fst   = dst_n;
  U32  lst   = 0;

  TMPARRAY_CREATE(U8,flg,dst_n);
  memset(flg,0,dst_n*sizeof *flg);

  // release
  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    if (i >= dst_n) break;
    if (i < fst) fst = i;
    if (i > lst) lst = i;
    flg[i] = 1; grelease(dst[i]);
    idx += idx_s;
  }
  
  if (idx != end) {
    TMPARRAY_DESTROY(flg);
    test_assert( 0, "index out of range" );
  }

  // shrink
  {
    OBJ *end = lst + arr->object;
    U8  *slt = fst + flg;
    U32  sht = 0;

    for (dst += fst; dst != end; ++dst, ++slt) {
      if (*slt) sht++;
      dst[sht] = *dst;
    }

    memmove(dst, dst+idx_n, (arr->size - (dst-arr->object))*sizeof *dst);
    arr->size -= idx_n;
  }

  TMPARRAY_DESTROY(flg);
        
  retmethod(_1);
endmethod

// --- dequeue aliases
defalias(OBJ, (gprepend)gpushFront, ArrayDyn, Object);
defalias(OBJ, (gappend )gpushBack , ArrayDyn, Object);
defalias(OBJ, (gfirst  )gtopFront , Array );
defalias(OBJ, (glast   )gtopBack  , Array );

// --- stack aliases
defalias(OBJ, (gpushBack)gpush, ArrayDyn, Object);
defalias(OBJ, (gpopBack )gpop , ArrayDyn);
defalias(OBJ, (gtopBack )gtop , Array);


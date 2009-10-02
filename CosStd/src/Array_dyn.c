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
 | $Id: Array_dyn.c,v 1.17 2009/10/02 21:56:20 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/container.h>
#include <cos/gen/object.h>

#include <cos/carray.h>

#include "Array_utl.h"

#include <string.h>

// -----

makclass(ArrayFix,Array);
makclass(ArrayDyn,ArrayFix);

// -----

useclass(ArrayDyn,ExBadAlloc);

// -----

#ifndef ARRAY_GROWTH_RATE
#define ARRAY_GROWTH_RATE SEQUENCE_GROWTH_RATE
#endif

#ifndef ARRAY_MINSIZE
#define ARRAY_MINSIZE 1024
#endif

STATIC_ASSERT(array_growth_rate_is_too_small , ARRAY_GROWTH_RATE >= 1.5);
STATIC_ASSERT(array_minimun_size_is_too_small, ARRAY_MINSIZE     >= 256);

// ----- constructors

defalias (OBJ, (ginit)gnew, pmArray);
defmethod(OBJ,  ginit     , pmArray) // Dynamic array
  retmethod(ginitWith(galloc(ArrayDyn),aInt(0)));
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Int);
defmethod(OBJ,  ginitWith         , pmArray, Int) // Dynamic array with capacity
  retmethod(ginitWith(galloc(ArrayDyn),_2));
endmethod

defmethod(OBJ, ginitWith, ArrayDyn, Int)
  PRT(_1);
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  test_assert(self2->value >= 0, "negative array capacity");

  if (self2->value > 0) {
    arrf->_object = malloc(self2->value * sizeof *arr->object);
    if (!arrf->_object) THROW(ExBadAlloc);
  } else
    arrf->_object = 0;

  arr->size      = 0;
  arr->stride    = 1;
  arr->object    = arrf->_object;
  arrf->capacity = self2->value;

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayFix)
  next_method(self);

  if (self->_object)            // take care of protection cases
    free(self->_object);

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->ArrayFix.capacity >= self->ArrayFix.Array.size,
               "dynamic array has capacity < size", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod

// ----- memory management

static I32
extra_size(U32 old_capacity, U32 size)
{
  U32 new_capacity = old_capacity < ARRAY_MINSIZE ? ARRAY_MINSIZE : old_capacity;
  
  while (new_capacity - old_capacity < size)
    new_capacity *= ARRAY_GROWTH_RATE;

  I32 extra = new_capacity - old_capacity;
  
  test_assert(extra > 0 && (U32)extra > size, "array size overflow");

  return extra;
}

defmethod(OBJ, genlarge, ArrayDyn, Float) // negative factor means enlarge front
  PRE
    test_assert(self2->value < -1 ||
                self2->value >  1, "invalid growing factor");
  BODY
    F64 factor   = self2->value;
    U32 capacity = self->ArrayFix.capacity;

    if (factor > 1)
      retmethod( genlarge(_1, aInt(capacity * (factor-1)) ));
    else if (factor < 1)
      retmethod( genlarge(_1, aInt(capacity * (factor+1))) );
endmethod

defmethod(OBJ, genlarge, ArrayDyn, Int) // negative size means enlarge front
  PRE
    test_assert(self2->value, "invalid growing size");
  BODY
    struct ArrayFix* arrf = &self->ArrayFix;
    struct Array*    arr  = &arrf->Array;
    U32     capacity = arrf->capacity;
    ptrdiff_t offset = arr->object - arrf->_object;
    BOOL       front = self2->value < 0;
    U32         size = front ? -self2->value : self2->value;

    capacity += size = extra_size(capacity, size);
    
    OBJ *_object = realloc(arrf->_object, capacity*sizeof *arrf->_object);
    if (!_object) THROW(ExBadAlloc);

    arr -> object  = _object + offset;
    arrf->_object  = _object;
    arrf->capacity = capacity;
    
    if (front) // move data to book the new space front
      arr->object = memmove(arr->object+size, arr->object, arr->size*sizeof *arr->object);
    
    retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, ArrayDyn)
  BOOL ch_cls;
  
  PRE
  POST
    test_assert( ch_cls, "unable to change from dynamic to fixed size array" );
  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    // move data to base
    if (arr->object != arrf->_object)
      arr->object = memmove(arrf->_object, arr->object, arr->size*sizeof *arrf->_object);

    // shrink storage
    if (arr->size != arrf->capacity) {
      OBJ *_object = realloc(arrf->_object, arr->size*sizeof *arrf->_object);
      if (!_object) THROW(ExBadAlloc);

      arr -> object  = _object;
      arrf->_object  = _object;
      arrf->capacity = arr->size;
    }

    ch_cls = cos_object_changeClass(_1, classref(ArrayFix));
    
    retmethod(_1);
endmethod

// ----- clear (size -> 0)

defmethod(OBJ, gclear, ArrayDyn)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  U32 *val_n = &arr->size;
  OBJ *val   = arr->object;
  OBJ *end   = val + *val_n;

  while (val != end) {
    grelease(*--end), --*val_n;
  }

  arr->object = arrf->_object;
  
  retmethod(_1);
endmethod

// ----- dropFirst, dropLast, drop

defmethod(OBJ, gdropFirst, ArrayDyn)
  struct Array *arr = &self->ArrayFix.Array;

  if (arr->size)
    arr->size--, grelease(*arr->object++);
      
  retmethod(_1);
endmethod

defmethod(OBJ, gdropLast, ArrayDyn)
  struct Array *arr = &self->ArrayFix.Array;

  if (arr->size)
    grelease(arr->object[--arr->size]);
      
  retmethod(_1);
endmethod

defmethod(OBJ, gdrop, ArrayDyn, Int)
  struct Array *arr = &self->ArrayFix.Array;
  BOOL front = self2->value < 0;
  U32 n = front ? -self2->value : self2->value;

  if (n > arr->size)
    n = arr->size;

  if (front)
    while (n-- > 0)
      arr->size--, grelease(*arr->object++);
  else
    while (n-- > 0)
      grelease(arr->object[--arr->size]);
      
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

  if (arr->object + arr->size == arrf->_object + arrf->capacity)
    genlarge(_1, aInt(1));
    
  arr->object[arr->size++] = gretain(_2);
  
  retmethod(_1);
endmethod

// ----- prepend, append array

defmethod(OBJ, gprepend, ArrayDyn, Array)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

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

  if (arr->object + arr->size + self2->size > arrf->_object + arrf->capacity)
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
  U32 i;

  PRE
    i = Range_index(self2->value, self->ArrayFix.Array.size);
    test_assert( i <= self->ArrayFix.Array.size, "index out of range" );
 
  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    if (arr->size == arrf->capacity)
      genlarge(_1, aInt(1));

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, arr->size);
 
    OBJ *dst = arr->object+i;

    memmove(dst+1, dst, (arr->size-i)*sizeof *dst);
    *dst = gretain(_3);
    arr->size++;

    retmethod(_1);
endmethod

defmethod(OBJ, ginsertAt, ArrayDyn, Slice, Object)
  PRE
    test_assert( Slice_first(self2) <= self->ArrayFix.Array.size &&
                 Slice_last (self2) <= self->ArrayFix.Array.size, "slice out of range" );
 
  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    OBJ *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    if (arr->size + dst_n > arrf->capacity)
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

defmethod(OBJ, ginsertAt, ArrayDyn, Range, Object)
  struct Range range = Range_normalize(self2,self->ArrayFix.Array.size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod( ginsertAt(_1,(OBJ)&slice,_3) );
endmethod

defmethod(OBJ, ginsertAt, ArrayDyn, IntVector, Object)
  struct ArrayFix *arrf = &self->ArrayFix;
  struct Array    *arr  = &arrf->Array;

  // enlarge
  if (arr->size + self2->size > arrf->capacity)
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

    if (arr->size + dst_n > arrf->capacity)
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

defmethod(OBJ, ginsertAt, ArrayDyn, IntVector, Array)
  PRE
    test_assert( self2->size <= self3->size, "source array is too small" );

  BODY
    struct ArrayFix *arrf = &self->ArrayFix;
    struct Array    *arr  = &arrf->Array;

    // enlarge
    if (arr->size + self2->size > arrf->capacity)
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

// --- removeAt

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

defmethod(OBJ, gremoveAt, ArrayDyn, Range)
  struct Range range = Range_normalize(self2,self->ArrayFix.Array.size);
  struct Slice slice = Slice_fromRange(&range);
          
  retmethod( gremoveAt(_1,(OBJ)&slice) );
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
defalias(OBJ, (gprepend  )gpushFront, ArrayDyn, Object);
defalias(OBJ, (gappend   )gpushBack , ArrayDyn, Object);
defalias(OBJ, (gdropFirst)gpopFront , ArrayDyn);
defalias(OBJ, (gdropLast )gpopBack  , ArrayDyn);
defalias(OBJ, (gfirst    )gfront    , Array );
defalias(OBJ, (glast     )gback     , Array );

// --- stack aliases
defalias(OBJ, (gappend  )gpush, ArrayDyn, Object);
defalias(OBJ, (gdropLast)gpop , ArrayDyn);
defalias(OBJ, (glast    )gtop , Array );


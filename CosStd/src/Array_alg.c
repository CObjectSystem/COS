/*
 o---------------------------------------------------------------------o
 |
 | COS Array - algorithms not using functor
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
 | $Id: Array_alg.c,v 1.12 2009/08/19 16:34:13 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/carray.h>

// -----

useclass(Array, ExBadAlloc);

// ----- equality

defmethod(OBJ, gisEqual, Array, Array)
  if (self1 == self2)
    retmethod(True);

  if (self1->size != self2->size)
    retmethod(False);

  OBJ *obj1   = self1->object;
  I32  obj1_s = self1->stride;
  OBJ *end    = self1->object + self1->size*self1->stride;
  OBJ *obj2   = self2->object;
  I32  obj2_s = self2->stride;
  
  while (obj1 != end) {
    if (gisEqual(*obj1,*obj2) != True)
      retmethod(False);
    obj1 += obj1_s;
    obj2 += obj2_s;
  }

  retmethod(True);
endmethod

// ----- in place

defmethod(void, greverse, Array)
  if (self->size < 2)
    retmethod();

  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + (self->size-1)*self->stride;
  OBJ  tmp;

  while (obj != end) {
    tmp = *obj, *obj = *end, *end = tmp;
    obj += obj_s;
    end -= obj_s;
  }
endmethod

defmethod(void, gpermute, Array, IntVector)
  PRE
    test_assert( self1->size == self2->size, "incompatible array sizes" );

  BODY
    if (self1->size < 2)
      retmethod();

    OBJ *obj   = self1->object;
    U32  obj_n = self1->size;
    I32  obj_s = self1->stride;
    I32 *idx   = self2->value;
    I32  idx_s = self2->stride;

    TMPARRAY_CREATE(OBJ,buf,obj_n); // OBJ buf[obj_n];

    OBJ *cur, *end = buf + obj_n;
    U32  i = 0;

    // permute
    for (cur = buf; cur != end; cur++) {
      i = Range_index(*idx, obj_n);
      if ( !(i < obj_n && obj[i*obj_s]) ) break;
      *cur = obj[i*obj_s], obj[i*obj_s] = 0;
       idx += idx_s;
    }

    if (cur == end) {
      // copy back
      for (cur = buf; cur != end; cur++)
        *obj = *cur, obj += obj_s;

      TMPARRAY_DESTROY(buf);
    } else {
      // rollback (error)
      BOOL iiir = i < obj_n; // last index-is-in-range flag

      while (cur != buf) {
        idx -= idx_s;
        i = Range_index(*idx, obj_n);
        obj[i*obj_s] = *--cur;
      }

      TMPARRAY_DESTROY(buf);
      test_assert( iiir, "index out of range"  );
      test_assert(    0, "invalid permutation" );
    }
endmethod

// ----- repeat

defmethod(OBJ, grepeat, Object, Int)
  PRE
    test_assert(self2->value >= 0, "invalid number of repeat");

  BODY
    struct Array* arr = Array_alloc(self2->value);
    OBJ _arr = (OBJ)arr; PRT(_arr);

    OBJ *dst = arr->object;
    OBJ *end = arr->object + arr->size;
    
    while (dst != end)
      *dst++ = gretain(_1);

    UNPRT(_arr);
    retmethod(gautoDelete(_arr));
endmethod

// ----- zip, zip3, zip4

defmethod(OBJ, gzip, Array, Array)
  U32 size = self1->size < self2->size ? self1->size : self2->size;

  struct Array* arr = Array_alloc(2*size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst    = arr->object;
  OBJ *end    = arr->object + arr->size;
  OBJ *src1   = self1->object; 
  I32  src1_s = self1->stride;
  OBJ *src2   = self2->object;
  I32  src2_s = self2->stride;

  while (dst != end) {
    *dst++ = gretain(*src1), src1 += src1_s;
    *dst++ = gretain(*src2), src2 += src2_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gzip3, Array, Array, Array)
  U32 size = self1->size < self2->size ? self1->size : self2->size;
  if (size > self3->size) size = self3->size;

  struct Array* arr = Array_alloc(3*size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst    = arr->object;
  OBJ *end    = arr->object + arr->size;
  OBJ *src1   = self1->object; 
  I32  src1_s = self1->stride;
  OBJ *src2   = self2->object;
  I32  src2_s = self2->stride;
  OBJ *src3   = self3->object;
  I32  src3_s = self3->stride;

  while (dst != end) {
    *dst++ = gretain(*src1), src1 += src1_s;
    *dst++ = gretain(*src2), src2 += src2_s;
    *dst++ = gretain(*src3), src3 += src3_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gzip4, Array, Array, Array, Array)
  U32 size = self1->size < self2->size ? self1->size : self2->size;
  if (size > self3->size) size = self3->size;
  if (size > self4->size) size = self4->size;

  struct Array* arr = Array_alloc(4*size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst    = arr->object;
  OBJ *end    = arr->object + arr->size;
  OBJ *src1   = self1->object; 
  I32  src1_s = self1->stride;
  OBJ *src2   = self2->object;
  I32  src2_s = self2->stride;
  OBJ *src3   = self3->object;
  I32  src3_s = self3->stride;
  OBJ *src4   = self4->object;
  I32  src4_s = self4->stride;

  while (dst != end) {
    *dst++ = gretain(*src1), src1 += src1_s;
    *dst++ = gretain(*src2), src2 += src2_s;
    *dst++ = gretain(*src3), src3 += src3_s;
    *dst++ = gretain(*src4), src4 += src4_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

// ----- cat, cat3, cat4, cat5

defmethod(OBJ, gcat, Array, Array)
  U32 size = self1->size + self2->size;

  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + self1->size;
  OBJ *src   = self1->object;
  I32  src_s = self1->stride;

  while (dst != end)
    *dst++ = gretain(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->object;
  src_s = self2->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gcat3, Array, Array, Array)
  U32 size = self1->size + self2->size + self3->size;

  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + self1->size;
  OBJ *src   = self1->object;
  I32  src_s = self1->stride;

  while (dst != end)
    *dst++ = gretain(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->object;
  src_s = self2->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  end  += self3->size;
  src   = self3->object;
  src_s = self3->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gcat4, Array, Array, Array, Array)
  U32 size = self1->size + self2->size + self3->size + self4->size;

  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + self1->size;
  OBJ *src   = self1->object;
  I32  src_s = self1->stride;

  while (dst != end)
    *dst++ = gretain(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->object;
  src_s = self2->stride;

  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  end  += self3->size;
  src   = self3->object;
  src_s = self3->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  end  += self4->size;
  src   = self4->object;
  src_s = self4->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gcat5, Array, Array, Array, Array, Array)
  U32 size = self1->size + self2->size +
             self3->size + self4->size + self5->size;

  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + self1->size;
  OBJ *src   = self1->object;
  I32  src_s = self1->stride;

  while (dst != end)
    *dst++ = gretain(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->object;
  src_s = self2->stride;

  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  end  += self3->size;
  src   = self3->object;
  src_s = self3->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  end  += self4->size;
  src   = self4->object;
  src_s = self4->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  end  += self5->size;
  src   = self5->object;
  src_s = self5->stride;
  
  while (dst != end)
    *dst++ = gretain(*src), src += src_s;

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

// ----- search (object)

static OBJ*
findObj(OBJ *obj, U32 obj_n, I32 obj_s, OBJ _2)
{
  if (!obj_n) return 0;

  OBJ *end = obj + obj_n*obj_s;

  while (obj != end) {
    if (gisEqual(*obj, _2) == True)
      return obj;
    obj += obj_s;
  }

  return 0;  
}

defmethod(OBJ, gfind, Array, Object)
  OBJ *obj   = self->object;
  U32  obj_n = self->size;
  I32  obj_s = self->stride;

  OBJ *p = findObj(obj,obj_n,obj_s,_2);
  if (!p) retmethod(Nil);

  retmethod( p ? *p : Nil );  
endmethod

defmethod(OBJ, gifind, Array, Object)
  OBJ *obj   = self->object;
  U32  obj_n = self->size;
  I32  obj_s = self->stride;

  OBJ *p = findObj(obj,obj_n,obj_s,_2);
  if (!p) retmethod(Nil);

  retmethod(obj ? gautoDelete( aInt((p-obj)/obj_s) ) : Nil);
endmethod

// ----- search (array)

// -- KnuthMorrisPratt (linear)

static OBJ*
KnuthMorrisPratt(OBJ *obj, U32 obj_n, I32 obj_s, OBJ *pat, I32 pat_n, I32 pat_s)
{
  TMPARRAY_CREATE(I32,kmpNext,pat_n);

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

    while (j < obj_n) {
      while (i > -1 && gisEqual(pat[i*pat_s],obj[j*obj_s]) == False)
        i = kmpNext[i];
      i++;
      j++;
      if (i >= pat_n) { // found
        TMPARRAY_DESTROY(kmpNext);
        return obj + (j - i)*obj_s;
      }
    }
  }

  TMPARRAY_DESTROY(kmpNext);
  return 0;
}

// -- find front-end

static OBJ*
findSub(OBJ *obj, U32 obj_n, I32 obj_s, OBJ *pat, U32 pat_n, I32 pat_s)
{
  // string too short
  if (obj_n < pat_n) return 0;

  // empty pattern
  if (!pat_n) return obj;

  // find first
  OBJ *p = findObj(obj, obj_n, obj_s, *pat);
  if (!p) return 0;

  // single object pattern
  if (pat_n == 1) return p;

  // linear search
  return KnuthMorrisPratt(p, obj_n-(p-obj)*obj_s, obj_s, pat, pat_n, pat_s);
}

// -- find methods

defmethod(OBJ, gfind, Array, Array)
  OBJ *obj   = self->object;
  U32  obj_n = self->size;
  I32  obj_s = self->stride;

  OBJ *p = findSub(obj,obj_n,obj_s,self2->object,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ avw = aArrayView(self, atSlice((p-obj)/obj_s,self2->size,obj_s) );
  retmethod(gautoDelete( avw ));
endmethod

defmethod(OBJ, gifind, Array, Array)
  OBJ *obj   = self->object;
  U32  obj_n = self->size;
  I32  obj_s = self->stride;

  OBJ *p = findSub(obj,obj_n,obj_s,self2->object,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ slc = aSlice((p-obj)/obj_s,self2->size,obj_s);
  retmethod(gautoDelete( slc ));  
endmethod


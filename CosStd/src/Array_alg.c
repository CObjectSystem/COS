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
 | $Id: Array_alg.c,v 1.8 2009/07/24 12:36:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/carray.h>

// -----

useclass(Array, ExBadAlloc);

// ----- in place

defmethod(void, greverse, Array)
  if (self->size < 2)
    retmethod();

  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *end   = self->object+(self->size-1)*self->stride;
  OBJ  tmp;

  while (obj != end) {
    tmp = *obj, *obj = *end, *end = tmp;
    obj += obj_s;
    end -= obj_s;
  }
endmethod

defmethod(void, gpermute, Array, IntVector)
  test_assert( self1->size == self2->size, "incompatible array sizes" );

  if (self1->size < 2)
    retmethod();

  OBJ *obj   = self1->object;
  U32  obj_z = self1->size;
  I32  obj_s = self1->stride;
  I32 *idx   = self2->value;
  I32  idx_s = self2->stride;

  TMPARRAY_CREATE(OBJ,buf,obj_z); // OBJ buf[obj_z];

  OBJ *cur, *end = buf + obj_z;
  U32  i = 0;

  // permute
  for (cur = buf; cur != end; cur++) {
    i = Range_index(*idx, obj_z);
    if ( !(i < obj_z && obj[i*obj_s]) ) break;
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
    BOOL iiir = i < obj_z; // last index-is-in-range flag

    while (cur != buf) {
      idx -= idx_s;
      i = Range_index(*idx, obj_z);
      obj[i*obj_s] = *--cur;
    }

    TMPARRAY_DESTROY(buf);
    test_assert( iiir, "index out of range"  );
    test_assert(    0, "invalid permutation" );
  }
endmethod

// ----- min/max

defmethod(OBJ, gmin, Array)
  useclass(Greater);
  
  if (self->size == 0)
    retmethod(Nil);

  OBJ *obj   = self->object + self->stride;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;
  OBJ  min   = self->object[0];

  while (obj != end) {
    if (gcompare(min, *obj) == Greater)
      min = *obj;
    obj += obj_s;
  }

  retmethod(min);
endmethod

defmethod(OBJ, gmax, Array)
  useclass(Lesser);
  
  if (self->size == 0)
    retmethod(Nil);

  OBJ *obj   = self->object + self->stride;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;
  OBJ  max   = self->object[0];

  while (obj != end) {
    if (gcompare(max, *obj) == Lesser)
      max = *obj;
    obj += obj_s;
  }
      
  retmethod(max);
endmethod

// ----- zip, zip3, zip4, zipn

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
  retmethod(gautoRelease(_arr));
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
  retmethod(gautoRelease(_arr));
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
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gzipn, Array)
  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *obj_e = self->object + self->size*self->stride;
  U32  size  = -1;

  while (obj != obj_e) {
    test_assert( cos_object_isKindOf(*obj, classref(Array)),
                 "invalid array element (should be an Array)" );
    U32 sz = STATIC_CAST(struct Array*, *obj)->size;
    if (sz < size) size = sz;
    obj += obj_s;
  }

  struct Array* arr = Array_alloc(size*self->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst = arr->object;
  OBJ *end = arr->object + arr->size;

  for (U32 i = 0; dst != end; i++) {
    obj = self->object;
    while (obj != obj_e) {
       struct Array* src = STATIC_CAST(struct Array*, *obj);
       *dst++ = gretain( src->object[i*src->stride] );
       obj += obj_s;
    }
  }

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- cat, cat3, cat4, catn

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
  retmethod(gautoRelease(_arr));
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
  retmethod(gautoRelease(_arr));
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
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gcatn, Array)
  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *obj_e = self->object + self->size*self->stride;
  U32  size  = 0;

  while (obj != obj_e) {
    test_assert( cos_object_isKindOf(*obj, classref(Array)),
                 "invalid array element (should be an Array)" );
    size += STATIC_CAST(struct Array*, *obj)->size;
    obj += obj_s;
  }

  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst = arr->object;
  OBJ *end = arr->object;
  OBJ *src;
  I32  src_s;

  obj = self->object;

  while (obj != obj_e) {
    struct Array *arr = STATIC_CAST(struct Array*, *obj);
    end  += arr->size;
    src   = arr->object;
    src_s = arr->stride;
  
    while (dst != end)
      *dst++ = gretain(*src), src += src_s;

    obj += obj_s;
  }

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod


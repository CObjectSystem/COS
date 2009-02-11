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
 | $Id: Array_alg.c,v 1.3 2009/02/11 11:48:47 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

useclass(Array);

// ----- in place

defmethod(void, gclear, Array)
  OBJ *obj = self->object;
  OBJ *end = self->object+self->size;

  while (obj < end)
    grelease(*obj), *obj++ = Nil;
endmethod

defmethod(void, greverse, Array)
  if (self->size < 2)
    retmethod();

  OBJ *obj = self->object;
  OBJ *end = self->object+self->size-1;
  OBJ  tmp;

  while (obj < end)
    tmp = *obj, *obj++ = *end, *end-- = tmp;
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Array, Array)
  if (self1 == self2)
    retmethod(True);
    
  if (self1->size != self2->size)
    retmethod(False);
  
  OBJ *obj1 = self1->object;
  OBJ *end1 = self1->object+self1->size;
  OBJ *obj2 = self2->object;

  while (obj1 < end1)
    if (gisEqual(*obj1++, *obj2++) == False)
      retmethod(False);
      
  retmethod(True);
endmethod

// ----- min/max

defmethod(OBJ, gmin, Array)
  useclass(Greater);
  
  if (!self->size)
    retmethod(0);

  OBJ  min = self->object[0];
  OBJ *obj = self->object+1;
  OBJ *end = self->object+self->size;

  while (obj < end)
    if (gcompare(min, *obj++) == Greater)
      min = *obj;
      
  retmethod(min);
endmethod

defmethod(OBJ, gmax, Array)
  useclass(Lesser);
  
  if (self->size == 0)
    retmethod(0);

  OBJ  max = self->object[0];
  OBJ *obj = self->object+1;
  OBJ *end = self->object+self->size;

  while (obj < end)
    if (gcompare(max, *obj++) == Lesser)
      max = *obj;
      
  retmethod(max);
endmethod

// ----- zip, zip3, zip4, zipn

defmethod(OBJ, gzip, Array, Array)
  U32 size = self1->size+self2->size;
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object, *end  = obj +arr  ->size;
  OBJ *src1 = self1->object, *end1 = src1+self1->size;
  OBJ *src2 = self2->object, *end2 = src2+self2->size;

  if (self1->size < self2->size) {
    while(src1 < end1) {
      *obj++ = gretain( *src1++ );
      *obj++ = gretain( *src2++ );
    }
    while(obj  < end )
      *obj++ = gretain( *src2++ );
  } else {
    while(src2 < end2) {
      *obj++ = gretain( *src1++ );
      *obj++ = gretain( *src2++ );
    }
    while(obj  < end )
      *obj++ = gretain( *src1++ );
  }

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gzip3, Array, Array, Array)
  U32 size = self1->size+self2->size+self3->size;
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object, *end  = obj +arr  ->size;
  OBJ *src1 = self1->object, *end1 = src1+self1->size;
  OBJ *src2 = self2->object, *end2 = src2+self2->size;
  OBJ *src3 = self3->object, *end3 = src3+self3->size;

  while(obj < end) {
    if (src1 < end1) *obj++ = gretain( *src1++ );
    if (src2 < end2) *obj++ = gretain( *src2++ );
    if (src3 < end3) *obj++ = gretain( *src3++ );
  }

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gzip4, Array, Array, Array, Array)
  U32 size = self1->size+self2->size+self3->size+self4->size;
  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object, *end  = obj +arr  ->size;
  OBJ *src1 = self1->object, *end1 = src1+self1->size;
  OBJ *src2 = self2->object, *end2 = src2+self2->size;
  OBJ *src3 = self3->object, *end3 = src3+self3->size;
  OBJ *src4 = self4->object, *end4 = src4+self4->size;

  while(obj < end) {
    if (src1 < end1) *obj++ = gretain( *src1++ );
    if (src2 < end2) *obj++ = gretain( *src2++ );
    if (src3 < end3) *obj++ = gretain( *src3++ );
    if (src4 < end4) *obj++ = gretain( *src4++ );
  }

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gzipn, Array)
  U32 size = 0;
  OBJ *obj = self->object;
  OBJ *end = self->object+self->size;

  for (; obj < end; obj++) {
    test_assert( cos_any_isKindOf(*obj, classref(Array)),
                 "invalid array element (should be an Array)" );
    size += gsize(*obj);
  }

  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  obj = arr->object;
  end = arr->object+arr->size;

  for (U32 i = 0; obj < end; i++) {
    OBJ *src = self->object;
    OBJ *end = self->object+self->size;
    
    for (; src < end; src++) {
       struct Array* arr = STATIC_CAST(struct Array*, *src);
       if (i < arr->size) *obj++ = gretain( arr->object[i] );
    }
  }

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- cat, cat3, cat4, catn

defmethod(OBJ, gcat, Array, Array)
  U32 size = self1->size+self2->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+self1->size;
  OBJ *src = self1->object;

  while (obj < end)
    *obj++ = gretain(*src++);
  
  src  = self2->object;
  end += self2->size;
  
  while (obj < end)
    *obj++ = gretain(*src++);

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gcat3, Array, Array, Array)
  U32 size = self1->size+self2->size+self3->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+self1->size;
  OBJ *src = self1->object;

  while (obj < end)
    *obj++ = gretain(*src++);
  
  src  = self2->object;
  end += self2->size;
  
  while (obj < end)
    *obj++ = gretain(*src++);

  src  = self3->object;
  end += self3->size;
  
  while (obj < end)
    *obj++ = gretain(*src++);

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gcat4, Array, Array, Array, Array)
  U32 size = self1->size+self2->size+self3->size+self4->size;
  struct Array *arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+self1->size;
  OBJ *src = self1->object;

  while (obj < end)
    *obj++ = gretain(*src++);
  
  src  = self2->object;
  end += self2->size;
  
  while (obj < end)
    *obj++ = gretain(*src++);

  src  = self3->object;
  end += self3->size;
  
  while (obj < end)
    *obj++ = gretain(*src++);

  src  = self4->object;
  end += self4->size;
  
  while (obj < end)
    *obj++ = gretain(*src++);

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gcatn, Array)
  OBJ *obj = self->object;
  OBJ *end = self->object+self->size;
  U32 size = 0;

  while (obj < end)
    size += gsize(*obj++);

  OBJ arr = gnewWith(Array,aInt(size)); PRT(arr);
  
  obj = self->object;
  end = self->object+self->size;

  while (obj < end)
    gappend(arr, *obj++);

  gadjust(arr);
  UNPRT(arr);
  retmethod(gautoRelease(arr));
endmethod


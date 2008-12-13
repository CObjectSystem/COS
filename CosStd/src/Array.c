/*
 o---------------------------------------------------------------------o
 |
 | COS Array
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
 | $Id: Array.c,v 1.17 2008/12/13 00:50:03 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Array.h>
#include <cos/Value.h>
#include <cos/Slice.h>
#include <cos/Number.h>
#include <cos/Vector.h>
#include <cos/Functor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/gen/init.h>

#include <stdlib.h>

useclass(Array);

makclass(Array    , Collection);
makclass(Array0   , Array);
makclass(Array1   , Array);
makclass(Array2   , Array);
makclass(Array3   , Array);
makclass(Array4   , Array);
makclass(Array5   , Array);
makclass(Array6   , Array);
makclass(Array7   , Array);
makclass(Array8   , Array);
makclass(Array9   , Array);
makclass(ArrayN   , Array);
makclass(SubArray , Array);
makclass(DynArrayN, Array);
makclass(DynArray , DynArrayN);

// ----- shared private implementation

#include "./Array_p.h"

// ----- ctor/dtor of a (dynamic) array

defmethod(OBJ, galloc, mArray)
  retmethod(_1); // lazy alloc
endmethod

defmethod(OBJ, ginit, mArray)
  retmethod( (OBJ)dynarray_alloc(10) );
endmethod

defmethod(OBJ, ginitWith, mArray, Int)
  test_assert(self2->value >= 0, "negative array size");
  
  retmethod( (OBJ)dynarray_alloc(self2->value) );
endmethod

defmethod(OBJ, ginitWith, Array, Array) // copy
  test_assert(self1->size <= self2->size, "incompatible array sizes");

  OBJ *obj = self1->object;
  OBJ *end = self1->object+self1->size;
  OBJ *src = self2->object;

  while(obj < end)
    *obj++ = gretain(*src++);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, mArray, Array) // clone
  struct Array* arr = array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object;

  while(obj < end)
    *obj++ = gretain(*src++);

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Any, Int) // singleton
  test_assert(self3->value >= 0, "negative array size");

  struct Array* arr = array_alloc(self3->value);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr->object;
  OBJ *end = arr->object+arr->size;
  
  while(obj < end)
    *obj++ = gretain(_2);

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Functor, Int) // generator
  test_assert(self3->value >= 0, "negative array size");

  struct Array* arr = array_alloc(self3->value);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr->object;
  OBJ *end = arr->object+arr->size;
  int argc = gsize(_2);

  if (!argc)
    while(obj < end)
      *obj++ = gretain(geval(_2));

  else
    for (I32 i = 0; obj < end; i++)
      *obj++ = gretain(geval1(_2, aInt(i)));

  UNPRT(_arr);
  retmethod(_arr);
endmethod


defmethod(OBJ, ginitWith2, mArray, Array, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self2->size);

  retmethod( ginitWith2(_1,_2,slice) );  
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, Slice1)
  test_assert( self3->start < self2->size && Slice1_last(self3) < self2->size,
               "slice out of range" );

  struct Array* arr = array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object+self3->start;
  I32 step = self3->stride;

  for (; obj < end; src += step)
    *obj++ = gretain(*src);
  
  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, IntVector)
  struct Array* arr = array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object;
  U32 size = self2->size;
  I32 *idx = self3->value;

  while(obj < end) {
    U32 i = index_abs(*idx++, size);
    test_assert( i < size, "index out of range" );
    *obj++ = gretain(src[i]);
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWithObjPtr, mArray, (U32)n, (OBJ*)obj)
  retmethod( ginitWith(_1, aArrayRef(n,obj)) ); // clone
endmethod

defmethod(OBJ, gdeinit, Array)
  OBJ *obj = self1->object;
  OBJ *end = self1->object+self1->size;

  while (obj < end && *obj) // take care of protection cases
    grelease(*obj++);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, DynArrayN)
  next_method(self);
  free(self->Array.object);
  
  retmethod(_1);
endmethod

// ----- ctor/dtor of a subarray

defmethod(OBJ, ginitWith2, mSubArray, Array, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self2->size);

  retmethod( ginitWith2(_1,_2,slice) );
endmethod

defmethod(OBJ, ginitWith2, mSubArray, Array, Slice1)
  OBJ arr = gretain(_2);
 
  test_assert( cos_any_isa(arr, classref(DynArray)),
               "subarray accepts only fixed size Array" );
  test_assert( Slice1_iscontiguous(self3),
               "subarray slice must be contiguous");
  test_assert( Slice1_last(self3) < self2->size,
               "subarray slice out of range" );

  struct Array *ref = STATIC_CAST(struct Array*, arr);

  retmethod( (OBJ)subarray_alloc(ref, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, SubArray)
  grelease(self->array);
  
  retmethod(_1);
endmethod
 
// ----- setters

defmethod(OBJ, gputAt, Array, Any, Int)
  U32 i = index_abs(self3->value, self->size);
  test_assert( i < self->size, "index out of range" );

  OBJ *obj = self->object+i;
  OBJ  old = *obj;
  *obj = gretain(_2);
  grelease(old);
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self->size);

  retmethod( gputAt(_1,_2,slice) );  
endmethod

defmethod(OBJ, gputAt, Array, Array, Slice1)
  test_assert( self3->start < self->size && Slice1_last(self3) < self->size,
               "slice out of range" );

  OBJ *obj = self1->object+self3->start;
  OBJ *src = self2->object;
  OBJ *end = self2->object+self2->size;
  I32 step = self3->stride;

  for (; src < end; src++, obj += step) {
    OBJ old = *obj;
    *obj = gretain(*src);
    grelease(old);
  }
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, IntVector)
  test_assert( self2->size >= self3->size,
               "incompatible array sizes" );

  OBJ *obj = self1->object;
  OBJ *src = self2->object;
  U32 size = self1->size;
  I32 *idx = self3->value;
  I32 *end = self3->value+self3->size;

  for(; idx < end; idx++, src++) {
    U32 i = index_abs(*idx, size);
    test_assert( i < size, "index out of range" );
    OBJ old = obj[i];
    obj[i] = gretain(*src);
    grelease(old);
  }

  retmethod(_1);  
endmethod

// ----- getters

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, ggetAt, Array, Int)
  U32 i = index_abs(self2->value, self->size);
  test_assert( i < self->size, "index out of range" );

  retmethod( self->object[i] );
endmethod

defmethod(OBJ, ggetAt, Array, Range1)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, Slice1)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoRelease(ginitWith2(Array,_1,_2)) );
endmethod

// ----- accessors and adjustment

defalias (OBJ, (gput)gappend, DynArray, Any);
defalias (OBJ, (gput)gpush  , DynArray, Any);
defmethod(OBJ,  gput        , DynArray, Any)
  struct Array *arr = &self->DynArrayN.Array;

  if (arr->size == self->capacity)
    dynarray_resizeBy(self, 1.8);
    
  arr->object[arr->size++] = gretain(_2);

  retmethod(_1);
endmethod

defalias (OBJ, (gget)glast, DynArray);
defalias (OBJ, (gget)gtop , DynArray);
defmethod(OBJ,  gget      , DynArray)
  struct Array *arr = &self->DynArrayN.Array;
  
  retmethod( arr->size ? arr->object[arr->size-1] : 0 );
endmethod

defalias (OBJ, (gdrop)gpop, DynArray);
defmethod(OBJ,  gdrop     , DynArray)
  struct Array *arr = &self->DynArrayN.Array;
  
  retmethod(arr->size ? grelease(arr->object[--arr->size]) : 0);
endmethod

defmethod(OBJ, gadjust, DynArray)
  if (self->DynArrayN.Array.size < self->capacity)
    dynarray_resizeBy(self, 1.0);

  test_assert( cos_any_changeClass(_1, classref(DynArrayN)),
               "unable to change dynamic array to fixed size array" );

  retmethod(_1);
endmethod

defmethod(OBJ,  gappend, DynArray, Array)
  struct Array *arr = &self->DynArrayN.Array;

  if (self->capacity - arr->size < self2->size) { // enlarge first
    FLOAT size = arr->size;

    do size *= 1.8;
    while (self->capacity - size < self2->size);

    dynarray_resizeBy(self, size);
  }

  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+self2->size;
  OBJ *src = self2->object;

  while (obj < end)
    *obj++ = gretain(*src++);

  arr->size += self2->size;

  retmethod(_1);
endmethod

// ----- clear (in place) 

defmethod(OBJ, gclear, Array)
  OBJ *obj = self1->object;
  OBJ *end = self1->object+self1->size;

  while (obj < end)
    grelease(*obj), *obj++ = Nil; 

  retmethod(_1);
endmethod

// ----- reverse (in place)

defmethod(OBJ, greverse, Array)
  OBJ *obj = self->object;
  OBJ *end = self->object+self->size-1;
  OBJ  tmp;
  
  while (obj < end)
    tmp = *obj, *obj++ = *end, *end-- = tmp;

  retmethod(_1);
endmethod

// ----- apply (in place)

defmethod(OBJ, gapply, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  while(obj < end) geval1(_1, *obj++);
  
  retmethod(_2);
endmethod

defmethod(OBJ, gapply, Function1, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;
  OBJFCT1 fct = self->fct;

  while(obj < end) fct(*obj++);
  
  retmethod(_2);
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, Array)
  struct Array* arr = array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object;

  while(obj < end)
    *obj++ = gretain( geval1(_1,*src++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap, Function1, Array)
  struct Array* arr = array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size; 
  OBJ *src = self2->object;
  OBJFCT1 fct = self->fct;

  while(obj < end)
    *obj++ = gretain( fct(*src++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap2, Functor, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;

  while(obj < end)
    *obj++ = gretain( geval2(_1,*src1++,*src2++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap2, Function2, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJFCT2 fct = self->fct;

  while(obj < end)
    *obj++ = gretain( fct(*src1++,*src2++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap3, Functor, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJ *src3 = self4->object;

  while(obj < end)
    *obj++ = gretain( geval3(_1,*src1++,*src2++,*src3++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap3, Function3, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJ *src3 = self4->object;
  OBJFCT3 fct = self->fct;

  while(obj < end)
    *obj++ = gretain( fct(*src1++,*src2++,*src3++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap4, Functor, Array, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJ *src3 = self4->object;
  OBJ *src4 = self5->object;

  while(obj < end)
    *obj++ = gretain( geval4(_1,*src1++,*src2++,*src3++,*src4++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap4, Function4, Array, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJ *src3 = self4->object;
  OBJ *src4 = self5->object;
  OBJFCT4 fct = self->fct;

  while(obj < end)
    *obj++ = gretain( fct(*src1++,*src2++,*src3++,*src4++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- zip, zip3, zip4, zip5, zipn

defmethod(OBJ, gzip, Array, Array)
  U32 size = self1->size+self2->size;
  struct Array* arr = array_alloc(size);
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
  struct Array* arr = array_alloc(size);
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
  struct Array* arr = array_alloc(size);
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
    test_assert( array_isa(*obj),
                 "invalid array element (should be an Array)" );
    size += gsize(*obj);
  }

  struct Array* arr = array_alloc(size);
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
  struct Array *arr = array_alloc(size);
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
  struct Array *arr = array_alloc(size);
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
  struct Array *arr = array_alloc(size);
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
  U32 size = 0;
  OBJ *obj = self->object;
  OBJ *end = self->object+self->size;

  for (; obj < end; obj++) {
    test_assert( array_isa(*obj),
                 "invalid array element (should be an Array)" );
    size += gsize(*obj);
  }

  struct Array* arr = array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  
  obj = arr->object;

  for (U32 i = 0; i < self->size; i++) {
    struct Array *arr = STATIC_CAST(struct Array*, self->object[i]);
    OBJ *src = arr->object;
    OBJ *end = arr->object+arr->size;

    while (src < end)
      *obj++ = gretain(*src++);
  }  

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- all, any

defmethod(OBJ, gall, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  for (; obj < end; obj++)
    if (geval1(_1, *obj) == False)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gall, Function1, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;
  OBJFCT1 fct = self->fct;

  for (; obj < end; obj++)
    if (fct(*obj) == False)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  for (; obj < end; obj++)
    if (geval1(_1, *obj) == True)
      retmethod(True);
      
  retmethod(False);
endmethod

defmethod(OBJ, gany, Function1, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;
  OBJFCT1 fct = self->fct;

  for (; obj < end; obj++)
    if (fct(*obj) == True)
      retmethod(True);
      
  retmethod(False);
endmethod

// ----- equal, min, max

defmethod(OBJ, gequal, Array, Array)
  if (self1 == self2)
    retmethod(True);
    
  if (self1->size != self2->size)
    retmethod(False);
  
  OBJ *obj1 = self1->object;
  OBJ *end1 = self1->object+self1->size;
  OBJ *obj2 = self2->object;

  for (; obj1 < end1; obj1++, obj2++)
    if (gequal(*obj1, *obj2) == False)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gmin, Array)
  useclass(Greater);
  
  if (self->size == 0)
    retmethod(Nil);

  OBJ  min = self->object[0];
  OBJ *obj = self->object+1;
  OBJ *end = self->object+self->size;

  for (; obj < end; obj++)
    if (gcompare(min, *obj) == Greater)
      min = *obj;
      
  retmethod(min);
endmethod

defmethod(OBJ, gmax, Array)
  useclass(Lesser);
  
  if (self->size == 0)
    retmethod(Nil);

  OBJ  max = self->object[0];
  OBJ *obj = self->object+1;
  OBJ *end = self->object+self->size;

  for (; obj < end; obj++)
    if (gcompare(max, *obj) == Lesser)
      max = *obj;
      
  retmethod(max);
endmethod

// ----- filter, reduce, accumulate

defmethod(OBJ, gfilter, Functor, Array)
  struct Array* arr = dynarray_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *end = self2->object+self2->size;
  OBJ *obj = arr  ->object;
  OBJ *src = self2->object;

  for (; src < end; src++)
    if (geval1(_1, *src) == True)
      *obj++ = gretain(*src), ++arr->size;

  UNPRT(_arr);
  retmethod(gadjust(gautoRelease(_arr)));
endmethod

defmethod(OBJ, gfilter, Function1, Array)
  struct Array* arr = dynarray_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *src = self2->object;
  OBJ *end = self2->object+self2->size;
  OBJFCT1 fct = self->fct;

  for (; src < end; src++)
    if (fct(*src) == True)
      *obj++ = gretain(*src), ++arr->size;

  UNPRT(_arr);
  retmethod(gadjust(gautoRelease(_arr)));
endmethod

defmethod(OBJ, greduce, Functor, Any, Array)
  OBJ  obj = _2;
  OBJ *src = self3->object;
  OBJ *end = self3->object+self3->size;
  
  while (src < end)
    obj = geval2(_1, obj, *src++);

  retmethod(obj);
endmethod

defmethod(OBJ, greduce, Function2, Any, Array)
  OBJ  obj = _2;
  OBJ *src = self3->object;
  OBJ *end = self3->object+self3->size;
  OBJFCT2 fct = self->fct;
  
  while (src < end)
    obj = fct(obj, *src++);

  retmethod(obj);
endmethod

defmethod(OBJ, gaccumulate, Functor, Any, Array)
  struct Array* arr = array_alloc(self3->size+1);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self3->object;

  *obj++ = gretain(_2);
  
  for (; obj < end; obj++)
    *obj = gretain( geval2(_1,obj[-1],*src++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gaccumulate, Function2, Any, Array)
  struct Array* arr = array_alloc(self3->size+1);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self3->object;
  OBJFCT2 fct = self->fct;

  *obj++ = gretain(_2);
  
  for (; obj < end; obj++)
    *obj = gretain( fct(obj[-1],*src++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- finding

defmethod(OBJ, gfind, Functor, Any, Array)
  useclass(Lesser, Equal, Greater);

  if (self3->size == 0)
    retmethod(Nil);

  OBJ *obj = self3->object;
  OBJ  res = geval2(_1, _2, *obj);

  if (res == True || res == Equal) // found
    retmethod(*obj);

  // linear search
  if (res == False) {
    OBJ *end = self3->object+self3->size;
    
    for (++obj; obj < end; obj++)
      if (geval2(_1, _2, *obj) == True) // found
        retmethod(*obj);

    retmethod(Nil);
  }

  // binary search
  if (res == Lesser)
    retmethod(Nil);
  
  test_assert( res == Greater,
    "gfind expects functor returning TrueFalse or Ordered predicates" );

  U32 lo = 1, hi = self3->size-1;
    
  while(lo <= hi) {
    U32 i = (lo + hi) / 2;
    res = geval2(_1, _2, obj[i]);

    if (res == Equal)
      retmethod(obj[i]); // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

  retmethod(Nil);  
endmethod

defmethod(OBJ, gfind, Function2, Any, Array)
  useclass(Lesser, Equal, Greater);

  if (self3->size == 0)
    retmethod(Nil);

  OBJFCT2 fct = self->fct;
  OBJ *obj = self3->object;
  OBJ res = fct(_2, *obj);

  if (res == True || res == Equal) // found
    retmethod(*obj);

  // linear search
  if (res == False) {
    OBJ *end = self3->object+self3->size;
    
    for (++obj; obj < end; obj++)
      if (fct(_2, *obj) == True) // found
        retmethod(*obj);

    retmethod(Nil);
  }

  // binary search
  if (res == Lesser)
    retmethod(Nil);
  
  test_assert( res == Greater,
    "gfind expects functor returning TrueFalse or Ordered predicates" );

  U32 lo = 1, hi = self3->size-1;
    
  while(lo <= hi) {
    U32 i = (lo + hi) / 2;
    res = fct(_2, obj[i]);

    if (res == Equal)
      retmethod(obj[i]); // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

endmethod

// ----- sorting (in place)

#define NETSORT(a,r) \
  do { \
    switch(r) { \
    case 1: \
      SORT(a[0],a[1]); \
      return; \
    \
    case 2: \
      SORT(a[0],a[1]); \
      SORT(a[0],a[2]); \
      SORT(a[1],a[2]); \
      return; \
    \
    case 3: \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[0],a[1]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); \
      return; \
    \
    case 4: \
      SORT(a[0],a[4]); SORT(a[1],a[3]); \
      SORT(a[0],a[2]); \
      SORT(a[2],a[4]); SORT(a[0],a[1]); \
      SORT(a[2],a[3]); SORT(a[1],a[4]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      return; \
    \
    case 5: \
      SORT(a[0],a[4]); SORT(a[1],a[5]); \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[2],a[4]); SORT(a[3],a[5]); \
      SORT(a[0],a[1]); SORT(a[4],a[5]); \
      SORT(a[1],a[4]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      return; \
    } \
  } while(0)

/* from "Quicksort Is Optimal", R. Sedgwick & J. Bentley, 2002
   plus some practical improvements.
 */

#define EXCH(a,b) (t=(a),(a)=(b),(b)=t)
#define SORT(a,b) if (GCMP(b,a) == Lesser) EXCH(a,b)
#define GCMP(a,b) geval2(fun,a,b)

static inline U32
pivot(void)
{
  static U32 x = 1; // no need to be thread safe
  
  return x = x * 2621124293u + 1;
}

static void
quicksort_fun(OBJ a[], I32 r, OBJ fun)
{
  useclass(Lesser, Equal);
  I32 i, j, p, q;
  OBJ t, ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,r);

  // select pivot as the median-of-three taken pseudo-randomly
  i = pivot() % (r+1) + 0, EXCH(a[i],a[0  ]);
  i = pivot() % (r  ) + 1, EXCH(a[i],a[r  ]);
  i = pivot() % (r-1) + 1, EXCH(a[i],a[r-1]);
  SORT(a[0],a[r-1]);
  if ((ri = GCMP(a[r  ],a[0])) == Lesser) EXCH(a[r],a[0  ]);
  if ((rj = GCMP(a[r-1],a[r])) == Lesser) EXCH(a[r],a[r-1]);

  // partitioning initialization
  i = 0, j = r-1;
  p = ri == Equal ? i : -1;
  q = rj == Equal ? j :  r;

  // three-way partitioning
  for (;;) {
    while ((rj = GCMP(a[++i],a[  r])) == Lesser     ) ;
    while ((ri = GCMP(a[  r],a[--j])) == Lesser && j) ;

    if (i >= j) break;

    EXCH(a[i], a[j]);
    if (ri == Equal) ++p, EXCH(a[p],a[i]);
    if (rj == Equal) --q, EXCH(a[q],a[j]);
  }

  // move pivot to center
  EXCH(a[i], a[r]);

  // move equal partition from borders to center
  for (j = i-1; p-- > 0; j--) EXCH(a[p],a[j]);
  for (i = i+1; ++q < r; i++) EXCH(a[q],a[i]);

  // divide & conquer (small first)
  OBJ *s, *l;
  
  if (j < r-i)
    s = a, l = a+i, p = j, q = r-i;
  else
    l = a, s = a+i, q = j, p = r-i;

  quicksort_fun(s,p,fun);
  quicksort_fun(l,q,fun); // tail recursion
}

#undef  GCMP
#define GCMP(a,b) fct(a,b)

static void
quicksort_fct(OBJ a[], I32 r, OBJFCT2 fct)
{
  useclass(Lesser, Equal);
  I32 i, j, p, q;
  OBJ t, ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,r);

  // select pivot as the median-of-three taken pseudo-randomly
  i = pivot() % (r+1) + 0, EXCH(a[i],a[0  ]);
  i = pivot() % (r  ) + 1, EXCH(a[i],a[r  ]);
  i = pivot() % (r-1) + 1, EXCH(a[i],a[r-1]);
  SORT(a[0],a[r-1]);
  if ((ri = GCMP(a[r  ],a[0])) == Lesser) EXCH(a[r],a[0  ]);
  if ((rj = GCMP(a[r-1],a[r])) == Lesser) EXCH(a[r],a[r-1]);
//  else  if (GCMP(a[r-1],a[0])  == Lesser) EXCH(a[0],a[r-1]), EXCH(ri,rj);

  // partitioning initialization
  i = 0, j = r-1;
  p = ri == Equal ? i : -1;
  q = rj == Equal ? j :  r;

  // three-way partitioning
  for (;;) {
    while ((rj = GCMP(a[++i],a[  r])) == Lesser     ) ;
    while ((ri = GCMP(a[  r],a[--j])) == Lesser && j) ;

    if (i >= j) break;

    EXCH(a[i], a[j]);
    if (ri == Equal) ++p, EXCH(a[p],a[i]);
    if (rj == Equal) --q, EXCH(a[q],a[j]);
  }

  // move pivot to center
  EXCH(a[i], a[r]);

  // move equal partition from borders to center
  for (j = i-1; p-- > 0; j--) EXCH(a[p],a[j]);
  for (i = i+1; ++q < r; i++) EXCH(a[q],a[i]);

  // divide & conquer (small first)
  OBJ *s, *l;
  
  if (j < r-i)
    s = a, l = a+i, p = j, q = r-i;
  else
    l = a, s = a+i, q = j, p = r-i;

  quicksort_fct(s,p,fct);
  quicksort_fct(l,q,fct); // tail recursion
}

defmethod(OBJ, gsort, Array)
  quicksort_fct(self->object, self->size-1, gcompare);
  retmethod(_1);
endmethod

defmethod(OBJ, gsortBy, Array, Functor)
  quicksort_fun(self->object, self->size-1, _2);
  retmethod(_1);
endmethod

defmethod(OBJ, gsortBy, Array, Function2)
  quicksort_fct(self->object, self->size-1, self2->fct);
  retmethod(_1);
endmethod


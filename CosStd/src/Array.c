/*
 o---------------------------------------------------------------------o
 |
 | COS Array - basics
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
 | $Id: Array.c,v 1.31 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/View.h>

#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/init.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>
#include <cos/prp/sequence.h>

#include <stdlib.h>

// -----

makclass(Array        , Sequence);
makclass(Array0       , Array);
makclass(Array1       , Array);
makclass(Array2       , Array);
makclass(Array3       , Array);
makclass(Array4       , Array);
makclass(Array5       , Array);
makclass(Array6       , Array);
makclass(Array7       , Array);
makclass(Array8       , Array);
makclass(Array9       , Array);
makclass(ArrayN       , Array);
makclass(ArrayView    , Array);
makclass(ArrayDynamicN, Array);
makclass(ArrayDynamic , ArrayDynamicN);

// -----

useclass(Array, ExBadAlloc);

// ----- properties

#define size_to_OBJ(siz) gautoDelete(aInt(siz))
#define array_class(arr) Array

defproperty(Array    ,   size , size_to_OBJ);
defproperty(Array    , ()class, array_class);
defproperty(Array    , ()array, (OBJ)); // return (OBJ)self
defproperty(ArrayView,   array, (OBJ)); // return (OBJ)self->array

#undef size_to_OBJ
#undef array_class

// ---

defmethod(struct Slice, gslice, Array)
  retmethod( *atSlice(0,self->size,self->stride) );
endmethod

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, gisEmpty, Array)
  retmethod(self->size ? False : True);
endmethod

defmethod(OBJ, gclass, Array)
  retmethod(Array); // class cluster: hide implementation details
endmethod

// ----- initializers

struct Array*
ArrayView_init(struct ArrayView *view, struct Array *arr, struct Slice *slc)
{
  test_assert( !cos_object_isa((OBJ)arr, classref(ArrayDynamic)),
               "ArrayView accepts only non-dynamic Array" );

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < arr->size &&
               last  < arr->size, "slice out of range" );

  struct Array* avw = &view->Array;

  avw->object = Slice_start (slc)*arr->stride + arr->object;
  avw->size   = Slice_size  (slc);
  avw->stride = Slice_stride(slc)*arr->stride;
  view->array = arr;

  return avw;
}

// ----- allocators

struct Array*
Array_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[N] = {
    classref(Array0,Array1,Array2,Array3,Array4,
             Array5,Array6,Array7,Array8,Array9)
  };

  useclass(ArrayN);

  OBJ _cls = size >= N ? ArrayN : (OBJ)cls[size];
  OBJ _arr = gallocWithSize(_cls, size * sizeof(OBJ));

  struct ArrayN *arrn = STATIC_CAST(struct ArrayN*, _arr);
  struct Array  *arr  = &arrn->Array;

  arr->object = arrn->_object;
  arr->size   = size;
  arr->stride = 1;

  return arr;
}

struct Array*
ArrayDynamic_alloc(U32 size)
{
  useclass(ArrayDynamic);

  OBJ _arrd = galloc(ArrayDynamic); PRT(_arrd);

  struct ArrayDynamic  *arrd = STATIC_CAST(struct ArrayDynamic*, _arrd);
  struct ArrayDynamicN *arrn = &arrd->ArrayDynamicN;
  struct Array         *arr  = &arrn->Array;

  arr->object = malloc(size * sizeof *arr->object);
  if (!arr->object) THROW(ExBadAlloc);

  arr->size      = 0;
  arr->stride    = 1;
  arrn->_object  = arr->object;
  arrd->capacity = size;

  UNPRT(_arrd);
  return arr;
}

struct Array*
ArrayView_alloc(struct Array *ref, struct Slice *slc)
{
  useclass(ArrayView);

  OBJ _avw = galloc(ArrayView); PRT(_avw);
  OBJ _arr = gretain((OBJ)ref);

  struct ArrayView* avw = STATIC_CAST(struct ArrayView*, _avw);
  struct Array*     arr = STATIC_CAST(struct Array*    , _arr);

  ArrayView_init(avw, arr, slc);

  UNPRT(_avw);
  return &avw->Array;
}

// ----- constructors

defmethod(OBJ, galloc, pmArray) // lazy alloc
  retmethod(_1);
endmethod

defmethod(OBJ, ginit, pmArray) // dynamic array
  retmethod( (OBJ)ArrayDynamic_alloc(0) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Int) // dynamic array with capacity
  test_assert(self2->value >= 0, "negative array size");

  retmethod( (OBJ)ArrayDynamic_alloc(self2->value) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Array) // clone
  struct Array* arr = Array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + arr->size;
  OBJ *src   = self2->object;
  I32  src_s = self2->stride;

  while (dst != end) {
    *dst++ = gretain(*src);
    src += src_s;
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith, pmArray, Slice) // Int sequence
  U32 size = Slice_size(self2);

  struct Array* arr = Array_alloc(size);

  for (U32 i = 0; i < size; i++)
    arr->object[i] = gretain(aInt(Slice_eval(self2,i)));

  retmethod((OBJ)arr);
endmethod

defmethod(OBJ, ginitWith, pmArray, Range) // Int sequence
  U32 size = Range_size(self2);

  struct Array* arr = Array_alloc(size);

  for (U32 i = 0; i < size; i++)
    arr->object[i] = gretain(aInt(Range_eval(self2,i)));

  retmethod((OBJ)arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Int, Object) // element
  test_assert(self2->value >= 0, "negative array size");

  struct Array* arr = Array_alloc(self2->value);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst = arr->object;
  OBJ *end = arr->object + arr->size;
  
  while (dst != end)
    *dst++ = gretain(_3);

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Int, Functor) // generator
  test_assert(self2->value >= 0, "negative array size");

  struct Array* arr = Array_alloc(self2->value);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst = arr->object;
  OBJ *end = arr->object + arr->size;
  int argc = garity(_3);

  if (!argc)
    while (dst != end)
      *dst++ = gretain(geval(_3));

  else
    for (I32 i = 0; dst != end; i++)
      *dst++ = gretain(geval1(_3, aInt(i)));

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Array, Slice)  // sub array
  U32 first  = Slice_first (self3);
  U32 last   = Slice_last  (self3);
  U32 start  = Slice_first (self3)*self2->stride;
  I32 stride = Slice_stride(self3)*self2->stride;

  test_assert( first < self2->size &&
               last  < self2->size, "slice out of range" );

  struct Array* arr = Array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + arr->size;
  OBJ *src   = self2->object + start;
  I32  src_s = stride;

  while (dst != end) {
    *dst++ = gretain(*src);
    src += src_s;
  }
  
  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Array, IntVector) // random sequence
  struct Array* arr = Array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + arr->size;
  OBJ *src   = self2->object;
  U32  src_z = self2->size;
  I32  src_s = self2->stride;
  I32 *idx   = self3->value;
  I32  idx_s = self3->stride;

  while (dst != end) {
    U32 i = Range_index(*idx, src_z);
    test_assert( i < src_z, "index out of range" );
    *dst++ = gretain(src[i*src_s]);
    idx += idx_s;
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, mView, Array, Slice) // array view
  retmethod( (OBJ)ArrayView_alloc(self2, self3) );
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, Array)
  OBJ *obj = self->object;
  OBJ *end = self->object + self->size;

  while (obj != end && *obj) // take care of protection cases
    grelease(*obj++);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayDynamicN)
  next_method(self);
  free(self->_object);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayView)
  if (self->array) // take care of protection cases
    grelease( (OBJ)self->array );
  retmethod(_1);
endmethod

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

// ----- invariants

defmethod(void, ginvariant, Array, (STR)func, (STR)file, (int)line)
  OBJ *obj   = self->object;
  OBJ *end   = self->object + self->size*self->stride;
  I32  obj_s = self->stride;

  while (obj != end && *obj)
    obj += obj_s;

  test_assert( obj == end,
               "Array contains null elements", func, file, line);
endmethod

defmethod(void, ginvariant, ArrayDynamic, (STR)func, (STR)file, (int)line)
  test_assert( self->capacity >= self->ArrayDynamicN.Array.size,
               "ArrayDynamic has capacity < size", func, file, line);

  next_method(self, func, file, line);
endmethod

defmethod(void, ginvariant, ArrayView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf((OBJ)self->array, classref(Array)),
               "ArrayView points to something not an array", func, file, line);

  test_assert( !cos_object_isa((OBJ)self->array, classref(ArrayDynamic)),
               "ArrayView points to a dynamic array", func, file, line);

  struct Array *arr = STATIC_CAST(struct Array*, self->array);

  I32 start  = (arr->object - self->Array.object)/arr->stride;
  U32 size   = self->Array.size;
  I32 stride = self->Array.stride/arr->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < self->array->size && last < self->array->size,
               "ArrayView is out of range", func, file, line);

  next_method(self, func, file, line);
endmethod


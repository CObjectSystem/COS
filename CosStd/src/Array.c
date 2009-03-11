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
 | $Id: Array.c,v 1.28 2009/03/11 10:20:41 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/gen/init.h>
#include <cos/prp/object.h>

#include <stdlib.h>
#include <string.h>

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

// NOTE-TODO: TO REMOVE
makclass(Vector, ValueSequence);
makclass(IntVector, Vector);

// -----

useclass(Array, ExBadAlloc);

// ----- properties

#define size_to_OBJ(size) gautoRelease(aInt(size))
#define array_class(array) Array

defproperty(Array, size   , size_to_OBJ);
defproperty(Array, ()class, array_class);

#undef size_to_OBJ
#undef array_class

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, gisEmpty, Array)
  retmethod(self->size ? False : True);
endmethod

defmethod(OBJ, gclass, Array)
  retmethod(Array); // class cluster
endmethod

// ----- initializers

struct Array*
ArrayView_init(struct ArrayView *view, I32 idx)
{
//  test_assert( cos_object_isKindOf(view->array, classref(Array)),
//               "ArrayView accepts only arrays" );

  struct Array* arr = &view->Array;
  struct Array* ref =  view->array;

  U32 start  = index_abs(idx, ref->size);

  test_assert( start < ref->size && 
               start + arr->stride*(arr->size-1) < ref->size,
               "ArrayView out of range" );

  arr->stride *= ref->stride;
  arr->object  = ref->object + ref->stride * start;

  return arr;
}

struct Array*
ArraySubview_init(struct ArrayView *view, I32 idx)
{
//  test_assert( cos_object_isKindOf(view->array, classref(Array)),
//               "ArrayView accepts only arrays" );

  struct Array* arr = &view->Array;
  struct Array* ref =  view->array;

  U32 start  = index_abs(idx, ref->size);

  test_assert( start < ref->size && 
               start + arr->stride*(arr->size-1) <= ref->stride*(ref->size-1),
               "ArrayView out of range" );

  arr->object = ref->object + ref->stride * start;

  return arr;
}

// ----- allocators

defmethod(OBJ, galloc, pmArray) // lazy alloc
  retmethod(_1);
endmethod

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

  arr->size   = size;
  arr->stride = 1;
  arr->object = arrn->base;

  return arr;
}

struct Array*
ArrayView_alloc(struct Array *ref, U32 start, U32 size, U32 stride)
{
  useclass(ArrayView);

  OBJ _view = galloc(ArrayView); PRT(_view);
  OBJ _ref  = gretain((OBJ)ref);
  
  struct ArrayView *view = STATIC_CAST(struct ArrayView*, _view);
  struct Array     * arr = &view->Array;

  view->array  = _ref;
  arr ->size   = size;
  arr ->stride = stride;
  arr ->object = STATIC_CAST(struct Array*, _ref)->object + start;

  UNPRT(_view);
  return arr;
}

struct Array*
ArrayDynamic_alloc(U32 size)
{
  useclass(ArrayDynamic);

  OBJ _dyna = galloc(ArrayDynamic);

  struct ArrayDynamic  *dyna = STATIC_CAST(struct ArrayDynamic*, _dyna);
  struct ArrayDynamicN *dynn = &dyna->ArrayDynamicN;
  struct Array         * arr = &dynn->Array;

  dynn->base = malloc(size * sizeof *dynn->base);
  
  if (!dynn->base) {
    gdealloc(_dyna);
    THROW(ExBadAlloc);
  }

  dyna->capacity = size;
  arr ->size     = 0;
  arr ->object   = dynn->base;

  return arr;
}

// ----- constructors

defmethod(OBJ, ginit, pmArray) // dynamic array
  retmethod( (OBJ)ArrayDynamic_alloc(0) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Int) // dynarray with capacity
  test_assert(self2->value >= 0, "negative array size");

  retmethod( (OBJ)ArrayDynamic_alloc(self2->value) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Array) // clone
  struct Array* arr = Array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object;

  while (obj < end)
    *obj++ = gretain(*src++);

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Int, Object) // element
  test_assert(self2->value >= 0, "negative array size");

  struct Array* arr = Array_alloc(self2->value);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr->object;
  OBJ *end = arr->object+arr->size;
  
  while (obj < end)
    *obj++ = gretain(_3);

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Int, Functor) // generator
  test_assert(self2->value >= 0, "negative array size");

  struct Array* arr = Array_alloc(self2->value);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr->object;
  OBJ *end = arr->object+arr->size;
  int argc = garity(_3);

  if (argc)
    for (I32 i = 0; obj < end; i++)
      *obj++ = gretain(geval1(_3, aInt(i)));

  else
    while (obj < end)
      *obj++ = gretain(geval (_3));

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Array, Slice)  // sub array
  test_assert( Slice_first(self3) < self2->size
            && Slice_last (self3) < self2->size, "slice out of range" );

  struct Array* arr = Array_alloc(self3->size);
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

defmethod(OBJ, ginitWith2, pmArray, Array, IntVector) // sequence
  struct Array* arr = Array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object;
  U32 size = self2->size;
  I32 *idx = self3->value;

  while (obj < end) {
    U32 i = index_abs(*idx++, size);
    test_assert( i < size, "index out of range" );
    *obj++ = gretain(src[i]);
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWithObjPtr, pmArray, (OBJ*)obj, (U32)n) // clone buffer
  retmethod( ginitWith(_1, aArrayRef(obj,n)) );
endmethod

defmethod(OBJ, ginitWith2, pmView, Array, Slice) // array view
  test_assert( !cos_object_isa(_2, classref(ArrayDynamic)),
               "ArrayView accepts only fixed size Array" );
  test_assert( Slice_first(self3) < self2->size
            && Slice_last (self3) < self2->size, "ArrayView slice out of range" );

  retmethod( (OBJ)ArrayView_alloc(self2, self3->start, self3->size, self3->stride) );
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, Array)
  OBJ *obj = self1->object;
  OBJ *end = self1->object+self1->size;

  while (obj < end && *obj) // take care of protection cases
    grelease(*obj++);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayView)
  if (self->array) // take care of protection cases
    grelease(self->array);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayDynamicN)
  next_method(self);
  free(self->base);
  retmethod(_1);
endmethod

// ----- invariants

defmethod(void, ginvariant, Array, (STR)func, (STR)file, (int)line)
  OBJ *obj = self->object;
  OBJ *end = self->object+self->size;

  while (obj < end && *obj) ;

  test_assert( obj == end,
               "Array contains null elements", func, file, line);
endmethod

defmethod(void, ginvariant, ArrayView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf(self->array, classref(Array)),
               "ArrayView points to something not an array", func, file, line);
  test_assert( !cos_object_isa(self->array, classref(ArrayDynamic)),
               "ArrayView points to a dynamic array", func, file, line);

  struct Array *arr = STATIC_CAST(struct Array*, self->array);

  test_assert( self->Array.object                  >= arr->object &&
               self->Array.object+self->Array.size <= arr->object+arr->size,
               "ArrayView is out of range", func, file, line);
  next_method(self, func, file, line);
endmethod

defmethod(void, ginvariant, ArrayDynamic, (STR)func, (STR)file, (int)line)
  test_assert( self->capacity >= self->ArrayDynamicN.Array.size,
               "ArrayDynamic has capacity < size", func, file, line);
  next_method(self, func, file, line);
endmethod


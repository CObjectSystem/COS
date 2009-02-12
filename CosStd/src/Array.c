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
 | $Id: Array.c,v 1.24 2009/02/12 11:06:02 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/Slice.h>
#include <cos/Vector.h>
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
makclass(DynamicArrayN, Array);
makclass(DynamicArray , DynamicArrayN);

// NOTE-TODO: TO REMOVE
makclass(Vector, ValueSequence);
makclass(IntVector, Vector);

// -----

useclass(Array, ExBadAlloc);

// ----- properties

#define size_to_OBJ(size) gautoRelease(aInt(size))

defproperty(Array, size, size_to_OBJ);

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, gisEmpty, Array)
  retmethod(self->size ? False : True);
endmethod

// ----- allocators and initializers

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
  arr->object = arrn->base;

  return arr;
}

struct Array*
Array_init(struct Array *arr)
{
  test_assert( arr->object, "Array got null pointer as buffer" );
  return arr;
}

struct Array*
ArrayView_alloc(struct Array *ref, U32 start, U32 size)
{
  useclass(ArrayView);

  OBJ _view = galloc(ArrayView); PRT(_view);
  OBJ _ref  = gretain((OBJ)ref);
  
  struct ArrayView *view = STATIC_CAST(struct ArrayView*, _view);
  struct Array     * arr = &view->Array;

  view->array  = _ref;
  arr ->size   = size;
  arr ->object = STATIC_CAST(struct Array*, _ref)->object + start;

  UNPRT(_view);
  return arr;
}

struct Array*
ArrayView_init(struct ArrayView *view, I32 idx)
{
  test_assert( cos_any_isKindOf(view->array, classref(Array)),
               "ArrayView accepts only arrays" );
  test_assert( !cos_any_isa(view->array, classref(DynamicArray)),
               "ArrayView accepts only fixed size array" );

  struct Array* arr = &view->Array;
  struct Array* ref = STATIC_CAST(struct Array*, view->array);

  U32 start = index_abs(idx, ref->size);
  
  test_assert( start + arr->size <= ref->size,
               "ArrayView out of range" );

  arr->object = ref->object + start;

  return arr;
}

struct Array*
DynamicArray_alloc(U32 size)
{
  useclass(DynamicArray);

  OBJ _dyna = galloc(DynamicArray);

  struct DynamicArray  *dyna = STATIC_CAST(struct DynamicArray*, _dyna);
  struct DynamicArrayN *dynn = &dyna->DynamicArrayN;
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
  retmethod( (OBJ)DynamicArray_alloc(0) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Int) // dynarray with capacity
  test_assert(self2->value >= 0, "negative array size");

  retmethod( (OBJ)DynamicArray_alloc(self2->value) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Array) // clone
  struct Array* arr = Array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  _arr = ginitWith(_arr,_2);
  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith, Array, Array) // copy
  test_assert( self1->size <= self2->size, "incompatible array sizes");

  OBJ *obj = self1->object;
  OBJ *end = self1->object+self1->size;
  OBJ *src = self2->object;

  while (obj < end)
    *obj++ = gretain(*src++);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Int, Any) // element
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
  int argc = gsize(_3);

  if (argc)
    for (I32 i = 0; obj < end; i++)
      *obj++ = gretain(geval1(_3, aInt(i)));

  else
    while (obj < end)
      *obj++ = gretain(geval (_3));

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, pmArray, Array, Slice1)  // sub array
  test_assert( self3->start < self2->size && Slice1_last(self3) < self2->size,
               "slice out of range" );

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

defmethod(OBJ, ginitWith2, pmView, Array, Slice1) // array view
  test_assert( !cos_any_isa(_2, classref(DynamicArray)),
               "ArrayView accepts only fixed size Array" );
  test_assert( Slice1_iscontiguous(self3),
               "ArrayView slice must be contiguous");
  test_assert( Slice1_last(self3) < self2->size,
               "ArrayView slice out of range" );

  retmethod( (OBJ)ArrayView_alloc(self2, self3->start, self3->size) );
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

defmethod(OBJ, gdeinit, DynamicArrayN)
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
  test_assert( cos_any_isKindOf(self->array, classref(Array)),
               "ArrayView points to something not an array", func, file, line);
  test_assert( !cos_any_isa(self->array, classref(DynamicArray)),
               "ArrayView points to a dynamic array", func, file, line);

  struct Array *arr = STATIC_CAST(struct Array*, self->array);

  test_assert( self->Array.object                  >= arr->object &&
               self->Array.object+self->Array.size <= arr->object+arr->size,
               "ArrayView is out of range", func, file, line);
  next_method(self, func, file, line);
endmethod

defmethod(void, ginvariant, DynamicArray, (STR)func, (STR)file, (int)line)
  test_assert( self->capacity >= self->DynamicArrayN.Array.size,
               "DynamicArray has capacity < size", func, file, line);
  next_method(self, func, file, line);
endmethod


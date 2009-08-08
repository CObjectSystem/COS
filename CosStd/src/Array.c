/*
 o---------------------------------------------------------------------o
 |
 | COS Array - ctors & dtors
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
 | $Id: Array.c,v 1.32 2009/08/08 16:36:09 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/View.h>

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

makclass(Array    , Sequence);
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
makclass(ArrayView, Array);
makclass(ArrayAdj , Array);
makclass(ArrayDyn , ArrayAdj);
makclass(ArrayLazy, ArrayDyn);

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

defmethod(OBJ*, gobjPtr, Array)
  retmethod(self->object);
endmethod

defmethod(OBJ, gisEmpty, Array)
  retmethod(self->size ? False : True);
endmethod

defmethod(OBJ, gclass, Array)
  retmethod(Array); // class cluster: hide implementation details
endmethod

// ----- initializers

struct Array*
Array_init(struct Array *arr, U32 size)
{
  arr->size   = size;
  arr->stride = 1;

  return arr;
}

struct Array*
ArrayView_init(struct ArrayView *arrv, struct Array *arr, struct Slice *slc)
{
  OBJ _arrv = (OBJ)arrv; PRT(_arrv);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < arr->size &&
               last  < arr->size, "slice out of range" );

  struct Array* avw = &arrv->Array;

  avw->object = Slice_start (slc)*arr->stride + arr->object;
  avw->size   = Slice_size  (slc);
  avw->stride = Slice_stride(slc)*arr->stride;
  arrv->array = arr;

  UNPRT(_arrv);
  return avw;
}

struct Array*
ArrayDyn_init(struct ArrayDyn *arrd, U32 size)
{
  OBJ _arrd = (OBJ)arrd; PRT(_arrd);

  struct ArrayAdj *arrn = &arrd->ArrayAdj;
  struct Array    *arr  = &arrn->Array;

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
ArrayLazy_init(struct ArrayLazy *arrl, U32 size, struct Functor *fun)
{
  ArrayDyn_init(&arrl->ArrayDyn, size);

  arrl->generator = (OBJ)fun;

  return &arrl->ArrayDyn.ArrayAdj.Array;
}

// ----- allocators

struct Array*
Array_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[] = {
    classref(Array0,Array1,Array2,Array3,Array4,
             Array5,Array6,Array7,Array8,Array9,
             ArrayN)
  };

  OBJ _cls = (OBJ)cls[size > N ? N : size];
  OBJ _arr = gallocWithSize(_cls, size * sizeof(OBJ));

  struct ArrayN *arrn = STATIC_CAST(struct ArrayN*, _arr);
  struct Array  *arr  = &arrn->Array;

  arr->object = arrn->_object;

  return Array_init(arr, size);
}

struct Array*
ArrayView_alloc(struct Array *arr, struct Slice *slc)
{
  useclass(ArrayView);

  return ArrayView_init( STATIC_CAST(struct ArrayView*, galloc(ArrayView)), arr, slc );
}

struct Array*
ArrayDyn_alloc(U32 size)
{
  useclass(ArrayDyn);

  return ArrayDyn_init( STATIC_CAST(struct ArrayDyn*, galloc(ArrayDyn)), size );
}

struct Array*
ArrayLazy_alloc(U32 size, struct Functor *fun)
{
  useclass(ArrayLazy);

  return ArrayLazy_init( STATIC_CAST(struct ArrayLazy*, galloc(ArrayLazy)), size, fun );
}

// ----- constructors

defmethod(OBJ, galloc, pmArray) // lazy alloc
  retmethod(_1);
endmethod

defmethod(OBJ, ginit, pmArray) // Dyn array
  retmethod( (OBJ)ArrayDyn_alloc(0) );
endmethod

defmethod(OBJ, ginitWith, pmArray, Int) // Dyn array with capacity
  test_assert(self2->value >= 0, "negative array size");

  retmethod( (OBJ)ArrayDyn_alloc(self2->value) );
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
  test_assert( !cos_object_isa(_2, classref(ArrayDyn))
            && !cos_object_isa(_2, classref(ArrayLazy   )),
               "Array views accept only non-Dyn arrays" );

  retmethod( (OBJ)ArrayView_alloc( STATIC_CAST(struct Array*, gretain(_2)), self3 ) );
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, Array)
  OBJ *obj = self->object;
  OBJ *end = self->object + self->size;

  while (obj != end && *obj)    // take care of protection cases
    grelease(*obj++);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayAdj)
  if (self->_object)            // take care of protection cases
    free(self->_object);
  next_method(self);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayLazy)
  if (self->generator)          // take care of protection cases
    grelease(self->generator);
  next_method(self);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ArrayView)
  if (self->array)              // take care of protection cases
    grelease( (OBJ)self->array );
  retmethod(_1);
endmethod


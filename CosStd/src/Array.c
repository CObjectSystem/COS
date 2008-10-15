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
 | $Id: Array.c,v 1.2 2008/10/15 19:18:06 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Array.h>
#include <cos/Size.h>
#include <cos/Index.h>
#include <cos/Range.h>
#include <cos/Slice.h>
#include <cos/Vector.h>
#include <cos/Functor.h>
#include <cos/gen/init.h>
#include <cos/gen/access.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>
#include <cos/gen/value.h>

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

// ----- local allocators

static inline struct Array*
array_alloc(U32 size)
{
  enum { N = 10 };
  static const OBJ cls[N] = {
    classref(Array0,Array1,Array2,Array3,Array4),
    classref(Array5,Array6,Array7,Array8,Array9) }; 

  useclass(ArrayN);

  OBJ _cl  = size >= N ? ArrayN : cls[size];
  OBJ _arr = gallocWithSize(_cl, size * sizeof(OBJ));
  struct ArrayN *narr = STATIC_CAST(struct ArrayN*, _arr);
  struct Array  * arr = &narr->Array;

  arr->size   = size;
  arr->object = narr->_object;

  return arr;
}

static inline struct Array*
subarray_alloc(struct Array *ref, U32 start, U32 size)
{
  useclass(SubArray);

  OBJ _arr = gallocWithSize(SubArray, 0);
  struct SubArray *sarr = STATIC_CAST(struct SubArray*, _arr);
  struct Array    * arr = &sarr->Array;

  arr->size   = size;
  arr->object = ref->object + start;
  sarr->array = (OBJ)ref;

  return arr;
}

static inline struct Array*
dynarray_alloc(U32 size)
{
  useclass(DynArray, ExBadAlloc);

  OBJ _arr = gallocWithSize(DynArray, 0);
  struct DynArray *darr = STATIC_CAST(struct DynArray*, _arr);
  struct Array    * arr = &darr->DynArrayN.Array;

  arr->object = malloc(size * sizeof *arr->object);
  if (!arr->object) THROW(ExBadAlloc);
  darr->capacity = size;

  return arr;
}

static void
dynarray_resizeBy(struct DynArray *darr, double factor)
{
  useclass(ExBadAlloc);

  struct Array *arr = &darr->DynArrayN.Array;
  U32  size = darr->capacity * factor;
  OBJ *object = realloc(arr->object, size * sizeof *arr->object);

  if (!object) THROW(ExBadAlloc);
  arr->object = object;
  darr->capacity = size;
}

// ----- ctor/dtor of a array

defmethod(OBJ, galloc, mArray)
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, mArray, Size1)
  retmethod( (OBJ)array_alloc(self2->size) );
endmethod

defmethod(OBJ, ginitWith, mArray, Array) // clone
  retmethod( ginitWith((OBJ)array_alloc(self2->size),_2) );
endmethod

defmethod(OBJ, ginitWith, Array, Array) // copy
  test_assert(self->size == self2->size);

  for (U32 i = 0; i < self->size; i++) {
    OBJ obj = self2->object[i];
    if (obj) self->object[i] = gclone(obj);
  }
  
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mArray, Any, Size1)
  struct Array* arr = array_alloc(self3->size);

  for (U32 i = 0; i < arr->size; i++)
    arr->object[i] = gclone(_2);

  retmethod((OBJ)arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);

  retmethod( ginitWith2(_1,_2,s) );  
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, Slice1)
  struct Array* arr = array_alloc(self3->size);

  test_assert( self3->start < self2->size && Slice1_last(self3) < self2->size );

  for (U32 i = 0; i < arr->size; i++) {
    OBJ obj = self2->object[ Slice1_eval(self3,i) ];
    if (obj) arr->object[i] = gclone(obj);
  }
  
  retmethod((OBJ)arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, IntVector)
  struct Array* arr = array_alloc(self3->size);

  for (U32 i = 0; i < arr->size; i++) {
    U32 j = index_abs(self3->value[i], self2->size);
    test_assert( j < self2->size );
    OBJ obj = self2->object[j];
    if (obj) arr->object[i] = gclone(obj);
  }

  retmethod((OBJ)arr);
endmethod

defmethod(OBJ, ginitWithObjPtr, mArray, (U32)n, (OBJ*)obj)
  retmethod( ginitWith(_1, aArrRef(n,obj)) );
endmethod

defmethod(OBJ, gdeinit, Array)
  for (U32 i = 0; i < self->size; i++) {
    OBJ obj = self->object[i];
    if (obj) grelease(obj);
  }
  retmethod(_1);
endmethod

// ----- ctor/dtor of a dynamic array

defmethod(OBJ, ginit, mDynArray)
  retmethod( (OBJ)dynarray_alloc(10) );
endmethod

defmethod(OBJ, ginitWith, mDynArray, Size1)
  retmethod( (OBJ)dynarray_alloc(self2->size) );
endmethod

defmethod(OBJ, gdeinit, DynArrayN)
  next_method(self);
  free(self->Array.object);
  retmethod(_1);
endmethod

// ----- ctor/dtor of a subarray

defmethod(OBJ, ginitWith2, mSubArray, Array, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);

  retmethod( ginitWith2(_1,_2,s) );
endmethod

defmethod(OBJ, ginitWith2, mSubArray, Array, Slice1)
  OBJ arr_ = gretain(_2);
  OBJ arr_spr = (OBJ)cos_class_get(cos_any_id(arr_))->spr;
  struct Array *arr = STATIC_CAST(struct Array*, arr_);

  test_assert( arr_spr == Array );
  test_assert( Slice1_iscontiguous(self3) && Slice1_last(self3) < self2->size );

  retmethod( (OBJ)subarray_alloc(arr, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, SubArray)
  if (self->array) grelease(self->array);
  retmethod(_1);
endmethod
 
// ----- equality

defmethod(OBJ, gequal, Array, Array)
  BOOL res = self->size == self2->size;

  for (U32 i = 0; res && i < self->size; i++)
    res = gequal(self->object[i], self2->object[i]) == True;

  retmethod( res ? True : False );
endmethod

// ----- setters

defmethod(OBJ, gput, Array, Array)
  test_assert(self->size == self2->size);

  for (U32 i = 0; i < self->size; i++) {
    OBJ old = self1->object[i];
    OBJ new = self2->object[i];

    self->object[i] = new ? gretain(new) : 0;
    if (old) grelease(old);
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Any, Index1)
  U32 i = index_abs(self3->index, self->size);

  test_assert( i < self->size );
  
  OBJ old = self->object[i];
  
  self->object[i] = gretain(_2);
  if (old) grelease(old);
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, Index1)
  U32 i = index_abs(self3->index, self->size);

  test_assert( i+self2->size <= self->size );

  for (U32 j = 0; j < self2->size; i++, j++) {
    OBJ old = self1->object[i];
    OBJ new = self2->object[j];

    self->object[i] = new ? gretain(new) : 0;
    if (old) grelease(old);
  }
  
  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self->size);

  retmethod( gputAt(_1,_2,s) );  
endmethod

defmethod(OBJ, gputAt, Array, Array, Slice1)
  test_assert( self3->start < self->size && Slice1_last(self3) < self->size );

  for (U32 j = 0; j < self3->size; j++) {
    U32 i   = Slice1_eval(self3,j);
    OBJ old = self1->object[i];
    OBJ new = self2->object[j];

    self->object[i] = new ? gretain(new) : 0;
    if (old) grelease(old);
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, IntVector)
  for (U32 j = 0; j < self3->size; j++) {
    U32 i = index_abs(self3->value[j], self->size);
    test_assert( i < self->size );
    OBJ old = self1->object[i];
    OBJ new = self2->object[j];

    self->object[i] = new ? gretain(new) : 0;
    if (old) grelease(old);
  }

  retmethod(_1);  
endmethod

// ----- getter

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, ggetAt, Array, Index1)
  U32 i = index_abs(self2->index, self->size);
  test_assert( i < self->size );
  retmethod( self->object[i] );
endmethod

defmethod(OBJ, ggetAt, Array, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self2, self->size);

  retmethod( ggetAt(_1,s) );
endmethod

defmethod(OBJ, ggetAt, Array, Slice1)
  retmethod( gautoRelease( gputAt((OBJ)array_alloc(self2->size),_1,_2) ) );
endmethod

defmethod(OBJ, ggetAt, Array, IntVector)
  retmethod( gautoRelease( gputAt((OBJ)array_alloc(self2->size),_1,_2) ) );
endmethod

// ----- stack-like accessors and adjustment

defalias (OBJ, (gpush)gconcat, DynArray, Any);
defmethod(OBJ,  gpush        , DynArray, Any)
  struct Array *arr = &self->DynArrayN.Array;

  if (arr->size == self->capacity)
    dynarray_resizeBy(self, 1.75);
    
  arr->object[arr->size++] = gretain(_2);
  retmethod(_1);
endmethod

defalias (OBJ, (gtop)glast, DynArray);
defmethod(OBJ,  gtop      , DynArray)
  struct Array *arr = &self->DynArrayN.Array;

  if (!arr->size) retmethod(0);
  retmethod( arr->object[arr->size-1] );
endmethod

defmethod(OBJ, gpop, DynArray)
  struct Array *arr = &self->DynArrayN.Array;

  if (!arr->size) retmethod(False);
  grelease(arr->object[--arr->size]);
  retmethod(True);
endmethod

defmethod(OBJ, gconcat, DynArray, Array)
  struct Array *arr = &self->DynArrayN.Array;

  if (self->capacity - arr->size < self2->size) {
    double size = arr->size;

    do size *= 1.75;
    while (self->capacity - size < self2->size);

    dynarray_resizeBy(self, size);
  }

  for (U32 i = 0; i < self2->size; i++) {
    OBJ obj = self2->object[i];
    arr->object[arr->size++] = obj ? gretain(obj) : obj;
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gadjust, DynArray)
  struct Class *cls = &COS_CLS_NAME(DynArrayN);

  if (self->DynArrayN.Array.size < self->capacity)
    dynarray_resizeBy(self, 1.0);

  test_assert( cos_any_changeClass(_1, cls) );

  retmethod(_1);
endmethod

// ----- map, fold, ...

defmethod(void, gapply, Array, Functor)
  for (U32 i = 0; i < self->size; i++) {
    OBJ old = self->object[i];
    if (old) {
      OBJ new = geval1(_2, old);
      if (new != old) {
        self->object[i] = new ? gretain(new) : 0;
        grelease(old);
      }
    }
  }
endmethod

defmethod(OBJ, gmap, Array, Functor)
  struct Array* arr = array_alloc(self->size);

  for (U32 i = 0; i < arr->size; i++) {
    OBJ old = self->object[i];
    if (old) {
      OBJ new = geval1(_2, old);
      if (new) arr->object[i] = gretain(new);
    }
  }

  retmethod( gautoRelease((OBJ)arr) );
endmethod

defmethod(OBJ, gmap2, Array, Array, Functor)
  test_assert(self1->size == self2->size);

  struct Array* arr = array_alloc(self->size);

  for (U32 i = 0; i < arr->size; i++) {
    OBJ old1 = self1->object[i];
    OBJ old2 = self2->object[i];
    if (old1 && old2) {
      OBJ new = geval2(_3, old1,old2);
      if (new) arr->object[i] = gretain(new);
    }
  }

  retmethod( gautoRelease((OBJ)arr) );
endmethod

defmethod(OBJ, gmap3, Array, Array, Array, Functor)
  test_assert(self1->size == self2->size && self1->size == self3->size);

  struct Array* arr = array_alloc(self->size);

  for (U32 i = 0; i < arr->size; i++) {
    OBJ old1 = self1->object[i];
    OBJ old2 = self2->object[i];
    OBJ old3 = self3->object[i];
    if (old1 && old2 && old3) {
      OBJ new = geval3(_4, old1,old2,old3);
      if (new) arr->object[i] = gretain(new);
    }
  }

  retmethod( gautoRelease((OBJ)arr) );
endmethod

#define COS_TRACE_METHOD

defmethod(OBJ, gfilter, Array, Functor)
  struct Array* arr = dynarray_alloc(self->size);

  for (U32 i = 0; i < arr->size; i++) {
    OBJ obj = self->object[i];
    if (obj && geval1(_2, obj) == True)
      arr->object[arr->size++] = gretain(obj);
  }

  retmethod( gautoRelease(gadjust((OBJ)arr)) );
endmethod

defmethod(OBJ, gfold, Array, Any, Functor)
  OBJ res = _2;
  
  for (U32 i = 0; i < self->size; i++) {
    OBJ obj = self->object[i];
    if (obj) res = geval2(_3, res,obj);
  }

  retmethod(res);
endmethod

#undef COS_TRACE_METHOD

/*
defmethod(OBJ, gscan, Array, Any, Functor)
  struct Array* arr = array_alloc(self->size);
  // TODO

  for (U32 i = 0; i < arr->size; i++) {
    OBJ obj = self->object[i];
    if (old) {
      OBJ new = geval1(_3, old);
      if (new) arr->object[i] = gretain(new);
    }
  }

  retmethod( gautoRelease((OBJ)arr) );
endmethod
*/

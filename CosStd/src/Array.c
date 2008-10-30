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
 | $Id: Array.c,v 1.13 2008/10/30 10:19:40 ldeniau Exp $
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

defmethod(OBJ, ginitWith, mArray, Size1)
  retmethod( (OBJ)dynarray_alloc(self2->size) );
endmethod

defmethod(OBJ, ginitWith, mArray, Array) // clone
  retmethod( ginitWith((OBJ)array_alloc(self2->size),_2) );
endmethod

defmethod(OBJ, ginitWith, Array, Array) // copy
  test_assert(self->size <= self2->size);

  for (U32 i = 0; i < self->size; i++)
    self->object[i] = gretain(self2->object[i]);
  
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mArray, Any, Size1) // generator
  struct Array* arr = array_alloc(self3->size);
  OBJ _arr = (OBJ)arr;
  
  for (U32 i = 0; i < arr->size; i++)
    arr->object[i] = gretain(_2);

  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);
  retmethod( ginitWith2(_1,_2,s) );  
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, Slice1)
  test_assert( self3->start < self2->size && Slice1_last(self3) < self2->size );
  struct Array* arr = array_alloc(self3->size);

  for (U32 i = 0; i < arr->size; i++) {
    OBJ obj = self2->object[ Slice1_eval(self3,i) ];
    arr->object[i] = gretain(obj);
  }
  
  retmethod((OBJ)arr);
endmethod

defmethod(OBJ, ginitWith2, mArray, Array, IntVector)
  struct Array* arr = array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < arr->size; i++) {
    U32 j = index_abs(self3->value[i], self2->size);
    test_assert( j < self2->size );
    arr->object[i] = gretain(self2->object[j]);
  }

  UNPRT(_arr);
  retmethod(_arr);
endmethod

defmethod(OBJ, ginitWithObjPtr, mArray, (U32)n, (OBJ*)obj)
  retmethod( ginitWith(_1, aArrayRef(n,obj)) ); // clone
endmethod

defmethod(OBJ, gdeinit, Array)
  for (U32 i = 0; i < self->size; i++) {
    OBJ obj = self->object[i];
    if (obj) grelease(obj); // check obj because of PRT
  }

  retmethod(_1);
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
  struct Array *arr = STATIC_CAST(struct Array*, gretain(_2));
  OBJ _arr = (OBJ)arr; 
 
  test_assert( cos_any_isa(_arr, classref(DynArray)) );
  test_assert( Slice1_iscontiguous(self3) && Slice1_last(self3) < self2->size );

  retmethod( (OBJ)subarray_alloc(arr, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, SubArray)
  grelease(self->array);
  retmethod(_1);
endmethod
 
// ----- setters

defmethod(OBJ, gputAt, Array, Any, Index1)
  U32 i = index_abs(self3->index, self->size);

  test_assert( i < self->size );
  OBJ old = self->object[i];
  self->object[i] = gretain(_2);
  grelease(old);
  
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
    U32 i = Slice1_eval(self3,j);
    OBJ old = self->object[i];
    self->object[i] = gretain(self2->object[j]);
    grelease(old);
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, IntVector)
  for (U32 j = 0; j < self3->size; j++) {
    U32 i = index_abs(self3->value[j], self->size);
    test_assert( i < self->size );
    OBJ old = self->object[i];
    self->object[i] = gretain(self2->object[j]);
    grelease(old);
  }

  retmethod(_1);  
endmethod

// ----- getters

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ, ggetAt, Array, Index1)
  U32 i = index_abs(self2->index, self->size);
  test_assert( i < self->size );
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
defalias (OBJ, (gput)gconcat, DynArray, Any);
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
  retmethod( arr->size ? arr->object[arr->size-1] : Nil );
endmethod

defalias (OBJ, (gdrop)gpop, DynArray);
defmethod(OBJ,  gdrop     , DynArray)
  struct Array *arr = &self->DynArrayN.Array;
  retmethod(arr->size ? grelease(arr->object[--arr->size]) : Nil);
endmethod

defmethod(OBJ, gadjust, DynArray)
  if (self->DynArrayN.Array.size < self->capacity)
    dynarray_resizeBy(self, 1.0);

  test_assert( cos_any_changeClass(_1, classref(DynArrayN)) );

  retmethod(_1);
endmethod

// ----- concat

defmethod(OBJ,  gconcat, DynArray, Array)
  struct Array *arr = &self->DynArrayN.Array;

  if (self->capacity - arr->size < self2->size) {
    double size = arr->size;

    do size *= 1.8;
    while (self->capacity - size < self2->size);

    dynarray_resizeBy(self, size);
  }

  for (U32 i = 0; i < self2->size; i++)
    arr->object[arr->size++] = gretain(self2->object[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gconcat, Array, Array)
  struct Array *arr = array_alloc(self->size + self2->size);
  U32 i, j = 0;

  for (i = 0; i < self1->size; i++, j++)
    arr->object[j] = gretain(self1->object[i]);

  for (i = 0; i < self2->size; i++, j++)
    arr->object[j] = gretain(self2->object[i]);

  retmethod( gautoRelease((OBJ)arr) );
endmethod

// ----- apply

defmethod(void, gapply, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  while(obj < end) geval1(_1, *obj++);
endmethod

defmethod(void, gapply, Function1, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;
  OBJFCT1 fct = self->fct;

  while(obj < end) fct(*obj++);
endmethod

// ----- map, map2, map3, scan (Nil -> discard result)

defmethod(OBJ, gmap, Functor, Array)
  U32 size = self2->size;
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  struct Array* arr = array_alloc(size);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJ *res = arr->object;

  while(obj < end)
    *res++ = gretain( geval1(_1, *obj++) );

  retmethod(_arr);
endmethod

defmethod(OBJ, gmap, Function1, Array)
  U32 size = self2->size;
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  struct Array* arr = array_alloc(size);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJ *res = arr->object;
  
  OBJFCT1 fct = self->fct;

  while(obj < end)
    *res++ = gretain( fct(*obj++) );

  retmethod(_arr);
endmethod

defmethod(OBJ, gmap2, Functor, Array, Array)
  U32 s = self2->size < self3->size ? self2->size : self3->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = gautoRelease((OBJ)arr);

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval2(_1, self2->object[i], self3->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  retmethod(gadjust(_arr));
endmethod

defmethod(OBJ, gmap2, Function2, Array, Array)
  U32 s = self2->size < self3->size ? self2->size : self3->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJFCT2 fct = self->fct;

  for (U32 i = 0; i < s; i++) {
    OBJ res = fct(self2->object[i], self3->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  retmethod(gadjust(_arr));
endmethod

defmethod(OBJ, gmap3, Functor, Array, Array, Array)
  U32 s = self2->size < self3->size ? self2->size : self3->size;
  if (s > self4->size) s = self4->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = gautoRelease((OBJ)arr);

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval3(_1, self2->object[i], self3->object[i], self4->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  retmethod(gadjust(_arr));
endmethod

defmethod(OBJ, gmap3, Function3, Array, Array, Array)
  U32 s = self2->size < self3->size ? self2->size : self3->size;
  if (s > self4->size) s = self4->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJFCT3 fct = self->fct;

  for (U32 i = 0; i < s; i++) {
    OBJ res = fct(self2->object[i], self3->object[i], self4->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  retmethod(gadjust(_arr));
endmethod

defmethod(OBJ, gscan, Functor, Any, Array)
  struct Array* arr = dynarray_alloc(self3->size+1);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJ obj = _2;

  for (U32 i = 0; i < self3->size; i++) {
    OBJ res = geval2(_1, obj, self3->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(obj);
    obj = res;
  }
  arr->object[arr->size++] = gretain(obj);

  retmethod(gadjust(_arr));
endmethod

// ----- filter, fold, unfold (Nil -> stop iteration)

defmethod(OBJ, gfilter, Functor, Array)
  struct Array* arr = dynarray_alloc(self2->size);
  OBJ _arr = gautoRelease((OBJ)arr);

  for (U32 i = 0; i < self2->size; i++) {
    OBJ obj = self2->object[i];
    OBJ res = geval1(_1, obj);
    if (res == Nil ) break;
    if (res != True) continue;
    arr->object[arr->size++] = gretain(obj);
  }

  retmethod(gadjust(_arr));
endmethod

defmethod(OBJ, gfilter, Function1, Array)
  struct Array* arr = dynarray_alloc(self2->size);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJFCT1 fct = self->fct;

  for (U32 i = 0; i < self2->size; i++) {
    OBJ obj = self2->object[i];
    OBJ res = fct(obj);
    if (res == Nil ) break;
    if (res != True) continue;
    arr->object[arr->size++] = gretain(obj);
  }

  retmethod(gadjust(_arr));
endmethod

defmethod(OBJ, gfold, Functor, Any, Array)
  OBJ obj = _2;

  for (U32 i = 0; i < self3->size; i++) {
    OBJ res = geval2(_1, obj, self3->object[i]);
    if (res == Nil) break;
    obj = res;
  }

  retmethod(obj);
endmethod

defmethod(OBJ, gfold, Function2, Any, Array)
  OBJFCT2 fct = self->fct;
  OBJ obj = _2;

  for (U32 i = 0; i < self3->size; i++) {
    OBJ res = fct(obj, self3->object[i]);
    if (res == Nil) break;
    obj = res;
  }

  retmethod(obj);
endmethod

defmethod(OBJ, gunfold, Functor, Any)
  struct Array* arr = dynarray_alloc(10);
  OBJ _arr = gautoRelease((OBJ)arr);
  OBJ obj = _2;

  while (1) {
    OBJ res = geval1(_1, obj);
    if (res == Nil) break;
    arr->object[arr->size++] = gretain(obj);
    obj = res;
  }
  arr->object[arr->size++] = gretain(obj);

  retmethod(gadjust(_arr));
endmethod

// ----- sorting

defmethod(OBJ, gsort, Functor, Array)
  struct Array* arr = array_alloc(self2->size);
  OBJ _arr = gautoRelease((OBJ)arr);
  // TODO
  
  retmethod(_arr);
endmethod

// ----- finding

defmethod(OBJ, gfind, Functor, Any, Array)
  useclass(Lesser, Equal, Greater, ExBadPredicate);

  if (self3->size == 0)
    retmethod(Nil);

  OBJ res = geval2(_1, _2, self3->object[0]);

  if (res == True || res == Equal) // found
    retmethod(self3->object[0]);

  if (res == False) { // linear search
    for (U32 i = 1; i < self3->size; i++) {
      res = geval2(_1, _2, self3->object[i]);

      if (res == True)
        retmethod(self3->object[i]); // found
    }
    retmethod(Nil);
  }

  if (res == Lesser || res == Greater) { // binary search
    U32 low = 1, high = self3->size-1;
    
    while(low <= high) {
      U32 i = low + (high-low) / 2;
      res = geval2(_1, _2, self3->object[i]);

      if (res == Equal)
        retmethod(self3->object[i]); // found

      if (res == Lesser)
        high = i-1;
      else
        low = i+1;
    }
    retmethod(Nil);  
  }
  
  THROW( gnewWithStr(ExBadPredicate,
           "gfind expect True/False or Lesser/Equal/Greater predicates") );
endmethod

defmethod(OBJ, gfind, Function2, Any, Array)
  useclass(Lesser, Equal, Greater, ExBadPredicate);
  OBJFCT2 fct = self->fct;

  if (self3->size == 0)
    retmethod(Nil);

  OBJ res = geval2(_1, _2, self3->object[0]);

  if (res == True || res == Equal) // found
    retmethod(self3->object[0]);

  if (res == False) { // linear search
    for (U32 i = 1; i < self3->size; i++) {
      res = fct(_2, self3->object[i]);

      if (res == True)
        retmethod(self3->object[i]); // found
    }
    retmethod(Nil);
  }

  if (res == Lesser || res == Greater) { // binary search
    U32 low = 1, high = self3->size-1;
    
    while(low <= high) {
      U32 i = low + (high-low) / 2;
      res = fct(_2, self3->object[i]);

      if (res == Equal)
        retmethod(self3->object[i]); // found

      if (res == Lesser)
        high = i-1;
      else
        low = i+1;
    }
    retmethod(Nil);  
  }
  
  THROW( gnewWithStr(ExBadPredicate,
           "gfind expect True/False or Lesser/Equal/Greater predicates") );
endmethod


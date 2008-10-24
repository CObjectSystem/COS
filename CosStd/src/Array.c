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
 | $Id: Array.c,v 1.9 2008/10/24 16:41:29 ldeniau Exp $
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

// ----- private implementation

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

defmethod(OBJ, ginitWith, Array, Array)
  test_assert(self->size <= self2->size);

  for (U32 i = 0; i < self->size; i++)
    self->object[i] = gretain(self2->object[i]);
  
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mArray, Any, Size1)  // generator
  struct Array* arr = array_alloc(self3->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  
  for (U32 i = 0; i < arr->size; i++)
    arr->object[i] = gclone(_2);

  UNPRT(_arr);
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
  BOOL is_not_a_DynArray = cos_any_id((OBJ)arr) != cos_class_id(classref(DynArray));
  
  test_assert( is_not_a_DynArray );
  test_assert( Slice1_iscontiguous(self3) && Slice1_last(self3) < self2->size );

  retmethod( (OBJ)subarray_alloc(arr, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, SubArray)
  grelease(self->array);
  retmethod(_1);
endmethod
 
// ----- equality

defmethod(OBJ, gequal, Array, Array)
  OBJ res = self->size == self2->size ? True : False;

  for (U32 i = 0; res == True && i < self->size; i++)
    res = gequal(self->object[i], self2->object[i]);

  retmethod(res);
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

  for (U32 j = 0; j < self3->size; j++) { // TODO, filling policy
    U32 i = Slice1_eval(self3,j);
    OBJ old = self->object[i];
    self->object[i] = gretain(self2->object[j]);
    grelease(old);
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, Array, Array, IntVector)
  for (U32 j = 0; j < self3->size; j++) { // TODO, filling policy
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

defmethod(void, gapply, Array, Functor)
  for (U32 i = 0; i < self->size; i++) {
    OBJ obj = self->object[i];
    OBJ res = geval1(_2, obj);
    if (res != obj) gdiscard(res);
  }
endmethod

// ----- map, map2, map3, scan (Nil -> discard result)

defmethod(OBJ, gmap, Array, Functor)
  U32 s = self->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval1(_2, self->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  UNPRT(_arr);
  retmethod( gadjust(gautoRelease(_arr)) );
endmethod

defmethod(OBJ, gmap2, Array, Array, Functor)
  U32 s = self1->size < self2->size ? self1->size : self2->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval2(_3, self1->object[i], self2->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  UNPRT(_arr);
  retmethod( gadjust(gautoRelease(_arr)) );
endmethod

defmethod(OBJ, gmap3, Array, Array, Array, Functor)
  U32 s = self1->size < self2->size ? (self1->size < self3->size ? self1->size : self3->size)
                                    : (self2->size < self3->size ? self2->size : self3->size);
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval3(_3, self1->object[i], self2->object[i], self3->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gretain(res);
  }

  UNPRT(_arr);
  retmethod( gadjust(gautoRelease(_arr)) );
endmethod

defmethod(OBJ, gscan, Any, Array, Functor)
  U32 s = self2->size;
  struct Array* arr = dynarray_alloc(s+1);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ obj = _1;

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval2(_3, obj, self2->object[i]);
    if (res == Nil) continue;
    arr->object[arr->size++] = gclone(obj);
    obj = res;
  }
  arr->object[arr->size++] = gclone(obj);

  UNPRT(_arr);
  retmethod( gadjust(gautoRelease(_arr)) );
endmethod

// ----- filter, fold, unfold (Nil -> stop iteration)

defmethod(OBJ, gfilter, Array, Functor)
  U32 s = self->size;
  struct Array* arr = dynarray_alloc(s);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  for (U32 i = 0; i < s; i++) {
    OBJ obj = self->object[i];
    OBJ res = geval1(_2, obj);
    if (res == Nil ) break;
    if (res != True) continue;
    arr->object[arr->size++] = gretain(obj);
  }

  UNPRT(_arr);
  retmethod( gadjust(gautoRelease(_arr)) );
endmethod

defmethod(OBJ, gfold, Any, Array, Functor)
  U32 s = self2->size;
  OBJ obj = _1;

  for (U32 i = 0; i < s; i++) {
    OBJ res = geval2(_3, obj, self2->object[i]);
    if (res == Nil) break;
    obj = res;
  }

  retmethod(obj);
endmethod


// TODO: REVIEW
defmethod(OBJ, gunfold, Any, Functor)
  struct Array* arr = dynarray_alloc(10);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ obj = _1;

  while (1) {
    OBJ res = geval1(_2, obj);
    if (res == Nil) break;
    arr->object[arr->size++] = gclone(obj);
    obj = res;
  }
  arr->object[arr->size++] = gclone(obj);

  UNPRT(_arr);
  retmethod( gadjust(gautoRelease(_arr)) );
endmethod

// ----- sorting

defmethod(OBJ, gsort, Array, Functor)
  U32 s = self->size;
  struct Array* arr = array_alloc(s);
  // TODO
  
  retmethod( gautoRelease((OBJ)arr) );
endmethod

// ----- finding

defmethod(OBJ, gfind, Array, Any, Functor)
  // U32 s = self->size;
  // TODO
  
  retmethod( _1 );
endmethod



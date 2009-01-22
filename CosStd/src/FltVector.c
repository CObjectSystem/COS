/*
 o---------------------------------------------------------------------o
 |
 | COS FltVector
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
 | $Id: FltVector.c,v 1.7 2009/01/22 16:45:08 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/Value.h>
#include <cos/Slice.h>
#include <cos/Number.h>
#include <cos/Sequence.h>
#include <cos/Functor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdlib.h>

useclass(FltVector);

makclass(FltVector    , Vector);
makclass(FltVector0   , FltVector);
makclass(FltVector1   , FltVector);
makclass(FltVector2   , FltVector);
makclass(FltVector3   , FltVector);
makclass(FltVector4   , FltVector);
makclass(FltVector5   , FltVector);
makclass(FltVector6   , FltVector);
makclass(FltVector7   , FltVector);
makclass(FltVector8   , FltVector);
makclass(FltVector9   , FltVector);
makclass(FltVectorN   , FltVector);
makclass(FltSubVector , FltVector);
makclass(FltDynVectorN, FltVector);
makclass(FltDynVector , FltDynVectorN);

// ----- shared private implementation

#include "./FltVector_p.h"

// ----- ctor/dtor of a (dynamic) array

defmethod(OBJ, ginit, mFltVector)
  retmethod( (OBJ)dynvector_alloc(10) );
endmethod

defmethod(OBJ, ginitWith, mFltVector, Int)
  test_assert(self2->value >= 0, "negative vector size");
  
  retmethod( (OBJ)dynvector_alloc(self2->value) );
endmethod

defmethod(OBJ, ginitWith, FltVector, FltVector) // copy
  test_assert(self1->size <= self2->size, "incompatible vector sizes");

  F64 *src = self2->value;
  F64 *val = self1->value;
  F64 *end = self1->value+self1->size;
  
  while (val < end)
    *val++ = *src++;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, mFltVector, FltVector) // clone
  struct FltVector* vec = vector_alloc(self2->size);
  OBJ _vec = (OBJ)vec; PRT(_vec);
  F64 *src = self2->value;
  F64 *val = vec  ->value;
  F64 *end = vec  ->value+vec->size;
  
  while (val < end)
    *val++ = *src++;

  UNPRT(_vec);
  retmethod(_vec);
endmethod

defmethod(OBJ, ginitWith2, mFltVector, Value, Int) // constant
  test_assert(self3->value >= 0, "negative vector size");
  
  struct FltVector* vec = vector_alloc(self3->value);
  OBJ _vec = (OBJ)vec; PRT(_vec);
  F64 *val = vec->value;
  F64 *end = vec->value+vec->size;
  F64  ini = gflt(_2);
  
  while (val < end)
    *val++ = ini;

  UNPRT(_vec);
  retmethod(_vec);
endmethod

defmethod(OBJ, ginitWith2, mFltVector, FltVector, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self2->size);

  retmethod( ginitWith2(_1,_2,slice) );  
endmethod

defmethod(OBJ, ginitWith2, mFltVector, FltVector, Slice1)
  test_assert( self3->start < self2->size && Slice1_last(self3) < self2->size,
               "slice out of range" );

  struct FltVector* vec = vector_alloc(self3->size);
  OBJ _vec = (OBJ)vec; PRT(_vec);
  F64 *src = self2->value+self3->start;
  I32 step = self3->stride;
  F64 *val = vec->value;
  F64 *end = vec->value+vec->size;

  for (; val < end; src += step)
    *val++ = *src;
  
  UNPRT(_vec);
  retmethod(_vec);
endmethod

defmethod(OBJ, ginitWith2, mFltVector, FltVector, IntVector)
  struct FltVector* vec = vector_alloc(self3->size);
  OBJ _vec = (OBJ)vec; PRT(_vec);
  F64 *val = vec->value;
  F64 *end = vec->value+vec->size;
  F64 *src = self2->value;
  U32 size = self2->size;
  I32 *idx = self3->value;

  while(val < end) {
    U32 i = index_abs(*idx++, size);
    test_assert( i < size, "index out of range" );
    *val++ = src[i];
  }

  UNPRT(_vec);
  retmethod(_vec);
endmethod

// default deinit provided by Vector

defmethod(OBJ, gdeinit, FltDynVectorN)
  free(self->FltVector.value);
  retmethod(_1);
endmethod

// ----- ctor/dtor of a subvector

defmethod(OBJ, ginitWith2, mFltSubVector, FltVector, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self2->size);

  retmethod( ginitWith2(_1,_2,slice) );
endmethod

defmethod(OBJ, ginitWith2, mFltSubVector, FltVector, Slice1)
  OBJ vec = gretain(_2);
 
  test_assert( cos_any_isa(vec, classref(FltDynVector)),
               "subvector accepts only fixed size vector" );
  test_assert( Slice1_iscontiguous(self3),
               "subvector slice must be contiguous");
  test_assert( Slice1_last(self3) < self2->size,
               "subvector slice out of range" );

  struct FltVector *ref = STATIC_CAST(struct FltVector*, vec);

  retmethod( (OBJ)subvector_alloc(ref, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, FltSubVector)
  grelease(self->vector);
  
  retmethod(_1);
endmethod
 
// ----- equality

defmethod(OBJ, gisEqual, FltVector, FltVector)
  if (self1 == self2)
    retmethod(True);

  if (self1->size != self2->size)
    retmethod(False);
    
  F64 *val1 = self1->value;
  F64 *end1 = self1->value+self1->size;
  F64 *val2 = self2->value;

  for (; val1 < end1; val1++, val2++)
    if (float_equal(*val1,*val2))
      retmethod(False);

  retmethod(True);
endmethod

// ----- setters

defmethod(void, gput, FltVector, Value)
  F64 *val = self->value;
  F64 *end = self->value+self->size;
  F64  ini = gflt(_2);

  while (val < end)
    *val++ = ini;
endmethod

defmethod(void, gput, FltVector, FltVector)
  F64 *val = self->value;
  F64 *end = self->value+self->size;

  while (val < end) {
    if (end-val < self2->size) {
      F64 *src = self2->value;

      while (val < end)
        *val++ = *src++;

    } else {
      F64 *src = self2->value;
      F64 *end = self2->value+self2->size;

      while (src < end)
        *val++ = *src++;
    }
  }
endmethod

defmethod(void, gputAt, FltVector, Value, Int)
  U32 i = index_abs(self3->value, self->size);
  test_assert( i < self->size, "index out of range" );

  self1->value[i] = gflt(_2);
endmethod

defmethod(void, gputAt, FltVector, Value, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self->size);

  gputAt(_1,_2,slice);
endmethod

defmethod(void, gputAt, FltVector, Value, Slice1)
  test_assert( self3->start < self->size && Slice1_last(self3) < self->size,
               "slice out of range" );

  F64 *val = self1->value+self3->start;
  F64 *end = self1->value+Slice1_last(self3);
  I32 step = self3->stride;
  F64  ini = gflt(_2);

  for (; val < end; val += step)
    *val = ini;
endmethod

defmethod(void, gputAt, FltVector, Value, IntVector)
  F64 *val = self1->value;
  U32 size = self1->size;
  I32 *idx = self3->value;
  I32 *end = self3->value+self3->size;
  F64  ini = gflt(_2);

  for(; idx < end; idx++) {
    U32 i = index_abs(*idx, size);
    test_assert( i < size, "index out of range" );
    val[i] = ini;
  }
endmethod

defmethod(void, gputAt, FltVector, FltVector, Range1)
  OBJ slice = Slice1_range(atSlice(0,0), self3, self->size);

  gputAt(_1,_2,slice);
endmethod

defmethod(void, gputAt, FltVector, FltVector, Slice1)
  test_assert( self3->start < self->size && Slice1_last(self3) < self->size,
               "slice out of range" );

  F64 *val = self1->value+self3->start;
  F64 *src = self2->value;
  F64 *end = self2->value+self2->size;
  I32 step = self3->stride;

  for (; src < end; src++, val += step)
    *val = *src;
endmethod

defmethod(void, gputAt, FltVector, FltVector, IntVector)
  test_assert( self2->size == self3->size,
               "incompatible vector sizes" );

  F64 *val = self1->value;
  F64 *src = self2->value;
  U32 size = self1->size;
  I32 *idx = self3->value;
  I32 *end = self3->value+self3->size;

  for(; idx < end; idx++, src++) {
    U32 i = index_abs(*idx, size);
    test_assert( i < size, "index out of range" );
    val[i] = *src;
  }
endmethod

// ----- getter

defmethod(F64, gfltAt, FltVector, Int)
  U32 i = index_abs(self2->value, self->size);
  test_assert( i < self->size, "index out of range" );

  retmethod( self->value[i] );
endmethod

defmethod(OBJ, ggetAt, FltVector, Int)
  U32 i = index_abs(self2->value, self->size);
  test_assert( i < self->size, "index out of range" );

  retmethod( gautoRelease(aFloat(self->value[i])) );
endmethod

defmethod(OBJ, ggetAt, FltVector, Range1)
  retmethod( gautoRelease(gnewWith2(FltVector,_1,_2)) );  
endmethod

defmethod(OBJ, ggetAt, FltVector, Slice1)
  retmethod( gautoRelease(gnewWith2(FltVector,_1,_2)) );  
endmethod

defmethod(OBJ, ggetAt, FltVector, IntVector)
  retmethod( gautoRelease(gnewWith2(FltVector,_1,_2)) );
endmethod

// ----- accessors and adjustment

defalias (void, (gput)gappend, FltDynVector, Value);
defalias (void, (gput)gpush  , FltDynVector, Value);
defmethod(void,  gput        , FltDynVector, Value)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;

  if (vec->size == self->capacity)
    dynvector_resizeBy(self, 1.8);

  vec->value[vec->size++] = gflt(_2);
endmethod

defalias (OBJ, (gget)glast, FltDynVector);
defalias (OBJ, (gget)gtop , FltDynVector);
defmethod(OBJ,  gget      , FltDynVector)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;
  
  retmethod( vec->size ? gautoRelease(aFloat(vec->value[vec->size-1])) : 0 );
endmethod

defalias (void, (gdrop)gpop, FltDynVector);
defmethod(void,  gdrop     , FltDynVector)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;
  
  if (vec->size) --vec->size;
endmethod

defmethod(void, gadjust, FltDynVector)
  if (self->FltDynVectorN.FltVector.size < self->capacity)
    dynvector_resizeBy(self, 1.0);

  test_assert( cos_any_changeClass(_1, classref(FltDynVectorN)),
               "unable to change dynamic vector to fixed size vector" );
endmethod

defmethod(void, gappend, FltDynVector, FltVector)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;

  if (self->capacity - vec->size < self2->size) { // enlarge first
    FLOAT size = vec->size;

    do size *= 1.8;
    while (self->capacity - size < self2->size);

    dynvector_resizeBy(self, size);
  }

  F64 *val = vec  ->value;
  F64 *end = vec  ->value+self2->size;
  F64 *src = self2->value;

  while (val < end)
    *val++ = *src++;

  vec->size += self2->size;
endmethod

// ----- clear (in place) 

defmethod(void, gclear, FltVector)
  F64 *val = self1->value;
  F64 *end = self1->value+self1->size;

  while (val < end)
    *val++ = 0; 
endmethod

// ----- reverse (in place)

defmethod(void, greverse, FltVector)
  F64 *val = self->value;
  F64 *end = self->value+self->size-1;
  F64  tmp;
  
  while (val < end)
    tmp = *val, *val++ = *end, *end-- = tmp;
endmethod

// ----- apply (in place)

defmethod(void, gapply, Functor, FltVector)
  F64 *val = self2->value;
  F64 *end = self2->value+self2->size;
  struct Float *flt = atFloat(0);
  OBJ obj = (OBJ)flt;

  while(val < end) {
    flt->value = *val;
    geval1(_1, obj);
    *val++ = flt->value;
  }
endmethod

defmethod(void, gapply, Function1, FltVector)
  F64 *val = self2->value;
  F64 *end = self2->value+self2->size;
  OBJFCT1 fct = self->fct;
  struct Float *flt = atFloat(0);
  OBJ obj = (OBJ)flt;

  while(val < end) {
    flt->value = *val;
    fct(obj);
    *val++ = flt->value;
  }
endmethod

// ----- map, fold, ...

/*
defmethod(void, gapply, FltVector, Functor)
  struct Float *Flt = atFloat(0);
  OBJ val = (OBJ)Flt;
  OBJ res;

  for (U32 i = 0; i < self->size; i++) {
    Flt->value = self->value[i];
    res = geval1(_2, val);
    test_assert(res == val);
    self->value[i] = Flt->value;
  }
endmethod

defmethod(OBJ, gmap, FltVector, Functor)
  struct FltVector* vec = vector_alloc(self->size);
  struct Float *Flt = atFloat(0);
  OBJ val = (OBJ)Flt;
  OBJ res;

  for (U32 i = 0; i < vec->size; i++) {
    Flt->value = self->value[i];
    res = geval1(_2, val);
    test_assert(res == val);
    vec->value[i] = Flt->value;
  }

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, gmap, Array, Functor)
  struct Array *arr = array_alloc(self->size); PRT(arr);

  for (U32 i = 0; i < self->size; i++)
    arr->value[i] = gretain(geval1(_2, self->value[i]));

  UNPRT(arr);
  retmethod(gautorelease((OBJ)arr));
endmethod
*/

/****************************************************************
 * SPECIAL CASES
 */

defmethod(U32, gsize, FltVector)
  retmethod(self->size);
endmethod

defmethod(F64*, gfltPtr, FltVector)
  retmethod(self->value);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Sequence1)
  struct FltVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = Sequence1_eval(self2, i);

  retmethod((OBJ)vec);
endmethod

defmethod(void, gput, FltVector, Sequence1)
  U32 i, j;

  for (i = j = 0; i < self->size; i++, j++) {
    if (j >= self2->size) j = 0;
    self1->value[i] = Sequence1_eval(self2, j);
  }
endmethod



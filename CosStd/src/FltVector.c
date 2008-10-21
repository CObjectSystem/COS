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
 | $Id: FltVector.c,v 1.3 2008/10/21 15:43:42 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/Number.h>
#include <cos/Size.h>
#include <cos/Index.h>
#include <cos/Range.h>
#include <cos/Slice.h>
#include <cos/Point.h>
#include <cos/Functor.h>
#include <cos/Sequence.h>
#include <cos/gen/value.h>
#include <cos/gen/access.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

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

// ----- local allocators

static struct FltVector*
vector_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[N] = {
    classref(FltVector0,FltVector1,FltVector2,FltVector3,FltVector4),
    classref(FltVector5,FltVector6,FltVector7,FltVector8,FltVector9) }; 

  useclass(FltVectorN);

  OBJ _cls = size >= N ? FltVectorN : (OBJ)cls[size];
  OBJ _vec = gallocWithSize(_cls, size * sizeof(FLOAT));
  struct FltVectorN *nvec = STATIC_CAST(struct FltVectorN*, _vec);
  struct FltVector  * vec = &nvec->FltVector;

  vec->size  = size;
  vec->value = nvec->_value;

  return vec;
}

static struct FltVector*
subvector_alloc(struct FltVector *ref, U32 start, U32 size)
{
  useclass(FltSubVector);

  OBJ _vec = gallocWithSize(FltSubVector, 0);
  struct FltSubVector *svec = STATIC_CAST(struct FltSubVector*, _vec);
  struct FltVector    * vec = &svec->FltVector;

  vec->size = size;
  vec->value = ref->value + start;
  svec->vector = (OBJ)ref;

  return vec;
}

static struct FltVector*
dynvector_alloc(U32 size)
{
  useclass(FltDynVector, ExBadAlloc);

  OBJ _vec = gallocWithSize(FltDynVector, 0);
  struct FltDynVector *dvec = STATIC_CAST(struct FltDynVector*, _vec);
  struct FltVector    * vec = &dvec->FltDynVectorN.FltVector;

  vec->value = malloc(size * sizeof *vec->value);
  if (!vec->value) THROW(ExBadAlloc);
  dvec->capacity = size;

  return vec;
}

static void
dynvector_resizeBy(struct FltDynVector *dvec, FLOAT factor)
{
  useclass(ExBadAlloc);

  struct FltVector *vec = &dvec->FltDynVectorN.FltVector;
  U32  size  = dvec->capacity * factor;
  R64 *value = realloc(vec->value, size * sizeof *vec->value);

  if (!value) THROW(ExBadAlloc);
  vec->value = value;
  dvec->capacity = size;
}

// ----- ctor/dtor of a vector

defmethod(OBJ, ginitWith, mFltVector, Size1)
  struct FltVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = 0;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mFltVector, FltVector)
  struct FltVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mFltVector, Value, Size1)
  struct FltVector* vec = vector_alloc(self3->size);
  R64 value = gflt(_2);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mFltVector, FltVector, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);

  retmethod( ginitWith2(_1,_2,s) );  
endmethod

defmethod(OBJ, ginitWith2, mFltVector, FltVector, Slice1)
  struct FltVector* vec = vector_alloc(self3->size);

  test_assert( self3->start < self2->size
            && Slice1_last(self3) < self2->size );

  for (U32 i = 0; i < self3->size; i++)
    vec->value[i] = self2->value[ Slice1_eval(self3,i) ];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mFltVector, FltVector, IntVector)
  struct FltVector* vec = vector_alloc(self3->size);

  for (U32 i = 0; i < vec->size; i++) {
    U32 j = index_abs(self3->value[i], self2->size);
    test_assert( j < self2->size );
    vec->value[i] = self2->value[j];
  }

  retmethod((OBJ)vec);
endmethod

// ----- ctor/dtor of a dynamic vector

defmethod(OBJ, ginit, mFltDynVector)
  retmethod( (OBJ)dynvector_alloc(10) );
endmethod

defmethod(OBJ, ginitWith, mFltDynVector, Size1)
  retmethod( (OBJ)dynvector_alloc(self2->size) );
endmethod

defmethod(OBJ, gdeinit, FltDynVectorN)
  free(self->FltVector.value);
  retmethod(_1);
endmethod

// ----- ctor/dtor of a subvector

defmethod(OBJ, ginitWith2, mFltSubVector, FltVector, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);

  retmethod( ginitWith2(_1,_2,s) );
endmethod

defmethod(OBJ, ginitWith2, mFltSubVector, FltVector, Slice1)
  OBJ vec = gretain(_2);
  OBJ vec_spr = (OBJ)cos_class_get(cos_any_id(vec))->spr;

  test_assert( vec_spr == FltVector );
  test_assert( Slice1_iscontiguous(self3)
            && self3->start < self2->size
            && Slice1_last(self3) < self2->size );

  retmethod( (OBJ)subvector_alloc((struct FltVector*)vec, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, FltSubVector)
  if (self->vector) grelease(self->vector);
  retmethod(_1);
endmethod
 
// ----- copy

defmethod(OBJ, ginitWith, FltVector, FltVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, FltVector, FltVector)
  BOOL res = self1->size == self2->size;

  for (U32 i = 0; res && i < self->size; i++)
    res = float_equal(self1->value[i], self2->value[i]);

  retmethod( res ? True : False );
endmethod

// ----- setters

defmethod(OBJ, gput, FltVector, Value)
  FLOAT value = gflt(_2);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = value;

  retmethod(_1);
endmethod

defmethod(OBJ, gput, FltVector, FltVector)
  U32 i, j;

  for (i = j = 0; i < self->size; i++, j++) {
    if (j >= self2->size) j = 0;
    self1->value[i] = self2->value[j];
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, FltVector, Value, Index1)
  U32 i = index_abs(self3->index, self->size);

  test_assert( i < self->size );
  self1->value[i] = gflt(_2);

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, FltVector, Value, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self->size);

  retmethod( gputAt(_1,_2,s) );  
endmethod

defmethod(OBJ, gputAt, FltVector, Value, Slice1)
  FLOAT value = gflt(_2);

  test_assert( Slice1_last(self3) < self->size );

  for (U32 i = 0; i < self3->size; i++)
    self1->value[ Slice1_eval(self3,i) ] = value;

   retmethod(_1);
endmethod

defmethod(OBJ, gputAt, FltVector, Value, IntVector)
  FLOAT value = gflt(_2);

  for (U32 i = 0; i < self3->size; i++) {
    U32 j = index_abs(self3->value[i], self->size);
    test_assert( j < self->size );
    self1->value[j] = value;
  }

  retmethod(_1);  
endmethod

defmethod(OBJ, gputAt, FltVector, FltVector, Index1)
  U32 start = index_abs(self3->index, self->size);

  test_assert( start+self2->size < self->size );

  for (U32 i = 0; i < self2->size; i++)
    self1->value[start+i] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, FltVector, FltVector, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self->size);

  retmethod( gputAt(_1,_2,s) );  
endmethod

defmethod(OBJ, gputAt, FltVector, FltVector, Slice1)
  U32 i, j;

  test_assert( Slice1_last(self3) < self->size );

  for (i = j = 0; i < self3->size; i++, j++) {
    if (j > self2->size) j = 0;
    self1->value[ Slice1_eval(self3,i) ] = self2->value[j];
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, FltVector, FltVector, IntVector)
  U32 i, j;

  for (i = j = 0; i < self3->size; i++, j++) {
    U32 k = index_abs(self3->value[i], self->size);
    test_assert( k < self->size );
    if (j > self2->size) j = 0;
    self1->value[k] = self2->value[j];
  }

  retmethod(_1);  
endmethod

// ----- getter

defmethod(R64, gfltAt, FltVector, Index1)
  U32 i = index_abs(self2->index, self->size);
  test_assert( i < self->size );
  retmethod( self->value[i] );
endmethod

defmethod(OBJ, ggetAt, FltVector, Index1)
  retmethod( gautoRelease(aFloat(gfltAt(_1,_2))) );
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

// ----- stack-like accessors and adjustment

defmethod(OBJ, gpush, FltDynVector, Value)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;

  if (vec->size == self->capacity)
    dynvector_resizeBy(self, 1.75);

  vec->value[vec->size++] = gflt(_2);

  retmethod(_1);
endmethod

defmethod(OBJ, gpush, FltDynVector, FltVector)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;

  if (self->capacity - vec->size < self2->size) {
    FLOAT size = vec->size;

    do size *= 1.75;
    while (self->capacity - size < self2->size);

    dynvector_resizeBy(self, size);
  }

  for (U32 i = 0; i < self2->size; i++)
    vec->value[vec->size++] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, gpop, FltDynVector)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;
  test_assert( vec->size > 0 );
  retmethod( gautoRelease(aFloat(vec->value[--vec->size])) );
endmethod

defmethod(OBJ, gadjust, FltDynVector)
  struct FltVector *vec = &self->FltDynVectorN.FltVector;
  struct Class *cls = &COS_CLS_NAME(FltDynVectorN);

  if (vec->size < self->capacity)
    dynvector_resizeBy(self, 1.0);

  test_assert( cos_any_changeClass(_1, cls) );

  retmethod(_1);
endmethod

// ----- map, fold, ...

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

/*
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

defmethod(R64*, gfltPtr, FltVector)
  retmethod(self->value);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Sequence1)
  struct FltVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = Sequence1_eval(self2, i);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, gput, FltVector, Sequence1)
  U32 i, j;

  for (i = j = 0; i < self->size; i++, j++) {
    if (j >= self2->size) j = 0;
    self1->value[i] = Sequence1_eval(self2, j);
  }

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Point1)
  struct FltVector* vec = vector_alloc(1);
  vec->value[0] = self2->coord;
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Point2)
  struct FltVector* vec = vector_alloc(2);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Point3)
  struct FltVector* vec = vector_alloc(3);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  vec->value[2] = self2->coord[2];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Point4)
  struct FltVector* vec = vector_alloc(4);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  vec->value[2] = self2->coord[2];
  vec->value[3] = self2->coord[3];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mFltVector, Point5)
  struct FltVector* vec = vector_alloc(5);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  vec->value[2] = self2->coord[2];
  vec->value[3] = self2->coord[3];
  vec->value[4] = self2->coord[4];
  retmethod((OBJ)vec);
endmethod


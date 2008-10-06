/*
 o---------------------------------------------------------------------o
 |
 | COS DblVector
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
 | $Id: DblVector.c,v 1.4 2008/10/06 17:34:58 ldeniau Exp $
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
#include <cos/gen/object.h>
#include <cos/gen/eval.h>
#include <cos/gen/value.h>
#include <cos/gen/access.h>

#include <stdlib.h>

useclass(DblVector);

makclass(DblVector    , Vector);
makclass(DblVector0   , DblVector);
makclass(DblVector1   , DblVector);
makclass(DblVector2   , DblVector);
makclass(DblVector3   , DblVector);
makclass(DblVector4   , DblVector);
makclass(DblVector5   , DblVector);
makclass(DblVector6   , DblVector);
makclass(DblVector7   , DblVector);
makclass(DblVector8   , DblVector);
makclass(DblVector9   , DblVector);
makclass(DblVectorN   , DblVector);
makclass(DblSubVector , DblVector);
makclass(DblDynVectorN, DblVector);
makclass(DblDynVector , DblDynVectorN);

// ----- local allocators

static struct DblVector*
vector_alloc(U32 size)
{
  enum { N = 10 };
  static const OBJ cls[N] = {
    classref(DblVector0,DblVector1,DblVector2,DblVector3,DblVector4),
    classref(DblVector5,DblVector6,DblVector7,DblVector8,DblVector9) }; 

  useclass(DblVectorN);

  OBJ _cl  = size >= N ? DblVectorN : cls[size];
  OBJ _vec = gallocWithSize(_cl, size * sizeof(DOUBLE));
  struct DblVectorN *nvec = STATIC_CAST(struct DblVectorN*, _vec);
  struct DblVector  * vec = &nvec->DblVector;

  vec->size  = size;
  vec->value = nvec->_value;

  return vec;
}

static struct DblVector*
subvector_alloc(struct DblVector *ref, U32 start, U32 size)
{
  useclass(DblSubVector);

  OBJ _vec = gallocWithSize(DblSubVector, 0);
  struct DblSubVector *svec = STATIC_CAST(struct DblSubVector*, _vec);
  struct DblVector    * vec = &svec->DblVector;

  vec->size = size;
  vec->value = ref->value + start;
  svec->vector = (OBJ)ref;

  return vec;
}

static struct DblVector*
dynvector_alloc(U32 size)
{
  useclass(DblDynVector, ExBadAlloc);

  OBJ _vec = gallocWithSize(DblDynVector, 0);
  struct DblDynVector *dvec = STATIC_CAST(struct DblDynVector*, _vec);
  struct DblVector    * vec = &dvec->DblDynVectorN.DblVector;

  vec->value = malloc(size * sizeof *vec->value);
  if (!vec->value) THROW(ExBadAlloc);
  dvec->capacity = size;

  return vec;
}

static void
dynvector_resizeBy(struct DblDynVector *dvec, double factor)
{
  useclass(ExBadAlloc);

  struct DblVector *vec = &dvec->DblDynVectorN.DblVector;
  U32  size  = dvec->capacity * factor;
  R64 *value = realloc(vec->value, size * sizeof *vec->value);

  if (!value) THROW(ExBadAlloc);
  vec->value = value;
  dvec->capacity = size;
}

// ----- ctor/dtor of a vector

defmethod(OBJ, ginitWith, mDblVector, Size1)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = 0;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, DblVector)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, Sequence1)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = Sequence1_eval(self2, i);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, Point1)
  struct DblVector* vec = vector_alloc(1);
  vec->value[0] = self2->coord;
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, Point2)
  struct DblVector* vec = vector_alloc(2);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, Point3)
  struct DblVector* vec = vector_alloc(3);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  vec->value[2] = self2->coord[2];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, Point4)
  struct DblVector* vec = vector_alloc(4);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  vec->value[2] = self2->coord[2];
  vec->value[3] = self2->coord[3];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, Point5)
  struct DblVector* vec = vector_alloc(5);
  vec->value[0] = self2->coord[0];
  vec->value[1] = self2->coord[1];
  vec->value[2] = self2->coord[2];
  vec->value[3] = self2->coord[3];
  vec->value[4] = self2->coord[4];
  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Size1, Double)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Size1, Functor)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = gdbl(geval(_3));

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, DblVector, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);

  retmethod( ginitWith2(_1,_2,s) );  
endmethod

defmethod(OBJ, ginitWith2, mDblVector, DblVector, Slice1)
  struct DblVector* vec = vector_alloc(self3->size);

  test_assert( Slice1_last(self3) < self2->size );

  for (U32 i = 0; i < self3->size; i++)
    vec->value[i] = self2->value[ Slice1_eval(self3,i) ];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, DblVector, IntVector)
  struct DblVector* vec = vector_alloc(self3->size);

  for (U32 i = 0; i < vec->size; i++) {
    U32 j = index_abs(self3->value[i], self2->size);
    test_assert( j < self2->size );
    vec->value[i] = self2->value[j];
  }

  retmethod((OBJ)vec);
endmethod

// ----- ctor/dtor of a dynamic vector

defmethod(OBJ, ginit, mDblDynVector)
  retmethod( (OBJ)dynvector_alloc(10) );
endmethod

defmethod(OBJ, ginitWith, mDblDynVector, Size1)
  retmethod( (OBJ)dynvector_alloc(self2->size) );
endmethod

defmethod(OBJ, gdeinit, DblDynVectorN)
  free(self->DblVector.value);
  retmethod(_1);
endmethod

// ----- ctor/dtor of a subvector

defmethod(OBJ, ginitWith2, mDblSubVector, DblVector, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self2->size);

  retmethod( ginitWith2(_1,_2,s) );
endmethod

defmethod(OBJ, ginitWith2, mDblSubVector, DblVector, Slice1)
  OBJ vec = gretain(_2);
  OBJ vec_spr = (OBJ)cos_class_get(cos_any_id(vec))->spr;

  test_assert( vec_spr == DblVector );
  test_assert( Slice1_iscontiguous(self3) );
  test_assert( Slice1_last(self3) < self2->size );

  retmethod( (OBJ)subvector_alloc((void*)vec, self3->start, self3->size) );
endmethod

defmethod(OBJ, gdeinit, DblSubVector)
  if (self->vector) grelease(self->vector);
  retmethod(_1);
endmethod
 
// ----- copy

defmethod(OBJ, ginitWith, DblVector, DblVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, DblVector, DblVector)
  BOOL res = self1->size == self2->size;

  for (U32 i = 0; res && i < self->size; i++)
    res = dbl_equal(self1->value[i], self2->value[i]);

  retmethod( res ? True : False );
endmethod

// ----- setters

defmethod(OBJ, gput, DblVector, Double)
  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gput, DblVector, Functor)
  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = gdbl(geval(_2));

  retmethod(_1);
endmethod

defmethod(OBJ, gput, DblVector, DblVector)
  U32 i, j;

  for (i = j = 0; i < self->size; i++, j++) {
    if (j >= self2->size) j = 0;
    self1->value[i] = self2->value[j];
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gput, DblVector, Sequence1)
  U32 i, j;

  for (i = j = 0; i < self->size; i++, j++) {
    if (j >= self2->size) j = 0;
    self1->value[i] = Sequence1_eval(self2, i);
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, Double, Index1)
  U32 i = index_abs(self3->index, self->size);

  test_assert( i < self->size );

  self1->value[i] = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, Double, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self->size);

  retmethod( gputAt(_1,_2,s) );  
endmethod

defmethod(OBJ, gputAt, DblVector, Double, Slice1)
  test_assert( Slice1_last(self3) < self->size );

  for (U32 i = 0; i < self3->size; i++)
    self1->value[ Slice1_eval(self3,i) ] = self2->value;

   retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, Double, IntVector)
  for (U32 i = 0; i < self3->size; i++) {
    U32 j = index_abs(self3->value[i], self->size);
    test_assert( j < self->size );
    self1->value[j] = self2->value;
  }

  retmethod(_1);  
endmethod

defmethod(OBJ, gputAt, DblVector, DblVector, Index1)
  U32 start = index_abs(self3->index, self->size);

  test_assert( start+self2->size < self->size );

  for (U32 i = 0; i < self2->size; i++)
    self1->value[start+i] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, DblVector, Range1)
  struct Slice1 slice[1];
  OBJ s = Slice1_range(slice, self3, self->size);

  retmethod( gputAt(_1,_2,s) );  
endmethod

defmethod(OBJ, gputAt, DblVector, DblVector, Slice1)
  U32 i, j;

  test_assert( Slice1_last(self3) < self->size );

  for (i = j = 0; i < self3->size; i++, j++) {
    if (j > self2->size) j = 0;
    self1->value[ Slice1_eval(self3,i) ] = self2->value[j];
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, DblVector, IntVector)
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

defmethod(OBJ, ggetAt, DblVector, Index1)
  U32 i = index_abs(self2->index, self->size);
  test_assert( i < self->size );
  retmethod( gautoRelease(aDbl(self->value[i])) );
endmethod

defmethod(OBJ, ggetAt, DblVector, Range1)
  retmethod( gautoRelease(gnewWith2(DblVector,_1,_2)) );  
endmethod

defmethod(OBJ, ggetAt, DblVector, Slice1)
  retmethod( gautoRelease(gnewWith2(DblVector,_1,_2)) );  
endmethod

defmethod(OBJ, ggetAt, DblVector, IntVector)
  retmethod( gautoRelease(gnewWith2(DblVector,_1,_2)) );
endmethod

defmethod(OBJ, gpop, DblDynVector)
  struct DblVector *vec = &self->DblDynVectorN.DblVector;
  test_assert( vec->size > 0 );
  retmethod( gautoRelease(aDbl(vec->value[--vec->size])) );
endmethod

// ----- push setter and adjustment

defmethod(OBJ, gpush, DblDynVector, Double)
  struct DblVector *vec = &self->DblDynVectorN.DblVector;

  if (vec->size == self->capacity)
    dynvector_resizeBy(self, 1.75);

  vec->value[vec->size++] = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gpush, DblDynVector, DblVector)
  struct DblVector *vec = &self->DblDynVectorN.DblVector;

  if (self->capacity - vec->size < self2->size) {
    double size = vec->size;

    // size *= pow(1.75, log(1+self2->size/self->size) / log(1.75));
    do size *= 1.75;
    while (self->capacity - size < self2->size);

    dynvector_resizeBy(self, size);
  }

  for (U32 i = 0; i < self2->size; i++)
    vec->value[vec->size++] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, gadjust, DblDynVector)
  struct DblVector *vec = &self->DblDynVectorN.DblVector;

  if (vec->size < self->capacity)
    dynvector_resizeBy(self, 1.0);

  retmethod(_1);
endmethod

/****************************************************************
 * PROMOTIONS
 */

// ----- Int, IntVector

defmethod(OBJ, ginitWith, DblVector, IntVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Size1, Int)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Size1, Int)
  struct DblVector* vec = dynvector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, IntVector)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblDynVector, IntVector)
  struct DblVector* vec = dynvector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, gput, DblVector, Int)
  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, Int, Index1)
  U32 idx = self3->index;
  if (self3->index < 0) idx += self1->size;

  test_assert( idx < self1->size );
  self1->value[idx] = self2->value;

  retmethod(_1);
endmethod

// ----- Long, LongVector

defmethod(OBJ, ginitWith, DblVector, LngVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Size1, Long)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Size1, Long)
  struct DblVector* vec = dynvector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, LngVector)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblDynVector, LngVector)
  struct DblVector* vec = dynvector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, gput, DblVector, Long)
  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, Long, Index1)
  U32 idx = self3->index;
  if (self3->index < 0) idx += self1->size;

  test_assert( idx < self1->size );
  self1->value[idx] = self2->value;

  retmethod(_1);
endmethod


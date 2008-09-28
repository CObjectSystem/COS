/*
 o---------------------------------------------------------------------o
 |
 | COS DblVector and DblSubVector
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
 | $Id: DblVector.c,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
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
  struct DblVectorN *vecn = STATIC_CAST(struct DblVectorN*, _vec);
  struct DblVector  *vec  = &vecn->DblVector;

  vec->size  = size;
  vec->value = vecn->_value;

  return vec;
}

static struct DblVector*
dynvector_alloc(U32 size)
{
  useclass(DblDynVector, ExBadAlloc);

  OBJ _vec = gallocWithSize(DblDynVector, 0);
  struct DblDynVector *dvec = STATIC_CAST(struct DblDynVector*, _vec);
  struct DblVector    *vec  = &dvec->DblDynVectorN.DblVector;

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
    vec->value[i] = Sequence1_value(self2, i);

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
  U32 start = self3->start + (self3->start < 0) * self2->size;
  U32 end   = self3->end   + (self3->end   < 0) * self2->size;
  U32 size  = (start < end) ? end-start+1 : 0;

  test_assert(YES);

  struct DblVector* vec = vector_alloc(size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[start+i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, DblVector, Slice1)
  struct DblVector* vec = vector_alloc(self3->size);
  U32 j = self3->start + (self3->start < 0) * self2->size;

  for (U32 i = 0; i < vec->size && j < self3->size; i++, j += self3->stride)
    vec->value[i] = self2->value[j];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, DblVector, IntVector)
  struct DblVector* vec = vector_alloc(self3->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

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
  useclass(DblSubVector);

  U32 start = self3->start + (self3->start < 0) * self2->size;
  U32 end   = self3->end   + (self3->end   < 0) * self2->size;
  U32 size  = (start < end) ? end-start+1 : 0;

  OBJ _vec  = gretain(_2); // clone automatic object first
  OBJ _svec = gallocWithSize(DblSubVector, 0);

  struct DblSubVector* svec = STATIC_CAST(struct DblSubVector*, _svec);
  struct DblVector*     vec = STATIC_CAST(struct DblVector   *, _vec );
  struct DblVector*      sv = &svec->DblVector;

  sv->size = size;
  sv->value = vec->value + start;
  svec->vector = _vec;

  test_assert( sv->value >= vec->value );
  test_assert( sv->value + size <= vec->value + vec->size );

  retmethod(_svec);
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

// ----- fill setter

defmethod(OBJ, gput, DblVector, Double)
  R64 *dst = self1->value;
  R64  src = self2->value;

  COS_MEM_SET(dst, src, self->size);

  retmethod(_1);
endmethod

// ----- index setter

defmethod(OBJ, gputAt, DblVector, Double, Index1)
  U32 idx = self3->index;
  if (self3->index < 0) idx += self1->size;

  test_assert( idx < self1->size );
  self1->value[idx] = self2->value;

  retmethod(_1);
endmethod

// ----- push setter and adjustment

defmethod(OBJ, gpush, DblDynVector, Double)
  struct DblVector *vec = &self->DblDynVectorN.DblVector;

  if (vec->size == self->capacity)
    dynvector_resizeBy(self, 1.75);

  vec->value[vec->size++] = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gadjust, DblDynVector)
  struct DblVector *vec = &self->DblDynVectorN.DblVector;

  if (vec->size < self->capacity)
    dynvector_resizeBy(self, 1.0);

  retmethod(_1);
endmethod

// ----- index getter

defmethod(OBJ, ggetAt, DblVector, Index1)
  U32 idx = self2->index;
  if (self2->index < 0) idx += self1->size;
  test_assert( idx < self1->size );
  retmethod( gautoRelease( aDbl(self1->value[idx]) ) );
endmethod

defmethod(void, ggetValueAt, DblVector, Double, Index1)
  U32 idx = self3->index;
  if (self3->index < 0) idx += self1->size;
  test_assert( idx < self1->size );
  self2->value = self1->value[idx];
endmethod

// ----- access

// TODO push putAt getAt getValue getValueAt


/****************************************************************
 * PROMOTIONS
 */

// ----- Int, IntVector

defmethod(OBJ, ginitWith, DblVector, IntVector)
  test_assert(self1->size == self2->size);
  R64 *dst = self1->value;
  I32 *src = self2->value;

  COS_MEM_MAP(dst, src, self->size);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Size1, Int)
  struct DblVector* vec = vector_alloc(self2->size);
  R64 *dst = vec->value;

  COS_MEM_SET(dst, self3->value, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Size1, Int)
  struct DblVector* vec = dynvector_alloc(self2->size);
  R64 *dst = vec->value;

  COS_MEM_SET(dst, self3->value, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, IntVector)
  struct DblVector* vec = vector_alloc(self2->size);
  R64 *dst = vec->value;
  I32 *src = self2->value;

  COS_MEM_MAP(dst, src, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblDynVector, IntVector)
  struct DblVector* vec = dynvector_alloc(self2->size);
  R64 *dst = vec->value;
  I32 *src = self2->value;

  COS_MEM_MAP(dst, src, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, gput, DblVector, Int)
  R64 *dst = self1->value;
  R64  src = self2->value;

  COS_MEM_SET(dst, src, self->size);

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
  R64 *dst = self1->value;
  I64 *src = self2->value;

  COS_MEM_MAP(dst, src, self->size);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Size1, Long)
  struct DblVector* vec = vector_alloc(self2->size);
  R64 *dst = vec->value;

  COS_MEM_SET(dst, self3->value, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Size1, Long)
  struct DblVector* vec = dynvector_alloc(self2->size);
  R64 *dst = vec->value;

  COS_MEM_SET(dst, self3->value, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, LngVector)
  struct DblVector* vec = vector_alloc(self2->size);
  R64 *dst = vec->value;
  I64 *src = self2->value;

  COS_MEM_MAP(dst, src, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblDynVector, LngVector)
  struct DblVector* vec = dynvector_alloc(self2->size);
  R64 *dst = vec->value;
  I64 *src = self2->value;

  COS_MEM_MAP(dst, src, vec->size);

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, gput, DblVector, Long)
  R64 *dst = self1->value;
  R64  src = self2->value;

  COS_MEM_SET(dst, src, self->size);

  retmethod(_1);
endmethod

defmethod(OBJ, gputAt, DblVector, Long, Index1)
  U32 idx = self3->index;
  if (self3->index < 0) idx += self1->size;

  test_assert( idx < self1->size );
  self1->value[idx] = self2->value;

  retmethod(_1);
endmethod




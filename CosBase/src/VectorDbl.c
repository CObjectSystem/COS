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
 | $Id: VectorDbl.c,v 1.1 2008/08/21 15:54:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/Number.h>
#include <cos/Range.h>
#include <cos/gen/object.h>

#include <stdlib.h>

makclass(DblVector   , Vector);
makclass(DblVector0  , DblVector);
makclass(DblVector1  , DblVector);
makclass(DblVector2  , DblVector);
makclass(DblVector3  , DblVector);
makclass(DblVector4  , DblVector);
makclass(DblVector5  , DblVector);
makclass(DblVector6  , DblVector);
makclass(DblVector7  , DblVector);
makclass(DblVector8  , DblVector);
makclass(DblVector9  , DblVector);
makclass(DblVectorN  , DblVector);
makclass(DblDynVector, DblVector);
makclass(DblSubVector, DblVector);

// ----- helpers

static struct DblVector*
vector_alloc(U32 size)
{
  enum { N = 10 };
  static const OBJ cls[N] = {
    classref(DblVector0),classref(DblVector1),classref(DblVector2),classref(DblVector3),
    classref(DblVector4),classref(DblVector5),classref(DblVector6),classref(DblVector7), 
    classref(DblVector8),classref(DblVector9) }; 

  OBJ _cl = size >= N ? classref(DblVectorN) : cls[size];
  OBJ _sz = aInt(size * sizeof(DOUBLE));
  OBJ _vec = gallocWith(_cl, _sz);
  struct DblVector * vec  = (struct DblVector *)_vec;
  struct DblVectorN* vecn = (struct DblVectorN*)_vec;

  vec->size  = size;
  vec->value = vecn->_value;

  return vec;
}

static struct DblVector*
dynvector_alloc(U32 size)
{
  useclass(DblDynVector, ExBadAlloc);

  OBJ _vec = gallocWith(DblDynVector, aInt(0));

  struct DblVector*     vec = (struct DblVector    *)_vec;
  struct DblDynVector* dvec = (struct DblDynVector *)_vec;

  if (size) {
    vec->value = 0;
    vec->size  = 0;
    dvec->capacity = 0;
  } else {
    vec->value = malloc(size * sizeof(DOUBLE));
    if (!vec->value) THROW(ExBadAlloc);
    vec->size = size;
    dvec->capacity = size;
  }
  dvec->refcnt = 0;

  return vec;
}

// ----- constructors from an element

defmethod(OBJ, ginitWith2, mDblVector, Int, Int)
  struct DblVector* vec = vector_alloc(self2->value);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Int, Long)
  struct DblVector* vec = vector_alloc(self2->value);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblVector, Int, Double)
  struct DblVector* vec = vector_alloc(self2->value);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

// ----- constructors from a vector

defmethod(OBJ, ginitWith, mDblVector, IntVector)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, LngVector)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblVector, DblVector)
  struct DblVector* vec = vector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

// ----- constructors for subvector

defmethod(OBJ, ginitWith2, mDblSubVector, DblVector, Range1)
  useclass(DblSubVector);

  OBJ _src = gretain(_2);
  OBJ _vec = gallocWith(DblSubVector, aInt(0));

  struct DblVector*     vec = (struct DblVector    *)_vec;
  struct DblSubVector* svec = (struct DblSubVector *)_vec;
  struct DblVector*     src = (struct DblVector    *)_src;

  svec->vector = _src;
  vec->size = self3->size;

  if (self3->start < 0)
    vec->value = src->value - self3->start + src->size;
  else
    vec->value = src->value + self3->start;

  test_assert( vec->value >= self2->value );
  test_assert( vec->value + vec->size <= self2->value + self2->size );

  retmethod(_vec);
endmethod

// ----- constructors for dynvector

defmethod(OBJ, ginit, mDblDynVector)
  retmethod( (OBJ)dynvector_alloc(0) );
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Int, Int)
  struct DblVector* vec = dynvector_alloc(self2->value);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Int, Long)
  struct DblVector* vec = dynvector_alloc(self2->value);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mDblDynVector, Int, Double)
  struct DblVector* vec = dynvector_alloc(self2->value);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self3->value;

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mDblDynVector, IntVector)
  struct DblVector* vec = dynvector_alloc(self2->size);

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

defmethod(OBJ, ginitWith, mDblDynVector, DblVector)
  struct DblVector* vec = dynvector_alloc(self2->size);

  for (U32 i = 0; i < vec->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

// ----- copy constructor

defmethod(OBJ, ginitWith, DblVector, DblVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self1->size; i++)
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

// ----- access

// TODO push putAt getAt getValue getValueAt

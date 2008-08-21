/*
 o---------------------------------------------------------------------o
 |
 | COS IntVector and IntSubVector
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
 | $Id: VectorInt.c,v 1.1 2008/08/21 15:54:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/Number.h>
#include <cos/Range.h>
#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(IntVector   , Vector);
makclass(IntVector0  , IntVector);
makclass(IntVector1  , IntVector);
makclass(IntVector2  , IntVector);
makclass(IntVector3  , IntVector);
makclass(IntVector4  , IntVector);
makclass(IntVector5  , IntVector);
makclass(IntVector6  , IntVector);
makclass(IntVector7  , IntVector);
makclass(IntVector8  , IntVector);
makclass(IntVector9  , IntVector);
makclass(IntVectorN  , IntVector);
makclass(IntSubVector, IntVector);
makclass(IntDynVector, IntVector);

// ----- helpers

static struct IntVector*
vector_new(U32 size)
{
  enum { N = 10 };
  static const OBJ cls[N] = {
    classref(IntVector0),classref(IntVector1),classref(IntVector2),classref(IntVector3),
    classref(IntVector4),classref(IntVector5),classref(IntVector6),classref(IntVector7), 
    classref(IntVector8),classref(IntVector9) }; 

  OBJ _cl = size >= N ? classref(IntVectorN) : cls[size];
  OBJ _sz = aInt(size * sizeof(DOUBLE));
  OBJ _vec = gallocWith(_cl, _sz);
  struct IntVector * vec  = (struct IntVector *)_vec;
  struct IntVectorN* vecn = (struct IntVectorN*)_vec;

  vec->size  = size;
  vec->value = vecn->_value;

  return vec;
}

// ----- constructors

defmethod(OBJ, ginitWith, mIntVector, IntVector)
  struct IntVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mIntSubVector, IntVector, Range1)
  useclass(IntSubVector);

  OBJ _vec = gallocWith(IntSubVector, aInt(0));
  OBJ _src = gretain(_2);

  struct IntVector*     vec = (struct IntVector    *)_vec;
  struct IntSubVector* svec = (struct IntSubVector *)_vec;
  struct IntVector*     src = (struct IntVector    *)_src;

  svec->vector = _src;
  vec->size  = self3->size;

  if (self3->start < 0)
    vec->value = src->value - self3->start + src->size;
  else
    vec->value = src->value + self3->start;

  retmethod(_vec);
endmethod

// ----- copy constructor

defmethod(OBJ, ginitWith, IntVector, IntVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, IntVector, IntVector)
  BOOL res = self1->size == self2->size;

  for (U32 i = 0; res && i < self->size; i++)
    res = self1->value[i] == self2->value[i];

  retmethod( res ? True : False );
endmethod


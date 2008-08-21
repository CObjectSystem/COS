/*
 o---------------------------------------------------------------------o
 |
 | COS LngVector and LngSubVector
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
 | $Id: VectorLng.c,v 1.1 2008/08/21 15:54:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/Number.h>
#include <cos/Range.h>
#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(LngVector   , Vector);
makclass(LngVector0  , LngVector);
makclass(LngVector1  , LngVector);
makclass(LngVector2  , LngVector);
makclass(LngVector3  , LngVector);
makclass(LngVector4  , LngVector);
makclass(LngVector5  , LngVector);
makclass(LngVector6  , LngVector);
makclass(LngVector7  , LngVector);
makclass(LngVector8  , LngVector);
makclass(LngVector9  , LngVector);
makclass(LngVectorN  , LngVector);
makclass(LngSubVector, LngVector);
makclass(LngDynVector, LngVector);

// ----- helpers

static struct LngVector*
vector_new(U32 size)
{
  enum { N = 10 };
  static const OBJ cls[N] = {
    classref(LngVector0),classref(LngVector1),classref(LngVector2),classref(LngVector3),
    classref(LngVector4),classref(LngVector5),classref(LngVector6),classref(LngVector7), 
    classref(LngVector8),classref(LngVector9) }; 

  OBJ _cl = size >= N ? classref(LngVectorN) : cls[size];
  OBJ _sz = aInt(size * sizeof(DOUBLE));
  OBJ _vec = gallocWith(_cl, _sz);
  struct LngVector * vec  = (struct LngVector *)_vec;
  struct LngVectorN* vecn = (struct LngVectorN*)_vec;

  vec->size  = size;
  vec->value = vecn->_value;

  return vec;
}

// ----- constructors

defmethod(OBJ, ginitWith, mLngVector, IntVector)
  struct LngVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mLngVector, LngVector)
  struct LngVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mLngSubVector, LngVector, Range1)
  useclass(LngSubVector);

  OBJ _vec = gallocWith(LngSubVector, aInt(0));
  OBJ _src = gretain(_2);

  struct LngVector*     vec = (struct LngVector    *)_vec;
  struct LngSubVector* svec = (struct LngSubVector *)_vec;
  struct LngVector*     src = (struct LngVector    *)_src;

  svec->vector = _src;
  vec->size = self3->size;

  if (self3->start < 0)
    vec->value = src->value - self3->start + src->size;
  else
    vec->value = src->value + self3->start;

  retmethod(_vec);
endmethod

// ----- copy constructor

defmethod(OBJ, ginitWith, LngVector, LngVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, LngVector, LngVector)
  BOOL res = self1->size == self2->size;

  for (U32 i = 0; res && i < self->size; i++)
    res = self1->value[i] == self2->value[i];

  retmethod( res ? True : False );
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS CpxVector and CpxSubVector
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
 | $Id: VectorCpx.c,v 1.1 2008/08/21 15:54:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/Number.h>
#include <cos/Range.h>
#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(CpxVector   , Vector);
makclass(CpxVector0  , CpxVector);
makclass(CpxVector1  , CpxVector);
makclass(CpxVector2  , CpxVector);
makclass(CpxVector3  , CpxVector);
makclass(CpxVector4  , CpxVector);
makclass(CpxVector5  , CpxVector);
makclass(CpxVector6  , CpxVector);
makclass(CpxVector7  , CpxVector);
makclass(CpxVector8  , CpxVector);
makclass(CpxVector9  , CpxVector);
makclass(CpxVectorN  , CpxVector);
makclass(CpxSubVector, CpxVector);
makclass(CpxDynVector, CpxVector);

// ----- helpers

static struct CpxVector*
vector_new(U32 size)
{
  enum { N = 10 };
  static const OBJ cls[N] = {
    classref(CpxVector0),classref(CpxVector1),classref(CpxVector2),classref(CpxVector3),
    classref(CpxVector4),classref(CpxVector5),classref(CpxVector6),classref(CpxVector7), 
    classref(CpxVector8),classref(CpxVector9) }; 

  OBJ _cl = size >= N ? classref(CpxVectorN) : cls[size];
  OBJ _sz = aInt(size * sizeof(COMPLEX));
  OBJ _vec = gallocWith(_cl, _sz);
  struct CpxVector * vec  = (struct CpxVector *)_vec;
  struct CpxVectorN* vecn = (struct CpxVectorN*)_vec;

  vec->size  = size;
  vec->value = vecn->_value;

  return vec;
}

// ----- constructors

defmethod(OBJ, ginitWith, mCpxVector, IntVector)
  struct CpxVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mCpxVector, LngVector)
  struct CpxVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mCpxVector, DblVector)
  struct CpxVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith, mCpxVector, CpxVector)
  struct CpxVector* vec = vector_new(self2->size);

  for (U32 i = 0; i < self2->size; i++)
    vec->value[i] = self2->value[i];

  retmethod((OBJ)vec);
endmethod

defmethod(OBJ, ginitWith2, mCpxSubVector, CpxVector, Range1)
  useclass(CpxSubVector);

  OBJ _vec = gallocWith(CpxSubVector, aInt(0));
  OBJ _src = gretain(_2);

  struct CpxVector*     vec = (struct CpxVector    *)_vec;
  struct CpxSubVector* svec = (struct CpxSubVector *)_vec;
  struct CpxVector*     src = (struct CpxVector    *)_src;

  svec->vector = _src;
  vec->size = self3->size;

  if (self3->start < 0)
    vec->value = src->value - self3->start + src->size;
  else
    vec->value = src->value + self3->start;

  retmethod(_vec);
endmethod

// ----- copy constructor

defmethod(OBJ, ginitWith, CpxVector, CpxVector)
  test_assert(self1->size == self2->size);

  for (U32 i = 0; i < self->size; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, CpxVector, CpxVector)
  BOOL res = self1->size == self2->size;

  for (U32 i = 0; res && i < self->size; i++)
    res = cpx_equal(self1->value[i], self2->value[i]);

  retmethod( res ? True : False );
endmethod


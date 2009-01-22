#ifndef COS_FLTVECTOR_P_H
#define COS_FLTVECTOR_P_H

/*
 o---------------------------------------------------------------------o
 |
 | COS FltVector (private shared implementation)
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
 | $Id: FltVector_p.h,v 1.2 2009/01/22 16:45:08 ldeniau Exp $
 |
*/

static inline BOOL
vector_isa(OBJ _1)
{
  return cos_any_superClass(_1) == classref(   FltVector) ||
         cos_any_isa(       _1  ,  classref(FltDynVector));
}

static inline struct FltVector*
vector_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[N] = {
    classref(FltVector0,FltVector1,FltVector2,FltVector3,FltVector4,
             FltVector5,FltVector6,FltVector7,FltVector8,FltVector9) }; 

  useclass(FltVectorN);

  OBJ _cls = size >= N ? FltVectorN : (OBJ)cls[size];
  OBJ _vec = gallocWithSize(_cls, size * sizeof(F64));
  struct FltVectorN *nvec = STATIC_CAST(struct FltVectorN*, _vec);
  struct FltVector  * vec = &nvec->FltVector;

  vec->size  = size;
  vec->value = nvec->_value;

  return vec;
}

static inline struct FltVector*
subvector_alloc(struct FltVector *ref, U32 start, U32 size)
{
  useclass(FltSubVector);

  OBJ _vec = gallocWithSize(FltSubVector, 0);
  struct FltSubVector *svec = STATIC_CAST(struct FltSubVector*, _vec);
  struct FltVector    * vec = &svec->FltVector;

  vec->size  = size;
  vec->value = ref->value + start;
  svec->vector = (OBJ)ref;

  return vec;
}

static inline struct FltVector*
dynvector_alloc(U32 size)
{
  useclass(FltDynVector, ExBadAlloc);

  OBJ _vec = gallocWithSize(FltDynVector, 0);
  struct FltDynVector *dvec = STATIC_CAST(struct FltDynVector*, _vec);
  struct FltVector    * vec = &dvec->FltDynVectorN.FltVector;

  vec->value = malloc(size * sizeof *vec->value);
  
  if (!vec->value) {
    gdealloc(_vec);
    THROW(ExBadAlloc);
  }

  dvec->capacity = size;

  return vec;
}

static void
dynvector_resizeBy(struct FltDynVector *dvec, float factor)
{
  useclass(ExBadAlloc);

  struct FltVector *vec = &dvec->FltDynVectorN.FltVector;
  U32  size  = dvec->capacity * factor;
  F64 *value = realloc(vec->value, size * sizeof(OBJ));

  if (!value) THROW(ExBadAlloc);
  
  vec->value = value;
  dvec->capacity = size;
}

#endif // COS_FLTVECTOR_P_H


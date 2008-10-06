#ifndef COS_VECTOR_H
#define COS_VECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Vectors and SubVectors
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
 | $Id: Vector.h,v 1.3 2008/10/06 17:34:58 ldeniau Exp $
 |
*/

#include <cos/Index.h>

/* Vector subclasses:
<- Vector
   <- IntVector  <- IntVectorN (0..9)
                 <- IntDynVectorN <- IntDynVector
                 <- IntSubVector
   <- LngVector  <- LngVectorN (0..9)
                 <- LngDynVectorN <- LngDynVector
                 <- LngSubVector
   <- DblVector  <- DblVectorN (0..9)
                 <- DblDynVectorN <- DblDynVector
                 <- DblSubVector
   <- CpxVector  <- CpxVectorN (0..9)
                 <- CpxDynVectorN <- CpxDynVector
                 <- CpxSubVector
*/

defclass(Vector)
endclass

// ----- Vectors

defclass(IntVector, Vector)
  I32 *value;
  U32  size;
endclass

defclass(LngVector, Vector)
  I64 *value;
  U32  size;
endclass

defclass(DblVector, Vector)
  R64 *value;
  U32  size;
endclass

defclass(CpxVector, Vector)
  C64 *value;
  U32  size;
endclass

// ----- Dynamic Vectors

defclass(IntDynVectorN, IntVector) endclass
defclass(LngDynVectorN, LngVector) endclass
defclass(DblDynVectorN, DblVector) endclass
defclass(CpxDynVectorN, CpxVector) endclass

defclass(IntDynVector, IntDynVectorN)
  U32 capacity;
endclass

defclass(LngDynVector, LngDynVectorN)
  U32 capacity;
endclass

defclass(DblDynVector, DblDynVectorN)
  U32 capacity;
endclass

defclass(CpxDynVector, CpxDynVectorN)
  U32 capacity;
endclass

// ----- Sub Vectors

defclass(IntSubVector, IntVector)
  OBJ vector;
endclass

defclass(LngSubVector, LngVector)
  OBJ vector;
endclass

defclass(DblSubVector, DblVector)
  OBJ vector;
endclass

defclass(CpxSubVector, CpxVector)
  OBJ vector;
endclass

// ----- Vector of integer (I32)

defclass(IntVector0, IntVector) I32 _value[]; endclass
defclass(IntVector1, IntVector) I32 _value[]; endclass
defclass(IntVector2, IntVector) I32 _value[]; endclass
defclass(IntVector3, IntVector) I32 _value[]; endclass
defclass(IntVector4, IntVector) I32 _value[]; endclass
defclass(IntVector5, IntVector) I32 _value[]; endclass
defclass(IntVector6, IntVector) I32 _value[]; endclass
defclass(IntVector7, IntVector) I32 _value[]; endclass
defclass(IntVector8, IntVector) I32 _value[]; endclass
defclass(IntVector9, IntVector) I32 _value[]; endclass
defclass(IntVectorN, IntVector) I32 _value[]; endclass

#define aIntVec(...)                   aVectorT   (Int,I32,__VA_ARGS__)
#define aIntVecRef(size,array)         aVectorRefT(Int,size,array)
#define aIntSubVec(vector,start,size)  aSubVectorT(Int,vector,start,size)

#define atIntVec(...)                  atVectorT   (Int,I32,__VA_ARGS__)
#define atIntVecRef(size,array)        atVectorRefT(Int,size,array)
#define atIntSubVec(vector,start,size) atSubVectorT(Int,vector,start,size)

// ----- Vector of integer (I64)

defclass(LngVector0, LngVector) I64 _value[]; endclass
defclass(LngVector1, LngVector) I64 _value[]; endclass
defclass(LngVector2, LngVector) I64 _value[]; endclass
defclass(LngVector3, LngVector) I64 _value[]; endclass
defclass(LngVector4, LngVector) I64 _value[]; endclass
defclass(LngVector5, LngVector) I64 _value[]; endclass
defclass(LngVector6, LngVector) I64 _value[]; endclass
defclass(LngVector7, LngVector) I64 _value[]; endclass
defclass(LngVector8, LngVector) I64 _value[]; endclass
defclass(LngVector9, LngVector) I64 _value[]; endclass
defclass(LngVectorN, LngVector) I64 _value[]; endclass

#define aLngVec(...)                   aVectorT   (Lng,I64,__VA_ARGS__)
#define aLngVecRef(size,array)         aVectorRefT(Lng,size,array)
#define aLngSubVec(vector,start,size)  aSubVectorT(Lng,vector,start,size)

#define atLngVec(...)                  atVectorT   (Lng,I64,__VA_ARGS__)
#define atLngVecRef(size,array)        atVectorRefT(Lng,size,array)
#define atLngSubVec(vector,start,size) atSubVectorT(Lng,vector,start,size)

// ----- Vector of double

defclass(DblVector0, DblVector) R64 _value[]; endclass
defclass(DblVector1, DblVector) R64 _value[]; endclass
defclass(DblVector2, DblVector) R64 _value[]; endclass
defclass(DblVector3, DblVector) R64 _value[]; endclass
defclass(DblVector4, DblVector) R64 _value[]; endclass
defclass(DblVector5, DblVector) R64 _value[]; endclass
defclass(DblVector6, DblVector) R64 _value[]; endclass
defclass(DblVector7, DblVector) R64 _value[]; endclass
defclass(DblVector8, DblVector) R64 _value[]; endclass
defclass(DblVector9, DblVector) R64 _value[]; endclass
defclass(DblVectorN, DblVector) R64 _value[]; endclass

#define aDblVec(...)                   aVectorT   (Dbl,R64,__VA_ARGS__)
#define aDblVecRef(size,array)         aVectorRefT(Dbl,size,array)
#define aDblSubVec(vector,start,size)  aSubVectorT(Dbl,vector,start,size)

#define atDblVec(...)                  atVectorT   (Dbl,R64,__VA_ARGS__)
#define atDblVecRef(size,array)        atVectorRefT(Dbl,size,array)
#define atDblSubVec(vector,start,size) atSubVectorT(Dbl,vector,start,size)

// ----- Vector of complex

defclass(CpxVector0, CpxVector) C64 _value[]; endclass
defclass(CpxVector1, CpxVector) C64 _value[]; endclass
defclass(CpxVector2, CpxVector) C64 _value[]; endclass
defclass(CpxVector3, CpxVector) C64 _value[]; endclass
defclass(CpxVector4, CpxVector) C64 _value[]; endclass
defclass(CpxVector5, CpxVector) C64 _value[]; endclass
defclass(CpxVector6, CpxVector) C64 _value[]; endclass
defclass(CpxVector7, CpxVector) C64 _value[]; endclass
defclass(CpxVector8, CpxVector) C64 _value[]; endclass
defclass(CpxVector9, CpxVector) C64 _value[]; endclass
defclass(CpxVectorN, CpxVector) C64 _value[]; endclass

#define aCpxVec(...)                   aVectorT   (Cpx,C64,__VA_ARGS__)
#define aCpxVecRef(size,array)         aVectorRefT(Cpx,size,array)
#define aCpxSubVec(vector,start,size)  aSubVectorT(Cpx,vector,start,size)

#define atCpxVec(...)                  atVectorT   (Cpx,C64,__VA_ARGS__)
#define atCpxVecRef(size,array)        atVectorRefT(Cpx,size,array)
#define atCpxSubVec(vector,start,size) atSubVectorT(Cpx,vector,start,size)

// ----- automatic constructors implementation

#define aVectorT(P,T,...) \
        ( (OBJ)atVectorT(P,T,__VA_ARGS__) )
#define atVectorT(P,T,...) \
        atVectorN(P,T,COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),10)) \
                  (N,COS_PP_NARG(__VA_ARGS__)),__VA_ARGS__)
#define atVectorN(P,T,N,...) \
        ( (struct COS_PP_CAT(P,Vector)*)&(struct COS_PP_CAT3(P,Vector,N)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT3(P,Vector,N)).Behavior.id, COS_RC_AUTO }}}, \
          (T[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__) }} )

#define aVectorRefT(P,size,array) \
        ( (OBJ)atVectorRefT(P,size,array) )
#define atVectorRefT(P,size,array) \
        ( &(struct COS_PP_CAT(P,Vector)) { \
          {{{ COS_CLS_NAME(COS_PP_CAT(P,Vector)).Behavior.id, COS_RC_AUTO }}}, \
          (array), (size) } )

#define aSubVectorT(P,vector,substart,subsize) \
        ( (OBJ)atSubVectorT(P,vector,substart,subsize) )
#define atSubVectorT(P,vector,substart,subsize) \
        ( COS_PP_CAT(P,SubVector_init)(&(struct COS_PP_CAT(P,SubVector)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT(P,SubVector)).Behavior.id, COS_RC_AUTO }}}, \
          (subsize), 0 }, (vector) }, (substart)) )

// ----- automatic sub-vectors init/checker

static inline struct IntSubVector*
IntSubVector_init(struct IntSubVector *subvec, I32 substart)
{
  useclass(IntVector);

  OBJ vec_spr = (OBJ)cos_class_get(cos_any_id(subvec->vector))->spr;
  struct IntVector *svec = &subvec->IntVector;
  struct IntVector *vec  = STATIC_CAST(struct IntVector*, subvec->vector);
  U32 start;

  test_assert( vec_spr == IntVector );
  start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size );
  svec->value = vec->value + start;

  return subvec;
}

static inline struct LngSubVector*
LngSubVector_init(struct LngSubVector *subvec, I32 substart)
{
  useclass(LngVector);

  OBJ vec_spr = (OBJ)cos_class_get(cos_any_id(subvec->vector))->spr;
  struct LngVector *svec = &subvec->LngVector;
  struct LngVector *vec  = STATIC_CAST(struct LngVector*, subvec->vector);
  U32 start;

  test_assert( vec_spr == LngVector );
  start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size );
  svec->value = vec->value + start;

  return subvec;
}

static inline struct DblSubVector*
DblSubVector_init(struct DblSubVector *subvec, I32 substart)
{
  useclass(DblVector);

  OBJ vec_spr = (OBJ)cos_class_get(cos_any_id(subvec->vector))->spr;
  struct DblVector *svec = &subvec->DblVector;
  struct DblVector *vec  = STATIC_CAST(struct DblVector*, subvec->vector);
  U32 start;

  test_assert( vec_spr == DblVector );
  start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size );
  svec->value = vec->value + start;

  return subvec;
}

static inline struct CpxSubVector*
CpxSubVector_init(struct CpxSubVector *subvec, I32 substart)
{
  useclass(CpxVector);

  OBJ vec_spr = (OBJ)cos_class_get(cos_any_id(subvec->vector))->spr;
  struct CpxVector *svec = &subvec->CpxVector;
  struct CpxVector *vec  = STATIC_CAST(struct CpxVector*, subvec->vector);
  U32 start;

  test_assert( vec_spr == CpxVector );
  start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size );
  svec->value = vec->value + start;

  return subvec;
}

#endif // COS_VECTOR_H

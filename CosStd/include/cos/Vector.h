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
 | $Id: Vector.h,v 1.8 2009/01/22 16:45:07 ldeniau Exp $
 |
*/

/* Vector subclasses:
<- Vector
   <- IntVector  <- IntVectorN (0..9)
                 <- IntDynVectorN <- IntDynVector
                 <- IntSubVector
   <- LngVector  <- LngVectorN (0..9)
                 <- LngDynVectorN <- LngDynVector
                 <- LngSubVector
   <- FltVector  <- FltVectorN (0..9)
                 <- FltDynVectorN <- FltDynVector
                 <- FltSubVector
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

defclass(FltVector, Vector)
  F64 *value;
  U32  size;
endclass

defclass(CpxVector, Vector)
  C64 *value;
  U32  size;
endclass

// ----- Dynamic Vectors

defclass(IntDynVectorN, IntVector) endclass
defclass(LngDynVectorN, LngVector) endclass
defclass(FltDynVectorN, FltVector) endclass
defclass(CpxDynVectorN, CpxVector) endclass

defclass(IntDynVector, IntDynVectorN)
  U32 capacity;
endclass

defclass(LngDynVector, LngDynVectorN)
  U32 capacity;
endclass

defclass(FltDynVector, FltDynVectorN)
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

defclass(FltSubVector, FltVector)
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

#define aIntVector(...)                  ( (OBJ)atIntVector   (__VA_ARGS__      ) )
#define aIntVectorRef(size,array)        ( (OBJ)atIntVectorRef(size,array       ) )
#define aIntSubVector(vector,start,size) ( (OBJ)atIntSubVector(vector,start,size) )

#define atIntVector(...)                  atVectorT   (Int,I32,__VA_ARGS__)
#define atIntVectorRef(size,array)        atVectorRefT(Int,size,array)
#define atIntSubVector(vector,start,size) atSubVectorT(Int,vector,start,size)

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

#define aLngVector(...)                  ( (OBJ)atLngVector   (__VA_ARGS__      ) )
#define aLngVectorRef(size,array)        ( (OBJ)atLngVectorRef(size,array       ) )
#define aLngSubVector(vector,start,size) ( (OBJ)atLngSubVector(vector,start,size) )

#define atLngVector(...)                  atVectorT   (Lng,I64,__VA_ARGS__)
#define atLngVectorRef(size,array)        atVectorRefT(Lng,size,array)
#define atLngSubVector(vector,start,size) atSubVectorT(Lng,vector,start,size)

// ----- Vector of double

defclass(FltVector0, FltVector) F64 _value[]; endclass
defclass(FltVector1, FltVector) F64 _value[]; endclass
defclass(FltVector2, FltVector) F64 _value[]; endclass
defclass(FltVector3, FltVector) F64 _value[]; endclass
defclass(FltVector4, FltVector) F64 _value[]; endclass
defclass(FltVector5, FltVector) F64 _value[]; endclass
defclass(FltVector6, FltVector) F64 _value[]; endclass
defclass(FltVector7, FltVector) F64 _value[]; endclass
defclass(FltVector8, FltVector) F64 _value[]; endclass
defclass(FltVector9, FltVector) F64 _value[]; endclass
defclass(FltVectorN, FltVector) F64 _value[]; endclass

#define aFltVector(...)                  ( (OBJ)atFltVector   (__VA_ARGS__      ) )
#define aFltVectorRef(size,array)        ( (OBJ)atFltVectorRef(size,array       ) )
#define aFltSubVector(vector,start,size) ( (OBJ)atFltSubVector(vector,start,size) )

#define atFltVector(...)                  atVectorT   (Flt,F64,__VA_ARGS__)
#define atFltVectorRef(size,array)        atVectorRefT(Flt,size,array)
#define atFltSubVector(vector,start,size) atSubVectorT(Flt,vector,start,size)

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

#define aCpxVector(...)                  ( (OBJ)atCpxVector   (__VA_ARGS__      ) )
#define aCpxVectorRef(size,array)        ( (OBJ)atCpxVectorRef(size,array       ) )
#define aCpxSubVector(vector,start,size) ( (OBJ)atCpxSubVector(vector,start,size) )

#define atCpxVector(...)                  atVectorT   (Cpx,C64,__VA_ARGS__)
#define atCpxVectorRef(size,array)        atVectorRefT(Cpx,size,array)
#define atCpxSubVector(vector,start,size) atSubVectorT(Cpx,vector,start,size)

// ----- automatic constructors implementation

#define atVectorT(P,T,...) \
        atVectorN(P,T,COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),10)) \
                  (N,COS_PP_NARG(__VA_ARGS__)),__VA_ARGS__)
#define atVectorN(P,T,N,...) \
        ( (struct COS_PP_CAT(P,Vector)*)&(struct COS_PP_CAT3(P,Vector,N)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT3(P,Vector,N)).Behavior.id, COS_RC_AUTO }}}, \
          (T[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__) }} )

#define atVectorRefT(P,size,array) \
        ( &(struct COS_PP_CAT(P,Vector)) { \
          {{{ COS_CLS_NAME(COS_PP_CAT(P,Vector)).Behavior.id, COS_RC_AUTO }}}, \
          (array), (size) } )

#define atSubVectorT(P,vector,substart,subsize) \
        ( COS_PP_CAT(P,SubVector_init)(&(struct COS_PP_CAT(P,SubVector)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT(P,SubVector)).Behavior.id, COS_RC_AUTO }}}, \
          (subsize), 0 }, (vector) }, (substart)) )

// ----- automatic sub-vectors init/checker

#ifndef COS_VALUE_H
#include <cos/Value.h>
#endif

static inline struct IntVector*
IntSubVector_init(struct IntSubVector *subvec, I32 substart)
{
  test_assert( cos_any_superClass(subvec->vector) == classref(IntVector),
               "subvector accepts only fixed size vector" );

  struct IntVector *svec = &subvec->IntVector;
  struct IntVector * vec = STATIC_CAST(struct IntVector*, subvec->vector);

  U32 start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size, "subvector out of range" );

  svec->value = vec->value + start;

  return svec;
}

static inline struct LngVector*
LngSubVector_init(struct LngSubVector *subvec, I32 substart)
{
  test_assert( cos_any_superClass(subvec->vector) == classref(LngVector),
               "subvector accepts only fixed size vector" );

  struct LngVector *svec = &subvec->LngVector;
  struct LngVector * vec = STATIC_CAST(struct LngVector*, subvec->vector);

  U32 start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size, "subvector out of range" );

  svec->value = vec->value + start;

  return svec;
}

static inline struct FltVector*
FltSubVector_init(struct FltSubVector *subvec, I32 substart)
{
  test_assert( cos_any_superClass(subvec->vector) == classref(FltVector),
               "subvector accepts only fixed size vector" );

  struct FltVector *svec = &subvec->FltVector;
  struct FltVector * vec = STATIC_CAST(struct FltVector*, subvec->vector);

  U32 start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size, "subvector out of range" );

  svec->value = vec->value + start;

  return svec;
}

static inline struct CpxVector*
CpxSubVector_init(struct CpxSubVector *subvec, I32 substart)
{
  test_assert( cos_any_superClass(subvec->vector) == classref(CpxVector),
               "subvector accepts only fixed size vector" );

  struct CpxVector *svec = &subvec->CpxVector;
  struct CpxVector * vec = STATIC_CAST(struct CpxVector*, subvec->vector);

  U32 start = index_abs(substart, vec->size);
  test_assert( start + svec->size <= vec->size, "subvector out of range" );

  svec->value = vec->value + start;

  return svec;
}

#endif // COS_VECTOR_H

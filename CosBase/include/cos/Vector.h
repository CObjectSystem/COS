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
 | $Id: Vector.h,v 1.1 2008/08/21 15:53:43 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

/* Vector subclasses:
<- Vector
   <- IntVector  <- IntVector0..9,N
                 <- IntSubVector
                 <- IntDynVector
   <- LngVector  <- LngVector0..9
                 <- LngSubVector
                 <- LngDynVector
   <- DblVector  <- DblVector0..9,N
                 <- DblSubVector
                 <- DblDynVector
   <- CpxVector  <- CpxVector0..9,N
                 <- CpxSubVector
                 <- CpxDynVector
   <- IntVectorView (sliced)
   <- LngVectorView (sliced)
   <- DblVectorView (sliced)
   <- CpxVectorView (sliced)
*/

defclass(Vector)
endclass

// ----- Vectors

defclass(IntVector, Vector)
  S32 *value;
  U32  size;
endclass

defclass(LngVector, Vector)
  S64 *value;
  U32  size;
endclass

defclass(DblVector, Vector)
  DOUBLE *value;
  U32     size;
endclass

defclass(CpxVector, Vector)
  COMPLEX *value;
  U32      size;
endclass

// ----- Dynamic Vectors

defclass(IntDynVector, IntVector)
  U32 capacity;
  U32 refcnt;
endclass

defclass(LngDynVector, LngVector)
  U32 capacity;
  U32 refcnt;
endclass

defclass(DblDynVector, DblVector)
  U32 capacity;
  U32 refcnt;
endclass

defclass(CpxDynVector, CpxVector)
  U32 capacity;
  U32 refcnt;
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

// ----- Vector of integer (S32)

defclass(IntVector0, IntVector) S32 _value[]; endclass
defclass(IntVector1, IntVector) S32 _value[]; endclass
defclass(IntVector2, IntVector) S32 _value[]; endclass
defclass(IntVector3, IntVector) S32 _value[]; endclass
defclass(IntVector4, IntVector) S32 _value[]; endclass
defclass(IntVector5, IntVector) S32 _value[]; endclass
defclass(IntVector6, IntVector) S32 _value[]; endclass
defclass(IntVector7, IntVector) S32 _value[]; endclass
defclass(IntVector8, IntVector) S32 _value[]; endclass
defclass(IntVector9, IntVector) S32 _value[]; endclass
defclass(IntVectorN, IntVector) S32 _value[]; endclass

#define aIntVec(...) \
        aVectorT(Int,S32,__VA_ARGS__)

#define aIntSubVec(vector,start,size) \
        aSubVectorT(Int,vector,start,size)

#define aIntVecRef(size,array) \
        aVectorRefT(Int,size,array)

// ----- Vector of integer (S64)

defclass(LngVector0, LngVector) S64 _value[]; endclass
defclass(LngVector1, LngVector) S64 _value[]; endclass
defclass(LngVector2, LngVector) S64 _value[]; endclass
defclass(LngVector3, LngVector) S64 _value[]; endclass
defclass(LngVector4, LngVector) S64 _value[]; endclass
defclass(LngVector5, LngVector) S64 _value[]; endclass
defclass(LngVector6, LngVector) S64 _value[]; endclass
defclass(LngVector7, LngVector) S64 _value[]; endclass
defclass(LngVector8, LngVector) S64 _value[]; endclass
defclass(LngVector9, LngVector) S64 _value[]; endclass
defclass(LngVectorN, LngVector) S64 _value[]; endclass

#define aLngVec(...) \
        aVectorT(Lng,S64,__VA_ARGS__)

#define aLngSubVec(vector,start,size) \
        aSubVectorT(Lng,vector,start,size)

#define aLngVecRef(size,array) \
        aVectorRefT(Lng,size,array)

// ----- Vector of double

defclass(DblVector0, DblVector) DOUBLE _value[]; endclass
defclass(DblVector1, DblVector) DOUBLE _value[]; endclass
defclass(DblVector2, DblVector) DOUBLE _value[]; endclass
defclass(DblVector3, DblVector) DOUBLE _value[]; endclass
defclass(DblVector4, DblVector) DOUBLE _value[]; endclass
defclass(DblVector5, DblVector) DOUBLE _value[]; endclass
defclass(DblVector6, DblVector) DOUBLE _value[]; endclass
defclass(DblVector7, DblVector) DOUBLE _value[]; endclass
defclass(DblVector8, DblVector) DOUBLE _value[]; endclass
defclass(DblVector9, DblVector) DOUBLE _value[]; endclass
defclass(DblVectorN, DblVector) DOUBLE _value[]; endclass

#define aDblVec(...) \
        aVectorT(Dbl,DOUBLE,__VA_ARGS__)

#define aDblSubVec(vector,start,size) \
        aSubVectorT(Dbl,vector,start,size)

#define aDblVecRef(size,array) \
        aVectorRefT(Dbl,size,array)

// ----- Vector of complex

defclass(CpxVector0, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector1, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector2, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector3, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector4, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector5, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector6, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector7, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector8, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVector9, CpxVector) COMPLEX _value[]; endclass
defclass(CpxVectorN, CpxVector) COMPLEX _value[]; endclass

#define aCpxVec(...) \
        aVectorT(Cpx,COMPLEX,__VA_ARGS__)

#define aCpxSubVec(vector,start,size) \
        aSubVectorT(Cpx,vector,start,size)

#define aCpxVecRef(size,array) \
        aVectorRefT(Cpx,size,array)

// ----- automatic constructors implementation

#define aVectorT(P,T,...) \
        aVectorN(P,T,COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),10)) \
                 (N,COS_PP_NARG(__VA_ARGS__)),__VA_ARGS__)

#define aVectorN(P,T,N,...) \
        ( (OBJ)&(struct COS_PP_CAT3(P,Vector,N)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT3(P,Vector,N)).Behavior.id, COS_RC_AUTO }}}, \
          (T[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__) }} )

#define aSubVectorT(P,vector,start,size) \
        ( (OBJ)&(struct COS_PP_CAT(P,SubVector)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT(P,SubVector)).Behavior.id, COS_RC_AUTO }}}, \
          (vector)->value+(start), (size) }, (OBJ)(vector) } )

#define aVectorRefT(P,size,array) \
        ( (OBJ)&(struct COS_PP_CAT(P,Vector)) { \
          {{{ COS_CLS_NAME(COS_PP_CAT(P,Vector)).Behavior.id, COS_RC_AUTO }}}, \
          (array), (size) } )

#endif // COS_VECTOR_H

#ifndef COS_FLTVECTOR_H
#define COS_FLTVECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Float Vector, Dynamic Vector and Vector View
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
 | $Id: FltVector.h,v 1.2 2009/02/27 23:28:53 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: FltVector class cluster constructors

   see cos/Vector.h
*/

defclass(FltVector, Vector)
  U32  size;
  I32  stride;
  F64 *value;
endclass

// ----- automatic constructors

#define aFltVector(...)        ( (OBJ)atFltVector       (__VA_ARGS__) )
#define aFltVectorRef(...)     ( (OBJ)atFltVectorRef    (__VA_ARGS__) )
#define aFltVectorView(...)    ( (OBJ)atFltVectorView   (__VA_ARGS__) )
#define aFltVectorSubview(...) ( (OBJ)atFltVectorSubview(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aFltVec(...)         aFltVector       (__VA_ARGS__)
#define aFltVecRef(...)      aFltVectorRef    (__VA_ARGS__)
#define aFltVecView(...)     aFltVectorView   (__VA_ARGS__)
#define aFltVecSubview(...)  aFltVectorSubview(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Vector view

defclass(FltVectorView, FltVector)
  OBJ vector;
endclass

// ----- Dynamic vector

defclass(FltVectorDynamicN, FltVector)
  F64 *base;
endclass

// ---

defclass(FltVectorDynamic, FltVectorDynamicN)
  U32 capacity;
endclass

// ----- Fixed size vector

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

// ----- allocators and initializers

struct FltVector* FltVector_alloc         (U32);
struct FltVector* FltVectorView_alloc     (struct FltVector*,U32,U32,U32);
struct FltVector* FltVectorView_init      (struct FltVectorView*,I32);
struct FltVector* FltVectorSubview_init   (struct FltVectorView*,I32);
struct FltVector* FltVectorDynamic_alloc  (U32);
void              FltVectorDynamic_adjust (struct FltVectorDynamic*);
void              FltVectorDynamic_enlarge(struct FltVectorDynamic*,F64);

// ----- automatic constructors

#define atFltVector(...)         atVector       (Flt,F64,__VA_ARGS__)
#define atFltVectorRef(...)      atVectorRef    (Flt,F64,__VA_ARGS__)
#define atFltVectorView(...)     atVectorView   (Flt,F64,__VA_ARGS__)
#define atFltVectorSubview(...)  atVectorSubview(Flt,F64,__VA_ARGS__)

#endif // COS_FLTVECTOR_H

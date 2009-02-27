#ifndef COS_CPXVECTOR_H
#define COS_CPXVECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Complex Vector, Dynamic Vector and Vector View
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
 | $Id: CpxVector.h,v 1.1 2009/02/27 20:14:25 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: CpxVector class cluster constructors

   see cos/Vector.h
*/

defclass(CpxVector, Vector)
  U32  size;
  I32  stride;
  C64 *value;
endclass

// ----- automatic constructors

#define aCpxVector(...)     ( (OBJ)atCpxVector    (__VA_ARGS__) )
#define aCpxVectorRef(...)  ( (OBJ)atCpxVectorRef (__VA_ARGS__) )
#define aCpxVectorView(...) ( (OBJ)atCpxVectorView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aCpxVec(...)      aCpxVector    (__VA_ARGS__)
#define aCpxVecRef(...)   aCpxVectorRef (__VA_ARGS__)
#define aCpxVecView(...)  aCpxVectorView(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Vector view

defclass(CpxVectorView, CpxVector)
  OBJ vector;
endclass

// ----- Dynamic vector

defclass(CpxVectorDynamicN, CpxVector)
  C64 *base;
endclass

// ---

defclass(CpxVectorDynamic, CpxVectorDynamicN)
  U32 capacity;
endclass

// ----- Fixed size vector

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

// ----- allocators and initializers

struct CpxVector* CpxVector_alloc         (U32);
struct CpxVector* CpxVectorView_alloc     (struct CpxVector*,U32,U32,U32);
struct CpxVector* CpxVectorView_init      (struct CpxVectorView*,I32);
struct CpxVector* CpxVectorDynamic_alloc  (U32);
void              CpxVectorDynamic_adjust (struct CpxVectorDynamic*);
void              CpxVectorDynamic_enlarge(struct CpxVectorDynamic*,F64);

// ----- automatic constructors

#define atCpxVector(...)      atVector    (Cpx,C64,__VA_ARGS__)
#define atCpxVectorRef(...)   atVectorRef (Cpx,C64,__VA_ARGS__)
#define atCpxVectorView(...)  atVectorView(Cpx,C64,__VA_ARGS__)

#endif // COS_CPXVECTOR_H

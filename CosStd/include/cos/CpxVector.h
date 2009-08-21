#ifndef COS_CPXVECTOR_H
#define COS_CPXVECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Vector, Dynamic Vector, Lazy Vector and Vector View
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
 | $Id: CpxVector.h,v 1.4 2009/08/21 12:27:46 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: CpxVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(CpxVector, Vector)
  C64 *value;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aCpxVector(...)     ( (OBJ)atCpxVector    (__VA_ARGS__) )
#define aCpxVectorRef(...)  ( (OBJ)atCpxVectorRef (__VA_ARGS__) )
#define aCpxVectorView(...) ( (OBJ)atCpxVectorView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aCVec(...)  aCpxVector(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Block vector

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

// ----- Fixed vector, Dynamic vector and Lazy vector

defclass(CpxVectorFix, CpxVector)
  C64 *_value;
  U32  _cls;
  U32  capacity;
endclass

defclass(CpxVectorDyn, CpxVectorFix)
endclass

defclass(CpxVectorLzy, CpxVectorDyn)
  OBJ generator;
  I32 arity;
endclass

// ----- CpxVector view

defclass(CpxVectorView, CpxVector)
  struct CpxVector *vector;
endclass

// ----- allocators and initializers

struct Slice;
struct CpxVector* CpxVector_alloc(U32);
struct CpxVector* CpxVectorView_init(struct CpxVectorView*, struct CpxVector*,
                                     struct Slice*);

// ----- automatic constructors

#define atCpxVector(...)              atVector    (Cpx,C64,__VA_ARGS__)
#define atCpxVectorRef(buffer,size)   atVectorRef (Cpx,buffer,size)
#define atCpxVectorView(vector,slice) atVectorView(Cpx,vector,slice)

#endif // COS_CPXVECTOR_H

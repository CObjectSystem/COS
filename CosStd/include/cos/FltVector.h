#ifndef COS_FLTVECTOR_H
#define COS_FLTVECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Vector, Dynamic Vector and Vector View
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
 | $Id: FltVector.h,v 1.10 2010/05/31 14:02:23 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: FltVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(FltVector, FloatingVector)
  F64 *value;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aFltVector(...)        ( (OBJ)atFltVector       (__VA_ARGS__) )
#define aFltVectorRef(...)     ( (OBJ)atFltVectorRef    (__VA_ARGS__) )
#define aFltVectorView(...)    ( (OBJ)atFltVectorView   (__VA_ARGS__) )
#define aFltVectorSubView(...) ( (OBJ)atFltVectorSubView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aFVec(...)  aFltVector(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Block vector

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

// ----- Fixed vector, Dynamic vector and Lazy vector

defclass(FltVectorFix, FltVector)
  F64 *_value;
  U32  capacity;
endclass

defclass(FltVectorDyn, FltVectorFix)
endclass

// ----- FltVector view and subview

defclass(FltVectorView, FltVector)
  struct FltVector *ref;
endclass

defclass(FltVectorSubView, FltVectorView)
endclass

// ----- allocators and initializers

struct Slice;
struct FltVector* FltVector_alloc(U32);
struct FltVector* FltVectorView_init(struct FltVectorView*, struct FltVector*,
                                     struct Slice*, BOOL);

// ----- automatic constructors

#define atFltVector(...)                 atVector    (Flt,F64,__VA_ARGS__)
#define atFltVectorRef(...)              atVectorRef (Flt,    __VA_ARGS__)
#define atFltVectorView(vector,slice)    atVectorView(Flt,vector,slice,COS_NO)
#define atFltVectorSubView(vector,slice) atVectorView(Flt,vector,slice,COS_YES)

#endif // COS_FLTVECTOR_H

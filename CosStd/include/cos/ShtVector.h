#ifndef COS_SHTVECTOR_H
#define COS_SHTVECTOR_H

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
 | $Id: ShtVector.h,v 1.4 2009/09/04 12:09:17 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: ShtVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(ShtVector, IntegralVector)
  I16 *value;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aShtVector(...)        ( (OBJ)atShtVector       (__VA_ARGS__) )
#define aShtVectorRef(...)     ( (OBJ)atShtVectorRef    (__VA_ARGS__) )
#define aShtVectorView(...)    ( (OBJ)atShtVectorView   (__VA_ARGS__) )
#define aShtVectorSubView(...) ( (OBJ)atShtVectorSubView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aSVec(...)  aShtVector(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Block vector

defclass(ShtVector0, ShtVector) I16 _value[]; endclass
defclass(ShtVector1, ShtVector) I16 _value[]; endclass
defclass(ShtVector2, ShtVector) I16 _value[]; endclass
defclass(ShtVector3, ShtVector) I16 _value[]; endclass
defclass(ShtVector4, ShtVector) I16 _value[]; endclass
defclass(ShtVector5, ShtVector) I16 _value[]; endclass
defclass(ShtVector6, ShtVector) I16 _value[]; endclass
defclass(ShtVector7, ShtVector) I16 _value[]; endclass
defclass(ShtVector8, ShtVector) I16 _value[]; endclass
defclass(ShtVector9, ShtVector) I16 _value[]; endclass
defclass(ShtVectorN, ShtVector) I16 _value[]; endclass

// ----- Fixed vector, Dynamic vector and Lazy vector

defclass(ShtVectorFix, ShtVector)
  I16 *_value;
  U32  capacity;
endclass

defclass(ShtVectorDyn, ShtVectorFix)
endclass

defclass(ShtVectorLzy, ShtVectorDyn)
  I32 arity;
  OBJ generator;
endclass

// ----- ShtVector view and subview

defclass(ShtVectorView, ShtVector)
  struct ShtVector *ref;
endclass

defclass(ShtVectorSubView, ShtVectorView)
endclass

// ----- allocators and initializers

struct Slice;
struct ShtVector* ShtVector_alloc(U32);
struct ShtVector* ShtVectorView_init(struct ShtVectorView*, struct ShtVector*,
                                     struct Slice*, BOOL);

// ----- automatic constructors

#define atShtVector(...)                 atVector    (Sht,I16,__VA_ARGS__)
#define atShtVectorRef(buffer,size)      atVectorRef (Sht,buffer,size)
#define atShtVectorView(vector,slice)    atVectorView(Sht,vector,slice,0)
#define atShtVectorSubView(vector,slice) atVectorView(Sht,vector,slice,1)

#endif // COS_SHTVECTOR_H

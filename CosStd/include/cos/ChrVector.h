#ifndef COS_CHRVECTOR_H
#define COS_CHRVECTOR_H

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
 | $Id: ChrVector.h,v 1.2 2009/09/04 12:09:17 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: ChrVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(ChrVector, IntegralVector)
  I8* value;
  U32 size;
  I32 stride;
endclass

// ----- automatic constructors

#define aChrVector(...)        ( (OBJ)atChrVector       (__VA_ARGS__) )
#define aChrVectorRef(...)     ( (OBJ)atChrVectorRef    (__VA_ARGS__) )
#define aChrVectorView(...)    ( (OBJ)atChrVectorView   (__VA_ARGS__) )
#define aChrVectorSubView(...) ( (OBJ)atChrVectorSubView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aCVec(...)  aChrVector(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Block vector

defclass(ChrVector0, ChrVector) I8 _value[]; endclass
defclass(ChrVector1, ChrVector) I8 _value[]; endclass
defclass(ChrVector2, ChrVector) I8 _value[]; endclass
defclass(ChrVector3, ChrVector) I8 _value[]; endclass
defclass(ChrVector4, ChrVector) I8 _value[]; endclass
defclass(ChrVector5, ChrVector) I8 _value[]; endclass
defclass(ChrVector6, ChrVector) I8 _value[]; endclass
defclass(ChrVector7, ChrVector) I8 _value[]; endclass
defclass(ChrVector8, ChrVector) I8 _value[]; endclass
defclass(ChrVector9, ChrVector) I8 _value[]; endclass
defclass(ChrVectorN, ChrVector) I8 _value[]; endclass

// ----- Fixed vector, Dynamic vector and Lazy vector

defclass(ChrVectorFix, ChrVector)
  I8* _value;
  U32  capacity;
endclass

defclass(ChrVectorDyn, ChrVectorFix)
endclass

defclass(ChrVectorLzy, ChrVectorDyn)
  I32 arity;
  OBJ generator;
endclass

// ----- ChrVector view and subview

defclass(ChrVectorView, ChrVector)
  struct ChrVector *ref;
endclass

defclass(ChrVectorSubView, ChrVectorView)
endclass

// ----- allocators and initializers

struct Slice;
struct ChrVector* ChrVector_alloc(U32);
struct ChrVector* ChrVectorView_init(struct ChrVectorView*, struct ChrVector*,
                                     struct Slice*, BOOL);

// ----- automatic constructors

#define atChrVector(...)                 atVector    (Chr,I8,__VA_ARGS__)
#define atChrVectorRef(buffer,size)      atVectorRef (Chr,buffer,size)
#define atChrVectorView(vector,slice)    atVectorView(Chr,vector,slice,0)
#define atChrVectorSubView(vector,slice) atVectorView(Chr,vector,slice,1)

#endif // COS_CHRVECTOR_H

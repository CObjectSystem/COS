#ifndef COS_LNGVECTOR_H
#define COS_LNGVECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Long Vector, Dynamic Vector and Vector View
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
 | $Id: LngVector.h,v 1.2 2009/02/27 23:28:53 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: LngVector class cluster constructors

   see cos/Vector.h
*/

defclass(LngVector, Vector)
  U32  size;
  I32  stride;
  I64 *value;
endclass

// ----- automatic constructors

#define aLngVector(...)        ( (OBJ)atLngVector       (__VA_ARGS__) )
#define aLngVectorRef(...)     ( (OBJ)atLngVectorRef    (__VA_ARGS__) )
#define aLngVectorView(...)    ( (OBJ)atLngVectorView   (__VA_ARGS__) )
#define aLngVectorSubview(...) ( (OBJ)atLngVectorSubview(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aLngVec(...)         aLngVector       (__VA_ARGS__)
#define aLngVecRef(...)      aLngVectorRef    (__VA_ARGS__)
#define aLngVecView(...)     aLngVectorView   (__VA_ARGS__)
#define aLngVecSubview(...)  aLngVectorSubview(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Vector view

defclass(LngVectorView, LngVector)
  OBJ vector;
endclass

// ----- Dynamic vector

defclass(LngVectorDynamicN, LngVector)
  I64 *base;
endclass

// ---

defclass(LngVectorDynamic, LngVectorDynamicN)
  U32 capacity;
endclass

// ----- Fixed size vector

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

// ----- allocators and initializers

struct LngVector* LngVector_alloc         (U32);
struct LngVector* LngVectorView_alloc     (struct LngVector*,U32,U32,U32);
struct LngVector* LngVectorView_init      (struct LngVectorView*,I32);
struct LngVector* LngVectorSubview_init   (struct LngVectorView*,I32);
struct LngVector* LngVectorDynamic_alloc  (U32);
void              LngVectorDynamic_adjust (struct LngVectorDynamic*);
void              LngVectorDynamic_enlarge(struct LngVectorDynamic*,F64);

// ----- automatic constructors

#define atLngVector(...)         atVector       (Lng,I64,__VA_ARGS__)
#define atLngVectorRef(...)      atVectorRef    (Lng,I64,__VA_ARGS__)
#define atLngVectorView(...)     atVectorView   (Lng,I64,__VA_ARGS__)
#define atLngVectorSubview(...)  atVectorSubview(Lng,I64,__VA_ARGS__)

#endif // COS_LNGVECTOR_H

#ifndef COS_INTVECTOR_H
#define COS_INTVECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Int Vector, Dynamic Vector and Vector View
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
 | $Id: IntVector.h,v 1.2 2009/02/27 23:28:53 ldeniau Exp $
 |
*/

#include <cos/Vector.h>

/* NOTE-USER: IntVector class cluster constructors

   see cos/Vector.h
*/

defclass(IntVector, Vector)
  U32  size;
  I32  stride;
  I32 *value;
endclass

// ----- automatic constructors

#define aIntVector(...)        ( (OBJ)atIntVector       (__VA_ARGS__) )
#define aIntVectorRef(...)     ( (OBJ)atIntVectorRef    (__VA_ARGS__) )
#define aIntVectorView(...)    ( (OBJ)atIntVectorView   (__VA_ARGS__) )
#define aIntVectorSubview(...) ( (OBJ)atIntVectorSubview(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aIntVec(...)        aIntVector       (__VA_ARGS__)
#define aIntVecRef(...)     aIntVectorRef    (__VA_ARGS__)
#define aIntVecView(...)    aIntVectorView   (__VA_ARGS__)
#define aIntVecSubview(...) aIntVectorSubview(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Vector view

defclass(IntVectorView, IntVector)
  OBJ vector;
endclass

// ----- Dynamic vector

defclass(IntVectorDynamicN, IntVector)
  I32 *base;
endclass

// ---

defclass(IntVectorDynamic, IntVectorDynamicN)
  U32 capacity;
endclass

// ----- Fixed size vector

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

// ----- allocators and initializers

struct IntVector* IntVector_alloc         (U32);
struct IntVector* IntVectorView_alloc     (struct IntVector*,U32,U32,U32);
struct IntVector* IntVectorView_init      (struct IntVectorView*,I32);
struct IntVector* IntVectorSubview_init   (struct IntVectorView*,I32);
struct IntVector* IntVectorDynamic_alloc  (U32);
void              IntVectorDynamic_adjust (struct IntVectorDynamic*);
void              IntVectorDynamic_enlarge(struct IntVectorDynamic*,F64);

// ----- automatic constructors

#define atIntVector(...)         atVector       (Int,I32,__VA_ARGS__)
#define atIntVectorRef(...)      atVectorRef    (Int,I32,__VA_ARGS__)
#define atIntVectorView(...)     atVectorView   (Int,I32,__VA_ARGS__)
#define atIntVectorSubview(...)  atVectorSubview(Int,I32,__VA_ARGS__)

#endif // COS_INTVECTOR_H

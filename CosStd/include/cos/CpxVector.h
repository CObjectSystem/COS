#ifndef COS_CPXVECTOR_H
#define COS_CPXVECTOR_H

/**
 * C Object System
 * COS Vector, Dynamic Vector and Vector View
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/Vector.h>

/* NOTE-USER: CpxVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(CpxVector, FloatingVector)
  C64 *value;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aCpxVector(...)        ( (OBJ)atCpxVector       (__VA_ARGS__) )
#define aCpxVectorRef(...)     ( (OBJ)atCpxVectorRef    (__VA_ARGS__) )
#define aCpxVectorView(...)    ( (OBJ)atCpxVectorView   (__VA_ARGS__) )
#define aCpxVectorSubView(...) ( (OBJ)atCpxVectorSubView(__VA_ARGS__) )

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
  U32  capacity;
endclass

defclass(CpxVectorDyn, CpxVectorFix)
endclass

// ----- CpxVector view and subview

defclass(CpxVectorView, CpxVector)
  struct CpxVector *ref;
endclass

defclass(CpxVectorSubView, CpxVectorView)
endclass

// ----- allocators and initializers

struct Slice;
struct CpxVector* CpxVector_alloc(U32);
struct CpxVector* CpxVectorView_init(struct CpxVectorView*, struct CpxVector*,
                                     struct Slice*, BOOL);

// ----- automatic constructors

#define atCpxVector(...)                 atVector    (Cpx,C64,__VA_ARGS__)
#define atCpxVectorRef(...)              atVectorRef (Cpx,    __VA_ARGS__)
#define atCpxVectorView(vector,slice)    atVectorView(Cpx,vector,slice,COS_NO)
#define atCpxVectorSubView(vector,slice) atVectorView(Cpx,vector,slice,COS_YES)

#endif // COS_CPXVECTOR_H

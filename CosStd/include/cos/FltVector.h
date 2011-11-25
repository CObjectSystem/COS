#ifndef COS_FLTVECTOR_H
#define COS_FLTVECTOR_H

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

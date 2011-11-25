#ifndef COS_LNGVECTOR_H
#define COS_LNGVECTOR_H

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

/* NOTE-USER: LngVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(LngVector, IntegralVector)
  I64 *value;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aLngVector(...)        ( (OBJ)atLngVector       (__VA_ARGS__) )
#define aLngVectorRef(...)     ( (OBJ)atLngVectorRef    (__VA_ARGS__) )
#define aLngVectorView(...)    ( (OBJ)atLngVectorView   (__VA_ARGS__) )
#define aLngVectorSubView(...) ( (OBJ)atLngVectorSubView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aLVec(...)  aLngVector(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Block vector

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

// ----- Fixed vector, Dynamic vector and Lazy vector

defclass(LngVectorFix, LngVector)
  I64 *_value;
  U32  capacity;
endclass

defclass(LngVectorDyn, LngVectorFix)
endclass

// ----- LngVector view and subview

defclass(LngVectorView, LngVector)
  struct LngVector *ref;
endclass

defclass(LngVectorSubView, LngVectorView)
endclass

// ----- allocators and initializers

struct Slice;
struct LngVector* LngVector_alloc(U32);
struct LngVector* LngVectorView_init(struct LngVectorView*, struct LngVector*,
                                     struct Slice*, BOOL);

// ----- automatic constructors

#define atLngVector(...)                 atVector    (Lng,I64,__VA_ARGS__)
#define atLngVectorRef(...)              atVectorRef (Lng,    __VA_ARGS__)
#define atLngVectorView(vector,slice)    atVectorView(Lng,vector,slice,COS_NO)
#define atLngVectorSubView(vector,slice) atVectorView(Lng,vector,slice,COS_YES)

#endif // COS_LNGVECTOR_H

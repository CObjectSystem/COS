#ifndef COS_SHTVECTOR_H
#define COS_SHTVECTOR_H

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
#define atShtVectorRef(...)              atVectorRef (Sht,    __VA_ARGS__)
#define atShtVectorView(vector,slice)    atVectorView(Sht,vector,slice,COS_NO)
#define atShtVectorSubView(vector,slice) atVectorView(Sht,vector,slice,COS_YES)

#endif // COS_SHTVECTOR_H

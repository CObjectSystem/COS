#ifndef COS_INTVECTOR_H
#define COS_INTVECTOR_H

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

/* NOTE-USER: IntVector class cluster constructors

   see cos/Vector.h for description
*/

defclass(IntVector, IntegralVector)
  I32 *value;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aIntVector(...)        ( (OBJ)atIntVector       (__VA_ARGS__) )
#define aIntVectorRef(...)     ( (OBJ)atIntVectorRef    (__VA_ARGS__) )
#define aIntVectorView(...)    ( (OBJ)atIntVectorView   (__VA_ARGS__) )
#define aIntVectorSubView(...) ( (OBJ)atIntVectorSubView(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aIVec(...)  aIntVector(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Block vector

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

// ----- Fixed vector, Dynamic vector and Lazy vector

defclass(IntVectorFix, IntVector)
  I32 *_value;
  U32  capacity;
endclass

defclass(IntVectorDyn, IntVectorFix)
endclass

// ----- IntVector view and subview

defclass(IntVectorView, IntVector)
  struct IntVector *ref;
endclass

defclass(IntVectorSubView, IntVectorView)
endclass

// ----- initializers, allocators (for the class cluster)

struct Slice;
struct IntVector* IntVector_alloc(U32);
struct IntVector* IntVectorView_init(struct IntVectorView*, struct IntVector*,
                                     struct Slice*, BOOL);

// ----- automatic constructors

#define atIntVector(...)                 atVector    (Int,I32,__VA_ARGS__)
#define atIntVectorRef(...)              atVectorRef (Int,    __VA_ARGS__)
#define atIntVectorView(vector,slice)    atVectorView(Int,vector,slice,COS_NO)
#define atIntVectorSubView(vector,slice) atVectorView(Int,vector,slice,COS_YES)

#endif // COS_INTVECTOR_H

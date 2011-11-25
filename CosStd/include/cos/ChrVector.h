#ifndef COS_CHRVECTOR_H
#define COS_CHRVECTOR_H

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
#define atChrVectorRef(...)              atVectorRef (Chr,   __VA_ARGS__)
#define atChrVectorView(vector,slice)    atVectorView(Chr,vector,slice,COS_NO)
#define atChrVectorSubView(vector,slice) atVectorView(Chr,vector,slice,COS_YES)

#endif // COS_CHRVECTOR_H

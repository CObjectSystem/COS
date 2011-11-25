#ifndef COS_VECTOR_H
#define COS_VECTOR_H

/**
 * C Object System
 * COS Vector
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

#include <cos/Sequence.h>

/* NOTE-USER: Vector class cluster constructors

   aTVector       (val,...)               -> Block vector    (automatic)
   aTVectorRef    (buffer,size[,stride])  -> Vector          (automatic)
   aTVectorView   (vector,slice)          -> Vector view     (automatic)
   aTVectorSubView(vector,slice)          -> Vector view     (automatic)

   gnewWith (TVector,vector)              -> Block vector    (clone)
   gnewWith (TVector,slice)               -> Block vector    (sequence)
   gnewWith (TVector,range)               -> Block vector    (sequence)
   gnewWith2(TVector,size,obj)            -> Block vector    (element)
   gnewWith2(TVector,size,fun)            -> Block vector    (generator)
   gnewWith2(TVector,vector,slice)        -> Block vector    (subvector)
   gnewWith2(TVector,vector,range)        -> Block vector    (subvector)
   gnewWith2(TVector,vector,intvec)       -> Block vector    (sequence)
   
   gnew     (TVector)                     -> Dynamic vector
   gnewWith (TVector,capacity)            -> Dynamic vector  (pre-allocated)

   gnewWith2(View,vector,slice)           -> Vector view     (view)
   gnewWith2(View,vector,range)           -> Vector view     (view)

   gnewWith2(SubView,vector,slice)        -> Vector view     (substride view)
   gnewWith2(SubView,vector,range)        -> Vector view     (substride view)

   where:
   - T stands for Chr, Sht, Int, Lng, Flt, Cpx
   - All vectors are mutable and strided
   - All vectors hold value elements
   - Block vectors will be one of TVector0..9 if size is < 10, TVectorN otherwise
   - Dynamic vectors can shrink and grow (gappend, gpreprend)
   - Dynamic vectors can be converted to fixed vector (gadjust)
   - Vector views convert dynamic vectors into fixed vectors
   - Vector views copy/clone are block vectors, not views
   - Vector subviews are views which don't follow the underlying vectors strides
*/

defclass(Vector, ValueSequence)
endclass

defclass(IntegralVector, Vector)
endclass

defclass(FloatingVector, Vector)
endclass

/***********************************************************
 * Implementation (private)
 */

/* NOTE-INFO:
    P  type prefix  (e.g. Chr, Sht, Int, Lng, Flt, Cpx)
    E  element type (e.g. I8 , I16, I32, I64, F64, C64)
    T  type         (e.g. IntVector , LngVector)
    TN sized type   (e.g. IntVector0, IntVector1, ..)
*/

// ----- automatic constructors (helpers for specialization)

#define atVector(P,E,...) \
  atVectorN(COS_PP_CAT(P,Sequence_SizedName(Vector,10,N,__VA_ARGS__)), \
            COS_PP_CAT(P,Vector),E,__VA_ARGS__)

#define atVectorN(TN,T,E,...) ( (struct T*) \
  ( &(struct TN) {{ {{{{{ cos_object_auto(TN) }}}}}, \
    (E[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__), 1 }} ))

// --- VectorView

#define atVectorView(P,vector,slice,sub) COS_PP_CAT(P,VectorView_init) ( \
  atVectorView_Default(COS_PP_CAT(P,VectorView)), vector, slice, sub )

#define atVectorView_Default(T) \
  ( &(struct T) {{ {{{{{ cos_object_auto(T) }}}}}, 0, 0, 0 }, 0 } )

// --- VectorRef

#define atVectorRef(P,...) \
  COS_PP_CAT_NARG(atVectorRef_,__VA_ARGS__)(COS_PP_CAT(P,Vector),__VA_ARGS__)

#define atVectorRef_2(T,buffer,size) \
        atVectorRef_3(T,buffer,size,1) \

#define atVectorRef_3(T,buffer,size,stride) \
  ( &(struct T) { {{{{{ cos_object_auto(T) }}}}}, buffer, size, stride } )

#endif // COS_VECTOR_H

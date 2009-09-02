#ifndef COS_VECTOR_H
#define COS_VECTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Vector
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
 | $Id: Vector.h,v 1.14 2009/09/02 10:48:16 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Vector class cluster constructors

   aTVector    (val,...)            -> Block vector    (automatic)
   aTVectorRef (buffer,size)        -> Vector          (automatic)
   aTVectorView(vector,slice)       -> Vector view     (automatic)

   gnewWith (TVector,vector)        -> Block vector    (clone)
   gnewWith (TVector,slice)         -> Block vector    (sequence)
   gnewWith (TVector,range)         -> Block vector    (sequence)
   gnewWith2(TVector,size,obj)      -> Block vector    (element)
   gnewWith2(TVector,size,fun)      -> Block vector    (generator)
   gnewWith2(TVector,vector,slice)  -> Block vector    (subvector)
   gnewWith2(TVector,vector,range)  -> Block vector    (subvector)
   gnewWith2(TVector,vector,intvec) -> Block vector    (sequence)
   
   gnew     (TVector)               -> Dynamic vector
   gnewWith (TVector,capacity)      -> Dynamic vector  (pre-allocated)

   gnewWith (TVector,fun)           -> Lazy vector     (generator)
   gnewWith2(TVector,fun,vector)    -> Lazy vector     (generator)

   gnewWith2(View,vector,slice)     -> Vector view     (view)
   gnewWith2(View,vector,range)     -> Vector view     (view)

   where:
   - T stands for Int, Lng, Flt, Cpx
   - All vectors are mutable and strided
   - All vectors hold value elements
   - Block vectors will be one of TVector0..9 if size is < 10, TVectorN otherwise
   - Dynamic vectors can shrink and grow (gappend, gpreprend)
   - Dynamic vectors can be converted to fixed vector (gfix, gadjust)
   - Lazy vectors are dynamic vectors growing automatically using a generator
   - Vector views work only on non-dynamic vectors
   - Vector views clone are block vectors (copy), not views
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

#include <cos/Slice.h>

/* NOTE-INFO:
    P  type prefix  (e.g. Int, Lng, Flt, Cpx)
    E  element type (e.g. I32, I64, F64, C64)
    T  type         (e.g. IntVector , LngVector)
    TN sized type   (e.g. IntVector0, IntVector1, ..)
*/

// ----- automatic constructors (helpers for specialization)

#define atVector(P,E,...) \
  atVectorN(COS_PP_CAT(P,Sequence_SizedName(Vector,10,N,__VA_ARGS__)), \
            COS_PP_CAT(P,Vector),E,__VA_ARGS__)

#define atVectorN(TN,T,E,...) ( (struct T*) \
  ( &(struct TN) { {{{{{ cos_object_auto(TN) }}}}}, \
    (E[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__), 1 } ))

// --- VectorRef

#define atVectorRef(P,buffer,size) \
  atVectorRef_Default(COS_PP_CAT(P,Vector), buffer, size)

#define atVectorRef_Default(T,buffer,size) \
  ( &(struct T) { {{{{{ cos_object_auto(T) }}}}}, (buffer), (size), 1 } )

// --- VectorView

#define atVectorView(P,vector,slice) COS_PP_CAT(P,VectorView_init) ( \
  atVectorView_Default(COS_PP_CAT(P,VectorView)), vector, slice )

#define atVectorView_Default(T) \
  ( &(struct T) {{ {{{{{ cos_object_auto(T) }}}}}, 0, 0, 0 }, 0 } )

#endif // COS_VECTOR_H

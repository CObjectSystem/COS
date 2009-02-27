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
 | $Id: Vector.h,v 1.11 2009/02/27 23:28:53 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Vector class cluster constructors

   aXVector    (obj,...)                     -> Fixed size vector (automatic)
   aXVectorRef (buffer,size[,stride])        -> Vector view       (automatic)
   aXVectorView(vector,start,size[,stride])  -> Vector view       (automatic)

   gnew       (XVector)                      -> Dynamic vector
   gnewWith   (XVector,capacity)             -> Dynamic vector    (pre-allocated)

   gnewWith   (XVector,vector)               -> Fixed size vector (clone)

   gnewWith2  (XVector,size,obj)             -> Fixed size vector (element)
   gnewWith2  (XVector,size,fun)             -> Fixed size vector (generator)
   gnewWith2  (XVector,vector,range)         -> Fixed size vector (subvector)
   gnewWith2  (XVector,vector,slice)         -> Fixed size vector (subvector)
   gnewWith2  (XVector,vector,intvec)        -> Fixed size vector (sequence)
   
   gnewWith2  (View,vector,range)            -> Vector view       (view)
   gnewWith2  (View,vector,slice)            -> Vector view       (view)

   gnewWithXPtr(XVector,buffer,size,copy)    -> Fixed size vector (copy)
                                             -> Vector           (!copy)

   where:
   - X stands for Int, Lng, Flt, Cpx
   - All vectors are mutable
   - All vectors own value elements
   - Fixed size vectors will be one of XVector0 to XVector9 if size is < 10.
   - Dynamic vectors can shrink and grow (gput, gcat, ...)
   - Dynamic vectors can be converted to fixed size vector (gadjust)
   - Vector views work only on vectors which do not resize (undefined behavior)
   - Vector views clone are fixed size vectors (copy), not views
*/

defclass(Vector, ValueSequence)
endclass

/***********************************************************
 * Implementation (private)
 */

// ----- automatic constructors (helpers for specialization)

/* NOTE-INFO:
    P  type prefix  (e.g. Int, Lng, Flt, Cpx)
    E  element type (e.g. I32, I64, F64, C64)
    T  type         (e.g. IntVector , LngVector)
    TN sized type   (e.g. IntVector0, IntVector1, ..)
*/

#define atVector(P,E,...) \
  atVectorN(COS_PP_CAT(P,Sequence_FSName(Vector,10,__VA_ARGS__)), \
            COS_PP_CAT(P,Vector),E,__VA_ARGS__)

#define atVectorN(TN,T,E,...) \
  ( (struct T*)&(struct TN) {{ \
    {{{{ COS_CLS_NAME(TN).Behavior.id, COS_RC_AUTO }}}}, \
    COS_PP_NARG(__VA_ARGS__), 1, (E[]){ __VA_ARGS__ } }} )

// ---

#define atVectorRef(P,E,...) \
  COS_PP_CAT_NARG(atArrayRef,__VA_ARGS__)(COS_PP_CAT(P,Vector),__VA_ARGS__)

#define atVectorRef2(T,buffer,size) \
        atVectorRef3(T,buffer,size,1)

#define atVectorRef3(T,buffer,size,stride) \
  ( &(struct T) { \
    {{{{ COS_CLS_NAME(T).Behavior.id, COS_RC_AUTO }}}}, \
    (size), (stride), (buffer) } )

// ---

#define atVectorView(P,E,...) \
  COS_PP_CAT(P,VectorView_init)( \
    COS_PP_CAT_NARG(atVectorView,__VA_ARGS__) \
      (COS_PP_CAT(P,VectorView),__VA_ARGS__) )

#define atVectorSubview(P,E,...) \
  COS_PP_CAT(P,VectorSubview_init)( \
    COS_PP_CAT_NARG(atVectorView,__VA_ARGS__) \
      (COS_PP_CAT(P,VectorView),__VA_ARGS__) )

#define atVectorView3(T,vector,start,size) \
        atVectorView4(T,vector,start,size,1)

#define atVectorView4(T,vector,start,size,stride) \
  &(struct T) {{ \
    {{{{ COS_CLS_NAME(T).Behavior.id, COS_RC_AUTO }}}}, \
    (size), (stride), 0 }, (vector) }, (start)

#endif // COS_VECTOR_H

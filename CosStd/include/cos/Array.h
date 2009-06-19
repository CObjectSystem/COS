#ifndef COS_ARRAY_H
#define COS_ARRAY_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Array, Dynamic Array and Array View
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
 | $Id: Array.h,v 1.16 2009/06/19 23:57:27 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Array class cluster constructors

   aArray       (obj,...)                   -> Fixed size array (automatic)
   aArrayRef    (buffer,size[,stride])      -> Array view       (automatic)
   aArrayView   (array,start,size[,stride]) -> Array view       (automatic)
   aArraySubView(array,start,size[,stride]) -> Array view       (automatic)

   gnew      (Array)                        -> Dynamic array
   gnewWith  (Array,capacity)               -> Dynamic array    (pre-allocated)

   gnewWith  (Array,array)                  -> Fixed size array (clone)

   gnewWith2 (Array,size,obj)               -> Fixed size array (element)
   gnewWith2 (Array,size,fun)               -> Fixed size array (generator)
   gnewWith2 (Array,array,range)            -> Fixed size array (subarray)
   gnewWith2 (Array,array,slice)            -> Fixed size array (subarray)
   gnewWith2 (Array,array,intvec)           -> Fixed size array (sequence)
   
   gnewWith2 (View,array,range)             -> Array view       (view)
   gnewWith2 (View,array,slice)             -> Array view       (view)

   gnewWith2 (Subview,array,range)          -> Array view       (view)
   gnewWith2 (Subview,array,slice)          -> Array view       (view)

   gnewWithObjPtr(Array,buffer,size,copy)   -> Fixed size array (copy)
                                            -> Array           (!copy)

   where:
   - All arrays are mutable
   - All arrays own their elements (gretain) except automatic arrays
   - Fixed size arrays will be one of Array0 to Array9 if size is < 10.
   - Dynamic arrays can shrink and grow (gput, gcat, ...)
   - Dynamic arrays can be converted to fixed size array (gadjust)
   - Array views work only on arrays which do not resize (undefined behavior)
   - Array views clone are fixed size arrays (copy), not views
   - Subviews are views with 'raw' stride (not multiplied by array's stride)
*/

defclass(Array, Sequence)
  OBJ *object;
  U32  size;
  U32  stride;
endclass

// ----- automatic constructors

#define aArray(...)         ( (OBJ)atArray       (__VA_ARGS__) )
#define aArrayRef(...)      ( (OBJ)atArrayRef    (__VA_ARGS__) )
#define aArrayView(...)     ( (OBJ)atArrayView   (__VA_ARGS__) )
#define aArraySubview(...)  ( (OBJ)atArraySubview(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aArr(...)         aArray       (__VA_ARGS__)
#define aArrRef(...)      aArrayRef    (__VA_ARGS__)
#define aArrView(...)     aArrayView   (__VA_ARGS__)
#define aArrSubView(...)  aArraySubView(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Array view

defclass(ArrayView, Array)
  struct Array *array;
endclass

// ----- Dynamic array

defclass(ArrayDynamicN, Array)
  OBJ *base;
endclass

defclass(ArrayDynamic, ArrayDynamicN)
  U32 capacity;
endclass

// ----- Fixed size array

defclass(Array0, Array) OBJ base[]; endclass
defclass(Array1, Array) OBJ base[]; endclass
defclass(Array2, Array) OBJ base[]; endclass
defclass(Array3, Array) OBJ base[]; endclass
defclass(Array4, Array) OBJ base[]; endclass
defclass(Array5, Array) OBJ base[]; endclass
defclass(Array6, Array) OBJ base[]; endclass
defclass(Array7, Array) OBJ base[]; endclass
defclass(Array8, Array) OBJ base[]; endclass
defclass(Array9, Array) OBJ base[]; endclass
defclass(ArrayN, Array) OBJ base[]; endclass

// ----- allocators and initializers (class cluster)

struct Array* Array_alloc         (U32);
struct Array* ArrayView_alloc     (struct Array*,U32,U32,U32);
struct Array* ArrayView_init      (struct ArrayView*,I32);
struct Array* ArraySubview_init   (struct ArrayView*,I32);
struct Array* ArrayDynamic_alloc  (U32);
void          ArrayDynamic_adjust (struct ArrayDynamic*);
void          ArrayDynamic_enlarge(struct ArrayDynamic*,F64);

// ----- automatic constructors

#define atArray(...) \
  atArrayN(Sequence_FSName(Array,10,__VA_ARGS__),__VA_ARGS__)

#define atArrayN(TN,...) \
  ( (struct Array*)&(struct TN) {{ \
    {{{ COS_CLS_NAME(TN).Behavior.id, COS_RC_AUTO }}}, \
    (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__), 1 }} )
          
// ---

#define atArrayRef(...) \
  COS_PP_CAT_NARG(atArrayRef,__VA_ARGS__)(__VA_ARGS__)

#define atArrayRef2(buffer,size) \
        atArrayRef3(buffer,size,1)

#define atArrayRef3(buffer,size,stride) \
        ( &(struct Array) { \
          {{{ COS_CLS_NAME(Array).Behavior.id, COS_RC_AUTO }}}, \
          (buffer), (size), (stride) } )

// ---

#define atArrayView(...) \
  ArrayView_init( \
    COS_PP_CAT_NARG(atArrayView,__VA_ARGS__)(__VA_ARGS__) )

#define atArraySubview(...) \
  ArraySubview_init( \
    COS_PP_CAT_NARG(atArrayView,__VA_ARGS__)(__VA_ARGS__) )

#define atArrayView3(array,start,size) \
        atArrayView4(array,start,size,1)

#define atArrayView4(array,start,size,stride) \
  &(struct ArrayView) {{ \
    {{{ COS_CLS_NAME(ArrayView).Behavior.id, COS_RC_AUTO }}}, \
    0, (size), (stride) }, (array) }, (start)

#endif // COS_ARRAY_H

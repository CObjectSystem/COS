#ifndef COS_ARRAY_H
#define COS_ARRAY_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Array, Dynamic Array and Sub Array
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
 | $Id: Array.h,v 1.12 2009/02/24 14:44:34 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Array class cluster constructors

   aArray    (obj,...)                    -> Fixed size array (automatic)
   aArrayRef (buffer,size)                -> Array            (automatic)
   aArrayView(array,start,size)           -> Array view       (automatic)

   gnew      (Array)                      -> Dynamic array
   gnewWith  (Array,capacity)             -> Dynamic array    (pre-allocated)

   gnewWith  (Array,array)                -> Fixed size array (clone)

   gnewWith2 (Array,size,obj)             -> Fixed size array (element)
   gnewWith2 (Array,size,fun)             -> Fixed size array (generator)
   gnewWith2 (Array,array,range)          -> Fixed size array (subarray)
   gnewWith2 (Array,array,slice)          -> Fixed size array (subarray)
   gnewWith2 (Array,array,intvec)         -> Fixed size array (sequence)
   
   gnewWith2 (View,array,range)           -> Array view       (view)
   gnewWith2 (View,array,slice)           -> Array view       (view)

   gnewWithObjPtr(Array,buffer,size,copy) -> Fixed size array (copy)
                                          -> Dynamic array   (!copy)
                                          -> Array   (!free & !copy)

   where:
   - All arrays are mutable
   - All arrays can shrink from either sides
   - All arrays own their elements (gretain) except automatic arrays
   - Fixed size arrays will be one of Array0 to Array9 if size is < 10.
   - Dynamic arrays can grow (gput, gcat, ...)
   - Dynamic arrays can be converted to fixed size array (gadjust)
   - Array views require non-dynamic array and contiguous range and slice
   - Array views clone are fixed size arrays (copy), not views
*/

defclass(Array, Sequence)
  OBJ *object;
  U32  size;
endclass

// ----- automatic constructors

#define aArray(...)                  ( (OBJ)atArray    (__VA_ARGS__)      )
#define aArrayRef(buffer,size)       ( (OBJ)atArrayRef (buffer,size)      )
#define aArrayView(array,start,size) ( (OBJ)atArrayView(array,start,size) )

/***********************************************************
 * Implementation (private)
 */

// ----- Array view

defclass(ArrayView, Array)
  OBJ array;
endclass

// ----- Dynamic array

defclass(DynamicArrayN, Array)
  OBJ *base;
endclass

defclass(DynamicArray, DynamicArrayN)
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

// ----- allocators and initializers

struct Array* Array_alloc         (U32);
struct Array* Array_init          (struct Array*);
struct Array* ArrayView_alloc     (struct Array*,U32,U32);
struct Array* ArrayView_init      (struct ArrayView*,I32);
struct Array* DynamicArray_alloc  (U32);
void          DynamicArray_adjust (struct DynamicArray*);
void          DynamicArray_enlarge(struct DynamicArray*,F64);

// ----- automatic constructors

#define atArray(...) \
        atArrayN(COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),10)) \
                 (ArrayN,COS_PP_CAT_NARG(Array,__VA_ARGS__)),__VA_ARGS__)
#define atArrayN(T,...) \
        ( (struct Array*)&(struct T) {{ \
          {{{{ COS_CLS_NAME(T).Behavior.id, COS_RC_AUTO }}}}, \
          (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__) }} )

#define atArrayRef(buffer,size) \
        ( Array_init(&(struct Array) { \
          {{{{ COS_CLS_NAME(Array).Behavior.id, COS_RC_AUTO }}}}, \
          (buffer), (size) }) )

#define atArrayView(array,start,size) \
        ( ArrayView_init(&(struct ArrayView) {{ \
          {{{{ COS_CLS_NAME(ArrayView).Behavior.id, COS_RC_AUTO }}}}, \
          0, (size) }, (array) }, (start)) )

#endif // COS_ARRAY_H

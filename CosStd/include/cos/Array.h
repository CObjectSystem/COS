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
 | $Id: Array.h,v 1.18 2009/07/24 20:49:58 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Array class cluster constructors

   aArray    (obj,...)           -> Fixed size array (automatic)
   aArrayRef (buffer,size)       -> Array            (automatic)
   aArrayView(array ,slice) 	 -> Array view       (automatic)

   gnew     (Array)              -> Dynamic array
   gnewWith (Array,capacity)     -> Dynamic array    (pre-allocated)
   gnewWith (Array,array)        -> Fixed size array (clone, whatever array is!)
   gnewWith2(Array,size,obj)     -> Fixed size array (element)
   gnewWith2(Array,size,fun)     -> Fixed size array (generator)
   gnewWith2(Array,array,slice)  -> Fixed size array (subarray)
   gnewWith2(Array,array,range)  -> Fixed size array (subarray)
   gnewWith2(Array,array,intvec) -> Fixed size array (sequence)

   gnewWith2(View,array,slice)   -> Array view       (view)
   gnewWith2(View,array,range)   -> Array view       (view)

   where:
   - All arrays are mutable
   - All arrays own their elements (gretain) except automatic arrays
   - Fixed size arrays will be one of Array0 to Array9 if size is < 10.
   - Dynamic arrays can shrink and grow (gappend, gpreprend)
   - Dynamic arrays can be converted to fixed size array (gadjust)
   - Array views work only on non-dynamic arrays
   - Array views clone are fixed size arrays (copy), not views
*/

defclass(Array, Sequence)
  OBJ *object;
  U32 size;
  I32 stride;
endclass

// ----- automatic constructors

#define aArray(...)     ( (OBJ)atArray       (__VA_ARGS__) )
#define aArrayRef(...)  ( (OBJ)atArrayRef    (__VA_ARGS__) )
#define aArrayView(...) ( (OBJ)atArrayView   (__VA_ARGS__) )

/***********************************************************
 * Implementation (private)
 */

#include <cos/Slice.h>

// ----- Array view

defclass(ArrayView, Array)
  struct Array *array;
endclass

// ----- Dynamic array

defclass(ArrayDynamicN, Array)
  OBJ *_object;
endclass

defclass(ArrayDynamic, ArrayDynamicN)
  U32 capacity;
endclass

// ----- Fixed size array

defclass(Array0, Array) OBJ _object[]; endclass
defclass(Array1, Array) OBJ _object[]; endclass
defclass(Array2, Array) OBJ _object[]; endclass
defclass(Array3, Array) OBJ _object[]; endclass
defclass(Array4, Array) OBJ _object[]; endclass
defclass(Array5, Array) OBJ _object[]; endclass
defclass(Array6, Array) OBJ _object[]; endclass
defclass(Array7, Array) OBJ _object[]; endclass
defclass(Array8, Array) OBJ _object[]; endclass
defclass(Array9, Array) OBJ _object[]; endclass
defclass(ArrayN, Array) OBJ _object[]; endclass

// ----- initializers, allocators and utilities (class cluster)

struct Array* ArrayRef_init (struct Array*,OBJ*,U32);
struct Array* ArrayView_init(struct ArrayView*,struct Array*,struct Slice*);

struct Array* Array_alloc       (U32);
struct Array* ArrayDynamic_alloc(U32);
struct Array* ArrayView_alloc   (struct Array*,struct Slice*);

void ArrayDynamic_adjust      (struct ArrayDynamic*);
void ArrayDynamic_enlarge     (struct ArrayDynamic*,F64);
void ArrayDynamic_enlargeFront(struct ArrayDynamic*,F64);

// ----- automatic constructors

#define atArray(...) \
  atArrayN(Sequence_SizedName(Array,10,N,__VA_ARGS__),__VA_ARGS__)

#define atArrayN(TN,...) \
  ( (struct Array*)&(struct TN) {{ {{ cos_object_auto(TN) }}, \
    (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__), 1 }} )
          
// --- ArrayRef

#define atArrayRef(buffer,size) \
  (&(struct Array) {{ {{ cos_object_auto(Array) }}, (buffer), (size), 1 } })

// --- ArrayView

#define atArrayView(array,slice) \
  ArrayView_init(atArrayView_Default(),array,slice)

#define atArrayView_Default() \
  (&(struct ArrayView) {{ {{ cos_object_auto(ArrayView) }}, 0, 0, 0 }, 0 })

#endif // COS_ARRAY_H

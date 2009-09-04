#ifndef COS_ARRAY_H
#define COS_ARRAY_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Array, Dynamic Array, Lazy Array and Array View
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
 | $Id: Array.h,v 1.27 2009/09/04 12:09:17 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Array class cluster constructors

   aArray    (obj,...)           -> Block array    (automatic)
   aArrayRef (buffer,size)       -> Array          (automatic)
   aArrayView(array ,slice)      -> Array view     (automatic)

   gnewWith (Array,array)        -> Block array    (clone)
   gnewWith (Array,slice)        -> Block array    (Ints)
   gnewWith (Array,range)        -> Block array    (Ints)
   gnewWith2(Array,size,obj)     -> Block array    (element)
   gnewWith2(Array,size,fun)     -> Block array    (generator)
   gnewWith2(Array,array,slice)  -> Block array    (subarray)
   gnewWith2(Array,array,range)  -> Block array    (subarray)
   gnewWith2(Array,array,intvec) -> Block array    (sequence)

   gnew     (Array)              -> Dynamic array
   gnewWith (Array,capacity)     -> Dynamic array  (pre-allocated)

   gnewWith (Array,fun)          -> Lazy array     (generator)
   gnewWith2(Array,fun,array)    -> Lazy array     (generator)

   gnewWith2(View,array,slice)   -> Array view     (view)
   gnewWith2(View,array,range)   -> Array view     (view)

   where:
   - All arrays are mutable and strided
   - All arrays own their elements (gretain) except automatic arrays
   - Block arrays will be one of Array0..9 if size is < 10, ArrayN otherwise
   - Dynamic arrays can shrink and grow (gappend, gpreprend)
   - Dynamic arrays can be converted to fixed array (gfix, gadjust)
   - Lazy arrays are dynamic arrays growing automatically using a generator
   - Array views work only on non-dynamic arrays
   - Array views clone are block arrays (copy), not views
*/

defclass(Array, Sequence)
  OBJ *object;
  U32  size;
  I32  stride;
endclass

// ----- automatic constructors

#define aArray(...)        ( (OBJ)atArray       (__VA_ARGS__) )
#define aArrayRef(...)     ( (OBJ)atArrayRef    (__VA_ARGS__) )
#define aArrayView(...)    ( (OBJ)atArrayView   (__VA_ARGS__) )
#define aArraySubView(...) ( (OBJ)atArraySubView(__VA_ARGS__) )

/***********************************************************
 * Implementation (private)
 */

// ----- Block array

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

// ----- Fixed array, Dynamic array and Lazy array

defclass(ArrayFix, Array)
  OBJ *_object;
  U32  capacity;
endclass

defclass(ArrayDyn, ArrayFix)
endclass

defclass(ArrayLzy, ArrayDyn)
  I32 arity;
  OBJ generator;
endclass

// ----- Array view and subview

defclass(ArrayView, Array)
  struct Array *ref;
endclass

defclass(ArraySubView, ArrayView)
endclass

// ----- initializers, allocators (for the class cluster)

struct Slice;
struct Array* Array_alloc(U32);
struct Array* ArrayView_init(struct ArrayView*, struct Array*, struct Slice*, BOOL);

// ----- automatic constructors

#define atArray(...) \
  atArrayN(Sequence_SizedName(Array,10,N,__VA_ARGS__),__VA_ARGS__)

#define atArrayN(TN,...) \
  ( (struct Array*)&(struct TN) {{ {{ cos_object_auto(TN) }}, \
    (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__), 1 }} )
          
// --- ArrayRef

#define atArrayRef(buffer,size) \
  ( &(struct Array) { {{ cos_object_auto(Array) }}, (buffer), (size), 1 } )

// --- ArrayView

#define atArrayView(array,slice) ArrayView_init( \
  (&(struct ArrayView) {{ {{ cos_object_auto(ArrayView) }}, 0, 0, 0 }, 0 }), \
  array,slice,0)

#define atArraySubView(array,slice) ArrayView_init( \
  (&(struct ArrayView) {{ {{ cos_object_auto(ArrayView) }}, 0, 0, 0 }, 0 }), \
  array,slice,1)

#endif // COS_ARRAY_H

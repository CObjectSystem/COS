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
 | $Id: Array.h,v 1.36 2010/06/04 23:27:21 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: Array constructors (class cluster)

   aArray       (obj,...)               -> Block array    (automatic)
   aArray0      ()                      -> Block array    (automatic)
   aArrayRef    (buffer,size[,stride])  -> Array          (automatic)
   aArrayView   (array,slice)           -> Array view     (automatic)
   aArrayView   (array,range)           -> Array view     (automatic)
   aArraySubView(array,slice)           -> Array view     (automatic)
   aArraySubView(array,range)           -> Array view     (automatic)

   gnewWith (Array,array)               -> Block array    (copy)
   gnewWith (Array,slice)               -> Block array    (Int sequence)
   gnewWith (Array,range)               -> Block array    (Int sequence)
   gnewWith (Array,xrange)              -> Block array    (Float sequence)
   
   gnewWith2(Array,size,obj)            -> Block array    (element)
   gnewWith2(Array,size,fun)            -> Block array    (generator)
   gnewWith2(Array,array,slice)         -> Block array    (subarray)
   gnewWith2(Array,array,range)         -> Block array    (subarray)
   gnewWith2(Array,array,intvec)        -> Block array    (random subarray)

   gnew     (Array)                     -> Dynamic array
   gnewWith (Array,size)                -> Dynamic array  (with capacity)

   gnewWith2(View,array,slice)          -> Array view     (view)
   gnewWith2(View,array,range)          -> Array view     (view)

   gnewWith2(SubView,array,slice)       -> Array view     (substride view)
   gnewWith2(SubView,array,range)       -> Array view     (substride view)

   where:
   - All arrays are mutable and strided
   - All arrays own their elements (gretain) except automatic arrays
   - Block arrays will be one of Array0..9 if size is < 10, ArrayN otherwise
   - Dynamic arrays can shrink and grow (gappend, gpreprend)
   - Dynamic arrays can be converted to fixed array (gadjust)
   - Array (non-auto) views convert dynamic arrays into fixed arrays
   - Array views copy/clone are block arrays, not views
   - Array subviews are views which don't follow the underlying arrays strides
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
#define aArray0()          ( (OBJ)atArray0      (           ) )

/***********************************************************
 * Implementation (private)
 */

// ----- Block array

defclass(ArrayBlk, Array)
endclass

defclass(Array0, ArrayBlk) OBJ _object[]; endclass
defclass(Array1, ArrayBlk) OBJ _object[]; endclass
defclass(Array2, ArrayBlk) OBJ _object[]; endclass
defclass(Array3, ArrayBlk) OBJ _object[]; endclass
defclass(Array4, ArrayBlk) OBJ _object[]; endclass
defclass(Array5, ArrayBlk) OBJ _object[]; endclass
defclass(Array6, ArrayBlk) OBJ _object[]; endclass
defclass(Array7, ArrayBlk) OBJ _object[]; endclass
defclass(Array8, ArrayBlk) OBJ _object[]; endclass
defclass(Array9, ArrayBlk) OBJ _object[]; endclass
defclass(ArrayN, ArrayBlk) OBJ _object[]; endclass

// ----- Fixed array, Dynamic array and Lazy array

defclass(ArrayFix, Array)
  OBJ *_object;
endclass

defclass(ArrayDyn, ArrayFix)
  U32 capacity;
endclass

// ----- Array view and subview

defclass(ArrayView, Array)
  OBJ ref;
endclass

defclass(ArraySubView, ArrayView)
endclass

// ----- allocators (for the class cluster)

struct Array* Array_alloc(U32);

// ----- automatic constructors

#define atArray(...) \
  atArrayN(Sequence_SizedName(Array,10,N,__VA_ARGS__),__VA_ARGS__)

#define atArrayN(TN,...) \
  ( (struct Array*)&(struct TN) {{{ {{ cos_object_auto(TN) }}, \
    (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__), 1 }}} )

#define atArray0() \
  ( (struct Array*)&(struct Array0) {{{ {{ cos_object_auto(Array0) }}, \
    0, 0, 1 }}} )

// --- ArrayView

#define atArrayView(array,slice) ((struct ArrayView*) ginitWith2( \
  (OBJ)&(struct ArrayView) {{ {{ cos_object_auto(ArrayView) }}, \
    0, 0, 0 }, 0 }, array, slice))

#define atArraySubView(array,slice) ((struct ArraySubView*) ginitWith2( \
  (OBJ)&(struct ArraySubView) {{{ {{ cos_object_auto(ArraySubView) }}, \
    0, 0, 0 }, 0 }}, array, slice))

// --- ArrayRef (low-level)

#define atArrayRef(...) \
  COS_PP_CAT_NARG(atArrayRef_,__VA_ARGS__)(__VA_ARGS__)

#define atArrayRef_2(buffer,size) \
        atArrayRef_3(buffer,size,1)

#define atArrayRef_3(buffer,size,stride) \
  ( &(struct Array) { {{ cos_object_auto(Array) }}, \
    buffer, size, stride } )

#endif // COS_ARRAY_H

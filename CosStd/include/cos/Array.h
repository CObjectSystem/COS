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
 | $Id: Array.h,v 1.8 2008/12/02 17:32:21 ldeniau Exp $
 |
*/

#include <cos/Collection.h>

/* Array subclasses:
<- Collection
   <- Array <- ArrayN (0..9)
            <- DynArrayN <- DynArray
            <- SubArray
*/

defclass(Array, Collection)
  OBJ *object;
  U32  size;
endclass

// ----- Dynamic array

defclass(DynArrayN, Array)
endclass

defclass(DynArray, DynArrayN)
  U32 capacity;
endclass

// ----- Sub array

defclass(SubArray, Array)
  OBJ array;
endclass

// ----- Fixed size arrays

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

// ----- automatic constructors

#define aArray(...)                 ( (OBJ)atArray   (__VA_ARGS__     ) )
#define aArrayRef(size,array)       ( (OBJ)atArrayRef(size,array      ) )
#define aSubArray(array,start,size) ( (OBJ)atSubArray(array,start,size) )

#define atArray(...) \
        atArrayN(COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),10)) \
                 (N,COS_PP_NARG(__VA_ARGS__)),__VA_ARGS__)
#define atArrayN(N,...) \
        ( (struct Array*)&(struct COS_PP_CAT(Array,N)) {{ \
          {{{ COS_CLS_NAME(COS_PP_CAT(Array,N)).Behavior.id, COS_RC_AUTO }}}, \
          (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__) }} )

#define atArrayRef(size,array) \
        ( &(struct Array) { \
          {{{ COS_CLS_NAME(Array).Behavior.id, COS_RC_AUTO }}}, \
          (array), (size) } )

#define atSubArray(array,start,size) \
        ( SubArray_init(&(struct SubArray) {{ \
          {{{{ COS_CLS_NAME(SubArray).Behavior.id, COS_RC_AUTO }}}}, \
          (size), 0 }, (array) }, (start)) )

// ----- automatic sub-arrays init/checker

#ifndef COS_VALUE_H
#include <cos/Value.h>
#endif

static inline struct Array*
SubArray_init(struct SubArray *subarr, I32 substart)
{
  test_assert( cos_any_superClass(subarr->array) == classref(Array),
               "subarray accepts only fixed size array" );

  struct Array *sarr = &subarr->Array;
  struct Array * arr = STATIC_CAST(struct Array*, subarr->array);

  U32 start = index_abs(substart, arr->size);
  test_assert( start + sarr->size <= arr->size, "subarray out of range" );

  sarr->object = arr->object + start;

  return sarr;
}

#endif // COS_ARRAY_H

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
 | $Id: Array.h,v 1.3 2008/10/17 18:12:21 ldeniau Exp $
 |
*/

#include <cos/Collection.h>
#include <cos/Index.h>

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

#define aArr(...)                 ( (OBJ)atArr   (__VA_ARGS__     ) )
#define aArrRef(size,array)       ( (OBJ)atArrRef(size,array      ) )
#define aSubArr(array,start,size) ( (OBJ)atSubArr(array,start,size) )

#define atArr(...) \
        atArrN(COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),10)) \
               (N,COS_PP_NARG(__VA_ARGS__)),__VA_ARGS__)
#define atArrN(N,...) \
        ( (struct Array*)&(struct COS_PP_CAT(Array,N)) {{ \
          {{{{ COS_CLS_NAME(COS_PP_CAT(Array,N)).Behavior.id, COS_RC_AUTO }}}}, \
          (OBJ[]){ __VA_ARGS__ }, COS_PP_NARG(__VA_ARGS__) }} )

#define atArrRef(size,array) \
        ( &(struct Array) { \
          {{{ COS_CLS_NAME(Array).Behavior.id, COS_RC_AUTO }}}, \
          (array), (size) } )

#define atSubArr(array,start,size) \
        ( SubArray_init(&(struct SubArray) {{ \
          {{{{ COS_CLS_NAME(SubArray).Behavior.id, COS_RC_AUTO }}}}, \
          (size), 0 }, (array) }, (start)) )

// ----- automatic sub-vectors init/checker

static inline struct Array*
SubArray_init(struct SubArray *subarr, I32 substart)
{
  useclass(Array);

  OBJ arr_spr = (OBJ)cos_class_get(cos_any_id(subarr->array))->spr;
  struct Array *sarr = &subarr->Array;
  struct Array * arr = STATIC_CAST(struct Array*, subarr->array);
  U32 start;

  // ensure that we have an Array excluding DynArray
  test_assert( arr_spr == Array );
  start = index_abs(substart, arr->size);
  test_assert( start + sarr->size <= arr->size );
  sarr->object = arr->object + start;

  return sarr;
}

#endif // COS_ARRAY_H

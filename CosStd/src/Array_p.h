#ifndef COS_ARRAY_P_H
#define COS_ARRAY_P_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Array (private shared implementation)
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
 | $Id: Array_p.h,v 1.4 2009/01/22 16:45:08 ldeniau Exp $
 |
*/

static inline BOOL
array_isa(OBJ _1)
{
  return cos_any_superClass(_1) == classref(   Array) ||
         cos_any_isa(       _1  ,  classref(DynArray));
}

static inline struct Array*
array_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[N] = {
    classref(Array0,Array1,Array2,Array3,Array4,
             Array5,Array6,Array7,Array8,Array9) }; 

  useclass(ArrayN);

  OBJ _cls = size >= N ? ArrayN : (OBJ)cls[size];
  OBJ _arr = gallocWithSize(_cls, size * sizeof(OBJ));
  struct ArrayN *narr = STATIC_CAST(struct ArrayN*, _arr);
  struct Array  * arr = &narr->Array;

  arr->size   = size;
  arr->object = narr->_object;

  return arr;
}

static inline struct Array*
subarray_alloc(struct Array *ref, U32 start, U32 size)
{
  useclass(SubArray);

  OBJ _arr = gallocWithSize(SubArray, 0);
  struct SubArray *sarr = STATIC_CAST(struct SubArray*, _arr);
  struct Array    * arr = &sarr->Array;

  arr->size   = size;
  arr->object = ref->object + start;
  sarr->array = (OBJ)ref;

  return arr;
}

static inline struct Array*
dynarray_alloc(U32 size)
{
  useclass(DynArray, ExBadAlloc);

  OBJ _arr = gallocWithSize(DynArray, 0);
  struct DynArray *darr = STATIC_CAST(struct DynArray*, _arr);
  struct Array    * arr = &darr->DynArrayN.Array;

  arr->object = malloc(size * sizeof *arr->object);
  
  if (!arr->object) {
    gdealloc(_arr);
    THROW(ExBadAlloc);
  }

  darr->capacity = size;

  return arr;
}

static void
dynarray_resizeBy(struct DynArray *darr, float factor)
{
  useclass(ExBadAlloc);

  struct Array *arr = &darr->DynArrayN.Array;
  U32  size = darr->capacity * factor;
  OBJ *object = realloc(arr->object, size * sizeof(OBJ));

  if (!object) THROW(ExBadAlloc);
  
  arr->object = object;
  darr->capacity = size;
}

#endif // COS_ARRAY_P_H


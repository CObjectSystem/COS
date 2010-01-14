/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - block vectors
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
 | $Id: Vector.c,v 1.14 2010/01/14 13:17:15 ldeniau Exp $
 |
*/

#define VECTOR_TMPL

#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/XRange.h>
#include <cos/View.h>

#include <cos/gen/accessor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/init.h>
#include <cos/gen/new.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/carray.h>

#include <stdlib.h>
#include <string.h>

// -----

makclass(COS_PP_CAT(T,0), T);
makclass(COS_PP_CAT(T,1), T);
makclass(COS_PP_CAT(T,2), T);
makclass(COS_PP_CAT(T,3), T);
makclass(COS_PP_CAT(T,4), T);
makclass(COS_PP_CAT(T,5), T);
makclass(COS_PP_CAT(T,6), T);
makclass(COS_PP_CAT(T,7), T);
makclass(COS_PP_CAT(T,8), T);
makclass(COS_PP_CAT(T,9), T);
makclass(COS_PP_CAT(T,N), T);

// -----

useclass(T);
useclass(ExBadAlloc);
useclass(Lesser,Equal,Greater);

// --- getters

defmethod(struct Slice, gslice, T)
  retmethod( *atSlice(0,self->size,self->stride) );
endmethod

defmethod(U32, gsize, T)
  retmethod(self->size);
endmethod

defmethod(VAL*, TOVALPTR, T)
  retmethod(self->value);
endmethod

defmethod(OBJ, gisEmpty, T)
  retmethod(self->size ? False : True);
endmethod

defmethod(OBJ, gclass, T)
  retmethod(T);     // class cluster: hide implementation details
endmethod

// --- alloc

struct T*
T_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[] = {
    classref(COS_PP_CAT(T,0),COS_PP_CAT(T,1),COS_PP_CAT(T,2),COS_PP_CAT(T,3),
             COS_PP_CAT(T,4),COS_PP_CAT(T,5),COS_PP_CAT(T,6),COS_PP_CAT(T,7),
             COS_PP_CAT(T,8),COS_PP_CAT(T,9),TN)
  };

  OBJ _cls = (OBJ)cls[size > N ? N : size];
  OBJ _vec = gallocWithSize(_cls, size * sizeof(VAL));

  struct TN *vecn = STATIC_CAST(struct TN*, _vec);
  struct T  *vec  = &vecn->T;

  vec->value = vecn->_value;
  vec->size   = 0;
  vec->stride = 1;

  return vec;
}

// ----- allocator

defmethod(OBJ, galloc, TP) // lazy alloc
  retmethod(_1);
endmethod

// ----- constructors

defmethod(OBJ, gclone, T) // clone
  struct T* vec = T_alloc(self->size);

  copy(vec->value,&vec->size,self->value,self->stride,self->size);

  retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, T);
defmethod(OBJ,  ginitWith         , TP, T) // clone
  struct T* vec = T_alloc(self2->size);

  copy(vec->value,&vec->size,self2->value,self2->stride,self2->size);

  retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Slice);
defmethod(OBJ,  ginitWith         , TP, Slice) // Int sequence
  U32 size = Slice_size(self2);
  struct T* vec = T_alloc(size);

  for (U32 i = 0; i < size; i++) {
    vec->value[i] = Slice_eval(self2,i);
    vec->size++;
  }

  retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Range);
defmethod(OBJ,  ginitWith         , TP, Range) // Int sequence
  U32 size = Range_size(self2);
  struct T* vec = T_alloc(size);

  for (U32 i = 0; i < size; i++) {
    vec->value[i] = Range_eval(self2,i);
    vec->size++;
  }

  retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, XRange);
defmethod(OBJ,  ginitWith         , TP, XRange) // Float sequence
  U32 size = XRange_size(self2);
  struct T* vec = T_alloc(size);

  for (U32 i = 0; i < size; i++) {
    vec->value[i] = XRange_eval(self2,i);
    vec->size++;
  }

#ifdef FLTVECTOR_ONLY
  // avoid overshoot
  if (size && (
      (XRange_stride(self2) > 0 && vec->value[size-1] > XRange_end(self2)) ||
      (XRange_stride(self2) < 0 && vec->value[size-1] < XRange_end(self2))))
     vec->value[size-1] = XRange_end(self2);
#endif
  
  retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Int, Object);
defmethod(OBJ,  ginitWith2          , TP, Int, Object) // element
  PRE
    test_assert(self2->value >= 0, "negative " TS " size");

  BODY
    VAL val = TOVAL(_3);
    U32 size = self2->value;
    
    struct T* vec = T_alloc(size);

    U32 *dst_n = &vec->size;
    VAL *dst   = vec->value;
    VAL *end   = dst + size;

    while (dst != end)
      *dst++ = val, ++*dst_n;

    retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Int, Functor);
defmethod(OBJ,  ginitWith2          , TP, Int, Functor) // generator
  PRE
    test_assert(self2->value >= 0, "negative " TS " size");

  BODY
    U32 size = self2->value;
    struct T* vec = T_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    U32 *dst_n = &vec->size;
    VAL *dst   = vec->value;
    VAL *end   = dst + size;

    while (dst != end)
      *dst++ = TOVAL(geval(_3)), ++*dst_n;

    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, T, Slice);
defmethod(OBJ,  ginitWith2          , TP, T, Slice) // sub vector
  PRE
    test_assert( Slice_first(self3) < self2->size &&
                 Slice_last (self3) < self2->size, "slice out of range" );
  POST
  BODY
    I32 start  = Slice_start (self3)*self2->stride;
    I32 stride = Slice_stride(self3)*self2->stride;
    U32 size   = self3->size;
    struct T* vec = T_alloc(size);

    copy(vec->value,&vec->size,self2->value+start,stride,size);

    retmethod( (OBJ)vec );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, T, Range);
defmethod(OBJ,  ginitWith2          , TP, T, Range) // sub vector
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod( ginitWith2(_1,_2,(OBJ)&slice) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, T, IntVector);
defmethod(OBJ,  ginitWith2          , TP, T, IntVector) // random sequence
  U32 size = self3->size;
  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  U32  val_n = self2->size;
  I32  val_s = self2->stride;
  VAL *val   = self2->value;
  I32  idx_s = self3->stride;
  I32 *idx   = self3->value;
  U32 *dst_n = &vec->size;
  VAL *dst   = vec->value;
  VAL *end   = dst + size;

  while (dst != end) {
    U32 i = Range_index(*idx, val_n);
    test_assert( i < val_n, "index out of range" );
    *dst++ = val[i*val_s], ++*dst_n;
    idx += idx_s;
  }

  UNPRT(_vec);
  retmethod(_vec);
endmethod

// ----- constructors from C array

#ifdef CHRVECTOR_ONLY
defalias (OBJ, (ginitWithChrPtr)gnewWithChrPtr, TP, (I8*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithChrPtr               , TP, (I8*)ref, (U32)n, (I32)s)
  retmethod( gclone(aChrVectorRef(ref,n,s)) );
endmethod
#endif

#ifdef SHTVECTOR_ONLY
defalias (OBJ, (ginitWithShtPtr)gnewWithShtPtr, TP, (I16*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithShtPtr               , TP, (I16*)ref, (U32)n, (I32)s)
  retmethod( gclone(aShtVectorRef(ref,n,s)) );
endmethod
#endif

#ifdef INTVECTOR_ONLY
defalias (OBJ, (ginitWithIntPtr)gnewWithIntPtr, TP, (I32*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithIntPtr               , TP, (I32*)ref, (U32)n, (I32)s)
  retmethod( gclone(aIntVectorRef(ref,n,s)) );
endmethod
#endif

#ifdef LNGVECTOR_ONLY
defalias (OBJ, (ginitWithLngPtr)gnewWithLngPtr, TP, (I64*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithLngPtr               , TP, (I64*)ref, (U32)n, (I32)s)
  retmethod( gclone(aLngVectorRef(ref,n,s)) );
endmethod
#endif

#ifdef FLTVECTOR_ONLY
defalias (OBJ, (ginitWithFltPtr)gnewWithFltPtr, TP, (F64*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithFltPtr               , TP, (F64*)ref, (U32)n, (I32)s)
  retmethod( gclone(aFltVectorRef(ref,n,s)) );
endmethod
#endif

#ifdef CPXVECTOR_ONLY
defalias (OBJ, (ginitWithCpxPtr)gnewWithCpxPtr, TP, (C64*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithCpxPtr               , TP, (C64*)ref, (U32)n, (I32)s)
  retmethod( gclone(aCpxVectorRef(ref,n,s)) );
endmethod
#endif


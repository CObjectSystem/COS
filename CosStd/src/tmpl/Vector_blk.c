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
 | $Id: Vector_blk.c,v 1.2 2009/09/01 11:57:37 ldeniau Exp $
 |
*/

#define VECTOR_TMPL

#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/XRange.h>
#include <cos/View.h>

#include <cos/gen/accessor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/init.h>
#include <cos/gen/new.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>
#include <cos/prp/sequence.h>

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

// ----- properties

#define size(siz) gautoDelete(aInt(siz))
#define class(vec) T

defproperty(T,   size , size);
defproperty(T, ()class, class);

#undef size
#undef class

// --- getters

defmethod(struct Slice, gslice, T)
  retmethod( *atSlice(0,self->size,self->stride) );
endmethod

defmethod(U32, gsize, T)
  retmethod(self->size);
endmethod

defmethod(VAL*, TOVALPTR, T)
  retmethod(self->valref);
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

  vec->valref = vecn->_valref;
  vec->size   = size;
  vec->stride = 1;

  return vec;
}

// --- copy

static inline void
copy(VAL *dst, U32 dst_n, VAL *src, I32 src_s)
{
  VAL *end = dst + dst_n;

  while (dst != end) {
    *dst++ = RETAIN(*src);
    src += src_s;
  }
}

// ----- allocator

defmethod(OBJ, galloc, TP) // lazy alloc
  retmethod(_1);
endmethod

// ----- initializers

defmethod(OBJ, ginitWith, T, T) // copy
  PRE
    test_assert(self->size == self2->size, "incompatible " TS "sizes");
    
  POST
    // automatically trigger ginvariant

  BODY
    copy(self->valref,self->size,self2->valref,self2->stride);
    
    retmethod(_1);
endmethod

// ----- constructors

defalias (OBJ, (ginitWith)gnewWith, TP, T);
defmethod(OBJ,  ginitWith         , TP, T) // clone
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct T* vec = T_alloc(self2->size);
    OBJ _vec = (OBJ)vec; PROTECT(_vec);

    copy(vec->valref,vec->size,self2->valref,self2->stride);

    UNPROTECT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Slice);
defmethod(OBJ,  ginitWith         , TP, Slice) // Int sequence
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    U32 size = Slice_size(self2);
    
    struct T* vec = T_alloc(size);
    OBJ _vec = (OBJ)vec; PROTECT(_vec);
  
    for (U32 i = 0; i < size; i++)
      vec->valref[i] = RETAIN(VALINT(Slice_eval(self2,i)));

    UNPROTECT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Range);
defmethod(OBJ,  ginitWith         , TP, Range) // Int sequence
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    U32 size = Range_size(self2);
    
    struct T* vec = T_alloc(size);
    OBJ _vec = (OBJ)vec; PROTECT(_vec);
  
    for (U32 i = 0; i < size; i++)
      vec->valref[i] = RETAIN(VALINT(Range_eval(self2,i)));

    UNPROTECT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, XRange);
defmethod(OBJ,  ginitWith         , TP, XRange) // Float sequence
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    U32 size = XRange_size(self2);
    
    struct T* vec = T_alloc(size);
    OBJ _vec = (OBJ)vec; PROTECT(_vec);
  
    for (U32 i = 0; i < size; i++)
      vec->valref[i] = RETAIN(VALFLT(XRange_eval(self2,i)));

    UNPROTECT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Int, Object);
defmethod(OBJ,  ginitWith2          , TP, Int, Object) // element
  PRE
    test_assert(self2->value >= 0, "negative " TS " size");

  POST
    // automatically trigger ginvariant

  BODY
    VAL val = TOVAL(_3);

    struct T* vec = T_alloc(self2->value);
    OBJ _vec = (OBJ)vec; PROTECT(_vec);

    VAL *dst = vec->valref;
    VAL *end = vec->valref + vec->size;

    while (dst != end)
      *dst++ = RETAIN(val);

    UNPROTECT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Int, Functor);
defmethod(OBJ,  ginitWith2          , TP, Int, Functor) // generator
  PRE
    test_assert(self2->value >= 0, "negative " TS " size");

  POST
    // automatically trigger ginvariant

  BODY
    struct T* vec = T_alloc(self2->value);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    VAL *dst = vec->valref;
    VAL *end = vec->valref + vec->size;
    int argc = garity(_3);

    if (!argc)
      while (dst != end)
        *dst++ = RETAIN(TOVAL(geval(_3)));

    else
      for (I32 i = 0; dst != end; i++)
        *dst++ = RETAIN(TOVAL(geval1(_3, aInt(i))));

    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, T, Slice);
defmethod(OBJ,  ginitWith2          , TP, T, Slice) // sub vector
  PRE
    test_assert( Slice_first(self3) < self2->size &&
                 Slice_last (self3) < self2->size, "slice out of range" );

  POST
    // automatically trigger ginvariant

  BODY
    I32 start  = Slice_start (self3)*self2->stride;
    I32 stride = Slice_stride(self3)*self2->stride;

    struct T* vec = T_alloc(self3->size);
    OBJ _vec = (OBJ)vec; PROTECT(_vec);

    copy(vec->valref,vec->size,self2->valref+start,stride);

    UNPROTECT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, T, Range);
defmethod(OBJ,  ginitWith2          , TP, T, Range) // sub vector
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod( ginitWith2(_1,_2,(OBJ)&slice) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, T, IntVector);
defmethod(OBJ,  ginitWith2          , TP, T, IntVector) // random sequence
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct T* vec = T_alloc(self3->size);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    VAL *dst   = vec->valref;
    VAL *end   = vec->valref + vec->size;
    VAL *src   = self2->valref;
    U32  src_n = self2->size;
    I32  src_s = self2->stride;
    I32 *idx   = self3->value;
    I32  idx_s = self3->stride;

    while (dst != end) {
      U32 i = Range_index(*idx, src_n);
      test_assert( i < src_n, "index out of range" );
      *dst++ = RETAIN(src[i*src_s]);
      idx += idx_s;
    }

    UNPRT(_vec);
    retmethod(_vec);
endmethod

#ifdef ARRAY_ONLY

// ----- destructor

defmethod(OBJ, gdeinit, T)
  VAL *val = self->valref;
  VAL *end = self->valref + self->size;

  while (val != end) // take care of protection cases
    if (*val) RELEASE(*val++);

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, T, (STR)func, (STR)file, (int)line)
  VAL *val   = self->valref;
  VAL *end   = self->valref + self->size*self->stride;
  I32  val_s = self->stride;

  while (val != end && *val)
    val += val_s;

  test_assert( val == end, TS " contains null elements", func, file, line);
endmethod

#endif // ARRAY_ONLY

// ----- constructors from C array

#ifdef SHTVECTOR_ONLY
defalias (OBJ, (ginitWithShtPtr)gnewWithShtPtr, TP, (I16*)ref, (U32)n);
defmethod(OBJ,  ginitWithShtPtr               , TP, (I16*)ref, (U32)n)
  retmethod( ginitWith(_1, aShtVectorRef(ref,n)) );
endmethod
#endif

#ifdef INTVECTOR_ONLY
defalias (OBJ, (ginitWithIntPtr)gnewWithIntPtr, TP, (I32*)ref, (U32)n);
defmethod(OBJ,  ginitWithIntPtr               , TP, (I32*)ref, (U32)n)
  retmethod( ginitWith(_1, aIntVectorRef(ref,n)) );
endmethod
#endif

#ifdef LNGVECTOR_ONLY
defalias (OBJ, (ginitWithLngPtr)gnewWithLngPtr, TP, (I64*)ref, (U32)n);
defmethod(OBJ,  ginitWithLngPtr               , TP, (I64*)ref, (U32)n)
  retmethod( ginitWith(_1, aLngVectorRef(ref,n)) );
endmethod
#endif

#ifdef FLTVECTOR_ONLY
defalias (OBJ, (ginitWithFltPtr)gnewWithFltPtr, TP, (F64*)ref, (U32)n);
defmethod(OBJ,  ginitWithFltPtr               , TP, (F64*)ref, (U32)n)
  retmethod( ginitWith(_1, aFltVectorRef(ref,n)) );
endmethod
#endif

#ifdef CPXVECTOR_ONLY
defalias (OBJ, (ginitWithCpxPtr)gnewWithCpxPtr, TP, (C64*)ref, (U32)n);
defmethod(OBJ,  ginitWithCpxPtr               , TP, (C64*)ref, (U32)n)
  retmethod( ginitWith(_1, aCpxVectorRef(ref,n)) );
endmethod
#endif


/*
 o---------------------------------------------------------------------o
 |
 | COS Array - block array
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
 | of MERCHANTABILITY or FIArrayNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Array.c,v 1.54 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/XRange.h>

#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include "Array_utl.h"

// -----

makclass(Array, Sequence);

makclass(Array0, Array);
makclass(Array1, Array);
makclass(Array2, Array);
makclass(Array3, Array);
makclass(Array4, Array);
makclass(Array5, Array);
makclass(Array6, Array);
makclass(Array7, Array);
makclass(Array8, Array);
makclass(Array9, Array);
makclass(ArrayN, Array);

// -----

useclass(Array);

// --- getters

defmethod(U32, gsize, Array)
  retmethod(self->size);
endmethod

defmethod(OBJ*, gobjPtr, Array)
  retmethod(self->object);
endmethod

defmethod(OBJ, gisEmpty, Array)
  retmethod(self->size ? False : True);
endmethod

defmethod(OBJ, gclass, Array)
  retmethod(Array);     // class cluster: hide implementation details
endmethod

// --- alloc

struct Array*
Array_alloc(U32 size)
{
  enum { N = 10 };
  static struct Class* cls[] = {
    classref(Array0, Array1, Array2, Array3, Array4,
             Array5, Array6, Array7, Array8, Array9,
             ArrayN)
  };

  OBJ _cls = (OBJ)cls[size > N ? N : size];
  OBJ _vec = gallocWithSize(_cls, size * sizeof(OBJ));

  struct ArrayN *vecn = STATIC_CAST(struct ArrayN*, _vec);
  struct Array  *vec  = &vecn->Array;

  vec->object = vecn->_object;
  vec->size   = 0;
  vec->stride = 1;

  return vec;
}

// ----- allocator

defmethod(OBJ, galloc, pmArray) // lazy alloc
  retmethod(_1);
endmethod

// ----- constructors

defmethod(OBJ, gcopy, Array) // copy
  struct Array* cpy = Array_alloc(self->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  copy(cpy->object,1,&cpy->size,self->object,self->stride,self->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defmethod(OBJ, gclone, Array) // clone
  struct Array* cpy = Array_alloc(self->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  clone(cpy->object,1,&cpy->size,self->object,self->stride,self->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Array);
defmethod(OBJ,  ginitWith         , pmArray, Array) // copy
  struct Array* cpy = Array_alloc(self2->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  copy(cpy->object,1,&cpy->size,self2->object,self2->stride,self2->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Slice);
defmethod(OBJ,  ginitWith         , pmArray, Slice) // Int sequence
  U32 size = Slice_size(self2);
  
  struct Array* vec = Array_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  for (U32 i = 0; i < size; i++) {
    vec->object[i] = gclone(aInt(Slice_eval(self2,i)));
    vec->size++;
  }

  UNPRT(_vec);
  retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, Range);
defmethod(OBJ,  ginitWith         , pmArray, Range) // Int sequence
  PRE POST BODY
    U32 size = Range_size(self2);
    
    struct Array* vec = Array_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);
  
    for (U32 i = 0; i < size; i++) {
      vec->object[i] = gclone(aInt(Range_eval(self2,i)));
      vec->size++;
    }

    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmArray, XRange);
defmethod(OBJ,  ginitWith         , pmArray, XRange) // Float sequence
  PRE POST BODY
    U32 size = XRange_size(self2);

    struct Array* vec = Array_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);
  
    for (U32 i = 0; i < size; i++) {
      vec->object[i] = gclone(aFloat(XRange_eval(self2,i)));
      vec->size++;
    }
    
    if (size) { // avoid overshoot
      F64 end = XRange_eval(self2, size-1);

      if ((XRange_stride(self2) > 0 && end > XRange_end(self2)) ||
          (XRange_stride(self2) < 0 && end < XRange_end(self2)))
        ginitWith(vec->object[size-1], aFloat(XRange_end(self2)));     
    }
    
    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Int, Object);
defmethod(OBJ,  ginitWith2          , pmArray, Int, Object) // element
  PRE
    test_assert(self2->value >= 0, "negative array size");
  POST
  BODY
    OBJ val = _3;
    U32 size = self2->value;
    
    struct Array* vec = Array_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    U32 *dst_n = &vec->size;
    OBJ *dst   = vec->object;
    OBJ *end   = dst + size;

    while (dst != end)
      *dst++ = gretain(val), ++*dst_n;

    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Int, Functor);
defmethod(OBJ,  ginitWith2          , pmArray, Int, Functor) // generator
  PRE
    test_assert(self2->value >= 0, "negative array size");
  POST
  BODY
    U32 size = self2->value;
    struct Array* vec = Array_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    U32 *dst_n = &vec->size;
    OBJ *dst   = vec->object;
    OBJ *end   = dst + size;
    OBJ res;

    while (dst != end) {
      res = geval(_3);
      *dst++ = gretain(res), ++*dst_n;
    }

    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Array, Slice);
defmethod(OBJ,  ginitWith2          , pmArray, Array, Slice) // sub vector
  PRE
    test_assert( Slice_first(self3) < self2->size &&
                 Slice_last (self3) < self2->size, "slice out of range" );
  POST
  BODY
    I32 start  = Slice_start (self3)*self2->stride;
    I32 stride = Slice_stride(self3)*self2->stride;
    U32 size   = self3->size;
    struct Array* vec = Array_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    copy(vec->object,1,&vec->size,self2->object+start,stride,size);

    UNPRT(_vec);
    retmethod(_vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Array, Range);
defmethod(OBJ,  ginitWith2          , pmArray, Array, Range) // sub vector
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);

  retmethod( ginitWith2(_1,_2,(OBJ)&slice) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Array, IntVector);
defmethod(OBJ,  ginitWith2          , pmArray, Array, IntVector) // random sequence
  PRE POST BODY
    U32 size = self3->size;
    struct Array* vec = Array_alloc(size);
    OBJ _vec = (OBJ)vec; PRT(_vec);

    U32  val_n = self2->size;
    I32  val_s = self2->stride;
    OBJ *val   = self2->object;
    I32  idx_s = self3->stride;
    I32 *idx   = self3->value;
    U32 *dst_n = &vec->size;
    OBJ *dst   = vec->object;
    OBJ *end   = dst + size;

    while (dst != end) {
      U32 i = Range_index(*idx, val_n);
      test_assert( i < val_n, "index out of range" );
      *dst++ = gretain(val[i*val_s]), ++*dst_n;
      idx += idx_s;
    }

    UNPRT(_vec);
    retmethod(_vec);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, Array)
  U32 *val_n = &self->size;
  OBJ *val   = self->object;
  OBJ *end   = val + *val_n;

  while (val != end)
    grelease(*--end), --*val_n;

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, Array, (STR)func, (STR)file, (int)line)
  U32  size  = self->size;
  I32  val_s = self->stride;
  OBJ *val   = self->object;
  OBJ *end   = val + val_s*size;

  while (val != end && *val)
    val += val_s;

  test_assert( val == end, "array contains null elements", func, file, line);
endmethod


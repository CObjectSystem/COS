/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Array view
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
 | $Id: Array_vw.c,v 1.8 2010/06/02 22:47:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Number.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/collection.h>
#include <cos/gen/sequence.h>
#include <cos/gen/object.h>

// -----

makclass(ArrayView, Array);
makclass(ArraySubView, ArrayView);

// -----

useclass(ArrayView, ArraySubView);

// ----- initializer

struct Array*
ArrayView_init(struct ArrayView *arrv, struct Array *arr, struct Slice *slc, BOOL isSub)
{
  test_assert( Slice_first(slc) < arr->size &&
               Slice_last (slc) < arr->size, "slice out of range" );

  struct Array* vw = &arrv->Array;

  vw->object = Slice_start (slc)*arr->stride + arr->object;
  vw->size   = Slice_size  (slc);
  vw->stride = isSub ? Slice_stride(slc) : Slice_stride(slc)*arr->stride;
  arrv->ref  = (OBJ)arr;

  return vw;
}

static OBJ
ArrayView_make(OBJ vw, struct Array *arr, struct Slice *slc, BOOL isSub)
{
  PRT(vw);
  struct ArrayView *arrv = chkcast(ArrayView, vw);
  
  arrv->ref = 0;
  arrv->ref = gretain(gadjust( (OBJ)arr ));

  ArrayView_init(arrv, arr, slc, isSub);

  UNPRT(vw);
  return vw;
}

// ----- view constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mView, Array, Slice) // array view
  retmethod( ArrayView_make(galloc(ArrayView), self2, self3, NO) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Range);
defmethod(OBJ,  ginitWith2          , mView, Array, Range) // array view
  struct Slice *slice = Slice_fromRange(atSlice(0), self3, &self2->size);
  
  retmethod( ArrayView_make(galloc(ArrayView), self2, slice, NO) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Slice) // array subview
  retmethod( ArrayView_make(galloc(ArraySubView), self2, self3, YES) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Range);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Range) // vector subview
  struct Slice *slice = Slice_fromRange(atSlice(0),self3, &self2->size);

  retmethod( ArrayView_make(galloc(ArraySubView), self2, slice, YES) );
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayView)
  if (self->ref)              // take care of protection cases
    grelease(self->ref), self->ref = 0;
    
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf(self->ref, classref(Array)),
               "array view points to something not an array", func, file, line);

  test_assert( !cos_object_isKindOf((OBJ)self->ref, classref(ArrayDyn)) ||
                cos_object_rc(self->ref) == COS_RC_AUTO ,
               "array view points to a dynamic array", func, file, line);

  struct Array *vec = chkcast(Array, self->ref);

  I32 start  = (vec->object - self->Array.object)/vec->stride;
  U32 size   = self->Array.size;
  I32 stride = self->Array.stride/vec->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < vec->size &&
               last  < vec->size, "array view is out of range", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod


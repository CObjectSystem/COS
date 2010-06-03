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
 | $Id: Array_vw.c,v 1.9 2010/06/03 15:27:50 ldeniau Exp $
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

// ----- initializer (weaker than constructors: no retain)

defmethod(OBJ, ginitWith2, ArrayView, Array, Slice) // array view
  test_assert( Slice_first(self3) < self2->size &&
               Slice_last (self3) < self2->size, "slice out of range" );

  self->Array.object = Slice_start (self3)*self2->stride + self2->object;
  self->Array.size   = Slice_size  (self3);
  self->Array.stride = Slice_stride(self3)*self2->stride;
  self->ref          = _2; // no retain!

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, ArrayView, Array, Range) // array view
  OBJ slc = (OBJ)Slice_fromRange(atSlice(0), self3, &self2->size);
  retmethod( ginitWith2(_1,_2,(OBJ)slc) );
endmethod

defmethod(OBJ, ginitWith2, ArraySubView, Array, Slice) // array subview
  test_assert( Slice_first(self3) < self2->size &&
               Slice_last (self3) < self2->size, "slice out of range" );

  self->ArrayView.Array.object = Slice_start (self3) + self2->object;
  self->ArrayView.Array.size   = Slice_size  (self3);
  self->ArrayView.Array.stride = Slice_stride(self3);
  self->ArrayView.ref          = _2; // no retain!

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, ArraySubView, Array, Range) // array subview
  OBJ slc = (OBJ)Slice_fromRange(atSlice(0), self3, &self2->size);
  retmethod( ginitWith2(_1,_2,(OBJ)slc) );
endmethod

// ----- view constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mView, Array, Slice) // array view
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArrayView);    PRT(avw);

  ginitWith2(avw, arr, _3);

  UNPRT(arr);
  retmethod(avw);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Range);
defmethod(OBJ,  ginitWith2          , mView, Array, Range) // array view
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArrayView);    PRT(avw);

  ginitWith2(avw, arr, _3);

  UNPRT(arr);
  retmethod(avw);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Slice) // array subview
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArraySubView); PRT(avw);

  ginitWith2(avw, arr, _3);

  UNPRT(arr);
  retmethod(avw);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Range);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Range) // array subview
  OBJ arr = gretain(gadjust(_2)); PRT(arr);
  OBJ avw = galloc(ArraySubView); PRT(avw);

  ginitWith2(avw, arr, _3);
  
  UNPRT(arr);
  retmethod(avw);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayView)
  if (self->ref && cos_object_rc(_1) != COS_RC_AUTO)
    grelease(self->ref), self->ref = 0;
    
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayView, (STR)file, (int)line)
  test_assert( cos_object_isKindOf(self->ref, classref(Array)),
               "array view points to something not an array", file, line);

  test_assert( !cos_object_isKindOf(self->ref, classref(ArrayDyn)) ||
                cos_object_rc(_1) == COS_RC_AUTO,
               "array view points to a dynamic array", file, line);

  struct Array *vec = edyncast(Array, self->ref);

  I32 start  = (vec->object - self->Array.object)/vec->stride;
  U32 size   = self->Array.size;
  I32 stride = self->Array.stride/vec->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < vec->size &&
               last  < vec->size, "array view is out of range", file, line);

  if (next_method_p)
    next_method(self, file, line);
endmethod


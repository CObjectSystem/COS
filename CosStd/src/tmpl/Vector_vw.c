/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - Vector view
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
 | $Id: Vector_vw.c,v 1.3 2009/08/29 21:53:08 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// -----

makclass(TV, T);

// -----

useclass(TV);

// ----- initializer

struct T*
TV_init(struct TV *vecv, struct T *vec, struct Slice *slc)
{
  test_assert( Slice_first(slc) < vec->size &&
               Slice_last (slc) < vec->size, "slice out of range" );

  struct T* vw = &vecv->T;

  vw->valref = Slice_start (slc)*vec->stride + vec->valref;
  vw->size   = Slice_size  (slc);
  vw->stride = Slice_stride(slc)*vec->stride;
  vecv->ref  = vec;

  return vw;
}

// ----- constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, T, Slice);
defmethod(OBJ,  ginitWith2          , mView, T, Slice) // vector view
  OBJ vec = galloc(TV); PRT(vec);
  vec = ginitWith2(vec,_2,_3);
  UNPRT(vec);
  retmethod(vec);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mView, T, Range);
defmethod(OBJ,  ginitWith2          , mView, T, Range) // vector view
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod( ginitWith2(_1,_2,(OBJ)&slice) );
endmethod

defmethod(OBJ, ginitWith2, TV, T, Slice) // vector view
  PRE
    test_assert( !cos_object_isKindOf(_2, classref(TD)),
                 TS " views accept only non-dynamic " TS );
  POST
  
  BODY
    OBJ ref = gretain(_2); PRT(ref);

    TV_init(self1, STATIC_CAST(struct T*, ref), self3);

    UNPRT(ref);
    retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, TV)
  if (self->ref)              // take care of protection cases
    grelease( (OBJ)self->ref );
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, TV, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf((OBJ)self->ref, classref(T)),
               TS " view points to something not a " TS, func, file, line);

  test_assert( !cos_object_isKindOf((OBJ)self->ref, classref(TD)),
               TS " view points to a dynamic " TS, func, file, line);

  struct T *vec = self->ref;

  I32 start  = (vec->valref - self->T.valref)/vec->stride;
  U32 size   = self->T.size;
  I32 stride = self->T.stride/vec->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < self->ref->size && last < self->ref->size,
               TS " view is out of range", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod


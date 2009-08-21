/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - accessors
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
 | $Id: Vector_acc.c,v 1.1 2009/08/21 12:10:00 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// ----- getters (index, slice, intvector)

#if defined(INTVECTOR_ONLY) || defined(LNGVECTOR_ONLY) || defined(FLTVECTOR_ONLY)

defmethod(F64, gfltAt, T, Int)
  U32 i;

  PRE
    i = Range_index(self2->valref, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->valref, self->size);
      
    retmethod( self->valref[i*self->stride] );
endmethod

#endif // VECTOR_ONLY

defmethod(OBJ, ggetAt, T, Int)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );
    
  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->value, self->size);

    retmethod( AUTODELETE(VALOBJ(self->valref[i*self->stride])) );
endmethod

defmethod(OBJ, ggetAt, T, Slice)
  retmethod( gautoDelete(ginitWith2(T,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, T, IntVector)
  retmethod( gautoDelete(ginitWith2(T,_1,_2)) );
endmethod

// ---

defalias (OBJ, (gget)glast, T);
defalias (OBJ, (gget)gtop , T);
defmethod(OBJ,  gget      , T)
  retmethod( self->size
           ? AUTODELETE(VALOBJ(self->valref[(self->size-1)*self->stride]))
           : Nil );
endmethod

defmethod(OBJ, gfirst, T)
  retmethod( self->size ? AUTODELETE(VALOBJ(self->valref[0])) : Nil );
endmethod

// ----- setters (index, slice, intvector)

defmethod(void, gputAt, T, Int, Object)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->value, self->size);
 
    VAL *dst = self->valref + i*self->stride;
    ASSIGN(*dst,TOVAL(_3));
endmethod

#ifdef FLTVECTOR_ONLY

defmethod(void, gputAt, T, Int, Float)
  U32 i;
  
  PRE
    i = Range_index(self2->valref, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->valref, self->size);
      
    self->valref[i*self->stride] = self3->valref;
endmethod

#endif

defmethod(void, gputAt, T, Slice, T)
  PRE
    U32 first = Slice_first(self2);
    U32 last  = Slice_last (self2);

    test_assert( first < self->size &&
                 last  < self->size, "slice out of range" );

    test_assert( self->size < self3->size, "source " TS " is too small" );
    
  BODY
    U32 start  = Slice_first (self2)*self->stride;
    I32 stride = Slice_stride(self2)*self->stride;
    VAL *dst   = self->valref + start;
    I32  dst_s = stride;
    VAL *src   = self3->valref;
    I32  src_s = self3->stride;
    VAL *end   = self3->valref + self3->size*self3->stride;

    while (src != end) {
      ASSIGN(*dst,*src);
      src += src_s;
      dst += dst_s;
    }
endmethod

defmethod(void, gputAt, T, IntVector, T)
  PRE
    test_assert( self2->size <= self3->size, "incompatible " TS " sizes" );

  BODY
    VAL *dst   = self->valref;
    U32  dst_n = self->size;
    I32  dst_s = self->stride;
    I32 *idx   = self2->value;
    I32  idx_s = self2->stride;
    VAL *src   = self3->valref;
    I32  src_s = self3->stride;
    VAL *end   = self3->valref + self3->size*self3->stride;

    while (src != end) {
      U32 i = Range_index(*idx, dst_n);
      test_assert( i < dst_n, "index out of range" );
      ASSIGN(dst[i*dst_s],*src);
      src += src_s;
      idx += idx_s;
    }
endmethod


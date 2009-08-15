/*
 o---------------------------------------------------------------------o
 |
 | COS String - accessors
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
 | $Id: String_acc.c,v 1.1 2009/08/15 22:29:49 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Slice.h>

#include <cos/gen/accessor.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

useclass(String);

// ----- getters (index, slice, intvector)

defmethod(I32, gchrAt, String, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->value, self->size);
      
    retmethod( self->value[i] );
endmethod

defmethod(OBJ, ggetAt, String, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->value, self->size);
      
    retmethod( gautoDelete(aChar(self->value[i])) );
endmethod

defmethod(OBJ, ggetAt, String, Slice)
  retmethod( gautoDelete(ginitWith2(String,_1,_2)) );
endmethod

defmethod(OBJ, ggetAt, String, IntVector)
  retmethod( gautoDelete(ginitWith2(String,_1,_2)) );
endmethod

// ---

defalias (OBJ, (gget)glast, String);
defalias (OBJ, (gget)gtop , String);
defmethod(OBJ,  gget      , String)
  retmethod( self->size
           ? gautoDelete(aChar(self->value[(self->size-1)]))
           : Nil );
endmethod

defmethod(OBJ, gfirst, String)
  retmethod( self->size ? gautoDelete(aChar(self->value[0])) : Nil );
endmethod

// ----- setters (index, slice, intvector)

defmethod(void, gputAt, String, Int, Object)
  U32 i;
  
  PRE
    i = Range_index(self2->value, self->size);
    test_assert( i < self->size, "index out of range" );

  BODY
    if (!COS_CONTRACT)
      i = Range_index(self2->value, self->size);
      
    self->value[i] = gchr(_3);
endmethod

defmethod(void, gputAt, String, Slice, String)
  PRE
    U32 first = Slice_first(self2);
    U32 last  = Slice_last (self2);

    test_assert( first < self1->size &&
                 last  < self1->size, "slice out of range" );

    test_assert( self1->size < self3->size, "Source string is too small" );

  BODY
    U32   start  = Slice_first (self2);
    I32   stride = Slice_stride(self2);
    char *dst    = self1->value + start;
    I32   dst_s  = stride;
    char *src    = self3->value;
    char *end    = self3->value + self3->size;

  while (src != end) {
    *dst = *src++;
    dst += dst_s;
  }
endmethod

defmethod(void, gputAt, String, IntVector, String)
  PRE
    test_assert( self2->size <= self3->size, "incompatible array sizes" );

  BODY
    char *dst   = self1->value;
    U32   dst_z = self1->size;
    I32  *idx   = self2->value;
    I32   idx_s = self2->stride;
    char *src   = self3->value;
    char *end   = self3->value + self3->size;

    while (src != end) {
      U32 i = Range_index(*idx, dst_z);
      test_assert( i < dst_z, "index out of range" );
      dst[i] = *src++;
      idx += idx_s;
  }
endmethod


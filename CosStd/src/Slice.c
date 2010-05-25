/*
 o---------------------------------------------------------------------o
 |
 | COS Slice
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
 | $Id: Slice.c,v 1.21 2010/05/25 15:33:39 ldeniau Exp $
 |
*/

#include <cos/Slice.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/IntVector.h>

#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/range.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>
// #include <cos/prp/sequence.h>

makclass(Slice, ValueSequence);

// -----

useclass(Slice);

// ----- new

defmethod(OBJ, gnewSlc, pmSlice, (I32)start, (U32)size, (I32)stride)
  retmethod( (OBJ)Slice_init((struct Slice*)galloc(_1), start, size, stride) );
endmethod

// ----- copy/clone

defalias (OBJ, (gcopy)gclone, Slice);
defmethod(OBJ,  gcopy       , Slice)
  retmethod( (OBJ)Slice_copy((struct Slice*)galloc(Slice), self) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Slice, Slice)
  retmethod( Slice_isEqual(self, self2) ? True : False );
endmethod

// ----- size

defmethod(U32, gsize, Slice)
  retmethod(self->size);
endmethod

// ----- foreach

defmethod(void, gforeach, Slice, Functor)
  U32 size = Slice_size(self);
  
  for (U32 i = 0; i < size; i++)
    geval(_2, aInt(Slice_eval(self,i)));
endmethod

defmethod(void, gforeach, Slice, IntFunction1)
  U32 size = Slice_size(self);
  I32FCT1 fct = self2->fct;

  for (U32 i = 0; i < size; i++)
    fct(Slice_eval(self,i));
endmethod

// ----- map

defmethod(OBJ, gmap, Functor, Slice)
  U32 size = Slice_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  U32 *dst_n = &vec->size;
  I32 *dst   = vec->value;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = gint( geval1(_1, aInt(Slice_eval(self2,i))) ), ++*dst_n;

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap, IntFunction1, Slice)
  U32 size = Slice_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  U32 *dst_n  = &vec->size;
  I32 *dst    = vec->value;
  I32FCT1 fct = self1->fct;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = fct(Slice_eval(self2,i)), ++*dst_n;

   retmethod(_vec);
endmethod


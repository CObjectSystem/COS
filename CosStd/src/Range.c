/*
 o---------------------------------------------------------------------o
 |
 | COS Range
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
 | $Id: Range.c,v 1.20 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

#include <cos/Range.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/Number.h>
#include <cos/IntVector.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

makclass(Range, ValueSequence);

// -----

useclass(Range);

// ----- new

defmethod(OBJ, gnewRng, pmRange, (I32)start, (I32)end, (I32)stride)
  retmethod( (OBJ)Range_init((void*)galloc(_1), start, end, stride) );
endmethod

// ----- clone

defalias (OBJ, (gcopy)gclone, Range);
defmethod(OBJ,  gcopy       , Range)
  retmethod( (OBJ)Range_copy((void*)galloc(Range), self) );
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Range, Range)
  retmethod( Range_isEqual(self, self2) ? True : False );
endmethod

// ----- size

defmethod(U32, gsize, Range)
  retmethod(Range_size(self));
endmethod

// ----- foreach

defmethod(void, gforeach, Range, Functor)
  U32 size = Range_size(self);
  
  for (U32 i = 0; i < size; i++)
    geval(_2, aInt(Range_eval(self,i)));
endmethod

defmethod(void, gforeach, Range, IntFunction1)
  U32 size = Range_size(self);
  I32FCT1 fct = self2->fct;

  for (U32 i = 0; i < size; i++)
    fct(Range_eval(self,i));
endmethod

// ----- map

defmethod(OBJ, gmap, Functor, Range)
  U32 size = Range_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  U32 *dst_n = &vec->size;
  I32 *dst   = vec->value;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = gint( geval1(_1, aInt(Range_eval(self2,i))) ), ++*dst_n;

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap, IntFunction1, Range)
  U32 size = Range_size(self2);
  struct IntVector* vec = IntVector_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  U32 *dst_n  = &vec->size;
  I32 *dst    = vec->value;
  I32FCT1 fct = self1->fct;
  U32  i;

  for (i = 0; i < size; i++)
    *dst++ = fct(Range_eval(self2,i)), ++*dst_n;

  retmethod(_vec);
endmethod


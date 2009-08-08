/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Dyn array
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
 | $Id: Array_lzy.c,v 1.1 2009/08/08 19:56:53 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Range.h>
#include <cos/Number.h>
#include <cos/gen/accessor.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/new.h>

// ----- exception

useclass(ExBadArity);

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, ArrayLazy)
  if (self->generator)
    grelease(self->generator);
  next_method(self);
endmethod

// ----- getter

defmethod(OBJ, ggetAt, ArrayLazy, Int)
  struct Array *arr = &self->ArrayDyn.ArrayAdj.Array;
  U32 i = Range_index(self2->value, arr->size);

  switch(self->arity) {
  case 0:
    while (arr->size <= i)
      gappend(_1, geval(self->generator));
    break;

  case 1:
    while (arr->size <= i)
      gappend(_1, geval1(self->generator, _1));
    break;

  case 2:
    while (arr->size <= i)
      gappend(_1, geval2(self->generator, _1, aInt(arr->size)));
    break;

  default:
    THROW( gnewWithStr(ExBadArity, "Lazy array generator eval") );
  }

  retmethod( arr->object[i*arr->stride] );
endmethod



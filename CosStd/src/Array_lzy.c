/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Lazy dynamic array
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
 | $Id: Array_lzy.c,v 1.9 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/Range.h>

#include <cos/gen/accessor.h>
#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>

// -----

makclass(ArrayLzy, ArrayDyn);

// -----

useclass(ArrayLzy);

// ----- constructors

defalias (OBJ, (ginitWith)gnewWith, pmArray, Functor);
defmethod(OBJ,  ginitWith         , pmArray, Functor) // generator
  retmethod(ginitWith3(galloc(ArrayLzy),_2,aArrayRef(0,0),aInt(0)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Functor, Array);
defmethod(OBJ,  ginitWith2          , pmArray, Functor, Array) // generator
  retmethod(ginitWith3(galloc(ArrayLzy),_2,_3,aInt(self3->size*2)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmArray, Functor, Int);
defmethod(OBJ,  ginitWith2          , pmArray, Functor, Int) // generator
  retmethod(ginitWith3(galloc(ArrayLzy),_2,aArrayRef(0,0),_3));
endmethod

defalias (OBJ, (ginitWith3)gnewWith3, pmArray, Functor, Array, Int);
defmethod(OBJ,  ginitWith3          , pmArray, Functor, Array, Int) // generator
  retmethod(ginitWith3(galloc(ArrayLzy),_2,_3,_4));
endmethod

defmethod(OBJ,  ginitWith3, ArrayLzy, Functor, Array, Int) // generator
  defnext(OBJ,  ginitWith , ArrayLzy, Int); // forward to dynamic array
  
  next_method(self, self4);

  PRT(_1);
  self->generator = gretain(_2);

  if (self3->size > 0)
    gappend(_1,_3);

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayLzy)
  if (self->generator)          // take care of protection cases
    grelease(self->generator);
  next_method(self);
  retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, ArrayLzy)
  if (self->generator)
    grelease(self->generator), self->generator = 0;
  next_method(self);
endmethod

// ----- getter

defmethod(OBJ, ggetAt, ArrayLzy, Int)
  struct Array *vec = &self->ArrayDyn.ArrayFix.Array;
  U32 i = Range_index(self2->value, vec->size);

  while (vec->size <= i)
    gappend(_1, geval(self->generator));

  retmethod( vec->object[i*vec->stride] );
endmethod

// NOTE-TODO: other getters?


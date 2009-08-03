/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (closure)
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
 | $Id: Functor_itr.c,v 1.1 2009/08/03 21:20:39 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(IterateFun, Functor);

// ----- dtor

defmethod(OBJ, gdeinit, IterateFun)
  grelease(self->fun);
  retmethod(_1);
endmethod

// ----- builder - ctor

defmethod(OBJ, giterate, Functor, Int)
  useclass(IterateFun);

  test_assert(self2->value > 0, "invalid number of iteration");

  OBJ _itr = galloc(IterateFun); PRT(_itr);
  struct IterateFun *itr = STATIC_CAST(struct IterateFun*, _itr);

  itr->num = self2->value;
  itr->fun = gretain(_1);
  itr->fct =  0;

  if ( cos_object_isKindOf(itr->fun, classref(Function1)) )
    itr->fct = STATIC_CAST(struct Function1*, itr->fun)->fct;

  UNPRT(_itr);
  retmethod(gautoDelete(_itr));
endmethod

// ----- arity

defmethod(I32, garity, IterateFun)
  retmethod( garity(self->fun) ); // should be one
endmethod

// ----- eval

defmethod(OBJ, geval1, IterateFun, (OBJ))
  forward_message(self->fun);

  if (self->fct) {
    OBJFCT1 fct = self->fct;
    for (U32 i = self->num-1; i; i--)
      RETVAL = fct(RETVAL);
  }
  else {
    OBJ fun = self->fun;
    for (U32 i = self->num-1; i; i--)
      RETVAL = geval1(fun, RETVAL);
  }
endmethod



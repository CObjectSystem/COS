/*
 o---------------------------------------------------------------------o
 |
 | COS Functor iteration
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
 | $Id: Functor_itr.c,v 1.3 2009/08/29 21:33:39 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>
#include <cos/gen/algorithm.h>

makclass(IterateFun, Functor);

// ----- ator

static inline struct IterateFun*
IterateFun_alloc(I32 num)
{
  useclass(IterateFun);

  OBJ _itr = galloc(IterateFun);
  struct IterateFun *itr = STATIC_CAST(struct IterateFun*, _itr);

  itr->num = num;
  
  return itr;
}

// ----- dtor

defmethod(OBJ, gdeinit, IterateFun)
  grelease(self->fun);
  retmethod(_1);
endmethod

// ----- builder - ctor

defmethod(OBJ, giterate, Functor, Int)

  test_assert(self2->value > 0, "invalid number of iteration");
  test_assert(garity(_1)  == 1, "invalid arity");

  struct IterateFun *itr = IterateFun_alloc(self2->value);
  OBJ _itr = (OBJ)itr; PRT(_itr);

  itr->fun = gretain(_1);
  itr->fct =  0;

  UNPRT(_itr);
  retmethod(gautoDelete(_itr));
endmethod

defmethod(OBJ, giterate, Function1, Int)
  test_assert(self2->value > 0, "invalid number of iteration");

  struct IterateFun *itr = IterateFun_alloc(self2->value);
  OBJ _itr = (OBJ)itr; PRT(_itr);

  itr->fun = gretain(_1);
  itr->fct = STATIC_CAST(struct Function1*, itr->fun)->fct;

  UNPRT(_itr);
  retmethod(gautoDelete(_itr));
endmethod

// ----- arity

defmethod(I32, garity, IterateFun)
  retmethod(1);
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



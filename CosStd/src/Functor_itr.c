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
 | $Id: Functor_itr.c,v 1.6 2010/01/07 00:46:26 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/Functor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

makclass(IterateFun, Functor);

// -----

useclass(IterateFun);

// ----- dtor

defmethod(OBJ, gdeinit, IterateFun)
  grelease(self->fun);
  retmethod(_1);
endmethod

// ----- builder - ctor

defmethod(OBJ, giterate, Functor, Int)
  test_assert(self2->value > 0, "invalid number of iteration");

  OBJ _itr = gautoDelete(galloc(IterateFun));
  struct IterateFun *itr = STATIC_CAST(struct IterateFun*, _itr);

  itr->Functor.msk = self->msk;
  itr->num = self2->value;
  itr->fun = gretain(_1);
  itr->fct = 0;

  retmethod(_itr);
endmethod

defmethod(OBJ, giterate, Function1, Int)
  test_assert(self2->value > 0, "invalid number of iteration");

  OBJ _itr = gautoDelete(galloc(IterateFun));
  struct IterateFun *itr = STATIC_CAST(struct IterateFun*, _itr);

  itr->Functor.msk = self->FunExpr.Functor.msk;
  itr->num = self2->value;
  itr->fun = gretain(_1);
  itr->fct = STATIC_CAST(struct Function1*, itr->fun)->fct;

  retmethod(_itr);
endmethod

// ----- str

defmethod(STR, gstr, IterateFun)
  retmethod(gstr(self->fun));
endmethod

// ----- eval

defmethod(OBJ, gevalEnv, IterateFun, Container)
  forward_message(self->fun, _2);

  if (self->fct) {
    FUN1 fct = self->fct;
    for (U32 i = self->num-1; i; i--)
      RETVAL = fct(RETVAL);
  }
  else {
    OBJ fun = self->fun;
    struct Array *env = atArray(0);
    OBJ *arg = env->object;

    for (U32 i = self->num-1; i; i--) {
      *arg = RETVAL;
      RETVAL = gevalEnv(fun, (OBJ)env);
    }
  }
endmethod



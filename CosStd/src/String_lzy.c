/*
 o---------------------------------------------------------------------o
 |
 | COS String - Lazy dynamic string
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_lzy.c,v 1.5 2009/09/18 16:42:30 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/Slice.h>

#include <cos/gen/accessor.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/new.h>

// -----

makclass(StringLzy, StringDyn);

// ----- exception

useclass(ExBadArity, StringLzy);

// ----- constructors

defalias (OBJ, (ginitWith)gnewWith, pmString, Functor);
defmethod(OBJ,  ginitWith         , pmString, Functor) // generator
  retmethod( ginitWith3(galloc(StringLzy),_2,aStringRef(0,0),aInt(0)) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, Functor, String);
defmethod(OBJ,  ginitWith2          , pmString, Functor, String) // generator
  retmethod( ginitWith3(galloc(StringLzy),_2,_3,aInt(self3->size*2)) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, Functor, Int);
defmethod(OBJ,  ginitWith2          , pmString, Functor, Int) // generator
  retmethod( ginitWith3(galloc(StringLzy),_2,aStringRef(0,0),_3) );
endmethod

defalias (OBJ, (ginitWith3)gnewWith3, pmString, Functor, String, Int);
defmethod(OBJ,  ginitWith3          , pmString, Functor, String, Int) // generator
  retmethod( ginitWith3(galloc(StringLzy),_2,_3,_4) );
endmethod

defmethod(OBJ,  ginitWith3, StringLzy, Functor, String, Int) // generator
  defnext(OBJ,  ginitWith , StringLzy, Int); // forward to dynamic string

  next_method(self, self4);

  PRT(_1);
  self->generator = gretain(_2);
  self->arity     = garity (_2);

  test_assert( (U32)self->arity < 3, "invalid generator arity" );

  if (self3->size > 0)
    gappend(_1,_3);

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, StringLzy)
  if (self->generator)          // take care of protection cases
    grelease(self->generator);
  next_method(self);
  retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, StringLzy)
  if (self->generator)
    grelease(self->generator);
  next_method(self);
endmethod

// ----- getter

defmethod(OBJ, ggetAt, StringLzy, Int)
  struct String *str = &self->StringDyn.StringFix.String;
  U32 i = Range_index(self2->value, str->size);

  switch(self->arity) {
  case 0:
    while (str->size <= i)
      gappend(_1, geval(self->generator));
    break;

  case 1:
    while (str->size <= i)
      gappend(_1, geval(self->generator, _1));
    break;

  case 2:
    while (str->size <= i)
      gappend(_1, geval(self->generator, _1, aInt(str->size)));
    break;

  default:
    THROW( gnewWithStr(ExBadArity, "lazy string generator eval") );
  }

  retmethod( gautoDelete(aChar(str->value[i])) );
endmethod

// NOTE-TODO: other getters?


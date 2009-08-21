/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - Lazy dynamic vector
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
 | $Id: Vector_lzy.c,v 1.1 2009/08/21 12:10:00 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// -----

makclass(TL, TD);

// -----

useclass(ExBadArity, TL);

// ----- constructors

defalias (OBJ, (ginitWith)gnewWith, TP, Functor);
defmethod(OBJ,  ginitWith         , TP, Functor) // generator
  retmethod( ginitWith(galloc(TL),_2) );
endmethod

defmethod(OBJ, ginitWith, TL, Functor)
  retmethod( ginitWith2(_1,_2,aTRef(0,0)) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Functor, T);
defmethod(OBJ,  ginitWith2          , TP, Functor, T) // generator
  retmethod( ginitWith2(galloc(TL),_2,_3) );
endmethod

defmethod(OBJ, ginitWith2, TL, Functor, T)
  defnext(OBJ, ginitWith , TL, Int); // dynamic array
  
  next_method(self, atInt(self3->size*2));

  self->generator = gretain(_2);
  self->arity     = garity (_2);

  test_assert( (U32)self->arity < 3, "invalid generator arity" );

  if (self3->size > 0)
    gappend(_1,_3);

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, TL)
  if (self->generator)          // take care of protection cases
    grelease(self->generator);
  next_method(self);
  retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, TL)
  if (self->generator)
    grelease(self->generator);
  next_method(self);
endmethod

// ----- getter

defmethod(OBJ, ggetAt, TL, Int)
  struct T *vec = &self->TD.TF.T;
  U32 i = Range_index(self2->value, vec->size);

  switch(self->arity) {
  case 0:
    while (vec->size <= i)
      gappend(_1, geval(self->generator));
    break;

  case 1:
    while (vec->size <= i)
      gappend(_1, geval1(self->generator, _1));
    break;

  case 2:
    while (vec->size <= i)
      gappend(_1, geval2(self->generator, _1, aInt(vec->size)));
    break;

  default:
    THROW( gnewWithStr(ExBadArity, "lazy " TS " generator eval") );
  }

  retmethod( AUTODELETE(VALOBJ(vec->valref[i*vec->stride])) );
endmethod



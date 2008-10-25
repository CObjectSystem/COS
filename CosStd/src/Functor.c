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
 | $Id: Functor.c,v 1.4 2008/10/25 19:56:05 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(Functor , Object );

makclass(Functor1, Functor);
makclass(Functor2, Functor);
makclass(Functor3, Functor);
makclass(Functor4, Functor);
makclass(Functor5, Functor);

makclass(Function1, Functor);
makclass(Function2, Functor);
makclass(Function3, Functor);
makclass(Function4, Functor);
makclass(Function5, Functor);

makclass(Compose  , Functor);

makclass(MultiFunctor2, Functor);
makclass(MultiFunctor3, Functor);

// -----

STATIC_ASSERT(functor1_to_function1_compatibility,
              COS_FIELD_COMPATIBILITY(Function1,Functor1,fct));

STATIC_ASSERT(functor2_to_function2_compatibility,
              COS_FIELD_COMPATIBILITY(Function2,Functor2,fct));

STATIC_ASSERT(functor3_to_function3_compatibility,
              COS_FIELD_COMPATIBILITY(Function3,Functor3,fct));

STATIC_ASSERT(functor4_to_function4_compatibility,
              COS_FIELD_COMPATIBILITY(Function4,Functor4,fct));

STATIC_ASSERT(functor5_to_function5_compatibility,
              COS_FIELD_COMPATIBILITY(Function5,Functor5,fct));

// -----

useclass(ExBadArity);

// ----- ctors

defmethod(OBJ, ginitWith, Functor1, Functor1)
  self->fct   = self2->fct;
  self->arity = self2->arity;
  self->arg   = self2->arg ? gretain(self2->arg) : 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor2, Functor2)
  self->fct    = self2->fct;
  self->arity  = self2->arity;
  self->arg[0] = self2->arg[0] ? gretain(self2->arg[0]) : 0;
  self->arg[1] = self2->arg[1] ? gretain(self2->arg[1]) : 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor3, Functor3)
  self->fct   = self2->fct;
  self->arity = self2->arity;

  for (int i = 0; i < 3; i++)
    self->arg[i] = self2->arg[i] ? gretain(self2->arg[i]) : 0;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor4, Functor4)
  self->fct   = self2->fct;
  self->arity = self2->arity;

  for (int i = 0; i < 4; i++)
    self->arg[i] = self2->arg[i] ? gretain(self2->arg[i]) : 0;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor5, Functor5)
  self->fct   = self2->fct;
  self->arity = self2->arity;

  for (int i = 0; i < 5; i++)
    self->arg[i] = self2->arg[i] ? gretain(self2->arg[i]) : 0;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function1, Function1)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function2, Function2)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function3, Function3)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function4, Function4)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function5, Function5)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, MultiFunctor2, MultiFunctor2)
  self->functor[0] = gretain(self2->functor[0]);
  self->functor[1] = gretain(self2->functor[1]);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, MultiFunctor3, MultiFunctor3)
  self->functor[0] = gretain(self2->functor[0]);
  self->functor[1] = gretain(self2->functor[1]);
  self->functor[2] = gretain(self2->functor[2]);
  retmethod(_1);
endmethod

defmethod(OBJ, galloc, mCompose)
  retmethod(_1); // lazy alloc
endmethod

defmethod(OBJ, ginitWith, mCompose, Compose) // clone
  useclass(Compose);

  OBJ _cmp = gallocWithSize(Compose, self2->size * sizeof *self2->functor);
  struct Compose *cmp = STATIC_CAST(struct Compose*, _cmp);

  cmp->size = self2->size;
  cmp->functor = cmp->_functor;

  retmethod( ginitWith(_cmp,_2) );
endmethod

defmethod(OBJ, ginitWith, Compose, Compose)
  test_assert(self->size <= self2->size);

  for (U32 i = 0; i < self->size; i++)
    self->functor[i] = gretain(self2->functor[i]);
  
  retmethod(_1);
endmethod

// ----- dtors

defmethod(OBJ, gdeinit, Functor)
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor1)
  if (self->arg) grelease(self->arg);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor2)
  if (self->arg[0]) grelease(self->arg[0]);
  if (self->arg[1]) grelease(self->arg[1]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor3)
  for (int i = 0; i < 3; i++)
    if (self->arg[i]) grelease(self->arg[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor4)
  for (int i = 0; i < 4; i++)
    if (self->arg[i]) grelease(self->arg[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor5)
  for (int i = 0; i < 5; i++)
    if (self->arg[i]) grelease(self->arg[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, MultiFunctor2)
  grelease(self->functor[0]);
  grelease(self->functor[1]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, MultiFunctor3)
  grelease(self->functor[0]);
  grelease(self->functor[1]);
  grelease(self->functor[3]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Compose)
  for (U32 i = 0; i < self->size; i++)
    grelease(self->functor[i]);

  retmethod(_1);
endmethod

// ----- Eval

// Functor1 & Function1

defmethod(OBJ, geval, Functor1)
  switch(self->arity) {
  case 1: // 1
    retmethod(self->fct(self->arg));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor1)") );
  }
endmethod

defmethod(OBJ, geval1, Functor1, (OBJ)arg1)
  switch(self->arity) {
  case 0: // 0
    retmethod(self->fct(arg1));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor1)") );
  }
endmethod

defmethod(OBJ, geval1, Function1, (OBJ)arg1)
  retmethod(self->fct(arg1));
endmethod

// ----- Functor2  & Function2

defmethod(OBJ, geval, Functor2)
  switch(self->arity) {
  case 3: // 1 1
    retmethod(self->fct(self->arg[0],self->arg[1]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor2)") );
  }
endmethod

defmethod(OBJ, geval1, Functor2, (OBJ)arg1)
  switch(self->arity) {
  case 1: // 1 0
    retmethod(self->fct(self->arg[0],arg1        ));
  case 2: // 0 1
    retmethod(self->fct(arg1        ,self->arg[1]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor2)") );
  }
endmethod

defmethod(OBJ, geval2, Functor2, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case 0: // 0 0
    retmethod(self->fct(arg1,arg2));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor2)") );
  }
endmethod

defmethod(OBJ, geval2, Function2, (OBJ)arg1, (OBJ)arg2)
  retmethod(self->fct(arg1,arg2));
endmethod

// ----- Functor3 & Function3

defmethod(OBJ, geval, Functor3)
  switch(self->arity) {
  case 7: // 1 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor3)") );
  }
endmethod

defmethod(OBJ, geval1, Functor3, (OBJ)arg1)
  switch(self->arity) {
  case 3: // 1 1 0
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ));
  case 5: // 1 0 1
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2]));
  case 6: // 0 1 1
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor3)") );
  }
endmethod

defmethod(OBJ, geval2, Functor3, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case 1: // 1 0 0
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ));
  case 2: // 0 1 0
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ));
  case 4: // 0 0 1
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor3)") );
  }
endmethod

defmethod(OBJ, geval3, Functor3, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  switch(self->arity) {
  case 0: // 0 0 0
    retmethod(self->fct(arg1,arg2,arg3));
  default:
    THROW( gnewWithStr(ExBadArity, "geval3(Functor3)") );
  }
endmethod

defmethod(OBJ, geval3, Function3, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  retmethod(self->fct(arg1,arg2,arg3));
endmethod

// ----- Functor4 & Function4

defmethod(OBJ, geval, Functor4)
  switch(self->arity) {
  case 15: // 1 1 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor4)") );
  }
endmethod

defmethod(OBJ, geval1, Functor4, (OBJ)arg1)
  switch(self->arity) {
  case  7: // 1 1 1 0
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],arg1        ));
  case 11: // 1 1 0 1
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,self->arg[3]));
  case 13: // 1 0 1 1
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],self->arg[3]));
  case 14: // 0 1 1 1
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor4)") );
  }
endmethod

defmethod(OBJ, geval2, Functor4, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case  3: // 1 1 0 0
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,arg2        ));
  case  5: // 1 0 1 0
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],arg2        ));
  case  6: // 0 1 1 0
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],arg2        ));
  case  9: // 1 0 0 1
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,self->arg[3]));
  case 10: // 0 1 0 1
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,self->arg[3]));
  case 12: // 0 0 1 1
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor4)") );
  }
endmethod

defmethod(OBJ, geval3, Functor4, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  switch(self->arity) {
  case 1: // 1 0 0 0
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,arg3        ));
  case 2: // 0 1 0 0
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,arg3        ));
  case 4: // 0 0 1 0
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],arg3        ));
  case 8: // 0 0 0 1
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval3(Functor4)") );
  }
endmethod

defmethod(OBJ, geval4, Functor4, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4)
  switch(self->arity) {
  case 0: // 0 0 0 0
    retmethod(self->fct(arg1,arg2,arg3,arg4));
  default:
    THROW( gnewWithStr(ExBadArity, "geval4(Functor4)") );
  }
endmethod

defmethod(OBJ, geval4, Function4, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4)
  retmethod(self->fct(arg1,arg2,arg3,arg4));
endmethod

// ----- Functor5 & Function5

defmethod(OBJ, geval, Functor5)
  switch(self->arity) {
  case 31: // 1 1 1 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor5)") );
  }
endmethod

defmethod(OBJ, geval1, Functor5, (OBJ)arg1)
  switch(self->arity) {
  case 15: // 1 1 1 1 0
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3],arg1        ));
  case 23: // 1 1 1 0 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],arg1        ,self->arg[4]));
  case 27: // 1 1 0 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,self->arg[3],self->arg[4]));
  case 29: // 1 0 1 1 1
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],self->arg[3],self->arg[4]));
  case 30: // 0 1 1 1 1
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor5)") );
  }
endmethod

defmethod(OBJ, geval2, Functor5, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case  7: // 1 1 1 0 0
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],arg1        ,arg2        ));
  case 11: // 1 1 0 1 0
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,self->arg[3],arg2        ));
  case 13: // 1 0 1 1 0
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],self->arg[3],arg2        ));
  case 14: // 0 1 1 1 0
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],self->arg[3],arg2        ));
  case 19: // 1 1 0 0 1
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,arg2        ,self->arg[4]));
  case 21: // 1 0 1 0 1
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],arg2        ,self->arg[4]));
  case 22: // 0 1 1 0 1
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],arg2        ,self->arg[4]));
  case 25: // 1 0 0 1 1
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,self->arg[3],self->arg[4]));
  case 26: // 0 1 0 1 1
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,self->arg[3],self->arg[4]));
  case 28: // 0 0 1 1 1
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor5)") );
  }
endmethod

defmethod(OBJ, geval3, Functor5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  switch(self->arity) {
  case  3: // 1 1 0 0 0
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,arg2        ,arg3        ));
  case  5: // 1 0 1 0 0
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],arg2        ,arg3        ));
  case  6: // 0 1 1 0 0
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],arg2        ,arg3        ));
  case  9: // 1 0 0 1 0
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,self->arg[3],arg3        ));
  case 10: // 0 1 0 1 0
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,self->arg[3],arg3        ));
  case 12: // 0 0 1 1 0
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],self->arg[3],arg3        ));
  case 17: // 1 0 0 0 1
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,arg3        ,self->arg[4]));
  case 18: // 0 1 0 0 1
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,arg3        ,self->arg[4]));
  case 20: // 0 0 1 0 1
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],arg3        ,self->arg[4]));
  case 24: // 0 0 0 1 1
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval3(Functor5)") );
  }
endmethod

defmethod(OBJ, geval4, Functor5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4)
  switch(self->arity) {
  case  1: // 1 0 0 0 0
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,arg3        ,arg4        ));
  case  2: // 0 1 0 0 0
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,arg3        ,arg4        ));
  case  4: // 0 0 1 0 0
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],arg3        ,arg4        ));
  case  8: // 0 0 0 1 0
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,self->arg[3],arg4        ));
  case 16: // 0 0 0 0 1
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,arg4        ,self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval4(Functor5)") );
  }
endmethod

defmethod(OBJ, geval5, Functor5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4, (OBJ)arg5)
  switch(self->arity) {
  case 0: // 0 0 0 0 0
    retmethod(self->fct(arg1,arg2,arg3,arg4,arg5));
  default:
    THROW( gnewWithStr(ExBadArity, "geval5(Functor5)") );
  }
endmethod

defmethod(OBJ, geval5, Function5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4, (OBJ)arg5)
  retmethod(self->fct(arg1,arg2,arg3,arg4,arg5));
endmethod

// ----- Compose

defmethod(OBJ, geval1, Compose, (OBJ))
  forward_message(self->functor[0]);

  for (U32 i = 1; i < self->size; i++)
    RETVAL = geval1(self->functor[i], RETVAL);

endmethod

defmethod(OBJ, geval2, Compose, (OBJ), (OBJ))
  forward_message(self->functor[0]);

  for (U32 i = 1; i < self->size; i++)
    RETVAL = geval1(self->functor[i], RETVAL);

endmethod

defmethod(OBJ, geval3, Compose, (OBJ), (OBJ), (OBJ))
  forward_message(self->functor[0]);

  for (U32 i = 1; i < self->size; i++)
    RETVAL = geval1(self->functor[i], RETVAL);

endmethod

defmethod(OBJ, geval4, Compose, (OBJ), (OBJ), (OBJ), (OBJ))
  forward_message(self->functor[0]);

  for (U32 i = 1; i < self->size; i++)
    RETVAL = geval1(self->functor[i], RETVAL);

endmethod

defmethod(OBJ, geval5, Compose, (OBJ), (OBJ), (OBJ), (OBJ), (OBJ))
  forward_message(self->functor[0]);

  for (U32 i = 1; i < self->size; i++)
    RETVAL = geval1(self->functor[i], RETVAL);

endmethod


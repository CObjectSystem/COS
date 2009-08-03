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
 | $Id: Functor.c,v 1.12 2009/08/03 21:20:39 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(Functor);

makclass(Functor1 , Functor);
makclass(Functor2 , Functor);
makclass(Functor3 , Functor);
makclass(Functor4 , Functor);
makclass(Functor5 , Functor);

useclass(ExBadArity);

// ----- Functors

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

// ----- arity

static const U8 argc[32] = {
//  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    0,  1,  1,  2,  1,  2,  2,  3,  1,  2,
// 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    2,  3,  2,  3,  3,  4,  1,  2,  2,  3,
// 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    2,  3,  3,  4,  2,  3,  3,  4,  3,  4,
// 30, 31
    4,  5
};

defmethod(I32, garity, Functor1)
  retmethod(0);
endmethod

defmethod(I32, garity, Functor2)
  retmethod(2-argc[self->arity]);
endmethod

defmethod(I32, garity, Functor3)
  retmethod(3-argc[self->arity]);
endmethod

defmethod(I32, garity, Functor4)
  retmethod(4-argc[self->arity]);
endmethod

defmethod(I32, garity, Functor5)
  retmethod(5-argc[self->arity]);
endmethod

// ----- eval


// --- Functor1

defmethod(OBJ, geval, Functor1)
  retmethod(self->fct(self->arg));
endmethod

// --- Functor2

defmethod(OBJ, geval, Functor2)
  switch (self->arity) {
  case 3: // 1 1
    retmethod(self->fct(self->arg[0],self->arg[1]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor2)") );
  }
endmethod

defmethod(OBJ, geval1, Functor2, (OBJ)arg1)
  switch (self->arity) {
  case 1: // 1 0
    retmethod(self->fct(self->arg[0],arg1        ));
  case 2: // 0 1
    retmethod(self->fct(arg1        ,self->arg[1]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor2)") );
  }
endmethod

// --- Functor3

defmethod(OBJ, geval, Functor3)
  switch (self->arity) {
  case 7: // 1 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor3)") );
  }
endmethod

defmethod(OBJ, geval1, Functor3, (OBJ)arg1)
  switch (self->arity) {
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
  switch (self->arity) {
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

// --- Functor4

defmethod(OBJ, geval, Functor4)
  switch (self->arity) {
  case 15: // 1 1 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor4)") );
  }
endmethod

defmethod(OBJ, geval1, Functor4, (OBJ)arg1)
  switch (self->arity) {
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
  switch (self->arity) {
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
  switch (self->arity) {
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

// --- Functor5

defmethod(OBJ, geval, Functor5)
  switch (self->arity) {
  case 31: // 1 1 1 1 1
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor5)") );
  }
endmethod

defmethod(OBJ, geval1, Functor5, (OBJ)arg1)
  switch (self->arity) {
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
  switch (self->arity) {
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
  switch (self->arity) {
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
  switch (self->arity) {
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


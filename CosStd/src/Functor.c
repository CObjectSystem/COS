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
 | $Id: Functor.c,v 1.3 2008/10/15 19:18:06 ldeniau Exp $
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

// -----

useclass(ExBadArity);

// ----- ctors

defmethod(OBJ, ginitWith, Functor1, Functor1)
  self->arity = self2->arity;
  self->fct   = self2->fct;
  self->arg   = self2->arg ? gretain(self2->arg) : 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor2, Functor2)
  self->arity  = self2->arity;
  self->fct    = self2->fct;
  self->arg[0] = self2->arg[0] ? gretain(self2->arg[0]) : 0;
  self->arg[1] = self2->arg[1] ? gretain(self2->arg[1]) : 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor3, Functor3)
  self->arity  = self2->arity;
  self->fct    = self2->fct;
  self->arg[0] = self2->arg[0] ? gretain(self2->arg[0]) : 0;
  self->arg[1] = self2->arg[1] ? gretain(self2->arg[1]) : 0;
  self->arg[2] = self2->arg[2] ? gretain(self2->arg[2]) : 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor4, Functor4)
  self->arity  = self2->arity;
  self->fct    = self2->fct;
  self->arg[0] = self2->arg[0] ? gretain(self2->arg[0]) : 0;
  self->arg[1] = self2->arg[1] ? gretain(self2->arg[1]) : 0;
  self->arg[2] = self2->arg[2] ? gretain(self2->arg[2]) : 0;
  self->arg[3] = self2->arg[3] ? gretain(self2->arg[3]) : 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Functor5, Functor5)
  self->arity  = self2->arity;
  self->fct    = self2->fct;
  self->arg[0] = self2->arg[0] ? gretain(self2->arg[0]) : 0;
  self->arg[1] = self2->arg[1] ? gretain(self2->arg[1]) : 0;
  self->arg[2] = self2->arg[2] ? gretain(self2->arg[2]) : 0;
  self->arg[3] = self2->arg[3] ? gretain(self2->arg[3]) : 0;
  self->arg[4] = self2->arg[4] ? gretain(self2->arg[4]) : 0;
  retmethod(_1);
endmethod

// ----- dtors

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
  if (self->arg[0]) grelease(self->arg[0]);
  if (self->arg[1]) grelease(self->arg[1]);
  if (self->arg[2]) grelease(self->arg[2]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor4)
  if (self->arg[0]) grelease(self->arg[0]);
  if (self->arg[1]) grelease(self->arg[1]);
  if (self->arg[2]) grelease(self->arg[2]);
  if (self->arg[3]) grelease(self->arg[3]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Functor5)
  if (self->arg[0]) grelease(self->arg[0]);
  if (self->arg[1]) grelease(self->arg[1]);
  if (self->arg[2]) grelease(self->arg[2]);
  if (self->arg[3]) grelease(self->arg[3]);
  if (self->arg[4]) grelease(self->arg[4]);
  retmethod(_1);
endmethod

// ----- Eval

// Functor1

defmethod(OBJ, geval, Functor1)
  switch(self->arity) {
  case 1: /* 1 */
    retmethod(self->fct(self->arg));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor1)") );
  }
endmethod

defmethod(OBJ, geval1, Functor1, (OBJ)arg1)
  switch(self->arity) {
  case 0: /* 0 */
    retmethod(self->fct(arg1));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor1)") );
  }
endmethod

// ----- Functor2

defmethod(OBJ, geval, Functor2)
  switch(self->arity) {
  case 3: /* 1 1 */
    retmethod(self->fct(self->arg[0],self->arg[1]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor2)") );
  }
endmethod

defmethod(OBJ, geval1, Functor2, (OBJ)arg1)
  switch(self->arity) {
  case 1: /* 1 0 */
    retmethod(self->fct(self->arg[0],arg1        ));
  case 2: /* 0 1 */
    retmethod(self->fct(arg1        ,self->arg[1]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor2)") );
  }
endmethod

defmethod(OBJ, geval2, Functor2, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case 0: /* 0 0 */
    retmethod(self->fct(arg1,arg2));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor2)") );
  }
endmethod

// ----- Functor3

defmethod(OBJ, geval, Functor3)
  switch(self->arity) {
  case 7: /* 1 1 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor3)") );
  }
endmethod

defmethod(OBJ, geval1, Functor3, (OBJ)arg1)
  switch(self->arity) {
  case 3: /* 1 1 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ));
  case 5: /* 1 0 1 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2]));
  case 6: /* 0 1 1 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor3)") );
  }
endmethod

defmethod(OBJ, geval2, Functor3, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case 1: /* 1 0 0 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ));
  case 2: /* 0 1 0 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ));
  case 4: /* 0 0 1 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor3)") );
  }
endmethod

defmethod(OBJ, geval3, Functor3, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  switch(self->arity) {
  case 0: /* 0 0 0 */
    retmethod(self->fct(arg1,arg2,arg3));
  default:
    THROW( gnewWithStr(ExBadArity, "geval3(Functor3)") );
  }
endmethod

// ----- Functor4

defmethod(OBJ, geval, Functor4)
  switch(self->arity) {
  case 15: /* 1 1 1 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor4)") );
  }
endmethod

defmethod(OBJ, geval1, Functor4, (OBJ)arg1)
  switch(self->arity) {
  case  7: /* 1 1 1 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],arg1        ));
  case 11: /* 1 1 0 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,self->arg[3]));
  case 13: /* 1 0 1 1 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],self->arg[3]));
  case 14: /* 0 1 1 1 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor4)") );
  }
endmethod

defmethod(OBJ, geval2, Functor4, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case  3: /* 1 1 0 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,arg2        ));
  case  5: /* 1 0 1 0 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],arg2        ));
  case  6: /* 0 1 1 0 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],arg2        ));
  case  9: /* 1 0 0 1 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,self->arg[3]));
  case 10: /* 0 1 0 1 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,self->arg[3]));
  case 12: /* 0 0 1 1 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor4)") );
  }
endmethod

defmethod(OBJ, geval3, Functor4, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  switch(self->arity) {
  case 1: /* 1 0 0 0 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,arg3        ));
  case 2: /* 0 1 0 0 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,arg3        ));
  case 4: /* 0 0 1 0 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],arg3        ));
  case 8: /* 0 0 0 1 */
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,self->arg[3]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval3(Functor4)") );
  }
endmethod

defmethod(OBJ, geval4, Functor4, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4)
  switch(self->arity) {
  case 0: /* 0 0 0 0 */
    retmethod(self->fct(arg1,arg2,arg3,arg4));
  default:
    THROW( gnewWithStr(ExBadArity, "geval4(Functor4)") );
  }
endmethod

// ----- Functor5

defmethod(OBJ, geval, Functor5)
  switch(self->arity) {
  case 31: /* 1 1 1 1 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval(Functor5)") );
  }
endmethod

defmethod(OBJ, geval1, Functor5, (OBJ)arg1)
  switch(self->arity) {
  case 15: /* 1 1 1 1 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],self->arg[3],arg1        ));
  case 23: /* 1 1 1 0 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],arg1        ,self->arg[4]));
  case 27: /* 1 1 0 1 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,self->arg[3],self->arg[4]));
  case 29: /* 1 0 1 1 1 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],self->arg[3],self->arg[4]));
  case 30: /* 0 1 1 1 1 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval1(Functor5)") );
  }
endmethod

defmethod(OBJ, geval2, Functor5, (OBJ)arg1, (OBJ)arg2)
  switch(self->arity) {
  case  7: /* 1 1 1 0 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],self->arg[2],arg1        ,arg2        ));
  case 11: /* 1 1 0 1 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,self->arg[3],arg2        ));
  case 13: /* 1 0 1 1 0 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],self->arg[3],arg2        ));
  case 14: /* 0 1 1 1 0 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],self->arg[3],arg2        ));
  case 19: /* 1 1 0 0 1 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,arg2        ,self->arg[4]));
  case 21: /* 1 0 1 0 1 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],arg2        ,self->arg[4]));
  case 22: /* 0 1 1 0 1 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],arg2        ,self->arg[4]));
  case 25: /* 1 0 0 1 1 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,self->arg[3],self->arg[4]));
  case 26: /* 0 1 0 1 1 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,self->arg[3],self->arg[4]));
  case 28: /* 0 0 1 1 1 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval2(Functor5)") );
  }
endmethod

defmethod(OBJ, geval3, Functor5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  switch(self->arity) {
  case  3: /* 1 1 0 0 0 */
    retmethod(self->fct(self->arg[0],self->arg[1],arg1        ,arg2        ,arg3        ));
  case  5: /* 1 0 1 0 0 */
    retmethod(self->fct(self->arg[0],arg1        ,self->arg[2],arg2        ,arg3        ));
  case  6: /* 0 1 1 0 0 */
    retmethod(self->fct(arg1        ,self->arg[1],self->arg[2],arg2        ,arg3        ));
  case  9: /* 1 0 0 1 0 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,self->arg[3],arg3        ));
  case 10: /* 0 1 0 1 0 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,self->arg[3],arg3        ));
  case 12: /* 0 0 1 1 0 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],self->arg[3],arg3        ));
  case 17: /* 1 0 0 0 1 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,arg3        ,self->arg[4]));
  case 18: /* 0 1 0 0 1 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,arg3        ,self->arg[4]));
  case 20: /* 0 0 1 0 1 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],arg3        ,self->arg[4]));
  case 24: /* 0 0 0 1 1 */
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,self->arg[3],self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval3(Functor5)") );
  }
endmethod

defmethod(OBJ, geval4, Functor5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4)
  switch(self->arity) {
  case  1: /* 1 0 0 0 0 */
    retmethod(self->fct(self->arg[0],arg1        ,arg2        ,arg3        ,arg4        ));
  case  2: /* 0 1 0 0 0 */
    retmethod(self->fct(arg1        ,self->arg[1],arg2        ,arg3        ,arg4        ));
  case  4: /* 0 0 1 0 0 */
    retmethod(self->fct(arg1        ,arg2        ,self->arg[2],arg3        ,arg4        ));
  case  8: /* 0 0 0 1 0 */
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,self->arg[3],arg4        ));
  case 16: /* 0 0 0 0 1 */
    retmethod(self->fct(arg1        ,arg2        ,arg3        ,arg4        ,self->arg[4]));
  default:
    THROW( gnewWithStr(ExBadArity, "geval4(Functor5)") );
  }
endmethod

defmethod(OBJ, geval5, Functor5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4, (OBJ)arg5)
  switch(self->arity) {
  case 0: /* 0 0 0 0 0 */
    retmethod(self->fct(arg1,arg2,arg3,arg4,arg5));
  default:
    THROW( gnewWithStr(ExBadArity, "geval5(Functor5)") );
  }
endmethod

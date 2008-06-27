/*
 o---------------------------------------------------------------------o
 |
 | COS Tuple
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
 | $Id: Tuple.c,v 1.1 2008/06/27 16:17:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Tuple.h>
#include <cos/gen/object.h>

makclass(Tuple ,Object);
makclass(Tuple2,Tuple);
makclass(Tuple3,Tuple);
makclass(Tuple4,Tuple);
makclass(Tuple5,Tuple);
makclass(Tuple6,Tuple);
makclass(Tuple7,Tuple);
makclass(Tuple8,Tuple);
makclass(Tuple9,Tuple);

// ----- constructors

defmethod(OBJ, ginitWith, Tuple2, Tuple2)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple3, Tuple3)

  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  retmethod(_1);

endmethod

defmethod(OBJ, ginitWith, Tuple4, Tuple4)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  self1->obj[3] = self2->obj[3] ? gretain(self2->obj[3]) : NIL;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple5, Tuple5)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  self1->obj[3] = self2->obj[3] ? gretain(self2->obj[3]) : NIL;
  self1->obj[4] = self2->obj[4] ? gretain(self2->obj[4]) : NIL;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple6, Tuple6)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  self1->obj[3] = self2->obj[3] ? gretain(self2->obj[3]) : NIL;
  self1->obj[4] = self2->obj[4] ? gretain(self2->obj[4]) : NIL;
  self1->obj[5] = self2->obj[5] ? gretain(self2->obj[5]) : NIL;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple7, Tuple7)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  self1->obj[3] = self2->obj[3] ? gretain(self2->obj[3]) : NIL;
  self1->obj[4] = self2->obj[4] ? gretain(self2->obj[4]) : NIL;
  self1->obj[5] = self2->obj[5] ? gretain(self2->obj[5]) : NIL;
  self1->obj[6] = self2->obj[6] ? gretain(self2->obj[6]) : NIL;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple8, Tuple8)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  self1->obj[3] = self2->obj[3] ? gretain(self2->obj[3]) : NIL;
  self1->obj[4] = self2->obj[4] ? gretain(self2->obj[4]) : NIL;
  self1->obj[5] = self2->obj[5] ? gretain(self2->obj[5]) : NIL;
  self1->obj[6] = self2->obj[6] ? gretain(self2->obj[6]) : NIL;
  self1->obj[7] = self2->obj[7] ? gretain(self2->obj[7]) : NIL;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple9, Tuple9)
  self1->obj[0] = self2->obj[0] ? gretain(self2->obj[0]) : NIL;
  self1->obj[1] = self2->obj[1] ? gretain(self2->obj[1]) : NIL;
  self1->obj[2] = self2->obj[2] ? gretain(self2->obj[2]) : NIL;
  self1->obj[3] = self2->obj[3] ? gretain(self2->obj[3]) : NIL;
  self1->obj[4] = self2->obj[4] ? gretain(self2->obj[4]) : NIL;
  self1->obj[5] = self2->obj[5] ? gretain(self2->obj[5]) : NIL;
  self1->obj[6] = self2->obj[6] ? gretain(self2->obj[6]) : NIL;
  self1->obj[7] = self2->obj[7] ? gretain(self2->obj[7]) : NIL;
  self1->obj[8] = self2->obj[8] ? gretain(self2->obj[8]) : NIL;
  retmethod(_1);
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, Tuple2)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple3)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple4)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  if (self1->obj[3]) grelease(self1->obj[3]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple5)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  if (self1->obj[3]) grelease(self1->obj[3]);
  if (self1->obj[4]) grelease(self1->obj[4]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple6)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  if (self1->obj[3]) grelease(self1->obj[3]);
  if (self1->obj[4]) grelease(self1->obj[4]);
  if (self1->obj[5]) grelease(self1->obj[5]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple7)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  if (self1->obj[3]) grelease(self1->obj[3]);
  if (self1->obj[4]) grelease(self1->obj[4]);
  if (self1->obj[5]) grelease(self1->obj[5]);
  if (self1->obj[6]) grelease(self1->obj[6]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple8)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  if (self1->obj[3]) grelease(self1->obj[3]);
  if (self1->obj[4]) grelease(self1->obj[4]);
  if (self1->obj[5]) grelease(self1->obj[5]);
  if (self1->obj[6]) grelease(self1->obj[6]);
  if (self1->obj[7]) grelease(self1->obj[7]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple9)
  if (self1->obj[0]) grelease(self1->obj[0]);
  if (self1->obj[1]) grelease(self1->obj[1]);
  if (self1->obj[2]) grelease(self1->obj[2]);
  if (self1->obj[3]) grelease(self1->obj[3]);
  if (self1->obj[4]) grelease(self1->obj[4]);
  if (self1->obj[5]) grelease(self1->obj[5]);
  if (self1->obj[6]) grelease(self1->obj[6]);
  if (self1->obj[7]) grelease(self1->obj[7]);
  if (self1->obj[8]) grelease(self1->obj[8]);
  retmethod(_1);
endmethod

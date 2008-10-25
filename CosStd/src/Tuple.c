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
 | $Id: Tuple.c,v 1.1 2008/10/25 13:12:59 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Tuple.h>
#include <cos/gen/object.h>

makclass(Tuple);
makclass(Tuple1,Tuple);
makclass(Tuple2,Tuple);
makclass(Tuple3,Tuple);
makclass(Tuple4,Tuple);
makclass(Tuple5,Tuple);
makclass(Tuple6,Tuple);
makclass(Tuple7,Tuple);
makclass(Tuple8,Tuple);
makclass(Tuple9,Tuple);

// ----- constructors

defmethod(OBJ, ginitWith, Tuple1, Tuple1)
  self->obj = gretain(self2->obj);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple2, Tuple2)
  self->obj[0] = gretain(self2->obj[0]);
  self->obj[1] = gretain(self2->obj[1]);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple3, Tuple3)
  for (int i = 0; i < 3; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple4, Tuple4)
  for (int i = 0; i < 4; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple5, Tuple5)
  for (int i = 0; i < 5; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple6, Tuple6)
  for (int i = 0; i < 6; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple7, Tuple7)
  for (int i = 0; i < 7; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple8, Tuple8)
  for (int i = 0; i < 8; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Tuple9, Tuple9)
  for (int i = 0; i < 9; i++)
    self->obj[i] = gretain(self2->obj[i]);

  retmethod(_1);
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, Tuple1)
  grelease(self->obj);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple2)
  grelease(self->obj[0]);
  grelease(self->obj[1]);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple3)
  for (int i = 0; i < 3; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple4)
  for (int i = 0; i < 4; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple5)
  for (int i = 0; i < 5; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple6)
  for (int i = 0; i < 6; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple7)
  for (int i = 0; i < 7; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple8)
  for (int i = 0; i < 8; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Tuple9)
  for (int i = 0; i < 9; i++)
    grelease(self->obj[i]);

  retmethod(_1);
endmethod


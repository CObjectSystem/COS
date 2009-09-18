/*
 o---------------------------------------------------------------------o
 |
 | COS Number
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
 | $Id: Number_io.c,v 1.1 2009/09/18 16:42:30 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/File.h>

#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

// ----- get

defmethod(OBJ, gget, OpenFile, Char)
  retmethod((self2->Int.value = getc(self->fd)) == EOF ? False : True);
endmethod

defmethod(OBJ, gget, OpenFile, Short)
  retmethod(fscanf(self->fd, "%d", &self2->Int.value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, OpenFile, Int)
  retmethod(fscanf(self->fd, "%d", &self2->value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, OpenFile, Float)
  retmethod(fscanf(self->fd, "%lf", &self2->value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, OpenFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fscanf(self->fd, "(%lf,%lf)", re, im) != 2 ? False : True);
endmethod

// ----- put

defmethod(OBJ, gput, OpenFile, Char)
  retmethod(putc(self2->Int.value, self->fd) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OpenFile, Short)
  retmethod(fprintf(self->fd, "%d", self2->Int.value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OpenFile, Int)
  retmethod(fprintf(self->fd, "%d", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OpenFile, Float)
  retmethod(fprintf(self->fd, "%g", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OpenFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fprintf(self->fd, "(%g,%g)", *re, *im) == EOF ? False : True);
endmethod

// ----- putLn

defmethod(OBJ, gputLn, OpenFile, Char)
  retmethod(putc(self2->Int.value, self->fd) == EOF ? False : True);
endmethod

defmethod(OBJ, gputLn, OpenFile, Short)
  retmethod(fprintf(self->fd, "%d\n", self2->Int.value) == EOF ? False : True);
endmethod

defmethod(OBJ, gputLn, OpenFile, Int)
  retmethod(fprintf(self->fd, "%d\n", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gputLn, OpenFile, Float)
  retmethod(fprintf(self->fd, "%g\n", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gputLn, OpenFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fprintf(self->fd, "(%g,%g)\n", *re, *im) == EOF ? False : True);
endmethod


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
 | $Id: Number_io.c,v 1.2 2009/09/21 07:55:06 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/File.h>

#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

// ----- get

defmethod(OBJ, gget, InFile, Char)
  retmethod((self2->Int.value = getc(self->OpenFile.fd)) == EOF ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Short)
  retmethod(fscanf(self->OpenFile.fd, "%d", &self2->Int.value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Int)
  retmethod(fscanf(self->OpenFile.fd, "%d", &self2->value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Long)
  long long val;
  int res = fscanf(self->OpenFile.fd, "%lld", &val) != 1;
  self2->value = val;
  retmethod(res ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Float)
  retmethod(fscanf(self->OpenFile.fd, "%lf", &self2->value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fscanf(self->OpenFile.fd, "(%lf,%lf)", re, im) != 2 ? False : True);
endmethod

// ----- put

defmethod(OBJ, gput, OutFile, Char)
  retmethod(putc(self2->Int.value, self->OpenFile.fd) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Short)
  retmethod(fprintf(self->OpenFile.fd, "%d", self2->Int.value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Int)
  retmethod(fprintf(self->OpenFile.fd, "%d", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Long)
  long long val = self2->value;
  retmethod(fprintf(self->OpenFile.fd, "%lld", val) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Float)
  retmethod(fprintf(self->OpenFile.fd, "%g", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fprintf(self->OpenFile.fd, "(%g,%g)", *re, *im) == EOF ? False : True);
endmethod


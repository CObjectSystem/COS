/*
 o---------------------------------------------------------------------o
 |
 | COS String - strings character processing
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
 | $Id: String_chr.c,v 1.1 2009/09/18 16:42:30 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/string.h>

#include <ctype.h>

// ----- predicate

defmethod(OBJ, gisAlnum, Char)
  retmethod(isalnum(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisAlpha, Char)
  retmethod(isalpha(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisBlank, Char)
  retmethod(isblank(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisCntrl, Char)
  retmethod(iscntrl(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisDigit, Char)
  retmethod(isdigit(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisGraph, Char)
  retmethod(isgraph(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisLower, Char)
  retmethod(islower(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisPrint, Char)
  retmethod(isprint(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisPunct, Char)
  retmethod(ispunct(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisSpace, Char)
  retmethod(isspace(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisUpper, Char)
  retmethod(isupper(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisXDigit, Char)
  retmethod(isxdigit(self->Int.value) ? True : False);
endmethod

// ----- conversion (in place)

defmethod(OBJ, gtoLower, Char)
  self->Int.value = tolower(self->Int.value);
  retmethod(_1);
endmethod

defmethod(OBJ, gtoUpper, Char)
  self->Int.value = toupper(self->Int.value);
  retmethod(_1);
endmethod


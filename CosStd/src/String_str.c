/*
 o---------------------------------------------------------------------o
 |
 | COS String - strings on string streams
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
 | $Id: String_str.c,v 1.1 2009/09/26 09:02:41 ldeniau Exp $
 |
*/

#include <cos/String.h>

// #include <cos/gen/container.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

defmethod(OBJ, gget, String, pmString)
  retmethod(_1);
endmethod

#if 0
defmethod(OBJ, gget, String, StringDyn)
  gappend(_2,_1);
  retmethod(True);
endmethod

defmethod(OBJ, gget, StringDyn, String)
  U32 size = self2->size;

  if (!size) retmethod(True);

  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->size >= size) {
    memcpy(self2->value, str->value, size * sizeof *self2->value);
    str->value += size, str->size -= size;
    retmethod(True);
  }
  retmethod(False);
endmethod
#endif


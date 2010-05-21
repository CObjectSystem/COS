/*
 o---------------------------------------------------------------------o
 |
 | COS example01 -- String class
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
 | $Id: String.c,v 1.4 2010/05/21 14:22:07 ldeniau Exp $
 |
*/

#include "String.h"
#include "generics.h"

#include <string.h>
#include <stdlib.h>

makclass(String);

static char* str_dup(STR str)
{
  size_t len = strlen(str);
  char *s = malloc(len+1);
  if (s) memcpy(s, str, len+1);
  return s;
}

defmethod(OBJ, ginitWithStr, String, (STR)str)
  useclass(ExBadAlloc);

  self->str = str_dup(str);
  if (!self->str)
    THROW(ExBadAlloc);
  
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, String)
  free(self->str), self->str = 0;
  retmethod(_1);
endmethod


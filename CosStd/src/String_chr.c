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
 | $Id: String_chr.c,v 1.2 2009/09/25 08:58:59 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Number.h>
#include <cos/Slice.h>

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

// ----- trim (remove white spaces)

useclass(View);

defmethod(OBJ, gtrim, String)
  U32 size = self->size;

  if (!size) retmethod(_1);
  
  U8* val  = self->value;
  U8* end  = val + size-1;

  while (val != end && isspace(*val)) ++val;
  while (val != end && isspace(*end)) --end;

  retmethod( gautoDelete(gnewWith2(View, _1, aSlice(val-self->value,end-val+1))) );
endmethod

defmethod(OBJ, gtrim, StringDyn)
  struct String *str = &self->StringFix.String;
  U32 size = str->size;

  if (!size) retmethod(_1);
  
  U8* val  = str->value;
  U8* end  = val + size-1;

  while (val != end && isspace(*val)) ++val;
  while (val != end && isspace(*end)) --end;

  str->value = val;
  str->size  = end-val+1;

  retmethod(_1);
endmethod




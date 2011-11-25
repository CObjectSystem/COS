/**
 * C Object System
 * COS String - strings character processing
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

// ----- strip (remove white spaces)

useclass(View);

defmethod(OBJ, gstrip, String)
  U32 size = self->size;

  if (!size) retmethod(_1);
  
  U8* val  = self->value;
  U8* end  = val + size;

  while (val != end && isspace(* val   )) val++;
  while (val != end && isspace(*(end-1))) end--;

  retmethod( gautoRelease(gnewWith2(View, _1, aSlice(val-self->value,end-val))) );
endmethod

defmethod(OBJ, gstrip, StringDyn)
  struct String *str = &self->StringFix.String;
  U32 size = str->size;

  if (!size) retmethod(_1);
  
  U8* val  = str->value;
  U8* end  = val + size;

  while (val != end && isspace(* val   )) val++;
  while (val != end && isspace(*(end-1))) end--;

  str->value = val;
  str->size  = end-val;

  retmethod(_1);
endmethod




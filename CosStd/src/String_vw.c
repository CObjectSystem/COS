/*
 o---------------------------------------------------------------------o
 |
 | COS String - String view
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
 | $Id: String_vw.c,v 1.4 2009/08/21 12:10:00 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/object.h>

// -----

makclass(StringView, String);

// -----

useclass(ExBadAlloc);
useclass(String, StringView);

// ----- initializer

struct String*
StringView_init(struct StringView *strv, struct String *str, struct Slice *slc)
{
  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);
  U32 size  = Slice_size (slc);

  test_assert( first < str->size &&
               last  < str->size, "slice out of range" );

  struct String* svw = &strv->String;

  svw->value   = first + str->value;
  svw->size    = size;
  strv->string = str;

  return svw;
}

// ----- constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, String, Slice);
defmethod(OBJ,  ginitWith2          , mView, String, Slice) // string view
  retmethod( ginitWith2(galloc(StringView),_2,_3) );
endmethod

defmethod(OBJ, ginitWith2, StringView, String, Slice)
  test_assert( !cos_object_isKindOf(_2, classref(StringDyn)),
               "string views accept only non-Dyn strings" );

  StringView_init(self, self2, self3);

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, StringView)
  if (self->string)              // take care of protection cases
    grelease( (OBJ)self->string );
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, StringView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf((OBJ)self->string, classref(String)),
               "string view points to something not a string", func, file, line);

  test_assert( !cos_object_isKindOf((OBJ)self->string, classref(StringDyn)),
               "string view points to a dynamic string", func, file, line);

  struct String *str = STATIC_CAST(struct String*, self->string);

  I32 start = (str->value - self->String.value);
  U32 size  = self->String.size;

  struct Slice *slc = atSlice(start, size, 1);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < self->string->size && last < self->string->size,
               "string view is out of range", func, file, line);

  next_method(self, func, file, line);
endmethod


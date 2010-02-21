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
 | $Id: String_vw.c,v 1.9 2010/02/21 00:46:24 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

makclass(StringView, String);

// -----

useclass(ExBadAlloc);
useclass(String, StringView);

// ----- getters

/*
defmethod(STR, gstr, StringView)
  gstr((OBJ)self->ref);
  retmethod((STR)self->String.value);
endmethod
*/

// ----- initializer

struct String*
StringView_init(struct StringView *strv, struct String *str, struct Slice *slc)
{
  test_assert( Slice_first(slc) < str->size &&
               Slice_last (slc) < str->size, "slice out of range" );

  struct String* svw = &strv->String;

  svw->value = Slice_start(slc) + str->value;
  svw->size  = Slice_size (slc);
  strv->ref  = str;

  return svw;
}

// ----- constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, String, Slice);
defmethod(OBJ,  ginitWith2          , mView, String, Slice) // string view
  retmethod( ginitWith2(galloc(StringView),_2,_3) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mView, String, Range);
defmethod(OBJ,  ginitWith2          , mView, String, Range) // string view
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod( ginitWith2(galloc(StringView),_2,(OBJ)&slice) );
endmethod

defmethod(OBJ, ginitWith2, StringView, String, Slice)
  PRT(_1);
  self->ref = 0;
  
  test_assert( !cos_object_isKindOf(_2, classref(StringDyn)),
               "string views accept only non-dynamic string" );

  OBJ ref = gretain(_2); PRT(ref);
  
  StringView_init(self, STATIC_CAST(struct String*, ref), self3);

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, StringView)
  if (self->ref)              // take care of protection cases
    grelease( (OBJ)self->ref );
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, StringView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf((OBJ)self->ref, classref(String)),
               "string view points to something not a string", func, file, line);

  test_assert( !cos_object_isKindOf((OBJ)self->ref, classref(StringDyn)),
               "string view points to a dynamic string", func, file, line);

  struct String *str = self->ref;

  I32 start = self->String.value - str->value;
  U32 size  = self->String.size;

  struct Slice *slc = atSlice(start, size);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < self->ref->size &&
               last  < self->ref->size, "string view is out of range", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod


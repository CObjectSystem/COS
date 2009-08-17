/*
 o---------------------------------------------------------------------o
 |
 | COS String - Dynamic string
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
 | $Id: String_dyn.c,v 1.1 2009/08/17 12:57:43 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Number.h>

#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdlib.h>
#include <string.h>

// -----

makclass(StringFix, String);
makclass(StringDyn, StringFix);

// -----

#define STRING_GROWTH_RATE 1.618034 // golden ratio

STATIC_ASSERT(string_growth_rate_is_too_small, STRING_GROWTH_RATE >= 1.5);

useclass(String, StringDyn, ExBadAlloc);

// ----- constructors

defalias (OBJ, (ginit)gnew, pmString);
defmethod(OBJ,  ginit     , pmString) // Dyn string
  retmethod( ginit(galloc(StringDyn)) );
endmethod

defmethod(OBJ, ginit, StringDyn)
  retmethod( ginitWith(_1,aInt(0)) );
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmString, Int);
defmethod(OBJ,  ginitWith         , pmString, Int) // Dyn string with capacity
  retmethod( ginitWith(galloc(StringDyn),_2) );
endmethod

defmethod(OBJ, ginitWith, StringDyn, Int)
  enum { MIN_SIZE = 1024 };
  
  I32 capacity = self2->value;

  test_assert(capacity >= 0, "negative string capacity");
  if (capacity < MIN_SIZE) capacity = MIN_SIZE;

  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  str->value = malloc(capacity * sizeof *str->value);
  if (!str->value) THROW(ExBadAlloc);

  str->size      = 0;
  strf->_value   = str->value;
  strf->_cls     = 0;
  strf->capacity = capacity;

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, StringFix)
  if (self->_value)            // take care of protection cases
    free(self->_value);
  next_method(self);
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, StringDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->StringFix.capacity >= self->StringFix.String.size,
               "dynamic string has capacity < size", func, file, line);

  next_method(self, func, file, line);
endmethod

// ----- memory management

defmethod(void, genlarge, StringDyn, Float)
  F64 factor   = self2->value;
  U32 capacity = self->StringFix.capacity;

  if (factor > 1.0)
    genlarge(_1, aInt(capacity * (factor-1)));
  else if (factor < 1.0)
    genlarge(_1, aInt(capacity * (1-factor)));
endmethod

defmethod(void, genlarge, StringDyn, Int)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;
  U32     capacity = strf->capacity;
  ptrdiff_t offset = str->value - strf->_value;
  BOOL       front = self2->value < 0;
  I32        addon = front ? -self2->value : self2->value;
  
  if (addon > 0) {
    U32 capacity = strf->capacity + addon;
    U8* _value = realloc(strf->_value, capacity*sizeof *strf->_value);
    if (!_value) THROW(ExBadAlloc);

    str ->value    = _value + offset;
    strf->_value   = _value;
    strf->capacity = capacity;
  }
  if (front) { // move data to book the new space front
    str->value = strf->_value + (strf->capacity - capacity);
    memmove(str->value, strf->_value + offset, str->size*sizeof *str->value);
  }
endmethod

// ----- fix/unfix

defmethod(void, gfix, StringDyn)
  PRE
    test_assert(!self->StringFix._cls, "corrupted dynamic string");

  BODY
    self->StringFix._cls = cos_object_id(_1);
    self->StringFix.String.ValueSequence.Sequence.Container.Object.id = classref(StringFix)->Behavior.id;
endmethod

defmethod(void, gunfix, StringFix)
  PRE
    test_assert(self->_cls, "corrupted dynamic string (already unfixed?)");

  BODY
    self->String.ValueSequence.Sequence.Container.Object.id = self->_cls;
    self->_cls = 0;
endmethod

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, StringDyn)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  // move data to storage base
  if (str->value != strf->_value)
    str->value = memmove(strf->_value, str->value, str->size*sizeof *strf->_value);

  // shrink storage
  if (str->size != strf->capacity) {
    U8* _value = realloc(strf->_value, str->size*sizeof *strf->_value);
    if (!_value) THROW(ExBadAlloc);

    str ->value    = _value;
    strf->_value   = _value;
    strf->capacity = str->size;
  }

  test_assert( cos_object_changeClass(_1, classref(StringFix)),
               "unable to change dynamic string to fixed size string" );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, StringDyn)
  self->StringFix.String.value = self->StringFix._value;
  self->StringFix.String.size  = 0;
endmethod

// ----- getters, setters

defalias (void, (gput)gappend, StringDyn, Char);
defalias (void, (gput)gpush  , StringDyn, Char);
defmethod(void,  gput        , StringDyn, Char)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->size == strf->capacity)
    genlarge(_1, aFloat(STRING_GROWTH_RATE));
    
  str->value[str->size] = self2->Int.value;
  str->size++;
endmethod

defalias (void, (gput)gappend, StringDyn, Object);
defalias (void, (gput)gpush  , StringDyn, Object);
defmethod(void,  gput        , StringDyn, Object)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->size == strf->capacity)
    genlarge(_1, aFloat(STRING_GROWTH_RATE));
    
  str->value[str->size] = gchr(_2);
  str->size++;
endmethod

defalias (void, (gdrop)gpop, StringDyn);
defmethod(void,  gdrop     , StringDyn)
  struct String *str = &self->StringFix.String;

  if (str->size) --str->size;
endmethod

// ----- prepend, append

defmethod(void, gprepend, StringDyn, Object)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value == strf->_value)
    genlarge(_1, aFloat(-STRING_GROWTH_RATE));

  str->value[-1] = gchr(_2);
  str->value--;
  str->size++;
endmethod

defmethod(void, gprepend, StringDyn, Char)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value == strf->_value)
    genlarge(_1, aFloat(-STRING_GROWTH_RATE));

  str->value[-1] = self2->Int.value;
  str->value--;
  str->size++;
endmethod

defmethod(void, gprepend, StringDyn, String)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value - strf->_value < self2->size) {
    F64 factor = 1.0;
    U32 capacity = strf->capacity;

    do
      factor *= STRING_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    genlarge(_1, aFloat(-factor));
  }

  str->value -= self2->size;
  str->size  += self2->size;
  memcpy(str->value,self2->value,self2->size);
endmethod

defmethod(void, gappend, StringDyn, String)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value - strf->_value < self2->size) {
    F64 factor = 1.0;
    U32 capacity = strf->capacity;

    do
      factor *= STRING_GROWTH_RATE;
    while (capacity*(factor - 1.0) < self2->size);

    genlarge(_1, aFloat(factor));
  }

  memcpy(str->value+str->size,self2->value,self2->size);
  str->size += self2->size;
endmethod


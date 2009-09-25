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
 | $Id: String_dyn.c,v 1.5 2009/09/25 08:58:59 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Number.h>
#include <cos/Range.h>

#include <cos/gen/container.h>
#include <cos/gen/message.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/string.h>
#include <cos/gen/value.h>

#include <stdlib.h>
#include <string.h>

// -----

makclass(StringFix, String);
makclass(StringDyn, StringFix);

// -----

useclass(String, StringDyn, ExBadAlloc);

// -----

#ifndef STRING_GROWTH_RATE
#define STRING_GROWTH_RATE SEQUENCE_GROWTH_RATE
#endif

#ifndef STRING_MINSIZE
#define STRING_MINSIZE 1024
#endif

STATIC_ASSERT(string_growth_rate_is_too_small , STRING_GROWTH_RATE >= 1.5);
STATIC_ASSERT(string_minimun_size_is_too_small, STRING_MINSIZE     >= 256);

// ----- constructors

defalias (OBJ, (ginit)gnew, pmString);
defmethod(OBJ,  ginit     , pmString) // Dynamic string
  retmethod(ginitWith(galloc(StringDyn),aInt(0)));
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmString, Int);
defmethod(OBJ,  ginitWith         , pmString, Int) // Dynamic string with capacity
  retmethod(ginitWith(galloc(StringDyn),_2));
endmethod

defmethod(OBJ, ginitWith, StringDyn, Int)
  PRE POST BODY
    PRT(_1);
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    test_assert(self2->value >= 0, "negative string capacity");

    if (self2->value > 0) {
      strf->_value = malloc(self2->value * sizeof *str->value);
      if (!strf->_value) THROW(ExBadAlloc);
    } else
      strf->_value = 0;

    str->size      = 0;
    str->value     = strf->_value;
    strf->capacity = self2->value;

    UNPRT(_1);
    retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, StringFix)
  next_method(self);

  if (self->_value)            // take care of protection cases
    free(self->_value);

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, StringDyn, (STR)func, (STR)file, (int)line)
  test_assert( self->StringFix.capacity >= self->StringFix.String.size,
               "dynamic string has capacity < size", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod

// ----- memory management

static I32
extra_size(U32 old_capacity, U32 size)
{
  U32 new_capacity = old_capacity < STRING_MINSIZE ? STRING_MINSIZE : old_capacity;
  
  while (new_capacity - old_capacity < size)
    new_capacity *= STRING_GROWTH_RATE;

  I32 extra = new_capacity - old_capacity;
  
  test_assert(extra > 0 && (U32)extra > size, "string size overflow");

  return extra;
}

defmethod(void, genlarge, StringDyn, Float) // negative factor means enlarge front
  PRE
    test_assert(self2->value < -1 ||
                self2->value >  1, "invalid growing factor");
  POST
  BODY
    F64 factor   = self2->value;
    U32 capacity = self->StringFix.capacity;

    if (factor > 1)
      genlarge(_1, aInt(capacity * (factor-1)));
    else if (factor < 1)
      genlarge(_1, aInt(capacity * (factor+1)));
endmethod

defmethod(void, genlarge, StringDyn, Int) // negative size means enlarge front
  PRE
    test_assert(self2->value, "invalid growing size");
  POST
  BODY
    struct StringFix* strf = &self->StringFix;
    struct String*    str  = &strf->String;
    U32           capacity = strf->capacity;
    ptrdiff_t       offset = str->value - strf->_value;
    BOOL             front = self2->value < 0;
    I32               size = front ? -self2->value : self2->value;

    capacity += size = extra_size(capacity, size);
    
    U8* _value = realloc(strf->_value, capacity*sizeof *strf->_value);
    if (!_value) THROW(ExBadAlloc);

    str -> value   = _value + offset;
    strf->_value   = _value;
    strf->capacity = capacity;

    if (front) // move data to book the new space front
      str->value = memmove(str->value+size, str->value, str->size*sizeof *str->value);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, StringDyn)
  BOOL ch_cls;

  PRE
  POST
    test_assert( ch_cls, "unable to change StringDyn to StringFix" );
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    // move data to storage base
    if (str->value != strf->_value)
      str->value = memmove(strf->_value, str->value, str->size*sizeof *strf->_value);

    // shrink storage
    if (str->size != strf->capacity) {
      U8* _value = realloc(strf->_value, str->size*sizeof *strf->_value);
      if (!_value) THROW(ExBadAlloc);

      str -> value   = _value;
      strf->_value   = _value;
      strf->capacity = str->size;
    }

    ch_cls = cos_object_changeClass(_1, classref(StringFix));

    retmethod(_1);
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, StringDyn)
  self->StringFix.String.size  = 0;
  self->StringFix.String.value = self->StringFix._value;
endmethod

// ----- dropFirst, dropLast, drop

defmethod(void, gdropFirst, StringDyn)
  struct String *str = &self->StringFix.String;

  if (str->size) {
    str->size--;
    str->value++;
  }
endmethod

defmethod(void, gdropLast, StringDyn)
  struct String *str = &self->StringFix.String;

  if (str->size)
    str->size--;
endmethod

defmethod(void, gchop, StringDyn, Char)
  struct String *str = &self->StringFix.String;

  if (str->size && str->value[str->size-1] == (U32)self2->Int.value)
    str->size--;
endmethod

defmethod(void, gdrop, StringDyn, Int)
  struct String *str = &self->StringFix.String;
  BOOL front = self2->value < 0;
  U32 n = front ? -self2->value : self2->value;

  if (n > str->size)
    n = str->size;

  str->size -= n;
  if (front)
    str->value += n;
endmethod

// ----- prepend, append char

defmethod(void, gprepend, StringDyn, Char)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value == strf->_value)
      genlarge(_1, aInt(-1));

    *--str->value = self2->Int.value, str->size++;
endmethod

defmethod(void, gappend, StringDyn, Char)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value + str->size == strf->_value + strf->capacity)
      genlarge(_1, aInt(1));

    str->value[str->size++] = self2->Int.value;
endmethod

// ----- prepend, append object

defmethod(void, gprepend, StringDyn, Object)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value == strf->_value)
      genlarge(_1, aInt(-1));

    str->value[-1] = (U32)gchr(_2), str->value--, str->size++;
endmethod

defmethod(void, gappend, StringDyn, Object)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value + str->size == strf->_value + strf->capacity)
      genlarge(_1, aInt(1));

    str->value[str->size] = (U32)gchr(_2), str->size++;
endmethod

// ----- prepend, append string

defmethod(void, gprepend, StringDyn, String)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value < strf->_value + self2->size)
      genlarge(_1, aInt(-self2->size));

    str->value -= self2->size;
    str->size  += self2->size;
    memcpy(str->value, self2->value, self2->size*sizeof *str->value);
endmethod

defmethod(void, gappend, StringDyn, String)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value + str->size + self2->size > strf->_value + strf->capacity)
      genlarge(_1, aInt(self2->size));

    memcpy(str->value+str->size, self2->value, self2->size*sizeof *str->value);
    str->size += self2->size;
endmethod

// --- insertAt

defmethod(void, ginsertAt, StringDyn, Int, Object)
  U32 i;

  PRE
    i = Range_index(self2->value, self->StringFix.String.size);
    test_assert( i <= self->StringFix.String.size, "index out of range" );
 
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->size == strf->capacity)
      genlarge(_1, aInt(1));

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, str->size);
 
    U8* dst = str->value+i;

    memmove(dst+1, dst, (str->size-i)*sizeof *str->value);
    *dst = (U32)gchr(_3);
    str->size++;
endmethod

defmethod(void, ginsertAt, StringDyn, Int, String)
  U32 i;

  PRE
    i = Range_index(self2->value, self->StringFix.String.size);
    test_assert( i <= self->StringFix.String.size, "index out of range" );
 
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->size == strf->capacity)
      genlarge(_1, aInt(self3->size));

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, str->size);
 
    U8* dst = str->value+i;

    memmove(dst+self3->size, dst, (str->size-i)*sizeof *dst);
    memcpy(dst, self3->value, self3->size*sizeof *dst);
    str->size += self3->size;
endmethod

// --- removeAt

defmethod(void, gremoveAt, StringDyn, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->StringFix.String.size);
    test_assert( i <= self->StringFix.String.size, "index out of range" );
 
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->StringFix.String.size);
 
    U8* dst  = str->value+i;

    str->size--;
    memmove(dst, dst+1, (str->size-i)*sizeof *dst);
endmethod

defmethod(void, gremoveAt, StringDyn, Slice)
  PRE
    test_assert( Slice_first(self2) <= self->StringFix.String.size &&
                 Slice_last (self2) <= self->StringFix.String.size, "slice out of range" );
    test_assert( Slice_stride(self2) != 1, "slice stride not 1");
     
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    U32 size = Slice_size(self2);
    U32 i    = Slice_start(self2);
    U8* dst  = str->value+i;

    str->size -= size;
    memmove(dst, dst+size, (str->size-i)*sizeof *dst);
endmethod

defmethod(void, gremoveAt, StringDyn, Range)
  struct Range range = Range_normalize(self2,self->StringFix.String.size);
  struct Slice slice = Slice_fromRange(&range);
  
  gremoveAt(_1,(OBJ)&slice);
endmethod

// --- dequeue aliases
defalias(void, (gprepend  )gpushFront, StringDyn, Char);
defalias(void, (gappend   )gpushBack , StringDyn, Char);
defalias(void, (gprepend  )gpushFront, StringDyn, Object);
defalias(void, (gappend   )gpushBack , StringDyn, Object);
defalias(void, (gdropFirst)gpopFront , StringDyn);
defalias(void, (gdropLast )gpopBack  , StringDyn);
defalias(OBJ , (gfirst    )gfront    , String);
defalias(OBJ , (glast     )gback     , String);

// --- stack aliases
defalias(void, (gappend  )gpush, StringDyn, Char  );
defalias(void, (gappend  )gpush, StringDyn, Object);
defalias(void, (gdropLast)gpop , StringDyn);
defalias(OBJ , (glast    )gtop , String);

// ----- generic get, getLine, getData from class

// NOTE-TODO: implement type-specific io on string stream

defalias (OBJ, (gget)ggetLine, StringDyn, Class);
defalias (OBJ, (gget)ggetData, StringDyn, Class);
defmethod(OBJ,  gget         , StringDyn, Class)
  OBJ obj = gautoDelete(gnew(_2));
  
  forward_message(_1, obj);

  if (gunderstandMessage1(obj, genericref(gadjust)))
    gadjust(obj);

  retmethod(RETVAL == True ? obj : Nil);
endmethod



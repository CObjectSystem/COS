/**
 * C Object System
 * COS String - Dynamic string
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
#include <cos/Range.h>

#include <cos/gen/collection.h>
#include <cos/gen/sequence.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdlib.h>
#include <string.h>

// -----

makclass(StringFix, String);
makclass(StringDyn, StringFix);

// -----

useclass(String, StringDyn, ExBadAlloc, ExOverflow);

// ----- getter

defmethod(U32, gcapacity, StringDyn)
  retmethod(self->capacity);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, StringFix)
  next_method(self);
  
  if (self->_value) { // take care of protection cases
    free(self->_value);
    self->String.value = 0;
    self->_value        = 0;
  }
  
  retmethod(_1);
endmethod

// ----- constructors

defalias (OBJ, (ginit)gnew, pmString);
defmethod(OBJ,  ginit     , pmString) // Dynamic string
  retmethod( ginit(galloc(StringDyn)) );
endmethod

defmethod(OBJ, ginit, StringDyn)
  self->StringFix.String.size  = 0;
  self->StringFix.String.value = 0;
  self->StringFix._value       = 0;
  self->capacity               = 0;

  retmethod(_1);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmString, Int);
defmethod(OBJ,  ginitWith         , pmString, Int) // Dynamic string with capacity
  retmethod(ginitWith(galloc(StringDyn),_2));
endmethod

defmethod(OBJ, ginitWith, StringDyn, Int)
  PRT(_1);
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;
  U32           capacity = self2->value;
  size_t            size = (capacity+1) * sizeof *str->value;

  if (size/sizeof *str->value < capacity+1) {
    strf->_value = 0;
    THROW(gnewWithStr(ExOverflow, "capacity is too large"));
  }

  strf->_value = malloc(size);
  if (!strf->_value && size)
    THROW(ExBadAlloc);

  str->size      = 0;
  str->value     = strf->_value;
  self->capacity = capacity;

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, StringDyn, (STR)file, (int)line)
  ensure( self->capacity >= self->StringFix.String.size,
               "dynamic string has capacity < size", file, line);

  if (next_method_p)
    next_method(self, file, line);
endmethod

// --- dequeue aliases
defalias(OBJ, (gprepend  )gpushFront, StringDyn, Object);
defalias(OBJ, (gappend   )gpushBack , StringDyn, Object);
defalias(OBJ, (gprepend  )gpushFront, StringDyn, Char);
defalias(OBJ, (gappend   )gpushBack , StringDyn, Char);
defalias(OBJ, (gfirst    )gtopFront , String);
defalias(OBJ, (glast     )gtopBack  , String);

// --- stack aliases
defalias(OBJ, (gpushBack)gpush, StringDyn, Object);
defalias(OBJ, (gpushBack)gpush, StringDyn, Char);
defalias(OBJ, (gpopBack )gpop , StringDyn);
defalias(OBJ, (gtopBack )gtop , String);

// ----- memory management

defmethod(OBJ, genlarge, StringDyn, Int) // negative size means enlarge front
  if (self2->value) {
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;
    
    ptrdiff_t offset = str->value - strf->_value;
    BOOL       front = self2->value < 0;
    U32        extra = front ? -self2->value : self2->value;
    U32     capacity = Sequence_enlargeCapacity(self->capacity, extra);
    size_t      size = (capacity+1) * sizeof *strf->_value;

    if (size/sizeof *strf->_value < capacity+1)
      THROW(gnewWithStr(ExOverflow, "extra size is too large"));
    
    U8* _value = realloc(strf->_value, size);

    if (!_value && size)
      THROW(ExBadAlloc);

    str->value = front ? // move data to book the new space front
        memmove(_value + offset + (capacity - self->capacity),
                _value + offset, str->size * sizeof *_value) :
                _value + offset; // restore offset

    strf->_value   = _value;
    self->capacity = capacity;
  }      
  retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, StringDyn)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;
  size_t            size = (str->size+1) * sizeof *str->value;

  // move data to storage base
  if (str->value != strf->_value)
    str->value = memmove(strf->_value, str->value, size);

  // shrink storage
  if (str->size != self->capacity) {
    U8* _value = realloc(strf->_value, size);
    if (!_value && size)
      THROW(ExBadAlloc);

    str -> value   = _value;
    strf->_value   = _value;
    self->capacity = size;
  }

  BOOL ch_cls = cos_object_changeClass(_1, classref(StringFix));
  ensure( ch_cls, "unable to change from dynamic to fixed size string" );

  retmethod(_1);
endmethod

// ----- clear (size -> 0)

defmethod(OBJ, gclear, StringDyn)
  self->StringFix.String.size  = 0;
  
  retmethod(_1);
endmethod

// ----- popFront, popBack, drop

defmethod(OBJ, gpopFront, StringDyn)
  struct String *str = &self->StringFix.String;

  if (str->size--)
    ++str->value;
  
  retmethod(_1);
endmethod

defmethod(OBJ, gpopBack, StringDyn)
  struct String *str = &self->StringFix.String;

  if (str->size--)
    {}
  
  retmethod(_1);
endmethod

defmethod(OBJ, gdrop, StringDyn, Int)
  struct String *str = &self->StringFix.String;
  BOOL          back = self2->value < 0;
  U32            cnt = back ? -self2->value : self2->value+1;

  if (cnt > str->size)
    cnt = str->size;

  str->size -= cnt;
  if (!back) str->value += cnt;
  
  retmethod(_1);
endmethod

// ----- prepend, append char

defmethod(OBJ, gprepend, StringDyn, Char)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value == strf->_value)
    genlarge(_1, aInt(-1));

  *--str->value = (U32)self2->Int.value, str->size++;

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, StringDyn, Char)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value + str->size == strf->_value + self->capacity)
    genlarge(_1, aInt(1));

  str->value[str->size++] = (U32)self2->Int.value;

  retmethod(_1);
endmethod

// ----- prepend, append object

defmethod(OBJ, gprepend, StringDyn, Object)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value == strf->_value)
    genlarge(_1, aInt(-1));

  str->value[-1] = (U32)gchr(_2), str->value--, str->size++;

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, StringDyn, Object)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (str->value + str->size == strf->_value + self->capacity)
    genlarge(_1, aInt(1));

  str->value[str->size++] = (U32)gchr(_2);

  retmethod(_1);
endmethod

// ----- prepend, append string

defmethod(OBJ, gprepend, StringDyn, String)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (strf->_value > strf->_value + self2->size || self2->size > I32_MAX)
    THROW(gnewWithStr(ExOverflow, "string to prepend is too large"));

  if (str->value < strf->_value + self2->size)
    genlarge(_1, aInt(-(I32)self2->size));

  str->value -= self2->size;
  str->size  += self2->size;
  memcpy(str->value, self2->value, self2->size * sizeof *str->value);

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, StringDyn, String)
  struct StringFix *strf = &self->StringFix;
  struct String    *str  = &strf->String;

  if (strf->_value > strf->_value + self->capacity + self2->size || self2->size > I32_MAX)
    THROW(gnewWithStr(ExOverflow, "string to append is too large"));

  if (str->value + str->size + self2->size > strf->_value + self->capacity)
    genlarge(_1, aInt(self2->size));

  memcpy(str->value + str->size, self2->value, self2->size * sizeof *str->value);
  str->size += self2->size;

  retmethod(_1);
endmethod

#if 0
/* TODO: unchecked code (certainly buggy)
*/

// --- insertAt

defmethod(OBJ, ginsertAt, StringDyn, Int, Object)
  U32 i;

  PRE
    i = Range_index(self2->value, self->StringFix.String.size);
    ensure( i <= self->StringFix.String.size, "index out of range" );
 
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
  
    retmethod(_1);
endmethod

defmethod(OBJ, ginsertAt, StringDyn, Int, String)
  U32 i;

  PRE
    i = Range_index(self2->value, self->StringFix.String.size);
    ensure( i <= self->StringFix.String.size, "index out of range" );
 
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
  
    retmethod(_1);
endmethod

// --- removeAt

defmethod(OBJ, gremoveAt, StringDyn, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->StringFix.String.size);
    ensure( i <= self->StringFix.String.size, "index out of range" );
 
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->StringFix.String.size);
 
    U8* dst  = str->value+i;

    str->size--;
    memmove(dst, dst+1, (str->size-i)*sizeof *dst);
  
    retmethod(_1);
endmethod

defmethod(OBJ, gremoveAt, StringDyn, Slice)
  PRE
    ensure( Slice_first(self2) <= self->StringFix.String.size &&
                 Slice_last (self2) <= self->StringFix.String.size, "slice out of range" );
    ensure( Slice_stride(self2) != 1, "slice stride not 1");
     
  BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    U32 size = Slice_size(self2);
    U32 i    = Slice_start(self2);
    U8* dst  = str->value+i;

    str->size -= size;
    memmove(dst, dst+size, (str->size-i)*sizeof *dst);
  
    retmethod(_1);
endmethod

defmethod(OBJ, gremoveAt, StringDyn, Range)
  U32            size = self->StringFix.String.size;
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &size);
  
  gremoveAt(_1,(OBJ)slice);
  
  retmethod(_1);
endmethod

#endif


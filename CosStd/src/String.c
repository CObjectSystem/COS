/**
 * C Object System
 * COS String - basic strings
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
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Range.h>

#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/init.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

// -----

makclass(String , ValueSequence);
makclass(StringN, String);

// -----

useclass(String, ExBadAlloc, ExOverflow);

// --- getters

defmethod(U32, gsize, String)
  retmethod(self->size);
endmethod

defmethod(I8*, gchrPtr, String)
  retmethod( (I8*)self->value );
endmethod

defmethod(STR, gstr, String)
  self->value[self->size] = '\0';
  retmethod((STR)self->value);
endmethod

defmethod(OBJ, gisEmpty, String)
  retmethod(self->size ? False : True);
endmethod

defmethod(OBJ, gclass, String)
  retmethod(String);     // class cluster: hide implementation details
endmethod

// ----- allocator

struct String*
String_alloc(U32 size)
{
  useclass(StringN);

  if (size == U32_MAX)
    THROW(gnewWithStr(ExOverflow, "size is too large"));
  
  OBJ _str = gallocWithSize(StringN, size+1);

  struct StringN *strn = CAST(struct StringN*, _str);
  struct String  *str  = &strn->String;

  str->value = strn->_value;
  str->size  = 0;

  return str;
}

// ----- allocator

defmethod(OBJ, galloc, pmString) // lazy alloc
  retmethod(_1);
endmethod

// ----- destructor

// generic gdeinit from ValueSequence

// ----- constructors

defalias (OBJ, (ginitWithStr)gnewWithStr, pmString, (STR)str);
defmethod(OBJ,  ginitWithStr            , pmString, (STR)str)
  U32 size = strlen(str);
  struct String* s = String_alloc(size);

  memcpy(s->value, str, s->size = size);

  retmethod((OBJ)s);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmString, String);
defmethod(OBJ,  ginitWith         , pmString, String) // copy
  struct String* str = String_alloc(self2->size);

  memcpy(str->value, self2->value, str->size = self2->size);

  retmethod( (OBJ)str );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, Int, Object);
defmethod(OBJ,  ginitWith2          , pmString, Int, Object) // element
PRE
  ensure(self2->value >= 0, "negative string size");

BODY
  I32 val = gchr(_3);
  struct String* str = String_alloc(self2->value);

  memset(str->value, val, str->size = self2->value);

  retmethod( (OBJ)str );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, Int, Functor);
defmethod(OBJ,  ginitWith2          , pmString, Int, Functor) // generator
PRE
  ensure(self2->value >= 0, "negative string size");

BODY
  U32 size = self2->value;
  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U32 *dst_n = &str->size;
  U8*  dst   = str->value;
  U8*  end   = dst + size;

  while (dst != end)
    *dst++ = (U32)gchr(geval(_3)), ++*dst_n;

  UNPRT(_str);
  retmethod(_str);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, String, Slice);
defmethod(OBJ,  ginitWith2          , pmString, String, Slice) // sub string
PRE
  ensure( Slice_first(self3) < self2->size &&
               Slice_last (self3) < self2->size, "slice out of range" );

BODY
  U32 size = Slice_size(self3);
  struct String* str = String_alloc(size);
  I32 start  = Slice_start (self3);
  I32 stride = Slice_stride(self3);

  if (stride == 1)
    memcpy(str->value, self2->value+start, size);
  else
    for (U32 i = 0; i < size; i++)
      str->value[i] = self2->value[i*stride];
  
  str->size = size;

  retmethod( (OBJ)str );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, String, Range);
defmethod(OBJ,  ginitWith2          , pmString, String, Range) // sub string
  struct Slice* slc = Slice_fromRange(atSlice(0), self3, &self2->size);

  retmethod( ginitWith2(_1,_2,(OBJ)slc) );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, String, IntVector);
defmethod(OBJ,  ginitWith2          , pmString, String, IntVector) // random sequence
  U32 size = self3->size;
  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U32  val_n = self2->size;
  U8  *val   = self2->value;
  I32  idx_s = self3->stride;
  I32 *idx   = self3->value;
  U32 *dst_n = &str->size;
  U8  *dst   = str->value;
  U8  *end   = dst + size;

  while (dst != end) {
    U32 i = Range_index(*idx, val_n);
    ensure( i < val_n, "index out of range" );
    *dst++ = val[i], ++*dst_n;
    idx += idx_s;
  }

  UNPRT(_str);
  retmethod(_str);
endmethod

// ----- constructors from C array

defmethod(OBJ, ginitWithChrPtr, pmString, (I8*)ref, (U32)size, (I32)stride)
  struct String* str = String_alloc(size);

  if (stride == 1)
    memcpy(str->value, ref, size);
  else
    for (U32 i = 0; i < size; i++)
      str->value[i] = ref[i*stride];

  str->size = size;

  retmethod((OBJ)str);
endmethod

// ----- copy, clone, swap, assign

defalias (OBJ, (gcopy)gclone, String); // clone
defmethod(OBJ,  gcopy       , String)  // copy
  struct String* str = String_alloc(self->size);

  memcpy(str->value, self->value, str->size = self->size);

  retmethod((OBJ)str);
endmethod


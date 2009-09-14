/*
 o---------------------------------------------------------------------o
 |
 | COS String - basic strings
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
 | $Id: String.c,v 1.6 2009/09/14 13:35:15 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/init.h>
#include <cos/gen/new.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>
#include <cos/prp/sequence.h>

// -----

makclass(String , ValueSequence);
makclass(StringN, String);

// -----

useclass(ExBadAlloc);
useclass(String, StringView);

// ----- properties

#define size_to_OBJ(siz) gautoDelete(aInt(siz))
#define string_class(str) String

defproperty(String,   size , size_to_OBJ);
defproperty(String, ()class, string_class);

#undef size_to_OBJ
#undef string_class

// --- getters

defmethod(struct Slice, gslice, String)
  retmethod( *atSlice(0,self->size,1) );
endmethod

defmethod(U32, gsize, String)
  retmethod(self->size);
endmethod

defmethod(I8*, gchrPtr, String)
  retmethod( (I8*)self->value );
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
  
  OBJ _str = gallocWithSize(StringN, size);

  struct StringN *strn = STATIC_CAST(struct StringN*, _str);
  struct String  *str  = &strn->String;

  str->value = strn->_value;
  str->size  = size;

  return str;
}

// ----- constructors

defmethod(OBJ, galloc, pmString) // lazy alloc
  retmethod(_1);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmString, String);
defmethod(OBJ,  ginitWith         , pmString, String) // clone
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct String* str = String_alloc(self2->size);

    memcpy(str->value, self2->value, str->size);

    retmethod( (OBJ)str );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, Int, Object);
defmethod(OBJ,  ginitWith2          , pmString, Int, Object) // element
  PRE
    test_assert(self2->value >= 0, "negative string size");

  POST
    // automatically trigger ginvariant

  BODY
    I32 val = gchr(_3);
    struct String* str = String_alloc(self2->value);

    memset(str->value, val, str->size);

    retmethod( (OBJ)str );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, Int, Functor);
defmethod(OBJ,  ginitWith2          , pmString, Int, Functor) // generator
  PRE
    test_assert(self2->value >= 0, "negative string size");

  POST
    // automatically trigger ginvariant

  BODY
    struct String* str = String_alloc(self2->value);
    OBJ _str = (OBJ)str; PRT(_str);

    U8* dst = str->value;
    U8* end = str->value + str->size;
    int argc = garity(_3);

    if (!argc)
      while (dst != end)
        *dst++ = gchr(geval(_3));

    else
      for (I32 i = 0; dst != end; i++)
        *dst++ = gchr(geval1(_3, aInt(i)));

    UNPRT(_str);
    retmethod(_str);
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, String, Slice);
defmethod(OBJ,  ginitWith2          , pmString, String, Slice) // sub string
  PRE
    U32 first = Slice_first(self3);
    U32 last  = Slice_last (self3);

    test_assert( first < self2->size &&
                 last  < self2->size, "slice out of range" );

  POST
    // automatically trigger ginvariant

  BODY
    U32 start  = Slice_first (self3);
    I32 stride = Slice_stride(self3);

    struct String* str = String_alloc(self3->size);

    U8* dst   = str->value;
    U8* end   = str->value + str->size;
    U8* src   = self2->value + start;
    I32 src_s = stride;

    while (dst != end) {
      *dst++ = *src;
      src += src_s;
    }

    retmethod( (OBJ)str );
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmString, String, IntVector);
defmethod(OBJ,  ginitWith2          , pmString, String, IntVector) // random sequence
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct String* str = String_alloc(self3->size);
    OBJ _str = (OBJ)str; PRT(_str);

    U8  *dst   = str->value;
    U8  *end   = str->value + str->size;
    U8  *src   = self2->value;
    U32  src_n = self2->size;
    I32 *idx   = self3->value;
    I32  idx_s = self3->stride;

    while (dst != end) {
      U32 i = Range_index(*idx, src_n);
      test_assert( i < src_n, "index out of range" );
      *dst++ = src[i];
      idx += idx_s;
    }

    UNPRT(_str);
    retmethod(_str);
endmethod

defalias (OBJ, (ginitWithChrPtr)gnewWithChrPtr, pmString, (I8*)ref, (U32)n, (I32)s);
defmethod(OBJ,  ginitWithChrPtr               , pmString, (I8*)ref, (U32)n, (I32)s)
  test_assert(s == 1, "strings are not strided");
  retmethod( ginitWith(_1, aStringRef((U8*)ref,n)) );
endmethod


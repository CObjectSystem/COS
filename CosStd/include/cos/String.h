#ifndef COS_STRING_H
#define COS_STRING_H

/*
 o---------------------------------------------------------------------o
 |
 | COS String and Dynamic String
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
 | $Id: String.h,v 1.11 2010/05/31 14:12:41 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>

/* NOTE-USER: String class cluster constructors

   aString    ("string")           -> String          (automatic)
   aStringRef (buffer[,size])      -> String          (automatic)

   gnewWith (String,string)        -> Block string    (copy)
   gnewWith2(String,size,chr)      -> Block string    (element)
   gnewWith2(String,size,fun)      -> Block string    (generator)
   gnewWith2(String,string,slice)  -> Block string    (substring)
   gnewWith2(String,string,range)  -> Block string    (substring)
   gnewWith2(String,string,intvec) -> Block string    (sequence)

   gnew     (String)               -> Dynamic string
   gnewWith (String,capacity)      -> Dynamic string  (pre-allocated)

   where:
   - All strings are mutable
   - All strings hold value elements
   - Dynamic strings can shrink and grow (gappend, gpreprend)
   - Dynamic strings can be converted to fixed string (gadjust)
   - StringRef buffer must allow to put '\0' at buffer[size] (WARNING)
*/

defclass(String, ValueSequence)
  U8* value;
  U32 size;
endclass

// ----- automatic constructors

#define aString(...)     ( (OBJ)atString    (__VA_ARGS__) )  // C-string literal
#define aStringRef(...)  ( (OBJ)atStringRef (__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aStr(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aString)) // C-string literal

#endif


/***********************************************************
 * Implementation (private)
 */

#include <string.h>

// ----- Block string

defclass(StringN, String)
  U8 _value[];
endclass

// ----- Fixed string, Dynamic string and Lazy string

defclass(StringFix, String)
  U8* _value;
  U32 capacity;
endclass

defclass(StringDyn, StringFix)
endclass

// ----- initializers, allocators (for the class cluster)

struct Slice;
struct String* String_alloc(U32);

// ----- automatic constructors

#define atString(cstr) \
  ( &(struct String) { {{{ cos_object_auto(String) }}}, \
    (U8[]){ cstr }, sizeof cstr -1 })

// --- StringRef (low-level)

#define atStringRef(...) \
  COS_PP_CAT_NARG(atStringRef_,__VA_ARGS__)(__VA_ARGS__)

#define atStringRef_1(buffer) \
        atStringRef_2(buffer, strlen(buffer))

#define atStringRef_2(buffer,size) \
  ( &(struct String) { {{{ cos_object_auto(String) }}}, (buffer), (size) } )

#endif // COS_STRING_H

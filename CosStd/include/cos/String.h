#ifndef COS_STRING_H
#define COS_STRING_H

/**
 * C Object System
 * COS String and Dynamic String
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
   gnewWith (String,size)          -> Dynamic string  (with capacity)

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

#define aArrStr(...) aArray(aStr(__VA_ARGS__))

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
endclass

defclass(StringDyn, StringFix)
  U32 capacity;
endclass

// ----- initializers, allocators (for the class cluster)

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
  ( &(struct String) { {{{ cos_object_auto(String) }}}, \
    buffer, size } )

#endif // COS_STRING_H

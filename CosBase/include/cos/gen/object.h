#ifndef COS_GEN_OBJECT_H
#define COS_GEN_OBJECT_H

/**
 * C Object System
 * COS generics for objects
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

#include <cos/Object.h>

// allocator, deallocator
defgeneric(OBJ , galloc        , _1);
defgeneric(OBJ , gallocWithSize, _1, (size_t)extra);
defgeneric(void, gdealloc      , _1);

// new
defgeneric(OBJ , gnew       , _1);
defgeneric(OBJ , gnewWith   , _1, _2);
defgeneric(OBJ , gnewWith2  , _1, _2, _3);
defgeneric(OBJ , gnewWith3  , _1, _2, _3, _4);
defgeneric(OBJ , gnewWith4  , _1, _2, _3, _4, _5);
defgeneric(OBJ , gnewWithStr, _1, (STR)str);

// constructors, copy ctor
defgeneric(OBJ , ginit       , _1);
defgeneric(OBJ , ginitWith   , _1, _2); // includes copy ctor: ginitWith(T,T)
defgeneric(OBJ , ginitWith2  , _1, _2, _3);
defgeneric(OBJ , ginitWith3  , _1, _2, _3, _4);
defgeneric(OBJ , ginitWith4  , _1, _2, _3, _4, _5);
defgeneric(OBJ , ginitWithStr, _1, (STR)str);

// destructor, clearing
defgeneric(OBJ , gdeinit, _1);
defgeneric(OBJ , gclear , _1);

// copy, clone
defgeneric(OBJ , gcopy , _1); // shallow copy
defgeneric(OBJ , gclone, _1); // deep    copy

// assign, swap
defgeneric(OBJ , gassign, _1, _2); // copy content
defgeneric(OBJ , gswap  , _1, _2); // swap content

// ownership
defgeneric(OBJ , gretain     , _1);
defgeneric(void, grelease    , _1);
defgeneric(OBJ , gautoRelease, _1);
defgeneric(U32 , gretainCount, _1);
  
// identity
defgeneric(OBJ , gisKindOf    , _1, _2); // returns True or False
defgeneric(OBJ , gisInstanceOf, _1, _2); // returns True or False
defgeneric(OBJ , gisNil       , _1);     // returns True or False
defgeneric(OBJ , gisNull      , _1);     // returns True or False
defgeneric(OBJ , gclass       , _1);
defgeneric(STR , gclassName   , _1);
defgeneric(OBJ , gsuperClass  , _1);

// initialization
defgeneric(void, ginitialize   , _1);
defgeneric(void, gdeinitialize , _1);

// contract
defgeneric(void, ginvariant, _1, (STR)file, (int)line);

// exception
defgeneric(void, gthrow, _1, (STR)file, (int)line);

// ----- inlined wrappers -----

#ifndef COS_RC_NOINLINE

#define gretain(obj)  gretain_inline (obj)
#define grelease(obj) grelease_inline(obj)

static cos_inline OBJ
gretain_inline(OBJ _1)
{
  return cos_object_rc(_1) >= COS_RC_UNIT ? cos_object_incRc(_1) : (gretain)(_1);
  COS_UNUSED(gretain_inline);
}

static cos_inline void
grelease_inline(OBJ _1)
{
  if (cos_object_rc(_1) > COS_RC_UNIT) cos_object_decRc(_1); else (grelease)(_1);
  COS_UNUSED(grelease_inline);
}

#endif // !COS_RC_NOINLINE

#endif // COS_GEN_OBJECT_H

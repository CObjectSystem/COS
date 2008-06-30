#ifndef COS_GEN_OBJECT_H
#define COS_GEN_OBJECT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for objects
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
 | $Id: object.h,v 1.2 2008/06/30 15:41:11 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif

// newXXX (= alloc+initXXX)
defgeneric(OBJ , gnew         , _1);
defgeneric(OBJ , gnewWith     , _1, _2);
defgeneric(OBJ , gnewWith2    , _1, _2, _3);
defgeneric(OBJ , gnewWith3    , _1, _2, _3, _4);
defgeneric(OBJ , gnewWith4    , _1, _2, _3, _4, _5);
defgeneric(OBJ , gnewWithLoc  , _1, _2, (STR)file, (int)line);
defgeneric(OBJ , gnewWithInt  , _1, (int)val);
defgeneric(OBJ , gnewWithStr  , _1, (STR)str);

// clone (=alloc+initWith(T,T))
defgeneric(OBJ , gclone       , _1);

// allocator, deallocator
defgeneric(OBJ , galloc       , _1);
defgeneric(OBJ , gallocWith   , _1, _2);
defgeneric(void, gdealloc     , _1);

// constructors, destructor
defgeneric(OBJ , ginit        , _1);
defgeneric(OBJ , ginitWith    , _1, _2); // ginitWith(T,T) = copy constructor
defgeneric(OBJ , ginitWith2   , _1, _2, _3);
defgeneric(OBJ , ginitWith3   , _1, _2, _3, _4);
defgeneric(OBJ , ginitWith4   , _1, _2, _3, _4, _5);
defgeneric(OBJ , ginitWithLoc , _1, _2, (STR)file, (int)line);
defgeneric(OBJ , ginitWithInt , _1, (int)val);
defgeneric(OBJ , ginitWithStr , _1, (STR)str);
defgeneric(OBJ , gdeinit      , _1);

// ownership
defgeneric(OBJ , gretain      , _1);
defgeneric(OBJ , grelease     , _1);
defgeneric(U32 , gretainCount , _1);
defgeneric(OBJ , gautoRelease , _1);

// identity, conversion, coercion
defgeneric(OBJ , gisKindOf    , _1, _2); // returns True or False
defgeneric(OBJ , gisInstanceOf, _1, _2); // returns True or False
defgeneric(OBJ , gclass       , _1);
defgeneric(STR , gclassName   , _1);

// inheritance
defgeneric(OBJ , gsuperClass  , _1);

// comparison
defgeneric(OBJ , gequal       , _1, _2);
defgeneric(OBJ , gcompare     , _1, _2); // return Equal, Lesser or Greater
defgeneric(U32 , ghash        , _1);

// contract
defgeneric(void, ginvariant   , _1, (STR)file, (int)line);

// exception
defgeneric(void, gthrow       , _1, (STR)file, (int)line);

// initialization
defgeneric(void, ginitialize  , _1);
defgeneric(void, gdeinitialize, _1);

#endif // COS_GEN_OBJECT_H

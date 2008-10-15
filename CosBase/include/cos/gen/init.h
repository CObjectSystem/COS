#ifndef COS_GEN_INIT_H
#define COS_GEN_INIT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for extra constructors
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
 | $Id: init.h,v 1.6 2008/10/15 19:18:06 ldeniau Exp $
 |
*/

#ifndef COS_GEN_OBJECT_H
#include <cos/gen/object.h>
#endif

// constructors
defgeneric(OBJ , ginitWithObj  , _1, (OBJ)_2);
defgeneric(OBJ , ginitWithObj2 , _1, (OBJ)_2, (OBJ)_3);
defgeneric(OBJ , ginitWithObj3 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4);
defgeneric(OBJ , ginitWithObj4 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5);
defgeneric(OBJ , ginitWithObj5 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6);
defgeneric(OBJ , ginitWithObj6 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7);
defgeneric(OBJ , ginitWithObj7 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7, (OBJ)_8);
defgeneric(OBJ , ginitWithObj8 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7, (OBJ)_8, (OBJ)_9);
defgeneric(OBJ , ginitWithObj9 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7, (OBJ)_8, (OBJ)_9, (OBJ)_10);

defgeneric(OBJ, ginitWithChr , _1, (I8 )val);
defgeneric(OBJ, ginitWithSht , _1, (I16)val);
defgeneric(OBJ, ginitWithInt , _1, (I32)val);
defgeneric(OBJ, ginitWithLng , _1, (I64)val);
defgeneric(OBJ, ginitWithFlt , _1, (R64)val);
defgeneric(OBJ, ginitWithCpx , _1, (C64)val);

defgeneric(OBJ, ginitWithChrPtr , _1, (U32)n, (I8 *)val);
defgeneric(OBJ, ginitWithShtPtr , _1, (U32)n, (I16*)val);
defgeneric(OBJ, ginitWithIntPtr , _1, (U32)n, (I32*)val);
defgeneric(OBJ, ginitWithLngPtr , _1, (U32)n, (I64*)val);
defgeneric(OBJ, ginitWithFltPtr , _1, (U32)n, (R64*)val);
defgeneric(OBJ, ginitWithCpxPtr , _1, (U32)n, (C64*)val);
defgeneric(OBJ, ginitWithObjPtr , _1, (U32)n, (OBJ*)obj);

// newXXX (= alloc+initXXX)

static inline OBJ
gnewWithObj(OBJ _1, OBJ _2) {
  return ginitWithObj(galloc(_1),_2);  COS_UNUSED(gnewWithObj);
}

static inline OBJ
gnewWithObj2(OBJ _1, OBJ _2, OBJ _3) {
  return ginitWithObj2(galloc(_1),_2,_3);  COS_UNUSED(gnewWithObj2);
}

static inline OBJ
gnewWithObj3(OBJ _1, OBJ _2, OBJ _3, OBJ _4) {
  return ginitWithObj3(galloc(_1),_2,_3,_4);  COS_UNUSED(gnewWithObj3);
}

static inline OBJ
gnewWithObj4(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5) {
  return ginitWithObj4(galloc(_1),_2,_3,_4,_5);  COS_UNUSED(gnewWithObj4);
}

static inline OBJ
gnewWithObj5(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, OBJ _6) {
  return ginitWithObj5(galloc(_1),_2,_3,_4,_5,_6);  COS_UNUSED(gnewWithObj5);
}

static inline OBJ
gnewWithObj6(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, OBJ _6, OBJ _7) {
  return ginitWithObj6(galloc(_1),_2,_3,_4,_5,_6,_7);  COS_UNUSED(gnewWithObj6);
}

static inline OBJ
gnewWithObj7(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, OBJ _6, OBJ _7, OBJ _8) {
  return ginitWithObj7(galloc(_1),_2,_3,_4,_5,_6,_7,_8);  COS_UNUSED(gnewWithObj7);
}

static inline OBJ
gnewWithObj8(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, OBJ _6, OBJ _7, OBJ _8, OBJ _9) {
  return ginitWithObj8(galloc(_1),_2,_3,_4,_5,_6,_7,_8,_9);  COS_UNUSED(gnewWithObj8);
}

static inline OBJ
gnewWithObj9(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, OBJ _6, OBJ _7, OBJ _8, OBJ _9, OBJ _10) {
  return ginitWithObj9(galloc(_1),_2,_3,_4,_5,_6,_7,_8,_9,_10);  COS_UNUSED(gnewWithObj9);
}

static inline OBJ
gnewWithChr(OBJ _1, I8 val) {
  return ginitWithChr(galloc(_1),val); COS_UNUSED(gnewWithChr);
}

static inline OBJ
gnewWithSht(OBJ _1, I16 val) {
  return ginitWithSht(galloc(_1),val); COS_UNUSED(gnewWithSht);
}

static inline OBJ
gnewWithInt(OBJ _1, I32 val) {
  return ginitWithInt(galloc(_1),val); COS_UNUSED(gnewWithInt);
}

static inline OBJ
gnewWithLng(OBJ _1, I64 val) {
  return ginitWithLng(galloc(_1),val); COS_UNUSED(gnewWithLng);
}

static inline OBJ
gnewWithFlt(OBJ _1, R64 val) {
  return ginitWithFlt(galloc(_1),val); COS_UNUSED(gnewWithFlt);
}

static inline OBJ
gnewWithCpx(OBJ _1, C64 val) {
  return ginitWithCpx(galloc(_1),val); COS_UNUSED(gnewWithCpx);
}

// newXXXPtr (= alloc+initXXXPtr)

static inline OBJ
gnewWithChrPtr(OBJ _1, U32 n, I8 *val) {
  return ginitWithChrPtr(galloc(_1),n,val); COS_UNUSED(gnewWithChrPtr);
}

static inline OBJ
gnewWithShtPtr(OBJ _1, U32 n, I16 *val) {
  return ginitWithShtPtr(galloc(_1),n,val); COS_UNUSED(gnewWithShtPtr);
}

static inline OBJ
gnewWithIntPtr(OBJ _1, U32 n, I32 *val) {
  return ginitWithIntPtr(galloc(_1),n,val); COS_UNUSED(gnewWithIntPtr);
}

static inline OBJ
gnewWithLngPtr(OBJ _1, U32 n, I64 *val) {
  return ginitWithLngPtr(galloc(_1),n,val); COS_UNUSED(gnewWithLngPtr);
}

static inline OBJ
gnewWithFltPtr(OBJ _1, U32 n, R64 *val) {
  return ginitWithFltPtr(galloc(_1),n,val); COS_UNUSED(gnewWithFltPtr);
}

static inline OBJ
gnewWithCpxPtr(OBJ _1, U32 n, C64 *val) {
  return ginitWithCpxPtr(galloc(_1),n,val); COS_UNUSED(gnewWithCpxPtr);
}

static inline OBJ
gnewWithObjPtr(OBJ _1, U32 n, OBJ *obj) {
  return ginitWithObjPtr(galloc(_1),n,obj); COS_UNUSED(gnewWithObjPtr);
}

#endif // COS_GEN_INIT_H

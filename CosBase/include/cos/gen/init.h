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
 | $Id: init.h,v 1.13 2009/08/03 21:07:13 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>

// constructors
defgeneric(OBJ , ginitWithObj  , _1, (OBJ)_2);
defgeneric(OBJ , ginitWithObj2 , _1, (OBJ)_2, (OBJ)_3);
defgeneric(OBJ , ginitWithObj3 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4);
defgeneric(OBJ , ginitWithObj4 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5);
defgeneric(OBJ , ginitWithObj5 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6);

defgeneric(OBJ, ginitWithChr   , _1, (I32)val);
defgeneric(OBJ, ginitWithSht   , _1, (I32)val);
defgeneric(OBJ, ginitWithInt   , _1, (I32)val);
defgeneric(OBJ, ginitWithLng   , _1, (I64)val);
defgeneric(OBJ, ginitWithFlt   , _1, (F64)val);
defgeneric(OBJ, ginitWithCpx   , _1, (C64)val);

defgeneric(OBJ, ginitWithChrPtr, _1, (I8 *)ref, (U32)n);
defgeneric(OBJ, ginitWithShtPtr, _1, (I16*)ref, (U32)n);
defgeneric(OBJ, ginitWithIntPtr, _1, (I32*)ref, (U32)n);
defgeneric(OBJ, ginitWithLngPtr, _1, (I64*)ref, (U32)n);
defgeneric(OBJ, ginitWithFltPtr, _1, (F64*)ref, (U32)n);
defgeneric(OBJ, ginitWithCpxPtr, _1, (C64*)ref, (U32)n);
defgeneric(OBJ, ginitWithObjPtr, _1, (OBJ*)ref, (U32)n);

// newXXX (= alloc+initXXX)

static always_inline OBJ
gnewWithObj(OBJ _1, OBJ _2) {
  return ginitWithObj(galloc(_1),_2);
  COS_UNUSED(gnewWithObj);
}

static always_inline OBJ
gnewWithObj2(OBJ _1, OBJ _2, OBJ _3) {
  return ginitWithObj2(galloc(_1),_2,_3);
  COS_UNUSED(gnewWithObj2);
}

static always_inline OBJ
gnewWithObj3(OBJ _1, OBJ _2, OBJ _3, OBJ _4) {
  return ginitWithObj3(galloc(_1),_2,_3,_4);
  COS_UNUSED(gnewWithObj3);
}

static always_inline OBJ
gnewWithObj4(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5) {
  return ginitWithObj4(galloc(_1),_2,_3,_4,_5);
  COS_UNUSED(gnewWithObj4);
}

static always_inline OBJ
gnewWithObj5(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, OBJ _6) {
  return ginitWithObj5(galloc(_1),_2,_3,_4,_5,_6);
  COS_UNUSED(gnewWithObj5);
}

static always_inline OBJ
gnewWithChr(OBJ _1, I32 val) {
  return ginitWithChr(galloc(_1),val);
  COS_UNUSED(gnewWithChr);
}

static always_inline OBJ
gnewWithSht(OBJ _1, I32 val) {
  return ginitWithSht(galloc(_1),val);
  COS_UNUSED(gnewWithSht);
}

static always_inline OBJ
gnewWithInt(OBJ _1, I32 val) {
  return ginitWithInt(galloc(_1),val);
  COS_UNUSED(gnewWithInt);
}

static always_inline OBJ
gnewWithLng(OBJ _1, I64 val) {
  return ginitWithLng(galloc(_1),val);
  COS_UNUSED(gnewWithLng);
}

static always_inline OBJ
gnewWithFlt(OBJ _1, F64 val) {
  return ginitWithFlt(galloc(_1),val);
  COS_UNUSED(gnewWithFlt);
}

static always_inline OBJ
gnewWithCpx(OBJ _1, C64 val) {
  return ginitWithCpx(galloc(_1),val);
  COS_UNUSED(gnewWithCpx);
}

// newXXXPtr (= alloc+initXXXPtr)

static always_inline OBJ
gnewWithChrPtr(OBJ _1, I8 *val, U32 n) {
  return ginitWithChrPtr(galloc(_1),val,n);
  COS_UNUSED(gnewWithChrPtr);
}

static always_inline OBJ
gnewWithShtPtr(OBJ _1, I16 *val, U32 n) {
  return ginitWithShtPtr(galloc(_1),val,n);
  COS_UNUSED(gnewWithShtPtr);
}

static always_inline OBJ
gnewWithIntPtr(OBJ _1, I32 *val, U32 n) {
  return ginitWithIntPtr(galloc(_1),val,n);
  COS_UNUSED(gnewWithIntPtr);
}

static always_inline OBJ
gnewWithLngPtr(OBJ _1, I64 *val, U32 n) {
  return ginitWithLngPtr(galloc(_1),val,n);
  COS_UNUSED(gnewWithLngPtr);
}

static always_inline OBJ
gnewWithFltPtr(OBJ _1, F64 *val, U32 n) {
  return ginitWithFltPtr(galloc(_1),val,n);
  COS_UNUSED(gnewWithFltPtr);
}

static always_inline OBJ
gnewWithCpxPtr(OBJ _1, C64 *val, U32 n) {
  return ginitWithCpxPtr(galloc(_1),val,n);
  COS_UNUSED(gnewWithCpxPtr);
}

static always_inline OBJ
gnewWithObjPtr(OBJ _1, OBJ *obj, U32 n) {
  return ginitWithObjPtr(galloc(_1),obj,n);
  COS_UNUSED(gnewWithObjPtr);
}

#endif // COS_GEN_INIT_H

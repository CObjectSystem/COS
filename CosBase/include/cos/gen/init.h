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
 | $Id: init.h,v 1.1 2008/07/15 08:00:46 ldeniau Exp $
 |
*/

#ifndef COS_GEN_OBJECT_H
#include <cos/gen/object.h>
#endif

// constructors
defgeneric(OBJ, ginitWithChr , _1, (S8 )val);
defgeneric(OBJ, ginitWithSht , _1, (S32)val);
defgeneric(OBJ, ginitWithInt , _1, (S32)val);
defgeneric(OBJ, ginitWithLng , _1, (S64)val);

defgeneric(OBJ, ginitWithUChr, _1, (U8 )val);
defgeneric(OBJ, ginitWithUSht, _1, (U16)val);
defgeneric(OBJ, ginitWithUInt, _1, (U32)val);
defgeneric(OBJ, ginitWithULng, _1, (U64)val);

defgeneric(OBJ, ginitWithDbl , _1, (double )val);
defgeneric(OBJ, ginitWithCpx , _1, (COMPLEX)val);

defgeneric(OBJ, ginitWithChrPtr , _1, (U32)n, (S8 *)val);
defgeneric(OBJ, ginitWithShtPtr , _1, (U32)n, (S16*)val);
defgeneric(OBJ, ginitWithIntPtr , _1, (U32)n, (S32*)val);
defgeneric(OBJ, ginitWithLngPtr , _1, (U32)n, (S64*)val);

defgeneric(OBJ, ginitWithUChrPtr, _1, (U32)n, (U8 *)val);
defgeneric(OBJ, ginitWithUShtPtr, _1, (U32)n, (U16*)val);
defgeneric(OBJ, ginitWithUIntPtr, _1, (U32)n, (U32*)val);
defgeneric(OBJ, ginitWithULngPtr, _1, (U32)n, (U64*)val);

defgeneric(OBJ, ginitWithDblPtr , _1, (U32)n, (double *)val);
defgeneric(OBJ, ginitWithCpxPtr , _1, (U32)n, (COMPLEX*)val);

// newXXX (= alloc+initXXX)

static inline OBJ
gnewWithChr(OBJ _1, S8 val) {
  return ginitWithChr(galloc(_1),val); COS_UNUSED(gnewWithChr);
}

static inline OBJ
gnewWithSht(OBJ _1, S16 val) {
  return ginitWithSht(galloc(_1),val); COS_UNUSED(gnewWithSht);
}

static inline OBJ
gnewWithInt(OBJ _1, S32 val) {
  return ginitWithInt(galloc(_1),val); COS_UNUSED(gnewWithInt);
}

static inline OBJ
gnewWithLng(OBJ _1, S64 val) {
  return ginitWithLng(galloc(_1),val); COS_UNUSED(gnewWithLng);
}

static inline OBJ
gnewWithUChr(OBJ _1, U8 val) {
  return ginitWithUChr(galloc(_1),val); COS_UNUSED(gnewWithUChr);
}

static inline OBJ
gnewWithUSht(OBJ _1, U16 val) {
  return ginitWithUSht(galloc(_1),val); COS_UNUSED(gnewWithUSht);
}

static inline OBJ
gnewWithUInt(OBJ _1, U32 val) {
  return ginitWithUInt(galloc(_1),val); COS_UNUSED(gnewWithUInt);
}

static inline OBJ
gnewWithULng(OBJ _1, U64 val) {
  return ginitWithULng(galloc(_1),val); COS_UNUSED(gnewWithULng);
}

static inline OBJ
gnewWithDbl(OBJ _1, double val) {
  return ginitWithDbl(galloc(_1),val); COS_UNUSED(gnewWithDbl);
}

static inline OBJ
gnewWithCpx(OBJ _1, COMPLEX val) {
  return ginitWithCpx(galloc(_1),val); COS_UNUSED(gnewWithCpx);
}

// newXXXPtr (= alloc+initXXXPtr)

static inline OBJ
gnewWithChrPtr(OBJ _1, U32 n, S8 *val) {
  return ginitWithChrPtr(galloc(_1),n,val); COS_UNUSED(gnewWithChrPtr);
}

static inline OBJ
gnewWithShtPtr(OBJ _1, U32 n, S16 *val) {
  return ginitWithShtPtr(galloc(_1),n,val); COS_UNUSED(gnewWithShtPtr);
}

static inline OBJ
gnewWithIntPtr(OBJ _1, U32 n, S32 *val) {
  return ginitWithIntPtr(galloc(_1),n,val); COS_UNUSED(gnewWithIntPtr);
}

static inline OBJ
gnewWithLngPtr(OBJ _1, U32 n, S64 *val) {
  return ginitWithLngPtr(galloc(_1),n,val); COS_UNUSED(gnewWithLngPtr);
}

static inline OBJ
gnewWithUChrPtr(OBJ _1, U32 n, U8 *val) {
  return ginitWithUChrPtr(galloc(_1),n,val); COS_UNUSED(gnewWithUChrPtr);
}

static inline OBJ
gnewWithUShtPtr(OBJ _1, U32 n, U16 *val) {
  return ginitWithUShtPtr(galloc(_1),n,val); COS_UNUSED(gnewWithUShtPtr);
}

static inline OBJ
gnewWithUIntPtr(OBJ _1, U32 n, U32 *val) {
  return ginitWithUIntPtr(galloc(_1),n,val); COS_UNUSED(gnewWithUIntPtr);
}

static inline OBJ
gnewWithULngPtr(OBJ _1, U32 n, U64 *val) {
  return ginitWithULngPtr(galloc(_1),n,val); COS_UNUSED(gnewWithULngPtr);
}

static inline OBJ
gnewWithDblPtr(OBJ _1, U32 n, double *val) {
  return ginitWithDblPtr(galloc(_1),n,val); COS_UNUSED(gnewWithDblPtr);
}

static inline OBJ
gnewWithCpxPtr(OBJ _1, U32 n, COMPLEX *val) {
  return ginitWithCpxPtr(galloc(_1),n,val); COS_UNUSED(gnewWithCpxPtr);
}

#endif // COS_GEN_INIT_H

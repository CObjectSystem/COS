#ifndef COS_GEN_COMPARE_H
#define COS_GEN_COMPARE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS comparison generics
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
 | $Id: compare.h,v 1.1 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Generic.h>

/* NOTE-USER: object comparison

   gcompare(a,b) =
     | a < b     -> Lesser
     | a > b     -> Geater
     | otherwise -> Equal

   gisEqual(a,b) =
     | a == b    -> True
     | otherwise -> False

   gisLesser(a,b) =
     | a < b     -> True
     | otherwise -> False

   gisGreater(a,b) =
     | a > b     -> True
     | otherwise -> False

   gmin(a,b) =
     | a > b     -> b
     | otherwise -> a

   gmax(a,b) =
     | a < b     -> b
     | otherwise -> a
*/

// comparison
defgeneric(OBJ, (GenComparator)gisEqual, _1, _2); // return True or False
defgeneric(OBJ, (GenComparator)gcompare, _1, _2); // return Equal,Lesser,Greater
defgeneric(U32, (GenOperator  )ghash   , _1);

// inliners

static always_inline BOOL
gequal(OBJ _1, OBJ _2) {
  return gisEqual(_1,_2) == True;
}

static always_inline BOOL
gnotEqual(OBJ _1, OBJ _2) {
  return gisEqual(_1,_2) != True;
}

static always_inline BOOL
glesser(OBJ _1, OBJ _2) {
  useclass(Lesser);
  return gcompare(_1,_2) == Lesser;
}

static always_inline BOOL
ggreater(OBJ _1, OBJ _2) {
  useclass(Greater);
  return gcompare(_1,_2) == Greater;
}

static always_inline BOOL
glesserOrEqual(OBJ _1, OBJ _2) {
  useclass(Greater);
  return gcompare(_1,_2) != Greater;
}

static always_inline BOOL
ggreaterOrEqual(OBJ _1, OBJ _2) {
  useclass(Lesser);
  return gcompare(_1,_2) != Lesser;
}

// ---

static always_inline OBJ
gisNotEqual(OBJ _1, OBJ _2) {
  return gnotEqual(_1,_2) ? True : False;
}

static always_inline OBJ
gisLesser(OBJ _1, OBJ _2) {
  return glesser(_1,_2) ? True : False;
}

static always_inline OBJ
gisGreater(OBJ _1, OBJ _2) {
  return ggreater(_1,_2) ? True : False;
}

static always_inline OBJ
gisLesserOrEqual(OBJ _1, OBJ _2) {
  return glesserOrEqual(_1,_2) ? True : False;
}

static always_inline OBJ
gisGreaterOrEqual(OBJ _1, OBJ _2) {
  return ggreaterOrEqual(_1,_2) ? True : False;
}

// ---

static always_inline OBJ
gmin(OBJ _1, OBJ _2) {
  return ggreater(_1,_2) ? _2 : _1;
}

static always_inline OBJ
gmax(OBJ _1, OBJ _2) {
  return glesser(_1,_2) ? _2 : _1;
}

#endif // COS_GEN_COMPARE_H

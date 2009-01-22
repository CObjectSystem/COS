#ifndef COS_GEN_LOGIC_H
#define COS_GEN_LOGIC_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generic logical operators
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
 | $Id: logic.h,v 1.5 2009/01/22 16:45:07 ldeniau Exp $
 |
*/

#include <cos/gen/object.h>

defgeneric(OBJ, gnot    , _1);     
defgeneric(OBJ, gand    , _1, _2);
defgeneric(OBJ, gor     , _1, _2);
defgeneric(OBJ, gxor    , _1, _2); // not (_1 isEqual _2)
defgeneric(OBJ, gimplies, _1, _2); // (not _1) or _2

// inliners

static inline BOOL
equal(OBJ _1, OBJ _2) {
  return gisEqual(_1,_2) == True;
}

static inline BOOL
lesser(OBJ _1, OBJ _2) {
  useclass(Lesser);
  return gcompare(_1,_2) == Lesser;
}

static inline BOOL
greater(OBJ _1, OBJ _2) {
  useclass(Greater);
  return gcompare(_1,_2) == Greater;
}

static inline BOOL
notEqual(OBJ _1, OBJ _2) {
  return gisEqual(_1,_2) != True;
}

static inline BOOL
lesserEqual(OBJ _1, OBJ _2) {
  useclass(Greater);
  return gcompare(_1,_2) != Greater;
}

static inline BOOL
greaterEqual(OBJ _1, OBJ _2) {
  useclass(Lesser);
  return gcompare(_1,_2) != Lesser;
}

#endif // COS_GEN_LOGIC_H

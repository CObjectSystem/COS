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
 | $Id: logic.h,v 1.8 2009/07/24 12:36:26 ldeniau Exp $
 |
*/

/* NOTE-USER: includes of generics
   One can find hereafter a trick to avoid multiple definition of generics when
   the instance generation is left to the COS makefiles (e.g automatic makgeneric).
*/

#ifndef COS_NOCOS
#include <cos/gen/object.h>
#endif

defgeneric(OBJ, gnot    , _1);
defgeneric(OBJ, gand    , _1, _2);
defgeneric(OBJ, gor     , _1, _2);
defgeneric(OBJ, gxor    , _1, _2); // not (_1 isEqual _2)
defgeneric(OBJ, gimplies, _1, _2); // (not _1) or _2

// inliners

static always_inline BOOL
gequal(OBJ _1, OBJ _2) {
  return gisEqual(_1,_2) == True;
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
gnotEqual(OBJ _1, OBJ _2) {
  return gisEqual(_1,_2) != True;
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

#endif // COS_GEN_LOGIC_H

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
 | $Id: logic.h,v 1.3 2008/10/20 14:41:29 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif

// return True, False or TrueFalse (= uncertain, undetermined)
defgeneric(OBJ, gbool   , _1);     
defgeneric(OBJ, gnot    , _1);     
defgeneric(OBJ, gand    , _1, _2);
defgeneric(OBJ, gor     , _1, _2);
defgeneric(OBJ, gxor    , _1, _2); // not (_1 equal _2)
defgeneric(OBJ, gimplies, _1, _2); // (not _1) or _2

// return True, False or Nil (= stop)
defgeneric(OBJ, gall    , _1, _2);
defgeneric(OBJ, gany    , _1, _2);

// gequal() and gcompare() are provided by cos/gen/object.h

// inliners
static inline OBJ
gEQ(OBJ _1, OBJ _2) {
  useclass(Equal);
  OBJ res = gcompare(_1,_2);
  return res == Equal ? True : False; COS_UNUSED(gEQ);
}

static inline OBJ
gNE(OBJ _1, OBJ _2) {
  useclass(Equal);
  OBJ res = gcompare(_1,_2);
  return res == Equal ? False : True; COS_UNUSED(gNE);
}

static inline OBJ
gLT(OBJ _1, OBJ _2) {
  useclass(Lesser);
  OBJ res = gcompare(_1,_2);
  return res == Lesser ? True : False; COS_UNUSED(gLT);
}

static inline OBJ
gGT(OBJ _1, OBJ _2) {
  useclass(Greater);
  OBJ res = gcompare(_1,_2);
  return res == Greater ? True : False; COS_UNUSED(gGT);
}

static inline OBJ
gLE(OBJ _1, OBJ _2) {
  useclass(Greater);
  OBJ res = gcompare(_1,_2);
  return res == Greater ? False : True; COS_UNUSED(gLE);
}

static inline OBJ
gGE(OBJ _1, OBJ _2) {
  useclass(Lesser);
  OBJ res = gcompare(_1,_2);
  return res == Lesser ? False : True; COS_UNUSED(gGE);
}

static inline OBJ
gmin(OBJ _1, OBJ _2) {
  useclass(Greater);
  OBJ res = gcompare(_1,_2);
  return res == Greater ? _2 : _1; COS_UNUSED(gmin);
}

static inline OBJ
gmax(OBJ _1, OBJ _2) {
  useclass(Lesser);
  OBJ res = gcompare(_1,_2);
  return res == Lesser ? _2 : _1; COS_UNUSED(gmax);
}

#endif // COS_GEN_LOGIC_H

#ifndef COS_GEN_ALGORITHM_H
#define COS_GEN_ALGORITHM_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for algorithms
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
 | $Id: algorithm.h,v 1.44 2010/05/31 14:02:58 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// linear search if fun _2 returns TrueFalse
// binary search if fun _2 returns Ordered (and it is sorted)
// return Nil if not found
defgeneric(OBJ, gfind , _1, fun); // return object
defgeneric(OBJ, gifind, _1, fun); // return res such that ggetAt(_1,res) get object

// sorting (fun must return Ordered)
defgeneric(OBJ, gsort    , _1, fun); // in place
defgeneric(OBJ, gisort   , _1, fun); // return an array of indexes/keys
defgeneric(OBJ, gisSorted, _1, fun); // return True or False

// all, any, count
defgeneric(OBJ, gall  , _1, fun); // fun should return TrueFalse
defgeneric(OBJ, gany  , _1, fun); // fun should return TrueFalse
defgeneric(U32, gcount, _1, fun); // fun should return TrueFalse

// seq-like algorithms
defgeneric(OBJ, gintersperse, _1, fun); // intersperse value when not Nil
defgeneric(OBJ, ggroup      , _1, fun); // group true then false (pair)
defgeneric(OBJ, gsplit      , _1, fun); // split when true
defgeneric(OBJ, gunique     , _1, fun); // remove contiguous equal elements

// set-like algorithms
defgeneric(OBJ, gdiff       , _1, _2, fun); // _1 - _2 [asymmetric]
defgeneric(OBJ, gmerge      , _1, _2, fun); // _1 + _2 (requires sorted _1, _2)
defgeneric(OBJ, gintersect  , _1, _2, fun); // _1 - (_1 - _2) [asymmetric]

// defgeneric(OBJ, gmatch      , _1, _2, fun); // _2 - (_2 - _1) [asymmetric]
  // note : gmatch(_1,_2) == gintersect(_2,_1), except for fun and complexity

#endif // COS_GEN_ALGORITHM_H


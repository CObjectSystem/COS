#ifndef COS_GEN_ALGORITHM_H
#define COS_GEN_ALGORITHM_H

/**
 * C Object System
 * COS generics for algorithms
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


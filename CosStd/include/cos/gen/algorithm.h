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
 | $Id: algorithm.h,v 1.17 2009/08/29 21:33:39 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// in place
defgeneric(void, gforeach, _1, fun); // fun return value is discarded
defgeneric(void, gpermute, _1, idx);
defgeneric(void, greverse, _1);
defgeneric(void, gapply  , fun, _1); // "in place" map

// cat
defgeneric(OBJ , gcat , _1, _2);
defgeneric(OBJ , gcat3, _1, _2, _3);
defgeneric(OBJ , gcat4, _1, _2, _3, _4);
defgeneric(OBJ , gcat5, _1, _2, _3, _4, _5);

// zip
defgeneric(OBJ , gzip , _1, _2);
defgeneric(OBJ , gzip3, _1, _2, _3);
defgeneric(OBJ , gzip4, _1, _2, _3, _4);
defgeneric(OBJ , gzip5, _1, _2, _3, _4, _5);

// map
defgeneric(OBJ , gmap , fun, _1);
defgeneric(OBJ , gmap2, fun, _1, _2);
defgeneric(OBJ , gmap3, fun, _1, _2, _3);
defgeneric(OBJ , gmap4, fun, _1, _2, _3, _4);

// filter, fold, scan
defgeneric(OBJ , gselect      , _1, fun);
defgeneric(OBJ , greject      , _1, fun);
defgeneric(OBJ , greduce      , _1, fun, ini);
defgeneric(OBJ , grreduce     , _1, fun, ini);
defgeneric(OBJ , gaccumulate  , _1, fun, ini);
defgeneric(OBJ , graccumulate , _1, fun, ini);

// repeat, iterate
defgeneric(OBJ , grepeat , obj, num);
defgeneric(OBJ , giterate, fun, num);

// all, any, count
defgeneric(OBJ , gall  , _1, fun); // fun should return TrueFalse
defgeneric(OBJ , gany  , _1, fun); // fun should return TrueFalse
defgeneric(U32 , gcount, _1, fun); // fun should return TrueFalse

// min, max
defgeneric(OBJ , gmin, _1, _2 or fun); // fun should return Ordered or the min
defgeneric(OBJ , gmax, _1, _2 or fun); // fun should return Ordered or the min
                // note: gmin(array, aFun(gmin,0,0) ) should work like a foldl

// sorting (fun must return Ordered)
defgeneric(void, gsort    , _1, fun); // in place
defgeneric(OBJ , gisort   , _1, fun); // return an array of indexes/keys
defgeneric(OBJ , gisSorted, _1, fun); // return True or False

// linear search if fun returns TrueFalse
// binary search if fun returns Ordered (and it is sorted)
defgeneric(OBJ , gfind , _1, fun); // return Nil if not found
defgeneric(OBJ , gifind, _1, fun); // return an index/key or Nil

// seq-like algorithms (fun must return TrueFalse)
defgeneric(OBJ , gunique, _1, fun); // remove contiguous equal elements
defgeneric(OBJ , ggroup , _1, fun); // split when false
defgeneric(OBJ , gsplit , _1, fun); // split when true

// set-like algorithms
defgeneric(OBJ , gdiff     , _1, _2, fun);
defgeneric(OBJ , gunion    , _1, _2, fun);
defgeneric(OBJ , gmerge    , _1, _2, fun);
defgeneric(OBJ , gintersect, _1, _2, fun);

#endif // COS_GEN_ALGORITHM_H


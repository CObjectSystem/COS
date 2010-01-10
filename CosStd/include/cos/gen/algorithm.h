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
 | $Id: algorithm.h,v 1.41 2010/01/10 21:23:04 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// in place
defgeneric(OBJ, greverse, _1);
defgeneric(OBJ, gpermute, _1, idx);

// concat
defgeneric(OBJ, gconcat , _1, _2);
defgeneric(OBJ, gconcat3, _1, _2, _3);
defgeneric(OBJ, gconcat4, _1, _2, _3, _4);
defgeneric(OBJ, gconcat5, _1, _2, _3, _4, _5);
defgeneric(OBJ, gconcatn, _1);

// zip
defgeneric(OBJ, gzip , _1, _2);
defgeneric(OBJ, gzip3, _1, _2, _3);
defgeneric(OBJ, gzip4, _1, _2, _3, _4);
defgeneric(OBJ, gzip5, _1, _2, _3, _4, _5);
defgeneric(OBJ, gzipn, _1);

// foreach (discard returned value)
defgeneric(void, gforeach     , _1, fun);
defgeneric(void, gforeach2    , _1, _2, fun);
defgeneric(void, gforeach3    , _1, _2, _3, fun);
defgeneric(void, gforeach4    , _1, _2, _3, _4, fun);
defgeneric(void, gforeachWhile, _1, fun); // stop if fun returns Nil

// apply (in-place map on _1, return _1)
defgeneric(OBJ, gapply     , fun, _1);
defgeneric(OBJ, gapply2    , fun, _1, _2);
defgeneric(OBJ, gapply3    , fun, _1, _2, _3);
defgeneric(OBJ, gapply4    , fun, _1, _2, _3, _4);
defgeneric(OBJ, gapplyIf   , fun, _1); // reject if fun returns Nil
defgeneric(OBJ, gapplyWhile, fun, _1); // stop   if fun returns Nil

// map
defgeneric(OBJ, gmap     , fun, _1);
defgeneric(OBJ, gmap2    , fun, _1, _2);
defgeneric(OBJ, gmap3    , fun, _1, _2, _3);
defgeneric(OBJ, gmap4    , fun, _1, _2, _3, _4);
defgeneric(OBJ, gmapIf   , fun, _1); // reject if fun returns Nil
defgeneric(OBJ, gmapWhile, fun, _1); // stop   if fun returns Nil

// filter
defgeneric(OBJ, gselect     , _1, fun); // select if    fun returns True
defgeneric(OBJ, gselectWhile, _1, fun); // select while fun returns True

// filter-out
defgeneric(OBJ, greject     , _1, fun); // reject if    fun returns True
defgeneric(OBJ, grejectWhile, _1, fun); // reject while fun returns True

// reduce, rreduce
defgeneric(OBJ, greduce , _1, fun);                // foldl1
defgeneric(OBJ, greduce1, _1, fun, ini);           // foldl
defgeneric(OBJ, greduce2, _1, fun, ini, fin);      // foldl with lookahead

defgeneric(OBJ, grreduce , _1, fun);               // foldr1
defgeneric(OBJ, grreduce1, _1, fun, ini);          // foldr
defgeneric(OBJ, grreduce2, _1, fun, ini, fin);     // foldr with lookahead

// accumulate, raccumulate
defgeneric(OBJ, gaccumulate , _1, fun);            // scanl1
defgeneric(OBJ, gaccumulate1, _1, fun, ini);       // scanl
defgeneric(OBJ, gaccumulate2, _1, fun, ini, fin);  // scanl with lookahead

defgeneric(OBJ, graccumulate , _1, fun);           // scanr1
defgeneric(OBJ, graccumulate1, _1, fun, ini);      // scanr
defgeneric(OBJ, graccumulate2, _1, fun, ini, fin); // scanr with lookahead

// repeat, generate
defgeneric(OBJ, grepeat  , obj, num);
defgeneric(OBJ, ggenerate, fun, ini); // stops when fun return Nil

// all, any, count
defgeneric(OBJ, gall  , _1, fun); // fun should return TrueFalse
defgeneric(OBJ, gany  , _1, fun); // fun should return TrueFalse
defgeneric(U32, gcount, _1, fun); // fun should return TrueFalse

// sorting (fun must return Ordered)
defgeneric(OBJ, gsort    , _1, fun); // in place
defgeneric(OBJ, gisort   , _1, fun); // return an array of indexes/keys
defgeneric(OBJ, gisSorted, _1, fun); // return True or False

// linear search if fun _2 returns TrueFalse
// binary search if fun _2 returns Ordered (and it is sorted)
// return Nil if not found
defgeneric(OBJ, gfind   , _1, fun); // return object
defgeneric(OBJ, gifind  , _1, fun); // return res such that ggetAt(_1,res) get object
defgeneric(I32, gindexOf, _1, fun); // return index or -1 if not found

// seq-like algorithms
defgeneric(OBJ, gintersperse, _1, fun); // intersperse value when not Nil
defgeneric(OBJ, ggroup      , _1, fun); // group true then false (pair)
defgeneric(OBJ, gsplit      , _1, fun); // split when true
defgeneric(OBJ, gunique     , _1, fun); // remove contiguous equal elements

defgeneric(OBJ, gdiff       , _1, _2, fun); // _1 - _2 [asymmetric]
defgeneric(OBJ, gmerge      , _1, _2, fun); // _1 + _2 (requires sorted _1, _2)
defgeneric(OBJ, gmatch      , _1, _2, fun); // _2 - (_2 - _1) [asymmetric]
defgeneric(OBJ, gintersect  , _1, _2, fun); // _1 - (_1 - _2) [asymmetric]
  // note : gmatch(_1,_2) == gintersect(_2,_1), except for fun and complexity
#endif // COS_GEN_ALGORITHM_H


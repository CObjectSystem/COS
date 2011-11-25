#ifndef COS_GEN_COLLECTION_H
#define COS_GEN_COLLECTION_H

/**
 * C Object System
 * COS generics for collections
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

// check for elements
defgeneric(OBJ, gisEmpty, _1);

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

// reduce
defgeneric(OBJ, greduce , _1, fun);                // foldl1
defgeneric(OBJ, greduce1, _1, fun, ini);           // foldl
defgeneric(OBJ, greduce2, _1, fun, ini, fin);      // foldl with lookahead

// accumulate
defgeneric(OBJ, gaccumulate , _1, fun);            // scanl1
defgeneric(OBJ, gaccumulate1, _1, fun, ini);       // scanl
defgeneric(OBJ, gaccumulate2, _1, fun, ini, fin);  // scanl with lookahead

#endif // COS_GEN_COLLECTION_H

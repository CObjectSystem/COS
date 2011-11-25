#ifndef COS_GEN_RELOP_H
#define COS_GEN_RELOP_H

/**
 * C Object System
 * COS generic for relational operators
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

#include <cos/gen/op/GRelOp.h>

/* NOTE-USER: object comparison

   gcompare(a,b)
     | a < b     = Lesser
     | a > b     = Geater
     | otherwise = Equal

   gisEqual(a,b)
     | a == b    = True
     | otherwise = False

   gisLesser(a,b)
     | a < b     = True
     | otherwise = False

   gisGreater(a,b)
     | a > b     = True
     | otherwise = False
*/

// comparison
defgeneric(OBJ, (G_compare         ) gcompare         , _1, _2);
defgeneric(OBJ, (G_isEqual         ) gisEqual         , _1, _2);
defgeneric(OBJ, (G_isLesser        ) gisLesser        , _1, _2);
defgeneric(OBJ, (G_isGreater       ) gisGreater       , _1, _2);
defgeneric(OBJ, (G_isLesserOrEqual ) gisLesserOrEqual , _1, _2);
defgeneric(OBJ, (G_isGreaterOrEqual) gisGreaterOrEqual, _1, _2);
defgeneric(OBJ, (G_isNotEqual      ) gisNotEqual      , _1, _2);

// hash
defgeneric(U64, (G_hash) ghash, _1);

// min, max (fun should return Ordered or the min, max)
defgeneric(OBJ, (G_min ) gmin, _1, _2 or fun);
defgeneric(OBJ, (G_max ) gmax, _1, _2 or fun);

#endif // COS_GEN_RELOP_H

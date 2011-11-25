#ifndef COS_GEN_NUMOP_H
#define COS_GEN_NUMOP_H

/**
 * C Object System
 * COS generic for math operators
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

#include <cos/gen/op/GNumOp.h>

/* NOTE-USER: operators policy
   The policy of these messages is to return the operation result in a
   new autoDelete object resulting from the promotion/coercion of _1
   and _2 which follows the rules of C99 for primitive types.
*/
defgeneric(OBJ, (G_abs) gabs, _1);     // return |_1|    
defgeneric(OBJ, (G_neg) gneg, _1);     // return -_1    
defgeneric(OBJ, (G_sqr) gsqr, _1);     // return _1 * _1
defgeneric(OBJ, (G_inv) ginv, _1);     // return  1 / _1   
defgeneric(OBJ, (G_add) gadd, _1, _2); // return _1 + _2
defgeneric(OBJ, (G_sub) gsub, _1, _2); // return _1 - _2
defgeneric(OBJ, (G_mul) gmul, _1, _2); // return _1 * _2
defgeneric(OBJ, (G_div) gdiv, _1, _2); // return _1 / _2
defgeneric(OBJ, (G_pow) gpow, _1, _2); // return _1 ^ _2
defgeneric(OBJ, (G_mod) gmod, _1, _2); // return _1 % _2

/* NOTE-USER: operators policy
   The policy of these messages is to perform the operation 'in place'
   in _1 without any type promotion/coercion and return _1. Therefore if
   the types of _1 and _2 differ, some operations may not be available
   if they may induce a loss of information (e.g. gaddTo(Int,Long)).
*/
defgeneric(OBJ, (G_absolute) gabsolute, _1);     // return _1 = |_1| 
defgeneric(OBJ, (G_negate  ) gnegate  , _1);     // return _1 = -_1
defgeneric(OBJ, (G_square  ) gsquare  , _1);     // return _1 = _1 ^ 2
defgeneric(OBJ, (G_invert  ) ginvert  , _1);     // return _1 = 1 / _1
defgeneric(OBJ, (G_addTo   ) gaddTo   , _1, _2); // return _1 += _2 
defgeneric(OBJ, (G_subTo   ) gsubTo   , _1, _2); // return _1 -= _2 
defgeneric(OBJ, (G_mulBy   ) gmulBy   , _1, _2); // return _1 *= _2 
defgeneric(OBJ, (G_divBy   ) gdivBy   , _1, _2); // return _1 /= _2 
defgeneric(OBJ, (G_power   ) gpower   , _1, _2); // return _1 = _1 ^ _2
defgeneric(OBJ, (G_modulo  ) gmodulo  , _1, _2); // return _1 %= _2 

#endif // COS_GEN_NUMOP_H

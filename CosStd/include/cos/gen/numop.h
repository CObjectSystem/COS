#ifndef COS_GEN_NUMOP_H
#define COS_GEN_NUMOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generic for math operators
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
 | $Id: numop.h,v 1.3 2010/05/25 15:33:39 ldeniau Exp $
 |
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

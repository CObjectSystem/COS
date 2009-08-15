#ifndef COS_GEN_OPERATOR_H
#define COS_GEN_OPERATOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generic for operators (except logic) 
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
 | $Id: operator.h,v 1.6 2009/08/15 14:54:57 ldeniau Exp $
 |
*/

#include <cos/Generic.h>

/* NOTE-USER: operators policy
   The policy of these methods is to return the operation result in a
   new autoDelete object resulting from the promotion/coercion of _1
   and _2 which follows the rules of C99 for primitive types.
*/
defgeneric(OBJ, (GenOperator) gabs, _1);     // return |_1|    
defgeneric(OBJ, (GenOperator) gneg, _1);     // return -_1    
defgeneric(OBJ, (GenOperator) gsqr, _1);     // return _1 * _1   
defgeneric(OBJ, (GenOperator) ginv, _1);     // return 1/_1   
defgeneric(OBJ, (GenOperator) gadd, _1, _2); // return _1 + _2
defgeneric(OBJ, (GenOperator) gsub, _1, _2); // return _1 - _2
defgeneric(OBJ, (GenOperator) gmul, _1, _2); // return _1 * _2
defgeneric(OBJ, (GenOperator) gdiv, _1, _2); // return _1 / _2
defgeneric(OBJ, (GenOperator) gpow, _1, _2); // return _1 ** _2
defgeneric(OBJ, (GenOperator) gmod, _1, _2); // return _1 % _2

/* NOTE-USER: operators policy
   The policy of these methods is to perform the operation 'in place'
   in _1 without any type promotion/coercion and return _1. Therefore if
   the types of _1 and _2 differ, some operations may not be available
   if they may induce a loss of information (e.g. gaddTo(Int,Long)).
*/
defgeneric(OBJ, (GenOperator) gabsolute, _1);     // return _1 = |_1| 
defgeneric(OBJ, (GenOperator) gnegate  , _1);     // return _1 = -_1 
defgeneric(OBJ, (GenOperator) ginvert  , _1);     // return _1 = 1/_1
defgeneric(OBJ, (GenOperator) gaddTo   , _1, _2); // return _1 += _2 
defgeneric(OBJ, (GenOperator) gsubTo   , _1, _2); // return _1 -= _2 
defgeneric(OBJ, (GenOperator) gmulBy   , _1, _2); // return _1 *= _2 
defgeneric(OBJ, (GenOperator) gdivBy   , _1, _2); // return _1 /= _2 
defgeneric(OBJ, (GenOperator) gpower   , _1, _2); // return _1 = _1 ** _2
defgeneric(OBJ, (GenOperator) gmodulo  , _1, _2); // return _1 %= _2 

#endif // COS_GEN_OPERATOR_H

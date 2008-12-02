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
 | $Id: operator.h,v 1.2 2008/12/02 17:32:21 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

/* NOTE-USER: operators policy
   The policy of these methods is to return the operation result in a
   new autoReleased object resulting from the promotion/coercion of _1
   and _2 which follows the rules of C99 for primitive types.
*/
defgeneric(OBJ, gneg , _1);     // return -_1    
defgeneric(OBJ, ginv , _1);     // return 1/_1   
defgeneric(OBJ, gconj, _1);     // return _1^*   
defgeneric(OBJ, gadd , _1, _2); // return _1 + _2
defgeneric(OBJ, gsub , _1, _2); // return _1 - _2
defgeneric(OBJ, gmul , _1, _2); // return _1 * _2
defgeneric(OBJ, gdiv , _1, _2); // return _1 / _2
defgeneric(OBJ, gpow , _1, _2); // return _1 ** _2
defgeneric(OBJ, gmod , _1, _2); // return _1 % _2

/* NOTE-USER: operators policy
   The policy of these methods it to perform the operation 'in place'
   in _1 without any type promotion/coercion and return _1. Therefore if
   the types of _1 and _2 differ, some operations may not be available
   if they may induce a loss of information (e.g. gaddTo(Int,Long)).
*/
defgeneric(OBJ, gnegate   , _1);     // return _1 = -_1 
defgeneric(OBJ, ginvert   , _1);     // return _1 = 1/_1
defgeneric(OBJ, gconjugate, _1);     // return _1 = _1^*
defgeneric(OBJ, gaddTo    , _1, _2); // return _1 += _2 
defgeneric(OBJ, gsubTo    , _1, _2); // return _1 -= _2 
defgeneric(OBJ, gmulBy    , _1, _2); // return _1 *= _2 
defgeneric(OBJ, gdivBy    , _1, _2); // return _1 /= _2 
defgeneric(OBJ, gpower    , _1, _2); // return _1 = _1 ** _2
defgeneric(OBJ, gmodulo   , _1, _2); // return _1 %= _2 

#endif // COS_GEN_OPERATOR_H

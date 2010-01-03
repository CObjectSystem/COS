#ifndef COS_GOPERATOR_H
#define COS_GOPERATOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for operators
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
 | $Id: GOperator.h,v 1.1 2010/01/03 12:29:57 ldeniau Exp $
 |
*/

#include <cos/Object.h>

defclass(GOperator , Generic  ) endclass
defclass(GUnaryOp  , GOperator) endclass
defclass(GBinaryOp , GOperator) endclass
defclass(GTernaryOp, GOperator) endclass

#endif // COS_GOPERATOR_H

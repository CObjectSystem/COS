#ifndef COS_GEN_OP_GRELOP_H
#define COS_GEN_OP_GRELOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for relational operators
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
 | $Id: GRelOp.h,v 1.2 2010/01/03 12:38:48 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(GCompare       , GBinaryOp) endclass
defclass(GEqual         , GBinaryOp) endclass
defclass(GNotEqual      , GBinaryOp) endclass
defclass(GLesser        , GBinaryOp) endclass
defclass(GLesserOrEqual , GBinaryOp) endclass
defclass(GGreater       , GBinaryOp) endclass
defclass(GGreaterOrEqual, GBinaryOp) endclass

defclass(GMin           , GBinaryOp) endclass
defclass(GMax           , GBinaryOp) endclass

defclass(GHash          , GUnaryOp ) endclass

#endif // COS_GEN_OP_GRELOP_H

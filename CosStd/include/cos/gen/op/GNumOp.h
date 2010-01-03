#ifndef COS_GEN_OP_GMATHOP_H
#define COS_GEN_OP_GMATHOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for math operators
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
 | $Id: GNumOp.h,v 1.1 2010/01/03 14:56:05 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(GAbs     , GUnaryOp ) endclass
defclass(GNeg     , GUnaryOp ) endclass
defclass(GSqr     , GUnaryOp ) endclass
defclass(GInv     , GUnaryOp ) endclass
defclass(GAdd     , GBinaryOp) endclass
defclass(GSub     , GBinaryOp) endclass
defclass(GMul     , GBinaryOp) endclass
defclass(GDiv     , GBinaryOp) endclass
defclass(GPow     , GBinaryOp) endclass
defclass(GMod     , GBinaryOp) endclass

defclass(GAbsolute, GUnaryOp ) endclass
defclass(GNegate  , GUnaryOp ) endclass
defclass(GSquare  , GUnaryOp ) endclass
defclass(GInvert  , GUnaryOp ) endclass
defclass(GAddTo   , GBinaryOp) endclass
defclass(GSubTo   , GBinaryOp) endclass
defclass(GMulBy   , GBinaryOp) endclass
defclass(GDivBy   , GBinaryOp) endclass
defclass(GPower   , GBinaryOp) endclass
defclass(GModulo  , GBinaryOp) endclass

#endif // COS_GEN_OP_GMATHOP_H

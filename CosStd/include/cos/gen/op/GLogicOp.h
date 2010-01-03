#ifndef COS_GEN_OP_GLOGICOP_H
#define COS_GEN_OP_GLOGICOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for logic operators
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
 | $Id: GLogicOp.h,v 1.2 2010/01/03 12:38:48 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(GNot    , GUnaryOp ) endclass
defclass(GAnd    , GBinaryOp) endclass
defclass(GOr     , GBinaryOp) endclass
defclass(GXOr    , GBinaryOp) endclass
defclass(GImplies, GBinaryOp) endclass

#endif // COS_GEN_OP_GLOGICOP_H

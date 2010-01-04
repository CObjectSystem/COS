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
 | $Id: GNumOp.h,v 1.2 2010/01/04 09:59:01 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(G_abs     , GUnaryOp ) endclass
defclass(G_neg     , GUnaryOp ) endclass
defclass(G_sqr     , GUnaryOp ) endclass
defclass(G_inv     , GUnaryOp ) endclass
defclass(G_add     , GBinaryOp) endclass
defclass(G_sub     , GBinaryOp) endclass
defclass(G_mul     , GBinaryOp) endclass
defclass(G_div     , GBinaryOp) endclass
defclass(G_pow     , GBinaryOp) endclass
defclass(G_mod     , GBinaryOp) endclass

defclass(G_absolute, GUnaryOp ) endclass
defclass(G_negate  , GUnaryOp ) endclass
defclass(G_square  , GUnaryOp ) endclass
defclass(G_invert  , GUnaryOp ) endclass
defclass(G_addTo   , GBinaryOp) endclass
defclass(G_subTo   , GBinaryOp) endclass
defclass(G_mulBy   , GBinaryOp) endclass
defclass(G_divBy   , GBinaryOp) endclass
defclass(G_power   , GBinaryOp) endclass
defclass(G_modulo  , GBinaryOp) endclass

#endif // COS_GEN_OP_GMATHOP_H

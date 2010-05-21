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
 | $Id: GNumOp.h,v 1.3 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(G_abs     , G_UnaryOp ) endclass
defclass(G_neg     , G_UnaryOp ) endclass
defclass(G_sqr     , G_UnaryOp ) endclass
defclass(G_inv     , G_UnaryOp ) endclass
defclass(G_add     , G_BinaryOp) endclass
defclass(G_sub     , G_BinaryOp) endclass
defclass(G_mul     , G_BinaryOp) endclass
defclass(G_div     , G_BinaryOp) endclass
defclass(G_pow     , G_BinaryOp) endclass
defclass(G_mod     , G_BinaryOp) endclass

defclass(G_absolute, G_UnaryOp ) endclass
defclass(G_negate  , G_UnaryOp ) endclass
defclass(G_square  , G_UnaryOp ) endclass
defclass(G_invert  , G_UnaryOp ) endclass
defclass(G_addTo   , G_BinaryOp) endclass
defclass(G_subTo   , G_BinaryOp) endclass
defclass(G_mulBy   , G_BinaryOp) endclass
defclass(G_divBy   , G_BinaryOp) endclass
defclass(G_power   , G_BinaryOp) endclass
defclass(G_modulo  , G_BinaryOp) endclass

#endif // COS_GEN_OP_GMATHOP_H

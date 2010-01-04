#ifndef COS_GEN_OP_GFLOATOP_H
#define COS_GEN_OP_GFLOATOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for float operators
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
 | $Id: GFloatOp.h,v 1.4 2010/01/04 09:59:01 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(G_conj       , GUnaryOp  ) endclass
defclass(G_arg        , GUnaryOp  ) endclass
defclass(G_exp        , GUnaryOp  ) endclass
defclass(G_log        , GUnaryOp  ) endclass
defclass(G_sqrt       , GUnaryOp  ) endclass
defclass(G_cos        , GUnaryOp  ) endclass
defclass(G_sin        , GUnaryOp  ) endclass
defclass(G_tan        , GUnaryOp  ) endclass
defclass(G_acos       , GUnaryOp  ) endclass
defclass(G_asin       , GUnaryOp  ) endclass
defclass(G_atan       , GUnaryOp  ) endclass
defclass(G_cosh       , GUnaryOp  ) endclass
defclass(G_sinh       , GUnaryOp  ) endclass
defclass(G_tanh       , GUnaryOp  ) endclass
defclass(G_acosh      , GUnaryOp  ) endclass
defclass(G_asinh      , GUnaryOp  ) endclass
defclass(G_atanh      , GUnaryOp  ) endclass
defclass(G_hypot      , GBinaryOp ) endclass
defclass(G_subSqr     , GBinaryOp ) endclass
defclass(G_mulAdd     , GTernaryOp) endclass

defclass(G_conjugate  , GUnaryOp  ) endclass
defclass(G_argument   , GUnaryOp  ) endclass
defclass(G_exponential, GUnaryOp  ) endclass
defclass(G_logarithm  , GUnaryOp  ) endclass
defclass(G_sqroot     , GUnaryOp  ) endclass
defclass(G_cosine     , GUnaryOp  ) endclass
defclass(G_sine       , GUnaryOp  ) endclass
defclass(G_tangent    , GUnaryOp  ) endclass
defclass(G_acosine    , GUnaryOp  ) endclass
defclass(G_asine      , GUnaryOp  ) endclass
defclass(G_atangent   , GUnaryOp  ) endclass
defclass(G_cosineh    , GUnaryOp  ) endclass
defclass(G_sineh      , GUnaryOp  ) endclass
defclass(G_tangenth   , GUnaryOp  ) endclass
defclass(G_acosineh   , GUnaryOp  ) endclass
defclass(G_asineh     , GUnaryOp  ) endclass
defclass(G_atangenth  , GUnaryOp  ) endclass
defclass(G_hypotenuse , GBinaryOp ) endclass

#endif // COS_GEN_OP_GFLOATOP_H

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
 | $Id: GFloatOp.h,v 1.5 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(G_conj       , G_UnaryOp  ) endclass
defclass(G_arg        , G_UnaryOp  ) endclass
defclass(G_exp        , G_UnaryOp  ) endclass
defclass(G_log        , G_UnaryOp  ) endclass
defclass(G_sqrt       , G_UnaryOp  ) endclass
defclass(G_cos        , G_UnaryOp  ) endclass
defclass(G_sin        , G_UnaryOp  ) endclass
defclass(G_tan        , G_UnaryOp  ) endclass
defclass(G_acos       , G_UnaryOp  ) endclass
defclass(G_asin       , G_UnaryOp  ) endclass
defclass(G_atan       , G_UnaryOp  ) endclass
defclass(G_cosh       , G_UnaryOp  ) endclass
defclass(G_sinh       , G_UnaryOp  ) endclass
defclass(G_tanh       , G_UnaryOp  ) endclass
defclass(G_acosh      , G_UnaryOp  ) endclass
defclass(G_asinh      , G_UnaryOp  ) endclass
defclass(G_atanh      , G_UnaryOp  ) endclass
defclass(G_hypot      , G_BinaryOp ) endclass
defclass(G_subSqr     , G_BinaryOp ) endclass
defclass(G_mulAdd     , G_TernaryOp) endclass

defclass(G_conjugate  , G_UnaryOp  ) endclass
defclass(G_argument   , G_UnaryOp  ) endclass
defclass(G_exponential, G_UnaryOp  ) endclass
defclass(G_logarithm  , G_UnaryOp  ) endclass
defclass(G_sqroot     , G_UnaryOp  ) endclass
defclass(G_cosine     , G_UnaryOp  ) endclass
defclass(G_sine       , G_UnaryOp  ) endclass
defclass(G_tangent    , G_UnaryOp  ) endclass
defclass(G_acosine    , G_UnaryOp  ) endclass
defclass(G_asine      , G_UnaryOp  ) endclass
defclass(G_atangent   , G_UnaryOp  ) endclass
defclass(G_cosineh    , G_UnaryOp  ) endclass
defclass(G_sineh      , G_UnaryOp  ) endclass
defclass(G_tangenth   , G_UnaryOp  ) endclass
defclass(G_acosineh   , G_UnaryOp  ) endclass
defclass(G_asineh     , G_UnaryOp  ) endclass
defclass(G_atangenth  , G_UnaryOp  ) endclass
defclass(G_hypotenuse , G_BinaryOp ) endclass

#endif // COS_GEN_OP_GFLOATOP_H

#ifndef COS_GEN_OP_GFLOATOP_H
#define COS_GEN_OP_GFLOATOP_H

/**
 * C Object System
 * COS Generic classes for float operators
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
defclass(G_sqrErr     , G_BinaryOp ) endclass
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

#endif // COS_GEN_OP_GFLOATOP_H

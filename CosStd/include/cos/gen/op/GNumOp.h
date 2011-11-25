#ifndef COS_GEN_OP_GMATHOP_H
#define COS_GEN_OP_GMATHOP_H

/**
 * C Object System
 * COS Generic classes for math operators
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

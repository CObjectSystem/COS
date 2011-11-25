#ifndef COS_GEN_OP_GRELOP_H
#define COS_GEN_OP_GRELOP_H

/**
 * C Object System
 * COS Generic classes for relational operators
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

defclass(G_compare         , G_BinaryOp) endclass
defclass(G_isEqual         , G_BinaryOp) endclass
defclass(G_isNotEqual      , G_BinaryOp) endclass
defclass(G_isLesser        , G_BinaryOp) endclass
defclass(G_isLesserOrEqual , G_BinaryOp) endclass
defclass(G_isGreater       , G_BinaryOp) endclass
defclass(G_isGreaterOrEqual, G_BinaryOp) endclass

defclass(G_min             , G_BinaryOp) endclass
defclass(G_max             , G_BinaryOp) endclass

defclass(G_hash            , G_UnaryOp ) endclass

#endif // COS_GEN_OP_GRELOP_H

#ifndef COS_GEN_OP_GLOGICOP_H
#define COS_GEN_OP_GLOGICOP_H

/**
 * C Object System
 * COS Generic classes for logic operators
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

defclass(G_not    , G_UnaryOp ) endclass
defclass(G_and    , G_BinaryOp) endclass
defclass(G_or     , G_BinaryOp) endclass
defclass(G_xor    , G_BinaryOp) endclass
defclass(G_implies, G_BinaryOp) endclass

#endif // COS_GEN_OP_GLOGICOP_H

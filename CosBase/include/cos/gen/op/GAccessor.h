#ifndef COS_GEN_OP_GACCESSOR_H
#define COS_GEN_OP_GACCESSOR_H

/**
 * C Object System
 * COS Generic classes for accessors
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

#include <cos/Object.h>

// Generic is a core class, see cos/cos/coscls.h

defclass(G_Accessor, Generic   ) endclass
defclass(G_getAt   , G_Accessor) endclass
defclass(G_putAt   , G_Accessor) endclass
defclass(G_getAtIdx, G_Accessor) endclass
defclass(G_putAtIdx, G_Accessor) endclass
defclass(G_getAtKey, G_Accessor) endclass
defclass(G_putAtKey, G_Accessor) endclass

#endif // COS_GEN_OP_GACCESSOR_H

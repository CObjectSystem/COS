#ifndef COS_GEN_LOGICOP_H
#define COS_GEN_LOGICOP_H

/**
 * C Object System
 * COS generic logical operators
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

#include <cos/gen/op/GLogicOp.h>

defgeneric(OBJ, (G_not    ) gnot    , _1);
defgeneric(OBJ, (G_and    ) gand    , _1, _2);
defgeneric(OBJ, (G_or     ) gor     , _1, _2);
defgeneric(OBJ, (G_xor    ) gxor    , _1, _2); // not (_1 isEqual _2)
defgeneric(OBJ, (G_implies) gimplies, _1, _2); // (not _1) or _2

#endif // COS_GEN_LOGICOP_H

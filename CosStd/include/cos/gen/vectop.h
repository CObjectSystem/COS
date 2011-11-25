#ifndef COS_GEN_VECTOP_H
#define COS_GEN_VECTOP_H

/**
 * C Object System
 * COS generic for (extra) vector operators
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

#include <cos/gen/op/GVectOp.h>

defgeneric(OBJ, (G_sum ) gsum , _1);
defgeneric(OBJ, (G_prod) gprod, _1);

#endif // COS_GEN_VECTOP_H

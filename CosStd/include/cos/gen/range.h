#ifndef COS_GEN_RANGE_H
#define COS_GEN_RANGE_H

/**
 * C Object System
 * COS generics for ranges and slices
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

// new (no 'init' for final classes)
defgeneric(OBJ, gnewSlc , _1, (I32)start, (U32)size, (I32)stride);
defgeneric(OBJ, gnewRng , _1, (I32)start, (I32)end , (I32)stride);
defgeneric(OBJ, gnewXRng, _1, (F64)start, (F64)end , (F64)stride);

#endif // COS_GEN_RANGE_H

#ifndef COS_GEN_ACCESSOR_H
#define COS_GEN_ACCESSOR_H

/**
 * C Object System
 * COS accessor generics
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

#include <cos/gen/op/GAccessor.h>

// getters, setters, properties, keys, etc...
defgeneric(OBJ, (G_getAt)    ggetAt   , _1, at);
defgeneric(OBJ, (G_putAt)    gputAt   , _1, at, what);

// common case for indexes
defgeneric(OBJ, (G_getAtIdx) ggetAtIdx, _1, (I32)idx);
defgeneric(OBJ, (G_putAtIdx) gputAtIdx, _1, (I32)idx, what);

// common case for strings
defgeneric(OBJ, (G_getAtKey) ggetAtKey, _1, (STR)key);
defgeneric(OBJ, (G_putAtKey) gputAtKey, _1, (STR)key, what);

#endif // COS_GEN_ACCESSOR_H

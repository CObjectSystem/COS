#ifndef GENERICS_H
#define GENERICS_H

/**
 * C Object System
 * COS example01 -- generics
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

#ifndef COS_NOCOS
#include <cos/gen/object.h>
#include <cos/gen/init.h>
#endif

defgeneric(void, gprint, _1, _2);

#endif


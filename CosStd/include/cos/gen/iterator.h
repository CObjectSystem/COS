#ifndef COS_GEN_ITERATOR_H
#define COS_GEN_ITERATOR_H

/**
 * C Object System
 * COS generics for iterators
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

defgeneric(OBJ, giterator   , _1);
defgeneric(OBJ, grevIterator, _1); // reverse iterator
defgeneric(OBJ, gnext       , _1);
defgeneric(OBJ, gallNext    , _1); // return an array of remaining objects

#endif // COS_GEN_ITERATOR_H

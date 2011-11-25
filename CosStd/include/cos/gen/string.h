#ifndef COS_GEN_STRING_H
#define COS_GEN_STRING_H

/**
 * C Object System
 * COS generics for strings
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

// return True or False
defgeneric(OBJ, gisAlnum , _1);
defgeneric(OBJ, gisAlpha , _1);
defgeneric(OBJ, gisBlank , _1);
defgeneric(OBJ, gisCntrl , _1);
defgeneric(OBJ, gisDigit , _1);
defgeneric(OBJ, gisGraph , _1);
defgeneric(OBJ, gisLower , _1);
defgeneric(OBJ, gisPrint , _1);
defgeneric(OBJ, gisPunct , _1);
defgeneric(OBJ, gisSpace , _1);
defgeneric(OBJ, gisUpper , _1);
defgeneric(OBJ, gisXDigit, _1);

// in place
defgeneric(OBJ, gtoLower , _1);
defgeneric(OBJ, gtoUpper , _1);

// remove heading and trailing white spaces
defgeneric(OBJ, gstrip   , _1);

#endif // COS_GEN_STRING_H

#ifndef COS_NIL_H
#define COS_NIL_H

/**
 * C Object System
 * COS Nil (root class)
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

/* NOTE-USER: Nil behavior

   Nil and classes deriving from Nil cannot have instance, also called
   class-objects from which properties and predicates derive.
   
   Use Nil (instead of 0) if you mean "no-object".
   Remember, message cannot be sent to (OBJ)0, but it can to Nil.
   
   Use Null (instead of Nil or 0) if you mean "no-data" object.
*/

defclass(Nil, _)
endclass

#endif // COS_NIL_H

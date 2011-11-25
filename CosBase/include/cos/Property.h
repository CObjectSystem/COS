#ifndef COS_PROPERTY_H
#define COS_PROPERTY_H

/**
 * C Object System
 * COS Property
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

#include <cos/Nil.h>

#ifndef COS_GEN_ACCESSOR_H
#include <cos/gen/accessor.h>
#endif

/* NOTE-USER: Property

   Property is the "root" class of all properties. Properties are classes
   deriving from the class Property usually with name prefixed by P_.
   Using the property 'name' is equivalent to use the class 'P_name'.
   
   Properties are useful for KVC (Key-Value Coding) which allows to use
   any object as an associative collection, as well as for serialization,
   attributes introspection and scripting.
*/

defclass(Property, Nil)
endclass

#endif // COS_PROPERTY_H

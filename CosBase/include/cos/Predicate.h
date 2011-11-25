#ifndef COS_PREDICATE_H
#define COS_PREDICATE_H

/**
 * C Object System
 * COS Predicate
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

/* NOTE-USER: Predicate

   Predicate is the "root" class of all predicate classes.
      
   Predicate classes are useful for dispatching on result of predicates
   like gisKindOf, gisEqual or gcompare. This allow automatic branching
   of execution flow based on results as well as storing predicates
   results as objects.
*/

defclass(Predicate, Nil)
endclass

#endif // COS_PREDICATE_H

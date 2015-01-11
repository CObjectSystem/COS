#ifndef COS_SEQUENCE_H
#define COS_SEQUENCE_H

/**
 * C Object System
 * COS Sequence
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

#include <cos/Collection.h>

defclass(Sequence, Collection)
endclass

defclass(ValueSequence, Sequence)
endclass

#ifndef SEQUENCE_GROWTH_RATE
#define SEQUENCE_GROWTH_RATE 1618 // golden ratio * 1000
#endif

#ifndef SEQUENCE_MIN_SIZE
#define SEQUENCE_MIN_SIZE 256     // dynamic sequence starting size
#endif

U32 Sequence_enlargeCapacity(U32 capacity, U32 extra);

/***********************************************************
 * Implementation (private)
 */

/* NOTE-INFO: Sized Name
   Many sequences in COS provide "size-aware" types.
   Sequence_SizedName build a type name by suffixing the type by the size
   If the size of (__VA_ARGS__) >= S, then suffix from N is used.
   Sequence_SizedName(Array,10,N,obj1,obj2,obj3) -> Array3 (with size == 3)
   Sequence_SizedName(Array,10,N,obj1,..,obj10)  -> ArrayN (with size == 10)
   Sequence_SizedName(Array,2,Long,obj1,obj2) -> ArrayLong (with size == 2)
*/

#define Sequence_SizedName(T,S,N,...) \
        COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),S)) \
                  (COS_PP_CAT(T,N), COS_PP_CAT_NARG(T,__VA_ARGS__))

#endif // COS_SEQUENCE_H


/**
 * C Object System
 * COS Method
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
#include <cos/Method.h>

// ----- 

makclass(Method);

makclass(Method1, Method);
makclass(Method2, Method);
makclass(Method3, Method);
makclass(Method4, Method);
makclass(Method5, Method);

// ----- 

STATIC_ASSERT(Method1_vs_Method2__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method1,Method2,fct)
           && COS_FIELD_COMPATIBILITY(Method1,Method2,cls[0]) );

STATIC_ASSERT(Method2_vs_Method3__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method2,Method3,fct)
           && COS_FIELD_COMPATIBILITY(Method2,Method3,cls[0])
           && COS_FIELD_COMPATIBILITY(Method2,Method3,cls[1]) );

STATIC_ASSERT(Method3_vs_Method4__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method3,Method4,fct)
           && COS_FIELD_COMPATIBILITY(Method3,Method4,cls[0])
           && COS_FIELD_COMPATIBILITY(Method3,Method4,cls[1])
           && COS_FIELD_COMPATIBILITY(Method3,Method4,cls[2]) );

STATIC_ASSERT(Method4_vs_Method5__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method4,Method5,fct)
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[0])
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[1])
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[2])
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[3]) );

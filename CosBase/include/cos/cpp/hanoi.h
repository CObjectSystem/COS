#ifndef COS_CPP_HANOI_H
#define COS_CPP_HANOI_H

/**
 * C Object System
 * COS - Hanoi tower game
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

#include <cos/cpp/cpp.h>

/* NOTE-USER: COS_PP_HANOI(N) returns the list of moves for n disks
   ex: COS_PP_HANOI(2)  -> ((1,2),(1,3),(2,3))
       COS_PP_HANOI(3)  -> ((1,3),(1,2),(3,2),(1,3),(2,1),(2,3),(1,3))
       COS_PP_HANOI(16) -> (.. 65535 moves ..)
       COS_PP_HANOI(20) -> (.. 1048575 moves ..)
                           after 45s on my Pentium-M 1.5Ghz with gcc 4.1.1
 */

#define COS_PP_HANOI(n) \
        COS_PP_CAT(COS_PP_HANOI_,n)(1,2,3)

#define COS_PP_HANOI_0( L,C,R)                                     (   )
#define COS_PP_HANOI_1( L,C,R)                                    ((L,R))
#define COS_PP_HANOI_2( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_1( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_1( C,L,R)))
#define COS_PP_HANOI_3( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_2( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_2( C,L,R)))
#define COS_PP_HANOI_4( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_3( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_3( C,L,R)))
#define COS_PP_HANOI_5( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_4( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_4( C,L,R)))
#define COS_PP_HANOI_6( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_5( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_5( C,L,R)))
#define COS_PP_HANOI_7( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_6( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_6( C,L,R)))
#define COS_PP_HANOI_8( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_7( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_7( C,L,R)))
#define COS_PP_HANOI_9( L,C,R) (COS_PP_SEQ(COS_PP_HANOI_8( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_8( C,L,R)))
#define COS_PP_HANOI_10(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_9( L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_9( C,L,R)))
#define COS_PP_HANOI_11(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_10(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_10(C,L,R)))
#define COS_PP_HANOI_12(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_11(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_11(C,L,R)))
#define COS_PP_HANOI_13(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_12(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_12(C,L,R)))
#define COS_PP_HANOI_14(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_13(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_13(C,L,R)))
#define COS_PP_HANOI_15(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_14(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_14(C,L,R)))
#define COS_PP_HANOI_16(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_15(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_15(C,L,R)))
#define COS_PP_HANOI_17(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_16(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_16(C,L,R)))
#define COS_PP_HANOI_18(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_17(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_17(C,L,R)))
#define COS_PP_HANOI_19(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_18(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_18(C,L,R)))
#define COS_PP_HANOI_20(L,C,R) (COS_PP_SEQ(COS_PP_HANOI_19(L,R,C)),(L,R),COS_PP_SEQ(COS_PP_HANOI_19(C,L,R)))

#endif // COS_CPP_HANOI_H

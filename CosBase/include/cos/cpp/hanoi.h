#ifndef COS_CPP_HANOI_H
#define COS_CPP_HANOI_H

/*
 o---------------------------------------------------------------------o
 |
 | C Object System -- Hanoi Tower game
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: hanoi.h,v 1.1 2009/10/05 18:46:19 ldeniau Exp $
 |
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

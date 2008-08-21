#ifndef COS_RANGE_H
#define COS_RANGE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Range
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
 | $Id: Range.h,v 1.2 2008/08/21 15:53:43 ldeniau Exp $
 |
*/

#include <cos/Value.h>

// ----- definitions

/* NOTE-USER: negative indexes
   negative indexes mean starting from the end
   e.g. -1 is the last element
 */

defclass(Range,Value)
endclass

defclass(Range1,Range)
  S32 start;
  U32 size;
endclass

defclass(Range2,Range)
  S32 start [2];
  U32 size  [2];
endclass

defclass(Range3,Range)
  S32 start [3];
  U32 size  [3];
endclass

defclass(Range4,Range)
  S32 start [4];
  U32 size  [4];
endclass

defclass(Range5,Range)
  S32 start [5];
  U32 size  [5];
endclass

// ----- automatic constructors

#define aRange(starts,sizes) \
        aRangeN(COS_PP_IF(COS_PP_ISTUPLE(starts))(COS_PP_NARG starts,1), \
                starts,sizes)

#define aRangeN(N,starts,sizes) ( (OBJ)&(struct COS_PP_CAT(Range,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(Range,N)).Behavior.id, COS_RC_AUTO }}}}, \
         COS_PP_IF(COS_PP_ISONE(N))(starts, { COS_PP_SEQ(starts) }), \
         COS_PP_IF(COS_PP_ISONE(N))(sizes , { COS_PP_SEQ(sizes)  }) } )

#endif // COS_RANGE_H

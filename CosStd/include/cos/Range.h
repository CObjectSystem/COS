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
 | $Id: Range.h,v 1.2 2008/10/31 15:19:44 ldeniau Exp $
 |
*/

#define ONLY__COS_VALUE_H
#include <cos/Value.h>

// ----- definitions

/* NOTE-USER: indexing policy
   indexing starts at zero
   negative indexes mean starting from the end
   bounds are included
   e.g. 0 is the first element, -1 is the last element
 */

defclass(Range, Value)
endclass

defclass(Range1,Range)
  I32 start;
  I32 end;
  I32 stride;
endclass

defclass(Range2,Range)
  I32 start [2];
  I32 end   [2];
  I32 stride[2];
endclass

defclass(Range3,Range)
  I32 start [3];
  I32 end   [3];
  I32 stride[3];
endclass

defclass(Range4,Range)
  I32 start [4];
  I32 end   [4];
  I32 stride[4];
endclass

defclass(Range5,Range)
  I32 start [5];
  I32 end   [5];
  I32 stride[5];
endclass

// ----- automatic constructors

#define aRange(...)  ( (OBJ)atRange(__VA_ARGS__) )
#define atRange(...) COS_PP_CAT_NARG(atRange_, __VA_ARGS__)(__VA_ARGS__)

#define atRange_2(starts,ends) \
        atRange_3(starts,ends, \
                 COS_PP_IF(COS_PP_ISTUPLE(starts))( \
                  (COS_PP_DUPSEQ(COS_PP_LEN(starts),1)),1))

#define atRange_3(starts,ends,strides) \
        atRangeN(COS_PP_IF(COS_PP_ISTUPLE(starts))(COS_PP_LEN(starts),1), \
                 starts,ends,strides)

#define atRangeN(N,starts,ends,strides) ( &(struct COS_PP_CAT(Range,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(Range,N)).Behavior.id, COS_RC_AUTO }}}}, \
         COS_PP_IF(COS_PP_ISONE(N))(starts , { COS_PP_SEQ(starts ) }), \
         COS_PP_IF(COS_PP_ISONE(N))(ends   , { COS_PP_SEQ(ends   ) }), \
         COS_PP_IF(COS_PP_ISONE(N))(strides, { COS_PP_SEQ(strides) }) } )

#endif // COS_RANGE_H

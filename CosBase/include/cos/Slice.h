#ifndef COS_SLICE_H
#define COS_SLICE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Slice
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
 | $Id: Slice.h,v 1.2 2008/07/02 17:08:57 ldeniau Exp $
 |
*/

#include <cos/Value.h>

// ----- definitions

defclass(Slice,Value)
endclass

defclass(Slice1,Slice)
  U32 start;
  U32 size;
  U32 stride;
endclass

defclass(Slice2,Slice)
  U32 start;
  U32 size  [2];
  U32 stride[2];
endclass

defclass(Slice3,Slice)
  U32 start;
  U32 size  [3];
  U32 stride[3];
endclass

defclass(Slice4,Slice)
  U32 start;
  U32 size  [4];
  U32 stride[4];
endclass

defclass(Slice5,Slice)
  U32 start;
  U32 size  [5];
  U32 stride[5];
endclass

// ----- index linearization

static inline U32
slice1_index(struct Slice1* s, U32 i1) {
  return s->start + i1 * s->stride;
}

static inline U32
slice2_index(struct Slice2* s, U32 i1, U32 i2) {
  return s->start + i1 * s->stride[0] + i2 * s->stride[1];
}

static inline U32
slice3_index(struct Slice3* s, U32 i1, U32 i2, U32 i3) {
  return s->start + i1 * s->stride[0] + i2 * s->stride[1] + i3 * s->stride[2];
}

static inline U32
slice4_index(struct Slice4* s, U32 i1, U32 i2, U32 i3, U32 i4) {
  return s->start + i1 * s->stride[0] + i2 * s->stride[1] + i3 * s->stride[2]
                  + i4 * s->stride[3];
}

static inline U32
slice5_index(struct Slice5* s, U32 i1, U32 i2, U32 i3, U32 i4, U32 i5) {
  return s->start + i1 * s->stride[0] + i2 * s->stride[1] + i3 * s->stride[2]
                  + i4 * s->stride[3] + i5 * s->stride[4];
}

// ----- automatic constructors

#define aSlice(start,sizes,strides) \
        aSlice_(COS_PP_IF(COS_PP_ISTUPLE(sizes))(COS_PP_NARG sizes,1), \
                start,sizes,strides)

#define aSlice_(N,start,sizes,strides) ( (OBJ)&(struct COS_PP_CAT(Slice,N)) { \
        {{{ COS_CLS_NAME(COS_PP_CAT(Slice,N)).Behavior.id, COS_RC_AUTO }}}, \
         start, \
         COS_PP_IF(COS_PP_ISONE(N))(sizes  , { COS_PP_SEQ(sizes)   }), \
         COS_PP_IF(COS_PP_ISONE(N))(strides, { COS_PP_SEQ(strides) }) } )

#endif // COS_SLICE_H

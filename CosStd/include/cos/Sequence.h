#ifndef COS_SEQUENCE_H
#define COS_SEQUENCE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Sequence
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
 | $Id: Sequence.h,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Value.h>

// ----- definitions

defclass(Sequence, Value)
endclass

defclass(Sequence1, Sequence)
  R64 start ;
  R64 stride;
  U32 size  ;
endclass

defclass(Sequence2, Sequence)
  R64 start;
  R64 stride[2];
  U32 size  [2];
endclass

defclass(Sequence3, Sequence)
  R64 start;
  R64 stride[3];
  U32 size  [3];
endclass

defclass(Sequence4, Sequence)
  R64 start;
  R64 stride[4];
  U32 size  [4];
endclass

defclass(Sequence5, Sequence)
  R64 start;
  R64 stride[5];
  U32 size  [5];
endclass

// ----- evaluation

static inline R64
Sequence1_eval(struct Sequence1 *s, U32 i0) {
  return s->start + i0 * s->stride;
}

static inline R64
Sequence2_eval(struct Sequence2 *s, U32 i0, U32 i1) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1];
}

static inline R64
Sequence3_eval(struct Sequence3 *s, U32 i0, U32 i1, U32 i2) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1] + i2 * s->stride[2];
}

static inline R64
Sequence4_eval(struct Sequence4 *s, U32 i0, U32 i1, U32 i2, U32 i3) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1] + i2 * s->stride[2]
                  + i3 * s->stride[3];
}

static inline R64
Sequence5_eval(struct Sequence5 *s, U32 i0, U32 i1, U32 i2, U32 i3, U32 i4) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1] + i2 * s->stride[2]
                  + i3 * s->stride[3] + i4 * s->stride[4];
}

// ----- size

static inline U32
Sequence1_size(struct Sequence1 *s) {
  return s->size;
}

static inline U32
Sequence2_size(struct Sequence2 *s) {
  return s->size[0] * s->size[1];
}

static inline U32
Sequence3_size(struct Sequence3 *s) {
  return s->size[0] * s->size[1] * s->size[2];
}

static inline U32
Sequence4_size(struct Sequence4 *s) {
  return s->size[0] * s->size[1] * s->size[2] * s->size[3];
}

static inline U32
Sequence5_size(struct Sequence5 *s) {
  return s->size[0] * s->size[1] * s->size[2] * s->size[3] * s->size[4];
}

// ----- automatic constructors

#define aSequence(...)  ( (OBJ)atSequence(__VA_ARGS__) )
#define atSequence(...) COS_PP_CAT_NARG(atSequence_, __VA_ARGS__)(__VA_ARGS__)

#define atSequence_2(start,sizes) \
        atSequence_3(start,sizes, \
          COS_PP_IF(COS_PP_ISTUPLE(sizes))( \
            (COS_PP_DUPSEQ(COS_PP_LEN(sizes),1)),1))

#define atSequence_3(start,sizes,strides) \
        atSequenceN(COS_PP_IF(COS_PP_ISTUPLE(sizes))(COS_PP_LEN(sizes),1), \
                    start,ends,strides)

#define atSequenceN(N,start,sizes,strides) ( &(struct COS_PP_CAT(Sequence,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(Sequence,N)).Behavior.id, COS_RC_AUTO }}}}, \
         start, \
         COS_PP_IF(COS_PP_ISONE(N))(strides, { COS_PP_SEQ(strides) }), \
         COS_PP_IF(COS_PP_ISONE(N))(sizes  , { COS_PP_SEQ(sizes  ) }) } )

#endif // COS_SEQUENCE_H

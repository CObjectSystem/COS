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
 | $Id: Range.h,v 1.5 2009/02/27 20:14:25 ldeniau Exp $
 |
*/

#include <cos/Value.h>

#ifndef COS_SEQUENCE_H
#include <cos/Sequence.h>
#endif

defclass(Range, Value)
  I32 start;
  I32 end;
  I32 stride;
endclass

defclass(Slice, Value)
  U32 start;
  U32 size;
  I32 stride;
endclass

// ----- automatic constructors

#define aRange(...)  ( (OBJ)atRange(__VA_ARGS__) )
#define aSlice(...)  ( (OBJ)atSlice(__VA_ARGS__) )

#define atRange(...) COS_PP_CAT_NARG(atRange,__VA_ARGS__)(__VA_ARGS__)
#define atSlice(...) COS_PP_CAT_NARG(atSlice,__VA_ARGS__)(__VA_ARGS__)

// ----- automatic constructors shortcuts

#ifndef COS_NOSHORTCUT

#define aRng(...)  aRange(__VA_ARGS__)
#define aSlc(...)  aSlice(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

#define atRange1(end) \
        atRange2(0,end)

#define atRange2(start,end) \
        atRange3(start,end,1)

#define atRange3(start,end,stride) \
  ( &(struct Range){ \
    {{ COS_CLS_NAME(Range).Behavior.id, COS_RC_AUTO }}, \
    start, end, stride })

// ---

#define atSlice1(size) \
        atSlice2(0,size)

#define atSlice2(start,size) \
        atSlice3(start,size,1)

#define atSlice3(start,size,stride) \
  ( &(struct Slice){ \
    {{ COS_CLS_NAME(Slice).Behavior.id, COS_RC_AUTO }}, \
    start, size, stride })

// --- inliners

static inline U32
Slice_size(struct Slice *s) {
  return s->size;
}

static inline U32
Slice_eval(struct Slice *s, U32 i) {
  return s->start + i * s->stride;
}

static inline U32
Slice_first(struct Slice *s) {
  return s->start;
}

static inline U32
Slice_last(struct Slice *s) {
  return Slice_eval(s, s->size-1);
}

static inline U32
Slice_end(struct Slice *s) {
  return Slice_eval(s, s->size);
}

static inline BOOL
Slice_isValid(struct Slice *s) {
  return s->stride != 0;
}

static inline BOOL
Slice_isContiguous(struct Slice *s) {
  return s->stride == 1;
}

static inline struct Slice*
Slice_fromRange(struct Slice *s, struct Range *r, U32 size)
{
  U32 start = index_abs(r->start, size);
  U32 end   = index_abs(r->end  , size);

  s->size   = (end - start + r->stride) / r->stride;
  s->stride = r->stride;
  s->start  = start;

  return s;  
}

#endif // COS_RANGE_H

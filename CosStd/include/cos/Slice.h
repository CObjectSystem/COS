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
 | $Id: Slice.h,v 1.9 2009/06/19 23:57:27 ldeniau Exp $
 |
*/

/* NOTE-USER: Range and Slice
   Ranges are almost always converted to Slices before being used
*/

#include <cos/Range.h>

#ifndef COS_SEQUENCE_H
#include <cos/Sequence.h>
#endif

defclass(Slice, Value)
  I32 start;
  U32 size;
  I32 stride;
endclass

// ----- automatic constructors

#define aSlice(...)  ( (OBJ)atSlice(__VA_ARGS__) )
#define atSlice(...) COS_PP_CAT_NARG(atSlice,__VA_ARGS__)(__VA_ARGS__)

// ----- automatic constructors shortcuts

#ifndef COS_NOSHORTCUT
#define aSlc(...) aSlice(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation (private)
 */

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

static inline I32
Slice_eval(struct Slice *s, I32 i) {
  return s->start + i * s->stride;
}

static inline I32
Slice_first(struct Slice *s) {
  return s->start;
}

static inline I32
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

/* NOTE-TODO: REMOVE (FROM JAN ?)
static inline struct Slice*
Slice_fromRange(struct Slice *s, struct Range *r, U32 size)
{
  U32 start;
  U32 end;

  if (r->stride < 0) {
    end    = index_abs(r->start, size);
    start  = index_abs(r->end  , size);
    stride = -r->stride;
  } else {
    start  = index_abs(r->start, size);
    end    = index_abs(r->end  , size);
    stride = r->stride;
  }

  if (start < end) {
    size = (end - start + stride) / stride;
  } else {
    size = (start - end + stride) / stride;
  }

  return s;
}
*/

#endif // COS_SLICE_H

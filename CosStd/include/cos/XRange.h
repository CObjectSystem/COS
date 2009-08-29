#ifndef COS_XRANGE_H
#define COS_XRANGE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS XRange
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
 | $Id: XRange.h,v 1.1 2009/08/29 21:38:46 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/Sequence.h>

/* NOTE-USER: XRanges
  - XRanges defines floating value sequences
*/

defclass(XRange, ValueSequence)
  F64 start;
  F64 end;
  F64 stride;
  FINAL_CLASS
endclass

// ----- automatic constructors

#define aXRange(...)  ( (OBJ)atXRange(__VA_ARGS__) )
#define atXRange(...) COS_PP_CAT_NARG(atXRange_,__VA_ARGS__)(__VA_ARGS__)

/***********************************************************
 * Implementation (private)
 */

#define atXRange_1(end) \
        atXRange_2(0,end)

#define atXRange_2(start,end) \
        atXRange_3(start,end,1)

#define atXRange_3(start,end,stride) \
  ( &(struct XRange) { {{{ cos_object_auto(XRange) }}}, \
    start, end, float_equal(stride,0) ? 1 : stride })

// --- XRange inliners (low-level monorphic interface)

// constructor
static inline struct XRange
XRange_make(F64 start, F64 end, F64 stride) {
  return *atXRange(start, end, stride);
}

// initializer
static inline struct XRange*
XRange_init(struct XRange *r, F64 start, F64 end, F64 stride) {
  r->start  = start;
  r->end    = end;
  r->stride = float_equal(stride,0) ? 1: stride;

  return r;
}

// copy
static inline struct XRange*
XRange_copy(struct XRange *r1, const struct XRange *r2) {
  r1->start  = r2->start;
  r1->end    = r2->end;
  r1->stride = r2->stride;

  return r1;
}

// getters
static inline F64
XRange_start(const struct XRange *r) {
  return r->start;
}

static inline F64
XRange_end(const struct XRange *r) {
  return r->end;
}

static inline F64
XRange_stride(const struct XRange *r) {
  return r->stride;
}

static inline F64
XRange_eval(const struct XRange *r, F64 x) {
  return r->start + x * r->stride;
}

static inline U32
XRange_size(const struct XRange *r) {
  U32 size  = (r->end - r->start + r->stride) / r->stride;
  return size > 0 ? size : 0;
}

static inline BOOL
XRange_isEqual(const struct XRange *r1, const struct XRange *r2) {
  return float_equal(r1->start , r2->start)
      && float_equal(r1->end   , r2->end)
      && float_equal(r1->stride, r2->stride);
}

// conversion
#include <cos/Slice.h>
#include <cos/Range.h>

static inline struct XRange
XRange_fromSlice(const struct Slice *s) {
  return *atXRange(Slice_start(s), Slice_end(s), Slice_stride(s));
}

static inline struct XRange
XRange_fromRange(const struct Range *r) {
  return *atXRange(Range_start(r), Range_end(r), Range_stride(r));
}

#endif // COS_XRANGE_H

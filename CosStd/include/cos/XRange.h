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
 | $Id: XRange.h,v 1.6 2010/05/21 14:59:07 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/Sequence.h>

#include <float.h>

/* NOTE-USER: XRanges
  - XRanges defines floating value sequences (see Range.h)
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

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aXRng(...)  aXRange(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

#define atXRange_1(end) \
        atXRange_2(0,end)

#define atXRange_2(start,end) \
        atXRange_3(start,end,1)

#define atXRange_3(start,end,stride) XRange_init( \
  &(struct XRange) { {{{ cos_object_auto(XRange) }}}, 0, 0, 0 }, \
  start, end, stride)

#define atXRange_4(start,next,_,end) XRange_enum( \
  &(struct XRange) { {{{ cos_object_auto(XRange) }}}, 0, 0, 0 }, \
  start, next, end)

// --- XRange inliners (low-level monorphic interface)

// constructor
static inline struct XRange*
XRange_init(struct XRange *r, F64 start, F64 end, F64 stride) {
  r->start  = start;
  r->end    = end;
  r->stride = float_equal(stride,0) ? 1 : stride;

  return r;
}

static inline struct XRange
XRange_make(F64 start, F64 end, F64 stride) {
  return *atXRange(start, end, stride);
}

// enumerator
static inline struct XRange*
XRange_enum(struct XRange *r, F64 start, F64 next, F64 end) {
  r->start  = start;
  r->end    = end;
  r->stride = float_equal(start,next) ? 1 : next-start;

  return r;
}

static inline struct XRange
XRange_makeEnum(F64 start, F64 next, F64 end) {
  return *atXRange(start, next, .., end);
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
XRange_size(const struct XRange *r)
{
  I32 size = (r->end - r->start) / r->stride + 1 + DBL_EPSILON;
  return size > 0 ? size : 0;
}

// predicates
BOOL XRange_isEqual(const struct XRange *r1, const struct XRange *r2);

// closed vs open interval
static inline BOOL
XRange_isClosed(const struct XRange *r) {
  return r->stride > 0 ? r->start <= r->end : r->start >= r->end;
}

// conversion
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

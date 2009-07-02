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
 | $Id: Range.h,v 1.10 2009/07/02 13:20:26 ldeniau Exp $
 |
*/

#include <cos/Value.h>

/* NOTE-USER: Ranges
  - Ranges are objects useful to represent relative strided interval of sequence
    aRange([start],end,[stride])   ([] means optional, default: start=0, stride=1)
    aRange( 1,10, 2) = range from index 1      to 10     included with step  2
    aRange(-5,-1, 1) = range from index size-5 to size-1 included with step  1
    aRange(10, 1,-1) = range from index 10     to 1      included with step -1
    aRange(-1,-9,-1) = range from index size-1 to size-9 included with step -1

  - Ranges can be normalized versus the sequence size
    negative relative indexes are converted to absolute indexes (abs_idx = size - neg_idx)
    normalization is not idempotent (cases where abs_idx is negative)
    aRange( -5,-1,1) with seq_size = 10 -> aRange( 5,9,1) with size =  5
    aRange(-15,-1,1) with seq_size = 10 -> aRange(-5,9,1) with size = 15

  - Ranges cannot have zero size, unless they represent open intervals
    aRange(0,5, 1) -> closed with size = 6
    aRange(0,0, 1) -> closed with size = 1
    aRange(0,5,-1) -> open   with size = 0
    aRange(0,0, 0) -> open   with size = 0 (non-monotonic)

  - Ranges with zero stride are considered as open intervals

  - Ranges can be converted to Slices for some sequence
  - Slices can be converted to Ranges
*/

defclass(Range, Value)
  I32 start;
  I32 end;
  I32 stride;
endclass

// ----- shortcuts

#ifndef COS_NOSHORTCUT
#define aRng(...) aRange(__VA_ARGS__)
#endif

// ----- automatic constructors

#define aRange(...)  ( (OBJ)atRange(__VA_ARGS__) )
#define atRange(...) COS_PP_CAT_NARG(atRange,__VA_ARGS__)(__VA_ARGS__)

/* NOTE-USER: Range indexing policy
   - starts at zero
     (index 0 is the first element)
   - negative indexe starts from the end of the sequence
     (index -1 is the last element, require the sequence's size)
   - the end is included in the range (Ranges cannot have zero size)
   - open ranges have zero size (consistent with conversion to Slice)
   - validation and consitency checks are the user's responsibility
*/
static inline I32
Range_index(I32 index, U32 seq_size) {
  return index + (index < 0) * seq_size;
}

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

// --- inliners (low-level monorphic interface)

// absolute/relative index (normalization should be performed before eval)
static inline I32
Range_eval(const struct Range *r, I32 idx) {
  return r->start + idx * r->stride;
}

// absolute starting index (normalized vs sequence's size)
static inline I32
Range_first(const struct Range *r, U32 seq_size) {
  return Range_index(r->start, seq_size);
}

// absolute ending index (normalized vs sequence's size)
static inline I32
Range_last(const struct Range *r, U32 seq_size) {
  return Range_index(r->end, seq_size);
}

// predicates
static inline BOOL
Range_isMonotonic(const struct Range *r) {
  return r->stride != 0;
}

static inline BOOL
Range_isContiguous(const struct Range *r) {
  return r->stride == 1 || r->stride == -1;
}

static inline BOOL
Range_isPosContiguous(const struct Range *r) {
  return r->stride == 1;
}

static inline BOOL
Range_isNegContiguous(const struct Range *r) {
  return r->stride == -1;
}

static inline BOOL
Range_isEqual(const struct Range *r1, const struct Range *r2) {
  return r1->start  == r2->start
      && r1->end    == r2->end
      && r1->stride == r2->stride;
}

// closed vs open interval (requires sequence's size)
static inline BOOL
Range_isClosed(const struct Range *r, U32 seq_size) {
  I32 start = Range_first(r, seq_size);
  I32 end   = Range_last (r, seq_size);

  return r->stride && (r->stride > 0 ? start <= end : start >= end);
}

// range's size (requires sequence's size)
static inline U32
Range_size(const struct Range *r, U32 seq_size) {
  I32 start = Range_first(r, seq_size);
  I32 end   = Range_last (r, seq_size);
  I32 size  = r->stride ? (end - start + r->stride) / r->stride : 0;

  return size > 0 ? size : 0;
}

// normalization (requires sequence's size)
static inline struct Range
Range_normalize(const struct Range *r, U32 seq_size) {
  I32 start = Range_first(r, seq_size);
  I32 end   = Range_last (r, seq_size);

  if ( (start <= end && r->stride >= 0)
    || (start >= end && r->stride <= 0) )
    return *atRange(start, end, r->stride);
  else
    return *atRange(end, start, r->stride);
}

// conversion
#include <cos/Slice.h>

static inline struct Range
Range_fromSlice(const struct Slice *s) {
  return *atRange(Slice_first(s), Slice_last(s), s->stride);
}

#endif // COS_RANGE_H

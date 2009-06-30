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
 | $Id: Range.h,v 1.8 2009/06/30 07:59:34 ldeniau Exp $
 |
*/

#include <cos/Value.h>

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
   - end is included in the sequence
   - Ranges cannot have zero size (Slices can have zero size)
   - consitency checks must be explicit
*/
static inline I32
Range_index(I32 index, U32 size) {
  return index + (index < 0) * size;
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

// relative index
static inline I32
Range_eval(const struct Range *r, I32 i) {
  return r->start + i * r->stride;
}

// absolute index (requires sequence's size)
static inline I32
Range_first(const struct Range *r, U32 size) {
  return Range_index(r->start, size);
}

static inline I32
Range_last(const struct Range *r, U32 size) {
  return Range_index(r->end, size);
}

// size (requires sequence's size)
static inline U32
Range_size(const struct Range *r, U32 size) {
  I32 start = Range_index(r->start, size);
  I32 end   = Range_index(r->end  , size);
  I32 r_sz  = (end - start + r->stride) / r->stride;

  return r_sz < 0 ? 0 : r_sz; 
}

// closed vs open (requires sequence's size)
static inline BOOL
Range_isClosed(const struct Range *r, U32 size) {
  I32 start = Range_first(r, size);
  I32 end   = Range_last (r, size);

  return r->stride && (r->stride > 0 ? start <= end : start >= end);
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

// normalization (requires sequence's size)
static inline struct Range
Range_normalize(const struct Range *r, U32 size) {
  I32 start = Range_first(r, size);
  I32 end   = Range_last (r, size);

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

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
 | $Id: Slice.h,v 1.11 2009/07/02 13:20:26 ldeniau Exp $
 |
*/

#include <cos/Value.h>

/* NOTE-USER: Slices
  - Slices are objects useful to represent sliced views of sequence
    aSlice([start],size,[stride])   ([] means optional, default: start=0, stride=1)
    aSlice( 1,10, 2) = range from index  1 to 19 included with step  2 (size = 10)
    aSlice( 5, 5,-1) = range from index  5 to  1 included with step -1 (size =  5)
    aSlice(-5, 5, 1) = range from index -5 to -1 included with step  1 (size =  5)

  - Slices with zero stride or negative size are considered as open intervals

  - Slices can be converted to Ranges
  - Ranges can be converted to Slices for some sequence
*/

defclass(Slice, Value)
  I32 start;
  I32 size;
  I32 stride;
endclass

// ----- shortcuts

#ifndef COS_NOSHORTCUT
#define aSlc(...) aSlice(__VA_ARGS__)
#endif

// ----- automatic constructors

#define aSlice(...)  ( (OBJ)atSlice(__VA_ARGS__) )
#define atSlice(...) COS_PP_CAT_NARG(atSlice,__VA_ARGS__)(__VA_ARGS__)

/* NOTE-USER: Slice indexing policy
   - start can be negative, zero or positive
     (negative start means positive first index)
   - size expresses the number of elements (i.e. seq = start..start+(size-1)*stride)
   - validation and consitency checks are the user's responsibility
*/

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

// --- inliners (low-level monorphic interface)

// absolute index
static inline I32
Slice_eval(const struct Slice *s, I32 idx) {
  return s->start + idx * s->stride;
}

// absolute starting index
static inline I32
Slice_first(const struct Slice *s) {
  return s->start;
}

// absolute ending index
static inline I32
Slice_last(const struct Slice *s) {
  return Slice_eval(s, s->size-1);
}

// predicates
static inline BOOL
Slice_isMonotonic(const struct Slice *s) {
  return s->stride != 0;
}

static inline BOOL
Slice_isContiguous(const struct Slice *s) {
  return s->stride == 1 || s->stride == -1;
}

static inline BOOL
Slice_isPosContiguous(const struct Slice *s) {
  return s->stride == 1;
}

static inline BOOL
Slice_isNegContiguous(const struct Slice *s) {
  return s->stride == -1;
}

static inline BOOL
Slice_isEqual(const struct Slice *s1, const struct Slice *s2) {
  return s1->start  == s2->start
      && s1->size   == s2->size
      && s1->stride == s2->stride;
}

// closed vs open interval
static inline BOOL
Slice_isClosed(const struct Slice *s) {
  return s->stride && s->size >= 0;
}

// slice's size
static inline U32
Slice_size(const struct Slice *s) {
  return Slice_isClosed(s) ? s->size : 0;
}

// conversion (requires sequence's size)
#include <cos/Range.h>

static inline struct Slice
Slice_fromRange(const struct Range *r, U32 seq_size)
{
  return *atSlice(Range_first(r,seq_size), Range_size(r,seq_size), r->stride);
}

#endif // COS_SLICE_H

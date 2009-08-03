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
 | $Id: Slice.h,v 1.13 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Value.h>

/* NOTE-USER: Slices
  - Slices are objects useful to represent sliced views of sequence
    aSlice([start],size,[stride])   ([] means optional, default: start=0, stride=1)
    aSlice( 1,10, 2) = range from index  1 to 21 excluded with step  2 (size = 10)
    aSlice( 5, 5,-1) = range from index  5 to  0 excluded with step -1 (size =  5)
    aSlice(-5, 5, 1) = range from index -5 to  0 excluded with step  1 (size =  5)

  - Slices can be converted to Ranges
  - Ranges can be converted to Slices given the sequence size
*/

defclass(Slice, Value)
  I32 start;
  U32 size;
  I32 stride;
  COS_FINAL_CLASS
endclass

// ----- automatic constructors

#define aSlice(...)  ( (OBJ)atSlice(__VA_ARGS__) )
#define atSlice(...) COS_PP_CAT_NARG(atSlice_,__VA_ARGS__)(__VA_ARGS__)

/* NOTE-USER: Slice indexing policy
   - start can be negative, zero or positive
     (negative start means positive first index)
   - size expresses the number of elements (i.e. seq = start..start+(size-1)*stride)
   - validation and consitency checks are the user's responsibility
*/

/***********************************************************
 * Implementation (private)
 */

#define atSlice_1(size) \
        atSlice_2(0,size)

#define atSlice_2(start,size) \
        atSlice_3(start,size,1)

#define atSlice_3(start,size,stride) \
  ( &(struct Slice){{ cos_object_auto(Slice) }, \
    start, size, stride ? stride : 1 })

// --- Slice inliners (low-level monorphic interface)

// constructor
static inline struct Slice
Slice_make(I32 start, U32 size, I32 stride) {
  return *atSlice(start, size, stride);
}

// initializer
static inline struct Slice*
Slice_init(struct Slice *s, I32 start, U32 size, I32 stride) {
  s->start  = start;
  s->size   = size;
  s->stride = stride ? stride : 1;

  return s;
}

// copy
static inline struct Slice*
Slice_copy(struct Slice *s1, const struct Slice *s2) {
  s1->start  = s2->start;
  s1->size   = s2->size;
  s1->stride = s2->stride;

  return s1;
}

// getters
static inline I32
Slice_start(const struct Slice *s) {
  return s->start;
}

static inline U32
Slice_size(const struct Slice *s) {
  return s->size;
}

static inline I32
Slice_stride(const struct Slice *s) {
  return s->stride;
}

static inline I32
Slice_eval(const struct Slice *s, I32 idx) {
  return s->start + idx * s->stride;
}

static inline I32
Slice_end(const struct Slice *s) {
  return Slice_eval(s, s->size-1);
}

// sequence first index (alias for start)
static inline I32
Slice_first(const struct Slice *s) {
  return Slice_start(s);
}

// sequence last index (alias for end )
static inline I32
Slice_last(const struct Slice *s) {
  return Slice_end(s);
}

// predicates
static inline BOOL
Slice_isContiguous(const struct Slice *s) {
  return s->stride == 1 || s->stride == -1;
}

static inline BOOL
Slice_isEqual(const struct Slice *s1, const struct Slice *s2) {
  return s1->start  == s2->start
      && s1->size   == s2->size
      && s1->stride == s2->stride;
}

// sliced Slice (s2 over s1)
static inline struct Slice*
Slice_addTo(struct Slice *s1, const struct Slice *s2) {
  s1->start  += s2->start*s1->stride;
  s1->size    = s2->size;
  s1->stride *= s2->stride;

  return s1;
}

// conversion
#include <cos/Range.h>

static inline struct Slice
Slice_fromRange(const struct Range *r)
{
  I32 start  = Range_start (r);
  U32 size   = Range_size  (r);
  I32 stride = Range_stride(r);

  return *atSlice(start, size, stride);
}

#endif // COS_SLICE_H

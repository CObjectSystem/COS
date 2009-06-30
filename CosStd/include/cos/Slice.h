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
 | $Id: Slice.h,v 1.10 2009/06/30 07:59:34 ldeniau Exp $
 |
*/

#include <cos/Value.h>

defclass(Slice, Value)
  I32 start;
  U32 size;
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
     (negative start means positive first element)
   - size expresses the number of elements
     (Slices can have zero size, but not Ranges)
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
Slice_eval(const struct Slice *s, I32 i) {
  return s->start + i * s->stride;
}

static inline I32
Slice_first(const struct Slice *s) {
  return s->start;
}

static inline I32
Slice_last(const struct Slice *s) {
  return Slice_eval(s, s->size-1);
}

// size
static inline U32
Slice_size(const struct Slice *s) {
  return s->size;
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

// conversion
#include <cos/Range.h>

static inline struct Slice
Slice_fromRange(const struct Range *r, U32 size)
{
  return *atSlice(Range_first(r, size), Range_size(r, size), r->stride);
}

#endif // COS_SLICE_H

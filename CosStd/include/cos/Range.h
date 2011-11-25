#ifndef COS_RANGE_H
#define COS_RANGE_H

/**
 * C Object System
 * COS Range
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/Sequence.h>

/* NOTE-USER: Ranges
  - Ranges are objects useful to represent relative strided interval of sequence
    aRange([start],end,[stride])   (default: start=0, stride=1)

    aRange(10)       = range from index 0      to 10     included with step  1
    aRange(0,10)     = range from index 0      to 10     included with step  1
    aRange(0,10,1)   = range from index 0      to 10     included with step  1

    aRange( 1,10, 2) = range from index 1      to 10     included with step  2
    aRange(-5,-1, 1) = range from index size-5 to size-1 included with step  1
    aRange(10, 1,-1) = range from index 10     to 1      included with step -1
    aRange(-1,-9,-1) = range from index size-1 to size-9 included with step -1

  - Ranges can be built from enumeration
    aRange(1,3,..,7) = range from index 1      to 7      included with step  2
    aRange(0,3,..,7) = range from index 0      to 6      included with step  3
     
  - Ranges can be normalized versus the size of a sequence
    . negative relative indexes are converted to absolute indexes using
      the normalization: absolute_index = sequence_size - negative_index
    . normalization is not idempotent (cases where absolute_index is negative)
    aRange( -5,-1,1) with seq_size = 10 -> aRange( 5,9,1) with size =  5
    aRange(-15,-1,1) with seq_size = 10 -> aRange(-5,9,1) with size = 15

  - Ranges cannot have zero size, unless they represent open intervals
    aRange(0,5, 1) -> closed with size = 6
    aRange(0,0, 1) -> closed with size = 1
    aRange(0,5,-1) -> open   with size = 0
    aRange(0,0, 0) -> close  with size = 0 and stride = 1 (0 strides become 1)

  - Ranges can be converted to Slices (given the sequence size)
  - Slices can be converted to Ranges
*/

defclass(Range, ValueSequence)
  I32 start;
  I32 end;
  I32 stride;
  FINAL_CLASS
endclass

// ----- automatic constructors

#define aRange(...)  ( (OBJ)atRange(__VA_ARGS__) )
#define atRange(...) COS_PP_CAT_NARG(atRange_,__VA_ARGS__)(__VA_ARGS__)

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aRng(...)  aRange(__VA_ARGS__)

#endif

/* NOTE-USER: Range and Sequence indexing policy
   - starts at zero
     (index 0 is the first element)
   - negative indexe starts from the end of the sequence
     (index -1 is the last element, require the sequence's size)
   - the end is included in the range (Ranges cannot have zero size)
   - open ranges have zero size (consistent with conversion to Slice)
   - validation and consitency checks are the user's responsibility
   - stride must never be zero! (converted to 1 if you use the ctor)
*/
static cos_inline U32
Range_index(I32 index, U32 seq_size) {
  return index + (index < 0) * seq_size;
}

/***********************************************************
 * Implementation (private)
 */

#define atRange_1(end) \
        atRange_2(0,end)

#define atRange_2(start,end) \
        atRange_3(start,end,1)

#define atRange_3(start,end,stride) Range_init( \
  &(struct Range) { {{{ cos_object_auto(Range) }}}, 0, 0, 0}, \
  start, end, stride)

#define atRange_4(start,next,_,end) Range_enum( \
  &(struct Range) { {{{ cos_object_auto(Range) }}}, 0, 0, 0 }, \
  start, next, end)

// --- Range inliners (low-level monorphic interface)

// constructor
static cos_inline struct Range*
Range_init(struct Range *r, I32 start, I32 end, I32 stride) {
  r->start  = start;
  r->end    = end;
  r->stride = stride ? stride : 1;

  return r;
}

// enumerator
static cos_inline struct Range*
Range_enum(struct Range *r, I32 start, I32 next, I32 end) {
  r->start  = start;
  r->end    = end;
  r->stride = start == next ? 1 : next-start;

  return r;
}

// copy
static cos_inline struct Range*
Range_copy(struct Range *r1, const struct Range *r2) {
  r1->start  = r2->start;
  r1->end    = r2->end;
  r1->stride = r2->stride;

  return r1;
}

// getters
static cos_inline I32
Range_start(const struct Range *r) {
  return r->start;
}

static cos_inline I32
Range_end(const struct Range *r) {
  return r->end;
}

static cos_inline I32
Range_stride(const struct Range *r) {
  return r->stride;
}

static cos_inline I32
Range_eval(const struct Range *r, I32 idx) {
  return r->start + idx * r->stride;
}

static cos_inline U32
Range_size(const struct Range *r) {
  I32 size  = (r->end - r->start + r->stride) / r->stride;
  return size > 0 ? size : 0;
}

// predicates
static cos_inline BOOL
Range_isContiguous(const struct Range *r) {
  return r->stride == 1 || r->stride == -1;
}

static cos_inline BOOL
Range_isEqual(const struct Range *r1, const struct Range *r2) {
  return r1->start  == r2->start
      && r1->end    == r2->end
      && r1->stride == r2->stride;
}

// closed vs open interval
static cos_inline BOOL
Range_isClosed(const struct Range *r) {
  return r->stride > 0 ? r->start <= r->end : r->start >= r->end;
}

// normalization

// sequence first index (normalized vs sequence's size)
static cos_inline U32
Range_first(const struct Range *r, U32 seq_size) {
  return Range_index(r->start, seq_size);
}

// sequence last index (normalized vs sequence's size) (included)
static cos_inline U32
Range_last(const struct Range *r, U32 seq_size) {
  return Range_index(r->end, seq_size);
}

// normalization (require sequence's size, preserve stride)
static cos_inline struct Range*
Range_normalize(struct Range *r, U32 seq_size) {
  U32 start = Range_first(r, seq_size);
  U32 end   = Range_last (r, seq_size);

  if ( (start <= end && r->stride >= 0)
    || (start >= end && r->stride <= 0) )
    r->start = start, r->end = end;
  else
    r->start = end  , r->end = start;

  return r;
}

// conversion
#include <cos/Slice.h>

static cos_inline struct Range*
Range_fromSlice(struct Range *r, const struct Slice *s) {
  return Range_init(r, Slice_start(s), Slice_end(s), Slice_stride(s));
}

#endif // COS_RANGE_H

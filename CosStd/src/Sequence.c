/**
 * C Object System
 * COS Sequence
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
#include <cos/Slice.h>

#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

STATIC_ASSERT(sequence_growth_rate_is_too_small , SEQUENCE_GROWTH_RATE >= 1500);
STATIC_ASSERT(sequence_minimun_size_is_too_small, SEQUENCE_MIN_SIZE    >= 32);

// -----

makclass(Sequence     , Collection);
makclass(ValueSequence, Sequence );

// -----

useclass(ExOverflow);

// -----

defmethod(OBJ, gdeinit, ValueSequence)
  retmethod(_1);
endmethod

// -----

U32
Sequence_enlargeCapacity(U32 capacity, U32 extra)
{
  U32 size = capacity + extra;
  U32 last = U32_MAX/SEQUENCE_GROWTH_RATE;

  // overflow
  if (capacity > U32_MAX-extra)
    THROW(gnewWithStr(ExOverflow, "extra size is too large"));

  // starting point
  if (capacity < SEQUENCE_MIN_SIZE)
    capacity = SEQUENCE_MIN_SIZE;
  
  // growth rate
  while (capacity < size && capacity <= last)
    capacity *= SEQUENCE_GROWTH_RATE/1000.0;

  // round last growth
  if (capacity < size)
    capacity = size;

  return capacity;
}


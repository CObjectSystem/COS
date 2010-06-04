/*
 o---------------------------------------------------------------------o
 |
 | COS Sequence
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
 | $Id: Sequence.c,v 1.16 2010/06/04 23:27:22 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>
#include <cos/Slice.h>

#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

STATIC_ASSERT(sequence_growth_rate_is_too_small , SEQUENCE_GROWTH_RATE >= 1.5);
STATIC_ASSERT(sequence_minimun_size_is_too_small, SEQUENCE_MIN_SIZE    >= 32 );

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
    capacity *= SEQUENCE_GROWTH_RATE;

  // round last growth
  if (capacity < size)
    capacity = size;

  return capacity;
}


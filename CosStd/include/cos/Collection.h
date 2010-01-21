#ifndef COS_COLLECTION_H
#define COS_COLLECTION_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Collection
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
 | $Id: Collection.h,v 1.5 2010/01/21 14:12:35 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: Collection subclasses

<- Collection
  <- Map    (hash+equal keys  )
  <- OrdMap (compare    keys  )
  <- Set    (hash+equal values)
  <- OrdSet (compare    values)
  <- Sequence
    <- Array
    <- Deque
    <- List
    <- ValueSequence (elements are values)
      <- Slice
      <- Range
      <- XRange
      <- String
      <- Vector
        <- BitVector // TODO
        <- ShtVector
        <- IntVector
        <- LngVector
        <- FltVector
        <- CpxVector

  - All collections provide maps (high-level) and iterators (low-level)
  - All collections own (gretain) their elements (and keys if any)
  - All collections do swallow copy (map/apply gclone for deep copy)
*/

defclass(Collection)
endclass

#endif // COS_COLLECTION_H


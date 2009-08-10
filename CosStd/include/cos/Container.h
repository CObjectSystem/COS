#ifndef COS_CONTAINER_H
#define COS_CONTAINER_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Container
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
 | $Id: Container.h,v 1.5 2009/08/10 21:02:14 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: Container subclasses

<- Container
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
      <- String
      <- WString
      <- Vector
        <- BitVector
        <- ChrVector
        <- ShtVector
        <- IntVector
        <- LngVector
        <- FltVector
        <- CpxVector
        <- ObjVector

  - All containers own (gretain) their elements (and keys if any)
  - All containers do swallow copy
*/

defclass(Container)
endclass

#endif // COS_CONTAINER_H


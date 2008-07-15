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
 | $Id: Slice.c,v 1.2 2008/07/15 08:00:46 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Slice.h>
#include <cos/gen/object.h>

makclass(Slice,Value);
makclass(Slice1,Slice);
makclass(Slice2,Slice);
makclass(Slice3,Slice);
makclass(Slice4,Slice);
makclass(Slice5,Slice);

defmethod(OBJ, ginitWith, Slice1, Slice1)
  self1->start  = self2->start;
  self1->size   = self2->size;
  self1->stride = self2->stride;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Slice2, Slice2)
  self1->start     = self2->start;
  self1->size  [0] = self2->size  [0];
  self1->size  [1] = self2->size  [1];
  self1->stride[0] = self2->stride[0];
  self1->stride[1] = self2->stride[1];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Slice3, Slice3)
  self1->start     = self2->start;
  self1->size  [0] = self2->size  [0];
  self1->size  [1] = self2->size  [1];
  self1->size  [2] = self2->size  [2];
  self1->stride[0] = self2->stride[0];
  self1->stride[1] = self2->stride[1];
  self1->stride[2] = self2->stride[2];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Slice4, Slice4)
  self1->start     = self2->start;
  self1->size  [0] = self2->size  [0];
  self1->size  [1] = self2->size  [1];
  self1->size  [2] = self2->size  [2];
  self1->size  [3] = self2->size  [3];
  self1->stride[0] = self2->stride[0];
  self1->stride[1] = self2->stride[1];
  self1->stride[2] = self2->stride[2];
  self1->stride[3] = self2->stride[3];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Slice5, Slice5)
  self1->start     = self2->start;
  self1->size  [0] = self2->size  [0];
  self1->size  [1] = self2->size  [1];
  self1->size  [2] = self2->size  [2];
  self1->size  [3] = self2->size  [3];
  self1->size  [4] = self2->size  [4];
  self1->stride[0] = self2->stride[0];
  self1->stride[1] = self2->stride[1];
  self1->stride[2] = self2->stride[2];
  self1->stride[3] = self2->stride[3];
  self1->stride[4] = self2->stride[4];
  retmethod(_1);
endmethod

defmethod(OBJ, gequal, Slice1, Slice1)
  BOOL res = self1->start  == self2->start
          && self1->size   == self2->size
          && self1->stride == self2->stride;
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Slice2, Slice2)
  BOOL res = self1->start     == self2->start
          && self1->size  [0] == self2->size  [0]
          && self1->size  [1] == self2->size  [1]
          && self1->stride[0] == self2->stride[0]
          && self1->stride[1] == self2->stride[1];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Slice3, Slice3)
  BOOL res = self1->start     == self2->start
          && self1->size  [0] == self2->size  [0]
          && self1->size  [1] == self2->size  [1]
          && self1->size  [2] == self2->size  [2]
          && self1->stride[0] == self2->stride[0]
          && self1->stride[1] == self2->stride[1]
          && self1->stride[2] == self2->stride[2];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Slice4, Slice4)
  BOOL res = self1->start     == self2->start
          && self1->size  [0] == self2->size  [0]
          && self1->size  [1] == self2->size  [1]
          && self1->size  [2] == self2->size  [2]
          && self1->size  [3] == self2->size  [3]
          && self1->stride[0] == self2->stride[0]
          && self1->stride[1] == self2->stride[1]
          && self1->stride[2] == self2->stride[2]
          && self1->stride[3] == self2->stride[3];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Slice5, Slice5)
  BOOL res = self1->start     == self2->start
          && self1->size  [0] == self2->size  [0]
          && self1->size  [1] == self2->size  [1]
          && self1->size  [2] == self2->size  [2]
          && self1->size  [3] == self2->size  [3]
          && self1->size  [4] == self2->size  [4]
          && self1->stride[0] == self2->stride[0]
          && self1->stride[1] == self2->stride[1]
          && self1->stride[2] == self2->stride[2]
          && self1->stride[3] == self2->stride[3]
          && self1->stride[4] == self2->stride[4];
  retmethod( res ? True : False );
endmethod


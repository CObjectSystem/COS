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
 | $Id: Range.c,v 1.1 2008/07/15 08:00:46 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Range.h>
#include <cos/gen/object.h>

makclass(Range ,Value);
makclass(Range1,Range);
makclass(Range2,Range);
makclass(Range3,Range);
makclass(Range4,Range);
makclass(Range5,Range);

defmethod(OBJ, ginitWith, Range1, Range1)
  self1->start = self2->start;
  self1->size  = self2->size ;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range2, Range2)
  self1->start[0] = self2->start[0];
  self1->start[1] = self2->start[1];
  self1->size [0] = self2->size [0];
  self1->size [1] = self2->size [1];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range3, Range3)
  self1->start[0] = self2->start[0];
  self1->start[1] = self2->start[1];
  self1->start[2] = self2->start[2];
  self1->size [0] = self2->size [0];
  self1->size [1] = self2->size [1];
  self1->size [2] = self2->size [2];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range4, Range4)
  self1->start[0] = self2->start[0];
  self1->start[1] = self2->start[1];
  self1->start[2] = self2->start[2];
  self1->start[3] = self2->start[3];
  self1->size [0] = self2->size [0];
  self1->size [1] = self2->size [1];
  self1->size [2] = self2->size [2];
  self1->size [3] = self2->size [3];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range5, Range5)
  self1->start[0] = self2->start[0];
  self1->start[1] = self2->start[1];
  self1->start[2] = self2->start[2];
  self1->start[3] = self2->start[3];
  self1->start[4] = self2->start[4];
  self1->size [0] = self2->size [0];
  self1->size [1] = self2->size [1];
  self1->size [2] = self2->size [2];
  self1->size [3] = self2->size [3];
  self1->size [4] = self2->size [4];
  retmethod(_1);
endmethod

defmethod(OBJ, gequal, Range1, Range1)
  BOOL res = self1->start == self2->start
          && self1->size  == self2->size ;
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range2, Range2)
  BOOL res = self1->start[0] == self2->start[0]
          && self1->start[1] == self2->start[1]
          && self1->size [0] == self2->size [0]
          && self1->size [1] == self2->size [1];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range3, Range3)
  BOOL res = self1->start[0] == self2->start[0]
          && self1->start[1] == self2->start[1]
          && self1->start[2] == self2->start[2]
          && self1->size [0] == self2->size [0]
          && self1->size [1] == self2->size [1]
          && self1->size [2] == self2->size [2];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range4, Range4)
  BOOL res = self1->start[0] == self2->start[0]
          && self1->start[1] == self2->start[1]
          && self1->start[2] == self2->start[2]
          && self1->start[3] == self2->start[3]
          && self1->size [0] == self2->size [0]
          && self1->size [1] == self2->size [1]
          && self1->size [2] == self2->size [2]
          && self1->size [3] == self2->size [3];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range5, Range5)
  BOOL res = self1->start[0] == self2->start[0]
          && self1->start[1] == self2->start[1]
          && self1->start[2] == self2->start[2]
          && self1->start[3] == self2->start[3]
          && self1->start[4] == self2->start[4]
          && self1->size [0] == self2->size [0]
          && self1->size [1] == self2->size [1]
          && self1->size [2] == self2->size [2]
          && self1->size [3] == self2->size [3]
          && self1->size [4] == self2->size [4];
  retmethod( res ? True : False );
endmethod


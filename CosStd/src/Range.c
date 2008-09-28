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
 | $Id: Range.c,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Range.h>
#include <cos/gen/object.h>

makclass(Range , Value);
makclass(Range1, Range);
makclass(Range2, Range);
makclass(Range3, Range);
makclass(Range4, Range);
makclass(Range5, Range);

// ----- copy

defmethod(OBJ, ginitWith, Range1, Range1)
  self1->start  = self2->start,
  self1->end    = self2->end  ,
  self1->stride = self2->end  ;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range2, Range2)
  for (int i = 0; i < 2; i++)
    self1->start [i] = self2->start [i],
    self1->end   [i] = self2->end   [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range3, Range3)
  for (int i = 0; i < 3; i++)
    self1->start [i] = self2->start [i],
    self1->end   [i] = self2->end   [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range4, Range4)
  for (int i = 0; i < 4; i++)
    self1->start [i] = self2->start [i],
    self1->end   [i] = self2->end   [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Range5, Range5)
  for (int i = 0; i < 5; i++)
    self1->start [i] = self2->start [i],
    self1->end   [i] = self2->end   [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, Range1, Range1)
  BOOL res = self1->start  == self2->start
          && self1->end    == self2->end 
          && self1->stride == self2->stride;

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range2, Range2)
  BOOL res = YES;

  for (int i = 0; res && i < 2; i++)
    res = res && self1->start [i] == self2->start [i]
              && self1->end   [i] == self2->end   [i]
              && self1->stride[i] == self2->stride[i];

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range3, Range3)
  BOOL res = YES;

  for (int i = 0; res && i < 3; i++)
    res = res && self1->start [i] == self2->start [i]
              && self1->end   [i] == self2->end   [i]
              && self1->stride[i] == self2->stride[i];

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range4, Range4)
  BOOL res = YES;

  for (int i = 0; res && i < 4; i++)
    res = res && self1->start [i] == self2->start [i]
              && self1->end   [i] == self2->end   [i]
              && self1->stride[i] == self2->stride[i];

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Range5, Range5)
  BOOL res = YES;

  for (int i = 0; res && i < 5; i++)
    res = res && self1->start [i] == self2->start [i]
              && self1->end   [i] == self2->end   [i]
              && self1->stride[i] == self2->stride[i];

  retmethod( res ? True : False );
endmethod


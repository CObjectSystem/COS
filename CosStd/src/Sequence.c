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
 | $Id: Sequence.c,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/Sequence.h>
#include <cos/gen/object.h>

makclass(Sequence , Value   );
makclass(Sequence1, Sequence);
makclass(Sequence2, Sequence);
makclass(Sequence3, Sequence);
makclass(Sequence4, Sequence);
makclass(Sequence5, Sequence);

// ----- copy

defmethod(OBJ, ginitWith, Sequence1, Sequence1)
  self1->start  = self2->start ,
  self1->size   = self2->size  ,
  self1->stride = self2->stride;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Sequence2, Sequence2)
  self1->start = self2->start;

  for (int i = 0; i < 2; i++)
    self1->size  [i] = self2->size  [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Sequence3, Sequence3)
  self1->start = self2->start;

  for (int i = 0; i < 3; i++)
    self1->size  [i] = self2->size  [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Sequence4, Sequence4)
  self1->start = self2->start;

  for (int i = 0; i < 4; i++)
    self1->size  [i] = self2->size  [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Sequence5, Sequence5)
  self1->start = self2->start;

  for (int i = 0; i < 5; i++)
    self1->size  [i] = self2->size  [i],
    self1->stride[i] = self2->stride[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, Sequence1, Sequence1)
  BOOL res = dbl_equal(self1->start , self2->start )
          &&           self1->size == self2->size
          && dbl_equal(self1->stride, self2->stride);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Sequence2, Sequence2)
  BOOL res = dbl_equal(self1->start, self2->start);

  for (int i = 0; res && i < 2; i++)
    res = res &&           self1->size  [i] == self2->size  [i]
              && dbl_equal(self1->stride[i] ,  self2->stride[i]);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Sequence3, Sequence3)
  BOOL res = dbl_equal(self1->start, self2->start);

  for (int i = 0; res && i < 3; i++)
    res = res &&           self1->size  [i] == self2->size  [i]
              && dbl_equal(self1->stride[i] ,  self2->stride[i]);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Sequence4, Sequence4)
  BOOL res = dbl_equal(self1->start, self2->start);

  for (int i = 0; res && i < 4; i++)
    res = res &&           self1->size  [i] == self2->size  [i]
              && dbl_equal(self1->stride[i] ,  self2->stride[i]);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Sequence5, Sequence5)
  BOOL res = dbl_equal(self1->start, self2->start);

  for (int i = 0; res && i < 5; i++)
    res = res &&           self1->size  [i] == self2->size  [i]
              && dbl_equal(self1->stride[i] ,  self2->stride[i]);

  retmethod( res ? True : False );
endmethod


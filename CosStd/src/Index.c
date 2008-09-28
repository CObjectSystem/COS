/*
 o---------------------------------------------------------------------o
 |
 | COS Index
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
 | $Id: Index.c,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Index.h>
#include <cos/gen/object.h>

makclass(Index , Value);
makclass(Index1, Index);
makclass(Index2, Index);
makclass(Index3, Index);
makclass(Index4, Index);
makclass(Index5, Index);

// ----- copy

defmethod(OBJ, ginitWith, Index1, Index1)
  self1->index = self2->index;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index2, Index2)
  self1->index[0] = self2->index[0],
  self1->index[1] = self2->index[1];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index3, Index3)
  for (int i = 0; i < 3; i++)
    self1->index[i] = self2->index[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index4, Index4)
  for (int i = 0; i < 4; i++)
    self1->index[i] = self2->index[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index5, Index5)
  for (int i = 0; i < 5; i++)
    self1->index[i] = self2->index[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, Index1, Index1)
  retmethod( self1->index == self2->index ? True : False );
endmethod

defmethod(OBJ, gequal, Index2, Index2)
  BOOL res = self1->index[0] == self2->index[0]
          && self1->index[1] == self2->index[1];

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index3, Index3)
  BOOL res = self1->index[0] == self2->index[0];

  for (int i = 1; res && i < 3; i++)
    res = res && self1->index[i] == self2->index[i];

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index4, Index4)
  BOOL res = self1->index[0] == self2->index[0];

  for (int i = 1; res && i < 4; i++)
    res = res && self1->index[i] == self2->index[i];

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index5, Index5)
  BOOL res = self1->index[0] == self2->index[0];

  for (int i = 1; res && i < 5; i++)
    res = res && self1->index[i] == self2->index[i];

  retmethod( res ? True : False );
endmethod


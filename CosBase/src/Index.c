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
 | $Id: Index.c,v 1.3 2008/08/21 15:54:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Index.h>
#include <cos/gen/object.h>

makclass(Index ,Value);
makclass(Index1,Index);
makclass(Index2,Index);
makclass(Index3,Index);
makclass(Index4,Index);
makclass(Index5,Index);

defmethod(OBJ, ginitWith, Index1, Index1)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index2, Index2)
  self1->value[0] = self2->value[0];
  self1->value[1] = self2->value[1];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index3, Index3)
  self1->value[0] = self2->value[0];
  self1->value[1] = self2->value[1];
  self1->value[2] = self2->value[2];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index4, Index4)
  self1->value[0] = self2->value[0];
  self1->value[1] = self2->value[1];
  self1->value[2] = self2->value[2];
  self1->value[3] = self2->value[3];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Index5, Index5)
  self1->value[0] = self2->value[0];
  self1->value[1] = self2->value[1];
  self1->value[2] = self2->value[2];
  self1->value[3] = self2->value[3];
  self1->value[4] = self2->value[4];
  retmethod(_1);
endmethod

defmethod(OBJ, gequal, Index1, Index1)
  BOOL res = self1->value == self2->value;
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index2, Index2)
  BOOL res = self1->value[0] == self2->value[0]
          && self1->value[1] == self2->value[1];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index3, Index3)
  BOOL res = self1->value[0] == self2->value[0]
          && self1->value[1] == self2->value[1]
          && self1->value[2] == self2->value[2];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index4, Index4)
  BOOL res = self1->value[0] == self2->value[0]
          && self1->value[1] == self2->value[1]
          && self1->value[2] == self2->value[2]
          && self1->value[3] == self2->value[3];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Index5, Index5)
  BOOL res = self1->value[0] == self2->value[0]
          && self1->value[1] == self2->value[1]
          && self1->value[2] == self2->value[2]
          && self1->value[3] == self2->value[3]
          && self1->value[4] == self2->value[4];
  retmethod( res ? True : False );
endmethod


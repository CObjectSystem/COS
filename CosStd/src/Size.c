/*
 o---------------------------------------------------------------------o
 |
 | COS Size
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
 | $Id: Size.c,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Size.h>
#include <cos/gen/object.h>

makclass(Size , Value);
makclass(Size1, Size);
makclass(Size2, Size);
makclass(Size3, Size);
makclass(Size4, Size);
makclass(Size5, Size);

defmethod(OBJ, ginitWith, Size1, Size1)
  self1->size = self2->size;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Size2, Size2)
  self1->size[0] = self2->size[0];
  self1->size[1] = self2->size[1];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Size3, Size3)
  self1->size[0] = self2->size[0];
  self1->size[1] = self2->size[1];
  self1->size[2] = self2->size[2];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Size4, Size4)
  self1->size[0] = self2->size[0];
  self1->size[1] = self2->size[1];
  self1->size[2] = self2->size[2];
  self1->size[3] = self2->size[3];
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Size5, Size5)
  self1->size[0] = self2->size[0];
  self1->size[1] = self2->size[1];
  self1->size[2] = self2->size[2];
  self1->size[3] = self2->size[3];
  self1->size[4] = self2->size[4];
  retmethod(_1);
endmethod

defmethod(OBJ, gequal, Size1, Size1)
  BOOL res = self1->size == self2->size;
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Size2, Size2)
  BOOL res = self1->size[0] == self2->size[0]
          && self1->size[1] == self2->size[1];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Size3, Size3)
  BOOL res = self1->size[0] == self2->size[0]
          && self1->size[1] == self2->size[1]
          && self1->size[2] == self2->size[2];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Size4, Size4)
  BOOL res = self1->size[0] == self2->size[0]
          && self1->size[1] == self2->size[1]
          && self1->size[2] == self2->size[2]
          && self1->size[3] == self2->size[3];
  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Size5, Size5)
  BOOL res = self1->size[0] == self2->size[0]
          && self1->size[1] == self2->size[1]
          && self1->size[2] == self2->size[2]
          && self1->size[3] == self2->size[3]
          && self1->size[4] == self2->size[4];
  retmethod( res ? True : False );
endmethod


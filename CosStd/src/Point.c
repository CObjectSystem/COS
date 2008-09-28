/*
 o---------------------------------------------------------------------o
 |
 | COS Point
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
 | $Id: Point.c,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/Point.h>
#include <cos/gen/object.h>

makclass(Point , Value);
makclass(Point1, Point);
makclass(Point2, Point);
makclass(Point3, Point);
makclass(Point4, Point);
makclass(Point5, Point);

// ----- copy

defmethod(OBJ, ginitWith, Point1, Point1)
  self1->value = self2->value;

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Point2, Point2)
  self1->value[0] = self2->value[0],
  self1->value[1] = self2->value[1];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Point3, Point3)
  for (int i = 0; i < 3; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Point4, Point4)
  for (int i = 0; i < 4; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Point5, Point5)
  for (int i = 0; i < 5; i++)
    self1->value[i] = self2->value[i];

  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gequal, Point1, Point1)
  BOOL res = dbl_equal(self1->value, self2->value);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Point2, Point2)
  BOOL res = dbl_equal(self1->value[0], self2->value[0])
          && dbl_equal(self1->value[1], self2->value[1]);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Point3, Point3)
  BOOL res = dbl_equal(self1->value[0], self2->value[0]);

  for (int i = 1; res && i < 3; i++)
    res = res && dbl_equal(self1->value[i], self2->value[i]);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Point4, Point4)
  BOOL res = dbl_equal(self1->value[0], self2->value[0]);

  for (int i = 1; res && i < 4; i++)
    res = res && dbl_equal(self1->value[i], self2->value[i]);

  retmethod( res ? True : False );
endmethod

defmethod(OBJ, gequal, Point5, Point5)
  BOOL res = dbl_equal(self1->value[0], self2->value[0]);

  for (int i = 1; res && i < 5; i++)
    res = res && dbl_equal(self1->value[i], self2->value[i]);

  retmethod( res ? True : False );
endmethod


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
 | $Id: Range.c,v 1.3 2009/02/27 20:14:26 ldeniau Exp $
 |
*/

#include <cos/Range.h>

#include <cos/gen/object.h>

makclass(Range, Value);

// ----- copy

defmethod(OBJ, ginitWith, Range, Range)
  self1->start  = self2->start,
  self1->end    = self2->end  ,
  self1->stride = self2->end  ;
  retmethod(_1);
endmethod

// ----- equality

defmethod(OBJ, gisEqual, Range, Range)
  BOOL res = self1->start  == self2->start
          && self1->end    == self2->end 
          && self1->stride == self2->stride;

  retmethod( res ? True : False );
endmethod


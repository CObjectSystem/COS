/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - MilliCounter class definition
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
 | $Id: MilliCounter.c,v 1.1 2008/06/27 16:17:18 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>

#include "MilliCounter.h"
#include "generics.h"

makclass(MilliCounter,Counter);

// --- contructors/destructor

defmethod(OBJ, ginit, MilliCounter)
  self->mval = 0;
  next_method(self);
endmethod

defmethod(OBJ, gdeinit, MilliCounter)
  retmethod(_1);
endmethod

// --- for speed tests ---

defmethod(OBJ, gincr, MilliCounter)
  next_method(self);
endmethod

defmethod(OBJ, gincrBy1, MilliCounter, (U32)a)
  next_method(self, a);
endmethod

defmethod(OBJ, gincrBy2, MilliCounter, (U32)a, (U32)b)
  next_method(self, a, b);
endmethod

defmethod(OBJ, gincrBy3, MilliCounter, (U32)a, (U32)b, (U32)c)
  next_method(self, a, b, c);
endmethod

defmethod(OBJ, gincrBy4, MilliCounter, (U32)a, (U32)b, (U32)c, (U32)d)
  next_method(self, a, b, c, d);
endmethod

defmethod(OBJ, gincrBy5, MilliCounter, (U32)a, (U32)b, (U32)c, (U32)d, (U32)e)
  next_method(self, a, b, c, d, e);
endmethod

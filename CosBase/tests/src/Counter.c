/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - Counter class definition
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
 | $Id: Counter.c,v 1.1 2008/06/27 16:17:18 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdio.h>

#include "Counter.h"
#include "generics.h"

makclass(Counter,Object);

// --- contructors/destructor

defmethod(OBJ, ginit, Counter)
  self->val = 0;
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Counter)
  retmethod(_1);
endmethod

// --- getter

defmethod(S32, gint, Counter)
  retmethod(self->val);
endmethod

// --- for speed tests ---

defmethod(OBJ, gincr, Counter)
  ++self->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gincrBy1, Counter, (U32)a)
  self->val += a;
  retmethod(_1);
endmethod

defmethod(OBJ, gincrBy2, Counter, (U32)a, (U32)b)
  self->val += a + b;
  retmethod(_1);
endmethod

defmethod(OBJ, gincrBy3, Counter, (U32)a, (U32)b, (U32)c)
  self->val += a + b + c;
  retmethod(_1);
endmethod

defmethod(OBJ, gincrBy4, Counter, (U32)a, (U32)b, (U32)c, (U32)d)
  self->val += a + b + c + d;
  retmethod(_1);
endmethod

defmethod(OBJ, gincrBy5, Counter, (U32)a, (U32)b, (U32)c, (U32)d, (U32)e)
  self->val += a + b + c + d + e;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo1, Counter, Counter)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo2, Counter, Counter, Counter)
  self1->val += self2->val + self3->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo3, Counter, Counter, Counter, Counter)
  self1->val += self2->val + self3->val + self4->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo4, Counter, Counter, Counter, Counter, Counter)
  self1->val += self2->val + self3->val + self4->val + self5->val;
  retmethod(_1);
endmethod

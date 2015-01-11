/**
 * C Object System
 * COS testsuites - Counter class definition
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

defmethod(I32, gint, Counter)
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

defmethod(OBJ, gaddToPlus, Counter, Counter, (U32)a)
  self1->val += self2->val + a;
  retmethod(_1);
endmethod


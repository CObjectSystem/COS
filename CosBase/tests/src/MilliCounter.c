/**
 * C Object System
 * COS testsuites - MilliCounter class definition
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

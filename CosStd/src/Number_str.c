/**
 * C Object System
 * COS Number from/to strings
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

#include <cos/Number.h>
#include <cos/String.h>

#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <stdio.h>

// ----- get

defmethod(OBJ, gget, String, Char)
  if (self->size) {
    self2->Int.value = self->value[0];
    retmethod(True);
  } 
  retmethod(False);
endmethod

defmethod(OBJ, gget, String, Int)
  if (self->size) {
    int res = sscanf(gstr(_1), "%d", &self2->value) == 1;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gget, String, Long)
  if (self->size) {
    long long val = 0;
    int res = sscanf(gstr(_1), "%lld", &val) == 1;
    self2->value = val;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gget, String, Float)
  if (self->size) {
    int res = sscanf(gstr(_1), "%lf", &self2->value) == 1;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gget, String, Complex)
  if (self->size) {
    C64 *cx = &self2->value;
    F64 *re = (F64*)cx;
    F64 *im = re+1;

    int res = sscanf(gstr(_1), "(%lf,%lf)", re, im) == 2;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

// ----- put

defmethod(OBJ, gput, String, Char)
  if (self->size) {
    self->value[0] = self2->Int.value, self->size = 1;
    retmethod(True);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gput, String, Int)
  int n = snprintf((char*)self->value, self->size+1, "%d", self2->value);
  if (n != EOF && n > 0 && (U32)n <= self->size) {
    self->size = n;
    retmethod(True);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gput, String, Long)
  long long val = self2->value;
  int n = snprintf((char*)self->value, self->size+1, "%lld", val);
  if (n != EOF && n > 0 && (U32)n <= self->size) {
    self->size = n;
    retmethod(True);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gput, String, Float)
  int n = snprintf((char*)self->value, self->size+1, "%g", self2->value);
  if (n != EOF && n > 0 && (U32)n <= self->size) {
    self->size = n;
    retmethod(True);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gput, String, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  int n = snprintf((char*)self->value, self->size+1, "(%g,%g)", *re, *im);
  if (n != EOF && n > 0 && (U32)n <= self->size) {
    self->size = n;
    retmethod(True);
  }
  retmethod(False);
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS Number from/to strings
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
 | $Id: Number_str.c,v 1.1 2009/09/25 08:59:46 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/String.h>

#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <stdio.h>

// ----- get

defmethod(OBJ, gget, String, Char)
  PRE POST BODY
    if (self->size) {
      self2->Int.value = self->value[0];
      retmethod(True);
    } 
    retmethod(False);
endmethod

defmethod(OBJ, gget, String, Int)
  PRE POST BODY
    if (self->size) {
      self->value[self->size] = '\0';
      retmethod(sscanf((STR)self->value, "%d", &self2->value) == 1 ? True : False);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gget, String, Long)
  PRE POST BODY
    if (self->size) {
      self->value[self->size] = '\0';
      long long val = 0;
      int res = sscanf((STR)self->value, "%lld", &val) == 1;
      self2->value = val;
      retmethod(res ? True : False);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gget, String, Float)
  PRE POST BODY
    if (self->size) {
      self->value[self->size] = '\0';
      retmethod(sscanf((STR)self->value, "%lf", &self2->value) == 1 ? True : False);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gget, String, Complex)
  PRE POST BODY
    if (self->size) {
      C64 *cx = &self2->value;
      F64 *re = (F64*)cx;
      F64 *im = re+1;

      self->value[self->size] = '\0';
      retmethod(sscanf((STR)self->value, "(%lf,%lf)", re, im) == 2 ? True : False);
    }
    retmethod(False);
endmethod

// ----- put

defmethod(OBJ, gput, String, Char)
  PRE POST BODY
    if (self->size) {
      self->value[0] = self2->Int.value, self->size = 1;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, String, Int)
  PRE POST BODY
    int n = snprintf((char*)self->value, self->size+1, "%d", self2->value);
    if (n != EOF && (U32)n <= self->size) {
      self->size = n;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, String, Long)
  PRE POST BODY
    long long val = self2->value;
    int n = snprintf((char*)self->value, self->size+1, "%lld", val);
    if (n != EOF && (U32)n <= self->size) {
      self->size = n;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, String, Float)
  PRE POST BODY
    int n = snprintf((char*)self->value, self->size+1, "%g", self2->value);
    if (n != EOF && (U32)n <= self->size) {
      self->size = n;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, String, Complex)
  PRE POST BODY
    C64 *cx = &self2->value;
    F64 *re = (F64*)cx;
    F64 *im = re+1;

    int n = snprintf((char*)self->value, self->size+1, "(%g,%g)", *re, *im);
    if (n != EOF && (U32)n <= self->size) {
      self->size = n;
      retmethod(True);
    }
    retmethod(False);
endmethod

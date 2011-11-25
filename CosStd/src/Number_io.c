/**
 * C Object System
 * COS Number
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
#include <cos/File.h>
#include <cos/String.h>

#include <cos/gen/collection.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

// ----- get

defmethod(OBJ, gget, InputStream, Char)
  I32 c = ggetChr(_1);
  
  if (c == EndOfStream)
    retmethod(Nil);

  self2->Int.value = c;

  retmethod(_2);
endmethod

defmethod(OBJ, gget, InputStream, Short)
  U32 n = Stream_parseI16(_1, &self2->Int.value, YES);
  retmethod(n ? _2 : Nil);
endmethod

defmethod(OBJ, gget, InputStream, Int)
  U32 n = Stream_parseI32(_1, &self2->value, YES);
  retmethod(n ? _2 : Nil);
endmethod

defmethod(OBJ, gget, InputStream, Long)
  U32 n = Stream_parseI64(_1, &self2->value, YES);
  retmethod(n ? _2 : Nil);
endmethod

defmethod(OBJ, gget, InputStream, Float)
  U32 n = Stream_parseF64(_1, &self2->value, YES);
  retmethod(n ? _2 : Nil);
endmethod

// ----- put

defmethod(OBJ, gput, OutputStream, Char)
  retmethod(gputChr(_1, self2->Int.value) != EndOfStream ? _1 : Nil);
endmethod

defmethod(OBJ, gput, OutputStream, Int)
  U8  b[32];
  I32 n = snprintf((char*)b, sizeof b, "%ld", (long)self2->value);
  I32 m = gputData(_1, b, n);
  retmethod(m == n ? _1 : Nil);
endmethod

defmethod(OBJ, gput, OutputStream, Long)
  U8  b[32];
  I32 n = snprintf((char*)b, sizeof b, "%lld", (long long)self2->value);
  I32 m = gputData(_1, b, n);
  retmethod(m == n ? _1 : Nil);
endmethod

defmethod(OBJ, gput, OutputStream, Float)
  U8  b[64];
  I32 n = snprintf((char*)b, sizeof b, "%g", self2->value);
  I32 m = gputData(_1, b, n);
  retmethod(m == n ? _1 : Nil);
endmethod

#if 0
// ----- specialization for File

defmethod(OBJ, gget, InFile, Long)
  long long val;
  int res = fscanf(self->OpenFile.fd, "%lld", &val) != 1;
  self2->value = val;
  retmethod(res ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Float)
  retmethod(fscanf(self->OpenFile.fd, "%lf", &self2->value) != 1 ? False : True);
endmethod

defmethod(OBJ, gget, InFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fscanf(self->OpenFile.fd, "(%lf,%lf)", re, im) != 2 ? False : True);
endmethod

// ----- put

defmethod(OBJ, gput, OutFile, Char)
  retmethod(putc(self2->Int.value, self->OpenFile.fd) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Int)
  retmethod(fprintf(self->OpenFile.fd, "%d", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Long)
  long long val = self2->value;
  retmethod(fprintf(self->OpenFile.fd, "%lld", val) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Float)
  retmethod(fprintf(self->OpenFile.fd, "%g", self2->value) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OutFile, Complex)
  C64 *cx = &self2->value;
  F64 *re = (F64*)cx;
  F64 *im = re+1;

  retmethod(fprintf(self->OpenFile.fd, "(%g,%g)", *re, *im) == EOF ? False : True);
endmethod

// ----- Text String (String stream)

// ----- get

defmethod(OBJ, gget, StringDyn, Char)
  struct String *str = &self->StringFix.String;
  
  if (str->size) {
    self2->Int.value = str->value[0];
    str->value++, str->size--;
    retmethod(True);
  } 
  retmethod(False);
endmethod

defmethod(OBJ, gget, StringDyn, Int)
  struct String *str = &self->StringFix.String;

  if (str->size) {
    str->value[str->size] = '\0';
    int n = 0;
    int res = sscanf((STR)str->value, "%d%n", &self2->value, &n) == 2;
    str->value += n, str->size -= n;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gget, StringDyn, Long)
  struct String *str = &self->StringFix.String;

  if (str->size) {
    str->value[str->size] = '\0';
    long long val = 0;
    int n = 0;
    int res = sscanf((STR)str->value, "%lld%n", &val, &n) == 2;
    str->value += n, str->size -= n, self2->value = val;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gget, StringDyn, Float)
  struct String *str = &self->StringFix.String;

  if (str->size) {
    str->value[str->size] = '\0';
    int n = 0;
    int res = sscanf((STR)str->value, "%lf%n", &self2->value, &n) == 2;
    str->value += n, str->size -= n;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

defmethod(OBJ, gget, StringDyn, Complex)
  struct String *str = &self->StringFix.String;

  if (str->size) {
    str->value[str->size] = '\0';
    C64 *cx = &self2->value;
    F64 *re = (F64*)cx;
    F64 *im = re+1;
    int n = 0;
    int res = sscanf((STR)str->value, "(%lf,%lf)%n", re, im, &n) == 3;
    str->value += n, str->size -= n;
    retmethod(res ? True : False);
  }
  retmethod(False);
endmethod

// ----- put

defmethod(OBJ, gput, StringDyn, Char)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;

    if (str->value + str->size == strf->_value + strf->capacity)
      genlarge(_1, aInt(1));

    str->value[str->size++] = self2->Int.value;

    retmethod(True);
endmethod

defmethod(OBJ, gput, StringDyn, Int)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;
    ptrdiff_t extra;

retry:
    extra = (strf->_value + strf->capacity) - (str->value + str->size);
    int n = snprintf((char*)str->value+str->size, extra+1, "%d", self2->value);
    if (n > extra) {
      genlarge(_1, aInt(n));      
      goto retry;
    }

    if (n != EOF && n > 0) {
      str->size += n;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, StringDyn, Long)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;
    long long val = self2->value;
    ptrdiff_t extra;

retry:
    extra = (strf->_value + strf->capacity) - (str->value + str->size);
    int n = snprintf((char*)str->value+str->size, extra+1, "%lld", val);
    if (n > extra) {
      genlarge(_1, aInt(n));      
      goto retry;
    }

    if (n != EOF && n > 0) {
      str->size += n;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, StringDyn, Float)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;
    ptrdiff_t extra;

retry:
    extra = (strf->_value + strf->capacity) - (str->value + str->size);
    int n = snprintf((char*)str->value+str->size, extra+1, "%g", self2->value);
    if (n > extra) {
      genlarge(_1, aInt(n));      
      goto retry;
    }

    if (n != EOF && n > 0) {
      str->size += n;
      retmethod(True);
    }
    retmethod(False);
endmethod

defmethod(OBJ, gput, StringDyn, Complex)
  PRE POST BODY
    struct StringFix *strf = &self->StringFix;
    struct String    *str  = &strf->String;
    C64 *cx = &self2->value;
    F64 *re = (F64*)cx;
    F64 *im = re+1;
    ptrdiff_t extra;

retry:
    extra = (strf->_value + strf->capacity) - (str->value + str->size);
    int n = snprintf((char*)str->value+str->size, extra+1, "(%g,%g)", *re, *im);
    if (n > extra) {
      genlarge(_1, aInt(n));      
      goto retry;
    }

    if (n != EOF && n > 0) {
      str->size += n;
      retmethod(True);
    }
    retmethod(False);
endmethod
#endif

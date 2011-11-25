/**
 * C Object System
 * COS String - strings IO
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

#include <cos/Stream.h>
#include <cos/String.h>

#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/stream.h>

// ----- get

defmethod(OBJ, gget, String, pmString)
  retmethod(gclone(_1));
endmethod

defmethod(OBJ, gget, String, Class)
  forward_message(_1, gautoRelease(gnew(_2)));
endmethod

// ----- getline

defmethod(OBJ, gget, InputStream, StringDyn)
  U8 buf[4096];
  size_t n, cnt = 0;
  
  do {
    n = ggetLine(_1, buf, sizeof buf);
    if (!n) break;
    gappend(_2, aStringRef(buf, n));
    cnt += n;
  } while (buf[n-1] != '\n');

  retmethod(cnt ? _2 : Nil);
endmethod

// ----- put

defmethod(OBJ, gput, OutputStream, String)
  U32 n = gputData(_1, self2->value, self2->size);
  retmethod(n == self2->size ? _1 : Nil);
endmethod


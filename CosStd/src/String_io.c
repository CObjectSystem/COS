/*
 o---------------------------------------------------------------------o
 |
 | COS String - strings IO
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_io.c,v 1.12 2010/06/04 23:27:22 ldeniau Exp $
 |
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


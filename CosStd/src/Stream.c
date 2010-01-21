/*
 o---------------------------------------------------------------------o
 |
 | COS Stream
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
 | $Id: Stream.c,v 1.3 2010/01/21 14:52:54 ldeniau Exp $
 |
*/

#include <cos/Stream.h>

#include <cos/gen/stream.h>

// -----

makclass(Stream);
makclass(InputStream , Stream);
makclass(OutputStream, Stream);

makclass(ExBadStream, Exception);

// ----- stream generic methods

defmethod(OBJ, gflush, Stream)
  if (!self->delegate)
    retmethod(_1);

  forward_message(self->delegate);
  if (RETVAL == self->delegate)
    retmethod(_1);
endmethod

defmethod(size_t, gputData, OutputStream, (U8*)buf, (size_t)len)
  size_t n = 0;

  while (n < len && gputChr(_1, buf[n++]) != EOF)
    ;

  retmethod( n );
endmethod

defmethod(size_t, ggetData, InputStream, (U8*)buf, (size_t)len)
  size_t n = 0;
  I32 c;
  
  while (n < len && (c = ggetChr(_1)) != EOF)
    buf[n++] = (U32)c;

  retmethod( n );
endmethod

defmethod(size_t, ggetDelim, InputStream, (U8*)buf, (size_t)len, (I32)delim)
  U32 n = 0;
  I32 c;
  
  while (n < len && (c = ggetChr(_1)) != EOF && c != delim)
    buf[n++] = (U32)c;

  retmethod( n );
endmethod

defmethod(size_t, ggetLine, InputStream, (U8*)buf, (size_t)len)
  U32 n = 0;
  I32 c, c2;
  
  while (n < len && (c = getChr(_1)) != EOF) {
    if (c == '\n') {
      if ((c2 = getChr(_1)) != EOF && c2 != '\r') gungetChr(_1, c2);
      break;
    }
    
    if (c == '\r') {
      if ((c2 = getChr(_1)) != EOF && c2 != '\n') gungetChr(_1, c2);
      break;
    }

    buf[n++] = (U32)c;
  }

  retmethod( n );
endmethod


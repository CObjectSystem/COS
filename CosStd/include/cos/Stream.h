#ifndef COS_STREAM_H
#define COS_STREAM_H

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
 | $Id: Stream.h,v 1.6 2010/05/26 15:02:00 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: Stream subclasses

<- Stream
  <- InputStream
  <- OutputStream
    
  Streams are buffer-oriented serial channels
*/

defclass(Stream)
endclass

defclass(InputStream, Stream)
endclass

defclass(OutputStream, Stream)
endclass

// ----- exception for streams

#include <cos/Exception.h>

defclass(ExBadStream, Exception)
endclass

// ----- simple parsers

// integer:  [+-]?[0-9]+
// floating: [+-]?[0-9]+(.[0-9]+)?([eE][+-]?[0-9]+)?
U32 Stream_parseI16(OBJ stream, I32 *val, BOOL skipSpc);
U32 Stream_parseI32(OBJ stream, I32 *val, BOOL skipSpc);
U32 Stream_parseI64(OBJ stream, I64 *val, BOOL skipSpc);
U32 Stream_parseF64(OBJ stream, F64 *val, BOOL skipSpc);

#endif // COS_STREAM_H

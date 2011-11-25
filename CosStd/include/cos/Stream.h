#ifndef COS_STREAM_H
#define COS_STREAM_H

/**
 * C Object System
 * COS Stream
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

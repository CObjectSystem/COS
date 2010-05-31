#ifndef COS_GEN_STREAM_H
#define COS_GEN_STREAM_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for streams
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau*cern.ch
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
 | $Id: stream.h,v 1.13 2010/05/31 14:02:58 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// ----- standard errors

enum { EndOfStream = -1 /* EOF */ };

// ----- standard streams

extern OBJ StdIn, StdOut, StdErr, StdLog;

// low-level character primitives (!REQUIRED!)
defgeneric(I32, ggetChr  , _1);           // return EndOfStream or chr
defgeneric(I32, gputChr  , _1, (I32)chr); // return EndOfStream or chr
defgeneric(I32, gungetChr, _1, (I32)chr); // return EndOfStream or chr, unlimited

// ------ primitives below return the number of element processed.

// low-level buffer primitives (optional, default provided by Stream)
defgeneric(size_t, gputData, _1, (U8*)buf, (size_t)len);
defgeneric(size_t, ggetData, _1, (U8*)buf, (size_t)len);

// low-level chars primitives (optional, default provided by Stream)
defgeneric(size_t, gputnChr , _1, (I32)chr, (size_t)len);
defgeneric(size_t, gskipnChr, _1,           (size_t)len);

// low-level string primitives (optional, default provided by Stream)
defgeneric(size_t, gputStr  , _1, (STR)str);
defgeneric(size_t, gputStrLn, _1, (STR)str);

// low-level line primitives I (optional, default provided by Stream)
defgeneric(size_t, ggetLine  , _1, (U8*)buf, (size_t)len);
defgeneric(size_t, ggetDelim , _1, (U8*)buf, (size_t)len, (I32)delim);
defgeneric(size_t, ggetDelims, _1, (U8*)buf, (size_t)len, (STR)delims);

// low-level line primitives II (optional, default provided by Stream)
defgeneric(size_t, gskipLine  , _1);
defgeneric(size_t, gskipDelim , _1, (I32)delim);
defgeneric(size_t, gskipDelims, _1, (STR)delims);

// low-level predicate primitives (optional, default provided by Stream)
defgeneric(size_t, ggetWhile , _1, (U8*)buf, (size_t)len, fun);
defgeneric(size_t, gskipWhile, _1,                        fun);

// ------ primitives below return Nil on failure.

// high-level stream primitives (optional, default provided by Stream)
defgeneric(OBJ, ggetLines  , _1); // return an array of strings
defgeneric(OBJ, ggetContent, _1); // return a string

// high-level object primitives (provided by non-streams)
defgeneric(OBJ, gget, _1, _2);  // return the object
defgeneric(OBJ, gput, _1, _2);  // return the object

// high-level object primitives (optional, default provided by Stream)
defgeneric(OBJ, gputLn, _1, _2); // return the object

// flush stream
defgeneric(OBJ, gflush, _1);     // return the stream

#endif // COS_GEN_STREAM_H

#ifndef COS_GEN_STREAM_H
#define COS_GEN_STREAM_H

/**
 * C Object System
 * COS generics for streams
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

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
 | $Id: stream.h,v 1.6 2010/01/21 14:12:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>

defgeneric(OBJ, gopen  , _1, name, mode);
defgeneric(OBJ, gclose , _1);
defgeneric(OBJ, gflush , _1);

// low-level character primitives (required)
defgeneric(I32, ggetChr  , _1);
defgeneric(I32, gputChr  , _1, (I32)chr);
defgeneric(I32, gungetChr, _1, (I32)chr);

// low-level buffer primitives (optional, return number of bytes read/written)
defgeneric(size_t, gputData, _1, (U8*)buf, (size_t)len);
defgeneric(size_t, ggetData, _1, (U8*)buf, (size_t)len);

// high-level line primitives (optional)
defgeneric(size_t, ggetLine , _1, (U8*)buf, (size_t)len);
defgeneric(size_t, ggetDelim, _1, (U8*)buf, (size_t)len, (I32)delim);

// high-level object primitives (optional for back-end)
defgeneric(OBJ, gget  , _1, _2); // (return Object or Nil on error)
defgeneric(OBJ, gput  , _1, _2); // (return Stream or Nil on error)
defgeneric(OBJ, gputLn, _1, _2); // (return Stream or Nil on error)

#endif // COS_GEN_STREAM_H

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
 | $Id: stream.h,v 1.4 2009/09/21 07:55:06 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <stdio.h>

defgeneric(OBJ , gopen  , _1, name, mode);
defgeneric(void, gclose , _1);
defgeneric(void, gflush , _1);
defgeneric(void, gremove, _1);

// primitives
defgeneric(I32, ggetChr  , _1);
defgeneric(I32, gputChr  , _1, (I32)chr);
defgeneric(I32, gungetChr, _1, (I32)chr);

// return True (success) or False (failure)
defgeneric(OBJ, gget    , _1, _2);
defgeneric(OBJ, ggetLine, _1, _2);
defgeneric(OBJ, ggetData, _1, _2);

defgeneric(OBJ, gput    , _1, _2);
defgeneric(OBJ, gputLn  , _1, _2);

// low-level FILE access (may be removed in the future)
defgeneric(FILE*, ggetFILE, _1);
defgeneric(void , gsetFILE, _1, (FILE*)fd, (STR)mode, (STR)name);

#endif // COS_GEN_STREAM_H

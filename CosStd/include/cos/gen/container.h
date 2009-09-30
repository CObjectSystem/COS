#ifndef COS_GEN_CONTAINER_H
#define COS_GEN_CONTAINER_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for containers
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
 | $Id: container.h,v 1.17 2009/09/30 12:09:58 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// list-like accessor
defgeneric(void, ginsertAt , _1, at, what);
defgeneric(void, gremoveAt , _1, at);

// stack-like accessors
defgeneric(void, gpush     , _1, what);
defgeneric(OBJ , gtop      , _1);
defgeneric(void, gpop      , _1);

// dequeue-like accessors
defgeneric(void, gpushFront, _1, what);
defgeneric(void, gpushBack , _1, what);
defgeneric(void, gpopFront , _1);
defgeneric(void, gpopBack  , _1);
defgeneric(OBJ , gfront    , _1);
defgeneric(OBJ , gback     , _1);

// seq-like accessor
defgeneric(void, gprepend  , _1, what);
defgeneric(void, gappend   , _1, what);
defgeneric(void, gchop     , _1, what);
defgeneric(void, gdrop     , _1, num); // front if num<0
defgeneric(void, gdropFirst, _1);
defgeneric(void, gdropLast , _1);
defgeneric(OBJ , gfirst    , _1);
defgeneric(OBJ , glast     , _1);

// check for elements
defgeneric(OBJ , gisEmpty  , _1);

// adjust object (e.g. capacity to size)
defgeneric(OBJ , gadjust   , _1);

// englarge object memory (e.g. front if by<0)
defgeneric(void, genlarge  , _1, by);

#endif // COS_GEN_CONTAINER_H

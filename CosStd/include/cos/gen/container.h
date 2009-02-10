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
 | $Id: container.h,v 1.6 2009/02/10 13:03:22 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// stream-like accessors
defgeneric(OBJ , gget       , _1);
defgeneric(void, gput       , _1, what);

// stack-like accessors
defgeneric(void, gpush      , _1, what);  // alias for gput
defgeneric(OBJ , gtop       , _1);        // alias for gget
defgeneric(void, gpop       , _1);        // alias for gdrop

// seq-like accessor
defgeneric(void, gappend    , _1, what);
defgeneric(void, ginsert    , _1, what);
defgeneric(OBJ , gfirst     , _1);
defgeneric(OBJ , glast      , _1);

// raw data (copy) accessors
defgeneric(void, ggetValue  , _1, what);
defgeneric(void, ggetValueAt, _1, what, at);

// drop element
defgeneric(void, gdrop      , _1);
defgeneric(void, gdropAt    , _1, at);

// check for element
defgeneric(OBJ , gisEmpty   , _1);

// adjust object (e.g. capacity to size)
defgeneric(void, gadjust    , _1);

#endif // COS_GEN_CONTAINER_H

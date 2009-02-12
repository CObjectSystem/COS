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
 | $Id: container.h,v 1.9 2009/02/12 08:47:53 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// stream-like accessors
defgeneric(OBJ , gget       , _1);
defgeneric(void, gput       , _1, what);
defgeneric(void, gdrop      , _1);

// stack-like accessors
defgeneric(void, gpush      , _1, what);  // alias for gput
defgeneric(OBJ , gtop       , _1);        // alias for gget
defgeneric(void, gpop       , _1);        // alias for gdrop

// list-like accessor
defgeneric(void, ginsert    , _1, what, at);
defgeneric(void, gremove    , _1, at);

// seq-like accessor
defgeneric(void, gprepend   , _1, what);
defgeneric(void, gappend    , _1, what);
defgeneric(OBJ , gfirst     , _1);
defgeneric(OBJ , glast      , _1);

// raw data (copy) accessors
defgeneric(void, ggetValue  , _1, what);
defgeneric(void, ggetValueAt, _1, what, at);

// check for elements
defgeneric(OBJ , gisEmpty   , _1);
defgeneric(OBJ , gisPrefixOf, _1, _2);
defgeneric(OBJ , gisSuffixOf, _1, _2);

// adjust object (e.g. capacity to size)
defgeneric(void, gadjust    , _1);

#endif // COS_GEN_CONTAINER_H

#ifndef COS_GEN_ACCESS_H
#define COS_GEN_ACCESS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics accessor
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
 | $Id: access.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// generic accessors
defgeneric(OBJ, gput     , _1, _2);
defgeneric(OBJ, gget     , _1);
defgeneric(OBJ, gdrop    , _1);
defgeneric(OBJ, gupdate  , _1, _2);

// generic accessors with location
defgeneric(OBJ, gputAt   , _1, _2, at);
defgeneric(OBJ, ggetAt   , _1, at);
defgeneric(OBJ, gdropAt  , _1, at);
defgeneric(OBJ, gupdateAt, _1, _2, at);

// stack-like or queue-like accessors
defgeneric(OBJ, gpush    , _1, _2); // alias for gput
defgeneric(OBJ, gtop     , _1);     // alias for gget
defgeneric(OBJ, gpop     , _1);     // alias for gdrop

#endif // COS_GEN_ACCESS_H

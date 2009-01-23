#ifndef COS_GEN_ACCESSOR_H
#define COS_GEN_ACCESSOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for accessor
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
 | $Id: accessor.h,v 1.1 2009/01/23 10:34:58 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// generic accessors
defgeneric(void, gput, to, what);
defgeneric(OBJ , gget, from);

// generic accessors with location
defgeneric(void, gputAt, to, what, at);
defgeneric(OBJ , ggetAt, from, at);

#endif // COS_GEN_ACCESSOR_H

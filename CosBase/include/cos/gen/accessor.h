#ifndef COS_GEN_ACCESSOR_H
#define COS_GEN_ACCESSOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS accessor generics
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
 | $Id: accessor.h,v 1.8 2010/01/03 11:02:39 ldeniau Exp $
 |
*/

#ifndef COS_GACCESSOR_H
#include <cos/GAccessor.h>
#endif 

// getters, setters, properties, keys
defgeneric(OBJ, (GGetter) ggetAt, _1, at);
defgeneric(OBJ, (GSetter) gputAt, _1, at, what);

// common case for indexes
defgeneric(OBJ, (GGetter) ggetAtIdx, _1, (I32)idx);
defgeneric(OBJ, (GSetter) gputAtIdx, _1, (I32)idx, what);

#endif // COS_GEN_ACCESSOR_H

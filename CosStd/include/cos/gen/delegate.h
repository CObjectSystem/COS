#ifndef COS_GEN_DELEGATE_H
#define COS_GEN_DELEGATE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS delegate generics
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
 | $Id: delegate.h,v 1.1 2010/02/02 16:28:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// getters, setters
defgeneric(OBJ, gdelegate   , _1);
defgeneric(OBJ, gsetDelegate, _1, del);

#endif // COS_GEN_DELEGATE_H

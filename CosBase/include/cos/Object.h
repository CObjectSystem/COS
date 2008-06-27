#ifndef COS_OBJECT_H
#define COS_OBJECT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Object
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
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
 | $Id: Object.h,v 1.1 2008/06/27 16:17:14 ldeniau Exp $
 |
*/

/*
 * --------------------------------------
 * Standard markers used inside the code:
 * --------------------------------------
 * NOTE-USER: mark the presence of comments for user
 * NOTE-INFO: mark the presence of comments for developer
 * NOTE-CONF: mark where configuration matters
 * NOTE-PORT: mark where portability matters
 * NOTE-TODO: mark where something needs to be done
 * --------------------------------------
 */

// <cos/Object.h> is a prefered alternative to <cos/cos/cos.h>
#ifndef COS_COS_COS_H
#include <cos/cos/cos.h>
#endif

// Object is a core class, see cos/cos/coscls.h

#endif // COS_OBJECT_H

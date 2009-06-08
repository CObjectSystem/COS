#ifndef COS_CFG_DARWIN_H
#define COS_CFG_DARWIN_H

/*
 o---------------------------------------------------------------------o
 |
 | COS config: Darwin
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
 | $Id: Darwin.h,v 1.3 2009/06/08 22:35:43 ldeniau Exp $
 |
*/

#define COS_HAVE_TLS   0
#define COS_HAVE_POSIX 1

#define COS_LIB_PREFIX "lib"
#define COS_LIB_SHEXT  ".so"

#endif // COS_CFG_DARWIN_H

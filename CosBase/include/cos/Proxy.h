#ifndef COS_PROXY_H
#define COS_PROXY_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Proxy (root class)
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
 | $Id: Proxy.h,v 1.4 2010/05/26 22:46:29 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: Proxy behavior

   A proxy is an object which aims to be as 'transparent' as possible
   while behaving on behalf of its delegate.

   Derive your own proxy from the Proxy class to implement your
   specific behaviors or hide its true nature.
*/

defclass(Proxy)
  OBJ obj;
endclass

#endif // COS_PROXY_H

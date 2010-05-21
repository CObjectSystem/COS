#ifndef COS_LOCKER_H
#define COS_LOCKER_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Locker (proxy)
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
 | $Id: Locker.h,v 1.4 2010/05/21 14:59:07 ldeniau Exp $
 |
*/

#include <cos/Proxy.h>

#if COS_HAVE_POSIX

#include <pthread.h>

defclass(Locker, Proxy)
  pthread_mutex_t lock;
endclass

#else

defclass(Locker, Proxy)
endclass

#endif

#endif // COS_LOCKER_H

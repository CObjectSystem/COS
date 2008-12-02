#ifndef COS_ERRNO_H
#define COS_ERRNO_H

/*
 o---------------------------------------------------------------------o
 |
 | COS TestErrno
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
 | $Id: errno.h,v 1.4 2008/12/02 17:32:21 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

#include <errno.h>

/* NOTE-USER: errno handler
   - throw ExErrno if errno != 0
   - use gint(err) from cos/gen/value.h to retrieve errno value
*/
#define test_errno() \
        ((void)(errno && \
         (cos_exception_errno(errno,__FUNC__,__FILE__,__LINE__),0)))

#endif // COS_ERRNO_H

#ifndef COS_STDEX_H
#define COS_STDEX_H

/*
 o---------------------------------------------------------------------o
 |
 | COS standard exceptions
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
 | $Id: stdex.h,v 1.1 2008/06/27 16:17:15 ldeniau Exp $
 |
*/

#include <cos/Exception.h>

defclass(ExBadAlloc      ,Exception) endclass
defclass(ExBadArity      ,Exception) endclass
defclass(ExBadAssert     ,Exception) endclass
defclass(ExBadCast       ,Exception) endclass
defclass(ExBadDomain     ,Exception) endclass
defclass(ExBadFormat     ,Exception) endclass
defclass(ExBadMessage    ,Exception) endclass
defclass(ExBadRange      ,Exception) endclass
defclass(ExBadSize       ,Exception) endclass
defclass(ExBadType       ,Exception) endclass
defclass(ExBadValue      ,Exception) endclass
defclass(ExNotFound      ,Exception) endclass
defclass(ExNotImplemented,Exception) endclass
defclass(ExNotSupported  ,Exception) endclass
defclass(ExOverflow      ,Exception) endclass
defclass(ExUnderflow     ,Exception) endclass

defclass(ExErrno,Exception)
  int err;
endclass

defclass(ExSignal,Exception)
  int sig;
endclass

#endif // COS_STDEX_H

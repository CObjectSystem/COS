#ifndef COS_EXCEPTION_H
#define COS_EXCEPTION_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Exception
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
 | $Id: Exception.h,v 1.10 2010/05/26 22:46:29 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: exception
   - use gstr(ex) from cos/gen/value.h to retrieve the reason
   - use gobj(ex) from cos/gen/value.h to retrieve the object
*/

defclass(Exception)
  OBJ   obj;
  char *str;
endclass

defclass(ExErrno, Exception)
  int err;
endclass

defclass(ExSignal, Exception)
  int sig;
endclass

defclass(ExBadAlloc      , Exception) endclass
defclass(ExBadArity      , Exception) endclass
defclass(ExBadAssert     , Exception) endclass
defclass(ExBadCast       , Exception) endclass
defclass(ExBadDomain     , Exception) endclass
defclass(ExBadFormat     , Exception) endclass
defclass(ExBadMessage    , Exception) endclass
defclass(ExBadMode       , Exception) endclass
defclass(ExBadProperty   , Exception) endclass
defclass(ExBadPredicate  , Exception) endclass
defclass(ExBadRange      , Exception) endclass
defclass(ExBadSize       , Exception) endclass
defclass(ExBadType       , Exception) endclass
defclass(ExBadValue      , Exception) endclass
defclass(ExNotFound      , Exception) endclass
defclass(ExNotImplemented, Exception) endclass
defclass(ExNotSupported  , Exception) endclass
defclass(ExOverflow      , Exception) endclass
defclass(ExUnderflow     , Exception) endclass

#endif // COS_EXCEPTION_H

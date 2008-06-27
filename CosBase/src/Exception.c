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
 | $Id: Exception.c,v 1.1 2008/06/27 16:17:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Exception.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

makclass(Exception,Object);

defmethod(OBJ, ginit, Exception)
  self->str = 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithStr, Exception, (STR)str)
  self->str = str;
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Exception)
  self->str = 0;
  retmethod(_1);
endmethod

defmethod(STR, gstr, Exception)
  retmethod(self->str);
endmethod


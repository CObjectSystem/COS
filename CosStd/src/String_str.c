/*
 o---------------------------------------------------------------------o
 |
 | COS String - strings on string streams
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_str.c,v 1.4 2010/05/31 14:02:58 ldeniau Exp $
 |
*/

#include <cos/String.h>

#include <cos/gen/collection.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>

defmethod(OBJ, gget, String, pmString)
  retmethod(gclone(_1));
endmethod

defmethod(OBJ, gget, String, Class)
  forward_message(_1, gautoRelease(gnew(_2)));
endmethod


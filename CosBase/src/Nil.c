/*
 o---------------------------------------------------------------------o
 |
 | COS Nil (root class)
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
 | $Id: Nil.c,v 1.7 2010/01/13 21:29:04 ldeniau Exp $
 |
*/

#include <cos/Nil.h>

#include <cos/gen/object.h>

// -----

makclass(Nil,_);

// -----

defalias (OBJ, (gclone)gdeepClone, mNil);
defmethod(OBJ,  gclone           , mNil)
  retmethod(_1);
endmethod

defmethod(OBJ, gisNil, pmNil)
  retmethod(True);
endmethod

defmethod(OBJ, gisNil, Object)
  retmethod(False);
endmethod


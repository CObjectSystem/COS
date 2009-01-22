/*
 o---------------------------------------------------------------------o
 |
 | COS Object (root class)
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
 | $Id: Object.c,v 1.9 2009/01/22 16:45:07 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>

#include <stdlib.h>

// ----- shared private implementation

#include "./Object_p.h"

// -----

makclass(Object,Any);

// ----- allocator, deallocator

defmethod(OBJ, galloc, mObject)
  retmethod( object_alloc(_1, 0) );
endmethod

defmethod(OBJ, gallocWithSize, mObject, (size_t)extra)
  retmethod( object_alloc(_1, extra) );
endmethod


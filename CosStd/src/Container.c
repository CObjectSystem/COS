/*
 o---------------------------------------------------------------------o
 |
 | COS Container
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
 | $Id: Container.c,v 1.3 2009/11/27 09:40:10 ldeniau Exp $
 |
*/

#include <cos/Container.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// -----

makclass(Container);

// ----- properties

defmethod(OBJ, ggetAt, Object, mP_size)
  retmethod( gautoDelete(aInt(gsize(_1))) );
endmethod

// ----- indexes

defmethod(OBJ, ggetAtIdx, Object, (I32)idx)
  retmethod(ggetAt(_1, aInt(idx)));
endmethod

defmethod(OBJ, gputAtIdx, Object, (I32)idx, Object)
  retmethod(gputAt(_1, aInt(idx), _2));
endmethod


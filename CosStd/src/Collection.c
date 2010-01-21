/*
 o---------------------------------------------------------------------o
 |
 | COS Collection
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
 | $Id: Collection.c,v 1.3 2010/01/21 14:52:54 ldeniau Exp $
 |
*/


#include <cos/Collection.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// -----

makclass(Collection);

// ----- properties

defmethod(OBJ, ggetAt, Collection, mP_size)
  retmethod( gautoDelete(aInt(gsize(_1))) );
endmethod


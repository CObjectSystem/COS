/*
 o---------------------------------------------------------------------o
 |
 | COS Sequence
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
 | $Id: Sequence.c,v 1.14 2009/08/29 21:33:40 ldeniau Exp $
 |
*/

#include <cos/Sequence.h>
#include <cos/Slice.h>

#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

makclass(Sequence     , Container);
makclass(ValueSequence, Sequence );

// -----

defmethod(OBJ, gdeinit, ValueSequence)
  retmethod(_1);
endmethod


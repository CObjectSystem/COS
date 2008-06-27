/*
 o---------------------------------------------------------------------o
 |
 | COS Pointer
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
 | $Id: Pointer.c,v 1.1 2008/06/27 16:17:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Pointer.h>
#include <cos/gen/object.h>

makclass(Pointer,Value);
makclass(AllocPointer,Pointer);
makclass(Function,Value);

// -----

defmethod(OBJ, gdeinit, AllocPointer)
  if (self->pfree)
    self->pfree(self->Pointer.ptr), self->Pointer.ptr = 0;
  retmethod(_1);
endmethod

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
 | $Id: Object.c,v 1.4 2008/07/15 08:00:46 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/gen/object.h>

#include <stdlib.h>

// -----

makclass(Object,Any);

// ----- allocator, deallocator

defmethod(OBJ, galloc, mObject)
  useclass(ExBadAlloc);

  struct Class *cls = STATIC_CAST(struct Class*, _1);
  struct Object *obj = malloc(cls->isz);

  if (!obj) THROW(ExBadAlloc);

  obj->Any.id = cls->Behavior.id;
  obj->Any.rc = COS_RC_UNIT;

  retmethod( (OBJ)obj );
endmethod

defmethod(OBJ, gallocWith, mObject, UInt) // alloc with extra size (max 4GB)
  useclass(ExBadAlloc, ExBadSize);

  struct Class *cls = STATIC_CAST(struct Class*, _1);
  size_t sz = (size_t)cls->isz + self2->val;
  struct Object *obj;
  
  if (sz < cls->isz)
    THROW( gnewWithStr(ExBadSize, "memory allocation size too big (overflow)") );
  
  obj = malloc(sz);

  if (!obj) THROW(ExBadAlloc); // throw the class, no allocation!

  obj->Any.id = cls->Behavior.id;
  obj->Any.rc = COS_RC_UNIT;

  retmethod( (OBJ)obj );
endmethod


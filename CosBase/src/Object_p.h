#ifndef COS_SRC_OBJECT_H
#define COS_SRC_OBJECT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS object private header
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
 | $Id: Object_p.h,v 1.2 2008/11/07 14:12:07 ldeniau Exp $
 |
*/

static inline void*
object_alloc(OBJ _cls, SIZE extra)
{
  useclass(ExBadAlloc);
  struct Class *cls = STATIC_CAST(struct Class*, _cls);
  struct Object *obj = calloc(1, cls->isz + extra);

  if (!obj) THROW(ExBadAlloc); // throw the class (no allocation)

  obj->Any.id = cos_class_id(cls);
  obj->Any.rc = COS_RC_UNIT;

  return obj;
}

#endif // COS_SRC_OBJECT_H


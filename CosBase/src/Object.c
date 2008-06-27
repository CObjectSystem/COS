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
 | $Id: Object.c,v 1.2 2008/06/27 16:53:06 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/gen/object.h>

#include <stdlib.h>

// -----

makclass(Object,Any);

// ----- newXXX, clone

defmethod(OBJ, gnew, mObject)
  retmethod( ginit(galloc(_1)) );
endmethod

defmethod(OBJ, gnewWith, mObject, Any)
  retmethod( ginitWith(galloc(_1),_2) );
endmethod

defmethod(OBJ, gnewWith2, mObject, Any, Any)
  retmethod( ginitWith2(galloc(_1),_2,_3) );
endmethod

defmethod(OBJ, gnewWith3, mObject, Any, Any, Any)
  retmethod( ginitWith3(galloc(_1),_2,_3,_4) );
endmethod

defmethod(OBJ, gnewWith4, mObject, Any, Any, Any, Any)
  retmethod( ginitWith4(galloc(_1),_2,_3,_4,_5) );
endmethod

defmethod(OBJ, gnewWithLoc, mObject, Any, (STR)file, (int)line)
  retmethod( ginitWithLoc(galloc(_1),_2,file,line) );
endmethod

defmethod(OBJ, gnewWithInt, mObject, (int)val)
  retmethod( ginitWithInt(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithStr, mObject, (STR)str)
  retmethod( ginitWithStr(galloc(_1),str) );
endmethod

defmethod(OBJ, gclone, Object)
  retmethod( ginitWith(galloc(gclass(_1)),_1) );
endmethod

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

defmethod(OBJ, gallocWith, mObject, Size) // alloc with extra size
  useclass(ExBadAlloc);

  struct Class *cls = STATIC_CAST(struct Class*, _1);
  struct Object *obj = malloc(cls->isz + self2->val);

  if (!obj) THROW(ExBadAlloc);

  obj->Any.id = cls->Behavior.id;
  obj->Any.rc = COS_RC_UNIT;

  retmethod( (OBJ)obj );
endmethod

defmethod(void, gdealloc, Object)
  PRE  TestAssert( self->Any.rc == COS_RC_UNIT );
  BODY free(_1);
endmethod

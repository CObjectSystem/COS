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
 | $Id: Object.c,v 1.10 2009/02/25 23:06:39 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/prp/object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

#include <stdlib.h>

// -----

makclass(Object,_);

// ----- exceptions

useclass(ExBadAlloc, ExBadMessage);

// ----- properties

defmethod(OBJ, ggetAt, Object, mP_class)
  retmethod( (OBJ)cos_class_get(self->id) );
endmethod

// ----- allocator, deallocator

static inline void*
object_alloc(OBJ _cls, size_t extra)
{
  struct Class *cls = STATIC_CAST(struct Class*, _cls);
  struct Object *obj = calloc(1, cls->isz + extra);

  if (!obj) THROW(ExBadAlloc); // throw the class (no allocation)

  obj->id = cos_class_id(cls);
  obj->rc = COS_RC_UNIT;

  return obj;
}

defmethod(OBJ, galloc, mObject)
  retmethod( object_alloc(_1, 0) );
endmethod

defmethod(OBJ, gallocWithSize, mObject, (size_t)extra)
  retmethod( object_alloc(_1, extra) );
endmethod

// ----- deallocator

defmethod(void, gdealloc, Object)
  free(_1);
endmethod

// ----- ownership

defmethod(U32, gretainCount, Object)
  retmethod( self->rc );
endmethod

// ----- identity, conversion, coercion

defmethod(OBJ, gisInstanceOf, Object, Class)
  retmethod( self1->id == self2->Behavior.id ? True : False );
endmethod

defmethod(OBJ, gisKindOf, Object, Class)
  retmethod( self1->id == self2->Behavior.id ||
             cos_object_isKindOf(_1,self2)
             ? True : False );
endmethod

defmethod(OBJ, gclass, Object)
  retmethod( (OBJ)cos_class_get(self->id) );
endmethod

defmethod(STR, gclassName, Object)
  retmethod( cos_class_get(self->id)->name );
endmethod

// ----- understanding

defmethod(OBJ, gunderstandMessage1, Object, (SEL)msg)
  retmethod( cos_method_understand1(msg, self1->id)
             ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage2, Object, Object, (SEL)msg)
  retmethod( cos_method_understand2(msg, self1->id, self2->id)
             ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage3, Object, Object, Object, (SEL)msg)
  retmethod( cos_method_understand3(msg, self1->id, self2->id, self3->id)
             ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Object, Object, Object, (SEL)msg)
 retmethod( cos_method_understand4(msg, self1->id, self2->id, self3->id,
                                        self4->id)
            ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Object, Object, Object, (SEL)msg)
 retmethod( cos_method_understand5(msg, self1->id, self2->id, self3->id,
                                        self4->id, self5->id)
            ? True : False );
endmethod

// ----- unrecognized

static void
trace(SEL sel, OBJ obj[])
{
  char buf[128];
  cos_debug("<Object> unrecognized message %s",
            cos_method_call(sel, obj, buf, sizeof buf));
}

defmethod(void, gunrecognizedMessage1, Object)
  OBJ obj[1]; obj[0]=_1;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->name) );
endmethod

defmethod(void, gunrecognizedMessage2, Object, Object)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->name) );
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Object)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->name) );
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Object)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->name) );
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Object)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->name) );
endmethod


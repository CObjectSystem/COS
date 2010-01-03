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
 | $Id: Object.c,v 1.22 2010/01/03 14:12:41 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>
#include <cos/gen/init.h>
#include <cos/gen/new.h>

#include <cos/prp/object.h>

#include <stdlib.h>

// ----- root class

makclass(Object,_);

// ----- exceptions

useclass(ExBadAlloc, ExBadMessage);

// ----- properties (read-only)

defmethod(OBJ, ggetAt, Object, mP_class)
  retmethod(gclass(_1));
endmethod

// ----- allocator, deallocator

static COS_ALWAYS_INLINE void*
object_alloc(OBJ _cls, size_t extra)
{
  struct Class *cls = STATIC_CAST(struct Class*, _cls);
  struct Object *obj = malloc(cls->isz + extra);

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
  PRE
    test_assert(self->id && self->rc != COS_RC_INVALID, "object already destroyed");
  BODY
    self->id = 0;
    self->rc = COS_RC_INVALID;
    free(_1);
endmethod

// ----- clone

defalias (OBJ, (gclone)gdeepClone, Object)
defmethod(OBJ,  gclone           , Object)
  retmethod( gnewWith(gclass(_1),_1) );
endmethod

// ----- new

defmethod(OBJ, gnew, mObject)
  retmethod( ginit(galloc(_1)) );
endmethod

defmethod(OBJ, gnewWith, mObject, Object)
  retmethod( ginitWith(galloc(_1),_2) );
endmethod

defmethod(OBJ, gnewWith2, mObject, Object, Object)
  retmethod( ginitWith2(galloc(_1),_2,_3) );
endmethod

defmethod(OBJ, gnewWith3, mObject, Object, Object, Object)
  retmethod( ginitWith3(galloc(_1),_2,_3,_4) );
endmethod

defmethod(OBJ, gnewWith4, mObject, Object, Object, Object, Object)
  retmethod( ginitWith4(galloc(_1),_2,_3,_4,_5) );
endmethod

defmethod(OBJ, gnewWithLoc, mObject, Object, (STR)func, (STR)file, (int)line)
  retmethod( ginitWithLoc(galloc(_1),_2,func,file,line) );
endmethod

defmethod(OBJ, gnewWithStr, mObject, (STR)str)
  retmethod( ginitWithStr(galloc(_1),str) );
endmethod

defmethod(OBJ, gnewWithObj, mObject, (OBJ)obj)
  retmethod( ginitWithObj(galloc(_1),obj) );
endmethod

defmethod(OBJ, gnewWithObj2, mObject, (OBJ)obj, (OBJ)obj2)
  retmethod( ginitWithObj2(galloc(_1),obj,obj2) );
endmethod

defmethod(OBJ, gnewWithObj3, mObject, (OBJ)obj, (OBJ)obj2, (OBJ)obj3)
  retmethod( ginitWithObj3(galloc(_1),obj,obj2,obj3) );
endmethod

defmethod(OBJ, gnewWithObj4, mObject, (OBJ)obj, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4)
  retmethod( ginitWithObj4(galloc(_1),obj,obj2,obj3,obj4) );
endmethod

defmethod(OBJ, gnewWithObj5, mObject, (OBJ)obj, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4, (OBJ)obj5)
  retmethod( ginitWithObj5(galloc(_1),obj,obj2,obj3,obj4,obj5) );
endmethod

defmethod(OBJ, gnewWithChr, mObject, (I32)val)
  retmethod( ginitWithChr(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithSht, mObject, (I32)val)
  retmethod( ginitWithSht(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithInt, mObject, (I32)val)
  retmethod( ginitWithInt(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithLng, mObject, (I64)val)
  retmethod( ginitWithLng(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithFlt, mObject, (F64)val)
  retmethod( ginitWithFlt(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithCpx, mObject, (C64)val)
  retmethod( ginitWithCpx(galloc(_1),val) );
endmethod

defmethod(OBJ, gnewWithChrPtr, mObject, (I8*)ref, (U32)n, (I32)s)
  retmethod( ginitWithChrPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithShtPtr, mObject, (I16*)ref, (U32)n, (I32)s)
  retmethod( ginitWithShtPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithIntPtr, mObject, (I32*)ref, (U32)n, (I32)s)
  retmethod( ginitWithIntPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithLngPtr, mObject, (I64*)ref, (U32)n, (I32)s)
  retmethod( ginitWithLngPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithFltPtr, mObject, (F64*)ref, (U32)n, (I32)s)
  retmethod( ginitWithFltPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithCpxPtr, mObject, (C64*)ref, (U32)n, (I32)s)
  retmethod( ginitWithCpxPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithObjPtr, mObject, (OBJ*)ref, (U32)n, (I32)s)
  retmethod( ginitWithObjPtr(galloc(_1),ref,n,s) );
endmethod

defmethod(OBJ, gnewWithVoidPtr, mObject, (void*)ref, (U32)n, (I32)s, (size_t)esize)
  retmethod( ginitWithVoidPtr(galloc(_1),ref,n,s,esize) );
endmethod

// ----- ownership

defmethod(U32, gretainCount, Object)
  retmethod( self->rc );
endmethod

// ----- identity

defmethod(OBJ, gisInstanceOf, Object, Class)
  retmethod( self1->id == self2->Behavior.id ? True : False );
endmethod

defmethod(OBJ, gisKindOf, Object, Class)
  retmethod( self1->id == self2->Behavior.id || cos_object_isKindOf(_1,self2)
             ? True : False );
endmethod

defmethod(OBJ, gclass, Object)
  retmethod( (OBJ)cos_class_get(self->id) );
endmethod

defmethod(STR, gclassName, Object)
  retmethod( cos_class_get(self->id)->str );
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
 retmethod( cos_method_understand4(msg, self1->id, self2->id,
                                        self3->id, self4->id)
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

  THROW( gnewWithStr(ExBadMessage, _sel->str) );
endmethod

defmethod(void, gunrecognizedMessage2, Object, Object)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->str) );
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Object)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->str) );
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Object)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->str) );
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Object)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);

  THROW( gnewWithStr(ExBadMessage, _sel->str) );
endmethod


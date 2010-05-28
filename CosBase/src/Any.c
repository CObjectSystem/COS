/*
 o---------------------------------------------------------------------o
 |
 | COS Any (root class)
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
 | $Id: Any.c,v 1.25 2010/05/28 08:39:12 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

#include <cos/prp/object.h>

#include <stdlib.h>

// ----- root class

makclass(Any, _);

// ----- exceptions

useclass(ExBadAlloc, ExBadMessage);

// ----- properties (read-only)

defmethod(OBJ, ggetAt, Any, mP_class)
  retmethod(gclass(_1));
endmethod
   
// ----- allocator

defmethod(OBJ, galloc, mAny)
  struct Any *obj = malloc(self->isz);

  if (!obj) THROW(ExBadAlloc); // throw the class (no allocation)

  obj->_id = cos_class_id(self);
  obj->_rc = COS_RC_UNIT;

  retmethod( (OBJ)obj );
endmethod

defmethod(OBJ, gallocWithSize, mAny, (size_t)extra)
  PRE
    test_assert(self->isz+extra > extra, "size overflow");
  BODY
    struct Any *obj = malloc(self->isz + extra);

    if (!obj) THROW(ExBadAlloc); // throw the class (no allocation)

    obj->_id = cos_class_id(self);
    obj->_rc = COS_RC_UNIT;

    retmethod( (OBJ)obj );
endmethod

// ----- deallocator

defmethod(void, gdealloc, Any)
  free(_1);
endmethod

// ----- ownership

defmethod(U32, gretainCount, Any)
  retmethod( cos_object_rc(_1) );
endmethod

// ----- identity

defmethod(OBJ, gisInstanceOf, Any, Class)
  retmethod( cos_object_isa(_1, self2) ? True : False );
endmethod

defmethod(OBJ, gisKindOf, Any, Class)
  retmethod( cos_object_isa     (_1, self2) ||
             cos_object_isKindOf(_1, self2) ? True : False );
endmethod

defmethod(OBJ, gclass, Any)
  retmethod( (OBJ)cos_class_get(cos_object_id(_1)) );
endmethod

defmethod(STR, gclassName, Any)
  retmethod( cos_class_get(cos_object_id(_1))->str );
endmethod

// ----- understanding

defmethod(OBJ, gunderstandMessage1, Any, (SEL)sel)
  retmethod( cos_method_understand1(sel, cos_object_id(_1))
             ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage2, Any, Any, (SEL)sel)
  retmethod( cos_method_understand2(sel, cos_object_id(_1), cos_object_id(_2))
             ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage3, Any, Any, Any, (SEL)sel)
  retmethod( cos_method_understand3(sel, cos_object_id(_1), cos_object_id(_2),
                                         cos_object_id(_3))
             ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage4, Any, Any, Any, Any, (SEL)sel)
 retmethod( cos_method_understand4(sel, cos_object_id(_1), cos_object_id(_2),
                                        cos_object_id(_3), cos_object_id(_4))
            ? True : False );
endmethod

defmethod(OBJ, gunderstandMessage5, Any, Any, Any, Any, Any, (SEL)sel)
 retmethod( cos_method_understand5(sel, cos_object_id(_1), cos_object_id(_2),
                                        cos_object_id(_3), cos_object_id(_4),
                                        cos_object_id(_5))
            ? True : False );
endmethod

// ----- unrecognized

defmethod(void, gunrecognizedMessage1, Any)
  OBJ obj[1]; obj[0]=_1;
  char buf[256];

  THROW( gnewWithStr(ExBadMessage, cos_method_call(_sel, obj, buf, sizeof buf)) );
endmethod

defmethod(void, gunrecognizedMessage2, Any, Any)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  char buf[256];

  THROW( gnewWithStr(ExBadMessage, cos_method_call(_sel, obj, buf, sizeof buf)) );
endmethod

defmethod(void, gunrecognizedMessage3, Any, Any, Any)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  char buf[256];

  THROW( gnewWithStr(ExBadMessage, cos_method_call(_sel, obj, buf, sizeof buf)) );
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, Any, Any)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  char buf[256];

  THROW( gnewWithStr(ExBadMessage, cos_method_call(_sel, obj, buf, sizeof buf)) );
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, Any, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  char buf[256];

  THROW( gnewWithStr(ExBadMessage, cos_method_call(_sel, obj, buf, sizeof buf)) );
endmethod


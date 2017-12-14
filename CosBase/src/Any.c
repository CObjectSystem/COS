/**
 * C Object System
 * COS Any (root class)
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

#include <cos/prp/object.h>

#include <stdlib.h>

// ----- root class

makclass(Any, _);

// ----- exceptions

useclass(ExBadAlloc, ExBadMessage, ExOverflow);

// ----- properties (read-only)

defmethod(OBJ, ggetAt, Any, mP_class)
  retmethod(gclass(_1));
endmethod

// ----- allocator

defmethod(OBJ, galloc, mAny)
  struct Any *obj = malloc(self->isz);

  if (!obj)
    THROW(ExBadAlloc); // throw the class (no allocation)

  obj->_id = cos_class_id(self);
  obj->_rc = COS_RC_UNIT;

  retmethod( (OBJ)obj );
endmethod

defmethod(OBJ, gallocWithSize, mAny, (size_t)extra)
  size_t size = self->isz + extra;
  struct Any *obj;

  if (size - extra != self->isz)
    THROW(gnewWithStr(ExOverflow, "extra size is too large"));

  if (!(obj = malloc(size)))
    THROW(ExBadAlloc); // throw the class (no allocation)

  obj->_id = cos_class_id(self);
  obj->_rc = COS_RC_UNIT;

  retmethod( (OBJ)obj );
endmethod

// ----- deallocator

defmethod(void, gdealloc, Any)
  free(_1);
endmethod

// ----- clone

defalias (OBJ, (gcopy)gclone, Any);
defmethod(OBJ,  gcopy       , Any)
  retmethod( ginitWith(galloc(gclass(_1)), _1) );
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


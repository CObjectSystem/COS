/**
 * C Object System
 * COS Null
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

#include <cos/Null.h>

#include <cos/gen/object.h>
#include <cos/gen/message.h>

// -----

makclass(Null, Predicate);

// -----

defmethod(OBJ, gisNull, pmNull)
  retmethod(True);
endmethod

defmethod(OBJ, gisNull, Object)
  retmethod(False);
endmethod

// ----- unrecognized

static cos_inline void
trace(SEL sel, OBJ obj[])
{
  char buf[128];
  cos_trace("<Null> unrecognized message %s",
            cos_method_call(sel, obj, buf, sizeof buf));
}

static cos_inline void
chkret(SEL sel, OBJ* ret)
{
  if (COS_GEN_ISOBJ(sel))
    *ret = Nil;
}

// ----- rank 1

defmethod(void, gunrecognizedMessage1, mNull)
  OBJ obj[1]; obj[0]=_1;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

// ----- rank 2

defmethod(void, gunrecognizedMessage2, mNull, Object)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage2, Object, mNull)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

// ----- rank 3

defmethod(void, gunrecognizedMessage3, mNull, Object, Object)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage3, Object, mNull, Object)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, mNull)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

// ----- rank 4

defmethod(void, gunrecognizedMessage4, mNull, Object, Object, Object)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage4, Object, mNull, Object, Object)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, mNull, Object)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, mNull)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

// ----- rank 5

defmethod(void, gunrecognizedMessage5, mNull, Object, Object, Object, Object)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage5, Object, mNull, Object, Object, Object)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, mNull, Object, Object)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, mNull, Object)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, mNull)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret);
endmethod


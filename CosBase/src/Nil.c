/*
 o---------------------------------------------------------------------o
 |
 | COS Nil (root class)
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
 | $Id: Nil.c,v 1.3 2008/10/16 10:46:45 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Nil.h>
#include <cos/gen/message.h>

// -----

makclass(Nil,Any);

// ----- Insensitive to unknown message (absorbent element)

static void
trace(SEL sel, OBJ obj[])
{
  char buf[128];
  cos_debug("<Nil> unrecognized message %s", cos_method_call(sel,obj,buf,sizeof buf));
}

static inline void
chkret(SEL sel, OBJ* ret, OBJ obj)
{
  if (COS_GEN_ORET(sel))
    *ret = obj;
}

// rank 1
defmethod(void, gunrecognizedMessage1, mNil)
  OBJ obj[1]; obj[0]=_1;
  trace(_sel,obj);
  chkret(_sel,_ret,_1);
endmethod

// rank 2
defmethod(void, gunrecognizedMessage2, mNil, Any)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  trace(_sel,obj);
  chkret(_sel,_ret,_1);
endmethod

defmethod(void, gunrecognizedMessage2, Any, mNil)
  OBJ obj[2]; obj[0]=_1, obj[1]=_2;
  trace(_sel,obj);
  chkret(_sel,_ret,_2);
endmethod

// rank 3
defmethod(void, gunrecognizedMessage3, mNil, Any, Any)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);
  chkret(_sel,_ret,_1);
endmethod

defmethod(void, gunrecognizedMessage3, Any, mNil, Any)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);
  chkret(_sel,_ret,_2);
endmethod

defmethod(void, gunrecognizedMessage3, Any, Any, mNil)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=_3;
  trace(_sel,obj);
  chkret(_sel,_ret,_3);
endmethod

// rank 4
defmethod(void, gunrecognizedMessage4, mNil, Any, Any, Any)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret,_1);
endmethod

defmethod(void, gunrecognizedMessage4, Any, mNil, Any, Any)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret,_2);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, mNil, Any)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret,_3);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, Any, mNil)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4;
  trace(_sel,obj);
  chkret(_sel,_ret,_4);
endmethod

// rank 5
defmethod(void, gunrecognizedMessage5, mNil, Any, Any, Any, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret,_1);
endmethod

defmethod(void, gunrecognizedMessage5, Any, mNil, Any, Any, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret,_2);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, mNil, Any, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret,_3);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, mNil, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret,_4);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, Any, mNil)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;
  trace(_sel,obj);
  chkret(_sel,_ret,_5);
endmethod


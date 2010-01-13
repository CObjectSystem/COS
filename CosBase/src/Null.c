/*
 o---------------------------------------------------------------------o
 |
 | COS Null
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
 | $Id: Null.c,v 1.4 2010/01/13 21:28:27 ldeniau Exp $
 |
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

static COS_ALWAYS_INLINE void
trace(SEL sel, OBJ obj[])
{
  char buf[128];
  cos_trace("<Null> unrecognized message %s",
            cos_method_call(sel, obj, buf, sizeof buf));
}

static COS_ALWAYS_INLINE void
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


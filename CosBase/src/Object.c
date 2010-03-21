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
 | $Id: Object.c,v 1.35 2010/03/21 20:34:48 ldeniau Exp $
 |
*/

#include <cos/Object.h>

#include <cos/gen/object.h>

// ----- root of most common classes

makclass(Object, Any);

// ----- clone

defalias (OBJ, (gcopy)gclone, Object);
defmethod(OBJ,  gcopy       , Object)
  retmethod( gnewWith(gclass(_1), _1) );
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

defmethod(OBJ, gnewWithStr, mObject, (STR)str)
  retmethod( ginitWithStr(galloc(_1),str) );
endmethod


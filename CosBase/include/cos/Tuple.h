#ifndef COS_TUPLE_H
#define COS_TUPLE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Tuples
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
 | $Id: Tuple.h,v 1.1 2008/06/27 16:17:15 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// ----- definitions

defclass(Tuple,Object)
endclass

defclass(Tuple2,Tuple)
  OBJ obj[2];
endclass

defclass(Tuple3,Tuple)
  OBJ obj[3];
endclass

defclass(Tuple4,Tuple)
  OBJ obj[4];
endclass

defclass(Tuple5,Tuple)
  OBJ obj[5];
endclass

defclass(Tuple6,Tuple)
  OBJ obj[6];
endclass

defclass(Tuple7,Tuple)
  OBJ obj[7];
endclass

defclass(Tuple8,Tuple)
  OBJ obj[8];
endclass

defclass(Tuple9,Tuple)
  OBJ obj[9];
endclass

// ----- automatic constructor

#define aTuple(...) \
        aTuple_(COS_PP_NARG(__VA_ARGS__),__VA_ARGS__)

#define aTuple_(N,...) ( (OBJ)&(struct COS_PP_CAT(Tuple,N)) { \
        {{ COS_CLS_NAME(COS_PP_CAT(Tuple,N)).Behavior.id, COS_RC_AUTO }}, \
         { __VA_ARGS__ } } )

#endif // COS_TUPLE_H

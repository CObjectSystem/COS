#ifndef COS_GEN_FUNCTOR_H
#define COS_GEN_FUNCTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for functors
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
 | $Id: functor.h,v 1.8 2009/09/16 17:03:02 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

defgeneric(I32, garity, fun);
defgeneric(OBJ, geval0, fun);
defgeneric(OBJ, geval1, fun, (OBJ)arg1);
defgeneric(OBJ, geval2, fun, (OBJ)arg1,(OBJ)arg2);
defgeneric(OBJ, geval3, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3);
defgeneric(OBJ, geval4, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4);
defgeneric(OBJ, geval5, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4,(OBJ)arg5);
defgeneric(OBJ, gevaln, fun, args); // rank 2

defgeneric(OBJ, gcompose, _1);      // compose Array of functors

// ----- wrapper

#define geval(...) \
   COS_PP_CAT(geval,COS_PP_DECR(COS_PP_NARG(__VA_ARGS__)))(__VA_ARGS__)

#endif // COS_GEN_FUNCTOR_H


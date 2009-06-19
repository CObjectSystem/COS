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
 | $Id: functor.h,v 1.4 2009/06/19 23:57:27 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

defgeneric(U32, garity, fun);
defgeneric(OBJ, geval , fun);
defgeneric(OBJ, geval1, fun, (OBJ)arg1);
defgeneric(OBJ, geval2, fun, (OBJ)arg1,(OBJ)arg2);
defgeneric(OBJ, geval3, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3);
defgeneric(OBJ, geval4, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4);
defgeneric(OBJ, geval5, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4,(OBJ)arg5);
defgeneric(OBJ, gevalN, fun, args);

#endif // COS_GEN_FUNCTOR_H


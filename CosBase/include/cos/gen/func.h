#ifndef COS_GEN_FUNC_H
#define COS_GEN_FUNC_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for functional expressions
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
 | $Id: func.h,v 1.1 2008/10/08 16:17:56 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

defgeneric(OBJ, geval , _1);
defgeneric(OBJ, geval1, _1, (OBJ)arg1);
defgeneric(OBJ, geval2, _1, (OBJ)arg1,(OBJ)arg2);
defgeneric(OBJ, geval3, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3);
defgeneric(OBJ, geval4, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4);
defgeneric(OBJ, geval5, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4,(OBJ)arg5);

defgeneric(void, gapply   , _1, fun);
defgeneric(void, gapplyAt , _1, fun, at);

defgeneric(OBJ , gmap     , _1, fun);
defgeneric(OBJ , gmapAt   , _1, fun, at);

defgeneric(OBJ , gmap2    , _1, _2, fun);
defgeneric(OBJ , gmap2At  , _1, _2, fun, at);

defgeneric(OBJ , gmap3    , _1, _2, _3, fun);
defgeneric(OBJ , gmap3At  , _1, _2, _3, fun, at);

defgeneric(OBJ , gfilter  , _1, fun);
defgeneric(OBJ , gfilterAt, _1, fun, at);

defgeneric(OBJ , gfold    , _1, u0, fun);
defgeneric(OBJ , gfoldAt  , _1, u0, fun, at);

defgeneric(OBJ , gscan    , _1, fun);
defgeneric(OBJ , gscanAt  , _1, fun, at);

#endif // COS_GEN_FUNC_H


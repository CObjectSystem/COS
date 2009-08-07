#ifndef COS_GEN_NEW_H
#define COS_GEN_NEW_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for extra constructors
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
 | $Id: new.h,v 1.1 2009/08/07 10:53:52 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// constructors
defgeneric(OBJ, gnewWithStr , _1, (STR)str);
defgeneric(OBJ, gnewWithLoc , _1, _2, (STR)func, (STR)file, (int)line);

defgeneric(OBJ, gnewWithObj , _1, (OBJ)obj1);
defgeneric(OBJ, gnewWithObj2, _1, (OBJ)obj1, (OBJ)obj2);
defgeneric(OBJ, gnewWithObj3, _1, (OBJ)obj1, (OBJ)obj2, (OBJ)obj3);
defgeneric(OBJ, gnewWithObj4, _1, (OBJ)obj1, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4);
defgeneric(OBJ, gnewWithObj5, _1, (OBJ)obj1, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4, (OBJ)obj5);

defgeneric(OBJ, gnewWithChr , _1, (I32)val);
defgeneric(OBJ, gnewWithSht , _1, (I32)val);
defgeneric(OBJ, gnewWithInt , _1, (I32)val);
defgeneric(OBJ, gnewWithLng , _1, (I64)val);
defgeneric(OBJ, gnewWithFlt , _1, (F64)val);
defgeneric(OBJ, gnewWithCpx , _1, (C64)val);

defgeneric(OBJ, gnewWithChrPtr , _1, (I8  *)ref, (U32)n);
defgeneric(OBJ, gnewWithShtPtr , _1, (I16 *)ref, (U32)n);
defgeneric(OBJ, gnewWithIntPtr , _1, (I32 *)ref, (U32)n);
defgeneric(OBJ, gnewWithLngPtr , _1, (I64 *)ref, (U32)n);
defgeneric(OBJ, gnewWithFltPtr , _1, (F64 *)ref, (U32)n);
defgeneric(OBJ, gnewWithCpxPtr , _1, (C64 *)ref, (U32)n);
defgeneric(OBJ, gnewWithObjPtr , _1, (OBJ *)ref, (U32)n);
defgeneric(OBJ, gnewWithVoidPtr, _1, (void*)ref, (U32)n, (size_t)esize);

#endif // COS_GEN_NEW_H

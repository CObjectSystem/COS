#ifndef COS_GEN_INIT_H
#define COS_GEN_INIT_H

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
 | $Id: init.h,v 1.19 2010/01/21 22:09:02 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// constructors
defgeneric (OBJ, ginitWithStr    , _1, (STR)str);
defgeneric (OBJ, ginitWithLoc    , _1, _2, (STR)func, (STR)file, (int)line);

defgeneric (OBJ, ginitWithObj    , _1, (OBJ)obj);
defgeneric (OBJ, ginitWithObj2   , _1, (OBJ)obj, (OBJ)obj2);
defgeneric (OBJ, ginitWithObj3   , _1, (OBJ)obj, (OBJ)obj2, (OBJ)obj3);
defgeneric (OBJ, ginitWithObj4   , _1, (OBJ)obj, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4);
defgeneric (OBJ, ginitWithObj5   , _1, (OBJ)obj, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4, (OBJ)obj5);
defgeneric (OBJ, ginitWithObjStr , _1, (OBJ)obj, (STR)str);
defgeneric (OBJ, ginitWithObjsVa , _1, (va_list)va);
defgenericv(OBJ, ginitWithObjs   , _1, ...);

defgeneric (OBJ, ginitWithChr    , _1, (I32)val);
defgeneric (OBJ, ginitWithSht    , _1, (I32)val);
defgeneric (OBJ, ginitWithInt    , _1, (I32)val);
defgeneric (OBJ, ginitWithLng    , _1, (I64)val);
defgeneric (OBJ, ginitWithFlt    , _1, (F64)val);
defgeneric (OBJ, ginitWithCpx    , _1, (C64)val);

defgeneric (OBJ, ginitWithChrPtr , _1, (I8  *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithShtPtr , _1, (I16 *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithIntPtr , _1, (I32 *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithLngPtr , _1, (I64 *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithFltPtr , _1, (F64 *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithCpxPtr , _1, (C64 *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithObjPtr , _1, (OBJ *)ref, (U32)size, (I32)stride);
defgeneric (OBJ, ginitWithVoidPtr, _1, (void*)ref, (U32)size, (I32)stride, (size_t)esize);

#endif // COS_GEN_INIT_H

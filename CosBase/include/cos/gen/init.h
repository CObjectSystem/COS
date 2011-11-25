#ifndef COS_GEN_INIT_H
#define COS_GEN_INIT_H

/**
 * C Object System
 * COS generics for extra constructors
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

#include <cos/Object.h>

// constructors
defgeneric (OBJ, ginitWithLoc    , _1, _2, (STR)file, (int)line);

defgeneric (OBJ, ginitWithObj    , _1, (OBJ)obj);
defgeneric (OBJ, ginitWithObj2   , _1, (OBJ)obj, (OBJ)obj2);
defgeneric (OBJ, ginitWithObj3   , _1, (OBJ)obj, (OBJ)obj2, (OBJ)obj3);
defgeneric (OBJ, ginitWithObj4   , _1, (OBJ)obj, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4);
defgeneric (OBJ, ginitWithObj5   , _1, (OBJ)obj, (OBJ)obj2, (OBJ)obj3, (OBJ)obj4, (OBJ)obj5);
defgeneric (OBJ, ginitWithObjStr , _1, (OBJ)obj, (STR)str);

defgenericv(OBJ, ginitWithVaArg  , _1, ...);
defgeneric (OBJ, ginitWithVaLst  , _1, (va_list)va);

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

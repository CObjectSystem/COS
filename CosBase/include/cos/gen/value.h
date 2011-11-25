#ifndef COS_GEN_VALUE_H
#define COS_GEN_VALUE_H

/**
 * C Object System
 * COS value generics (C primitive types)
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

defgeneric(STR  , gstr ,   _1);
     
defgeneric(I32  , gidx,    _1);
defgeneric(U32  , gsize,   _1);
defgeneric(I32  , gstride, _1);

defgeneric(BOOL , gbool, _1);
defgeneric(void*, gptr , _1);
defgeneric(FCT  , gfct , _1);

defgeneric(I32  , gchr , _1);
defgeneric(I32  , gsht , _1);
defgeneric(I32  , gint , _1);
defgeneric(I64  , glng , _1);
defgeneric(F64  , gflt , _1);
defgeneric(C64  , gcpx , _1);
defgeneric(OBJ  , gobj , _1);

defgeneric(I32  , gchrAt, _1, at);
defgeneric(I32  , gshtAt, _1, at);
defgeneric(I32  , gintAt, _1, at);
defgeneric(I64  , glngAt, _1, at);
defgeneric(F64  , gfltAt, _1, at);
defgeneric(C64  , gcpxAt, _1, at);

defgeneric(I8*  , gchrPtr, _1);
defgeneric(I16* , gshtPtr, _1);
defgeneric(I32* , gintPtr, _1);
defgeneric(I64* , glngPtr, _1);
defgeneric(F64* , gfltPtr, _1);
defgeneric(C64* , gcpxPtr, _1);
defgeneric(OBJ* , gobjPtr, _1);

#endif // COS_GEN_VALUE_H

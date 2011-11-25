/**
 * C Object System
 * COS Object (root class)
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


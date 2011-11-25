/**
 * C Object System
 * COS Nil (root class)
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

#include <cos/Nil.h>

#include <cos/gen/object.h>

// -----

makclass(Nil, _);

// -----

defalias (OBJ, (gcopy)gclone, mNil);
defmethod(OBJ,  gcopy       , mNil)
  retmethod(_1);
endmethod

defmethod(OBJ, gisNil, pmNil)
  retmethod(True);
endmethod

defmethod(OBJ, gisNil, Any)
  retmethod(False);
endmethod


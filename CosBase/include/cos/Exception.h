#ifndef COS_EXCEPTION_H
#define COS_EXCEPTION_H

/**
 * C Object System
 * COS Exception
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

/* NOTE-USER: exception
   - use gstr(ex) from cos/gen/value.h to retrieve the reason
   - use gobj(ex) from cos/gen/value.h to retrieve the object
*/

defclass(Exception)
  OBJ   obj;
  char *str;
endclass

defclass(ExErrno, Exception)
  int err;
endclass

defclass(ExSignal, Exception)
  int sig;
endclass

defclass(ExBadAlloc      , Exception) endclass
defclass(ExBadArity      , Exception) endclass
defclass(ExBadAssert     , Exception) endclass
defclass(ExBadCast       , Exception) endclass
defclass(ExBadDomain     , Exception) endclass
defclass(ExBadFormat     , Exception) endclass
defclass(ExBadMessage    , Exception) endclass
defclass(ExBadMode       , Exception) endclass
defclass(ExBadProperty   , Exception) endclass
defclass(ExBadPredicate  , Exception) endclass
defclass(ExBadRange      , Exception) endclass
defclass(ExBadSize       , Exception) endclass
defclass(ExBadType       , Exception) endclass
defclass(ExBadValue      , Exception) endclass
defclass(ExNotFound      , Exception) endclass
defclass(ExNotImplemented, Exception) endclass
defclass(ExNotSupported  , Exception) endclass
defclass(ExOverflow      , Exception) endclass
defclass(ExUnderflow     , Exception) endclass

#endif // COS_EXCEPTION_H

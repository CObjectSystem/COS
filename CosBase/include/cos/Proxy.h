#ifndef COS_PROXY_H
#define COS_PROXY_H

/**
 * C Object System
 * COS Proxy (root class)
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

/* NOTE-USER: Proxy behavior

   A proxy is an object which aims to be as 'transparent' as possible
   while behaving on behalf of its delegate.

   Derive your own proxy from the Proxy class to implement your
   specific behaviors or hide its true nature.
*/

defclass(Proxy)
  OBJ obj;
endclass

#endif // COS_PROXY_H

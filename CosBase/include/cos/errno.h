#ifndef COS_ERRNO_H
#define COS_ERRNO_H

/**
 * C Object System
 * COS TestErrno
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

#include <errno.h>

/* NOTE-USER: errno handler
   - throw ExErrno if errno != 0
   - use gint(err) from cos/gen/value.h to retrieve errno value
*/
#define test_errno() \
        ((void)(errno && \
         (cos_exception_errno(errno,__FILE__,__LINE__),0)))

#endif // COS_ERRNO_H

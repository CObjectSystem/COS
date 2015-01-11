#ifndef COS_CFG_FREEBSD_H
#define COS_CFG_FREEBSD_H

/**
 * C Object System
 * COS config: FreeBSD
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

#define COS_HAS_TLS   1
#define COS_HAS_POSIX 1
#define COS_HAS_DLINK 1

#define COS_LIB_PREFIX "lib"
#define COS_LIB_SHEXT  ".so"

#endif // COS_CFG_FREEBSD_H

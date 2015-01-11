#ifndef COS_COS_CONFIG_H
#define COS_COS_CONFIG_H

/**
 * C Object System
 * COS configuration (macros)
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

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/config.h>"
#endif

/* NOTE-CONF: System specific config
*/
#define COS_CFG_INCLUDE(OSNAME) <cos/cfg/OSNAME.h>

#ifdef OSNAME
#include COS_CFG_INCLUDE(OSNAME)
#else
#include COS_CFG_INCLUDE(Default)
#endif

/* NOTE-CONF: C89 compliance
*/
#ifdef COS_C89
#undef  __STDC_VERSION__
#define __STDC_VERSION__ 199409L
#endif

/* NOTE-CONF: constants for *default* configuration
   - Warning: these constants defined the default behavior of COS.
     Changing some of these values may deeply change the behavior of COS.
   - Some of these constants are intended to be (re)defined per translation
     unit instead of globally from this file.
*/
#ifndef COS_CONTRACT // default contracts level (see cos/cos/contract.h)
#define COS_CONTRACT COS_CONTRACT_PRE // COS_CONTRACT_POST, COS_CONTRACT_ALL
#endif

#ifndef COS_LOGMSG // default logmsg level (see cos/cos/cosapi.h)
#define COS_LOGMSG COS_LOGMSG_INFO // COS_LOGMSG_INFO and above
#endif

#ifndef COS_FAST_MESSAGE // default message inlining (see cos/cos/dispatch.h)
#define COS_FAST_MESSAGE 9 // always inline first level lookup
#endif

/* NOTE-CONF: C99 dialect
   define missing C99 keywords here or with 'configure'
*/
#if __STDC_VERSION__ < 199901L
#ifndef inline
#define inline // __inline__
#endif

#ifndef restrict
#define restrict // __restrict__
#endif

#ifndef va_copy
#define va_copy(d,s) ((d) = (s)) // __va_copy(d,s)
#endif

#else // C99

#endif

/* NOTE-CONF: Thread Local Storage
   see cos/cfg/OSNAME.h
*/
#if defined(_OPENMP) || !COS_HAS_TLS
#define __thread
#endif

/* NOTE-CONF: GCC dialect
   Automatic
*/
#ifndef __GNUC__

#undef  __attribute__         // not a macro so far but safer
#define __attribute__(a)      // disable GCC __attribute__
#define cos_inline inline

#else

#define cos_inline inline __attribute__((__always_inline__))
#define COS_INLINE_VALIST COS_NO // gcc doesn't know how to inline va_list arg

#endif

/* NOTE-CONF: POSIX dialect
 */

#define COS_HAS_STRSIGNAL 1

#endif // COS_COS_CONFIG_H

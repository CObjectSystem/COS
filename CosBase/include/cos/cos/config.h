#ifndef COS_COS_CONFIG_H
#define COS_COS_CONFIG_H

/*
 o---------------------------------------------------------------------o
 |
 | COS configuration (macros)
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
 | $Id: config.h,v 1.8 2008/10/02 21:09:55 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/config.h>"
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

#ifndef COS_FAST_MESSAGE // default message inlining (see cos/cos/dispatch.h)
#define COS_FAST_MESSAGE 9 // always inline first level lookup
#endif

#ifndef COS_LOGMSG_LEVEL // default logmsg level (see cos/cos/cosapi.h)
#define COS_LOGMSG_LEVEL cos_msg_trace
#endif

/* NOTE-CONF: C99 dialect
   define missing C99 keywords here or with 'configure'
*/
// #define inline        // __inline__
// #define restrict      // __restrict__
// #define va_copy(d,s)  // __va_copy(d,s) // ((d) = (s))
// #define _Bool         // __bool__
// #define _Complex      // __complex__
// #define _LongLong     // __long_long__

/* NOTE-CONF: POSIX and Thread Local Storage
   define system flags here or with SYSFLAGS in the config.xxx makefile
*/
// #define COS_POSIX 1
// #define COS_TLS   1

#if !COS_TLS
#define __thread
#endif

/* NOTE-CONF: GCC dialect
   Automatic
*/
#ifndef __GNUC__
#undef  __attribute__    // not a macro but safer
#define __attribute__(a) // disable GCC __attribute__
#endif

#endif // COS_COS_CONFIG_H

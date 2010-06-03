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
 | $Id: config.h,v 1.21 2010/06/03 09:03:49 ldeniau Exp $
 |
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

/*
#ifndef _LongLong
#define _LongLong            __long_long__
#define _ULongLong  unsigned __long_long__
#endif

#ifndef _ComplexDouble
#define _ComplexDouble __complex__
#endif
*/

#else // C99

#endif

/* NOTE-CONF: Thread Local Storage
   see cos/cfg/OSNAME.h
*/
#if !COS_HAVE_TLS
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

#endif // COS_COS_CONFIG_H

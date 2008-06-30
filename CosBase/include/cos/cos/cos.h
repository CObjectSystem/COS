#ifndef COS_COS_COS_H
#define COS_COS_COS_H

/*
 o---------------------------------------------------------------------o
 |
 | C Object System
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
 | $Id: cos.h,v 1.3 2008/06/30 15:41:11 ldeniau Exp $
 |
*/

/* NOTE-USER: ISO C89/C99 Compliance
   The preprocessor *must* be C99 compliant (see config.h).
   The compiler     *must* be C89 compliant (see config.h).
 */
#if !__STDC__ || __STDC_VERSION__ < 199901L
#error "COS: COS requires a C99 preprocessor/C89 compiler to work properly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* NOTE-USER: COS config header
 */
#include <cos/cos/local.h>
#include <cos/cos/config.h>

/* NOTE-USER: C headers
 */
#include <stddef.h>
#include <stdarg.h>
#include <limits.h>
#include <setjmp.h>

/* NOTE-USER: COS preprocessor headers
 */
#include <cos/cpp/narg.h>
#include <cos/cpp/utils.h>
#include <cos/cpp/tuple.h>
#include <cos/cpp/logic.h>
#include <cos/cpp/arith.h>
#include <cos/cpp/algos.h>

/* NOTE-USER: COS language headers
 */
#include <cos/cos/base.h>
#include <cos/cos/class.h>
#include <cos/cos/alias.h>
#include <cos/cos/method.h>
#include <cos/cos/generic.h>
#include <cos/cos/contract.h>
#include <cos/cos/exception.h>

/* NOTE-USER: COS library headers
 */
#include <cos/cos/cosdef.h>
#include <cos/cos/coscls.h>
#include <cos/cos/cosapi.h>

/* NOTE-USER: COS inlined dispatch
 */
#include <cos/cos/dispatch.h>

#ifdef __cplusplus
}
#endif

#endif // COS_COS_COS_H

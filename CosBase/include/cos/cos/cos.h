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
 | $Id: cos.h,v 1.16 2010/06/03 15:06:28 ldeniau Exp $
 |
*/

/*
 * --------------------------------------
 * Standard markers used inside the code:
 * --------------------------------------
 * NOTE-USER: mark the presence of comments for user
 * NOTE-INFO: mark the presence of comments for developer
 * NOTE-CONF: mark where configuration matters
 * NOTE-PORT: mark where portability matters
 * NOTE-TODO: mark where something needs to be done
 * --------------------------------------
 */

/* NOTE-USER: ISO C89/C99 Compliance
   The preprocessor *must* be C99 compliant.
   The compiler     *must* be C89 compliant.
 */
#if !__STDC__ || __STDC_VERSION__ < 199901L
#error "COS: COS requires an ISO C99 preprocessor to work properly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* NOTE-USER: COS config header
 */
#include <cos/cos/config.h>

/* NOTE-USER: C headers
 */
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <setjmp.h>

// disable COS language
#ifndef COS_NOCOS

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
#include <cos/cos/cast.h>
#include <cos/cos/class.h>
#include <cos/cos/alias.h>
#include <cos/cos/method.h>
#include <cos/cos/generic.h>
#include <cos/cos/property.h>
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

/* NOTE-USER: COS doc string system
 */
#include <cos/cos/docstr.h>

#endif // COS_NOCOS

#ifdef __cplusplus
}
#endif

#endif // COS_COS_COS_H

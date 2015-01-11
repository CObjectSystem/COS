#ifndef COS_COS_COS_H
#define COS_COS_COS_H

/**
 * C Object System
 * C Object System
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
#include <cos/cos/cosmem.h>

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

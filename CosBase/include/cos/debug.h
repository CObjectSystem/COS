#ifndef COS_DEBUG_H
#define COS_DEBUG_H

/**
 * C Object System
 * COS debug
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

/* low-level debug API
 */
#include <stdio.h>

extern FILE *cos_logmsg_out;

// in cos/cos_symbol.c
void cos_symbol_showSummary        (FILE*);
void cos_symbol_showClasses        (FILE*);
void cos_symbol_showProperties     (FILE*);
void cos_symbol_showClassProperties(FILE*, int);
void cos_symbol_showGenerics       (FILE*);
void cos_symbol_showMethods        (FILE*);

// in cos/cos_dispatch.c
void cos_method_statCache1(FILE*);
void cos_method_statCache2(FILE*);
void cos_method_statCache3(FILE*);
void cos_method_statCache4(FILE*);
void cos_method_statCache5(FILE*);
void cos_method_showCache1(FILE*);
void cos_method_showCache2(FILE*);
void cos_method_showCache3(FILE*);
void cos_method_showCache4(FILE*);
void cos_method_showCache5(FILE*);

// in cos/cos_exception.c
void cos_exception_showProtectionStack(FILE*);

// in cos/AutoRelease.c
void cos_autorelease_showStack(FILE*);

#endif // COS_DEBUG_H

#ifndef COS_DEBUG_H
#define COS_DEBUG_H

/*
 o---------------------------------------------------------------------o
 |
 | COS debug
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
 | $Id: debug.h,v 1.1 2008/10/31 15:19:43 ldeniau Exp $
 |
*/

/* low-level debug API
 */
#include <stdio.h>

extern FILE *cos_logmsg_out;
extern int   cos_logmsg_dispThreadId;
extern int   cos_stack_trace;

// in cos/cos_debug.c
void cos_showCallStack(FILE*);

// in cos/cos_symbol.c
void cos_symbol_showSummary (FILE*);
void cos_symbol_showClasses (FILE*);
void cos_symbol_showGenerics(FILE*);
void cos_symbol_showMethods (FILE*);

// in cos/cos_dispatch{1..5}.c
void cos_method_showCache1(FILE*);
void cos_method_showCache2(FILE*);
void cos_method_showCache3(FILE*);
void cos_method_showCache4(FILE*);
void cos_method_showCache5(FILE*);

// in cos/cos_exception.c
void cos_exception_showStack(FILE*);

// in cos/AutoRelease.c
void cos_autorelease_showStack(FILE*);

#endif // COS_DEBUG_H

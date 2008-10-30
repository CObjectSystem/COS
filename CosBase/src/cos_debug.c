/*
 o---------------------------------------------------------------------o
 |
 | COS debug feature
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
 | $Id: cos_debug.c,v 1.2 2008/10/30 10:19:40 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/cos/debug.h>

int cos_enable_stack_trace = 1;


#ifdef __GLIBC__

#include <stdio.h>
#include <unistd.h>
#include <execinfo.h>

void cos_showCallStack(FILE *out)
{
  extern int fileno(FILE*);
  enum { nmax = 1000 };
  void *buf[nmax];
  int n;

  if (!cos_enable_stack_trace) return;
  if (!out) out = stderr;
  
  n = backtrace(buf, nmax);
  backtrace_symbols_fd(buf, n, fileno(out));
}
     
#else

void cos_showCallStack(FILE *out)
{
  if (cos_enable_stack_trace)
    cos_debug("stack trace not available");  
}

#endif


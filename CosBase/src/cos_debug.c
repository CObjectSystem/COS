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
 | $Id: cos_debug.c,v 1.5 2008/12/04 16:46:46 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/debug.h>

#ifdef __GLIBC__

#include <unistd.h>
#include <execinfo.h>

void cos_showCallStack(FILE *out)
{
  extern int fileno(FILE*);
  enum { nmax = 1000 };
  void *buf[nmax];
  int n;

  if (cos_logmsg_level_ > COS_LOGMSG_TRACE)
    return;

  if (!out)
    out = cos_logmsg_out ? cos_logmsg_out : stderr;
  
  n = backtrace(buf, nmax);
  backtrace_symbols_fd(buf, n, fileno(out));
}
     
#else

void cos_showCallStack(FILE *out)
{
  cos_trace("stack trace not available");  
  COS_UNUSED(out);
}

#endif


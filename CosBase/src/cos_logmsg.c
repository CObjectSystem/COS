/*
 o---------------------------------------------------------------------o
 |
 | COS log message
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
 | $Id: cos_logmsg.c,v 1.17 2010/05/26 15:01:57 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/debug.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if COS_HAVE_POSIX
#include <unistd.h>
#include <pthread.h>
#endif

STATIC_ASSERT(COS_LOGMSG_value_must_be_within_trace_all_and_abort,
              COS_LOGMSG >= COS_LOGMSG_TRALL && COS_LOGMSG <= COS_LOGMSG_ABORT);

FILE *cos_logmsg_out    = 0;
int   cos_logmsg_level_ = COS_LOGMSG; // not thread safe

int
cos_logmsg_setLevel(int lvl)
{
  int old = cos_logmsg_level_;
  
  if (lvl >= COS_LOGMSG_TRALL && lvl <= COS_LOGMSG_ABORT)
    cos_logmsg_level_ = lvl;

  return old;
}

void
cos_logmsg_(int lvl, STR func, STR file, int line, STR fmt, ...)
{
  if (lvl < COS_LOGMSG_TRALL || lvl > COS_LOGMSG_ABORT) {
    cos_logmsg_(COS_LOGMSG_WARN, func, file, line,
                "cos_logmsg discards out-of-range message level %d", lvl);
    return;
  }

  if (lvl >= cos_logmsg_level_) {
    static STR tag[] = { "Trace", "Trace", "Debug", "Info ", "Warn ", "Error", "Abort" };
    va_list va;

    if (cos_logmsg_out == 0) cos_logmsg_out = stderr;
    if (cos_logmsg_out == stderr) fflush(stdout);

    va_start(va,fmt);
#if COS_HAVE_POSIX
    fprintf(cos_logmsg_out, "COS-%s[%u]: ", tag[lvl], (U32)getpid());
#else
    fprintf(cos_logmsg_out, "COS-%s: "    , tag[lvl]);
#endif
    if (lvl < COS_LOGMSG_INFO)
      fprintf(cos_logmsg_out, "(%s,%d,%s): ", file ? file : "", line, func ? func : "");

    vfprintf(cos_logmsg_out,fmt,va);
    putc('\n',cos_logmsg_out);
    va_end(va);

    if (lvl >= COS_LOGMSG_ABORT)
      abort();
  }
}


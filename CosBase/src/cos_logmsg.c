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
 | $Id: cos_logmsg.c,v 1.5 2008/10/29 15:43:10 ldeniau Exp $
 |
*/

#include <cos/Object.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if COS_POSIX
#include <unistd.h>
#include <pthread.h>
#endif

STATIC_ASSERT(COS_LOGMSG_must_be_within_trace_and_abort,
              COS_LOGMSG >= COS_LOGMSG_TRACE && COS_LOGMSG <= COS_LOGMSG_ABORT);

FILE *cos_logmsg_out = 0;
int   cos_logmsg_level_ = COS_LOGMSG;
BOOL  cos_logmsg_disp_pth = 0;

int
cos_logmsg_set(int lvl)
{
  int old;
  
  if (lvl < COS_LOGMSG_TRACE || lvl > COS_LOGMSG_ABORT)
    return cos_logmsg_level_;

  return old=cos_logmsg_level_, cos_logmsg_level_=lvl, old;
}

void
cos_logmsg_(int lvl, STR file, int line, STR fmt, ...)
{
  if (lvl < COS_LOGMSG_TRACE || lvl > COS_LOGMSG_ABORT) {
    cos_logmsg_(COS_LOGMSG_WARN, file, line, "cos_logmsg discarding level %d out of range", lvl);
    return;
  }

  if (lvl >= cos_logmsg_level_) {
    static STR tag[] = { "Invalid", "Trace", "Debug", "Info ", "Warn ", "Error", "Abort" };
    va_list va;

    if (cos_logmsg_out == 0     ) cos_logmsg_out = stderr;
    if (cos_logmsg_out == stderr) fflush(stdout);
   
    va_start(va,fmt);
#if COS_POSIX
    if (cos_logmsg_disp_pth)
      fprintf(cos_logmsg_out,"COS-%s[%u:%04x]:(%-18s,%04d): ",
              tag[lvl], (U32)getpid(), (U32)pthread_self(), file ? file : "-",line);
    else
      fprintf(cos_logmsg_out,"COS-%s[%u]:(%-18s,%04d): ",
              tag[lvl], (U32)getpid(), file ? file : "-",line);
#else
    fprintf(cos_logmsg_out,"COS-%s:(%-18s,%04d): ",tag[lvl],file ? file : "-",line);
#endif
    vfprintf(cos_logmsg_out,fmt,va);
    if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
      fprintf(cos_logmsg_out," %s",strerror(errno));
    putc('\n',cos_logmsg_out);
    va_end(va);

    if (lvl >= COS_LOGMSG_ABORT)
      abort();
  }
}


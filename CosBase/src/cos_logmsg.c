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
 | $Id: cos_logmsg.c,v 1.2 2008/06/29 14:48:28 ldeniau Exp $
 |
*/

#include <cos/Object.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static STR tag[] = { "Invalid", "Debug", "Trace", "Warning", "Error", "Abort" };

BOOL cos_logmsg_level[cos_msg_last] = { NO,
  cos_msg_debug >= COS_LOGMSG_LEVEL,
  cos_msg_trace >= COS_LOGMSG_LEVEL,
  cos_msg_warn  >= COS_LOGMSG_LEVEL,
  cos_msg_error >= COS_LOGMSG_LEVEL,
  cos_msg_abort >= COS_LOGMSG_LEVEL
};

void
cos_logmsg_setLevel(int lvl)
{
  int i;
  
  if (lvl <= cos_msg_invalid || lvl >= cos_msg_last) {
    cos_trace("logmsg_setLevel discarding level %d out of range", lvl);
    return;
  }

  for (i = 0; i <= lvl; i++)
    cos_logmsg_level[i] = NO;
    
  for (; i < cos_msg_last; i++)
    cos_logmsg_level[i] = YES;
}

void
(cos_logmsg)(int lvl, STR file, int line, STR fmt, ...)
{
  if (lvl <= cos_msg_invalid || lvl >= cos_msg_last) {
    cos_logmsg(cos_msg_trace, file, line, "logmsg discarding level %d out of range", lvl);
    return;
  }

  if (cos_logmsg_level[lvl]) {
    va_list va;

    va_start(va,fmt);
    fflush(stdout);
    fprintf(stderr,"COS-%s:(%s,%d): ",tag[lvl],file ? file : "-",line);
    vfprintf(stderr,fmt,va);
    if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
      fprintf(stderr," %s",strerror(errno));
    putc('\n',stderr);
    va_end(va);
  }

  if (lvl == cos_msg_abort)
    abort();
}


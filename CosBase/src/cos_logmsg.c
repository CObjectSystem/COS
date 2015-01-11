/**
 * C Object System
 * COS log message
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

#include <cos/Object.h>
#include <cos/debug.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if COS_HAS_POSIX
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
cos_logmsg_(int lvl, STR file, int line, STR fmt, ...)
{
  if (lvl < COS_LOGMSG_TRALL || lvl > COS_LOGMSG_ABORT) {
    cos_logmsg_(COS_LOGMSG_WARN, file, line,
                "cos_logmsg discards out-of-range message level %d", lvl);
    return;
  }

  if (lvl >= cos_logmsg_level_) {
    static STR tag[] = { "Trace", "Trace", "Debug", "Info ", "Warn ", "Error", "Abort" };
    va_list va;

    if (cos_logmsg_out == 0) cos_logmsg_out = stderr;
    if (cos_logmsg_out == stderr) fflush(stdout);

    va_start(va,fmt);
#if COS_HAS_POSIX
    fprintf(cos_logmsg_out, "COS-%s[%u]: ", tag[lvl], (U32)getpid());
#else
    fprintf(cos_logmsg_out, "COS-%s: "    , tag[lvl]);
#endif
    if (lvl < COS_LOGMSG_INFO)
      fprintf(cos_logmsg_out, "(%s,%d): ", file ? file : "", line);

    vfprintf(cos_logmsg_out,fmt,va);
    putc('\n',cos_logmsg_out);
    va_end(va);

    if (lvl >= COS_LOGMSG_ABORT)
      abort();
  }
}


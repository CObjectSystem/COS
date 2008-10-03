/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - basic unit test
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
 | $Id: utest.c,v 1.1 2008/10/03 07:37:31 ldeniau Exp $
 |
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utest.h"

static const char *const fail_str = "\033[31mFAIL\033[0m";
static const char *const pass_str = "\033[32mPASS\033[0m";

static double total_time = 0.0;
static int    total_pass = 0;
static int    total_fail = 0;

// -----

void
utest_check(struct utest_info *uti, int pass, const char *cond, int line)
{
  ++uti->test_cnt;
  if (!pass) {
    if (uti->fail_cnt < MAX_KEEP_FAIL) {
      uti->fail_cond[uti->fail_cnt] = cond;
      uti->fail_line[uti->fail_cnt] = line;
    }
    ++uti->fail_cnt;
  }
}

// -----

void
utest_init(struct utest_info *uti, const char *name, const char *file)
{
  const char *p = strrchr(file, '/');

  fprintf(stderr, " + %-50s ", name);
  uti->test_file = p ? p+1: file;
  uti->fail_cnt  = 0;
  uti->test_cnt  = 0;
  uti->test_t0   = clock();
}

void
stest_init (struct stest_info *sti, const char *name, int itr)
{
  fprintf(stderr, " + %-50s ", name);
  sti->i   = 0;
  sti->itr = itr;
  sti->t0  = clock();
}

// -----

void
utest_fini(struct utest_info *uti)
{
  double t1 = clock();
  double t = (t1 - uti->test_t0) / CLOCKS_PER_SEC;
  int i;
  
  fprintf(stderr, "(%.2f s) - %3d/%3d : %s\n",
          t,
          uti->test_cnt - uti->fail_cnt,
          uti->test_cnt,
          uti->fail_cnt ? fail_str: pass_str);

  for (i = 0; i < uti->fail_cnt && i < MAX_KEEP_FAIL; i++)
    fprintf(stderr, "   - (%s,%d) %s\n",
            uti->test_file,
            uti->fail_line[i],
            uti->fail_cond[i]);

  total_time += t;
  total_pass += uti->test_cnt-uti->fail_cnt;
  total_fail += uti->fail_cnt;
}

void
stest_fini (struct stest_info *sti)
{
  double t1 = clock();
  double t = (t1 - sti->t0) / CLOCKS_PER_SEC;
  
  fprintf(stderr, "(%.2f s) - %7.0f Kitr/s\n",
          t, sti->itr / t / 1000);

  total_time += t;
  total_pass += 1;
}

// -----

void
utest_clear(void)
{
  total_time = 0;
  total_pass = 0;
  total_fail = 0;
}

void
stest_clear(void)
{
  utest_clear();
}

// -----

void
utest_stat(void)
{
  fprintf(stderr, " = %5d total, %5d passed, %5d failed"
                  "            (%.2f s)             %s\n",
          total_pass+total_fail,
          total_pass,
          total_fail,
          total_time,
          total_fail ? fail_str : pass_str);
  utest_clear();
}

void
stest_stat(void)
{
  fprintf(stderr, " = %5d total                        "
                  "                (%.2f s)\n",
                  total_pass,
                  total_time);
  stest_clear();
}

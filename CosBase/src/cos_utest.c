/**
 * C Object System
 * COS - basic unit test
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

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <cos/utest.h>

static const char *const fail_str = "\033[31mFAIL\033[0m";
static const char *const pass_str = "\033[32mPASS\033[0m";

static double total_time = 0.0;
static int    total_pass = 0;
static int    total_fail = 0;

// -----

static FILE *utest_out = 0;

// -----

void
cos_utest_check(struct cos_utest_info *uti, int pass, const char *cond, int line)
{
  ++uti->test_cnt;
  if (!pass) {
    if (uti->fail_cnt < uti->keep_max) {
      uti->fail_cond[uti->fail_cnt] = cond;
      uti->fail_line[uti->fail_cnt] = line;
    }
    ++uti->fail_cnt;
  }
}

// -----

void
cos_utest_init(struct cos_utest_info *uti, int keep, const char *name, const char *file)
{
  const char *p = strrchr(file, '/');

  if (!utest_out) utest_out = stdout;
  
  fprintf(utest_out, " + %-50s ", name);
  uti->keep_max  = keep;
  uti->test_file = p ? p+1: file;
  uti->fail_cnt  = 0;
  uti->test_cnt  = 0;
  uti->test_t0   = clock();
}

void
cos_stest_init(struct cos_stest_info *sti, const char *name, long itr)
{
  if (!utest_out) utest_out = stdout;

  fprintf(utest_out, " + %-50s ", name);
  sti->i   = 0;
  sti->itr = itr;
  sti->t0  = clock();
}

// -----

void
cos_utest_fini(struct cos_utest_info *uti)
{
  double t1 = clock();
  double t = (t1 - uti->test_t0) / CLOCKS_PER_SEC;
  int i;
  
  if (!utest_out) utest_out = stdout;

  fprintf(utest_out, "(%.2f s) - %3d/%3d : %s\n",
          t,
          uti->test_cnt - uti->fail_cnt,
          uti->test_cnt,
          uti->fail_cnt ? fail_str: pass_str);

  for (i = 0; i < uti->fail_cnt && i < uti->keep_max; i++)
    fprintf(utest_out, "   - (%s,%d) %s\n",
            uti->test_file,
            uti->fail_line[i],
            uti->fail_cond[i]);

  total_time += t;
  total_pass += uti->test_cnt-uti->fail_cnt;
  total_fail += uti->fail_cnt;
}

void
cos_stest_fini(struct cos_stest_info *sti)
{
  double t1 = clock();
  double t = (t1 - sti->t0) / CLOCKS_PER_SEC;
  
  if (!utest_out) utest_out = stdout;

  fprintf(utest_out, "(%.2f s) - %7.0f Kitr/s\n",
          t, sti->itr / t / 1000);

  total_time += t;
  total_pass += 1;
}

// -----

void
cos_utest_clear(void)
{
  total_time = 0;
  total_pass = 0;
  total_fail = 0;
}

void
cos_stest_clear(void)
{
  cos_utest_clear();
}

// -----

void
cos_utest_stat(void)
{
  if (!utest_out) utest_out = stdout;

  fprintf(utest_out, " = %5d total, %5d passed, %5d failed"
                     "            (%.2f s)             %s\n",
                     total_pass+total_fail,
                     total_pass,
                     total_fail,
                     total_time,
                     total_fail ? fail_str : pass_str);
  cos_utest_clear();
}

void
cos_stest_stat(void)
{
  if (!utest_out) utest_out = stdout;

  fprintf(utest_out, " = %5d total                        "
                     "                (%.2f s)\n",
                     total_pass,
                     total_time);
  cos_stest_clear();
}

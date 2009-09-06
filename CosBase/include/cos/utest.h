#ifndef COS_UTEST_H
#define COS_UTEST_H

/*
 o---------------------------------------------------------------------o
 |
 | COS basic unit test and speed test
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
 | $Id: utest.h,v 1.5 2009/09/06 18:42:26 ldeniau Exp $
 |
*/

#define UTEST_START(name) \
  { \
    struct cos_utest_info _utst_info[1]; \
    cos_utest_init(_utst_info, KEEP_FAILED_MAX, name, __FILE__); \
    {

#define UTEST(cond) \
      cos_utest_check(_utst_info, (cond), #cond, __LINE__)

#define UTEST_END \
    } \
    cos_utest_fini(_utst_info); \
  }

#define STEST(name,itr,...) \
  do { \
    struct cos_stest_info _stst_info[1]; \
    cos_stest_init(_stst_info, name, itr); \
    while (_stst_info->i++ < (itr)) { \
      __VA_ARGS__; \
    }  \
    cos_stest_fini(_stst_info); \
  } while (0)

#define KEEP_FAILED_MAX 25

struct cos_utest_info {
  int         keep_max;
  const char *test_file;
  const char *fail_cond[KEEP_FAILED_MAX];
  int         fail_line[KEEP_FAILED_MAX];
  int         fail_cnt;
  int         test_cnt;
  double      test_t0;
};

struct cos_stest_info {
  long   i, itr;
  double t0;
};

void cos_utest_check(struct cos_utest_info*, int, const char*, int);
void cos_utest_init (struct cos_utest_info*, int, const char*, const char*);
void cos_utest_fini (struct cos_utest_info*);
void cos_utest_stat (void);
void cos_utest_clear(void);

void cos_stest_init (struct cos_stest_info*, const char*, long);
void cos_stest_fini (struct cos_stest_info*);
void cos_stest_stat (void);
void cos_stest_clear(void);

#endif // COS_UTEST_H

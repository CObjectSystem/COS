#ifndef COS_TESTS_UTEST_H
#define COS_TESTS_UTEST_H

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - basic unit test and speed test
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
 | $Id: utest.h,v 1.2 2009/03/11 12:35:06 ldeniau Exp $
 |
*/

#ifdef __cplusplus
extern "C" {
#endif

#define UTEST_START(name) \
        { \
          struct utest_info _uti[1]; \
          utest_init(_uti, KEEP_FAILED_MAX, name, __FILE__); \
          {

#define UTEST(cond) \
        utest_check(_uti, (cond), UTEST_STR(cond), __LINE__)

#define UTEST_END \
          } \
          utest_fini(_uti); \
        }

#define STEST(name,itr,expr) \
        do { \
          struct stest_info _sti[1]; \
          stest_init(_sti, name, itr); \
          while (_sti->i++ < (itr)) { \
            expr; \
          }  \
          stest_fini(_sti); \
        } while (0)

#define UTEST_STR(a)  UTEST_STR_(a)
#define UTEST_STR_(a) #a

enum { KEEP_FAILED_MAX = 10 };

struct utest_info {
  int         keep_max;
  const char *test_file;
  const char *fail_cond[KEEP_FAILED_MAX];
  int         fail_line[KEEP_FAILED_MAX];
  int         fail_cnt;
  int         test_cnt;
  double      test_t0;
};

struct stest_info {
  long   i, itr;
  double t0;
};

void utest_check(struct utest_info*, int, const char*, int);
void utest_init (struct utest_info*, int, const char*, const char*);
void utest_fini (struct utest_info*);
void utest_stat (void);
void utest_clear(void);

void stest_init (struct stest_info*, const char*, long);
void stest_fini (struct stest_info*);
void stest_stat (void);
void stest_clear(void);

#ifdef __cplusplus
}
#endif

#endif // COS_TESTS_UTEST_H

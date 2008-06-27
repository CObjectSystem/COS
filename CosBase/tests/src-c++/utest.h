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
 | $Id: utest.h,v 1.1 2008/06/27 16:17:25 ldeniau Exp $
 |
*/

#ifdef __cplusplus
extern "C" {
#endif

#define UTEST_START(name) \
        { \
          struct utest_info _uti[1]; \
          utest_init(_uti, name, __FILE__); \
          {

#define UTEST(cond) \
        utest_check(_uti, (cond), UTEST_STR(cond), __LINE__)

#define UTEST_END \
          } \
          utest_fini(_uti); \
        }

#define STEST(name,N,itr,expr) \
        do { \
          struct stest_info _sti[1]; \
          stest_init(_sti, name, N); \
          while (_sti->i++ < (itr)) { \
            expr; \
          }  \
          stest_fini(_sti); \
        } while (0)

enum { MAX_KEEP_FAIL = 10 };

struct utest_info {
  const char *test_file;
  const char *fail_cond[MAX_KEEP_FAIL];
  int         fail_line[MAX_KEEP_FAIL];
  int         fail_cnt;
  int         test_cnt;
  double      test_t0;
};

struct stest_info {
  int    i, itr;
  double t0;
};

void utest_check(struct utest_info *uti, int pass, const char *cond, int line);
void utest_init (struct utest_info *uti, const char *name, const char *file);
void utest_fini (struct utest_info *uti);
void utest_stat (void);
void utest_clear(void);

void stest_init (struct stest_info *sti, const char *name, int itr);
void stest_fini (struct stest_info *sti);
void stest_stat (void);
void stest_clear(void);

#define UTEST_STR(a)  UTEST_STR_(a)
#define UTEST_STR_(a) #a

#ifdef __cplusplus
}
#endif

#endif // COS_TESTS_UTEST_H

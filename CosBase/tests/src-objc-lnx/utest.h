#ifndef COS_TESTS_UTEST_H
#define COS_TESTS_UTEST_H

/**
 * C Object System
 * COS testsuites - basic unit test and speed test
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

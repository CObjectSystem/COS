#ifndef COS_UTEST_H
#define COS_UTEST_H

/**
 * C Object System
 * COS basic unit test and speed test
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

#define UTEST_START(name) \
  { \
    struct cos_utest_info _utst_info[1]; \
    cos_utest_init(_utst_info, UTEST_KEEP_MAX_FAILED, name, __FILE__); \
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

#define UTEST_KEEP_MAX_FAILED 25

struct cos_utest_info {
  int         keep_max;
  const char *test_file;
  const char *fail_cond[UTEST_KEEP_MAX_FAILED];
  int         fail_line[UTEST_KEEP_MAX_FAILED];
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

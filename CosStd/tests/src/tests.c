/**
 * C Object System
 * COS testsuites - tests suite
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
#include <cos/signal.h>
#include <cos/gen/object.h>
#include <cos/utest.h>

#include "tests.h"

#include <string.h>
#include <stdlib.h>

static void
on_exit(void)
{
  printf("\n** COS deinit duration: %.3f s\n", cos_deinitDuration());
}

int main(int argc, char *argv[])
{
  enum { bits = CHAR_BIT*sizeof(void*) };
  int init_time = NO;
  int speed_tst = NO;
  int debug_sym = NO;
  int alloc_trc = NO;
  int cache_trc = NO;
  int i;

  cos_logmsg_setLevel(COS_LOGMSG_DEBUG);

  for (i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-d"))
      debug_sym = YES;
    if (!strcmp(argv[i], "-ds"))
      debug_sym = YES+YES;
    if (!strcmp(argv[i], "-da"))
      alloc_trc = YES;
    if (!strcmp(argv[i], "-dc"))
      cache_trc = YES;
    if (!strcmp(argv[i], "-i"))
      init_time = YES;
    if (!strcmp(argv[i], "-s"))
      speed_tst = YES;
    if (!strcmp(argv[i], "-t"))
      cos_logmsg_setLevel(COS_LOGMSG_TRACE);
    if (!strcmp(argv[i], "-m"))
      cos_logmsg_setLevel(COS_LOGMSG_TRALL);
  }

  if (init_time) {
    // must be loaded before COS is initialized (and first message is sent)
    atexit(on_exit);
    cos_init(); // explicit initialization for measurement
    printf("** COS init duration: %.3f s\n", cos_initDuration());
  } else
    cos_init();

  // convert signal to exception
  cos_signal_std();

  // for debugging
  if (debug_sym)
    cos_symbol_showSummary(0);
    
  if (debug_sym > 1) {
    cos_symbol_showClasses(0);
    cos_symbol_showProperties(0);
    cos_symbol_showGenerics(0);
    cos_symbol_showMethods(0);
    cos_symbol_showClassProperties(0,YES);
  }

  // testsuites
  printf("\n** C Object System Library Testsuite (%d bits) **\n", bits);
  ut_slice();
  ut_range();
  ut_xrange();
  ut_string();
  ut_array_basics();
  ut_array_functor();

  cos_utest_stat();

  // speed testsuites
  if (speed_tst) {
    printf("\n** C Object System Library Speed Testsuite (%d bits) **\n", bits);

    // TODO

    cos_stest_stat();
  }

  if (cache_trc) {
    printf("\n** COS caches statistics\n");
    
    cos_method_statCache1(0);
    cos_method_statCache2(0);
    cos_method_statCache3(0);
    cos_method_statCache4(0);
    cos_method_statCache5(0);
  }

  if (alloc_trc)
    cos_deinit();
    
  return EXIT_SUCCESS;
}


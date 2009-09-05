/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - tests suite
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
 | $Id: tests.c,v 1.11 2009/09/05 17:49:32 ldeniau Exp $
 |
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

  cos_logmsg_set(COS_LOGMSG_DEBUG);

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
      cos_logmsg_set(COS_LOGMSG_TRACE);
  }

  if (alloc_trc)
    cos_mem_trace(YES);

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
  ut_array();

  cos_utest_stat();

  // speed testsuites
  if (speed_tst) {
    printf("\n** C Object System Library Speed Testsuite (%d bits) **\n", bits);

    // st_methods();
    // st_nextmethods();
    // st_multimethods();

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

  if (alloc_trc) {
    cos_deinit();
    printf("\n** COS alloc/free balance: %u/%u\n",
           cos_mem_nalloc(), cos_mem_nfree());
  }
    
  return EXIT_SUCCESS;
}


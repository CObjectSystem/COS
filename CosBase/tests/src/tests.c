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
 | $Id: tests.c,v 1.9 2008/10/16 12:50:11 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/cos/debug.h>
#include <cos/gen/object.h>
#include "utest.h"
#include "tests.h"

#include <string.h>
#include <stdlib.h>

static void
on_exit(void)
{
  fprintf(stdout, "** COS deinit duration: %.3f s\n", cos_deinitDuration());
}

int main(int argc, char *argv[])
{
  enum { bits = CHAR_BIT*sizeof(void*) };
  int init_time = NO;
  int speed_test = NO;
  int i;
  
  cos_logmsg_set(COS_LOGMSG_DEBUG);

  for (i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-i"))
      init_time = YES;
    if (!strcmp(argv[i], "-s"))
      speed_test = YES;
    if (!strcmp(argv[i], "-t"))
      cos_logmsg_set(COS_LOGMSG_TRACE);
  }


  if (init_time) {
    // must be loaded before first message is sent
    atexit(on_exit);
    // first message initialize COS
    gclass(Nil);
    fprintf(stdout, "** COS init duration: %.3f s\n", cos_initDuration());
  }
    
  // testsuites
  fprintf(stdout, "\n** C Object System Testsuite (%d bits) **\n", bits);
  ut_methods();
  ut_classes();
  ut_predlogic();
  ut_nextmethod();
  ut_unrecognized();
  ut_forwardmessage();
  ut_variadics();
  ut_proxy();
  ut_exception();
  ut_contract();
  ut_autorelease();

  utest_stat();

  // speed testsuites
  if (!speed_test) return EXIT_SUCCESS;
  
  fprintf(stdout, "\n** C Object System Speed Testsuite (%d bits) **\n", bits);

  st_methods();
  st_nextmethods();
  st_multimethods();

  st_methods_ptr();
  st_multimethods_ptr();

  st_pxymethods();
  st_pxynextmethods();
  st_pxymultimethods();
  
  st_memory();
  st_exception();

  stest_stat();

  return EXIT_SUCCESS;
}

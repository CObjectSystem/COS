/**
 * C Object System
 * COS testsuites - Objective-C tests suite
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
#include <stdlib.h>
#include <limits.h>

#include "utest.h"
#include "tests.h"

int
main(void)
{
  enum { bits = CHAR_BIT*sizeof(void*) };

  fprintf(stderr, "\n** C Object System Speed Testsuite (Objective-C, %d bits) **\n", bits);

  st_methods();
  st_multimethods();
  st_memory();

  stest_stat();

  return EXIT_SUCCESS;
}

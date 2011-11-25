/**
 * C Object System
 * COS speed tests - Objective-C methods
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

#include <stdlib.h>
#include <assert.h>
#include "utest.h"
#include "tests.h"
#include "Counter.h"

enum { N = 15000000 * sizeof(void*) };

void
st_methods()
{
  id cnt = [Counter new];

  STEST( "method (0 argument )", N, [cnt incr] );
  STEST( "method (1 argument )", N, [cnt incrBy: 1] );
  STEST( "method (2 arguments)", N, [cnt incrBy: 1 :1] );
  STEST( "method (3 arguments)", N, [cnt incrBy: 1 :1 :1] );
  STEST( "method (4 arguments)", N, [cnt incrBy: 1 :1 :1 :1] );
  STEST( "method (5 arguments)", N, [cnt incrBy: 1 :1 :1 :1 :1] );
  
  assert( (U32)[cnt value] == (U32)(N+N+2*N+3*N+4*N+5*N) );

  [cnt dealloc];
}

void
st_multimethods()
{
  id cnt = [Counter new];
  id one = [[Counter new] incr];

  STEST( "method & visitor pattern (rank 2)", N, [cnt addTo1: one] );
  STEST( "method & visitor pattern (rank 3)", N, [cnt addTo2: one :one] );
  STEST( "method & visitor pattern (rank 4)", N, [cnt addTo3: one :one :one] );
  STEST( "method & visitor pattern (rank 5)", N, [cnt addTo4: one :one :one :one] );

  assert( (U32)[cnt value] == (U32)(N+2*N+3*N+4*N) );

  [cnt dealloc];
  [one dealloc];
}

void
st_memory(void)
{
  enum { P = N/2/sizeof(void*) };
  static id arr[P];
  U32 i;

  i = 0;
  STEST( "alloc+init", P, arr[i++] = [[Counter alloc] init] );

  i = 0;
  STEST( "dealloc", P, [arr[i++] dealloc] );
}

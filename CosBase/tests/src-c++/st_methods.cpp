/**
 * C Object System
 * COS speed tests - C++ methods
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

#include <cstdlib>
#include <cassert>
#include "utest.h"
#include "tests.hpp"
#include "Counter.hpp"

enum { N = 15000000 * sizeof(void*) };

void
st_methods()
{
  Counter cnt;
  IIncr &inc = cnt;

  STEST( "virtual member function (0 argument )", N, inc.incr() );
  STEST( "virtual member function (1 argument )", N, inc.incrBy(1) );
  STEST( "virtual member function (2 arguments)", N, inc.incrBy(1,1) );
  STEST( "virtual member function (3 arguments)", N, inc.incrBy(1,1,1) );
  STEST( "virtual member function (4 arguments)", N, inc.incrBy(1,1,1,1) );
  STEST( "virtual member function (5 arguments)", N, inc.incrBy(1,1,1,1,1) );
  
  assert( cnt.value() == N+N+2*N+3*N+4*N+5*N );
}

void
st_multimethods()
{
  Counter cnt, cnt1(1);
  IAddTo1 &add1 = cnt, &one1 = cnt1;
  IAddTo2 &add2 = cnt, &one2 = cnt1;
  IAddTo3 &add3 = cnt, &one3 = cnt1;
  IAddTo4 &add4 = cnt, &one4 = cnt1;

  STEST( "virtual member function & visitor pattern (rank 2)", N, add1.addTo(one1) );
  STEST( "virtual member function & visitor pattern (rank 3)", N, add2.addTo(one2,one2) );
  STEST( "virtual member function & visitor pattern (rank 4)", N, add3.addTo(one3,one3,one3) );
  STEST( "virtual member function & visitor pattern (rank 5)", N, add4.addTo(one4,one4,one4,one4) );
  
  assert( cnt.value() == N+2*N+3*N+4*N );
}

void
st_memory(void)
{
  enum { P = N/2/sizeof(void*) };
  static Counter* arr[P];
  U32 i;
  
  i = 0;
  STEST( "new", P, arr[i++] = new Counter );

  i = 0;
  STEST( "delete", P, delete arr[i++] );
}

/**
 * C Object System
 * COS example01 -- main
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

#include <cos/Number.h>
#include <cos/Functor.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/array.h>
#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/numop.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

useclass(AutoRelease);

/*
-- ghc -O2 sum.hs -o sum
-- ./sum +RTS -K20000000

import Data.List

f = foldl' (.) id $ replicate 1000000 (+1)
main = putStrLn $ show $ f 0
*/

static void
sum_rep(I32 n)
{
  printf("*** functional sum (repeat + eval)\n");

  OBJ pool = gnew(AutoRelease);
  OBJ inc  = gautoRelease(aFunctor(gaddTo,0,aInt(1)));
  F64 t0   = clock();
  OBJ xs   = gcomposen(grepeat(inc,aInt(n)));
  F64 t1   = clock();
  I32 x    = gint(geval1(xs,aInt(0)));
  F64 t2   = clock();
             grelease(pool);
  F64 t3   = clock();

  printf("count [n] = %d [%d]\n" , x, n);
  printf("time init = %.2f sec\n", (t1-t0)/CLOCKS_PER_SEC);
  printf("time eval = %.2f sec\n", (t2-t1)/CLOCKS_PER_SEC);
  printf("time fini = %.2f sec\n", (t3-t2)/CLOCKS_PER_SEC);
  printf("time all  = %.2f sec\n", (t3-t0)/CLOCKS_PER_SEC);
}

static void
sum_itr(I32 n)
{
  printf("*** functional sum (iterate + eval)\n");

  OBJ pool = gnew(AutoRelease);
  OBJ inc  = gautoRelease(aFunctor(gaddTo,0,aInt(1)));
  F64 t0   = clock();
  OBJ xs   = giterate(inc,aInt(n));
  F64 t1   = clock();
  I32 x    = gint(geval1(xs,aInt(0)));
  F64 t2   = clock();
             grelease(pool);
  F64 t3   = clock();

  printf("count [n] = %d [%d]\n" , x, n);
  printf("time init = %.2f sec\n", (t1-t0)/CLOCKS_PER_SEC);
  printf("time eval = %.2f sec\n", (t2-t1)/CLOCKS_PER_SEC);
  printf("time fini = %.2f sec\n", (t3-t2)/CLOCKS_PER_SEC);
  printf("time all  = %.2f sec\n", (t3-t0)/CLOCKS_PER_SEC);
}

static void
sum_oop(I32 n)
{
  printf("*** object-oriented sum (repeat + foldl)\n");

  OBJ pool = gnew(AutoRelease);
  OBJ ini  = gautoRelease(aInt(1));
  F64 t0   = clock();
  OBJ xs   = grepeat(ini,aInt(n));
  F64 t1   = clock();
  I32 x    = gint(greduce1(xs,aFunctor(gaddTo,0,0),aInt(0)));
  F64 t2   = clock();
             grelease(pool);
  F64 t3   = clock();

  printf("count [n] = %d [%d]\n" , x, n);
  printf("time init = %.2f sec\n", (t1-t0)/CLOCKS_PER_SEC);
  printf("time eval = %.2f sec\n", (t2-t1)/CLOCKS_PER_SEC);
  printf("time fini = %.2f sec\n", (t3-t2)/CLOCKS_PER_SEC);
  printf("time all  = %.2f sec\n", (t3-t0)/CLOCKS_PER_SEC);
}

int main(int argc, char *argv[])
{
  I32 n = argc == 2 ? strtol(argv[1],0,0) : 1000000;

  if (n <= 10)
    cos_logmsg_setLevel(COS_LOGMSG_TRACE);

  sum_rep(n);
  sum_itr(n);
  sum_oop(n);

  return EXIT_SUCCESS;
}

/* COS OUTPUT:
*** functional sum (repeat + eval)
count [n] = 1000000 [1000000]
time init = 0.04 sec
time eval = 0.02 sec
time fini = 0.03 sec
time all  = 0.09 sec
*** functional sum (iterate + eval)
count [n] = 1000000 [1000000]
time init = 0.00 sec
time eval = 0.01 sec
time fini = 0.00 sec
time all  = 0.01 sec
*** object-oriented sum (repeat + foldl)
count [n] = 1000000 [1000000]
time init = 0.02 sec
time eval = 0.02 sec
time fini = 0.00 sec
time all  = 0.04 sec
*/

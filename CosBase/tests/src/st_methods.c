/**
 * C Object System
 * COS speed tests - methods
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
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/utest.h>

#include <string.h>

#include "tests.h"
#include "generics.h"

enum { N = 15000000 * sizeof(void*) };

void
st_methods(void)
{
  useclass(Counter);

  OBJ cnt = gnew(Counter);

  STEST( "method (0 argument )", N, gincr(cnt) );
  STEST( "method (1 argument )", N, gincrBy1(cnt,1) );
  STEST( "method (2 arguments)", N, gincrBy2(cnt,1,1) );
  STEST( "method (3 arguments)", N, gincrBy3(cnt,1,1,1) );
  STEST( "method (4 arguments)", N, gincrBy4(cnt,1,1,1,1) );
  STEST( "method (5 arguments)", N, gincrBy5(cnt,1,1,1,1,1) );
  
  ensure( gint(cnt) == N+N+2*N+3*N+4*N+5*N );

  grelease(cnt);
}

void
st_nextmethods(void)
{
  enum { P = N/2 };
  useclass(MilliCounter);

  OBJ cnt = gnew(MilliCounter);

  STEST( "method + next method (0 argument )", P, gincr(cnt) );
  STEST( "method + next method (1 argument )", P, gincrBy1(cnt,1) );
  STEST( "method + next method (2 arguments)", P, gincrBy2(cnt,1,1) );
  STEST( "method + next method (3 arguments)", P, gincrBy3(cnt,1,1,1) );
  STEST( "method + next method (4 arguments)", P, gincrBy4(cnt,1,1,1,1) );
  STEST( "method + next method (5 arguments)", P, gincrBy5(cnt,1,1,1,1,1) );
  
  ensure( gint(cnt) == P+P+2*P+3*P+4*P+5*P );
  grelease(cnt);
}

void
st_multimethods(void)
{
  useclass(Counter);

  OBJ cnt = gnew(Counter);
  OBJ one = gincr(gnew(Counter));

  STEST( "multimethod (rank 2)", N, gaddTo1(cnt,one) );
  STEST( "multimethod (rank 3)", N, gaddTo2(cnt,one,one) );
  STEST( "multimethod (rank 4)", N, gaddTo3(cnt,one,one,one) );
  STEST( "multimethod (rank 5)", N, gaddTo4(cnt,one,one,one,one) );
  
  STEST( "multimethod (rank 2 +1 arg)", N, gaddToPlus(cnt,one,1) );

  ensure( gint(cnt) == N+2*N+3*N+4*N+2*N );
  grelease(cnt);
  grelease(one);
}

void
st_methods_ptr(void)
{
  useclass(Counter);
  usegeneric((gincr)gincr_s,
             (gincrBy1)gincrBy1_s, (gincrBy2)gincrBy2_s, (gincrBy3)gincrBy3_s,
             (gincrBy4)gincrBy4_s, (gincrBy5)gincrBy5_s);

  OBJ cnt = gnew(Counter);
  OBJ ret;

  IMP1 gincr_p    = cos_method_lookup1((SEL)gincr_s   , cos_object_id(cnt));
  IMP1 gincrBy1_p = cos_method_lookup1((SEL)gincrBy1_s, cos_object_id(cnt));
  IMP1 gincrBy2_p = cos_method_lookup1((SEL)gincrBy2_s, cos_object_id(cnt));
  IMP1 gincrBy3_p = cos_method_lookup1((SEL)gincrBy3_s, cos_object_id(cnt));
  IMP1 gincrBy4_p = cos_method_lookup1((SEL)gincrBy4_s, cos_object_id(cnt));
  IMP1 gincrBy5_p = cos_method_lookup1((SEL)gincrBy5_s, cos_object_id(cnt));

  gincrBy1_arg_t arg1 = { 1 };
  gincrBy2_arg_t arg2 = { 1,1 };
  gincrBy3_arg_t arg3 = { 1,1,1 };
  gincrBy4_arg_t arg4 = { 1,1,1,1 };
  gincrBy5_arg_t arg5 = { 1,1,1,1,1 };

  STEST( "method pointer (0 argument )", N, gincr_p   ((SEL)gincr_s   ,cnt,0    ,&ret) );
  STEST( "method pointer (1 argument )", N, gincrBy1_p((SEL)gincrBy1_s,cnt,&arg1,&ret) );
  STEST( "method pointer (2 arguments)", N, gincrBy2_p((SEL)gincrBy2_s,cnt,&arg2,&ret) );
  STEST( "method pointer (3 arguments)", N, gincrBy3_p((SEL)gincrBy3_s,cnt,&arg3,&ret) );
  STEST( "method pointer (4 arguments)", N, gincrBy4_p((SEL)gincrBy4_s,cnt,&arg4,&ret) );
  STEST( "method pointer (5 arguments)", N, gincrBy5_p((SEL)gincrBy5_s,cnt,&arg5,&ret) );
  
  ensure( gint(cnt) == N+N+2*N+3*N+4*N+5*N );

  grelease(cnt);
}

void
st_multimethods_ptr(void)
{
  useclass(Counter);
  usegeneric((gaddTo1)gaddTo1_s, (gaddTo2)gaddTo2_s,
             (gaddTo3)gaddTo3_s, (gaddTo4)gaddTo4_s);

  OBJ cnt = gnew(Counter);
  OBJ one = gincr(gnew(Counter));
  OBJ ret;

  U32 cid = cos_object_id(cnt);
  U32 oid = cos_object_id(one);

  IMP2 gaddTo1_p = cos_method_lookup2((SEL)gaddTo1_s, cid, oid);
  IMP3 gaddTo2_p = cos_method_lookup3((SEL)gaddTo2_s, cid, oid, oid);
  IMP4 gaddTo3_p = cos_method_lookup4((SEL)gaddTo3_s, cid, oid, oid, oid);
  IMP5 gaddTo4_p = cos_method_lookup5((SEL)gaddTo4_s, cid, oid, oid, oid, oid);

  STEST( "multimethod pointer (rank 2)", N, gaddTo1_p((SEL)gaddTo1_s,cnt,one,0,&ret) );
  STEST( "multimethod pointer (rank 3)", N, gaddTo2_p((SEL)gaddTo2_s,cnt,one,one,0,&ret) );
  STEST( "multimethod pointer (rank 4)", N, gaddTo3_p((SEL)gaddTo3_s,cnt,one,one,one,0,&ret) );
  STEST( "multimethod pointer (rank 5)", N, gaddTo4_p((SEL)gaddTo4_s,cnt,one,one,one,one,0,&ret) );
  
  ensure( gint(cnt) == N+2*N+3*N+4*N );

  grelease(cnt);
  grelease(one);
}

void
st_memory(void)
{
  enum { P = N/2/sizeof(void*) };
  static OBJ arr[P];
  useclass(Counter, AutoRelease);
  OBJ ar = gnew(AutoRelease);
  size_t sz = gsize(Counter);
  size_t i;
  int lvl;

  // allocator warm up
  for (i = 0; i < P; i++)
    arr[i++] = malloc(sz);

  for (i = 0; i < P; i++)
    free(arr[i++]);

  i = 0;
  STEST( "malloc", P, arr[i++] = malloc(sz) );

  i = 0;
  STEST( "free", P, free(arr[i++]) );

  i = 0;
  STEST( "alloc + init", P, arr[i++] = ginit(galloc(Counter)) );

  i = 0;
  STEST( "retain", P, gretain(arr[i++]) );

  i = 0;
  lvl = cos_logmsg_setLevel(COS_LOGMSG_WARN);
  STEST( "autoRelease", P, gautoRelease(arr[i++]) );
  cos_logmsg_setLevel(lvl);

  i = 0;
  STEST( "release", P, grelease(arr[i++]) );

  STEST( "alloc + init + release", P, grelease(ginit(galloc(Counter))) );

  grelease(ar);
}

void
st_exception(void)
{
  STEST( "try-endtry", N/50, TRY ENDTRY );
}

/**
 * C Object System
 * COS testsuites - variadic message
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

#include "tests.h"
#include "generics.h"

#include <string.h>

static BOOL
check_msg(OBJ cls, STR res)
{
  OBJ _1 = gnew(cls);
  STR  s = gstr(_1);
  BOOL ret;

  gvputStr(_1, "%s understands variadic %s", gclassName(_1), "gvputStr");
  ret = !strcmp(s, res);
  grelease(_1);
  
  return ret;
}

static BOOL
check_vam(OBJ cls, STR res)
{
  OBJ _1 = gnew(cls);
  STR  s = gstr(_1);
  BOOL ret;

  gvputStr(_1, "%s understands %s", gclassName(_1), "gvputStr");
  ret = !strcmp(s, res);
  grelease(_1);
  
  return ret;
}

static BOOL
check_vaf(OBJ cls, STR res)
{
  useclass(Proxy);
  
  OBJ _1  = gnew(cls);
  OBJ pxy = gnewWith(Proxy, _1);
  STR s   = gstr(_1);
  BOOL ret = YES;

  grelease(_1);

  gvputStr(pxy, "%s understands %s", gclassName(_1), "gvputStr");

  if ( strcmp(s, res) )
    ret = NO;

  grelease(pxy);
  
  return ret;
}

void
ut_variadics(void)
{
  useclass(A,B,C,D,E);

  UTEST_START("variadic message")

    UTEST( check_msg(C, "C understands variadic gvputStr") );
    UTEST( check_msg(D, "D understands variadic gvputStr") );
    UTEST( check_msg(E, "E understands variadic gvputStr") );

    UTEST( check_vam(A, "A does not understand gvputStr") );
    UTEST( check_vam(B, "B does not understand gvputStr") );
    UTEST( check_vam(C, "C understands gvputStr") );
    UTEST( check_vam(D, "D understands gvputStr") );
    UTEST( check_vam(E, "E understands gvputStr") );

    UTEST( check_vaf(A, "A does not understand gvputStr") );
    UTEST( check_vaf(B, "B does not understand gvputStr") );
    UTEST( check_vaf(C, "C understands gvputStr") );
    UTEST( check_vaf(D, "D understands gvputStr") );
    UTEST( check_vaf(E, "E understands gvputStr") );

  UTEST_END
}

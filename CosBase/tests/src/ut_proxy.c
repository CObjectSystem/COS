/**
 * C Object System
 * COS testsuites - proxy
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
check_gmf(OBJ cls, STR res)
{
  useclass(PA);
  
  OBJ _1  = gnew(cls);
  OBJ pxy = gnewWith(PA, _1);
  STR s   = gstr(_1);
  BOOL ret;

  grelease(_1);
  gcatStr(pxy, " understands gcatStr");
  ret = !strcmp(s, res);
  grelease(pxy);
  
  return ret;
}

static BOOL
check_vmf(OBJ cls, STR res)
{
  useclass(PA);
  
  OBJ _1  = gnew(cls);
  OBJ pxy = gnewWith(PA, _1);
  STR s   = gstr(_1);
  BOOL ret;

  grelease(_1);
  gvputStr(pxy, "%s understands %s", gclassName(_1), "gvputStr");
  ret = !strcmp(s, res);
  grelease(pxy);
  
  return ret;
}

void
ut_proxy(void)
{
  useclass(A,B,C,D,E);

  UTEST_START("proxy & message intercept")

    UTEST( check_gmf(A, "A understands gcatStr (through proxy PA)") );
    UTEST( check_gmf(B, "B understands gcatStr (through proxy PA)") );
    UTEST( check_gmf(C, "C understands gcatStr (through proxy PA)") );
    UTEST( check_gmf(D, "D understands gcatStr (through proxy PA)") );
    UTEST( check_gmf(E, "E understands gcatStr (through proxy PA)") );

    UTEST( check_vmf(A, "A does not understand gvputStr") );
    UTEST( check_vmf(B, "B does not understand gvputStr") );
    UTEST( check_vmf(C, "C understands gvputStr (through proxy PA)") );
    UTEST( check_vmf(D, "D understands gvputStr (through proxy PA)") );
    UTEST( check_vmf(E, "E understands gvputStr (through proxy PA)") );

  UTEST_END
}

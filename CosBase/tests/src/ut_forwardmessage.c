/**
 * C Object System
 * COS testsuites - forward message
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

#include <string.h>

static BOOL
check_fwd(OBJ cls, OBJ (*func)(OBJ), STR res)
{
  useclass(Proxy);
  
  OBJ _1  = gnew(cls);
  OBJ pxy = gnewWith(Proxy, _1);
  STR s   = gstr(_1);
  BOOL ret;

  grelease(_1);
  func(pxy);
  ret = !strcmp(s, res);
  grelease(pxy);
  
  return ret;
}

static OBJ
gobool(OBJ obj)
{
  return gbool(obj) ? True : False;
}

void
ut_forwardmessage(void)
{
  useclass(A,B,C,D,E);

  UTEST_START("forwarding message")

    UTEST( check_fwd(A, gobool, "A does not understand gbool") );
    UTEST( check_fwd(A, gclass, "A")  );

    UTEST( check_fwd(B, gobool, "B does not understand gbool") );
    UTEST( check_fwd(B, gclass, "B")  );

    UTEST( check_fwd(C, gobool, "C does not understand gbool") );
    UTEST( check_fwd(C, gclass, "C")  );

    UTEST( check_fwd(D, gobool, "D does not understand gbool") );
    UTEST( check_fwd(D, gclass, "D")  );

    UTEST( check_fwd(E, gobool, "E does not understand gbool") );
    UTEST( check_fwd(E, gclass, "E")  );

  UTEST_END
}


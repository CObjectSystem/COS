/**
 * C Object System
 * COS testsuites - unrecognized message
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
check_msg(OBJ cls, OBJ (*func)(OBJ), STR res)
{
  OBJ _1 = gnew(cls);
  STR  s = gstr(_1);
  BOOL ret;

  func(_1);
  ret = !strcmp(s, res);
  grelease(_1);
  
  return ret;
}

static OBJ
gobool(OBJ obj)
{
  return gbool(obj) ? True : False;
}

void
ut_unrecognized(void)
{
  useclass(A,B,C,D,E);

  UTEST_START("unrecognized message")

    UTEST( check_msg(A, gobool, "A does not understand gbool") );
    UTEST( check_msg(A, gclass, "A")  );

    UTEST( check_msg(B, gobool, "B does not understand gbool") );
    UTEST( check_msg(B, gclass, "B")  );

    UTEST( check_msg(C, gobool, "C does not understand gbool") );
    UTEST( check_msg(C, gclass, "C")  );

    UTEST( check_msg(D, gobool, "D does not understand gbool") );
    UTEST( check_msg(D, gclass, "D")  );

    UTEST( check_msg(E, gobool, "E does not understand gbool") );
    UTEST( check_msg(E, gclass, "E")  );

  UTEST_END
}

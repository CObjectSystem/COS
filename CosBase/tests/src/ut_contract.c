/**
 * C Object System
 * COS testsuites - contract
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
#include <cos/signal.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/utest.h>

#include <string.h>

#include "tests.h"
#include "generics.h"

static BOOL
check_ctr(OBJ cls, int val, STR res)
{
  OBJ _1 = gnew(cls);
  STR  s = gstr(_1);
  BOOL ret;

  TRY
    gdoC(_1, val);
  CATCH_ANY(ex)
    ret = !strcmp(gstr(ex), "val == 0");
    grelease(ex);
  ENDTRY

  ret = !strcmp(s, res);
  grelease(_1);
  
  return ret;
}

void
ut_contract(void)
{
  useclass(A,B,C,D,E);

  int lvl = cos_contract_setLevel(COS_CONTRACT_ALL);
  
  UTEST_START("contract")

    UTEST( check_ctr(A,1,"A-PRE-BODY-POST-INV") );
    UTEST( check_ctr(B,1,"B-PRE-BODY")          );
    UTEST( check_ctr(C,1,"C-PRE")               );
    UTEST( check_ctr(D,1,"D-PRE-BODY")          );
    UTEST( check_ctr(E,1,"E-PRE-BODY-POST-INV") );
    
  UTEST_END

  cos_contract_setLevel(lvl);
}

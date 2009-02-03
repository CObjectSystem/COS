/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - contract
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUTEST ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: ut_contract.c,v 1.4 2009/02/03 14:40:48 ldeniau Exp $
 |
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
  ENDTRY

  ret = !strcmp(s, res);
  grelease(_1);
  
  return ret;
}

void
ut_contract(void)
{
  useclass(A,B,C,D,E);
  
  UTEST_START("contract")

    UTEST( check_ctr(A,1,"A-PRE-BODY-POST-INV") );
    UTEST( check_ctr(B,1,"B-PRE-BODY")          );
    UTEST( check_ctr(C,1,"C-PRE")               );
    UTEST( check_ctr(D,1,"D-PRE-BODY")          );
    UTEST( check_ctr(E,1,"E-PRE-BODY-POST-INV") );
    
  UTEST_END
}

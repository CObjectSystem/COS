/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - proxy
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
 | $Id: ut_proxy.c,v 1.4 2010/05/28 08:53:08 ldeniau Exp $
 |
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

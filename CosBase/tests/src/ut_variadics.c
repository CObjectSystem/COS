/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - variadic message
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
 | $Id: ut_variadics.c,v 1.3 2009/04/17 21:13:56 ldeniau Exp $
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
check_msg(OBJ cls, STR res)
{
  OBJ _1 = gnew(cls);
  STR  s = gstr(_1);
  BOOL ret;

  gvputStr(_1, "%s understands variadic %s", gclassName(_1), "gvputStr");
  ret = !strcmp(s, res);
  gdelete(_1);
  
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
  gdelete(_1);
  
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

  gdelete(_1);

  gvputStr(pxy, "%s understands %s", gclassName(_1), "gvputStr");

  if ( strcmp(s, res) )
    ret = NO;

  gdelete(pxy);
  
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

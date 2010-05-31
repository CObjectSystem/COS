/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - array
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
 | $Id: ut_string.c,v 1.4 2010/05/31 14:02:59 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/String.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>

#include <cos/utest.h>

#include "tests.h"

/*
static BOOL
isEq(OBJ r, OBJ ref)
{
  OBJ res = gisEqual(r, ref);
  grelease(r);
  return res == True;
}
*/

void
ut_string(void)
{
//  useclass(Array, String);
  useclass(Lesser,Equal,Greater);
  useclass(AutoRelease);
  
  OBJ buf[] = { aStr("toto","tutu","","titi") };
  OBJ srt[] = { aStr("","titi","toto","tutu") };
  OBJ arr;

  OBJ pool = gnew(AutoRelease);

  UTEST_START("String")

    UTEST(gisEqual(aStr(""),aStr("")) == True);
    UTEST(gisEqual(aStr(""),aStr("titi")) == False);
    UTEST(gisEqual(aStr("titi"),aStr("")) == False);

    UTEST(gisEqual(aStr("titi"),aStr("titi")) == True);
    UTEST(gisEqual(aStr("tutu"),aStr("titi")) == False);

    UTEST(gcompare(aStr(""),aStr("")) == Equal);
    UTEST(gcompare(aStr(""),aStr("titi")) == Lesser);
    UTEST(gcompare(aStr("titi"),aStr("")) == Greater);

    UTEST(gcompare(aStr("tata"),aStr("titi")) == Lesser);
    UTEST(gcompare(aStr("titi"),aStr("titi")) == Equal);
    UTEST(gcompare(aStr("tutu"),aStr("titi")) == Greater);

    UTEST(gcompare(aStr("titis"),aStr("tutu")) == Lesser);
    UTEST(gcompare(aStr("tutu"),aStr("titis")) == Greater);
    UTEST(gcompare(aStr("titis"),aStr("titi")) == Greater);
    UTEST(gcompare(aStr("titi"),aStr("titis")) == Lesser);

    arr = aArrayRef(buf, COS_ARRLEN(buf));

    UTEST(gfind(arr, aStr("toto")) != Nil);
    UTEST(gfind(arr, aStr("tutu")) != Nil);
    UTEST(gfind(arr, aStr("titi")) != Nil);
    UTEST(gfind(arr, aStr("tata")) == Nil);
    UTEST(gfind(arr, aStr("titis")) == Nil);
    UTEST(gfind(arr, aStr("totos")) == Nil);
    UTEST(gfind(arr, aStr("tutus")) == Nil);
    UTEST(gfind(arr, aStr("")) != Nil);
    
    UTEST(gfind(arr, aFun(gisEqual, aStr("titi"), __1)) != Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr("toto"), __1)) != Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr("tutu"), __1)) != Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr("tata"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr("titis"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr("totos"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr("tutus"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr(""), __1)) != Nil);

    gsort(arr, aFun(gcompare,__1,__2));

    UTEST(gisEqual(arr, aArrayRef(srt, COS_ARRLEN(srt))) == True);

    UTEST(gfind(arr, aFun(gcompare, aStr("titi"), __1)) != Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr("toto"), __1)) != Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr("tutu"), __1)) != Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr("tata"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr("titis"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr("totos"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr("tutus"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr(""), __1)) != Nil);

    arr = aArrayRef(0, 0);

    UTEST(gfind(arr, aStr("tata")) == Nil);
    UTEST(gfind(arr, aStr("")) == Nil);

    UTEST(gfind(arr, aFun(gisEqual, aStr("tata"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gisEqual, aStr(""), __1)) == Nil);

    UTEST(gfind(arr, aFun(gcompare, aStr("tata"), __1)) == Nil);
    UTEST(gfind(arr, aFun(gcompare, aStr(""), __1)) == Nil);

  UTEST_END

  grelease(pool);
}


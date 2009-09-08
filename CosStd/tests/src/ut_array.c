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
 | $Id: ut_array.c,v 1.5 2009/09/08 00:49:44 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Number.h>
#include <cos/XRange.h>
#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/value.h>
#include <cos/utest.h>
#include <cos/prp/sequence.h>

#include "tests.h"

static BOOL
isEq(OBJ r, OBJ ref)
{
  OBJ res = gisEqual(r, ref);
  gdelete(r);
  return res == True;
}

void
ut_array(void)
{
  useproperty(size);
  useclass(Array, Array1, Array2, Array5, Array9, ArrayN);
  useclass(AutoRelease);
  
  OBJ buf[] = { aInt(0,1,2,3,4,5,6,7,8,9) };
  OBJ pool = gnew(AutoRelease);

  UTEST_START("Array")

  // sizes
  UTEST(gsize(aArray(aInt(0))) == 1);
  UTEST(gsize(aArray(aInt(0,1))) == 2);
  UTEST(gsize(aArray(aInt(0,1,2,3,4))) == 5);
  UTEST(gsize(aArray(aInt(0,1,2,3,4,5,6,7,8,9))) == 10);

  UTEST(gisEmpty(aArray(aInt(0))) == False);
  UTEST(gisEqual(ggetAt(aArray(aInt(0)),size), aInt(1)) == True);
  UTEST(gisEqual(ggetAt(aArray(aInt(0,1)),size), aInt(2)) == True);
  UTEST(gisEqual(ggetAt(aArray(aInt(0,1,2,3,4)),size), aInt(5)) == True);
  UTEST(gisEqual(ggetAt(aArray(aInt(0,1,2,3,4,5,6,7,8,9)),size), aInt(10)) == True);

  // types
  UTEST(gisKindOf(aArray(aInt(0)), Array1) == True);
  UTEST(gisKindOf(aArray(aInt(0,1)), Array2) == True);
  UTEST(gisKindOf(aArray(aInt(0,1,2,3,4)), Array5) == True);
  UTEST(gisKindOf(aArray(aInt(0,1,2,3,4,5,6,7,8)), Array9) == True);
  UTEST(gisKindOf(aArray(aInt(0,1,2,3,4,5,6,7,8,9)), ArrayN) == True);

  // equals + copy
  UTEST(isEq(gnewWith(Array,aArrayRef(buf,1)) , aArray(aInt(0))));
  UTEST(isEq(gnewWith(Array,aArrayRef(buf,2)) , aArray(aInt(0,1))));
  UTEST(isEq(gnewWith(Array,aArrayRef(buf,5)) , aArray(aInt(0,1,2,3,4))));
  UTEST(isEq(gnewWith(Array,aArrayRef(buf,9)) , aArray(aInt(0,1,2,3,4,5,6,7,8))));
  UTEST(isEq(gnewWith(Array,aArrayRef(buf,10)), aArray(aInt(0,1,2,3,4,5,6,7,8,9))));

  // from slice
  UTEST(isEq(gnewWith(Array,aSlice( 0, 1, 1)), aArray(aInt(0))));
  UTEST(isEq(gnewWith(Array,aSlice(-1, 3, 1)), aArray(aInt(-1,0,1))));
  UTEST(isEq(gnewWith(Array,aSlice( 0, 5, 1)), aArray(aInt(0,1,2,3,4))));
  UTEST(isEq(gnewWith(Array,aSlice( 0, 9, 1)), aArray(aInt(0,1,2,3,4,5,6,7,8))));
  UTEST(isEq(gnewWith(Array,aSlice( 0,10, 1)), aArray(aInt(0,1,2,3,4,5,6,7,8,9))));
  UTEST(isEq(gnewWith(Array,aSlice( 0, 5, 2)), aArray(aInt(0,2,4,6,8))));
  UTEST(isEq(gnewWith(Array,aSlice( 1, 5,-2)), aArray(aInt(1,-1,-3,-5,-7))));

  // from range
  UTEST(isEq(gnewWith(Array,aRange( 0, 0, 1)), aArray(aInt(0))));
  UTEST(isEq(gnewWith(Array,aRange(-1, 1, 1)), aArray(aInt(-1,0,1))));
  UTEST(isEq(gnewWith(Array,aRange( 0, 4, 1)), aArray(aInt(0,1,2,3,4))));
  UTEST(isEq(gnewWith(Array,aRange( 0, 8, 1)), aArray(aInt(0,1,2,3,4,5,6,7,8))));
  UTEST(isEq(gnewWith(Array,aRange( 0, 9, 1)), aArray(aInt(0,1,2,3,4,5,6,7,8,9))));
  UTEST(isEq(gnewWith(Array,aRange( 0, 8, 2)), aArray(aInt(0,2,4,6,8))));
  UTEST(isEq(gnewWith(Array,aRange( 1,-7,-2)), aArray(aInt(1,-1,-3,-5,-7))));

  // from xrange
  UTEST(isEq(gnewWith(Array,aXRange( 0, 0, 1)), aArray(aInt(0))));
  UTEST(isEq(gnewWith(Array,aXRange(-1, 1, 1)), aArray(aInt(-1,0,1))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 4, 1)), aArray(aInt(0,1,2,3,4))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 8, 1)), aArray(aInt(0,1,2,3,4,5,6,7,8))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 9, 1)), aArray(aInt(0,1,2,3,4,5,6,7,8,9))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 8, 2)), aArray(aInt(0,2,4,6,8))));
  UTEST(isEq(gnewWith(Array,aXRange( 1,-7,-2)), aArray(aInt(1,-1,-3,-5,-7))));

  UTEST(isEq(gnewWith(Array,aXRange( 0, 0, 0)), aArray(aFlt(0))));
  UTEST(isEq(gnewWith(Array,aXRange(-1, 1, 1)), aArray(aFlt(-1,0,1))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 3, 0.5)), aArray(aFlt(0,0.5,1,1.5,2,2.5,3))));
  UTEST(isEq(gnewWith(Array,aXRange( 0,0.5,..,3)), aArray(aFlt(0,0.5,1,1.5,2,2.5,3))));
  UTEST(isEq(gnewWith(Array,aXRange( 0,0.1,..,0.4)), aArray(aFlt(0,.1,.2,.3,.4))));
  UTEST(isEq(gnewWith(Array,aXRange( 0,0.4,0.1)), aArray(aFlt(0,.1,.2,.3,.4))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 8, 1)), aArray(aFlt(0,1,2,3,4,5,6,7,8))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 9, 1)), aArray(aFlt(0,1,2,3,4,5,6,7,8,9))));
  UTEST(isEq(gnewWith(Array,aXRange( 0, 8, 2)), aArray(aFlt(0,2,4,6,8))));
  UTEST(isEq(gnewWith(Array,aXRange( 1,-7,-2)), aArray(aFlt(1,-1,-3,-5,-7))));

  UTEST_END

  gdelete(pool);
}


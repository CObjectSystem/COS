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
 | $Id: ut_array.c,v 1.10 2010/01/03 15:00:01 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/XRange.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/numop.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <cos/prp/sequence.h>

#include <cos/utest.h>

#include "tests.h"

static BOOL
isEq(OBJ r, OBJ ref)
{
  OBJ res = gisEqual(r, ref);
  gdelete(r);
  return res == True;
}

void
ut_array_basics(void)
{
  useproperty(size);
  useclass(Array, Array1, Array2, Array5, Array9, ArrayN);
  useclass(AutoRelease);
  
  OBJ buf[] = { aInt(0,1,2,3,4,5,6,7,8,9) };
  OBJ pool = gnew(AutoRelease);

  UTEST_START("Array basics")

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
  UTEST(isEq(gnewWith(Array,aArrayRef(buf,0)) , aArrayRef(buf,0)));
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

void
ut_array_functor(void)
{
  useclass(AutoRelease);

  OBJ buf[] = { aInt(0,1,2,3,4,5,6,7,8,9) };
  OBJ pool  = gnew(AutoRelease);
  OBJ id    = aFun(cos_ident, __1);
/* these definitions are equivalent and faster
  OBJ div   = aFun(gdiv      , __1, __2);
  OBJ add   = aFun(gadd      , __1, __2);
  OBJ addTo = aFun(gaddTo    , __1, __2);
  OBJ incr  = aFun(gaddTo    , __1, aInt(1));
  OBJ cmp   = aFun(gcompare  , __1, __2);
  OBJ eq    = aFun(gisEqual  , __1, __2);
  OBJ gt    = aFun(gisGreater, __1, aInt(3));
*/
  OBJ div   = gdiv      (__1, __2);
  OBJ add   = gadd      (__1, __2);
  OBJ addTo = gaddTo    (__1, __2);
  OBJ incr  = gaddTo    (__1, aInt(1));
  OBJ cmp   = gcompare  (__1, __2);
  OBJ eq    = gisEqual  (__1, __2);
  OBJ gt    = gisGreater(__1, aInt(3));
  OBJ arr   = Nil;
  OBJ obj   = Nil;

  UTEST_START("Array functor")

  // apply
  gapply(incr, arr = aArrayRef(buf,0));
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  gapply(incr, arr = aArray(aInt(0)));
  UTEST( gisEqual(arr, aArray(aInt(1))) == True );
  
  gapply(incr, arr = aArray(aInt(0,1,2,3)));
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  gapply(incr, arr = aArray(aInt(0,1,2,3)));
  UTEST( gisEqual(arr, aArray(aInt(0,1,2,3))) == False );

  // map
  arr = gmap(incr, aArrayRef(buf,0));
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gmap(incr, aArray(aInt(0)));
  UTEST( gisEqual(arr, aArray(aInt(1))) == True );
  
  arr = gmap(incr, aArray(aInt(0,1,2,3)));
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  arr = gmap(incr, aArray(aInt(0,1,2,3)));
  UTEST( gisEqual(arr, aArray(aInt(0,1,2,3))) == False );

  // select
  arr = gselect(aArrayRef(buf,0), gt);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gselect(aArray(aInt(4)), gt);
  UTEST( gisEqual(arr, aArray(aInt(4))) == True );
  
  arr = gselect(aArray(aInt(0,1,2,3)), gt);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gselect(aArray(aInt(0,1,2,3,4)), gt);
  UTEST( gisEqual(arr, aArray(aInt(4))) == True );

  arr = gselect(aArray(aInt(0,1,2,3,4,5,6,7,8)), gt);
  UTEST( gisEqual(arr, aArray(aInt(4,5,6,7,8))) == True );

  arr = gselect(aArray(aInt(0,1,2,3,4,5,6,7,8)), gt);
  UTEST( gisEqual(arr, aArray(aInt(3,4,5,6,7,8))) == False );

  // reject
  arr = greject(aArrayRef(buf,0), gt);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = greject(aArray(aInt(3)), gt);
  UTEST( gisEqual(arr, aArray(aInt(3))) == True );
  
  arr = greject(aArray(aInt(4,5,6,7)), gt);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = greject(aArray(aInt(0,1,2,3,4)), gt);
  UTEST( gisEqual(arr, aArray(aInt(0,1,2,3))) == True );

  arr = greject(aArray(aInt(0,1,2,3,4,5,6,7,8)), gt);
  UTEST( gisEqual(arr, aArray(aInt(0,1,2,3))) == True );

  arr = greject(aArray(aInt(0,1,2,3,4,5,6,7,8)), gt);
  UTEST( gisEqual(arr, aArray(aInt(4,5,6,7,8))) == False );

  // reduce
  obj = greduce(aArrayRef(buf,0), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(0)) == True );

  obj = greduce(aArray(aInt(3)), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(3)) == True );
  
  obj = greduce(aArray(aInt(1,2,3)), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(6)) == True );

  obj = greduce(aArray(aInt(1,2,3,4)), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(6)) == False );

  // rreduce
  obj = grreduce(aArrayRef(buf,0), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(0)) == True );

  obj = grreduce(aArray(aInt(3)), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(3)) == True );
  
  obj = grreduce(aArray(aInt(1,2,3)), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(6)) == True );

  obj = grreduce(aArray(aInt(1,2,3,4)), addTo, aInt(0));
  UTEST( gisEqual(obj, aInt(6)) == False );

  // accumulate
  arr = gaccumulate(aArrayRef(buf,0), addTo, aInt(0));
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gaccumulate(aArray(aInt(3)), addTo, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(3))) == True );
  
  arr = gaccumulate(aArray(aInt(1,2,3)), add, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(1,3,6))) == True );

  arr = gaccumulate(aArray(aInt(1,2,3,4)), add, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(1,3,6))) == False );

  arr = gaccumulate(aArray(aInt(64,4,2,8)), div, aInt(64*64));
  UTEST( gisEqual(arr, aArray(aInt(64,16,8,1))) == True );

  // raccumulate
  arr = graccumulate(aArrayRef(buf,0), addTo, aInt(0));
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = graccumulate(aArray(aInt(3)), addTo, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(3))) == True );
  
  graccumulate(arr = aArray(aInt(1,2,3)), addTo, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(6,5,3))) == True );

  arr = graccumulate(aArray(aInt(1,2,3)), add, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(6,5,3))) == True );

  arr = graccumulate(aArray(aInt(1,2,3,4)), add, aInt(0));
  UTEST( gisEqual(arr, aArray(aInt(4,7,9))) == False );

  arr = graccumulate(aArray(aInt(8,12,24,2)), div, aInt(1));
  UTEST( gisEqual(arr, aArray(aInt(8,1,12,2))) == True );

  // all
  UTEST( gall(aArrayRef(buf,0),id) == True );
  UTEST( gall(aArray(True),id) == True );
  UTEST( gall(aArray(False),id) == False );
  UTEST( gall(aArray(True, True, True),id) == True );
  UTEST( gall(aArray(True, False, True),id) == False );
 
  // any
  UTEST( gany(aArrayRef(buf,0),id) == False );
  UTEST( gany(aArray(True),id) == True );
  UTEST( gany(aArray(False),id) == False );
  UTEST( gany(aArray(True, True, True),id) == True );
  UTEST( gany(aArray(False, True, False),id) == True );

  // count
  UTEST( gcount(aArrayRef(buf,0),id) == 0 );
  UTEST( gcount(aArray(True),id) == 1 );
  UTEST( gcount(aArray(False),id) == 0 );
  UTEST( gcount(aArray(True, True, True),id) == 3 );
  UTEST( gcount(aArray(True, False, True),id) == 2 );
  UTEST( gcount(aArray(False, True, False),id) == 1 );

  // unique
  arr = gunique(aArrayRef(buf,0), eq);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gunique(aArray(aInt(1)), eq);
  UTEST( gisEqual(arr, aArray(aInt(1))) == True );

  arr = gunique(aArray(aInt(1,2,3,4)), eq);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  arr = gunique(aArray(aInt(1,1,2,3,4)), eq);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  arr = gunique(aArray(aInt(1,2,3,4,4)), eq);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  arr = gunique(aArray(aInt(1,1,2,2,3,4,4)), eq);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  // find
  obj = gfind(aArrayRef(buf,0), aInt(1));
  UTEST( gisEqual(obj, Nil) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aInt(4));
  UTEST( gisEqual(obj, aInt(4)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aInt(7));
  UTEST( gisEqual(obj, Nil) == True );

  obj = gfind(aArrayRef(buf,0), aFun(gisEqual, aInt(1), __1));
  UTEST( gisEqual(obj, Nil) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gisEqual, aInt(1), __1));
  UTEST( gisEqual(obj, aInt(1)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gisEqual, aInt(2), __1));
  UTEST( gisEqual(obj, aInt(2)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gisEqual, aInt(4), __1));
  UTEST( gisEqual(obj, aInt(4)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gisEqual, aInt(5), __1));
  UTEST( gisEqual(obj, aInt(5)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gisEqual, aInt(7), __1));
  UTEST( gisEqual(obj, Nil) == True );

  obj = gfind(aArrayRef(buf,0), aFun(gcompare, aInt(1), __1));
  UTEST( gisEqual(obj, Nil) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gcompare, aInt(1), __1));
  UTEST( gisEqual(obj, aInt(1)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gcompare, aInt(2), __1));
  UTEST( gisEqual(obj, aInt(2)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gcompare, aInt(4), __1));
  UTEST( gisEqual(obj, aInt(4)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gcompare, aInt(5), __1));
  UTEST( gisEqual(obj, aInt(5)) == True );

  obj = gfind(aArray(aInt(1,2,3,4,5)), aFun(gcompare, aInt(7), __1));
  UTEST( gisEqual(obj, Nil) == True );

  // diff
  arr = gdiff(aArrayRef(buf,0), aArrayRef(buf,0), cmp);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gdiff(aArrayRef(buf,0), aArray(aInt(2,3)), cmp);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gdiff(aArray(aInt(2,3)), aArrayRef(buf,0), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,3))) == True );

  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3))) == True );

  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(2,3)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,4))) == True );
 
  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(1,2)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(3,4))) == True );

  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(1,3)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,4))) == True );

  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(1,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,3))) == True );

  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(1,2,3)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(4))) == True );

  arr = gdiff(aArray(aInt(1,2,3,4)), aArray(aInt(2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1))) == True );

  arr = gdiff(aArray(aInt(1,1,2,2,3,3,4,4)), aArray(aInt(2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,1))) == True );

  arr = gdiff(aArray(aInt(2,1,2,1,3,4,4,3)), aArray(aInt(2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,1))) == True );

  arr = gdiff(aArray(aInt(2,1,2,1,3,4,4,3)), aArray(aInt(2,3,4,5)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,1))) == True );

  // intersect
  arr = gintersect(aArrayRef(buf,0), aArrayRef(buf,0), cmp);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gintersect(aArrayRef(buf,0), aArray(aInt(2,3)), cmp);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gintersect(aArray(aInt(2,3)), aArrayRef(buf,0), cmp);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(4))) == True );

  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(2,3)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,3))) == True );
 
  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(1,2)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,2))) == True );

  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(1,3)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,3))) == True );

  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(1,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,4))) == True );

  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(1,2,3)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3))) == True );

  arr = gintersect(aArray(aInt(1,2,3,4)), aArray(aInt(2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,3,4))) == True );

  arr = gintersect(aArray(aInt(1,1,2,2,3,3,4,4)), aArray(aInt(2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,2,3,3,4,4))) == True );

  arr = gintersect(aArray(aInt(1,1,2,2,3,3,4,4)), aArray(aInt(2,3,4,5)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(2,2,3,3,4,4))) == True );

  // sort
  arr = gsort(aArrayRef(buf,0), cmp);
  UTEST( gisEqual(arr, aArrayRef(buf,0)) == True );

  arr = gsort(aArray(aInt(1,2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  arr = gsort(aArray(aInt(1,3,2,3,4)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,3,4))) == True );

  arr = gsort(aArray(aInt(4,3,2,1)), cmp);
  UTEST( gisEqual(arr, aArray(aInt(1,2,3,4))) == True );

  // isSorted
  obj = gisSorted(aArrayRef(buf,0), cmp);
  UTEST( obj == True );

  obj = gisSorted(aArray(aInt(1,2,3,4)), cmp);
  UTEST( obj == True );

  obj = gisSorted(aArray(aInt(1,2,3,2,3,4)), cmp);
  UTEST( obj == False );

  UTEST_END

  gdelete(pool);
}


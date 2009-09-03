/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - range
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
 | $Id: ut_xrange.c,v 1.1 2009/09/03 23:22:32 ldeniau Exp $
 |
*/

#include <cos/XRange.h>
#include <cos/gen/compare.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/utest.h>

#include "tests.h"

static BOOL
eq(struct XRange r, struct XRange *ref)
{
  return XRange_isEqual(&r, ref);
}

static BOOL
isEq(OBJ r, OBJ ref)
{
  OBJ res = gisEqual(r, ref);
  gdelete(r);
  return res == True;
}

void
ut_xrange(void)
{
  useclass(XRange);

  UTEST_START("XRange")

    // equality and default args
    UTEST( XRange_isEqual(atXRange(10)  , atXRange(0,10, 1))  );
    UTEST( XRange_isEqual(atXRange(0,10), atXRange(0,10, 1))  );
    UTEST(!XRange_isEqual(atXRange(0,10), atXRange(0,10,-1))  );
    UTEST( XRange_isEqual(atXRange(0,10), atXRange(0,10, 0))  );

    UTEST( gisEqual(aXRange(10)  , aXRange(0,10, 1)) == True  );
    UTEST( gisEqual(aXRange(0,10), aXRange(0,10, 1)) == True  );
    UTEST( gisEqual(aXRange(0,10), aXRange(0,10,-1)) == False );

    // new vs auto
    UTEST( isEq(gnewXRng1(XRange, 10), aXRange(0,10,1)) );
    UTEST( isEq(gnewXRng2(XRange, 0, 10), aXRange(0,10,1)) );
    UTEST( isEq(gnewXRng3(XRange, 0, 10, 1), aXRange(0,10,1)) );
    UTEST(!isEq(gnewXRng1(XRange, 10), aXRange(0,10,-1)) );

    // clone vs auto
    UTEST( isEq(gclone(aXRange(10)), aXRange(10)) );
    UTEST( isEq(gclone(aXRange(0,10)), aXRange(0,10)) );
    UTEST( isEq(gclone(aXRange(0,10,-1)), aXRange(0,10,-1)) );

    // eval
    UTEST( float_equal(XRange_eval(atXRange(10),0),0) );
    UTEST( float_equal(XRange_eval(atXRange(10),1),1) );
    UTEST( float_equal(XRange_eval(atXRange(10),10),10) );
    UTEST( float_equal(XRange_eval(atXRange(1,10),0),1) );
    UTEST( float_equal(XRange_eval(atXRange(1,10),1),2) );
    UTEST( float_equal(XRange_eval(atXRange(1,10),10),11) );
    UTEST( float_equal(XRange_eval(atXRange(1,10,2),0),1) );
    UTEST( float_equal(XRange_eval(atXRange(1,10,2),1),3) );
    UTEST( float_equal(XRange_eval(atXRange(1,10,2),10),21) );
    UTEST( float_equal(XRange_eval(atXRange(10,1,-2),0),10) );
    UTEST( float_equal(XRange_eval(atXRange(10,1,-2),1),8) );
    UTEST( float_equal(XRange_eval(atXRange(10,1,-2),10),-10) );

    // size
    UTEST( XRange_size(atXRange(0,9,1)) == 10 );
    UTEST( XRange_size(atXRange(1,10,1)) == 10 );
    UTEST( XRange_size(atXRange(1,10,2)) == 5 );
    UTEST( XRange_size(atXRange(1,10,3)) == 4 );
    UTEST( XRange_size(atXRange(1,9,3)) == 3 );

    UTEST( XRange_size(atXRange(9,0,-1)) == 10 );
    UTEST( XRange_size(atXRange(10,1,-1)) == 10 );
    UTEST( XRange_size(atXRange(10,1,-2)) == 5 );
    UTEST( XRange_size(atXRange(10,1,-3)) == 4 );
    UTEST( XRange_size(atXRange(9,1,-3)) == 3 );

    UTEST( XRange_size(atXRange(-1,-10,-1)) == 10 );
    UTEST( XRange_size(atXRange(-1,-10,-2)) == 5 );
    UTEST( XRange_size(atXRange(-1,-10,-3)) == 4 );
    UTEST( XRange_size(atXRange(-1,-9,-3)) == 3 );

    UTEST( XRange_size(atXRange(-10,-1,1)) == 10 );
    UTEST( XRange_size(atXRange(-10,-1,2)) == 5 );
    UTEST( XRange_size(atXRange(-10,-1,3)) == 4 );
    UTEST( XRange_size(atXRange(-9,-1,3)) == 3 );

    UTEST( XRange_size(atXRange(-10,-1,-1)) == 0 );
    UTEST( XRange_size(atXRange(-10,-1,-2)) == 0 );
    UTEST( XRange_size(atXRange(-10,-1,-3)) == 0 );
    UTEST( XRange_size(atXRange(-9,-1,-3)) == 0 );

    UTEST( XRange_size(atXRange(1,-1,1)) == 0 );
    UTEST( XRange_size(atXRange(1,-1,2)) == 0 );
    UTEST( XRange_size(atXRange(0,-1,3)) == 0 );
    UTEST( XRange_size(atXRange(1,-1,3)) == 0 );
    UTEST( XRange_size(atXRange(1,-9,3)) == 0 );

    UTEST( XRange_size(atXRange(-1,1,-1)) == 0 );
    UTEST( XRange_size(atXRange(-1,1,-2)) == 0 );
    UTEST( XRange_size(atXRange(-1,0,-3)) == 0 );
    UTEST( XRange_size(atXRange(-1,1,-3)) == 0 );
    UTEST( XRange_size(atXRange(-1,9,-3)) == 0 );

    UTEST( XRange_size(atXRange(-1,1,1)) == 3 );
    UTEST( XRange_size(atXRange(-1,1,2)) == 2 );
    UTEST( XRange_size(atXRange(-1,0,3)) == 1 );
    UTEST( XRange_size(atXRange(-1,1,3)) == 1 );
    UTEST( XRange_size(atXRange(-1,9,3)) == 4 );

    // closed
    UTEST( XRange_isClosed(atXRange(0,10,1)) );
    UTEST(!XRange_isClosed(atXRange(0,10,-1)) );
    UTEST(!XRange_isClosed(atXRange(10,0,1)) );
    UTEST( XRange_isClosed(atXRange(10,0,-1)) );

    UTEST(!XRange_isClosed(atXRange(-1,1,-1)) );
    UTEST( XRange_isClosed(atXRange(1,-1,-1)) );
    UTEST( XRange_isClosed(atXRange(-1,1,1)) );
    UTEST(!XRange_isClosed(atXRange(1,-1,1)) );

    // size (floating)
    UTEST( XRange_size(atXRange(0,9,0.1)) == 91 );
    UTEST( XRange_size(atXRange(1,10,0.1)) == 91 );
    UTEST( XRange_size(atXRange(1,10,0.2)) == 46 );
    UTEST( XRange_size(atXRange(1,10,0.3)) == 31 );
    UTEST( XRange_size(atXRange(1,9,0.3)) == 27 );

    UTEST( XRange_size(atXRange(9,0,-0.1)) == 91 );
    UTEST( XRange_size(atXRange(10,1,-0.1)) == 91 );
    UTEST( XRange_size(atXRange(10,1,-0.2)) == 46 );
    UTEST( XRange_size(atXRange(10,1,-0.3)) == 31 );
    UTEST( XRange_size(atXRange(9,1,-0.3)) == 27 );

    UTEST( XRange_size(atXRange(-1,-10,-0.1)) == 91 );
    UTEST( XRange_size(atXRange(-1,-10,-0.2)) == 46 );
    UTEST( XRange_size(atXRange(-1,-10,-0.3)) == 31 );
    UTEST( XRange_size(atXRange(-1,-9,-0.3)) == 27 );

    UTEST( XRange_size(atXRange(-10,-1,0.1)) == 91 );
    UTEST( XRange_size(atXRange(-10,-1,0.2)) == 46 );
    UTEST( XRange_size(atXRange(-10,-1,0.3)) == 31 );
    UTEST( XRange_size(atXRange(-9,-1,0.3)) == 27 );

    UTEST( XRange_size(atXRange(-10,-1,-0.1)) == 0 );
    UTEST( XRange_size(atXRange(-10,-1,-0.2)) == 0 );
    UTEST( XRange_size(atXRange(-10,-1,-0.3)) == 0 );
    UTEST( XRange_size(atXRange(-9,-1,-0.3)) == 0 );

    UTEST( XRange_size(atXRange(1,-1,0.1)) == 0 );
    UTEST( XRange_size(atXRange(1,-1,0.2)) == 0 );
    UTEST( XRange_size(atXRange(0,-1,0.3)) == 0 );
    UTEST( XRange_size(atXRange(1,-1,0.3)) == 0 );
    UTEST( XRange_size(atXRange(1,-9,0.3)) == 0 );

    UTEST( XRange_size(atXRange(-1,1,-0.1)) == 0 );
    UTEST( XRange_size(atXRange(-1,1,-0.2)) == 0 );
    UTEST( XRange_size(atXRange(-1,0,-0.3)) == 0 );
    UTEST( XRange_size(atXRange(-1,1,-0.3)) == 0 );
    UTEST( XRange_size(atXRange(-1,9,-0.3)) == 0 );

    UTEST( XRange_size(atXRange(-1,1,0.1)) == 21 );
    UTEST( XRange_size(atXRange(-1,1,0.2)) == 11 );
    UTEST( XRange_size(atXRange(-1,0,0.3)) == 4 );
    UTEST( XRange_size(atXRange(-1,1,0.3)) == 7 );
    UTEST( XRange_size(atXRange(-1,9,0.3)) == 34 );

    // xrange vs enumeration
    UTEST( gisEqual(aXRange(1,2,..,10), aXRange(1,10,1)) == True );
    UTEST( gisEqual(aXRange(0,2,..,10), aXRange(0,10,2)) == True );
    UTEST( gisEqual(aXRange(-1,-2,..,-10), aXRange(-1,-10,-1)) == True );
    UTEST( gisEqual(aXRange(1,-2,..,-10), aXRange(1,-10,-3)) == True );

    UTEST( gisEqual(aXRange(1,2.1,..,10), aXRange(1,10,1.1)) == True );
    UTEST( gisEqual(aXRange(0,2.1,..,10), aXRange(0,10,2.1)) == True );
    UTEST( gisEqual(aXRange(-1,-2.1,..,-10), aXRange(-1,-10,-1.1)) == True );
    UTEST( gisEqual(aXRange(1,-2.1,..,-10), aXRange(1,-10,-3.1)) == True );

    // xrange vs slice
    UTEST( eq(XRange_fromSlice(atSlice(-1,3,1)), atXRange(-1,1,1)) );
    UTEST( eq(XRange_fromSlice(atSlice(-1,2,2)), atXRange(-1,1,2)) );
    UTEST( eq(XRange_fromSlice(atSlice(-1,3,3)), atXRange(-1,5,3)) );
    UTEST( eq(XRange_fromSlice(atSlice(-1,2,3)), atXRange(-1,2,3)) );
    UTEST( eq(XRange_fromSlice(atSlice( 1,2,3)), atXRange( 1,4,3)) );

    UTEST( eq(XRange_fromSlice(atSlice(9,10,-1)), atXRange(9,0,-1)) );
    UTEST( eq(XRange_fromSlice(atSlice(9,5,-2)), atXRange(9,1,-2)) );
    UTEST( eq(XRange_fromSlice(atSlice(9,4,-3)), atXRange(9,0,-3)) );
    UTEST( eq(XRange_fromSlice(atSlice(9,3,-3)), atXRange(9,3,-3)) );

    UTEST( eq(XRange_fromSlice(atSlice(0,10,1)),atXRange(0,9,1)) );
    UTEST( eq(XRange_fromSlice(atSlice(1,10,1)),atXRange(1,10,1)) );
    UTEST( eq(XRange_fromSlice(atSlice(1,5,2)),atXRange(1,9,2)) );
    UTEST( eq(XRange_fromSlice(atSlice(1,4,3)),atXRange(1,10,3)) );
    UTEST( eq(XRange_fromSlice(atSlice(1,3,3)),atXRange(1,7,3)) );

    UTEST( eq(XRange_fromSlice(atSlice(9,10,-1)),atXRange(9,0,-1)) );
    UTEST( eq(XRange_fromSlice(atSlice(10,10,-1)),atXRange(10,1,-1)) );
    UTEST( eq(XRange_fromSlice(atSlice(10,5,-2)),atXRange(10,2,-2)) );
    UTEST( eq(XRange_fromSlice(atSlice(10,4,-3)),atXRange(10,1,-3)) );
    UTEST( eq(XRange_fromSlice(atSlice(9,3,-3)),atXRange(9,3,-3)) );

    UTEST( eq(XRange_fromSlice(atSlice(-1,10,-1)),atXRange(-1,-10,-1)) );
    UTEST( eq(XRange_fromSlice(atSlice(-1,5,-2)),atXRange(-1,-9,-2)) );
    UTEST( eq(XRange_fromSlice(atSlice(-1,4,-3)),atXRange(-1,-10,-3)) );
    UTEST( eq(XRange_fromSlice(atSlice(-1,3,-3)),atXRange(-1,-7,-3)) );

    UTEST( eq(XRange_fromSlice(atSlice(-10,10,1)),atXRange(-10,-1,1)) );
    UTEST( eq(XRange_fromSlice(atSlice(-10,5,2)),atXRange(-10,-2,2)) );
    UTEST( eq(XRange_fromSlice(atSlice(-10,4,3)),atXRange(-10,-1,3)) );
    UTEST( eq(XRange_fromSlice(atSlice(-9,3,3)),atXRange(-9,-3,3)) );
    
    // xrange vs range
    UTEST( eq(XRange_fromRange(atRange(-1,1,1)), atXRange(-1,1,1)) );
    UTEST( eq(XRange_fromRange(atRange(-1,1,2)), atXRange(-1,1,2)) );
    UTEST( eq(XRange_fromRange(atRange(-1,5,3)), atXRange(-1,5,3)) );
    UTEST( eq(XRange_fromRange(atRange(-1,2,3)), atXRange(-1,2,3)) );
    UTEST( eq(XRange_fromRange(atRange( 1,4,3)), atXRange( 1,4,3)) );

    UTEST( eq(XRange_fromRange(atRange(9,0,-1)), atXRange(9,0,-1)) );
    UTEST( eq(XRange_fromRange(atRange(9,1,-2)), atXRange(9,1,-2)) );
    UTEST( eq(XRange_fromRange(atRange(9,0,-3)), atXRange(9,0,-3)) );
    UTEST( eq(XRange_fromRange(atRange(9,3,-3)), atXRange(9,3,-3)) );

    UTEST( eq(XRange_fromRange(atRange(0,9,1)),atXRange(0,9,1)) );
    UTEST( eq(XRange_fromRange(atRange(1,10,1)),atXRange(1,10,1)) );
    UTEST( eq(XRange_fromRange(atRange(1,9,2)),atXRange(1,9,2)) );
    UTEST( eq(XRange_fromRange(atRange(1,10,3)),atXRange(1,10,3)) );
    UTEST( eq(XRange_fromRange(atRange(1,7,3)),atXRange(1,7,3)) );

    UTEST( eq(XRange_fromRange(atRange(9,0,-1)),atXRange(9,0,-1)) );
    UTEST( eq(XRange_fromRange(atRange(10,1,-1)),atXRange(10,1,-1)) );
    UTEST( eq(XRange_fromRange(atRange(10,2,-2)),atXRange(10,2,-2)) );
    UTEST( eq(XRange_fromRange(atRange(10,1,-3)),atXRange(10,1,-3)) );
    UTEST( eq(XRange_fromRange(atRange(9,3,-3)),atXRange(9,3,-3)) );

    UTEST( eq(XRange_fromRange(atRange(-1,-10,-1)),atXRange(-1,-10,-1)) );
    UTEST( eq(XRange_fromRange(atRange(-1,-9,-2)),atXRange(-1,-9,-2)) );
    UTEST( eq(XRange_fromRange(atRange(-1,-10,-3)),atXRange(-1,-10,-3)) );
    UTEST( eq(XRange_fromRange(atRange(-1,-7,-3)),atXRange(-1,-7,-3)) );

    UTEST( eq(XRange_fromRange(atRange(-10,-1,1)),atXRange(-10,-1,1)) );
    UTEST( eq(XRange_fromRange(atRange(-10,-2,2)),atXRange(-10,-2,2)) );
    UTEST( eq(XRange_fromRange(atRange(-10,-1,3)),atXRange(-10,-1,3)) );
    UTEST( eq(XRange_fromRange(atRange(-9,-3,3)),atXRange(-9,-3,3)) );

  UTEST_END
}


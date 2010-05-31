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
 | $Id: ut_range.c,v 1.10 2010/05/31 14:02:59 ldeniau Exp $
 |
*/

#include <cos/Range.h>
#include <cos/gen/object.h>
#include <cos/gen/range.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/utest.h>

#include "tests.h"

static BOOL
eq(struct Range *r, struct Range *ref)
{
  return Range_isEqual(r, ref);
}

static BOOL
isEq(OBJ r, OBJ ref)
{
  OBJ res = gisEqual(r, ref);
  grelease(r);
  return res == True;
}

void
ut_range(void)
{
  useclass(Range);

  UTEST_START("Range")

    // equality and default args
    UTEST( Range_isEqual(atRange(10)  , atRange(0,10, 1))  );
    UTEST( Range_isEqual(atRange(0,10), atRange(0,10, 1))  );
    UTEST(!Range_isEqual(atRange(0,10), atRange(0,10,-1))  );
    UTEST( Range_isEqual(atRange(0,10), atRange(0,10, 0))  );

    UTEST( gisEqual(aRange(10)  , aRange(0,10, 1)) == True  );
    UTEST( gisEqual(aRange(0,10), aRange(0,10, 1)) == True  );
    UTEST( gisEqual(aRange(0,10), aRange(0,10,-1)) == False );

    // new vs auto
    UTEST( isEq(gnewRng(Range, 0, 10, 1), aRange(0,10,1)) );
    UTEST(!isEq(gnewRng(Range, 0, 10, 1), aRange(0,10,-1)) );

    // clone vs auto
    UTEST( isEq(gclone(aRange(10)), aRange(10)) );
    UTEST( isEq(gclone(aRange(0,10)), aRange(0,10)) );
    UTEST( isEq(gclone(aRange(0,10,-1)), aRange(0,10,-1)) );

    // index
    UTEST( Range_index(3,0) == 3 );
    UTEST( Range_index(3,10) == 3 );
    UTEST( Range_index(3,-10) == 3 );
    UTEST( Range_index(-3,0) == (U32)-3 + 0 );
    UTEST( Range_index(-3,10) == -3 + 10 );
    UTEST( Range_index(-3,-10) == (U32)-3 + -10 );

    // eval
    UTEST( Range_eval(atRange(10),0) == 0 );
    UTEST( Range_eval(atRange(10),1) == 1 );
    UTEST( Range_eval(atRange(10),10) == 10 );
    UTEST( Range_eval(atRange(1,10),0) == 1 );
    UTEST( Range_eval(atRange(1,10),1) == 2 );
    UTEST( Range_eval(atRange(1,10),10) == 11 );
    UTEST( Range_eval(atRange(1,10,2),0) == 1 );
    UTEST( Range_eval(atRange(1,10,2),1) == 3 );
    UTEST( Range_eval(atRange(1,10,2),10) == 21 );
    UTEST( Range_eval(atRange(10,1,-2),0) == 10 );
    UTEST( Range_eval(atRange(10,1,-2),1) == 8 );
    UTEST( Range_eval(atRange(10,1,-2),10) == -10 );

    // first
    UTEST( Range_first(atRange(10),0) == 0 );
    UTEST( Range_first(atRange(1,10),0) ==  1 );
    UTEST( Range_first(atRange(-1,10),0) == (U32)-1 );
    UTEST( Range_first(atRange(-1,10),10) == 9 );

    // last
    UTEST( Range_last(atRange(10),0) == 10 );
    UTEST( Range_last(atRange(0,-10),0) == (U32)-10 );
    UTEST( Range_last(atRange(-1,-10),0) == (U32)-10 );
    UTEST( Range_last(atRange(-1,-10),10) == 0 );

    // size
    UTEST( Range_size(atRange(0,9,1)) == 10 );
    UTEST( Range_size(atRange(1,10,1)) == 10 );
    UTEST( Range_size(atRange(1,10,2)) == 5 );
    UTEST( Range_size(atRange(1,10,3)) == 4 );
    UTEST( Range_size(atRange(1,9,3)) == 3 );

    UTEST( Range_size(atRange(9,0,-1)) == 10 );
    UTEST( Range_size(atRange(10,1,-1)) == 10 );
    UTEST( Range_size(atRange(10,1,-2)) == 5 );
    UTEST( Range_size(atRange(10,1,-3)) == 4 );
    UTEST( Range_size(atRange(9,1,-3)) == 3 );

    // size
    UTEST( Range_size(atRange(-1,-10,-1)) == 10 );
    UTEST( Range_size(atRange(-1,-10,-2)) == 5 );
    UTEST( Range_size(atRange(-1,-10,-3)) == 4 );
    UTEST( Range_size(atRange(-1,-9,-3)) == 3 );

    UTEST( Range_size(atRange(-10,-1,1)) == 10 );
    UTEST( Range_size(atRange(-10,-1,2)) == 5 );
    UTEST( Range_size(atRange(-10,-1,3)) == 4 );
    UTEST( Range_size(atRange(-9,-1,3)) == 3 );

    UTEST( Range_size(atRange(-10,-1,-1)) == 0 );
    UTEST( Range_size(atRange(-10,-1,-2)) == 0 );
    UTEST( Range_size(atRange(-10,-1,-3)) == 0 );
    UTEST( Range_size(atRange(-9,-1,-3)) == 0 );

    UTEST( Range_size(atRange(1,-1,1)) == 0 );
    UTEST( Range_size(atRange(1,-1,2)) == 0 );
    UTEST( Range_size(atRange(0,-1,3)) == 0 );
    UTEST( Range_size(atRange(1,-1,3)) == 0 );
    UTEST( Range_size(atRange(1,-9,3)) == 0 );

    UTEST( Range_size(atRange(-1,1,-1)) == 0 );
    UTEST( Range_size(atRange(-1,1,-2)) == 0 );
    UTEST( Range_size(atRange(-1,0,-3)) == 0 );
    UTEST( Range_size(atRange(-1,1,-3)) == 0 );
    UTEST( Range_size(atRange(-1,9,-3)) == 0 );

    UTEST( Range_size(atRange(-1,1,1)) == 3 );
    UTEST( Range_size(atRange(-1,1,2)) == 2 );
    UTEST( Range_size(atRange(-1,0,3)) == 1 );
    UTEST( Range_size(atRange(-1,1,3)) == 1 );
    UTEST( Range_size(atRange(-1,9,3)) == 4 );

    // closed
    UTEST( Range_isClosed(atRange(0,10,1)) );
    UTEST(!Range_isClosed(atRange(0,10,-1)) );
    UTEST(!Range_isClosed(atRange(10,0,1)) );
    UTEST( Range_isClosed(atRange(10,0,-1)) );

    UTEST(!Range_isClosed(atRange(-1,1,-1)) );
    UTEST( Range_isClosed(atRange(1,-1,-1)) );
    UTEST( Range_isClosed(atRange(-1,1,1)) );
    UTEST(!Range_isClosed(atRange(1,-1,1)) );

    // normalize (seq size independant)
    UTEST( eq(Range_normalize(atRange(0,9,1),0), atRange(0,9,1)) );
    UTEST( eq(Range_normalize(atRange(1,10,1),0), atRange(1,10,1)) );
    UTEST( eq(Range_normalize(atRange(1,10,2),0), atRange(1,10,2)) );
    UTEST( eq(Range_normalize(atRange(1,10,3),0), atRange(1,10,3)) );
    UTEST( eq(Range_normalize(atRange(1,9,3),0), atRange(1,9,3)) );

    UTEST( eq(Range_normalize(atRange(9,0,-1),0), atRange(9,0,-1)) );
    UTEST( eq(Range_normalize(atRange(10,1,-1),0), atRange(10,1,-1)) );
    UTEST( eq(Range_normalize(atRange(10,1,-2),0), atRange(10,1,-2)) );
    UTEST( eq(Range_normalize(atRange(10,1,-3),0), atRange(10,1,-3)) );
    UTEST( eq(Range_normalize(atRange(9,1,-3),0), atRange(9,1,-3)) );

    // normalize (seq size dependant: negative indexes)
    UTEST( eq(Range_normalize(atRange(-1,-10,-1),10), atRange(9,0,-1)) );
    UTEST( eq(Range_normalize(atRange(-1,-10,-2),10), atRange(9,0,-2)) );
    UTEST( eq(Range_normalize(atRange(-1,-10,-3),10), atRange(9,0,-3)) );
    UTEST( eq(Range_normalize(atRange(-1,-9,-3),10), atRange(9,1,-3)) );

    UTEST( eq(Range_normalize(atRange(-10,-1,1),10), atRange(0,9,1)) );
    UTEST( eq(Range_normalize(atRange(-10,-1,2),10), atRange(0,9,2)) );
    UTEST( eq(Range_normalize(atRange(-10,-1,3),10), atRange(0,9,3)) );
    UTEST( eq(Range_normalize(atRange(-9,-1,3),10), atRange(1,9,3)) );

    UTEST( eq(Range_normalize(atRange(1,-1,1),10), atRange(1,9,1)) );
    UTEST( eq(Range_normalize(atRange(1,-1,2),10), atRange(1,9,2)) );
    UTEST( eq(Range_normalize(atRange(0,-1,3),10), atRange(0,9,3)) );
    UTEST( eq(Range_normalize(atRange(1,-1,3),10), atRange(1,9,3)) );
    UTEST( eq(Range_normalize(atRange(1,-9,3),10), atRange(1,1,3)) );

    UTEST( eq(Range_normalize(atRange(-1,1,-1),10), atRange(9,1,-1)) );
    UTEST( eq(Range_normalize(atRange(-1,1,-2),10), atRange(9,1,-2)) );
    UTEST( eq(Range_normalize(atRange(-1,0,-3),10), atRange(9,0,-3)) );
    UTEST( eq(Range_normalize(atRange(-1,1,-3),10), atRange(9,1,-3)) );
    UTEST( eq(Range_normalize(atRange(-1,9,-3),10), atRange(9,9,-3)) );

    // range vs enumeration
    UTEST( gisEqual(aRange(1,2,..,10), aRange(1,10, 1)) == True );
    UTEST( gisEqual(aRange(0,2,..,10), aRange(0,10, 2)) == True );
    UTEST( gisEqual(aRange(-1,-2,..,-10), aRange(-1,-10,-1)) == True );
    UTEST( gisEqual(aRange(1,-2,..,-10), aRange(1,-10,-3)) == True );

    // range vs slice
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,3,1)), atRange(-1,1,1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,2,2)), atRange(-1,1,2)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,3,3)), atRange(-1,5,3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,2,3)), atRange(-1,2,3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice( 1,2,3)), atRange( 1,4,3)) );

    UTEST( eq(Range_fromSlice(atRange(0), atSlice(9,10,-1)), atRange(9,0,-1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(9,5,-2)), atRange(9,1,-2)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(9,4,-3)), atRange(9,0,-3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(9,3,-3)), atRange(9,3,-3)) );

    UTEST( eq(Range_fromSlice(atRange(0), atSlice(0,10,1)),atRange(0,9,1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(1,10,1)),atRange(1,10,1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(1,5,2)),atRange(1,9,2)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(1,4,3)),atRange(1,10,3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(1,3,3)),atRange(1,7,3)) );

    UTEST( eq(Range_fromSlice(atRange(0), atSlice(9,10,-1)),atRange(9,0,-1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(10,10,-1)),atRange(10,1,-1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(10,5,-2)),atRange(10,2,-2)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(10,4,-3)),atRange(10,1,-3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(9,3,-3)),atRange(9,3,-3)) );

    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,10,-1)),atRange(-1,-10,-1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,5,-2)),atRange(-1,-9,-2)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,4,-3)),atRange(-1,-10,-3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-1,3,-3)),atRange(-1,-7,-3)) );

    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-10,10,1)),atRange(-10,-1,1)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-10,5,2)),atRange(-10,-2,2)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-10,4,3)),atRange(-10,-1,3)) );
    UTEST( eq(Range_fromSlice(atRange(0), atSlice(-9,3,3)),atRange(-9,-3,3)) );

  UTEST_END
}


/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - slice
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
 | $Id: ut_slice.c,v 1.7 2010/02/02 16:27:42 ldeniau Exp $
 |
*/

#include <cos/Slice.h>
#include <cos/gen/object.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/utest.h>

#include "tests.h"

static BOOL
eq(struct Slice s, struct Slice *ref)
{
  return Slice_isEqual(&s, ref);
}

static BOOL
isEq(OBJ s, OBJ ref)
{
  OBJ res = gisEqual(s, ref);
  gdelete(s);
  return res == True;
}

void
ut_slice(void)
{
  useclass(Slice);

  UTEST_START("Slice")

    // equality and default args
    UTEST( Slice_isEqual(atSlice(10)  , atSlice(0,10, 1))  );
    UTEST( Slice_isEqual(atSlice(0,10), atSlice(0,10, 1))  );
    UTEST(!Slice_isEqual(atSlice(0,10), atSlice(0,10,-1))  );
    UTEST( Slice_isEqual(atSlice(0,10), atSlice(0,10, 0))  );

    UTEST( gisEqual(aSlice(10)  , aSlice(0,10, 1)) == True  );
    UTEST( gisEqual(aSlice(0,10), aSlice(0,10, 1)) == True  );
    UTEST( gisEqual(aSlice(0,10), aSlice(0,10,-1)) == False );

    // new vs auto
    UTEST( isEq(gnewSlc(Slice, 0, 10, 1), aSlice(0,10,1)) );
    UTEST(!isEq(gnewSlc(Slice, 0, 10, 1), aSlice(0,10,-1)) );

    // clone vs auto
    UTEST( isEq(gclone(aSlice(10)), aSlice(10)) );
    UTEST( isEq(gclone(aSlice(0,10)), aSlice(0,10)) );
    UTEST( isEq(gclone(aSlice(0,10,-1)), aSlice(0,10,-1)) );
    
    // eval
    UTEST( Slice_eval(atSlice(10),0) == 0 );
    UTEST( Slice_eval(atSlice(10),1) == 1 );
    UTEST( Slice_eval(atSlice(10),10) == 10 );
    UTEST( Slice_eval(atSlice(1,10),0) == 1 );
    UTEST( Slice_eval(atSlice(1,10),1) == 2 );
    UTEST( Slice_eval(atSlice(1,10),10) == 11 );
    UTEST( Slice_eval(atSlice(1,10,2),0) == 1 );
    UTEST( Slice_eval(atSlice(1,10,2),1) == 3 );
    UTEST( Slice_eval(atSlice(1,10,2),10) == 21 );
    UTEST( Slice_eval(atSlice(10,1,-2),0) == 10 );
    UTEST( Slice_eval(atSlice(10,1,-2),1) == 8 );
    UTEST( Slice_eval(atSlice(10,1,-2),10) == -10 );

    // first
    UTEST( Slice_first(atSlice(10)) == 0 );
    UTEST( Slice_first(atSlice(1,10)) == 1 );
    UTEST( Slice_first(atSlice(-1,10)) == (U32)-1 );
    UTEST( Slice_first(atSlice(-1,-10)) == (U32)-1 );

    // last
    UTEST( Slice_last(atSlice(10)) == 9 );
    UTEST( Slice_last(atSlice(1,10)) == 10 );
    UTEST( Slice_last(atSlice(1,10,2)) == 19 );
    UTEST( Slice_last(atSlice(0,-10)) == (U32)-11 );
    UTEST( Slice_last(atSlice(-1,-10)) == (U32)-12 );

    // size
    UTEST( Slice_size(atSlice(0,9,1)) == 9 );
    UTEST( Slice_size(atSlice(1,10,1)) == 10 );
    UTEST( Slice_size(atSlice(1,10,2)) == 10 );
    UTEST( Slice_size(atSlice(1,10,3)) == 10 );
    UTEST( Slice_size(atSlice(1,9,3)) == 9 );

    UTEST( Slice_size(atSlice(9,0,-1)) == 0 );
    UTEST( Slice_size(atSlice(10,1,-1)) == 1 );
    UTEST( Slice_size(atSlice(10,1,-2)) == 1 );
    UTEST( Slice_size(atSlice(10,1,-3)) == 1 );
    UTEST( Slice_size(atSlice(9,1,-3)) == 1 );

    // slice vs range
    UTEST( eq(Slice_fromRange(atRange(-1,1,1)), atSlice(-1,3,1)) );
    UTEST( eq(Slice_fromRange(atRange(-1,1,2)), atSlice(-1,2,2)) );
    UTEST( eq(Slice_fromRange(atRange(-1,5,3)), atSlice(-1,3,3)) );
    UTEST( eq(Slice_fromRange(atRange(-1,4,3)), atSlice(-1,2,3)) );
    UTEST( eq(Slice_fromRange(atRange( 1,5,3)), atSlice( 1,2,3)) );

    UTEST( eq(Slice_fromRange(atRange(9,0,-1)), atSlice(9,10,-1)) );
    UTEST( eq(Slice_fromRange(atRange(9,1,-2)), atSlice(9,5,-2)) );
    UTEST( eq(Slice_fromRange(atRange(9,0,-3)), atSlice(9,4,-3)) );
    UTEST( eq(Slice_fromRange(atRange(9,3,-3)), atSlice(9,3,-3)) );

    UTEST( eq(Slice_fromRange(atRange(0,9,1)),  atSlice(0,10,1)) );
    UTEST( eq(Slice_fromRange(atRange(1,10,1)), atSlice(1,10,1)) );
    UTEST( eq(Slice_fromRange(atRange(1,9,2)),  atSlice(1,5,2)) );
    UTEST( eq(Slice_fromRange(atRange(1,10,3)), atSlice(1,4,3)) );
    UTEST( eq(Slice_fromRange(atRange(1,7,3)),  atSlice(1,3,3)) );

    UTEST( eq(Slice_fromRange(atRange(9,0,-1)), atSlice(9,10,-1)) );
    UTEST( eq(Slice_fromRange(atRange(10,1,-1)),atSlice(10,10,-1)) );
    UTEST( eq(Slice_fromRange(atRange(10,2,-2)),atSlice(10,5,-2)) );
    UTEST( eq(Slice_fromRange(atRange(10,1,-3)),atSlice(10,4,-3)) );
    UTEST( eq(Slice_fromRange(atRange(9,3,-3)), atSlice(9,3,-3)) );

    UTEST( eq(Slice_fromRange(atRange(-1,-10,-1)),atSlice(-1,10,-1)) );
    UTEST( eq(Slice_fromRange(atRange(-1,-9,-2)),atSlice(-1,5,-2)) );
    UTEST( eq(Slice_fromRange(atRange(-1,-10,-3)),atSlice(-1,4,-3)) );
    UTEST( eq(Slice_fromRange(atRange(-1,-7,-3)),atSlice(-1,3,-3)) );

    UTEST( eq(Slice_fromRange(atRange(-10,-1,1)),atSlice(-10,10,1)) );
    UTEST( eq(Slice_fromRange(atRange(-10,-2,2)),atSlice(-10,5,2)) );
    UTEST( eq(Slice_fromRange(atRange(-10,-1,3)),atSlice(-10,4,3)) );
    UTEST( eq(Slice_fromRange(atRange(-9,-3,3)),atSlice(-9,3,3)) );

  UTEST_END
}


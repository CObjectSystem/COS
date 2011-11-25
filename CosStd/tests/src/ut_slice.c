/**
 * C Object System
 * COS testsuites - slice
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

#include <cos/Slice.h>
#include <cos/gen/object.h>
#include <cos/gen/range.h>
#include <cos/gen/relop.h>
#include <cos/gen/sequence.h>
#include <cos/utest.h>

#include "tests.h"

static BOOL
eq(struct Slice *s, struct Slice *ref)
{
  return Slice_isEqual(s, ref);
}

static BOOL
isEq(OBJ s, OBJ ref)
{
  OBJ res = gisEqual(s, ref);
  grelease(s);
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
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,1,1), 0), atSlice(-1,3,1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,1,2), 0), atSlice(-1,2,2)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,5,3), 0), atSlice(-1,3,3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,4,3), 0), atSlice(-1,2,3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange( 1,5,3), 0), atSlice( 1,2,3)) );

    UTEST( eq(Slice_fromRange(atSlice(0), atRange(9,0,-1), 0), atSlice(9,10,-1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(9,1,-2), 0), atSlice(9,5,-2)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(9,0,-3), 0), atSlice(9,4,-3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(9,3,-3), 0), atSlice(9,3,-3)) );

    UTEST( eq(Slice_fromRange(atSlice(0), atRange(0,9,1) , 0), atSlice(0,10,1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(1,10,1), 0), atSlice(1,10,1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(1,9,2) , 0), atSlice(1,5,2)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(1,10,3), 0), atSlice(1,4,3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(1,7,3) , 0), atSlice(1,3,3)) );

    UTEST( eq(Slice_fromRange(atSlice(0), atRange(9,0,-1) , 0), atSlice(9,10,-1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(10,1,-1), 0), atSlice(10,10,-1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(10,2,-2), 0), atSlice(10,5,-2)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(10,1,-3), 0), atSlice(10,4,-3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(9,3,-3) , 0), atSlice(9,3,-3)) );

    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,-10,-1), 0), atSlice(-1,10,-1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,-9,-2) , 0), atSlice(-1,5,-2)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,-10,-3), 0), atSlice(-1,4,-3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-1,-7,-3) , 0), atSlice(-1,3,-3)) );

    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-10,-1,1), 0), atSlice(-10,10,1)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-10,-2,2), 0), atSlice(-10,5,2)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-10,-1,3), 0), atSlice(-10,4,3)) );
    UTEST( eq(Slice_fromRange(atSlice(0), atRange(-9,-3,3) , 0), atSlice(-9,3,3)) );

  UTEST_END
}


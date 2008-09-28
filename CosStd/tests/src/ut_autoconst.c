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
 | $Id: ut_autoconst.c,v 1.1 2008/09/28 22:12:30 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Index.h>
#include <cos/Range.h>
#include <cos/Slice.h>
#include <cos/Number.h>
#include <cos/Vector.h>
#include <cos/signal.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <string.h>

#include "utest.h"
#include "tests.h"

static BOOL
idx_chk(I32 n, OBJ idx)
{
  BOOL res = YES;
  I32 i = 0;

  switch(n) {
   case 1:
     for (; i < n; i++)
       res = res && ((struct Index1*)idx)->index    == i+1;

   case 2:
     for (; i < n; i++)
       res = res && ((struct Index2*)idx)->index[i] == i+1;

   case 3:
     for (; i < n; i++)
       res = res && ((struct Index3*)idx)->index[i] == i+1;

   case 4:
     for (; i < n; i++)
       res = res && ((struct Index4*)idx)->index[i] == i+1;

   case 5:
     for (; i < n; i++)
       res = res && ((struct Index5*)idx)->index[i] == i+1;
  }  

  return res;
}

static BOOL
rng_chk(I32 n, OBJ rng)
{
  BOOL res = YES;
  I32 i = 0;

  switch(n) {
   case 1:
     for (; i < n; i++)
       res = res && ((struct Range1*)rng)->start    == i+1
                 && ((struct Range1*)rng)->size     == (U32)(n-i);

   case 2:
     for (; i < n; i++)
       res = res && ((struct Range2*)rng)->start[i] == i+1
                 && ((struct Range2*)rng)->size [i] == (U32)(n-i);

   case 3:
     for (; i < n; i++)
       res = res && ((struct Range3*)rng)->start[i] == i+1
                 && ((struct Range3*)rng)->size [i] == (U32)(n-i);

   case 4:
     for (; i < n; i++)
       res = res && ((struct Range4*)rng)->start[i] == i+1
                 && ((struct Range4*)rng)->size [i] == (U32)(n-i);

   case 5:
     for (; i < n; i++)
       res = res && ((struct Range5*)rng)->start[i] == i+1
                 && ((struct Range5*)rng)->size [i] == (U32)(n-i);
  }  

  return res;
}

static BOOL
slc_chk(I32 n, OBJ slc)
{
  BOOL res = ((struct Slice1*)slc)->start == n;
  I32 i = 0;

  switch(n) {
   case 1:
     for (; i < n; i++)
       res = res && ((struct Slice1*)slc)->size    == (U32)(i+1)
                 && ((struct Slice1*)slc)->stride  == n-i;

   case 2:
     for (; i < n; i++)
       res = res && ((struct Slice2*)slc)->size  [i] == (U32)(i+1)
                 && ((struct Slice2*)slc)->stride[i] == n-i;

   case 3:
     for (; i < n; i++)
       res = res && ((struct Slice3*)slc)->size  [i] == (U32)(i+1)
                 && ((struct Slice3*)slc)->stride[i] == n-i;

   case 4:
     for (; i < n; i++)
       res = res && ((struct Slice4*)slc)->size  [i] == (U32)(i+1)
                 && ((struct Slice4*)slc)->stride[i] == n-i;

   case 5:
     for (; i < n; i++)
       res = res && ((struct Slice5*)slc)->size  [i] == (U32)(i+1)
                 && ((struct Slice5*)slc)->stride[i] == n-i;
  }  

  return res;
}

static BOOL
obj_chk(OBJ obj)
{
  OBJ cpy = gclone(obj);
  OBJ res = gequal(obj, cpy);

  test_assert( res == True || res == False );

  return grelease(cpy) == Nil && res == True;
}

void
ut_autoconst(void)
{
  OBJ _chr  = aChr('a');
  OBJ _sht  = aSht(1);
  OBJ _i    = aInt(2);
  OBJ _lng  = aLng(3);
  OBJ _dbl  = aDbl(4);
  OBJ _cpx  = aCpx(5);
  OBJ _cpx2 = aCpx(6,7);

#define ref(T,a) struct T *a = (struct T*)_##a 
  ref(Char   ,chr );
  ref(Short  ,sht );
  ref(Int    ,i   );
  ref(Long   ,lng );
  ref(Double ,dbl );
  ref(Complex,cpx );
  ref(Complex,cpx2);

#undef ref

  OBJ idx1 = aIndex(1);
  OBJ idx2 = aIndex(1,2);
  OBJ idx3 = aIndex(1,2,3);
  OBJ idx4 = aIndex(1,2,3,4);
  OBJ idx5 = aIndex(1,2,3,4,5);

  OBJ rng1 = aRange( 1,           1 );
  OBJ rng2 = aRange((1,2),       (2,1));
  OBJ rng3 = aRange((1,2,3),     (3,2,1));
  OBJ rng4 = aRange((1,2,3,4),   (4,3,2,1));
  OBJ rng5 = aRange((1,2,3,4,5), (5,4,3,2,1));

  OBJ slc1 = aSlice(1,  1,           1 );
  OBJ slc2 = aSlice(2, (1,2),       (2,1));
  OBJ slc3 = aSlice(3, (1,2,3),     (3,2,1));
  OBJ slc4 = aSlice(4, (1,2,3,4),   (4,3,2,1));
  OBJ slc5 = aSlice(5, (1,2,3,4,5), (5,4,3,2,1));

  COMPLEX cpx_ref = *(DOUBLE[]){6,7};

  UTEST_START("automatic objects")

    UTEST( chr->Int.value == 'a' );
    UTEST( sht->Int.value ==  1  );
    UTEST( i  ->    value ==  2  );
    UTEST( lng->    value ==  3  );
    UTEST( dbl_equal(dbl->value,4) );
    UTEST( cpx_equal(cpx->value,5) );
    UTEST( cpx_equal(cpx2->value,cpx_ref) );

    UTEST( idx_chk(1, idx1) );
    UTEST( idx_chk(2, idx2) );
    UTEST( idx_chk(3, idx3) );
    UTEST( idx_chk(4, idx4) );
    UTEST( idx_chk(5, idx5) );

    UTEST( rng_chk(1, rng1) );
    UTEST( rng_chk(2, rng2) );
    UTEST( rng_chk(3, rng3) );
    UTEST( rng_chk(4, rng4) );
    UTEST( rng_chk(5, rng5) );

    UTEST( slc_chk(1, slc1) );
    UTEST( slc_chk(2, slc2) );
    UTEST( slc_chk(3, slc3) );
    UTEST( slc_chk(4, slc4) );
    UTEST( slc_chk(5, slc5) );

    UTEST( obj_chk(_chr) );
    UTEST( obj_chk(_sht) );
    UTEST( obj_chk(_i  ) );
    UTEST( obj_chk(_lng) );
    UTEST( obj_chk(_dbl) );
    UTEST( obj_chk(_cpx) );
    UTEST( obj_chk(_cpx2) );

    UTEST( obj_chk(idx1) );
    UTEST( obj_chk(idx2) );
    UTEST( obj_chk(idx3) );
    UTEST( obj_chk(idx4) );
    UTEST( obj_chk(idx5) );

    UTEST( obj_chk(rng1) );
    UTEST( obj_chk(rng2) );
    UTEST( obj_chk(rng3) );
    UTEST( obj_chk(rng4) );
    UTEST( obj_chk(rng5) );

    UTEST( obj_chk(slc1) );
    UTEST( obj_chk(slc2) );
    UTEST( obj_chk(slc3) );
    UTEST( obj_chk(slc4) );
    UTEST( obj_chk(slc5) );

  UTEST_END
}

void
ut_autovector(void)
{
  OBJ intv1 = aIntVec(1);
  OBJ intv2 = aIntVec(1,2);
  OBJ intv3 = aIntVec(1,2,3);
  OBJ intv4 = aIntVec(1,2,3,4);
  OBJ intv5 = aIntVec(1,2,3,4,5);
  OBJ intv6 = aIntVec(1,2,3,4,5,6);
  OBJ intv7 = aIntVec(1,2,3,4,5,6,7);
  OBJ intv8 = aIntVec(1,2,3,4,5,6,7,8);
  OBJ intv9 = aIntVec(1,2,3,4,5,6,7,8,9);
  OBJ intvn = aIntVec(1,2,3,4,5,6,7,8,9,10);
  OBJ intvv = aIntSubVec(intvn, 4, 4);

  OBJ lngv1 = aLngVec(1);
  OBJ lngv2 = aLngVec(1,2);
  OBJ lngv3 = aLngVec(1,2,3);
  OBJ lngv4 = aLngVec(1,2,3,4);
  OBJ lngv5 = aLngVec(1,2,3,4,5);
  OBJ lngv6 = aLngVec(1,2,3,4,5,6);
  OBJ lngv7 = aLngVec(1,2,3,4,5,6,7);
  OBJ lngv8 = aLngVec(1,2,3,4,5,6,7,8);
  OBJ lngv9 = aLngVec(1,2,3,4,5,6,7,8,9);
  OBJ lngvn = aLngVec(1,2,3,4,5,6,7,8,9,10);
  OBJ lngvv = aLngSubVec(lngvn, 4, 4);

  OBJ dblv1 = aDblVec(1);
  OBJ dblv2 = aDblVec(1,2);
  OBJ dblv3 = aDblVec(1,2,3);
  OBJ dblv4 = aDblVec(1,2,3,4);
  OBJ dblv5 = aDblVec(1,2,3,4,5);
  OBJ dblv6 = aDblVec(1,2,3,4,5,6);
  OBJ dblv7 = aDblVec(1,2,3,4,5,6,7);
  OBJ dblv8 = aDblVec(1,2,3,4,5,6,7,8);
  OBJ dblv9 = aDblVec(1,2,3,4,5,6,7,8,9);
  OBJ dblvn = aDblVec(1,2,3,4,5,6,7,8,9,10);
  OBJ dblvv = aDblSubVec(dblvn, 4, 4);

  OBJ cpxv1 = aCpxVec(1);
  OBJ cpxv2 = aCpxVec(1,2);
  OBJ cpxv3 = aCpxVec(1,2,3);
  OBJ cpxv4 = aCpxVec(1,2,3,4);
  OBJ cpxv5 = aCpxVec(1,2,3,4,5);
  OBJ cpxv6 = aCpxVec(1,2,3,4,5,6);
  OBJ cpxv7 = aCpxVec(1,2,3,4,5,6,7);
  OBJ cpxv8 = aCpxVec(1,2,3,4,5,6,7,8);
  OBJ cpxv9 = aCpxVec(1,2,3,4,5,6,7,8,9);
  OBJ cpxvn = aCpxVec(1,2,3,4,5,6,7,8,9,10);
  OBJ cpxvv = aCpxSubVec(cpxvn, 4, 4);

  UTEST_START("automatic vectors")

    UTEST( obj_chk(intv1) );
    UTEST( obj_chk(intv2) );
    UTEST( obj_chk(intv3) );
    UTEST( obj_chk(intv4) );
    UTEST( obj_chk(intv5) );
    UTEST( obj_chk(intv6) );
    UTEST( obj_chk(intv7) );
    UTEST( obj_chk(intv8) );
    UTEST( obj_chk(intv9) );
    UTEST( obj_chk(intvn) );
    UTEST( obj_chk(intvv) );

    UTEST( obj_chk(lngv1) );
    UTEST( obj_chk(lngv2) );
    UTEST( obj_chk(lngv3) );
    UTEST( obj_chk(lngv4) );
    UTEST( obj_chk(lngv5) );
    UTEST( obj_chk(lngv6) );
    UTEST( obj_chk(lngv7) );
    UTEST( obj_chk(lngv8) );
    UTEST( obj_chk(lngv9) );
    UTEST( obj_chk(lngvn) );
    UTEST( obj_chk(lngvv) );

    UTEST( obj_chk(dblv1) );
    UTEST( obj_chk(dblv2) );
    UTEST( obj_chk(dblv3) );
    UTEST( obj_chk(dblv4) );
    UTEST( obj_chk(dblv5) );
    UTEST( obj_chk(dblv6) );
    UTEST( obj_chk(dblv7) );
    UTEST( obj_chk(dblv8) );
    UTEST( obj_chk(dblv9) );
    UTEST( obj_chk(dblvn) );
    UTEST( obj_chk(dblvv) );

    UTEST( obj_chk(cpxv1) );
    UTEST( obj_chk(cpxv2) );
    UTEST( obj_chk(cpxv3) );
    UTEST( obj_chk(cpxv4) );
    UTEST( obj_chk(cpxv5) );
    UTEST( obj_chk(cpxv6) );
    UTEST( obj_chk(cpxv7) );
    UTEST( obj_chk(cpxv8) );
    UTEST( obj_chk(cpxv9) );
    UTEST( obj_chk(cpxvn) );
    UTEST( obj_chk(cpxvv) );

  UTEST_END
}


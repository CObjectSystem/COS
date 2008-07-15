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
 | $Id: ut_autoconst.c,v 1.2 2008/07/15 10:07:07 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/Index.h>
#include <cos/Range.h>
#include <cos/Slice.h>
#include <cos/signal.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <string.h>

#include "utest.h"
#include "tests.h"
#include "generics.h"

static BOOL
idx_chk(U32 n, OBJ idx)
{
  BOOL res = YES;
  U32 i = 0;

  switch(n) {
   case 1:
     for (; i < n; i++)
       res = res && ((struct Index1*)idx)->idx    == i+1;

   case 2:
     for (; i < n; i++)
       res = res && ((struct Index2*)idx)->idx[i] == i+1;

   case 3:
     for (; i < n; i++)
       res = res && ((struct Index3*)idx)->idx[i] == i+1;

   case 4:
     for (; i < n; i++)
       res = res && ((struct Index4*)idx)->idx[i] == i+1;

   case 5:
     for (; i < n; i++)
       res = res && ((struct Index5*)idx)->idx[i] == i+1;
  }  

  return res;
}

static BOOL
rng_chk(U32 n, OBJ rng)
{
  BOOL res = YES;
  U32 i = 0;

  switch(n) {
   case 1:
     for (; i < n; i++)
       res = res && ((struct Range1*)rng)->start    == i+1
                 && ((struct Range1*)rng)->size     == n-i;

   case 2:
     for (; i < n; i++)
       res = res && ((struct Range2*)rng)->start[i] == i+1
                 && ((struct Range2*)rng)->size [i] == n-i;

   case 3:
     for (; i < n; i++)
       res = res && ((struct Range3*)rng)->start[i] == i+1
                 && ((struct Range3*)rng)->size [i] == n-i;

   case 4:
     for (; i < n; i++)
       res = res && ((struct Range4*)rng)->start[i] == i+1
                 && ((struct Range4*)rng)->size [i] == n-i;

   case 5:
     for (; i < n; i++)
       res = res && ((struct Range5*)rng)->start[i] == i+1
                 && ((struct Range5*)rng)->size [i] == n-i;
  }  

  return res;
}

static BOOL
slc_chk(U32 n, OBJ slc)
{
  BOOL res = ((struct Slice1*)slc)->start == n;
  U32 i = 0;

  switch(n) {
   case 1:
     for (; i < n; i++)
       res = res && ((struct Slice1*)slc)->size    == i+1
                 && ((struct Slice1*)slc)->stride  == n-i;

   case 2:
     for (; i < n; i++)
       res = res && ((struct Slice2*)slc)->size  [i] == i+1
                 && ((struct Slice2*)slc)->stride[i] == n-i;

   case 3:
     for (; i < n; i++)
       res = res && ((struct Slice3*)slc)->size  [i] == i+1
                 && ((struct Slice3*)slc)->stride[i] == n-i;

   case 4:
     for (; i < n; i++)
       res = res && ((struct Slice4*)slc)->size  [i] == i+1
                 && ((struct Slice4*)slc)->stride[i] == n-i;

   case 5:
     for (; i < n; i++)
       res = res && ((struct Slice5*)slc)->size  [i] == i+1
                 && ((struct Slice5*)slc)->stride[i] == n-i;
  }  

  return res;
}

static BOOL
obj_chk(OBJ obj)
{
  OBJ cpy = gclone(obj);
  OBJ res = gequal(obj, cpy);

  TestAssert( res == True || res == False );

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

  OBJ _uchr = aUChr('b');
  OBJ _usht = aUSht(10);
  OBJ _uint = aUInt(11);
  OBJ _ulng = aULng(12);

#define ref(T,a) struct T *a = (struct T*)_##a 
  ref(Char   ,chr );
  ref(Short  ,sht );
  ref(Int    ,i   );
  ref(Long   ,lng );
  ref(Double ,dbl );
  ref(Complex,cpx );
  ref(Complex,cpx2);

  ref(UChar  ,uchr);
  ref(UShort ,usht);
  ref(UInt   ,uint);
  ref(ULong  ,ulng);
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

  COMPLEX cpx_ref = *(double[]){6,7};

  UTEST_START("automatic objects")

    UTEST( chr->Int.val == 'a' );
    UTEST( sht->Int.val ==  1  );
    UTEST( i  ->    val ==  2  );
    UTEST( lng->    val ==  3  );
    UTEST( dbl_equal(dbl->val,4) );
    UTEST( cpx_equal(cpx->val,5) );
    UTEST( cpx_equal(cpx2->val,cpx_ref) );

    UTEST( uchr->UInt.val == 'b' );
    UTEST( usht->UInt.val == 10  );
    UTEST( uint->     val == 11  );
    UTEST( ulng->     val == 12  );

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
    UTEST( obj_chk(_uchr) );
    UTEST( obj_chk(_usht) );
    UTEST( obj_chk(_uint) );
    UTEST( obj_chk(_ulng) );

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

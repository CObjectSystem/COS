/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - autorelease
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
 | $Id: ut_autorealease.c,v 1.1 2008/06/27 16:17:19 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/signal.h>

#include <string.h>

#include "utest.h"
#include "tests.h"
#include "generics.h"

void
ut_autorelease(void)
{
  useclass(A, AutoRelease);
  OBJ a, c;
  OBJ ar;
  volatile size_t i;
  volatile OBJ ar1, ar2, ar3;
  static OBJ arr[1000];
  
  UTEST_START("reference counting & autorelease")

    // ----
    a = gnew(A);
    c = gclone(a);
    UTEST( gretainCount(a) == 1 );
    UTEST( gretainCount(c) == 1 );
    UTEST( grelease(a) == Nil   );
    UTEST( grelease(c) == Nil   );

    // ----
    a = gretain(gnew(A));
    UTEST( gretainCount(a) == 2  );
    UTEST( grelease(a) == a      );
    UTEST( grelease(a) == Nil    );

    // ----
    ar = gnew(AutoRelease);
    a = gretain(gnew(A));
    gautoRelease(a);
    UTEST( gretainCount(a) == 2  );
    grelease(ar);
    UTEST( gretainCount(a) == 1  );
    UTEST( grelease(a) == Nil    );

    // ----
    ar = gnew(AutoRelease);
    for (i = 1; i <= 100000; i++) {
      size_t s;
      gautoRelease(gnew(A));
      s = gsize(ar);
      if (!(s & (s-1))) // check every 2^n
        UTEST( s == i );
    }
    grelease(ar);

    // ----
    ar = gnew(AutoRelease);
    ar1 = ar2 = ar3 = NIL;
    TRY
      ar1 = gnew(AutoRelease);
      for (i = 0; i < 100; i++)
        arr[i] = gretain(gautoRelease(gnew(A)));
      TRY
        ar2 = gnew(AutoRelease);
        for (; i < 300; i++)
          arr[i] = gretain(gautoRelease(gnew(A)));
        TRY
          ar3 = gnew(AutoRelease);
          for (; i < 600; i++)
            arr[i] = gretain(gautoRelease(gnew(A)));
          THROW(Nil);
        FINALLY()
          UTEST( gsize(ar3) == 300 ), ar3 = NIL;
        ENDTRY // rethrow Nil
      FINALLY()
        UTEST( gsize(ar2) == 200 ), ar2 = NIL;
      ENDTRY // rethrow Nil
    CATCH_ANY() // catch Nil
    FINALLY()
      UTEST( gsize(ar1) == 100 ), ar1 = NIL;
    ENDTRY
    UTEST( gsize(ar) == 0 );
    grelease(ar); // destroy all chained pools
    
    while (i-- > 0)
      if( gretainCount(arr[i]) != 1 || grelease(arr[i]) != Nil )
        break;
        
    UTEST( ++i == 0 );

  UTEST_END
}

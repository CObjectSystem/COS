/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - forward message
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
 | $Id: ut_forwardmessage.c,v 1.1 2008/06/27 16:17:24 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/logic.h>
#include <cos/gen/value.h>

#include "utest.h"
#include "tests.h"

#include <string.h>

static BOOL
check_fwd(OBJ cls, OBJ (*func)(OBJ), STR res)
{
  useclass(Proxy);
  
  OBJ _1  = gnew(cls);
  OBJ pxy = gnewWith(Proxy, _1);
  STR s   = gstr(_1);
  BOOL ret;

  grelease(_1);
  func(pxy);
  ret = !strcmp(s, res);
  grelease(pxy);
  
  return ret;
}

void
ut_forwardmessage(void)
{
  useclass(A,B,C,D,E);

  UTEST_START("forwarding message")

    UTEST( check_fwd(A, gbool,  "A does not understand gbool") );
    UTEST( check_fwd(A, gnot,   "A does not understand gnot")  );
    UTEST( check_fwd(A, gclass, "A")  );

    UTEST( check_fwd(B, gbool,  "B does not understand gbool") );
    UTEST( check_fwd(B, gnot,   "B does not understand gnot")  );
    UTEST( check_fwd(B, gclass, "B")  );

    UTEST( check_fwd(C, gbool,  "C does not understand gbool") );
    UTEST( check_fwd(C, gnot,   "C does not understand gnot")  );
    UTEST( check_fwd(C, gclass, "C")  );

    UTEST( check_fwd(D, gbool,  "D does not understand gbool") );
    UTEST( check_fwd(D, gnot,   "D does not understand gnot")  );
    UTEST( check_fwd(D, gclass, "D")  );

    UTEST( check_fwd(E, gbool,  "E does not understand gbool") );
    UTEST( check_fwd(E, gnot,   "E does not understand gnot")  );
    UTEST( check_fwd(E, gclass, "E")  );

  UTEST_END
}

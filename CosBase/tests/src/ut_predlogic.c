/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - class predicate logic
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
 | $Id: ut_predlogic.c,v 1.1 2008/06/27 16:17:24 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/logic.h>

#include "utest.h"
#include "tests.h"

void
ut_predlogic(void)
{
  useclass(TrueFalse);
  OBJ st[] = { TrueFalse, False, True };
  int i, j;

  UTEST_START("class predicate & logic")

    // gbool
    UTEST( gbool(TrueFalse) == TrueFalse );
    UTEST( gbool(False)     == False     );
    UTEST( gbool(True)      == True      );

    // gnot
    UTEST( gnot(TrueFalse) == TrueFalse );
    UTEST( gnot(False)     == True      );
    UTEST( gnot(True)      == False     );

    // gequal
    UTEST( gequal(TrueFalse, TrueFalse) == TrueFalse );
    UTEST( gequal(TrueFalse, False)     == TrueFalse );
    UTEST( gequal(False, TrueFalse)     == TrueFalse );
    UTEST( gequal(TrueFalse, True)      == TrueFalse );
    UTEST( gequal(True, TrueFalse)      == TrueFalse );
    UTEST( gequal(False, False)         == True      );
    UTEST( gequal(False, True)          == False     );
    UTEST( gequal(True, False)          == False     );
    UTEST( gequal(True, True)           == True      );

    // gand
    UTEST( gand(TrueFalse, TrueFalse) == TrueFalse );
    UTEST( gand(TrueFalse, False)     == False     );
    UTEST( gand(False, TrueFalse)     == False     );
    UTEST( gand(TrueFalse, True)      == TrueFalse );
    UTEST( gand(True, TrueFalse)      == TrueFalse );
    UTEST( gand(False, False)         == False     );
    UTEST( gand(False, True)          == False     );
    UTEST( gand(True, False)          == False     );
    UTEST( gand(True, True)           == True      );

    // gor
    UTEST( gor(TrueFalse, TrueFalse) == TrueFalse );
    UTEST( gor(TrueFalse, False)     == TrueFalse );
    UTEST( gor(False, TrueFalse)     == TrueFalse );
    UTEST( gor(TrueFalse, True)      == True      );
    UTEST( gor(True, TrueFalse)      == True      );
    UTEST( gor(False, False)         == False     );
    UTEST( gor(False, True)          == True      );
    UTEST( gor(True, False)          == True      );
    UTEST( gor(True, True)           == True      );
    
    // property: a == not not a
    for (i = 0; i < 3; i++)
      UTEST( st[i] == gnot(gnot(st[i])) );

    // property: not(a and b) == not a or not b
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      UTEST( gnot(gand(st[i],st[j])) == gor(gnot(st[i]),gnot(st[j])) );

    // property: not(a or b) == not a and not b
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      UTEST( gnot(gor(st[i],st[j])) == gand(gnot(st[i]),gnot(st[j])) );

    // property: a xor b == not(a equal b)
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      UTEST( gxor(st[i], st[j]) == gnot(gequal(st[i],st[j])) );

    // property: a implies b == not a or b
    for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      UTEST( gimplies(st[i],st[j]) == gor(gnot(st[i]),st[j]) );

  UTEST_END
}

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - method invocation & knowledge
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
 | $Id: ut_methods.c,v 1.5 2009/04/17 21:13:56 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/message.h>
#include <cos/utest.h>

#include "tests.h"

void
ut_methods(void)
{
  useclass(Object, Class, MetaClass, PropMetaClass);

  usegeneric((gunderstandMessage1)gum1);
  usegeneric((ginstancesUnderstandMessage1)gium1);
  usegeneric(gclass , gclassName);
  usegeneric(gretain, grelease, gdelete );
  usegeneric(galloc , gdealloc  );
  usegeneric(gisKindOf);

  UTEST_START("method invocation & knowledge")

    // Object
    UTEST(          gunderstandMessage1(Object, (SEL)gum1)       == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gum1)       == True  );

    UTEST(          gunderstandMessage1(Object, (SEL)gium1)      == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gium1)      == False );

    UTEST(          gunderstandMessage1(Object, (SEL)galloc)     == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)galloc)     == False );

    UTEST(          gunderstandMessage1(Object, (SEL)gdealloc)   == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gdealloc)   == True  );

    UTEST(          gunderstandMessage1(Object, (SEL)gclass)     == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gclass)     == True  );

    UTEST(          gunderstandMessage1(Object, (SEL)gclassName) == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gclassName) == True  );
    
    UTEST(          gunderstandMessage1(Object, (SEL)gretain)    == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gretain)    == True  );

    UTEST(          gunderstandMessage1(Object, (SEL)grelease)   == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)grelease)   == True  );

    UTEST(          gunderstandMessage1(Object, (SEL)gdelete)    == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)gdelete)    == True  );

    UTEST(          gunderstandMessage2(Object, Object, (SEL)gisKindOf) == True  );
    UTEST( ginstancesUnderstandMessage2(Object, Object, (SEL)gisKindOf) == False );

    UTEST(          gunderstandMessage2(Object, Class, (SEL)gisKindOf)  == True  );
    UTEST( ginstancesUnderstandMessage2(Object, Class, (SEL)gisKindOf)  == True  );

    // Class
    UTEST(          gunderstandMessage1(Class, (SEL)galloc)     == True );
    UTEST( ginstancesUnderstandMessage1(Class, (SEL)gdealloc)   == True );

    UTEST(          gunderstandMessage1(Class, (SEL)gclass)     == True );
    UTEST( ginstancesUnderstandMessage1(Class, (SEL)gclassName) == True );
    
    UTEST(          gunderstandMessage1(Class, (SEL)gretain)    == True );
    UTEST( ginstancesUnderstandMessage1(Class, (SEL)grelease)   == True );
    UTEST( ginstancesUnderstandMessage1(Class, (SEL)gdelete)    == True );

    // MetaClass
    UTEST(          gunderstandMessage1(MetaClass, (SEL)galloc)     == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)gdealloc)   == True );

    UTEST(          gunderstandMessage1(MetaClass, (SEL)gclass)     == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)gclassName) == True );
    
    UTEST(          gunderstandMessage1(MetaClass, (SEL)gretain)    == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)grelease)   == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)gdelete)    == True );

    // PropMetaClass
    UTEST(          gunderstandMessage1(PropMetaClass, (SEL)galloc)     == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)gdealloc)   == True );

    UTEST(          gunderstandMessage1(PropMetaClass, (SEL)gclass)     == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)gclassName) == True );
    
    UTEST(          gunderstandMessage1(PropMetaClass, (SEL)gretain)    == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)grelease)   == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)gdelete)    == True );
    
  UTEST_END
}

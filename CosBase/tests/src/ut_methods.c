/**
 * C Object System
 * COS testsuites - method invocation & knowledge
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
  usegeneric(gretain, grelease);
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

    UTEST(          gunderstandMessage1(Object, (SEL)grelease)    == True  );
    UTEST( ginstancesUnderstandMessage1(Object, (SEL)grelease)    == True  );

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
    UTEST( ginstancesUnderstandMessage1(Class, (SEL)grelease)    == True );

    // MetaClass
    UTEST(          gunderstandMessage1(MetaClass, (SEL)galloc)     == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)gdealloc)   == True );

    UTEST(          gunderstandMessage1(MetaClass, (SEL)gclass)     == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)gclassName) == True );
    
    UTEST(          gunderstandMessage1(MetaClass, (SEL)gretain)    == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)grelease)   == True );
    UTEST( ginstancesUnderstandMessage1(MetaClass, (SEL)grelease)    == True );

    // PropMetaClass
    UTEST(          gunderstandMessage1(PropMetaClass, (SEL)galloc)     == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)gdealloc)   == True );

    UTEST(          gunderstandMessage1(PropMetaClass, (SEL)gclass)     == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)gclassName) == True );
    
    UTEST(          gunderstandMessage1(PropMetaClass, (SEL)gretain)    == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)grelease)   == True );
    UTEST( ginstancesUnderstandMessage1(PropMetaClass, (SEL)grelease)    == True );
    
  UTEST_END
}

/**
 * C Object System
 * COS testsuites - class definition & inheritance
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
#include <cos/gen/object.h>
#include <cos/utest.h>

#include "tests.h"

void
ut_classes(void)
{
  useclass(Object  , Class  , MetaClass  , PropMetaClass  );
  useclass(mObject , mClass , mMetaClass , mPropMetaClass );
  useclass(pmObject, pmClass, pmMetaClass, pmPropMetaClass);
  useclass(Behavior, mBehavior, pmBehavior);
  useclass(Generic, mGeneric);
  useclass(Proxy);

  UTEST_START("class definition & inheritance")
  
    // root classes
    UTEST( gisKindOf(Object, Proxy)     == False );
    UTEST( gisKindOf(Object, Nil)       == False );

    UTEST( gisKindOf(Nil, Object)       == True  );
    UTEST( gisKindOf(Nil, Proxy)        == False );

    UTEST( gisKindOf(Proxy, Object)     == True  );
    UTEST( gisKindOf(Proxy, Nil)        == False );

    // Object
    UTEST( gisKindOf(Object, Object)          == True  );
    UTEST( gisKindOf(Object, mObject)         == True  );
    UTEST( gisKindOf(Object, pmObject)        == True  );
    UTEST( gisKindOf(Object, Class )          == True  );
    UTEST( gisKindOf(Object, mClass )         == False );
    UTEST( gisKindOf(Object, pmClass )        == False );
    UTEST( gisKindOf(Object, MetaClass)       == False );
    UTEST( gisKindOf(Object, mMetaClass)      == False );
    UTEST( gisKindOf(Object, pmMetaClass)     == False );
    UTEST( gisKindOf(Object, PropMetaClass)   == False );
    UTEST( gisKindOf(Object, mPropMetaClass)  == False );
    UTEST( gisKindOf(Object, pmPropMetaClass) == False );

    UTEST( gisKindOf(mObject, Object)          == True  );
    UTEST( gisKindOf(mObject, mObject)         == False );
    UTEST( gisKindOf(mObject, pmObject)        == False );
    UTEST( gisKindOf(mObject, Class )          == True  );
    UTEST( gisKindOf(mObject, mClass )         == False );
    UTEST( gisKindOf(mObject, pmClass )        == False );
    UTEST( gisKindOf(mObject, MetaClass)       == True  );
    UTEST( gisKindOf(mObject, mMetaClass)      == False );
    UTEST( gisKindOf(mObject, pmMetaClass)     == False );
    UTEST( gisKindOf(mObject, PropMetaClass)   == False );
    UTEST( gisKindOf(mObject, mPropMetaClass)  == False );
    UTEST( gisKindOf(mObject, pmPropMetaClass) == False );

    UTEST( gisKindOf(pmObject, Object)          == True  );
    UTEST( gisKindOf(pmObject, mObject)         == False );
    UTEST( gisKindOf(pmObject, pmObject)        == False );
    UTEST( gisKindOf(pmObject, Class )          == True  );
    UTEST( gisKindOf(pmObject, mClass )         == False );
    UTEST( gisKindOf(pmObject, pmClass )        == False );
    UTEST( gisKindOf(pmObject, MetaClass)       == True  );
    UTEST( gisKindOf(pmObject, mMetaClass)      == False );
    UTEST( gisKindOf(pmObject, pmMetaClass)     == False );
    UTEST( gisKindOf(pmObject, PropMetaClass)   == True  );
    UTEST( gisKindOf(pmObject, mPropMetaClass)  == False );
    UTEST( gisKindOf(pmObject, pmPropMetaClass) == False );

    // Class
    UTEST( gisKindOf(Class, Object)          == True  );
    UTEST( gisKindOf(Class, mObject)         == True  );
    UTEST( gisKindOf(Class, pmObject)        == False );
    UTEST( gisKindOf(Class, Class )          == True  );
    UTEST( gisKindOf(Class, mClass )         == True  );
    UTEST( gisKindOf(Class, pmClass )        == True  );
    UTEST( gisKindOf(Class, MetaClass)       == False );
    UTEST( gisKindOf(Class, mMetaClass)      == False );
    UTEST( gisKindOf(Class, pmMetaClass)     == False );
    UTEST( gisKindOf(Class, PropMetaClass)   == False );
    UTEST( gisKindOf(Class, mPropMetaClass)  == False );
    UTEST( gisKindOf(Class, pmPropMetaClass) == False );

    UTEST( gisKindOf(mClass, Object)          == True  );
    UTEST( gisKindOf(mClass, mObject)         == False );
    UTEST( gisKindOf(mClass, pmObject)        == False );
    UTEST( gisKindOf(mClass, Class )          == True  );
    UTEST( gisKindOf(mClass, mClass )         == False );
    UTEST( gisKindOf(mClass, pmClass )        == False );
    UTEST( gisKindOf(mClass, MetaClass)       == True  );
    UTEST( gisKindOf(mClass, mMetaClass)      == False );
    UTEST( gisKindOf(mClass, pmMetaClass)     == False );
    UTEST( gisKindOf(mClass, PropMetaClass)   == False );
    UTEST( gisKindOf(mClass, mPropMetaClass)  == False );
    UTEST( gisKindOf(mClass, pmPropMetaClass) == False );

    UTEST( gisKindOf(pmClass, Object)          == True  );
    UTEST( gisKindOf(pmClass, mObject)         == False );
    UTEST( gisKindOf(pmClass, pmObject)        == False );
    UTEST( gisKindOf(pmClass, Class )          == True  );
    UTEST( gisKindOf(pmClass, mClass )         == False );
    UTEST( gisKindOf(pmClass, pmClass )        == False );
    UTEST( gisKindOf(pmClass, MetaClass)       == True  );
    UTEST( gisKindOf(pmClass, mMetaClass)      == False );
    UTEST( gisKindOf(pmClass, pmMetaClass)     == False );
    UTEST( gisKindOf(pmClass, PropMetaClass)   == True  );
    UTEST( gisKindOf(pmClass, mPropMetaClass)  == False );
    UTEST( gisKindOf(pmClass, pmPropMetaClass) == False );

    // MetaClass
    UTEST( gisKindOf(MetaClass, Class )        == True  );
    UTEST( gisKindOf(MetaClass, MetaClass)     == False );
    UTEST( gisKindOf(MetaClass, PropMetaClass) == False );
    UTEST( gisKindOf(MetaClass, mMetaClass)    == True  );
    UTEST( gisKindOf(MetaClass, pmMetaClass)   == True  );
  
    UTEST( gisKindOf(mMetaClass, Class )        == True  );
    UTEST( gisKindOf(mMetaClass, MetaClass)     == True  );
    UTEST( gisKindOf(mMetaClass, PropMetaClass) == False );
    UTEST( gisKindOf(mMetaClass, mMetaClass)    == False );
    UTEST( gisKindOf(mMetaClass, pmMetaClass)   == False );

    UTEST( gisKindOf(pmMetaClass, Class )        == True  );
    UTEST( gisKindOf(pmMetaClass, MetaClass)     == True  );
    UTEST( gisKindOf(pmMetaClass, PropMetaClass) == True  );
    UTEST( gisKindOf(pmMetaClass, mMetaClass)    == False );
    UTEST( gisKindOf(pmMetaClass, pmMetaClass)   == False );

    // PropMetaClass 
    UTEST( gisKindOf(PropMetaClass, Class )          == True  );
    UTEST( gisKindOf(PropMetaClass, MetaClass)       == False );
    UTEST( gisKindOf(PropMetaClass, PropMetaClass)   == False );
    UTEST( gisKindOf(PropMetaClass, mPropMetaClass)  == True  );
    UTEST( gisKindOf(PropMetaClass, pmPropMetaClass) == True  );
  
    UTEST( gisKindOf(mPropMetaClass, Class )          == True  );
    UTEST( gisKindOf(mPropMetaClass, MetaClass)       == True  );
    UTEST( gisKindOf(mPropMetaClass, PropMetaClass)   == False );
    UTEST( gisKindOf(mPropMetaClass, mPropMetaClass)  == False );
    UTEST( gisKindOf(mPropMetaClass, pmPropMetaClass) == False );

    UTEST( gisKindOf(pmPropMetaClass, Class )          == True  );
    UTEST( gisKindOf(pmPropMetaClass, MetaClass)       == True  );
    UTEST( gisKindOf(pmPropMetaClass, PropMetaClass)   == True  );
    UTEST( gisKindOf(pmPropMetaClass, mPropMetaClass)  == False );
    UTEST( gisKindOf(pmPropMetaClass, pmPropMetaClass) == False );

    // Behavior
    UTEST( gisKindOf(Behavior, mObject)    == True  );
    UTEST( gisKindOf(Behavior, mClass)     == False );
    UTEST( gisKindOf(Behavior, mGeneric)   == False );
  
    UTEST( gisKindOf(Object,   mBehavior)  == False );
    UTEST( gisKindOf(Class,    mBehavior)  == True  );
    UTEST( gisKindOf(Generic,  mBehavior)  == True  );
    UTEST( gisKindOf(Behavior, mBehavior)  == True  );
  
    UTEST( gisKindOf(Object,   pmBehavior) == False );
    UTEST( gisKindOf(Class,    pmBehavior) == False );
    UTEST( gisKindOf(Generic,  pmBehavior) == False );
    UTEST( gisKindOf(Behavior, pmBehavior) == True  );

  UTEST_END
}

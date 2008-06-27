/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - class definition & inheritance
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
 | $Id: ut_classes.c,v 1.1 2008/06/27 16:17:19 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>

#include "utest.h"
#include "tests.h"

void
ut_classes(void)
{
  useclass(Any  , Object  , Class  , MetaClass  , PropMetaClass  );
  useclass(mAny , mObject , mClass , mMetaClass , mPropMetaClass );
  useclass(pmAny, pmObject, pmClass, pmMetaClass, pmPropMetaClass);
  useclass(Behavior, mBehavior, pmBehavior);
  useclass(Generic, mGeneric);
  useclass(Proxy);

  UTEST_START("class definition & inheritance")
  
    // root classes
    UTEST( gisKindOf(Any, Proxy)        == False );
    UTEST( gisKindOf(Any, Nil)          == False );

    UTEST( gisKindOf(Object, Proxy)     == False );
    UTEST( gisKindOf(Object, Nil)       == False );

    UTEST( gisKindOf(Proxy, Object)     == True  );
    UTEST( gisKindOf(Proxy, Nil)        == False );

    UTEST( gisKindOf(Nil, Object)       == True  );
    UTEST( gisKindOf(Nil, Proxy)        == False );

    // Any
    UTEST( gisKindOf(Any, Any)             == True  );
    UTEST( gisKindOf(Any, mAny)            == True  );
    UTEST( gisKindOf(Any, pmAny)           == True  );  
    UTEST( gisKindOf(Any, Object)          == True  );
    UTEST( gisKindOf(Any, mObject)         == False );
    UTEST( gisKindOf(Any, pmObject)        == False );
    UTEST( gisKindOf(Any, Class )          == True  );
    UTEST( gisKindOf(Any, mClass )         == False );
    UTEST( gisKindOf(Any, pmClass )        == False );
    UTEST( gisKindOf(Any, MetaClass)       == False );
    UTEST( gisKindOf(Any, mMetaClass)      == False );
    UTEST( gisKindOf(Any, pmMetaClass)     == False );
    UTEST( gisKindOf(Any, PropMetaClass)   == False );
    UTEST( gisKindOf(Any, mPropMetaClass)  == False );
    UTEST( gisKindOf(Any, pmPropMetaClass) == False );

    UTEST( gisKindOf(mAny, Any)             == True  );
    UTEST( gisKindOf(mAny, mAny)            == False );
    UTEST( gisKindOf(mAny, pmAny)           == False );
    UTEST( gisKindOf(mAny, Object)          == True  );
    UTEST( gisKindOf(mAny, mObject)         == False );
    UTEST( gisKindOf(mAny, pmObject)        == False );
    UTEST( gisKindOf(mAny, Class )          == True  );
    UTEST( gisKindOf(mAny, mClass )         == False );
    UTEST( gisKindOf(mAny, pmClass )        == False );
    UTEST( gisKindOf(mAny, MetaClass)       == True  );
    UTEST( gisKindOf(mAny, mMetaClass)      == False );
    UTEST( gisKindOf(mAny, pmMetaClass)     == False );
    UTEST( gisKindOf(mAny, PropMetaClass)   == False );
    UTEST( gisKindOf(mAny, mPropMetaClass)  == False );
    UTEST( gisKindOf(mAny, pmPropMetaClass) == False );

    UTEST( gisKindOf(pmAny, Any)             == True  );
    UTEST( gisKindOf(pmAny, mAny)            == False );
    UTEST( gisKindOf(pmAny, pmAny)           == False );
    UTEST( gisKindOf(pmAny, Object)          == True  );
    UTEST( gisKindOf(pmAny, mObject)         == False );
    UTEST( gisKindOf(pmAny, pmObject)        == False );
    UTEST( gisKindOf(pmAny, Class )          == True  );
    UTEST( gisKindOf(pmAny, mClass )         == False );
    UTEST( gisKindOf(pmAny, pmClass )        == False );
    UTEST( gisKindOf(pmAny, MetaClass)       == True  );
    UTEST( gisKindOf(pmAny, mMetaClass)      == False );
    UTEST( gisKindOf(pmAny, pmMetaClass)     == False );
    UTEST( gisKindOf(pmAny, PropMetaClass)   == True  );
    UTEST( gisKindOf(pmAny, mPropMetaClass)  == False );
    UTEST( gisKindOf(pmAny, pmPropMetaClass) == False );

    // Object
    UTEST( gisKindOf(Object, Any)             == True  );
    UTEST( gisKindOf(Object, mAny)            == True  );
    UTEST( gisKindOf(Object, pmAny)           == False );  
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

    UTEST( gisKindOf(mObject, Any)             == True  );
    UTEST( gisKindOf(mObject, mAny)            == False );
    UTEST( gisKindOf(mObject, pmAny)           == False );
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

    UTEST( gisKindOf(pmObject, Any)             == True  );
    UTEST( gisKindOf(pmObject, mAny)            == False );
    UTEST( gisKindOf(pmObject, pmAny)           == False );
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
    UTEST( gisKindOf(Class, Any)             == True  );
    UTEST( gisKindOf(Class, mAny)            == True  );
    UTEST( gisKindOf(Class, pmAny)           == False );  
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

    UTEST( gisKindOf(mClass, Any)             == True  );
    UTEST( gisKindOf(mClass, mAny)            == False );
    UTEST( gisKindOf(mClass, pmAny)           == False );
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

    UTEST( gisKindOf(pmClass, Any)             == True  );
    UTEST( gisKindOf(pmClass, mAny)            == False );
    UTEST( gisKindOf(pmClass, pmAny)           == False );
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

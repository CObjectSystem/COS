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
#include <cos/prp/object.h>
#include <cos/gen/object.h>
#include <cos/utest.h>

#include "tests.h"

static BOOL
chk_prop(OBJ prp, STR str)
{
  return prp == (OBJ)cos_property_getWithStr(str);
}

static BOOL
chk_prop_class(OBJ cls)
{
  useproperty(class);
  return ggetAt(cls, class) == gclass(cls);
}

static BOOL
chk_prop_superClass(OBJ cls)
{
  useproperty(superClass);
  return ggetAt(cls, superClass) == gsuperClass(cls);
}

void
ut_properties(void)
{
  useproperty(class, superClass);
  useproperty((class)cls, (superClass)spr); // check local renaming syntax

  useclass(Object, Class, MetaClass, PropMetaClass);
  useclass(A,B,C,D,E);

  UTEST_START("properties definition & use")
  
    UTEST( class      == cls );
    UTEST( superClass == spr );

    UTEST( chk_prop(class      , "class"      ) );
    UTEST( chk_prop(superClass , "superClass" ) );

    UTEST( chk_prop_class(Object) );
    UTEST( chk_prop_class(Class) );
    UTEST( chk_prop_class(MetaClass) );
    UTEST( chk_prop_class(PropMetaClass) );
    
    UTEST( chk_prop_class(A) );
    UTEST( chk_prop_class(B) );
    UTEST( chk_prop_class(C) );
    UTEST( chk_prop_class(D) );
    UTEST( chk_prop_class(E) );

    UTEST( chk_prop_superClass(Object) );
    UTEST( chk_prop_superClass(Class) );
    UTEST( chk_prop_superClass(MetaClass) );
    UTEST( chk_prop_superClass(PropMetaClass) );
    
    UTEST( chk_prop_superClass(A) );
    UTEST( chk_prop_superClass(B) );
    UTEST( chk_prop_superClass(C) );
    UTEST( chk_prop_superClass(D) );
    UTEST( chk_prop_superClass(E) );

  UTEST_END
}

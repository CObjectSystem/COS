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
 | $Id: ut_properties.c,v 1.3 2009/02/03 14:40:48 ldeniau Exp $
 |
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
  useproperty(class, name, size, superClass, error, signal);
  useproperty((class)cls,(size)sz,(superClass)spr); // check local renaming syntax

  useclass(Object,Class,MetaClass,PropMetaClass);
  useclass(A,B,C,D,E);

  UTEST_START("properties definition & use")
  
    UTEST( class == cls );
    UTEST( size == sz );
    UTEST( superClass == spr );

    UTEST( chk_prop(class, "class") );
    UTEST( chk_prop(error, "error") );
    UTEST( chk_prop(name, "name") );
    UTEST( chk_prop(signal, "signal") );
    UTEST( chk_prop(size, "size") );
    UTEST( chk_prop(superClass, "superClass") );

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

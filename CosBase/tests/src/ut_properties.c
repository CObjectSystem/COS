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
 | $Id: ut_properties.c,v 1.1 2009/01/26 15:19:35 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/prp/object.h>
#include <cos/gen/object.h>

#include "utest.h"
#include "tests.h"

void
ut_properties(void)
{
  useproperty((class)cls, name, size, superClass);
  
  UTEST_START("properties definition & use")
  
    UTEST( (OBJ)cos_property_getWithStr("class")      == cls        );
    UTEST( (OBJ)cos_property_getWithStr("name")       == name       );
    UTEST( (OBJ)cos_property_getWithStr("size")       == size       );
    UTEST( (OBJ)cos_property_getWithStr("superClass") == superClass );

  UTEST_END
}

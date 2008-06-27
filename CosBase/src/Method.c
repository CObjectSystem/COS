/*
 o---------------------------------------------------------------------o
 |
 | COS Method
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Method.c,v 1.1 2008/06/27 16:17:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Method.h>

// ----- 

makclass(Method ,Object);
makclass(Method1,Method);
makclass(Method2,Method);
makclass(Method3,Method);
makclass(Method4,Method);
makclass(Method5,Method);

// ----- 

STATIC_ASSERT(Method1_vs_Method2__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method1,Method2,fct)
           && COS_FIELD_COMPATIBILITY(Method1,Method2,cls[0]) );

STATIC_ASSERT(Method2_vs_Method3__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method2,Method3,fct)
           && COS_FIELD_COMPATIBILITY(Method2,Method3,cls[0])
           && COS_FIELD_COMPATIBILITY(Method2,Method3,cls[1]) );

STATIC_ASSERT(Method3_vs_Method4__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method3,Method4,fct)
           && COS_FIELD_COMPATIBILITY(Method3,Method4,cls[0])
           && COS_FIELD_COMPATIBILITY(Method3,Method4,cls[1])
           && COS_FIELD_COMPATIBILITY(Method3,Method4,cls[2]) );

STATIC_ASSERT(Method4_vs_Method5__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(Method4,Method5,fct)
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[0])
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[1])
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[2])
           && COS_FIELD_COMPATIBILITY(Method4,Method5,cls[3]) );

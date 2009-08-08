#ifndef COS_ORDERED_H
#define COS_ORDERED_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Ordered
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
 | $Id: Ordered.h,v 1.6 2009/08/08 16:36:09 ldeniau Exp $
 |
*/

#include <cos/Predicate.h>

defclass(Ordered, Predicate)             endclass
defclass(Equal  , Ordered  ) FINAL_CLASS endclass
defclass(Lesser , Ordered  ) FINAL_CLASS endclass
defclass(Greater, Ordered  ) FINAL_CLASS endclass

#endif // COS_ORDERED_H

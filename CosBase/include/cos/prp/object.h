#ifndef COS_PRP_OBJECT_H
#define COS_PRP_OBJECT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS properties for objects
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
 | $Id: object.h,v 1.1 2009/01/26 15:18:49 ldeniau Exp $
 |
*/

#include <cos/Property.h>

// object and class properties
defproperty(class     );
defproperty(error     );
defproperty(name      );
defproperty(signal    );
defproperty(size      );
defproperty(superClass);

#endif // COS_PRP_OBJECT_H

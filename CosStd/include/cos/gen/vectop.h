#ifndef COS_GEN_VECTOP_H
#define COS_GEN_VECTOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generic for (extra) vector operators
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
 | $Id: vectop.h,v 1.3 2010/01/03 12:28:56 ldeniau Exp $
 |
*/

#include <cos/GVectOp.h>

defgeneric(OBJ, (GSum   ) gsum , _1);
defgeneric(OBJ, (GProd  ) gprod, _1);

defgeneric(OBJ, (GMean  ) gmean  , _1);
defgeneric(OBJ, (GStdDev) gstddev, _1);

#endif // COS_GEN_VECTOP_H

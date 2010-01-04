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
 | $Id: vectop.h,v 1.6 2010/01/04 09:59:01 ldeniau Exp $
 |
*/

#include <cos/gen/op/GVectOp.h>

defgeneric(OBJ, (G_sum ) gsum , _1);
defgeneric(OBJ, (G_prod) gprod, _1);

#endif // COS_GEN_VECTOP_H

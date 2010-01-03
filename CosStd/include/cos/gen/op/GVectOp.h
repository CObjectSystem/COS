#ifndef COS_GEN_OP_GVECTOP_H
#define COS_GEN_OP_GVECTOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for vector operators
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
 | $Id: GVectOp.h,v 1.3 2010/01/03 14:54:33 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(GSum , GUnaryOp) endclass
defclass(GProd, GUnaryOp) endclass

#endif // COS_GEN_OP_GVECTOP_H

#ifndef COS_GEN_OP_GFLOATOP_H
#define COS_GEN_OP_GFLOATOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for float operators
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
 | $Id: GFloatOp.h,v 1.3 2010/01/03 14:54:33 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

defclass(GConj       , GUnaryOp  ) endclass
defclass(GArg        , GUnaryOp  ) endclass
defclass(GExp        , GUnaryOp  ) endclass
defclass(GLog        , GUnaryOp  ) endclass
defclass(GSqrt       , GUnaryOp  ) endclass
defclass(GCos        , GUnaryOp  ) endclass
defclass(GSin        , GUnaryOp  ) endclass
defclass(GTan        , GUnaryOp  ) endclass
defclass(GACos       , GUnaryOp  ) endclass
defclass(GASin       , GUnaryOp  ) endclass
defclass(GATan       , GUnaryOp  ) endclass
defclass(GCosH       , GUnaryOp  ) endclass
defclass(GSinH       , GUnaryOp  ) endclass
defclass(GTanH       , GUnaryOp  ) endclass
defclass(GACosH      , GUnaryOp  ) endclass
defclass(GASinH      , GUnaryOp  ) endclass
defclass(GATanH      , GUnaryOp  ) endclass
defclass(GHypot      , GBinaryOp ) endclass
defclass(GSubSqr     , GBinaryOp ) endclass
defclass(GMulAdd     , GTernaryOp) endclass

defclass(GConjugate  , GUnaryOp  ) endclass
defclass(GArgument   , GUnaryOp  ) endclass
defclass(GExponential, GUnaryOp  ) endclass
defclass(GLogarithm  , GUnaryOp  ) endclass
defclass(GSqRoot     , GUnaryOp  ) endclass
defclass(GCosine     , GUnaryOp  ) endclass
defclass(GSine       , GUnaryOp  ) endclass
defclass(GTangent    , GUnaryOp  ) endclass
defclass(GACosine    , GUnaryOp  ) endclass
defclass(GASine      , GUnaryOp  ) endclass
defclass(GATangent   , GUnaryOp  ) endclass
defclass(GCosineH    , GUnaryOp  ) endclass
defclass(GSineH      , GUnaryOp  ) endclass
defclass(GTangentH   , GUnaryOp  ) endclass
defclass(GACosineH   , GUnaryOp  ) endclass
defclass(GASineH     , GUnaryOp  ) endclass
defclass(GATangentH  , GUnaryOp  ) endclass
defclass(GHypotenuse , GBinaryOp ) endclass

#endif // COS_GEN_OP_GFLOATOP_H

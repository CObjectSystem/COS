/*
 o---------------------------------------------------------------------o
 |
 | COS Generic
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
 | $Id: Generic.c,v 1.3 2010/01/03 14:54:33 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

makclass(GOperator , Generic  );
makclass(GUnaryOp  , GOperator);
makclass(GBinaryOp , GOperator);
makclass(GTernaryOp, GOperator);

#include <cos/gen/op/GNumOp.h>

makclass(GAbs      , GUnaryOp );
makclass(GNeg      , GUnaryOp );
makclass(GSqr      , GUnaryOp );
makclass(GInv      , GUnaryOp );
makclass(GAdd      , GBinaryOp);
makclass(GSub      , GBinaryOp);
makclass(GMul      , GBinaryOp);
makclass(GDiv      , GBinaryOp);
makclass(GPow      , GBinaryOp);
makclass(GMod      , GBinaryOp);

makclass(GAbsolute , GUnaryOp );
makclass(GNegate   , GUnaryOp );
makclass(GSquare   , GUnaryOp );
makclass(GInvert   , GUnaryOp );
makclass(GAddTo    , GBinaryOp);
makclass(GSubTo    , GBinaryOp);
makclass(GMulBy    , GBinaryOp);
makclass(GDivBy    , GBinaryOp);
makclass(GPower    , GBinaryOp);
makclass(GModulo   , GBinaryOp);

#include <cos/gen/op/GFloatOp.h>

makclass(GConj       , GUnaryOp  );
makclass(GArg        , GUnaryOp  );
makclass(GExp        , GUnaryOp  );
makclass(GLog        , GUnaryOp  );
makclass(GSqrt       , GUnaryOp  );
makclass(GCos        , GUnaryOp  );
makclass(GSin        , GUnaryOp  );
makclass(GTan        , GUnaryOp  );
makclass(GACos       , GUnaryOp  );
makclass(GASin       , GUnaryOp  );
makclass(GATan       , GUnaryOp  );
makclass(GCosH       , GUnaryOp  );
makclass(GSinH       , GUnaryOp  );
makclass(GTanH       , GUnaryOp  );
makclass(GACosH      , GUnaryOp  );
makclass(GASinH      , GUnaryOp  );
makclass(GATanH      , GUnaryOp  );
makclass(GHypot      , GBinaryOp );
makclass(GSubSqr     , GBinaryOp );
makclass(GMulAdd     , GTernaryOp);

makclass(GConjugate  , GUnaryOp  );
makclass(GArgument   , GUnaryOp  );
makclass(GExponential, GUnaryOp  );
makclass(GLogarithm  , GUnaryOp  );
makclass(GSqRoot     , GUnaryOp  );
makclass(GCosine     , GUnaryOp  );
makclass(GSine       , GUnaryOp  );
makclass(GTangent    , GUnaryOp  );
makclass(GACosine    , GUnaryOp  );
makclass(GASine      , GUnaryOp  );
makclass(GATangent   , GUnaryOp  );
makclass(GCosineH    , GUnaryOp  );
makclass(GSineH      , GUnaryOp  );
makclass(GTangentH   , GUnaryOp  );
makclass(GACosineH   , GUnaryOp  );
makclass(GASineH     , GUnaryOp  );
makclass(GATangentH  , GUnaryOp  );
makclass(GHypotenuse , GBinaryOp );

#include <cos/gen/op/GRelOp.h>

makclass(GCompare       , GBinaryOp);
makclass(GEqual         , GBinaryOp);
makclass(GNotEqual      , GBinaryOp);
makclass(GLesser        , GBinaryOp);
makclass(GLesserOrEqual , GBinaryOp);
makclass(GGreater       , GBinaryOp);
makclass(GGreaterOrEqual, GBinaryOp);
makclass(GMin           , GBinaryOp);
makclass(GMax           , GBinaryOp);
makclass(GHash          , GUnaryOp );

#include <cos/gen/op/GLogicOp.h>

makclass(GNot    , GUnaryOp );
makclass(GAnd    , GBinaryOp);
makclass(GOr     , GBinaryOp);
makclass(GXOr    , GBinaryOp);
makclass(GImplies, GBinaryOp);

#include <cos/gen/op/GVectOp.h>

makclass(GSum , GUnaryOp);
makclass(GProd, GUnaryOp);


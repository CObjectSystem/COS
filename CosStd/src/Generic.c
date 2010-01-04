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
 | $Id: Generic.c,v 1.4 2010/01/04 09:59:02 ldeniau Exp $
 |
*/

#include <cos/gen/op/GOperator.h>

makclass(GOperator , Generic  );
makclass(GUnaryOp  , GOperator);
makclass(GBinaryOp , GOperator);
makclass(GTernaryOp, GOperator);

#include <cos/gen/op/GNumOp.h>

makclass(G_abs      , GUnaryOp );
makclass(G_neg      , GUnaryOp );
makclass(G_sqr      , GUnaryOp );
makclass(G_inv      , GUnaryOp );
makclass(G_add      , GBinaryOp);
makclass(G_sub      , GBinaryOp);
makclass(G_mul      , GBinaryOp);
makclass(G_div      , GBinaryOp);
makclass(G_pow      , GBinaryOp);
makclass(G_mod      , GBinaryOp);

makclass(G_absolute , GUnaryOp );
makclass(G_negate   , GUnaryOp );
makclass(G_square   , GUnaryOp );
makclass(G_invert   , GUnaryOp );
makclass(G_addTo    , GBinaryOp);
makclass(G_subTo    , GBinaryOp);
makclass(G_mulBy    , GBinaryOp);
makclass(G_divBy    , GBinaryOp);
makclass(G_power    , GBinaryOp);
makclass(G_modulo   , GBinaryOp);

#include <cos/gen/op/GFloatOp.h>

makclass(G_conj       , GUnaryOp  );
makclass(G_arg        , GUnaryOp  );
makclass(G_exp        , GUnaryOp  );
makclass(G_log        , GUnaryOp  );
makclass(G_sqrt       , GUnaryOp  );
makclass(G_cos        , GUnaryOp  );
makclass(G_sin        , GUnaryOp  );
makclass(G_tan        , GUnaryOp  );
makclass(G_acos       , GUnaryOp  );
makclass(G_asin       , GUnaryOp  );
makclass(G_atan       , GUnaryOp  );
makclass(G_cosh       , GUnaryOp  );
makclass(G_sinh       , GUnaryOp  );
makclass(G_tanh       , GUnaryOp  );
makclass(G_acosh      , GUnaryOp  );
makclass(G_asinh      , GUnaryOp  );
makclass(G_atanh      , GUnaryOp  );
makclass(G_hypot      , GBinaryOp );
makclass(G_subSqr     , GBinaryOp );
makclass(G_mulAdd     , GTernaryOp);

makclass(G_conjugate  , GUnaryOp  );
makclass(G_argument   , GUnaryOp  );
makclass(G_exponential, GUnaryOp  );
makclass(G_logarithm  , GUnaryOp  );
makclass(G_sqroot     , GUnaryOp  );
makclass(G_cosine     , GUnaryOp  );
makclass(G_sine       , GUnaryOp  );
makclass(G_tangent    , GUnaryOp  );
makclass(G_acosine    , GUnaryOp  );
makclass(G_asine      , GUnaryOp  );
makclass(G_atangent   , GUnaryOp  );
makclass(G_cosineh    , GUnaryOp  );
makclass(G_sineh      , GUnaryOp  );
makclass(G_tangenth   , GUnaryOp  );
makclass(G_acosineh   , GUnaryOp  );
makclass(G_asineh     , GUnaryOp  );
makclass(G_atangenth  , GUnaryOp  );
makclass(G_hypotenuse , GBinaryOp );

#include <cos/gen/op/GRelOp.h>

makclass(G_compare         , GBinaryOp);
makclass(G_isEqual         , GBinaryOp);
makclass(G_isNotEqual      , GBinaryOp);
makclass(G_isLesser        , GBinaryOp);
makclass(G_isLesserOrEqual , GBinaryOp);
makclass(G_isGreater       , GBinaryOp);
makclass(G_isGreaterOrEqual, GBinaryOp);
makclass(G_min             , GBinaryOp);
makclass(G_max             , GBinaryOp);
makclass(G_hash            , GUnaryOp );

#include <cos/gen/op/GLogicOp.h>

makclass(G_not    , GUnaryOp );
makclass(G_and    , GBinaryOp);
makclass(G_or     , GBinaryOp);
makclass(G_xor    , GBinaryOp);
makclass(G_implies, GBinaryOp);

#include <cos/gen/op/GVectOp.h>

makclass(G_sum , GUnaryOp);
makclass(G_prod, GUnaryOp);


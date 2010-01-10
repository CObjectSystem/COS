/*
 o---------------------------------------------------------------------o
 |
 | COS Functor
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
 | $Id: Functor.c,v 1.23 2010/01/10 13:13:31 ldeniau Exp $
 |
*/

/* NOTE-INFO: PlaceHolder specializations

   PlaceHolders should only override Object's methods, no more,
   since High Order Messages are commonly built with delegation.
*/
 
#include <cos/Functor.h>

#include "Functor.h"

// ----- class cluster root classes

makclass(Expression);

makclass(Functor    , Expression);
makclass(PlaceHolder, Expression);

// ----- placeholder

makclass(FunArg     , PlaceHolder);
makclass(FunVar     , PlaceHolder);
makclass(FunLzy     , PlaceHolder);

// ----- functor expression

makclass(FunExpr , Functor);
makclass(FunExpr1, FunExpr);
makclass(FunExpr2, FunExpr);
makclass(FunExpr3, FunExpr);
makclass(FunExpr4, FunExpr);
makclass(FunExpr5, FunExpr);
makclass(FunExpr6, FunExpr);
makclass(FunExpr7, FunExpr);
makclass(FunExpr8, FunExpr);
makclass(FunExpr9, FunExpr);

// ----- method expression

makclass(MthExpr , Functor);
makclass(MthExpr1, MthExpr);
makclass(MthExpr2, MthExpr);
makclass(MthExpr3, MthExpr);
makclass(MthExpr4, MthExpr);
makclass(MthExpr5, MthExpr);

// ----- function (lightweight optimization)

makclass(Function0, FunExpr);
makclass(Function1, FunExpr);
makclass(Function2, FunExpr);
makclass(Function3, FunExpr);
makclass(Function4, FunExpr);
makclass(Function5, FunExpr);
makclass(Function6, FunExpr);
makclass(Function7, FunExpr);
makclass(Function8, FunExpr);
makclass(Function9, FunExpr);

// ----- message (lightweight optimization)

makclass(Message1, MthExpr);
makclass(Message2, MthExpr);
makclass(Message3, MthExpr);
makclass(Message4, MthExpr);
makclass(Message5, MthExpr);

// ----- partially evaluated functor built by FunExpr_init (Functor_fun.h)

makclass(PFunExpr1, FunExpr1);
makclass(PFunExpr2, FunExpr2);
makclass(PFunExpr3, FunExpr3);
makclass(PFunExpr4, FunExpr4);
makclass(PFunExpr5, FunExpr5);

// ----- partially evaluated method built by MthExpr_init (Functor_mth.h)

makclass(PMthExpr1, MthExpr1);
makclass(PMthExpr2, MthExpr2);
makclass(PMthExpr3, MthExpr3);
makclass(PMthExpr4, MthExpr4);
makclass(PMthExpr5, MthExpr5);

// ----- optimized SFunExprs built by FunExpr_init

makclass(SFunExpr1, FunExpr1);
makclass(SFunExpr2, FunExpr2);
makclass(SFunExpr3, FunExpr3);
makclass(SFunExpr4, FunExpr4);

// ----- optimized SMthExprs built by MthExpr_init

makclass(SMthExpr1, MthExpr1);
makclass(SMthExpr2, MthExpr2);
makclass(SMthExpr3, MthExpr3);
makclass(SMthExpr4, MthExpr4);

// ----- more SFunExprs specializations for eval

makclass(SFunExpr21, SFunExpr2);
makclass(SFunExpr22, SFunExpr2);
makclass(SFunExpr23, SFunExpr2);
makclass(SFunExpr31, SFunExpr3);
makclass(SFunExpr32, SFunExpr3);
makclass(SFunExpr33, SFunExpr3);
makclass(SFunExpr34, SFunExpr3);
makclass(SFunExpr35, SFunExpr3);
makclass(SFunExpr36, SFunExpr3);
makclass(SFunExpr37, SFunExpr3);
makclass(SFunExpr41, SFunExpr4);
makclass(SFunExpr42, SFunExpr4);
makclass(SFunExpr43, SFunExpr4);
makclass(SFunExpr44, SFunExpr4);
makclass(SFunExpr45, SFunExpr4);
makclass(SFunExpr46, SFunExpr4);
makclass(SFunExpr47, SFunExpr4);
makclass(SFunExpr48, SFunExpr4);
makclass(SFunExpr49, SFunExpr4);
makclass(SFunExpr4A, SFunExpr4);
makclass(SFunExpr4B, SFunExpr4);
makclass(SFunExpr4C, SFunExpr4);
makclass(SFunExpr4D, SFunExpr4);
makclass(SFunExpr4E, SFunExpr4);
makclass(SFunExpr4F, SFunExpr4);

// ----- more SMthExprs specialization for eval

makclass(SMthExpr21, SMthExpr2);
makclass(SMthExpr22, SMthExpr2);
makclass(SMthExpr23, SMthExpr2);
makclass(SMthExpr31, SMthExpr3);
makclass(SMthExpr32, SMthExpr3);
makclass(SMthExpr33, SMthExpr3);
makclass(SMthExpr34, SMthExpr3);
makclass(SMthExpr35, SMthExpr3);
makclass(SMthExpr36, SMthExpr3);
makclass(SMthExpr37, SMthExpr3);
makclass(SMthExpr41, SMthExpr4);
makclass(SMthExpr42, SMthExpr4);
makclass(SMthExpr43, SMthExpr4);
makclass(SMthExpr44, SMthExpr4);
makclass(SMthExpr45, SMthExpr4);
makclass(SMthExpr46, SMthExpr4);
makclass(SMthExpr47, SMthExpr4);
makclass(SMthExpr48, SMthExpr4);
makclass(SMthExpr49, SMthExpr4);
makclass(SMthExpr4A, SMthExpr4);
makclass(SMthExpr4B, SMthExpr4);
makclass(SMthExpr4C, SMthExpr4);
makclass(SMthExpr4D, SMthExpr4);
makclass(SMthExpr4E, SMthExpr4);
makclass(SMthExpr4F, SMthExpr4);


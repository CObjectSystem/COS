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
 | $Id: Functor.c,v 1.27 2010/06/13 20:24:46 ldeniau Exp $
 |
*/

/* NOTE-INFO: PlaceHolder specializations

   PlaceHolders should only override Object's methods, no more,
   since High Order Messages are commonly built with delegation.
*/

#include <cos/Functor.h>

#include <cos/gen/object.h>

// ----- allocator

defmethod(OBJ, galloc, pmFunctor) // lazy alloc
  retmethod(_1);
endmethod

// ----- class cluster root classes

makclass(Functor    , Any);
makclass(VarExpr, Functor);
makclass(FunExpr, Functor);
makclass(MsgExpr, Functor);

// ----- functor operator (iterate, compose)

makclass(IterateFun, Functor);
makclass(ComposeFun, Functor);

// ------------------------------------------------------------
// ----- variable expression

makclass(FunArg , VarExpr);

// ------------------------------------------------------------
// ----- functor expression

makclass(FunExpr0, FunExpr);
makclass(FunExpr1, FunExpr);
makclass(FunExpr2, FunExpr);
makclass(FunExpr3, FunExpr);
makclass(FunExpr4, FunExpr);
makclass(FunExpr5, FunExpr);
makclass(FunExpr6, FunExpr);
makclass(FunExpr7, FunExpr);
makclass(FunExpr8, FunExpr);
makclass(FunExpr9, FunExpr);

// ----- specializations

makclass(FunExpr11, FunExpr1);
makclass(FunExpr12, FunExpr1);

makclass(FunExpr21, FunExpr2);
makclass(FunExpr22, FunExpr2);
makclass(FunExpr23, FunExpr2);
makclass(FunExpr24, FunExpr2);

makclass(FunExpr31, FunExpr3);
makclass(FunExpr32, FunExpr3);
makclass(FunExpr33, FunExpr3);
makclass(FunExpr34, FunExpr3);
makclass(FunExpr35, FunExpr3);
makclass(FunExpr36, FunExpr3);
makclass(FunExpr37, FunExpr3);
makclass(FunExpr38, FunExpr3);


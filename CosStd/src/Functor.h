#ifndef FUNCTOR_H
#define FUNCTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Functor - (private) classes
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
 | $Id: Functor.h,v 1.1 2010/01/10 13:14:19 ldeniau Exp $
 |
*/

// ----- method expression

defclass(MthExpr1, MthExpr)
  char *arg;    // arguments
  OBJ   rcv[1]; // receivers
  U16   off[8]; // arguments OBJects offsets
  U8    idx[8]; // arguments OBJects indexes
  U8    pos[1]; // receivers indexes as OBJects 
  U8    noff;   // number of arguments offsets
  U8    nexp;   // number of arguments expressions
endclass

defclass(MthExpr2, MthExpr)
  char *arg;
  OBJ   rcv[2];
  U16   off[7];
  U8    idx[7];
  U8    pos[2];
  U8    noff;
  U8    nexp;
endclass

defclass(MthExpr3, MthExpr)
  char *arg;
  OBJ   rcv[3];
  U16   off[6];
  U8    idx[6];
  U8    pos[3];
  U8    noff;
  U8    nexp;
endclass

defclass(MthExpr4, MthExpr)
  char *arg;
  OBJ   rcv[4];
  U16   off[5];
  U8    idx[5];
  U8    pos[4];
  U8    noff;
  U8    nexp;
endclass

defclass(MthExpr5, MthExpr)
  char *arg;
  OBJ   rcv[5];
  U16   off[4];
  U8    idx[4];
  U8    pos[5];
  U8    noff;
  U8    nexp;
endclass

// ----- partially evaluated functor built by FunExpr_init (Functor_fun.h)

defclass(PFunExpr1, FunExpr1) endclass
defclass(PFunExpr2, FunExpr2) endclass
defclass(PFunExpr3, FunExpr3) endclass
defclass(PFunExpr4, FunExpr4) endclass
defclass(PFunExpr5, FunExpr5) endclass

// ----- partially evaluated method built by MthExpr_init (Functor_mth.h)

defclass(PMthExpr1, MthExpr1) endclass
defclass(PMthExpr2, MthExpr2) endclass
defclass(PMthExpr3, MthExpr3) endclass
defclass(PMthExpr4, MthExpr4) endclass
defclass(PMthExpr5, MthExpr5) endclass

// ----- optimized SFunExprs built by FunExpr_init

defclass(SFunExpr1, FunExpr1) endclass
defclass(SFunExpr2, FunExpr2) endclass
defclass(SFunExpr3, FunExpr3) endclass
defclass(SFunExpr4, FunExpr4) endclass

// ----- optimized SMthExprs built by MthExpr_init

defclass(SMthExpr1, MthExpr1) endclass
defclass(SMthExpr2, MthExpr2) endclass
defclass(SMthExpr3, MthExpr3) endclass
defclass(SMthExpr4, MthExpr4) endclass

// ----- more SFunExprs specializations for eval

defclass(SFunExpr21, SFunExpr2) endclass
defclass(SFunExpr22, SFunExpr2) endclass
defclass(SFunExpr23, SFunExpr2) endclass
defclass(SFunExpr31, SFunExpr3) endclass
defclass(SFunExpr32, SFunExpr3) endclass
defclass(SFunExpr33, SFunExpr3) endclass
defclass(SFunExpr34, SFunExpr3) endclass
defclass(SFunExpr35, SFunExpr3) endclass
defclass(SFunExpr36, SFunExpr3) endclass
defclass(SFunExpr37, SFunExpr3) endclass
defclass(SFunExpr41, SFunExpr4) endclass
defclass(SFunExpr42, SFunExpr4) endclass
defclass(SFunExpr43, SFunExpr4) endclass
defclass(SFunExpr44, SFunExpr4) endclass
defclass(SFunExpr45, SFunExpr4) endclass
defclass(SFunExpr46, SFunExpr4) endclass
defclass(SFunExpr47, SFunExpr4) endclass
defclass(SFunExpr48, SFunExpr4) endclass
defclass(SFunExpr49, SFunExpr4) endclass
defclass(SFunExpr4A, SFunExpr4) endclass
defclass(SFunExpr4B, SFunExpr4) endclass
defclass(SFunExpr4C, SFunExpr4) endclass
defclass(SFunExpr4D, SFunExpr4) endclass
defclass(SFunExpr4E, SFunExpr4) endclass
defclass(SFunExpr4F, SFunExpr4) endclass

// ----- more SMthExprs specialization for eval

defclass(SMthExpr21, SMthExpr2) endclass
defclass(SMthExpr22, SMthExpr2) endclass
defclass(SMthExpr23, SMthExpr2) endclass
defclass(SMthExpr31, SMthExpr3) endclass
defclass(SMthExpr32, SMthExpr3) endclass
defclass(SMthExpr33, SMthExpr3) endclass
defclass(SMthExpr34, SMthExpr3) endclass
defclass(SMthExpr35, SMthExpr3) endclass
defclass(SMthExpr36, SMthExpr3) endclass
defclass(SMthExpr37, SMthExpr3) endclass
defclass(SMthExpr41, SMthExpr4) endclass
defclass(SMthExpr42, SMthExpr4) endclass
defclass(SMthExpr43, SMthExpr4) endclass
defclass(SMthExpr44, SMthExpr4) endclass
defclass(SMthExpr45, SMthExpr4) endclass
defclass(SMthExpr46, SMthExpr4) endclass
defclass(SMthExpr47, SMthExpr4) endclass
defclass(SMthExpr48, SMthExpr4) endclass
defclass(SMthExpr49, SMthExpr4) endclass
defclass(SMthExpr4A, SMthExpr4) endclass
defclass(SMthExpr4B, SMthExpr4) endclass
defclass(SMthExpr4C, SMthExpr4) endclass
defclass(SMthExpr4D, SMthExpr4) endclass
defclass(SMthExpr4E, SMthExpr4) endclass
defclass(SMthExpr4F, SMthExpr4) endclass

#endif // FUNCTOR_H

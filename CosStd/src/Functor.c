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
 | $Id: Functor.c,v 1.17 2009/12/28 00:18:54 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

makclass(Functor);

makclass(VarExpr, Functor);
makclass(FunExpr, Functor);
makclass(MthExpr, Functor);
makclass(LazyFun, Functor);

makclass(Argument, VarExpr);
makclass(Variable, VarExpr);

// ----- generics

defmethod(OBJ, gdeinit, FunExpr)
  retmethod(_1);
endmethod

defmethod(STR, gstr, FunExpr)
  retmethod(self->str);
endmethod


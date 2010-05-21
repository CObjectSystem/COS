/*
 o---------------------------------------------------------------------o
 |
 | COS Functor placeholder (index, variable, lazy)
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
 | $Id: Functor_var.c,v 1.7 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

/* NOTE-INFO: PlaceHolder specializations

   PlaceHolders should only override Object's methods, no more,
   since High Order Messages are commonly built with delegation.
*/
 
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>

#include "Functor_utl.h"

// -----

useclass(FunArg, FunVar, FunLzy);

// ----- ctors (for gautoRelease)

defmethod(OBJ, gclone, FunArg)
  OBJ _arg = galloc(FunArg);
  struct FunArg *arg = chkcast(FunArg, _arg);

  arg->idx = self->idx;
  
  retmethod(_arg);
endmethod

defmethod(OBJ, gclone, FunVar)
  OBJ _var = galloc(FunVar);
  struct FunVar *var = chkcast(FunVar, _var);

  var->var = gretain(self->var);

  retmethod(_var);
endmethod

defmethod(OBJ, gclone, FunLzy)
  OBJ _lzy = galloc(FunLzy);
  struct FunLzy *lzy = chkcast(FunLzy, _lzy);

  lzy->fun = gretain(self->fun);
  lzy->cnt = self->cnt;

  retmethod(_lzy);
endmethod

// ----- dtors

defmethod(OBJ, gdeinit, FunArg)
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, FunVar)
  grelease(self->var);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, FunLzy)
  grelease(self->fun);
  retmethod(_1);
endmethod

// ----- eval

defmethod(OBJ, gevalEnv, PlaceHolder, Collection)
  test_assert(0, "invalid placeholder evaluation (geval)");
  retmethod(Nil);
endmethod

defmethod(OBJ, gevalEnv, FunLzy, Collection)
  retmethod ( self->cnt == 1 ? self->fun :
              gautoDelete(aFunLzyN(self->cnt-1, self->fun)) );
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Closure)
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
 | $Id: Functor_clo.c,v 1.4 2010/01/07 14:53:52 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

#include "Functor_utl.h"

// ----- closure: optimized functors built by FunExpr_init

defclass(Functor1, FunExpr1) endclass
defclass(Functor2, FunExpr2) endclass
defclass(Functor3, FunExpr3) endclass
defclass(Functor4, FunExpr4) endclass

// -----

makclass(Functor1, FunExpr1);
makclass(Functor2, FunExpr2);
makclass(Functor3, FunExpr3);
makclass(Functor4, FunExpr4);

// ----- more specialization for eval

defclass(Functor21, Functor2) endclass
defclass(Functor22, Functor2) endclass
defclass(Functor23, Functor2) endclass
defclass(Functor31, Functor3) endclass
defclass(Functor32, Functor3) endclass
defclass(Functor33, Functor3) endclass
defclass(Functor34, Functor3) endclass
defclass(Functor35, Functor3) endclass
defclass(Functor36, Functor3) endclass
defclass(Functor37, Functor3) endclass
defclass(Functor41, Functor4) endclass
defclass(Functor42, Functor4) endclass
defclass(Functor43, Functor4) endclass
defclass(Functor44, Functor4) endclass
defclass(Functor45, Functor4) endclass
defclass(Functor46, Functor4) endclass
defclass(Functor47, Functor4) endclass
defclass(Functor48, Functor4) endclass
defclass(Functor49, Functor4) endclass
defclass(Functor4A, Functor4) endclass
defclass(Functor4B, Functor4) endclass
defclass(Functor4C, Functor4) endclass
defclass(Functor4D, Functor4) endclass
defclass(Functor4E, Functor4) endclass
defclass(Functor4F, Functor4) endclass

// -----

makclass(Functor21, Functor2);
makclass(Functor22, Functor2);
makclass(Functor23, Functor2);
makclass(Functor31, Functor3);
makclass(Functor32, Functor3);
makclass(Functor33, Functor3);
makclass(Functor34, Functor3);
makclass(Functor35, Functor3);
makclass(Functor36, Functor3);
makclass(Functor37, Functor3);
makclass(Functor41, Functor4);
makclass(Functor42, Functor4);
makclass(Functor43, Functor4);
makclass(Functor44, Functor4);
makclass(Functor45, Functor4);
makclass(Functor46, Functor4);
makclass(Functor47, Functor4);
makclass(Functor48, Functor4);
makclass(Functor49, Functor4);
makclass(Functor4A, Functor4);
makclass(Functor4B, Functor4);
makclass(Functor4C, Functor4);
makclass(Functor4D, Functor4);
makclass(Functor4E, Functor4);
makclass(Functor4F, Functor4);

// ---- eval

// ----- 1

defmethod(OBJ, gevalEnv, Functor1, Array)
  OBJ *arg = self->FunExpr1.arg;
  FUN1 fct = self->FunExpr1.fct;

  retmethod( fct(arg[0]) );
endmethod

// ----- 2

defmethod(OBJ, gevalEnv, Functor2, Array)
  U32 *id = &self->FunExpr2.FunExpr.Functor.Expression.Object.id;

  switch(self->FunExpr2.FunExpr.Functor.msk) {
    case 011: *id = cos_class_id(classref(Functor21)); break;
    case 012: *id = cos_class_id(classref(Functor22)); break;
    case 021: *id = cos_class_id(classref(Functor23)); break;
    default : test_assert(0, "invalid Functor2 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, Functor21, Array)
  OBJ *arg = self->Functor2.FunExpr2.arg;
  FUN2 fct = self->Functor2.FunExpr2.fct;

  retmethod( fct(arg[0], arg[1]) ); // 011
endmethod

defmethod(OBJ, gevalEnv, Functor22, Array)
  OBJ *arg = self->Functor2.FunExpr2.arg;
  FUN2 fct = self->Functor2.FunExpr2.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1]) ); // 012
endmethod

defmethod(OBJ, gevalEnv, Functor23, Array)
  OBJ *arg = self->Functor2.FunExpr2.arg;
  FUN2 fct = self->Functor2.FunExpr2.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0]) ); // 021
endmethod

// ----- 3

defmethod(OBJ, gevalEnv, Functor3, Array)
  U32 *id = &self->FunExpr3.FunExpr.Functor.Expression.Object.id;

  switch(self->FunExpr3.FunExpr.Functor.msk) {
    case 0111: *id = cos_class_id(classref(Functor31)); break;
    case 0112: *id = cos_class_id(classref(Functor32)); break;
    case 0121: *id = cos_class_id(classref(Functor33)); break;
    case 0122: *id = cos_class_id(classref(Functor34)); break;
    case 0211: *id = cos_class_id(classref(Functor35)); break;
    case 0212: *id = cos_class_id(classref(Functor36)); break;
    case 0221: *id = cos_class_id(classref(Functor37)); break;
    default  : test_assert(0, "invalid Functor3 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, Functor31, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;

  retmethod( fct(arg[0], arg[1], arg[2]) ); // 0111
endmethod

defmethod(OBJ, gevalEnv, Functor32, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], arg[2]) ); // 0112
endmethod

defmethod(OBJ, gevalEnv, Functor33, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], arg[2]) ); // 0121
endmethod

defmethod(OBJ, gevalEnv, Functor34, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], arg[2]) ); // 0122
endmethod

defmethod(OBJ, gevalEnv, Functor35, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], var[0]) ); // 0211
endmethod

defmethod(OBJ, gevalEnv, Functor36, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], var[1]) ); // 0212
endmethod

defmethod(OBJ, gevalEnv, Functor37, Array)
  OBJ *arg = self->Functor3.FunExpr3.arg;
  FUN3 fct = self->Functor3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], var[1]) ); // 0221
endmethod

// ----- 4

defmethod(OBJ, gevalEnv, Functor4, Array)
  U32 *id = &self->FunExpr4.FunExpr.Functor.Expression.Object.id;

  switch(self->FunExpr4.FunExpr.Functor.msk) {
    case 01111: *id = cos_class_id(classref(Functor41)); break;
    case 01112: *id = cos_class_id(classref(Functor42)); break;
    case 01121: *id = cos_class_id(classref(Functor43)); break;
    case 01122: *id = cos_class_id(classref(Functor44)); break;
    case 01211: *id = cos_class_id(classref(Functor45)); break;
    case 01212: *id = cos_class_id(classref(Functor46)); break;
    case 01221: *id = cos_class_id(classref(Functor47)); break;
    case 01222: *id = cos_class_id(classref(Functor48)); break;
    case 02111: *id = cos_class_id(classref(Functor49)); break;
    case 02112: *id = cos_class_id(classref(Functor4A)); break;
    case 02121: *id = cos_class_id(classref(Functor4B)); break;
    case 02122: *id = cos_class_id(classref(Functor4C)); break;
    case 02211: *id = cos_class_id(classref(Functor4D)); break;
    case 02212: *id = cos_class_id(classref(Functor4E)); break;
    case 02221: *id = cos_class_id(classref(Functor4F)); break;
    default   : test_assert(0, "invalid Functor4 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, Functor41, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;

  retmethod( fct(arg[0], arg[1], arg[2], arg[3]) ); // 01111
endmethod

defmethod(OBJ, gevalEnv, Functor42, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], arg[2], arg[3]) ); // 01112
endmethod

defmethod(OBJ, gevalEnv, Functor43, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], arg[2], arg[3]) ); // 01121
endmethod

defmethod(OBJ, gevalEnv, Functor44, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], arg[2], arg[3]) ); // 01122
endmethod

defmethod(OBJ, gevalEnv, Functor45, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], var[0], arg[3]) ); // 01211
endmethod

defmethod(OBJ, gevalEnv, Functor46, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], var[1], arg[3]) ); // 01212
endmethod

defmethod(OBJ, gevalEnv, Functor47, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], var[1], arg[3]) ); // 01221
endmethod

defmethod(OBJ, gevalEnv, Functor48, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], var[2], arg[3]) ); // 01222
endmethod

defmethod(OBJ, gevalEnv, Functor49, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], arg[2], var[0]) ); // 02111
endmethod

defmethod(OBJ, gevalEnv, Functor4A, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], arg[2], var[1]) ); // 02112
endmethod

defmethod(OBJ, gevalEnv, Functor4B, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], arg[2], var[1]) ); // 02121
endmethod

defmethod(OBJ, gevalEnv, Functor4C, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], arg[2], var[2]) ); // 02122
endmethod

defmethod(OBJ, gevalEnv, Functor4D, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], var[0], var[1]) ); // 02211
endmethod

defmethod(OBJ, gevalEnv, Functor4E, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], var[1], var[2]) ); // 02212
endmethod

defmethod(OBJ, gevalEnv, Functor4F, Array)
  OBJ *arg = self->Functor4.FunExpr4.arg;
  FUN4 fct = self->Functor4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], var[1], var[2]) ); // 02221
endmethod


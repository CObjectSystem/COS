/*
 o---------------------------------------------------------------------o
 |
 | COS SFunExpr (High Order Function)
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
 | $Id: Functor_hof.c,v 1.5 2010/06/02 22:47:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

#include "Functor.h"

// ---- eval

// ----- 1

defmethod(OBJ, gevalEnv, SFunExpr1, Array)
  OBJ *arg = self->FunExpr1.arg;
  FUN1 fct = self->FunExpr1.fct;

  retmethod( fct(arg[0]) );
endmethod

// ----- 2

defmethod(OBJ, gevalEnv, SFunExpr2, Array)
  switch(self->FunExpr2.FunExpr.Functor.msk) {
    case 011: cos_object_setId(_1, cos_class_id(classref(SFunExpr21))); break;
    case 012: cos_object_setId(_1, cos_class_id(classref(SFunExpr22))); break;
    case 021: cos_object_setId(_1, cos_class_id(classref(SFunExpr23))); break;
    default : test_assert(0, "invalid SFunExpr2 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, SFunExpr21, Array)
  OBJ *arg = self->SFunExpr2.FunExpr2.arg;
  FUN2 fct = self->SFunExpr2.FunExpr2.fct;

  retmethod( fct(arg[0], arg[1]) ); // 011
endmethod

defmethod(OBJ, gevalEnv, SFunExpr22, Array1)
  OBJ *arg = self->SFunExpr2.FunExpr2.arg;
  FUN2 fct = self->SFunExpr2.FunExpr2.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(var[0], arg[1]) ); // 012
endmethod

defmethod(OBJ, gevalEnv, SFunExpr23, Array1)
  OBJ *arg = self->SFunExpr2.FunExpr2.arg;
  FUN2 fct = self->SFunExpr2.FunExpr2.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(arg[0], var[0]) ); // 021
endmethod

// ---

defmethod(OBJ, gevalEnv, SFunExpr22, Array)
  OBJ *arg = self->SFunExpr2.FunExpr2.arg;
  FUN2 fct = self->SFunExpr2.FunExpr2.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1]) ); // 012
endmethod

defmethod(OBJ, gevalEnv, SFunExpr23, Array)
  OBJ *arg = self->SFunExpr2.FunExpr2.arg;
  FUN2 fct = self->SFunExpr2.FunExpr2.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0]) ); // 021
endmethod

// ----- 3

defmethod(OBJ, gevalEnv, SFunExpr3, Array)
  switch(self->FunExpr3.FunExpr.Functor.msk) {
    case 0111: cos_object_setId(_1, cos_class_id(classref(SFunExpr31))); break;
    case 0112: cos_object_setId(_1, cos_class_id(classref(SFunExpr32))); break;
    case 0121: cos_object_setId(_1, cos_class_id(classref(SFunExpr33))); break;
    case 0122: cos_object_setId(_1, cos_class_id(classref(SFunExpr34))); break;
    case 0211: cos_object_setId(_1, cos_class_id(classref(SFunExpr35))); break;
    case 0212: cos_object_setId(_1, cos_class_id(classref(SFunExpr36))); break;
    case 0221: cos_object_setId(_1, cos_class_id(classref(SFunExpr37))); break;
    default  : test_assert(0, "invalid SFunExpr3 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, SFunExpr31, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;

  retmethod( fct(arg[0], arg[1], arg[2]) ); // 0111
endmethod

defmethod(OBJ, gevalEnv, SFunExpr32, Array1)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(var[0], arg[1], arg[2]) ); // 0112
endmethod

defmethod(OBJ, gevalEnv, SFunExpr33, Array1)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(arg[0], var[0], arg[2]) ); // 0121
endmethod

defmethod(OBJ, gevalEnv, SFunExpr34, Array2)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(var[0], var[1], arg[2]) ); // 0122
endmethod

defmethod(OBJ, gevalEnv, SFunExpr35, Array1)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(arg[0], arg[1], var[0]) ); // 0211
endmethod

defmethod(OBJ, gevalEnv, SFunExpr36, Array2)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(var[0], arg[1], var[1]) ); // 0212
endmethod

defmethod(OBJ, gevalEnv, SFunExpr37, Array2)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->ArrayBlk.Array.object;

  retmethod( fct(arg[0], var[0], var[1]) ); // 0221
endmethod

// ---

defmethod(OBJ, gevalEnv, SFunExpr32, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], arg[2]) ); // 0112
endmethod

defmethod(OBJ, gevalEnv, SFunExpr33, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], arg[2]) ); // 0121
endmethod

defmethod(OBJ, gevalEnv, SFunExpr34, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], arg[2]) ); // 0122
endmethod

defmethod(OBJ, gevalEnv, SFunExpr35, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], var[0]) ); // 0211
endmethod

defmethod(OBJ, gevalEnv, SFunExpr36, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], var[1]) ); // 0212
endmethod

defmethod(OBJ, gevalEnv, SFunExpr37, Array)
  OBJ *arg = self->SFunExpr3.FunExpr3.arg;
  FUN3 fct = self->SFunExpr3.FunExpr3.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], var[1]) ); // 0221
endmethod

// ----- 4

defmethod(OBJ, gevalEnv, SFunExpr4, Array)
  switch(self->FunExpr4.FunExpr.Functor.msk) {
    case 01111: cos_object_setId(_1, cos_class_id(classref(SFunExpr41))); break;
    case 01112: cos_object_setId(_1, cos_class_id(classref(SFunExpr42))); break;
    case 01121: cos_object_setId(_1, cos_class_id(classref(SFunExpr43))); break;
    case 01122: cos_object_setId(_1, cos_class_id(classref(SFunExpr44))); break;
    case 01211: cos_object_setId(_1, cos_class_id(classref(SFunExpr45))); break;
    case 01212: cos_object_setId(_1, cos_class_id(classref(SFunExpr46))); break;
    case 01221: cos_object_setId(_1, cos_class_id(classref(SFunExpr47))); break;
    case 01222: cos_object_setId(_1, cos_class_id(classref(SFunExpr48))); break;
    case 02111: cos_object_setId(_1, cos_class_id(classref(SFunExpr49))); break;
    case 02112: cos_object_setId(_1, cos_class_id(classref(SFunExpr4A))); break;
    case 02121: cos_object_setId(_1, cos_class_id(classref(SFunExpr4B))); break;
    case 02122: cos_object_setId(_1, cos_class_id(classref(SFunExpr4C))); break;
    case 02211: cos_object_setId(_1, cos_class_id(classref(SFunExpr4D))); break;
    case 02212: cos_object_setId(_1, cos_class_id(classref(SFunExpr4E))); break;
    case 02221: cos_object_setId(_1, cos_class_id(classref(SFunExpr4F))); break;
    default   : test_assert(0, "invalid SFunExpr4 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, SFunExpr41, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;

  retmethod( fct(arg[0], arg[1], arg[2], arg[3]) ); // 01111
endmethod

defmethod(OBJ, gevalEnv, SFunExpr42, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], arg[2], arg[3]) ); // 01112
endmethod

defmethod(OBJ, gevalEnv, SFunExpr43, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], arg[2], arg[3]) ); // 01121
endmethod

defmethod(OBJ, gevalEnv, SFunExpr44, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], arg[2], arg[3]) ); // 01122
endmethod

defmethod(OBJ, gevalEnv, SFunExpr45, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], var[0], arg[3]) ); // 01211
endmethod

defmethod(OBJ, gevalEnv, SFunExpr46, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], var[1], arg[3]) ); // 01212
endmethod

defmethod(OBJ, gevalEnv, SFunExpr47, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], var[1], arg[3]) ); // 01221
endmethod

defmethod(OBJ, gevalEnv, SFunExpr48, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], var[2], arg[3]) ); // 01222
endmethod

defmethod(OBJ, gevalEnv, SFunExpr49, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], arg[2], var[0]) ); // 02111
endmethod

defmethod(OBJ, gevalEnv, SFunExpr4A, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], arg[2], var[1]) ); // 02112
endmethod

defmethod(OBJ, gevalEnv, SFunExpr4B, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], arg[2], var[1]) ); // 02121
endmethod

defmethod(OBJ, gevalEnv, SFunExpr4C, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(var[0], var[1], arg[2], var[2]) ); // 02122
endmethod

defmethod(OBJ, gevalEnv, SFunExpr4D, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( fct(arg[0], arg[1], var[0], var[1]) ); // 02211
endmethod

defmethod(OBJ, gevalEnv, SFunExpr4E, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(var[0], arg[1], var[1], var[2]) ); // 02212
endmethod

defmethod(OBJ, gevalEnv, SFunExpr4F, Array)
  OBJ *arg = self->SFunExpr4.FunExpr4.arg;
  FUN4 fct = self->SFunExpr4.FunExpr4.fct;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  retmethod( fct(arg[0], var[0], var[1], var[2]) ); // 02221
endmethod


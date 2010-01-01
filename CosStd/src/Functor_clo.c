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
 | $Id: Functor_clo.c,v 1.1 2010/01/01 14:23:37 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

#include "Functor_utl.h"

defclass(Functor1, FunExpr)
  FUN1 fct;
  U32  msk;
  I32  ary;
  OBJ  arg[1];
endclass

defclass(Functor2, FunExpr)
  FUN2 fct;
  U32  msk;
  I32  ary;
  OBJ  arg[2];
endclass

defclass(Functor3, FunExpr)
  FUN3 fct;
  U32  msk;
  I32  ary;
  OBJ  arg[3];
endclass

makclass(Functor1, FunExpr);
makclass(Functor2, FunExpr);
makclass(Functor3, FunExpr);

// ----- specialization for eval

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

// ----- type compatibility within the class cluster

STATIC_ASSERT(functor1_to_closure1_compatibility,
              COS_TYPE_COMPATIBILITY(struct FunExpr1, struct Functor1) &&
              COS_FIELD_COMPATIBILITY(Functor1,FunExpr1,fct) &&
              COS_FIELD_COMPATIBILITY(Functor1,FunExpr1,msk) &&
              COS_FIELD_COMPATIBILITY(Functor1,FunExpr1,ary) &&
              COS_FIELD_COMPATIBILITY(Functor1,FunExpr1,arg));

STATIC_ASSERT(functor2_to_closure2_compatibility,
              COS_TYPE_COMPATIBILITY(struct FunExpr2, struct Functor2) &&
              COS_FIELD_COMPATIBILITY(Functor2,FunExpr2,fct) &&
              COS_FIELD_COMPATIBILITY(Functor2,FunExpr2,msk) &&
              COS_FIELD_COMPATIBILITY(Functor2,FunExpr2,ary) &&
              COS_FIELD_COMPATIBILITY(Functor2,FunExpr2,arg));

STATIC_ASSERT(functor3_to_closure3_compatibility,
              COS_TYPE_COMPATIBILITY(struct FunExpr3, struct Functor3) &&
              COS_FIELD_COMPATIBILITY(Functor3,FunExpr3,fct) &&
              COS_FIELD_COMPATIBILITY(Functor3,FunExpr3,msk) &&
              COS_FIELD_COMPATIBILITY(Functor3,FunExpr3,ary) &&
              COS_FIELD_COMPATIBILITY(Functor3,FunExpr3,arg));

// ----- ctors

// TODO ?

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(Functor,N), COS_PP_CAT(Functor,N)) \
  self->FunExpr.str = self2->FunExpr.str; \
  self->fct = self2->fct; \
  self->msk = self2->msk; \
  self->ary = self2->ary; \
\
  for (int i = 0; i < N; i++) \
    self->arg[i] = isIdx(self->msk, i) ? self2->arg[i] : gretain(self2->arg[i]); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)

// ----- dtors

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, gdeinit, COS_PP_CAT(Functor,N)) \
  for (int i = 0; i < N; i++) \
    if (!isIdx(self->msk, i)) grelease(self->arg[i]); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)

// ----- arity

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(I32, garity, COS_PP_CAT(Functor,N)) \
  if (self->ary == -1) \
    self->ary = Functor_getArity(self->arg, N, self->msk); \
\
  retmethod(self->ary); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)

// ---- eval

// ----- 1

defmethod(OBJ, gevalEnv, Functor1, Array)
  retmethod( self->fct(self->arg[0]) );
endmethod

// ----- 2

defmethod(OBJ, gevalEnv, Functor2, Array)
  U32 *id = &self->FunExpr.Functor.Object.id;

  switch(self->msk) {
    case  9: *id = cos_class_id(classref(Functor23)); break;
    case 10: *id = cos_class_id(classref(Functor22)); break;
    case 17: *id = cos_class_id(classref(Functor21)); break;
    default:
      test_assert(0, "invalid Functor2 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, Functor21, Array) /* msk = 010 001 = 17 */
  OBJ *arg = self->Functor2.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( self->Functor2.fct(arg[0], var[0]) );
endmethod

defmethod(OBJ, gevalEnv, Functor22, Array) /* msk = 001 010 = 10 */
  OBJ *arg = self->Functor2.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( self->Functor2.fct(var[0], arg[1]) );
endmethod

defmethod(OBJ, gevalEnv, Functor23, Array) /* msk = 001 001 = 9 */
  OBJ *arg = self->Functor2.arg;

  retmethod( self->Functor2.fct(arg[0], arg[1]) );
endmethod

// ----- 3

defmethod(OBJ, gevalEnv, Functor3, Array)
  U32 *id = &self->FunExpr.Functor.Object.id;

  switch(self->msk) {
    case  73: *id = cos_class_id(classref(Functor37)); break;
    case  74: *id = cos_class_id(classref(Functor36)); break;
    case  81: *id = cos_class_id(classref(Functor35)); break;
    case  82: *id = cos_class_id(classref(Functor34)); break;
    case 137: *id = cos_class_id(classref(Functor33)); break;
    case 138: *id = cos_class_id(classref(Functor32)); break;
    case 145: *id = cos_class_id(classref(Functor31)); break;
    default:
      test_assert(0, "invalid Functor3 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, Functor31, Array) /* msk = 010 010 001 = 145 */
  OBJ *arg = self->Functor3.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( self->Functor3.fct(arg[0], var[0], var[1]) );
endmethod

defmethod(OBJ, gevalEnv, Functor32, Array) /* msk = 010 001 010 = 138 */
  OBJ *arg = self->Functor3.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( self->Functor3.fct(var[0], arg[1], var[1]) );
endmethod

defmethod(OBJ, gevalEnv, Functor33, Array) /* msk = 010 001 001 = 137 */
  OBJ *arg = self->Functor3.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( self->Functor3.fct(arg[0], arg[1], var[0]) );
endmethod

defmethod(OBJ, gevalEnv, Functor34, Array) /* msk = 001 010 010 = 82 */
  OBJ *arg = self->Functor3.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  retmethod( self->Functor3.fct(var[0], var[1], arg[2]) );
endmethod

defmethod(OBJ, gevalEnv, Functor35, Array) /* msk = 001 010 001 = 81 */
  OBJ *arg = self->Functor3.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( self->Functor3.fct(arg[0], var[0], arg[2]) );
endmethod

defmethod(OBJ, gevalEnv, Functor36, Array) /* msk = 001 001 010 = 74 */
  OBJ *arg = self->Functor3.arg;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  retmethod( self->Functor3.fct(var[0], arg[1], arg[2]) );
endmethod

defmethod(OBJ, gevalEnv, Functor37, Array) /* msk = 001 001 001 = 73 */
  OBJ *arg = self->Functor3.arg;

  retmethod( self->Functor3.fct(arg[0], arg[1], arg[2]) );
endmethod


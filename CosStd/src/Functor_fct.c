/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Function)
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
 | $Id: Functor_fct.c,v 1.4 2009/12/28 00:18:54 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

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

// ----- type compatibility within the class cluster

STATIC_ASSERT(functor1_to_function1_compatibility,
              COS_FIELD_COMPATIBILITY(Function1,FunExpr1,fct));

STATIC_ASSERT(functor2_to_function2_compatibility,
              COS_FIELD_COMPATIBILITY(Function2,FunExpr2,fct));

STATIC_ASSERT(functor3_to_function3_compatibility,
              COS_FIELD_COMPATIBILITY(Function3,FunExpr3,fct));

STATIC_ASSERT(functor4_to_function4_compatibility,
              COS_FIELD_COMPATIBILITY(Function4,FunExpr4,fct));

STATIC_ASSERT(functor5_to_function5_compatibility,
              COS_FIELD_COMPATIBILITY(Function5,FunExpr5,fct));

STATIC_ASSERT(functor6_to_function6_compatibility,
              COS_FIELD_COMPATIBILITY(Function6,FunExpr6,fct));

STATIC_ASSERT(functor7_to_function7_compatibility,
              COS_FIELD_COMPATIBILITY(Function7,FunExpr7,fct));

STATIC_ASSERT(functor8_to_function8_compatibility,
              COS_FIELD_COMPATIBILITY(Function8,FunExpr8,fct));

STATIC_ASSERT(functor9_to_function9_compatibility,
              COS_FIELD_COMPATIBILITY(Function9,FunExpr9,fct));

// ----- ctors

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(Function,N), COS_PP_CAT(Function,N)) \
  self->FunExpr.str = self2->FunExpr.str; \
  self->fct = self2->fct; \
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)
DEFMETHOD(6)
DEFMETHOD(7)
DEFMETHOD(8)
DEFMETHOD(9)

// ----- arity

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(I32, garity, COS_PP_CAT(Function,N)) \
  retmethod(N); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)
DEFMETHOD(6)
DEFMETHOD(7)
DEFMETHOD(8)
DEFMETHOD(9)

// ---- eval

defmethod(OBJ, gevalEnv, Function0, Container)
  retmethod( self->fct() );
endmethod

// ----- 1

defmethod(OBJ, gevalEnv, Function1, Array1)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0]) );
endmethod

defmethod(OBJ, gevalEnv, Function1, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 1, "invalid placeholder index" );

  retmethod( self->fct(var[0]) );
endmethod

// ----- 2

#include <cos/gen/value.h>

defmethod(OBJ, gevalEnv, Function2, Array2)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1]) );
endmethod

defmethod(OBJ, gevalEnv, Function2, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;
  
  test_assert( size >= 2, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1]) );
endmethod

// ----- 3

defmethod(OBJ, gevalEnv, Function3, Array3)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2]) );
endmethod

defmethod(OBJ, gevalEnv, Function3, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 3, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2]) );
endmethod

// ----- 4

defmethod(OBJ, gevalEnv, Function4, Array4)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2], var[3]) );
endmethod

defmethod(OBJ, gevalEnv, Function4, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 4, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2], var[3]) );
endmethod

// ----- 5

defmethod(OBJ, gevalEnv, Function5, Array5)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4]) );
endmethod

defmethod(OBJ, gevalEnv, Function5, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 5, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4]) );
endmethod

// ----- 6

defmethod(OBJ, gevalEnv, Function6, Array6)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4], var[5]) );
endmethod

defmethod(OBJ, gevalEnv, Function6, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 6, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4], var[5]) );
endmethod

// ----- 7

defmethod(OBJ, gevalEnv, Function7, Array7)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4],
                       var[5], var[6]) );
endmethod

defmethod(OBJ, gevalEnv, Function7, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 7, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4],
                       var[5], var[6]) );
endmethod

// ----- 8

defmethod(OBJ, gevalEnv, Function8, Array8)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4],
                       var[5], var[6], var[7]) );
endmethod

defmethod(OBJ, gevalEnv, Function8, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 8, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4],
                       var[5], var[6], var[7]) );
endmethod

// ----- 9

defmethod(OBJ, gevalEnv, Function9, Array9)
  OBJ *var = self2->Array.object;

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4],
                       var[5], var[6], var[7], var[8]) );
endmethod

defmethod(OBJ, gevalEnv, Function9, Array)
  OBJ *var = self2->object;
  U32 size = self2->size;

  test_assert( size >= 9, "invalid placeholder index" );

  retmethod( self->fct(var[0], var[1], var[2], var[3], var[4],
                       var[5], var[6], var[7], var[8]) );
endmethod


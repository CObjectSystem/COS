/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (message)
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
 | $Id: Functor_msg.c,v 1.6 2010/06/02 22:47:26 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>

#include "Functor.h"
#include "Functor_utl.h"

// ----- copy

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, ginitWith, COS_PP_CAT(Message,N), COS_PP_CAT(Message,N)) \
  self->MthExpr.Functor.msk = self2->MthExpr.Functor.msk; \
  self->MthExpr.sel = self2->MthExpr.sel; \
  self->arg = 0; \
\
  if (self2->arg) \
    self->arg = Functor_cloneArgs(self2->MthExpr.sel, self2->arg); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ----- dtors

#undef  DEFMETHOD
#define DEFMETHOD(N) \
\
defmethod(OBJ, gdeinit, COS_PP_CAT(Message,N)) \
  if (self->arg) \
    Functor_deleteArgs(self->MthExpr.sel, self->arg); \
\
  retmethod(_1); \
endmethod

DEFMETHOD(1)
DEFMETHOD(2)
DEFMETHOD(3)
DEFMETHOD(4)
DEFMETHOD(5)

// ---- eval

// ----- 1

defmethod(OBJ, gevalEnv, Message1, Array1)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->ArrayBlk.Array.object;
  
  U32 aid0 = cos_object_id(var[0]);
  IMP1 imp = cos_method_fastLookup1(sel, aid0);

  imp(sel, var[0], self->arg, _ret);
endmethod

defmethod(OBJ, gevalEnv, Message1, Array)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->object;
  
  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  IMP1 imp = cos_method_fastLookup1(sel, aid0);

  imp(sel, var[0], self->arg, _ret);
endmethod

// ----- 2

defmethod(OBJ, gevalEnv, Message2, Array2)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->ArrayBlk.Array.object;
  
  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  imp(sel, var[0], var[1], self->arg, _ret);
endmethod

defmethod(OBJ, gevalEnv, Message2, Array)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->object;
  
  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  imp(sel, var[0], var[1], self->arg, _ret);
endmethod

// ----- 3

defmethod(OBJ, gevalEnv, Message3, Array3)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->ArrayBlk.Array.object;
  
  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(var[2]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  imp(sel, var[0], var[1], var[2], self->arg, _ret);
endmethod

defmethod(OBJ, gevalEnv, Message3, Array)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->object;
  
  test_assert( self2->size >= 3, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(var[2]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  imp(sel, var[0], var[1], var[2], self->arg, _ret);
endmethod

// ----- 4

defmethod(OBJ, gevalEnv, Message4, Array)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->object;
  
  test_assert( self2->size >= 4, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(var[2]);
  U32 aid3 = cos_object_id(var[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  imp(sel, var[0], var[1], var[2], var[3], self->arg, _ret);
endmethod

// ----- 5

defmethod(OBJ, gevalEnv, Message5, Array)
  SEL  sel = self->MthExpr.sel;
  OBJ *var = self2->object;
  
  test_assert( self2->size >= 5, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(var[2]);
  U32 aid3 = cos_object_id(var[3]);
  U32 aid4 = cos_object_id(var[4]);
  IMP5 imp = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  imp(sel, var[0], var[1], var[2], var[3], var[4], self->arg, _ret);
endmethod


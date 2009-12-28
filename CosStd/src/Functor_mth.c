/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Method Expression)
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
 | $Id: Functor_mth.c,v 1.1 2009/12/28 00:18:54 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

#include "Functor_utl.h"

makclass(MthExpr1, MthExpr);
makclass(MthExpr2, MthExpr);
makclass(MthExpr3, MthExpr);
makclass(MthExpr4, MthExpr);
makclass(MthExpr5, MthExpr);

// ---- eval (stack-like environment)

defmethod(OBJ, gevalEnv, MthExpr1, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);

  IMP1 mth = cos_method_fastLookup1(sel, aid0);

  mth(sel, arg0, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr2, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);

  IMP2 mth = cos_method_fastLookup2(sel, aid0, aid1);

  mth(sel, arg0, arg1, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr3, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);

  IMP3 mth = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  mth(sel, arg0, arg1, arg2, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr4, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);

  IMP4 mth = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  mth(sel, arg0, arg1, arg2, arg3, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr5, Array)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;
  OBJ *var = self2->object;
  U32 size = self2->size;

  OBJ arg0 = getArg(0, msk, arg, var, size, _2);
  OBJ arg1 = getArg(1, msk, arg, var, size, _2);
  OBJ arg2 = getArg(2, msk, arg, var, size, _2);
  OBJ arg3 = getArg(3, msk, arg, var, size, _2);
  OBJ arg4 = getArg(4, msk, arg, var, size, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  U32 aid4 = cos_object_id(arg4);

  IMP5 mth = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  mth(sel, arg0, arg1, arg2, arg3, arg4, self->args, _ret);
endmethod

// ---- eval (generic environement)

defmethod(OBJ, gevalEnv, MthExpr1, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);

  IMP1 mth = cos_method_fastLookup1(sel, aid0);

  mth(sel, arg0, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr2, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);

  IMP2 mth = cos_method_fastLookup2(sel, aid0, aid1);

  mth(sel, arg0, arg1, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr3, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);
  OBJ arg2 = getVar(2, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);

  IMP3 mth = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  mth(sel, arg0, arg1, arg2, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr4, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);
  OBJ arg2 = getVar(2, msk, arg, _2);
  OBJ arg3 = getVar(3, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);

  IMP4 mth = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  mth(sel, arg0, arg1, arg2, arg3, self->args, _ret);
endmethod

defmethod(OBJ, gevalEnv, MthExpr5, Container)
  SEL  sel = self->sel;
  U32  msk = self->msk;
  OBJ *arg = self->arg;

  OBJ arg0 = getVar(0, msk, arg, _2);
  OBJ arg1 = getVar(1, msk, arg, _2);
  OBJ arg2 = getVar(2, msk, arg, _2);
  OBJ arg3 = getVar(3, msk, arg, _2);
  OBJ arg4 = getVar(4, msk, arg, _2);

  U32 aid0 = cos_object_id(arg0);
  U32 aid1 = cos_object_id(arg1);
  U32 aid2 = cos_object_id(arg2);
  U32 aid3 = cos_object_id(arg3);
  U32 aid4 = cos_object_id(arg4);

  IMP5 mth = cos_method_fastLookup5(sel, aid0, aid1, aid2, aid3, aid4);

  mth(sel, arg0, arg1, arg2, arg3, arg4, self->args, _ret);
endmethod


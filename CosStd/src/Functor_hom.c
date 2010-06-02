/*
 o---------------------------------------------------------------------o
 |
 | COS SMthExpr (High Order Message)
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
 | $Id: Functor_hom.c,v 1.5 2010/06/02 22:47:26 ldeniau Exp $
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

defmethod(OBJ, gevalEnv, SMthExpr1, Array)
  SEL  sel = self->MthExpr1.MthExpr.sel;
  OBJ *arg = self->MthExpr1.rcv;

  U32 aid0 = cos_object_id(arg[0]);
  IMP1 imp = cos_method_fastLookup1(sel, aid0);

  imp(sel, arg[0], self->MthExpr1.arg, _ret);
endmethod

// ----- 2

defmethod(OBJ, gevalEnv, SMthExpr2, Array)
  switch(self->MthExpr2.MthExpr.Functor.msk) {
    case 011: cos_object_setId(_1, cos_class_id(classref(SMthExpr21))); break;
    case 012: cos_object_setId(_1, cos_class_id(classref(SMthExpr22))); break;
    case 021: cos_object_setId(_1, cos_class_id(classref(SMthExpr23))); break;
    default : test_assert(0, "invalid SMthExpr2 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, SMthExpr21, Array)
  SEL  sel = self->SMthExpr2.MthExpr2.MthExpr.sel;
  OBJ *arg = self->SMthExpr2.MthExpr2.rcv;

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = &self->SMthExpr2.MthExpr2;

  imp(sel, arg[0], arg[1], mth->arg, _ret); // 011
endmethod

defmethod(OBJ, gevalEnv, SMthExpr22, Array1)
  SEL  sel = self->SMthExpr2.MthExpr2.MthExpr.sel;
  OBJ *arg = self->SMthExpr2.MthExpr2.rcv;
  OBJ *var = self2->ArrayBlk.Array.object;

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = &self->SMthExpr2.MthExpr2;

  imp(sel, var[0], arg[1], mth->arg, _ret); // 012
endmethod

defmethod(OBJ, gevalEnv, SMthExpr23, Array1)
  SEL  sel = self->SMthExpr2.MthExpr2.MthExpr.sel;
  OBJ *arg = self->SMthExpr2.MthExpr2.rcv;
  OBJ *var = self2->ArrayBlk.Array.object;

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = &self->SMthExpr2.MthExpr2;

  imp(sel, arg[0], var[0], mth->arg, _ret); // 021
endmethod

// ---

defmethod(OBJ, gevalEnv, SMthExpr22, Array)
  SEL  sel = self->SMthExpr2.MthExpr2.MthExpr.sel;
  OBJ *arg = self->SMthExpr2.MthExpr2.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = &self->SMthExpr2.MthExpr2;

  imp(sel, var[0], arg[1], mth->arg, _ret); // 012
endmethod

defmethod(OBJ, gevalEnv, SMthExpr23, Array)
  SEL  sel = self->SMthExpr2.MthExpr2.MthExpr.sel;
  OBJ *arg = self->SMthExpr2.MthExpr2.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  IMP2 imp = cos_method_fastLookup2(sel, aid0, aid1);

  struct MthExpr2 *mth = &self->SMthExpr2.MthExpr2;

  imp(sel, arg[0], var[0], mth->arg, _ret); // 021
endmethod

// ----- 3

defmethod(OBJ, gevalEnv, SMthExpr3, Array)
  switch(self->MthExpr3.MthExpr.Functor.msk) {
    case 0111: cos_object_setId(_1, cos_class_id(classref(SMthExpr31))); break;
    case 0112: cos_object_setId(_1, cos_class_id(classref(SMthExpr32))); break;
    case 0121: cos_object_setId(_1, cos_class_id(classref(SMthExpr33))); break;
    case 0122: cos_object_setId(_1, cos_class_id(classref(SMthExpr34))); break;
    case 0211: cos_object_setId(_1, cos_class_id(classref(SMthExpr35))); break;
    case 0212: cos_object_setId(_1, cos_class_id(classref(SMthExpr36))); break;
    case 0221: cos_object_setId(_1, cos_class_id(classref(SMthExpr37))); break;
    default  : test_assert(0, "invalid SMthExpr3 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, SMthExpr31, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(arg[2]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, arg[0], arg[1], arg[2], mth->arg, _ret); // 0111
endmethod

defmethod(OBJ, gevalEnv, SMthExpr32, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(arg[2]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, var[0], arg[1], arg[2], mth->arg, _ret); // 0112
endmethod

defmethod(OBJ, gevalEnv, SMthExpr33, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  U32 aid2 = cos_object_id(arg[2]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, arg[0], var[0], arg[2], mth->arg, _ret); // 0121
endmethod

defmethod(OBJ, gevalEnv, SMthExpr34, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(arg[2]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, var[0], var[1], arg[2], mth->arg, _ret); // 0122
endmethod

defmethod(OBJ, gevalEnv, SMthExpr35, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(var[0]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, arg[0], arg[1], var[0], mth->arg, _ret); // 0211
endmethod

defmethod(OBJ, gevalEnv, SMthExpr36, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(var[1]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, var[0], arg[1], var[1], mth->arg, _ret); // 0212
endmethod

defmethod(OBJ, gevalEnv, SMthExpr37, Array)
  SEL  sel = self->SMthExpr3.MthExpr3.MthExpr.sel;
  OBJ *arg = self->SMthExpr3.MthExpr3.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  U32 aid2 = cos_object_id(var[1]);
  IMP3 imp = cos_method_fastLookup3(sel, aid0, aid1, aid2);

  struct MthExpr3 *mth = &self->SMthExpr3.MthExpr3;

  imp(sel, arg[0], var[0], var[1], mth->arg, _ret); // 0221
endmethod

// ----- 4

defmethod(OBJ, gevalEnv, SMthExpr4, Array)
  switch(self->MthExpr4.MthExpr.Functor.msk) {
    case 01111: cos_object_setId(_1, cos_class_id(classref(SMthExpr41))); break;
    case 01112: cos_object_setId(_1, cos_class_id(classref(SMthExpr42))); break;
    case 01121: cos_object_setId(_1, cos_class_id(classref(SMthExpr43))); break;
    case 01122: cos_object_setId(_1, cos_class_id(classref(SMthExpr44))); break;
    case 01211: cos_object_setId(_1, cos_class_id(classref(SMthExpr45))); break;
    case 01212: cos_object_setId(_1, cos_class_id(classref(SMthExpr46))); break;
    case 01221: cos_object_setId(_1, cos_class_id(classref(SMthExpr47))); break;
    case 01222: cos_object_setId(_1, cos_class_id(classref(SMthExpr48))); break;
    case 02111: cos_object_setId(_1, cos_class_id(classref(SMthExpr49))); break;
    case 02112: cos_object_setId(_1, cos_class_id(classref(SMthExpr4A))); break;
    case 02121: cos_object_setId(_1, cos_class_id(classref(SMthExpr4B))); break;
    case 02122: cos_object_setId(_1, cos_class_id(classref(SMthExpr4C))); break;
    case 02211: cos_object_setId(_1, cos_class_id(classref(SMthExpr4D))); break;
    case 02212: cos_object_setId(_1, cos_class_id(classref(SMthExpr4E))); break;
    case 02221: cos_object_setId(_1, cos_class_id(classref(SMthExpr4F))); break;
    default   : test_assert(0, "invalid SMthExpr4 mask");
  }

  forward_message(_1,_2);
endmethod

defmethod(OBJ, gevalEnv, SMthExpr41, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], arg[1], arg[2], arg[3], mth->arg, _ret); // 01111
endmethod

defmethod(OBJ, gevalEnv, SMthExpr42, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], arg[1], arg[2], arg[3], mth->arg, _ret); // 01112
endmethod

defmethod(OBJ, gevalEnv, SMthExpr43, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], var[0], arg[2], arg[3], mth->arg, _ret); // 01121
endmethod

defmethod(OBJ, gevalEnv, SMthExpr44, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], var[1], arg[2], arg[3], mth->arg, _ret); // 01122
endmethod

defmethod(OBJ, gevalEnv, SMthExpr45, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(var[0]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], arg[1], var[0], arg[3], mth->arg, _ret); // 01211
endmethod

defmethod(OBJ, gevalEnv, SMthExpr46, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(var[1]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], arg[1], var[1], arg[3], mth->arg, _ret); // 01212
endmethod

defmethod(OBJ, gevalEnv, SMthExpr47, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  U32 aid2 = cos_object_id(var[1]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], var[0], var[1], arg[3], mth->arg, _ret); // 01221
endmethod

defmethod(OBJ, gevalEnv, SMthExpr48, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(var[2]);
  U32 aid3 = cos_object_id(arg[3]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], var[1], var[2], arg[3], mth->arg, _ret); // 01222
endmethod

defmethod(OBJ, gevalEnv, SMthExpr49, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 1, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(var[0]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], arg[1], arg[2], var[0], mth->arg, _ret); // 02111
endmethod

defmethod(OBJ, gevalEnv, SMthExpr4A, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(var[1]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], arg[1], arg[2], var[1], mth->arg, _ret); // 02112
endmethod

defmethod(OBJ, gevalEnv, SMthExpr4B, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(var[1]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], var[0], arg[2], var[1], mth->arg, _ret); // 02121
endmethod

defmethod(OBJ, gevalEnv, SMthExpr4C, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(var[1]);
  U32 aid2 = cos_object_id(arg[2]);
  U32 aid3 = cos_object_id(var[2]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], var[1], arg[2], var[2], mth->arg, _ret); // 02122
endmethod

defmethod(OBJ, gevalEnv, SMthExpr4D, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 2, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(var[0]);
  U32 aid3 = cos_object_id(var[1]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], arg[1], var[0], var[1], mth->arg, _ret); // 02211
endmethod

defmethod(OBJ, gevalEnv, SMthExpr4E, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  U32 aid0 = cos_object_id(var[0]);
  U32 aid1 = cos_object_id(arg[1]);
  U32 aid2 = cos_object_id(var[1]);
  U32 aid3 = cos_object_id(var[2]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, var[0], arg[1], var[1], var[2], mth->arg, _ret); // 02212
endmethod

defmethod(OBJ, gevalEnv, SMthExpr4F, Array)
  SEL  sel = self->SMthExpr4.MthExpr4.MthExpr.sel;
  OBJ *arg = self->SMthExpr4.MthExpr4.rcv;
  OBJ *var = self2->object;

  test_assert( self2->size >= 3, "invalid placeholder index" );

  U32 aid0 = cos_object_id(arg[0]);
  U32 aid1 = cos_object_id(var[0]);
  U32 aid2 = cos_object_id(var[1]);
  U32 aid3 = cos_object_id(var[2]);
  IMP4 imp = cos_method_fastLookup4(sel, aid0, aid1, aid2, aid3);

  struct MthExpr4 *mth = &self->SMthExpr4.MthExpr4;

  imp(sel, arg[0], var[0], var[1], var[2], mth->arg, _ret); // 02221
endmethod


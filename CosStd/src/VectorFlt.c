/*
 o---------------------------------------------------------------------o
 |
 | COS FltVector
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: VectorFlt.c,v 1.2 2010/06/13 20:24:46 ldeniau Exp $
 |
*/

#define FLTVECTOR_ONLY

#define T     FltVector
#define TM   mFltVector
#define TP  pmFltVector
#define TN    FltVectorN
#define TF    FltVectorFix
#define TD    FltVectorDyn
// #define TL    FltVectorLzy
#define TV    FltVectorView
#define TW    FltVectorSubView
#define TS    "float vector"
#define TE    Float

#define TF1   FltFunction1
#define TF2   FltFunction2
#define TF3   FltFunction3
#define TF4   FltFunction4
#define TF5   FltFunction5

#define PF1   F64FCT1
#define PF2   F64FCT2
#define PF3   F64FCT3
#define PF4   F64FCT4
#define PF5   F64FCT5

#define VS    Vector.ValueSequence.Sequence

#define VAL       F64
#define VALOBJ(v) aFloat(v)

#define aTView(v,s)    aFltVectorView(v,s)
#define aTRef(v,s)     aFltVectorRef(v,s)

#define T_alloc(s)        FltVector_alloc(s)
#define TV_init(vw,v,s,b) FltVectorView_init(vw,v,s,b)

#define TOVALPTR     gfltPtr
#define TOVAL(v)     gflt(v)
#define VALUE(v)     v->value
#define EQUAL(v1,v2) float_equal(v1,v2)

#include <cos/FltVector.h>
#include <cos/Function.h>

makclass(FltVector, FloatingVector);

// vector templates
#include "./tmpl/Vector_utl.h"

#include "./tmpl/Vector.c"

#include "./tmpl/Vector_dyn.c"
// #include "./tmpl/Vector_lzy.c"
#include "./tmpl/Vector_vw.c"

#include "./tmpl/Vector_acc.c"
#include "./tmpl/Vector_alg.c"
#include "./tmpl/Vector_fun.c"
// #include "./tmpl/Vector_fct.c"
// #include "./tmpl/Vector_vfn.c"


/*
 o---------------------------------------------------------------------o
 |
 | COS CpxVector - basic vectors
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
 | $Id: CpxVector.c,v 1.9 2009/10/02 21:56:20 ldeniau Exp $
 |
*/

#define CPXVECTOR_ONLY

#define T     CpxVector
#define TM   mCpxVector
#define TP  pmCpxVector
#define TN    CpxVectorN
#define TF    CpxVectorFix
#define TD    CpxVectorDyn
#define TL    CpxVectorLzy
#define TV    CpxVectorView
#define TW    CpxVectorSubView
#define TS    "complex vector"
#define TE    Complex

#define TF1   CpxFunction1
#define TF2   CpxFunction2
#define TF3   CpxFunction3
#define TF4   CpxFunction4
#define TF5   CpxFunction5

#define PF1   C64FCT1
#define PF2   C64FCT2
#define PF3   C64FCT3
#define PF4   C64FCT4
#define PF5   C64FCT5

#define VS    Vector.ValueSequence.Sequence

#define VAL       C64
#define VALOBJ(v) aComplex(v)

#define aTView(v,s)    aCpxVectorView(v,s)
#define aTRef(v,s)     aCpxVectorRef(v,s)

#define T_alloc(s)        CpxVector_alloc(s)
#define TV_init(vw,v,s,b) CpxVectorView_init(vw,v,s,b)

#define TOVALPTR     gcpxPtr
#define TOVAL(v)     gcpx(v)
#define VALUE(v)     v->value
#define EQUAL(v1,v2) complex_equal(v1,v2)

#include <cos/CpxVector.h>
#include <cos/Function.h>

makclass(CpxVector, FloatingVector);

// vector templates
#include "./tmpl/Vector_utl.h"

#include "./tmpl/Vector.c"

#include "./tmpl/Vector_dyn.c"
#include "./tmpl/Vector_lzy.c"
#include "./tmpl/Vector_vw.c"

#include "./tmpl/Vector_acc.c"
#include "./tmpl/Vector_alg.c"
#include "./tmpl/Vector_fun.c"
// #include "./tmpl/Vector_fct.c"
// #include "./tmpl/Vector_vfn.c"


/*
 o---------------------------------------------------------------------o
 |
 | COS ChrVector
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
 | $Id: VectorChr.c,v 1.1 2010/05/31 14:02:58 ldeniau Exp $
 |
*/

#define CHRVECTOR_ONLY

#define T     ChrVector
#define TM   mChrVector
#define TP  pmChrVector
#define TN    ChrVectorN
#define TF    ChrVectorFix
#define TD    ChrVectorDyn
#define TL    ChrVectorLzy
#define TV    ChrVectorView
#define TW    ChrVectorSubView
#define TS    "char vector"
#define TE    Char

#define TF1   IntFunction1
#define TF2   IntFunction2
#define TF3   IntFunction3
#define TF4   IntFunction4
#define TF5   IntFunction5

#define PF1   I32FCT1
#define PF2   I32FCT2
#define PF3   I32FCT3
#define PF4   I32FCT4
#define PF5   I32FCT5

#define VS    Vector.ValueSequence.Sequence

#define VAL       I8
#define VALOBJ(v) aChar(v)

#define aTView(v,s)    aChrVectorView(v,s)
#define aTRef(v,s)     aChrVectorRef(v,s)

#define T_alloc(s)        ChrVector_alloc(s)
#define TV_init(vw,v,s,b) ChrVectorView_init(vw,v,s,b)

#define TOVALPTR      gchrPtr
#define TOVAL(v)      gchr(v)
#define VALUE(v)      v->Int.value
#define EQUAL(v1,v2)  (v1 == v2)

#include <cos/ChrVector.h>
#include <cos/Function.h>

makclass(ChrVector, IntegralVector);

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


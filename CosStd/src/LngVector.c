/*
 o---------------------------------------------------------------------o
 |
 | COS LngVector
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
 | $Id: LngVector.c,v 1.6 2009/09/02 10:51:37 ldeniau Exp $
 |
*/

#define    VECTOR_ONLY
#define LNGVECTOR_ONLY

#define T     LngVector
#define TM   mLngVector
#define TP  pmLngVector
#define TN    LngVectorN
#define TF    LngVectorFix
#define TD    LngVectorDyn
#define TL    LngVectorLzy
#define TV    LngVectorView
#define TS    "long vector"
#define TE    Long

#define TF1   LngFunction1
#define TF2   LngFunction2
#define TF3   LngFunction3
#define TF4   LngFunction4
#define TF5   LngFunction5

#define PF1   I64FCT1
#define PF2   I64FCT2
#define PF3   I64FCT3
#define PF4   I64FCT4
#define PF5   I64FCT5

#define VS    Vector.ValueSequence.Sequence

#define VAL       I64
#define VALINT  
#define VALFLT  
#define VALOBJ(v) aLong(v)

#define  valref  value
#define _valref _value

#define aTView(v,s)    aLngVectorView(v,s)
#define aTRef(v,s)     aLngVectorRef(v,s)

#define T_alloc(s)      LngVector_alloc(s)
#define TV_init(vw,v,s) LngVectorView_init(vw,v,s)

#define TOVALPTR        glngPtr
#define TOVAL(v)        glng(v)
#define VALUE(v)        v->value
#define ASSIGN(d,s)     (d = s)
#define SWAP(v1,v2)     { VAL tmp = v1; v1 = v2; v2 = tmp; }
#define EQUAL(v1,v2)    (v1 == v2 ? True : False)
#define COMPARE(v1,v2)  (v1<v2 ? Lesser : v1>v2 ? Greater : Equal)
#define RETAIN(v)       (v)
#define RELEASE(v)      
#define AUTODELETE(v)   gautoDelete(v)
#define PROTECT(v)   
#define UNPROTECT(v) 

#include <cos/LngVector.h>
#include <cos/Function.h>

makclass(LngVector, IntegralVector);

// vector templates
#include "./tmpl/Vector.c"

#include "./tmpl/Vector_dyn.c"
#include "./tmpl/Vector_lzy.c"
#include "./tmpl/Vector_vw.c"

#include "./tmpl/Vector_acc.c"
#include "./tmpl/Vector_alg.c"
#include "./tmpl/Vector_fun.c"
#include "./tmpl/Vector_fct.c"
#include "./tmpl/Vector_vfn.c"


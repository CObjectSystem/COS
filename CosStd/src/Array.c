/*
 o---------------------------------------------------------------------o
 |
 | COS Array
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
 | $Id: Array.c,v 1.41 2009/08/29 21:33:39 ldeniau Exp $
 |
*/

#define ARRAY_ONLY

#define T     Array
#define TM   mArray
#define TP  pmArray
#define TN    ArrayN
#define TF    ArrayFix
#define TD    ArrayDyn
#define TL    ArrayLzy
#define TV    ArrayView
#define TS    "array"
#define TE    Object

#define VS    Sequence

#define VAL       OBJ
#define VALINT    aInt
#define VALFLT    aFloat
#define VALOBJ(v) v

#define  valref  object
#define _valref _object

#define aTView(v,s)    aArrayView(v,s)
#define aTRef(v,s)     aArrayRef(v,s)

#define T_alloc(s)      Array_alloc(s)
#define TV_init(vw,v,s) ArrayView_init(vw,v,s)

#define TOVALPTR        gobjPtr
#define TOVAL(v)        (v)   
#define VALUE(v)        ((OBJ)v)
#define ASSIGN(d,s)     { VAL old = d; d = RETAIN(s); RELEASE(old); }
#define SWAP(v1,v2)     { VAL tmp = v1; v1 = v2; v2 = tmp; }
#define EQUAL(v1,v2)    gisEqual(v1,v2)
#define COMPARE(v1,v2)  gcompare(v1,v2)
#define EVAL1(v1,v2)    geval1(v1,v2)
#define RETAIN(v)       gretain(v)
#define RELEASE(v)      grelease(v)
#define AUTODELETE(v)   (v)
#define PROTECT(v)      PRT(v)
#define UNPROTECT(v)    UNPRT(v)

#include <cos/Array.h>

makclass(Array, Sequence);

// vector templates
#include "./tmpl/Vector_blk.c"
#include "./tmpl/Vector_dyn.c"
#include "./tmpl/Vector_lzy.c"
#include "./tmpl/Vector_vw.c"

#include "./tmpl/Vector_acc.c"
#include "./tmpl/Vector_alg.c"
#include "./tmpl/Vector_fun.c"
#include "./tmpl/Vector_fct.c"


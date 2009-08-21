/*
 o---------------------------------------------------------------------o
 |
 | COS IntVector - basic vectors
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
 | $Id: IntVector.c,v 1.2 2009/08/21 13:04:40 ldeniau Exp $
 |
*/

#define    VECTOR_ONLY
#define INTVECTOR_ONLY

#define T     IntVector
#define TM   mIntVector
#define TP  pmIntVector
#define TN    IntVectorN
#define TF    IntVectorFix
#define TD    IntVectorDyn
#define TL    IntVectorLzy
#define TV    IntVectorView
#define TS    "int vector"
#define TE    Int

#define VS    Vector.ValueSequence.Sequence

#define VAL       I32
#define VALINT  
#define VALOBJ(v) aInt(v)

#define  valref  value
#define _valref _value

#define aTView(v,s)    aIntVectorView(v,s)
#define aTRef(v,s)     aIntVectorRef(v,s)

#define T_alloc(s)      IntVector_alloc(s)
#define TV_init(vw,v,s) IntVectorView_init(vw,v,s)

#define TOVALPTR        gintPtr
#define TOVAL(v)        gint(v)
#define VALUE(v)        v->value
#define ASSIGN(d,s)     (d = s)
#define SWAP(v1,v2)     { VAL tmp = v1; v1 = v2; v2 = tmp; }
#define EQUAL(v1,v2)    (v1 == v2 ? True : False)
#define COMPARE(v1,v2)  (v1<v2 ? Lesser : v1>v2 ? Greater : Equal)
#define RETAIN(v)       (v)
#define RELEASE(v)      (v)
#define AUTODELETE(v)   gautoDelete(v)
#define PROTECT(v)   
#define UNPROTECT(v) 

#include <cos/IntVector.h>

makclass(IntVector, Vector);

// vector templates
#include "./tmpl/Vector.c"
#include "./tmpl/Vector_dyn.c"
#include "./tmpl/Vector_lzy.c"
#include "./tmpl/Vector_vw.c"

#include "./tmpl/Vector_acc.c"
#include "./tmpl/Vector_alg.c"
#include "./tmpl/Vector_fun.c"
#include "./tmpl/Vector_fct.c"


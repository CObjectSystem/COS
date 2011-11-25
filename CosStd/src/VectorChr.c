/**
 * C Object System
 * COS ChrVector
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define CHRVECTOR_ONLY

#define T     ChrVector
#define TM   mChrVector
#define TP  pmChrVector
#define TN    ChrVectorN
#define TF    ChrVectorFix
#define TD    ChrVectorDyn
// #define TL    ChrVectorLzy
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


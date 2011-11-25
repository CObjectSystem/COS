/**
 * C Object System
 * COS CpxVector - basic vectors
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

#define CPXVECTOR_ONLY

#define T     CpxVector
#define TM   mCpxVector
#define TP  pmCpxVector
#define TN    CpxVectorN
#define TF    CpxVectorFix
#define TD    CpxVectorDyn
// #define TL    CpxVectorLzy
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
// #include "./tmpl/Vector_lzy.c"
#include "./tmpl/Vector_vw.c"

#include "./tmpl/Vector_acc.c"
#include "./tmpl/Vector_alg.c"
#include "./tmpl/Vector_fun.c"
// #include "./tmpl/Vector_fct.c"
// #include "./tmpl/Vector_vfn.c"


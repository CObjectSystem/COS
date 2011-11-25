/**
 * C Object System
 * COS LngVector
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

#define LNGVECTOR_ONLY

#define T     LngVector
#define TM   mLngVector
#define TP  pmLngVector
#define TN    LngVectorN
#define TF    LngVectorFix
#define TD    LngVectorDyn
// #define TL    LngVectorLzy
#define TV    LngVectorView
#define TW    LngVectorSubView
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
#define VALOBJ(v) aLong(v)

#define aTView(v,s)    aLngVectorView(v,s)
#define aTRef(v,s)     aLngVectorRef(v,s)

#define T_alloc(s)        LngVector_alloc(s)
#define TV_init(vw,v,s,b) LngVectorView_init(vw,v,s,b)

#define TOVALPTR        glngPtr
#define TOVAL(v)        glng(v)
#define VALUE(v)        v->value
#define EQUAL(v1,v2)    (v1 == v2)

#include <cos/LngVector.h>
#include <cos/Function.h>

makclass(LngVector, IntegralVector);

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


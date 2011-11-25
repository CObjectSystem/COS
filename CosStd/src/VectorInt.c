/**
 * C Object System
 * COS IntVector - basic vectors
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

#define INTVECTOR_ONLY

#define T     IntVector
#define TM   mIntVector
#define TP  pmIntVector
#define TN    IntVectorN
#define TF    IntVectorFix
#define TD    IntVectorDyn
// #define TL    IntVectorLzy
#define TV    IntVectorView
#define TW    IntVectorSubView
#define TS    "int vector"
#define TE    Int

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

#define VAL       I32
#define VALOBJ(v) aInt(v)

#define aTView(v,s)    aIntVectorView(v,s)
#define aTRef(v,s)     aIntVectorRef(v,s)

#define T_alloc(s)        IntVector_alloc(s)
#define TV_init(vw,v,s,b) IntVectorView_init(vw,v,s,b)

#define TOVALPTR      gintPtr
#define TOVAL(v)      gint(v)
#define VALUE(v)      v->value
#define EQUAL(v1,v2)  (v1 == v2)

#include <cos/IntVector.h>
#include <cos/Function.h>

makclass(IntVector, IntegralVector);

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


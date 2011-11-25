#ifndef COS_FUNCTION_H
#define COS_FUNCTION_H

/**
 * C Object System
 * COS Functions
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

#include <cos/Functor.h>

// ----- aliases

typedef I32 (*I32FCT0)(void);
typedef I64 (*I64FCT0)(void);
typedef F64 (*F64FCT0)(void);
typedef C64 (*C64FCT0)(void);

typedef I32 (*I32FCT1)(I32);
typedef I64 (*I64FCT1)(I64);
typedef F64 (*F64FCT1)(F64);
typedef C64 (*C64FCT1)(C64);

typedef I32 (*I32FCT2)(I32,I32);
typedef I64 (*I64FCT2)(I64,I64);
typedef F64 (*F64FCT2)(F64,F64);
typedef C64 (*C64FCT2)(C64,C64);

typedef I32 (*I32FCT3)(I32,I32,I32);
typedef I64 (*I64FCT3)(I64,I64,I64);
typedef F64 (*F64FCT3)(F64,F64,F64);
typedef C64 (*C64FCT3)(C64,C64,C64);

typedef I32 (*I32FCT4)(I32,I32,I32,I32);
typedef I64 (*I64FCT4)(I64,I64,I64,I64);
typedef F64 (*F64FCT4)(F64,F64,F64,F64);
typedef C64 (*C64FCT4)(C64,C64,C64,C64);

typedef I32 (*I32FCT5)(I32,I32,I32,I32,I32);
typedef I64 (*I64FCT5)(I64,I64,I64,I64,I64);
typedef F64 (*F64FCT5)(F64,F64,F64,F64,F64);
typedef C64 (*C64FCT5)(C64,C64,C64,C64,C64);

typedef I32 (*I32FCT6)(I32,I32,I32,I32,I32,I32);
typedef I64 (*I64FCT6)(I64,I64,I64,I64,I64,I64);
typedef F64 (*F64FCT6)(F64,F64,F64,F64,F64,F64);
typedef C64 (*C64FCT6)(C64,C64,C64,C64,C64,C64);

typedef I32 (*I32FCT7)(I32,I32,I32,I32,I32,I32,I32);
typedef I64 (*I64FCT7)(I64,I64,I64,I64,I64,I64,I64);
typedef F64 (*F64FCT7)(F64,F64,F64,F64,F64,F64,F64);
typedef C64 (*C64FCT7)(C64,C64,C64,C64,C64,C64,C64);

typedef I32 (*I32FCT8)(I32,I32,I32,I32,I32,I32,I32,I32);
typedef I64 (*I64FCT8)(I64,I64,I64,I64,I64,I64,I64,I64);
typedef F64 (*F64FCT8)(F64,F64,F64,F64,F64,F64,F64,F64);
typedef C64 (*C64FCT8)(C64,C64,C64,C64,C64,C64,C64,C64);

typedef I32 (*I32FCT9)(I32,I32,I32,I32,I32,I32,I32,I32,I32);
typedef I64 (*I64FCT9)(I64,I64,I64,I64,I64,I64,I64,I64,I64);
typedef F64 (*F64FCT9)(F64,F64,F64,F64,F64,F64,F64,F64,F64);
typedef C64 (*C64FCT9)(C64,C64,C64,C64,C64,C64,C64,C64,C64);

// ----- definitions

defclass(IntFunction , Functor    ) STR     str; endclass
defclass(IntFunction1, IntFunction) I32FCT1 fct; endclass
defclass(IntFunction2, IntFunction) I32FCT2 fct; endclass
defclass(IntFunction3, IntFunction) I32FCT3 fct; endclass
defclass(IntFunction4, IntFunction) I32FCT4 fct; endclass
defclass(IntFunction5, IntFunction) I32FCT5 fct; endclass
defclass(IntFunction6, IntFunction) I32FCT6 fct; endclass
defclass(IntFunction7, IntFunction) I32FCT7 fct; endclass
defclass(IntFunction8, IntFunction) I32FCT8 fct; endclass
defclass(IntFunction9, IntFunction) I32FCT9 fct; endclass

defclass(LngFunction , Functor    ) STR     str; endclass
defclass(LngFunction1, LngFunction) I64FCT1 fct; endclass
defclass(LngFunction2, LngFunction) I64FCT2 fct; endclass
defclass(LngFunction3, LngFunction) I64FCT3 fct; endclass
defclass(LngFunction4, LngFunction) I64FCT4 fct; endclass
defclass(LngFunction5, LngFunction) I64FCT5 fct; endclass
defclass(LngFunction6, LngFunction) I64FCT6 fct; endclass
defclass(LngFunction7, LngFunction) I64FCT7 fct; endclass
defclass(LngFunction8, LngFunction) I64FCT8 fct; endclass
defclass(LngFunction9, LngFunction) I64FCT9 fct; endclass

defclass(FltFunction , Functor    ) STR     str; endclass
defclass(FltFunction1, FltFunction) F64FCT1 fct; endclass
defclass(FltFunction2, FltFunction) F64FCT2 fct; endclass
defclass(FltFunction3, FltFunction) F64FCT3 fct; endclass
defclass(FltFunction4, FltFunction) F64FCT4 fct; endclass
defclass(FltFunction5, FltFunction) F64FCT5 fct; endclass
defclass(FltFunction6, FltFunction) F64FCT6 fct; endclass
defclass(FltFunction7, FltFunction) F64FCT7 fct; endclass
defclass(FltFunction8, FltFunction) F64FCT8 fct; endclass
defclass(FltFunction9, FltFunction) F64FCT9 fct; endclass

defclass(CpxFunction , Functor    ) STR     str; endclass
defclass(CpxFunction1, CpxFunction) C64FCT1 fct; endclass
defclass(CpxFunction2, CpxFunction) C64FCT2 fct; endclass
defclass(CpxFunction3, CpxFunction) C64FCT3 fct; endclass
defclass(CpxFunction4, CpxFunction) C64FCT4 fct; endclass
defclass(CpxFunction5, CpxFunction) C64FCT5 fct; endclass
defclass(CpxFunction6, CpxFunction) C64FCT6 fct; endclass
defclass(CpxFunction7, CpxFunction) C64FCT7 fct; endclass
defclass(CpxFunction8, CpxFunction) C64FCT8 fct; endclass
defclass(CpxFunction9, CpxFunction) C64FCT9 fct; endclass

// ----- automatic constructors

#define aIntFunction(F,...) aFunctionT(Int,F,COS_PP_NARG(__VA_ARGS__))
#define aLngFunction(F,...) aFunctionT(Lng,F,COS_PP_NARG(__VA_ARGS__))
#define aFltFunction(F,...) aFunctionT(Flt,F,COS_PP_NARG(__VA_ARGS__))
#define aCpxFunction(F,...) aFunctionT(Cpx,F,COS_PP_NARG(__VA_ARGS__))

// --- shortcuts

#ifndef COS_NOSHORTCUT
#define aIntFct(...)  aIntFunction (__VA_ARGS__)
#define aLngFct(...)  aLngFunction (__VA_ARGS__)
#define aFltFct(...)  aFltFunction (__VA_ARGS__)
#define aCpxFct(...)  aCpxFunction (__VA_ARGS__)
#endif

/***********************************************************
 * Implementation (private)
 */

#define aFunctionT(T,F,N) \
  ((OBJ)&(struct COS_PP_CAT3(T,Function,N)) { \
   {{ cos_object_auto(COS_PP_CAT3(T,Function,N)) }, COS_PP_STR(F) }, (F) })

#endif // COS_FUNCTION_H

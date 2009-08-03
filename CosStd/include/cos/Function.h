#ifndef COS_FUNCTION_H
#define COS_FUNCTION_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Functions
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
 | $Id: Function.h,v 1.8 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Functor.h>

// ----- aliases

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

// ----- definitions

defclass(GenFunction ,Functor    ) FUNC    fct; endclass

defclass(IntFunction ,Functor    )              endclass
defclass(IntFunction1,IntFunction) I32FCT1 fct; endclass
defclass(IntFunction2,IntFunction) I32FCT2 fct; endclass
defclass(IntFunction3,IntFunction) I32FCT3 fct; endclass
defclass(IntFunction4,IntFunction) I32FCT4 fct; endclass
defclass(IntFunction5,IntFunction) I32FCT5 fct; endclass

defclass(LngFunction ,Functor    )              endclass
defclass(LngFunction1,LngFunction) I64FCT1 fct; endclass
defclass(LngFunction2,LngFunction) I64FCT2 fct; endclass
defclass(LngFunction3,LngFunction) I64FCT3 fct; endclass
defclass(LngFunction4,LngFunction) I64FCT4 fct; endclass
defclass(LngFunction5,LngFunction) I64FCT5 fct; endclass

defclass(FltFunction ,Functor    )              endclass
defclass(FltFunction1,FltFunction) F64FCT1 fct; endclass
defclass(FltFunction2,FltFunction) F64FCT2 fct; endclass
defclass(FltFunction3,FltFunction) F64FCT3 fct; endclass
defclass(FltFunction4,FltFunction) F64FCT4 fct; endclass
defclass(FltFunction5,FltFunction) F64FCT5 fct; endclass

defclass(CpxFunction ,Functor    )              endclass
defclass(CpxFunction1,CpxFunction) C64FCT1 fct; endclass
defclass(CpxFunction2,CpxFunction) C64FCT2 fct; endclass
defclass(CpxFunction3,CpxFunction) C64FCT3 fct; endclass
defclass(CpxFunction4,CpxFunction) C64FCT4 fct; endclass
defclass(CpxFunction5,CpxFunction) C64FCT5 fct; endclass

// ----- automatic constructors

#define aGenFunction(F)     aFunctionT(Gen,F,                        )
#define aIntFunction(F,...) aFunctionT(Int,F,COS_PP_NARG(__VA_ARGS__))
#define aLngFunction(F,...) aFunctionT(Lng,F,COS_PP_NARG(__VA_ARGS__))
#define aFltFunction(F,...) aFunctionT(Flt,F,COS_PP_NARG(__VA_ARGS__))
#define aCpxFunction(F,...) aFunctionT(Cpx,F,COS_PP_NARG(__VA_ARGS__))

#define aFunctionT(T,F,N) \
  ((OBJ)&(struct COS_PP_CAT3(T,Function,N)) { \
   {{ cos_object_auto(COS_PP_CAT3(T,Function,N)) }}, \
   (F) })

#endif // COS_FUNCTION_H

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
 | $Id: Function.h,v 1.4 2009/01/22 16:45:07 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

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

defclass(Function) endclass

defclass(GenFunction ,Function) FUNC    fct; endclass

defclass(IntFunction1,Function) I32FCT1 fct; endclass
defclass(IntFunction2,Function) I32FCT2 fct; endclass
defclass(IntFunction3,Function) I32FCT3 fct; endclass
defclass(IntFunction4,Function) I32FCT4 fct; endclass
defclass(IntFunction5,Function) I32FCT5 fct; endclass

defclass(LngFunction1,Function) I64FCT1 fct; endclass
defclass(LngFunction2,Function) I64FCT2 fct; endclass
defclass(LngFunction3,Function) I64FCT3 fct; endclass
defclass(LngFunction4,Function) I64FCT4 fct; endclass
defclass(LngFunction5,Function) I64FCT5 fct; endclass

defclass(FltFunction1,Function) F64FCT1 fct; endclass
defclass(FltFunction2,Function) F64FCT2 fct; endclass
defclass(FltFunction3,Function) F64FCT3 fct; endclass
defclass(FltFunction4,Function) F64FCT4 fct; endclass
defclass(FltFunction5,Function) F64FCT5 fct; endclass

defclass(CpxFunction1,Function) C64FCT1 fct; endclass
defclass(CpxFunction2,Function) C64FCT2 fct; endclass
defclass(CpxFunction3,Function) C64FCT3 fct; endclass
defclass(CpxFunction4,Function) C64FCT4 fct; endclass
defclass(CpxFunction5,Function) C64FCT5 fct; endclass

// ----- automatic constructors

#define aGenFunction(F)     aFunctionT(Gen,F,                        )
#define aIntFunction(F,...) aFunctionT(Int,F,COS_PP_NARG(__VA_ARGS__))
#define aLngFunction(F,...) aFunctionT(Lng,F,COS_PP_NARG(__VA_ARGS__))
#define aFltFunction(F,...) aFunctionT(Flt,F,COS_PP_NARG(__VA_ARGS__))
#define aCpxFunction(F,...) aFunctionT(Cpx,F,COS_PP_NARG(__VA_ARGS__))

#define aFunctionT(T,F,N) \
  ((OBJ)&(struct COS_PP_CAT3(T,Function,N)) { \
   {{{ COS_CLS_NAME(COS_PP_CAT3(T,Function,N)).Behavior.id, COS_RC_AUTO }}}, (F) })

#endif // COS_FUNCTION_H

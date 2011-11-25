#ifndef COS_NUMBER_H
#define COS_NUMBER_H

/**
 * C Object System
 * COS Number
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

#include <cos/Value.h>

// ----- numbers

defclass(Number  , Value   )            endclass

defclass(Integral, Number  )            endclass
defclass(Int     , Integral) I32 value; endclass
defclass(Long    , Integral) I64 value; endclass
defclass(Char    , Int     )            endclass
defclass(Short   , Int     )            endclass

defclass(Floating, Number  )            endclass
defclass(Float   , Floating) F64 value; endclass
defclass(Complex , Floating) C64 value; endclass

// ----- automatic constructors

#define aChar(a)        ( (OBJ)atChar   (a) )
#define aShort(a)       ( (OBJ)atShort  (a) )
#define aInt(a)         ( (OBJ)atInt    (a) )
#define aLong(a)        ( (OBJ)atLong   (a) )
#define aFloat(a)       ( (OBJ)atFloat  (a) )
#define aComplex(...)   ( (OBJ)atComplex(__VA_ARGS__) )

#define atChar(a)       atNumber2(Char   , a)
#define atShort(a)      atNumber2(Short  , a)
#define atInt(a)        atNumber (Int    , a)
#define atLong(a)       atNumber (Long   , a)
#define atFloat(a)      atNumber (Float  , a)
#define atComplex(...)  COS_PP_CAT_NARG(atComplex,__VA_ARGS__)(__VA_ARGS__)
#define atComplex1(a)   atNumber (Complex, a)
#define atComplex2(r,i) atNumber (Complex, complex_make(r,i))

// --- shortcuts

#ifndef COS_NOSHORTCUT

#undef  aInt
#define aInt_(a)   ( (OBJ)atInt(a) )

#define aChr(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aChar   ))
#define aSht(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aShort  ))
#define aInt(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aInt_   ))
#define aLng(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aLong   ))
#define aFlt(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aFloat  ))
#define aCpx(...)  COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__),aComplex))

#define aArrChr(...)  aArray(aChr(__VA_ARGS__))
#define aArrSht(...)  aArray(aSht(__VA_ARGS__))
#define aArrInt(...)  aArray(aInt(__VA_ARGS__))
#define aArrLng(...)  aArray(aLng(__VA_ARGS__))
#define aArrFlt(...)  aArray(aFlt(__VA_ARGS__))
#define aArrCpx(...)  aArray(aCpx(__VA_ARGS__))

#endif

/***********************************************************
 * Implementation (private)
 */

#define atNumber(T,a) \
  ( &(struct T){ {{{ cos_object_auto(T) }}}, (a) } )

#define atNumber2(T,a) \
  ( &(struct T){{ {{{ cos_object_auto(T) }}}, (a) }} )

// ---- float inliners

F64  float_ipow    (F64,I32);
BOOL float_equal   (F64,F64);
BOOL float_equalEps(F64,F64,F64);

static inline BOOL
float_notEqual(F64 x, F64 y)
{
  return !float_equal(x,y);
}

static inline BOOL
float_notEqualEps(F64 x, F64 y, F64 e)
{
  return !float_equalEps(x,y,e);
}

// ---- complex inliners

C64  complex_ipow    (C64,I32);
BOOL complex_equal   (C64,C64);
BOOL complex_equalEps(C64,C64,F64);

static inline C64
complex_make(F64 x, F64 y)
{
  return *(F64[]){ x, y };
}

static inline F64
complex_real(C64 x)
{
  return ((F64*)&x)[0];
}

static inline F64
complex_imag(C64 x)
{
  return ((F64*)&x)[1];
}

static inline BOOL
complex_notEqual(C64 x, C64 y)
{
  return !complex_equal(x,y);
}

static inline BOOL
complex_notEqualEps(C64 x, C64 y, F64 e)
{
  return !complex_equalEps(x,y,e);
}

#endif // COS_NUMBER_H

#ifndef COS_NUMBER_H
#define COS_NUMBER_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Number
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
 | $Id: Number.h,v 1.9 2009/07/24 12:36:26 ldeniau Exp $
 |
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
#define atComplex1(a)   atNumber (Complex, a)
#define atComplex2(r,i) atNumber (Complex, complex_make(r,i))
#define atComplex(...)  COS_PP_CAT_NARG(atComplex,__VA_ARGS__)(__VA_ARGS__)

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aChr(...)  aChar   (__VA_ARGS__)
#define aSht(...)  aShort  (__VA_ARGS__)
#define aLng(...)  aLong   (__VA_ARGS__)
#define aFlt(...)  aFloat  (__VA_ARGS__)
#define aCpx(...)  aComplex(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

#define atNumber(T,a) \
  ( &(struct T){ {{{ cos_object_auto(T) }}}, (a) } )

#define atNumber2(T,a) \
  ( &(struct T){{ {{{ cos_object_auto(T) }}}, (a) }} )

// ---- float inliners

static inline BOOL
float_isEqual(FLOAT x, FLOAT y)
{
  return x <= y && x >= y;
}

// ---- complex inliners

static inline COMPLEX
complex_make(FLOAT x, FLOAT y)
{
  return *(FLOAT[]){ x, y };
}

static inline FLOAT
complex_real(COMPLEX x)
{
  return ((FLOAT*)&x)[0];
}

static inline FLOAT
complex_imag(COMPLEX x)
{
  return ((FLOAT*)&x)[1];
}

static inline BOOL
complex_isEqual(COMPLEX x, COMPLEX y)
{
  return float_isEqual(complex_real(x), complex_real(y)) &&
         float_isEqual(complex_imag(x), complex_imag(y));
}

#endif // COS_NUMBER_H

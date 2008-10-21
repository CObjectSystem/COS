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
 | $Id: Number.h,v 1.3 2008/10/21 15:43:42 ldeniau Exp $
 |
*/

#include <cos/Value.h>

// ----- number

defclass(Number, Value)
endclass

defclass(Integral, Number)
endclass

defclass(Floating, Number)
endclass

// ----- integral

defclass(Int, Integral)
  INT value;
endclass

defclass(Long, Integral)
  LONG value;
endclass

defclass(Char , Int) endclass
defclass(Short, Int) endclass

// ----- floating

defclass(Float, Floating)
  FLOAT value;
endclass

defclass(Complex, Floating)
  COMPLEX value;
endclass

// ----- automatic constructors

#define aChar(C)  ( (OBJ)atChar(C) )
#define atChar(C) ( &(struct Char) {{ \
        {{{{{ COS_CLS_NAME(Char).Behavior.id, COS_RC_AUTO }}}}}, (I8)(C) }} )

#define aShort(S)  ( (OBJ)atShort(S) )
#define atShort(S) ( &(struct Short) {{ \
        {{{{{ COS_CLS_NAME(Short).Behavior.id, COS_RC_AUTO }}}}}, (I16)(S) }} )

#define aInt(I)  ( (OBJ)atInt(I) )
#define atInt(I) ( &(struct Int) { \
        {{{{{ COS_CLS_NAME(Int).Behavior.id, COS_RC_AUTO }}}}}, (I) } )

#define aLong(L)  ( (OBJ)atLong(L) )
#define atLong(L) ( &(struct Long) { \
        {{{{{ COS_CLS_NAME(Long).Behavior.id, COS_RC_AUTO }}}}}, (L) } )

#define aFloat(R)  ( (OBJ)atFloat(R) )
#define atFloat(R) ( &(struct Float) { \
        {{{{{ COS_CLS_NAME(Float).Behavior.id, COS_RC_AUTO }}}}}, (R) } )

#define aComplex(...)  ( (OBJ)atComplex(__VA_ARGS__) )
#define atComplex(...) COS_PP_CAT_NARG(atComplex,__VA_ARGS__)(__VA_ARGS__)

#define atComplex1(C) ( &(struct Complex) { \
        {{{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}}, (C) } )
#define atComplex2(R,I) ( &(struct Complex) { \
        {{{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}}, \
         *(FLOAT[]) {(R),(I)} } )

// ---- inliners

static inline BOOL
float_equal(FLOAT x, FLOAT y)
{
  return x <= y && x >= y;
  COS_UNUSED(float_equal);
}

static inline COMPLEX
complex_make(FLOAT x, FLOAT y)
{
  return *(FLOAT[]){ x, y };
  COS_UNUSED(complex_make);
}

static inline FLOAT
complex_real(COMPLEX x)
{
  return ((FLOAT*)&x)[0];
  COS_UNUSED(complex_real);
}

static inline FLOAT
complex_imag(COMPLEX x)
{
  return ((FLOAT*)&x)[1];
  COS_UNUSED(complex_imag);
}

static inline BOOL
complex_equal(COMPLEX x, COMPLEX y)
{
  return float_equal(complex_real(x), complex_real(y)) &&
         float_equal(complex_imag(x), complex_imag(y));
  COS_UNUSED(complex_equal);
}

#endif // COS_NUMBER_H

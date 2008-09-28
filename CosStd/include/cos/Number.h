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
 | $Id: Number.h,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
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

defclass(Double, Floating)
  DOUBLE value;
endclass

defclass(Complex, Floating)
  COMPLEX value;
endclass

// ----- automatic constructors

#define aChr(value)  ( (OBJ)atChr(value) )
#define atChr(value) ( &(struct Char) {{ \
        {{{{{ COS_CLS_NAME(Char).Behavior.id, COS_RC_AUTO }}}}}, \
         (I8)(value) }} )

#define aSht(value)  ( (OBJ)atSht(value) )
#define atSht(value) ( &(struct Short) {{ \
        {{{{{ COS_CLS_NAME(Short).Behavior.id, COS_RC_AUTO }}}}}, \
         (I16)(value) }} )

#define aInt(value)  ( (OBJ)atInt(value) )
#define atInt(value) ( &(struct Int) { \
        {{{{{ COS_CLS_NAME(Int).Behavior.id, COS_RC_AUTO }}}}}, \
         (value) } )

#define aLng(value)  ( (OBJ)atLng(value) )
#define atLng(value) ( &(struct Long) { \
        {{{{{ COS_CLS_NAME(Long).Behavior.id, COS_RC_AUTO }}}}}, \
         (value) } )

#define aDbl(value)  ( (OBJ)atDbl(value) )
#define atDbl(value) ( &(struct Double) { \
        {{{{{ COS_CLS_NAME(Double).Behavior.id, COS_RC_AUTO }}}}}, \
         (value) } )

#define aCpx(...)  ( (OBJ)atCpx(__VA_ARGS__) )
#define atCpx(...) COS_PP_CAT_NARG(atCpx,__VA_ARGS__)(__VA_ARGS__)

#define atCpx1(value) ( &(struct Complex) { \
        {{{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}}, \
         (value) } )
#define atCpx2(real,imag) ( &(struct Complex) { \
        {{{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}}, \
         *(DOUBLE[]) {(real),(imag)} } )

// ---- inliners

static inline BOOL
dbl_equal(DOUBLE x, DOUBLE y)
{
  return x <= y && x >= y;
  COS_UNUSED(dbl_equal);
}

static inline COMPLEX
cpx_make(DOUBLE x, DOUBLE y)
{
  return *(DOUBLE[]){ x, y };
  COS_UNUSED(cpx_make);
}

static inline DOUBLE
cpx_real(COMPLEX x)
{
  return ((DOUBLE*)&x)[0];
  COS_UNUSED(cpx_real);
}

static inline DOUBLE
cpx_imag(COMPLEX x)
{
  return ((DOUBLE*)&x)[1];
  COS_UNUSED(cpx_imag);
}

static inline BOOL
cpx_equal(COMPLEX x, COMPLEX y)
{
  return dbl_equal(cpx_real(x), cpx_real(y)) &&
         dbl_equal(cpx_imag(x), cpx_imag(y));
  COS_UNUSED(cpx_equal);
}

#endif // COS_NUMBER_H

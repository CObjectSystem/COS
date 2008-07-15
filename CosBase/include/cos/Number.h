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
 | $Id: Number.h,v 1.3 2008/07/15 08:00:46 ldeniau Exp $
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
  S32 val;
endclass

defclass(UInt, Integral)
  U32 val;
endclass

defclass(Long, Integral)
  S64 val;
endclass

defclass(ULong, Integral)
  U64 val;
endclass

defclass(Char ,   Int) endclass
defclass(Short,   Int) endclass
defclass(UChar,  UInt) endclass
defclass(UShort, UInt) endclass

// ----- floating

defclass(Double, Floating)
  double val;
endclass

defclass(Complex, Floating)
  COMPLEX val;
endclass

// ----- automatic constructors

#define aChr(val) ( (OBJ)&(struct Char) {{ \
        {{{{{ COS_CLS_NAME(Char).Behavior.id, COS_RC_AUTO }}}}}, \
         (S8)(val) }} )

#define aUChr(val) ( (OBJ)&(struct UChar) {{ \
        {{{{{ COS_CLS_NAME(UChar).Behavior.id, COS_RC_AUTO }}}}}, \
         (U8)(val) }} )

#define aSht(val) ( (OBJ)&(struct Short) {{ \
        {{{{{ COS_CLS_NAME(Short).Behavior.id, COS_RC_AUTO }}}}}, \
         (S16)(val) }} )

#define aUSht(val) ( (OBJ)&(struct UShort) {{ \
        {{{{{ COS_CLS_NAME(UShort).Behavior.id, COS_RC_AUTO }}}}}, \
         (U16)(val) }} )

#define aInt(val) ( (OBJ)&(struct Int) { \
        {{{{{ COS_CLS_NAME(Int).Behavior.id, COS_RC_AUTO }}}}}, \
         (val) } )

#define aUInt(val) ( (OBJ)&(struct UInt) { \
        {{{{{ COS_CLS_NAME(UInt).Behavior.id, COS_RC_AUTO }}}}}, \
         (val) } )

#define aLng(val) ( (OBJ)&(struct Long) { \
        {{{{{ COS_CLS_NAME(Long).Behavior.id, COS_RC_AUTO }}}}}, \
         (val) } )

#define aULng(val) ( (OBJ)&(struct ULong) { \
        {{{{{ COS_CLS_NAME(ULong).Behavior.id, COS_RC_AUTO }}}}}, \
         (val) } )

#define aDbl(val) ( (OBJ)&(struct Double) { \
        {{{{{ COS_CLS_NAME(Double).Behavior.id, COS_RC_AUTO }}}}}, \
         (val) } )

#define aCpx(...) \
        COS_PP_CAT_NARG(aCpx,__VA_ARGS__)(__VA_ARGS__)

#define aCpx1(val) ( (OBJ)&(struct Complex) { \
        {{{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}}, \
         (val) } )

#define aCpx2(re,im) ( (OBJ)&(struct Complex) { \
        {{{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}}, \
         *(double[]) {(re),(im)} } )

// ---- inliners

static inline BOOL
dbl_equal(double x, double y)
{
  return x <= y && x >= y;
  COS_UNUSED(dbl_equal);
}

static inline COMPLEX
cpx_make(double x, double y)
{
  return *(double[]){ x, y };
  COS_UNUSED(cpx_make);
}

static inline double
cpx_real(COMPLEX x)
{
  return ((double*)&x)[0];
  COS_UNUSED(cpx_real);
}

static inline double
cpx_imag(COMPLEX x)
{
  return ((double*)&x)[1];
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

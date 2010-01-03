/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - numerics
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
 | $Id: Vector_num.c,v 1.3 2010/01/03 14:54:33 ldeniau Exp $
 |
*/

#include <cos/ShtVector.h>
#include <cos/IntVector.h>
#include <cos/LngVector.h>
#include <cos/FltVector.h>
#include <cos/CpxVector.h>
#include <cos/Number.h>

#include <cos/gen/numop.h>
#include <cos/gen/object.h>

// ----- absolute

#undef  DEFMETHOD
#define DEFMETHOD(T, V) \
\
defmethod(OBJ, gabsolute, T) \
  V  *val   = self->value; \
  I32 val_s = self->stride; \
  V  *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    if (*val < 0) *val = -*val; \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod

DEFMETHOD(ShtVector, I16)
DEFMETHOD(IntVector, I32)
DEFMETHOD(LngVector, I64)
DEFMETHOD(FltVector, F64)


// ----- negate

#undef  DEFMETHOD
#define DEFMETHOD(T, V) \
\
defmethod(OBJ, gnegate, T) \
  V  *val   = self->value; \
  I32 val_s = self->stride; \
  V  *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    *val = -*val; \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod

DEFMETHOD(ShtVector, I16)
DEFMETHOD(IntVector, I32)
DEFMETHOD(LngVector, I64)
DEFMETHOD(FltVector, F64)
DEFMETHOD(CpxVector, C64)

// ----- square

#undef  DEFMETHOD
#define DEFMETHOD(T, V) \
\
defmethod(OBJ, gsquare, T) \
  V  *val   = self->value; \
  I32 val_s = self->stride; \
  V  *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    *val *= *val; \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod

DEFMETHOD(ShtVector, I16)
DEFMETHOD(IntVector, I32)
DEFMETHOD(LngVector, I64)
DEFMETHOD(FltVector, F64)
DEFMETHOD(CpxVector, C64)

// ----- invert

#undef  DEFMETHOD
#define DEFMETHOD(T, V) \
\
defmethod(OBJ, ginvert, T) \
  V  *val   = self->value; \
  I32 val_s = self->stride; \
  V  *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    *val = 1 / *val; \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod

DEFMETHOD(FltVector, F64)
DEFMETHOD(CpxVector, C64)

// ----- addTo, subTo, mulTo, divTo, modulo

#undef  DEFMETHOD
#define DEFMETHOD(MTH,T1,V1,OP,T2,V2) \
defmethod(OBJ, MTH, T1, T2) \
  PRE \
    test_assert(self->size == self2->size, "incompatible vector sizes"); \
  BODY \
    V1 *dst   = self->value; \
    I32 dst_s = self->stride; \
    V2 *src   = self2->value; \
    I32 src_s = self2->stride; \
    V1 *end   = self->value + self->size*self->stride; \
\
    while (dst != end) { \
      *dst OP *src; \
      dst += dst_s; \
      src += src_s; \
    } \
\
    retmethod(_1); \
endmethod

DEFMETHOD(gaddTo, ShtVector, I16, +=, ShtVector, I16)
DEFMETHOD(gaddTo, IntVector, I32, +=, ShtVector, I16)
DEFMETHOD(gaddTo, IntVector, I32, +=, IntVector, I32)
DEFMETHOD(gaddTo, LngVector, I64, +=, ShtVector, I16)
DEFMETHOD(gaddTo, LngVector, I64, +=, IntVector, I32)
DEFMETHOD(gaddTo, LngVector, I64, +=, LngVector, I64)
DEFMETHOD(gaddTo, FltVector, F64, +=, ShtVector, I16)
DEFMETHOD(gaddTo, FltVector, F64, +=, IntVector, I32)
DEFMETHOD(gaddTo, FltVector, F64, +=, LngVector, I64)
DEFMETHOD(gaddTo, FltVector, F64, +=, FltVector, F64)
DEFMETHOD(gaddTo, CpxVector, C64, +=, ShtVector, I16)
DEFMETHOD(gaddTo, CpxVector, C64, +=, IntVector, I32)
DEFMETHOD(gaddTo, CpxVector, C64, +=, LngVector, I64)
DEFMETHOD(gaddTo, CpxVector, C64, +=, FltVector, F64)
DEFMETHOD(gaddTo, CpxVector, C64, +=, CpxVector, C64)

DEFMETHOD(gsubTo, ShtVector, I16, -=, ShtVector, I16)
DEFMETHOD(gsubTo, IntVector, I32, -=, ShtVector, I16)
DEFMETHOD(gsubTo, IntVector, I32, -=, IntVector, I32)
DEFMETHOD(gsubTo, LngVector, I64, -=, ShtVector, I16)
DEFMETHOD(gsubTo, LngVector, I64, -=, IntVector, I32)
DEFMETHOD(gsubTo, LngVector, I64, -=, LngVector, I64)
DEFMETHOD(gsubTo, FltVector, F64, -=, ShtVector, I16)
DEFMETHOD(gsubTo, FltVector, F64, -=, IntVector, I32)
DEFMETHOD(gsubTo, FltVector, F64, -=, LngVector, I64)
DEFMETHOD(gsubTo, FltVector, F64, -=, FltVector, F64)
DEFMETHOD(gsubTo, CpxVector, C64, -=, ShtVector, I16)
DEFMETHOD(gsubTo, CpxVector, C64, -=, IntVector, I32)
DEFMETHOD(gsubTo, CpxVector, C64, -=, LngVector, I64)
DEFMETHOD(gsubTo, CpxVector, C64, -=, FltVector, F64)
DEFMETHOD(gsubTo, CpxVector, C64, -=, CpxVector, C64)

DEFMETHOD(gmulBy, ShtVector, I16, *=, ShtVector, I16)
DEFMETHOD(gmulBy, IntVector, I32, *=, ShtVector, I16)
DEFMETHOD(gmulBy, IntVector, I32, *=, IntVector, I32)
DEFMETHOD(gmulBy, LngVector, I64, *=, ShtVector, I16)
DEFMETHOD(gmulBy, LngVector, I64, *=, IntVector, I32)
DEFMETHOD(gmulBy, LngVector, I64, *=, LngVector, I64)
DEFMETHOD(gmulBy, FltVector, F64, *=, ShtVector, I16)
DEFMETHOD(gmulBy, FltVector, F64, *=, IntVector, I32)
DEFMETHOD(gmulBy, FltVector, F64, *=, LngVector, I64)
DEFMETHOD(gmulBy, FltVector, F64, *=, FltVector, F64)
DEFMETHOD(gmulBy, CpxVector, C64, *=, ShtVector, I16)
DEFMETHOD(gmulBy, CpxVector, C64, *=, IntVector, I32)
DEFMETHOD(gmulBy, CpxVector, C64, *=, LngVector, I64)
DEFMETHOD(gmulBy, CpxVector, C64, *=, FltVector, F64)
DEFMETHOD(gmulBy, CpxVector, C64, *=, CpxVector, C64)

DEFMETHOD(gdivBy, ShtVector, I16, /=, ShtVector, I16)
DEFMETHOD(gdivBy, IntVector, I32, /=, ShtVector, I16)
DEFMETHOD(gdivBy, IntVector, I32, /=, IntVector, I32)
DEFMETHOD(gdivBy, LngVector, I64, /=, ShtVector, I16)
DEFMETHOD(gdivBy, LngVector, I64, /=, IntVector, I32)
DEFMETHOD(gdivBy, LngVector, I64, /=, LngVector, I64)
DEFMETHOD(gdivBy, FltVector, F64, /=, ShtVector, I16)
DEFMETHOD(gdivBy, FltVector, F64, /=, IntVector, I32)
DEFMETHOD(gdivBy, FltVector, F64, /=, LngVector, I64)
DEFMETHOD(gdivBy, FltVector, F64, /=, FltVector, F64)
DEFMETHOD(gdivBy, CpxVector, C64, /=, ShtVector, I16)
DEFMETHOD(gdivBy, CpxVector, C64, /=, IntVector, I32)
DEFMETHOD(gdivBy, CpxVector, C64, /=, LngVector, I64)
DEFMETHOD(gdivBy, CpxVector, C64, /=, FltVector, F64)
DEFMETHOD(gdivBy, CpxVector, C64, /=, CpxVector, C64)

DEFMETHOD(gmodulo, ShtVector, I16, %=, ShtVector, I16)
DEFMETHOD(gmodulo, IntVector, I32, %=, ShtVector, I16)
DEFMETHOD(gmodulo, IntVector, I32, %=, IntVector, I32)
DEFMETHOD(gmodulo, LngVector, I64, %=, ShtVector, I16)
DEFMETHOD(gmodulo, LngVector, I64, %=, IntVector, I32)
DEFMETHOD(gmodulo, LngVector, I64, %=, LngVector, I64)

// ----- power

defmethod(OBJ, gpower, FltVector, Int)
  F64 *val    = self->value;
  I32  val_s  = self->stride;
  F64 *end    = self->value + self->size*self->stride;

  while (val != end) {
    *val = float_ipow(*val,self2->value);
    val += val_s;
  }
  
  retmethod(_1);
endmethod

defmethod(OBJ, gpower, CpxVector, Int)
  C64 *val    = self->value;
  I32  val_s  = self->stride;
  C64 *end    = self->value + self->size*self->stride;

  while (val != end) {
    *val = complex_ipow(*val,self2->value);
    val += val_s;
  }
  
  retmethod(_1);
endmethod

// ----- abs

defmethod(OBJ, gabs, Vector)
  retmethod(gabsolute(gautoDelete(gclone(_1))));
endmethod

// ----- neg

defmethod(OBJ, gneg, Vector)
  retmethod(gnegate(gautoDelete(gclone(_1))));
endmethod

// ----- sqr

defmethod(OBJ, gsqr, Vector)
  retmethod(gsquare(gautoDelete(gclone(_1))));
endmethod

// ----- inv

defmethod(OBJ, ginv, FloatingVector)
  retmethod(ginvert(gautoDelete(gclone(_1))));
endmethod

// ----- add

defmethod(OBJ, gadd, Vector, Vector)
  retmethod(gaddTo(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gadd, IntegralVector, LngVector)
  retmethod(gaddTo(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, IntegralVector, FloatingVector)
  retmethod(gaddTo(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, FloatingVector, CpxVector)
  retmethod(gaddTo(gautoDelete(gclone(_2)),_1));
endmethod

// ----- sub

defmethod(OBJ, gsub, Vector, Vector)
  retmethod(gsubTo(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gsub, IntegralVector, LngVector)
  retmethod(gnegate(gsubTo(gautoDelete(gclone(_2)),_1)));
endmethod

defmethod(OBJ, gsub, IntegralVector, FloatingVector)
  retmethod(gnegate(gsubTo(gautoDelete(gclone(_2)),_1)));
endmethod

defmethod(OBJ, gsub, FloatingVector, CpxVector)
  retmethod(gnegate(gsubTo(gautoDelete(gclone(_2)),_1)));
endmethod

// ----- mul

defmethod(OBJ, gmul, Vector, Vector)
  retmethod(gmulBy(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gmul, IntegralVector, LngVector)
  retmethod(gmulBy(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, IntegralVector, FloatingVector)
  retmethod(gmulBy(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, FloatingVector, CpxVector)
  retmethod(gmulBy(gautoDelete(gclone(_2)),_1));
endmethod

// ----- div

defmethod(OBJ, gdiv, Vector, Vector)
  retmethod(gdivBy(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gdiv, IntegralVector, LngVector)
  retmethod(gmulBy(ginvert(gautoDelete(gclone(_2))),_1));
endmethod

defmethod(OBJ, gdiv, IntegralVector, FloatingVector)
  retmethod(gmulBy(ginvert(gautoDelete(gclone(_2))),_1));
endmethod

defmethod(OBJ, gdiv, FloatingVector, CpxVector)
  retmethod(gmulBy(ginvert(gautoDelete(gclone(_2))),_1));
endmethod

// ----- pow

defmethod(OBJ, gpow, FloatingVector, Int)
  retmethod(gpower(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gpow, FloatingVector, Floating)
  retmethod(gpower(gautoDelete(gclone(_1)),_2));
endmethod

// ----- mod

defmethod(OBJ, gmod, IntegralVector, Integral)
  retmethod(gmodulo(gautoDelete(gclone(_1)),_2));
endmethod


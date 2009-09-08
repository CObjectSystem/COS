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
 | $Id: Vector_flt.c,v 1.3 2009/09/08 00:49:44 ldeniau Exp $
 |
*/

#include <cos/FltVector.h>
#include <cos/CpxVector.h>
#include <cos/Number.h>
#include <cos/Function.h>

#include <cos/gen/object.h>
#include <cos/gen/operator.h>
#include <cos/gen/floatop.h>
#include <cos/gen/vectop.h>
#include <cos/gen/value.h>

#include <math.h>
#include <complex.h>

// ----- sum (Kahan Formula)

#undef  DEFMETHOD
#define DEFMETHOD(T,E,O) \
\
defmethod(OBJ, gsum, T) \
  E  *val   = self->value; \
  I32 val_s = self->stride; \
  E  *end   = self->value + self->size*self->stride; \
  E c, s, t, v, y; \
\
  s = c = 0; \
  while (val != end) { \
    v = *val; \
    y = v - c; \
    t = s + y; \
    c = (t - s) - y; \
    s = t; \
    val += val_s; \
  } \
\
  retmethod(gautoDelete(O(s))); \
endmethod

DEFMETHOD(FltVector, F64, aFloat  )
DEFMETHOD(CpxVector, C64, aComplex)

// ----- mapSum

#undef  DEFMETHOD
#define DEFMETHOD(T,E,TF,F,O) \
\
defmethod(OBJ, gmapSum, TF, T) \
  E  *val   = self2->value; \
  I32 val_s = self2->stride; \
  E  *end   = self2->value + self2->size*self2->stride; \
  F   fct   = self ->fct; \
  E c, s, t, v, y; \
\
  s = c = 0; \
  while (val != end) { \
    v = fct(*val); \
    y = v - c; \
    t = s + y; \
    c = (t - s) - y; \
    s = t; \
    val += val_s; \
  } \
\
  retmethod(gautoDelete(O(s))); \
endmethod

DEFMETHOD(FltVector, F64, FltFunction1, F64FCT1, aFloat  )
DEFMETHOD(CpxVector, C64, CpxFunction1, C64FCT1, aComplex)

// ----- mapSum2

#undef  DEFMETHOD
#define DEFMETHOD(T,E,TF,F,O) \
\
defmethod(OBJ, gmapSum2, TF, T, T) \
  PRE \
    test_assert(self2->size == self3->size, "incompatible vector sizes"); \
\
  BODY \
    E  *val    = self2->value; \
    I32 val_s  = self2->stride; \
    E  *end    = self2->value + self2->size*self2->stride; \
    E  *val2   = self3->value; \
    I32 val2_s = self3->stride; \
    F   fct    = self ->fct; \
    E c, s, t, v, y; \
\
    s = c = 0; \
    while (val != end) { \
      v = fct(*val,*val2); \
      y = v - c; \
      t = s + y; \
      c = (t - s) - y; \
      s = t; \
      val  += val_s; \
      val2 += val2_s; \
    } \
\
    retmethod(gautoDelete(O(s))); \
endmethod

DEFMETHOD(FltVector, F64, FltFunction2, F64FCT2, aFloat  )
DEFMETHOD(CpxVector, C64, CpxFunction2, C64FCT2, aComplex)

#undef  DEFMETHOD
#define DEFMETHOD(T,E,TE,TF,F,O) \
\
defmethod(OBJ, gmapSum2, TF, T, TE) \
  E  *val    = self2->value; \
  I32 val_s  = self2->stride; \
  E  *end    = self2->value + self2->size*self2->stride; \
  E   val2   = self3->value; \
  F   fct    = self ->fct; \
  E c, s, t, v, y; \
\
  s = c = 0; \
  while (val != end) { \
    v = fct(*val,val2); \
    y = v - c; \
    t = s + y; \
    c = (t - s) - y; \
    s = t; \
    val  += val_s; \
  } \
\
  retmethod(gautoDelete(O(s))); \
endmethod

DEFMETHOD(FltVector, F64, Float  , FltFunction2, F64FCT2, aFloat  )
DEFMETHOD(CpxVector, C64, Complex, CpxFunction2, C64FCT2, aComplex)

// ---- mean

defmethod(OBJ, gmean, Sequence)
  U32 size;

  PRE
    size = gsize(_1);
    test_assert(size > 0, "invalid sequence size");

  BODY
    if (!COS_CONTRACT)
      size = gsize(_1);

    retmethod( gdivBy(gsum(_1),aInt(size)) );
endmethod

// ---- standard deviation

static F64 sqrDiff(F64 x, F64 m) {
  return (x-m)*(x-m);
}

defmethod(OBJ, gstdev, Sequence)
  U32 size;

  PRE
    size = gsize(_1);
    test_assert(size > 1, "invalid sequence size");

  BODY
    if (!COS_CONTRACT)
      size = gsize(_1);

    OBJ mean = gdivBy(gsum(_1),aInt(size)); PRT(mean);
    OBJ stdev = gautoDelete(gsqroot(gmapSum2(aFltFunction(sqrDiff,0,0), _1, mean)));
    UNPRT(mean); gdelete(mean);

    retmethod( stdev );
endmethod

// ----- prod

#undef  DEFMETHOD
#define DEFMETHOD(T,E,O) \
\
defmethod(OBJ, gprod, T) \
  E  *val   = self->value; \
  I32 val_s = self->stride; \
  E  *end   = self->value + self->size*self->stride; \
  E   p     = 1; \
\
  while (val != end) { \
    p *= *val; \
    val += val_s; \
  } \
\
  retmethod(gautoDelete(O(p))); \
endmethod

DEFMETHOD(FltVector, F64, aFloat  )
DEFMETHOD(CpxVector, C64, aComplex)

// ----- absolute, conjugate and argument

#undef  DEFMETHOD
#define DEFMETHOD(gen,fun) \
\
defmethod(OBJ, gen, CpxVector) \
  C64 *val   = self->value; \
  I32  val_s = self->stride; \
  C64 *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    *val = fun(*val); \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod

DEFMETHOD(gabsolute , cabs)
DEFMETHOD(gconjugate, conj)
DEFMETHOD(gargument , carg)

// ----- math methods

#undef  DEFMETHOD
#define DEFMETHOD(gen,fun) \
\
defmethod(OBJ, gen, FltVector) \
  F64 *val   = self->value; \
  I32  val_s = self->stride; \
  F64 *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    *val = fun(*val); \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod \
\
defmethod(OBJ, gen, CpxVector) \
  C64 *val   = self->value; \
  I32  val_s = self->stride; \
  C64 *end   = self->value + self->size*self->stride; \
\
  while (val != end) { \
    *val = c##fun(*val); \
    val += val_s; \
  } \
\
  retmethod(_1); \
endmethod

DEFMETHOD(gexponential, exp )
DEFMETHOD(glogarithm  , log )
DEFMETHOD(gsqroot     , sqrt)

DEFMETHOD(gcosine     , cos )
DEFMETHOD(gsine       , sin )
DEFMETHOD(gtangent    , tan )

DEFMETHOD(gacosine    , acos )
DEFMETHOD(gasine      , asin )
DEFMETHOD(gatangent   , atan )

DEFMETHOD(gcosineh    , cosh )
DEFMETHOD(gsineh      , sinh )
DEFMETHOD(gtangenth   , tanh )

DEFMETHOD(gacosineh   , acosh )
DEFMETHOD(gasineh     , asinh )
DEFMETHOD(gatangenth  , atanh )

// ----- power

defmethod(OBJ, gpower, FltVector, Float)
  F64 *val   = self->value;
  I32  val_s = self->stride;
  F64 *end   = self->value + self->size*self->stride;
  F64  exp   = self2->value;

  while (val != end) {
    *val = pow(*val,exp);
    val += val_s;
  }
  
  retmethod(_1);
endmethod

defmethod(OBJ, gpower, CpxVector, Floating)
  C64 *val   = self->value;
  I32  val_s = self->stride;
  C64 *end   = self->value + self->size*self->stride;
  C64  exp   = gcpx(_2);

  while (val != end) {
    *val = cpow(*val,exp);
    val += val_s;
  }
  
  retmethod(_1);
endmethod

// ----- conj

defmethod(OBJ, gconj, CpxVector)
  retmethod(gautoDelete( gconjugate(gclone(_1)) ));
endmethod

// ----- abs

defmethod(OBJ, gabs, CpxVector)
  retmethod(gautoDelete( gabsolute(gclone(_1)) ));
endmethod

// ----- arg

defmethod(OBJ, garg, CpxVector)
  retmethod(gautoDelete( gargument(gclone(_1)) ));
endmethod

// ----- math methods

#undef  DEFMETHOD
#define DEFMETHOD(mth,gen) \
\
defmethod(OBJ, mth, FloatingVector) \
  retmethod(gautoDelete( gen(gclone(_1)) )); \
endmethod

DEFMETHOD(gexp  , gexponential)
DEFMETHOD(glog  , glogarithm  )
DEFMETHOD(gsqrt , gsqroot     )

DEFMETHOD(gcos  , gcosine     )
DEFMETHOD(gsin  , gsine       )
DEFMETHOD(gtan  , gtangent    )

DEFMETHOD(gacos , gacosine    )
DEFMETHOD(gasin , gasine      )
DEFMETHOD(gatan , gatangent   )

DEFMETHOD(gcosh , gcosineh    )
DEFMETHOD(gsinh , gsineh      )
DEFMETHOD(gtanh , gtangenth   )

DEFMETHOD(gacosh, gacosineh   )
DEFMETHOD(gasinh, gasineh     )
DEFMETHOD(gatanh, gatangenth  )


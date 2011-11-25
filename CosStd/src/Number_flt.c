/**
 * C Object System
 * COS Number -- floating operators
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

#include <cos/Object.h>
#include <cos/Number.h>

#include <cos/gen/floatop.h>
#include <cos/gen/init.h>
#include <cos/gen/numop.h>
#include <cos/gen/object.h>

#include <math.h>
#include <float.h>
#include <complex.h>

// -----

useclass(Float, Complex);

// ----- float

BOOL
float_equalEps(F64 x, F64 y, F64 eps)
{
  // absolute difference
  F64 d = x-y;
  
  if (d < 0) d = -d;
  if (d < 2*DBL_MIN) return YES;

  // relative difference
  if (x < 0) x = -x;
  if (y < 0) y = -y;
  
  return d <= (x > y ? x : y) * eps;
}

BOOL
float_equal(F64 x, F64 y)
{
  return float_equalEps(x, y, 2*DBL_EPSILON);
}

F64
float_ipow(F64 v, I32 n)
{
  F64 a = 1.0;
  
  if (n < 0) n = -n, v = 1.0/v;

  for (;;) {
    if (n  &  1) a *= v;

    if (n >>= 1) v *= v;
    else         break;
  }

  return v;
}

// ----- complex

BOOL
complex_equalEps(C64 x, C64 y, F64 eps)
{
  return float_equalEps(complex_real(x), complex_real(y), eps) &&
         float_equalEps(complex_imag(x), complex_imag(y), eps);
}

BOOL
complex_equal(C64 x, C64 y)
{
  return complex_equalEps(x, y, 2*DBL_EPSILON);
}

C64
complex_ipow(C64 v, I32 n)
{
  C64 a = 1.0;
  
  if (n < 0) n = -n, v = 1.0/v;

  for (;;) {
    if (n  &  1) a *= v;

    if (n >>= 1) v *= v;
    else         break;
  }

  return v;
}

// ----- absolute, conjugate and argument

#undef  DEFMETHOD
#define DEFMETHOD(gen,fun) \
\
defmethod(OBJ, gen, Complex) \
  self->value = fun(self->value); \
  retmethod(_1); \
endmethod

DEFMETHOD(gabsolute , cabs)
DEFMETHOD(gconjugate, conj)
DEFMETHOD(gargument , carg)

// ----- math methods

#undef  DEFMETHOD
#define DEFMETHOD(gen,fun) \
\
defmethod(OBJ, gen, Float) \
  self->value = fun(self->value); \
  retmethod(_1); \
endmethod \
\
defmethod(OBJ, gen, Complex) \
  self->value = c##fun(self->value); \
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

defmethod(OBJ, gpower, Float, Float)
  self->value = pow(self->value, self2->value);
  retmethod(_1);
endmethod

defmethod(OBJ, gpower, Complex, Float)
  self->value = cpow(self->value, self2->value);
  retmethod(_1);
endmethod

defmethod(OBJ, gpower, Complex, Complex)
  self->value = cpow(self->value, self2->value);
  retmethod(_1);
endmethod

// ----- conj

defmethod(OBJ, gconj, Complex)
  retmethod(gconjugate(gautoRelease(gclone(_1))));
endmethod

// ----- abs

defmethod(OBJ, gabs, Complex)
  struct Float *flt = CAST(struct Float*, gautoRelease(galloc(Float)));
  flt->value = cabs(self->value);
  retmethod( (OBJ)flt );
endmethod

// ----- arg

defmethod(OBJ, garg, Complex)
  struct Float *flt = CAST(struct Float*, gautoRelease(galloc(Float)));
  flt->value = carg(self->value);
  retmethod( (OBJ)flt );
endmethod

// ----- math methods

#undef  DEFMETHOD
#define DEFMETHOD(mth,gen) \
\
defmethod(OBJ, mth, Floating) \
  retmethod(gen( gautoRelease(gclone(_1)) )); \
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

// ----- hypot

defmethod(OBJ, ghypot, Float, Float)
  F64 value = hypot(self->value, self2->value);
  retmethod( gautoRelease(ginitWithFlt(galloc(Float), value)) );
endmethod

// ----- subSqr

defmethod(OBJ, gsqrErr, Number, Number)
  OBJ flt = gsub(_1,_2);
  retmethod( gmulBy(flt,flt) );
endmethod

defmethod(OBJ, gsqrErr, Integral, Number)
  OBJ flt = gsubTo(gautoRelease(gnewWith(Float,_1)),_2);
  retmethod( gmulBy(flt,flt) );
endmethod

// ----- mulAdd

defmethod(OBJ, gmulAdd, Floating, Floating, Floating)
  retmethod(gaddTo(gmulBy(gautoRelease(gclone(_1)),_2),_3));
endmethod

// avoid mulBy(Float,Complex)
defmethod(OBJ, gmulAdd, Float, Complex, Floating)
  retmethod(gaddTo(gmulBy(gautoRelease(gclone(_2)),_1),_3));
endmethod

// avoid addTo(Float,Complex)
defmethod(OBJ, gmulAdd, Float, Float, Complex)
  retmethod(gaddTo(gmulBy(gautoRelease(gnewWith(Complex,_1)),_2),_3));
endmethod

// use C99 fma
#ifdef FP_FAST_FMA
defmethod(OBJ, gmulAdd, Float, Float, Float)
  struct Float *flt = CAST(struct Float*, gautoRelease(galloc(Float)));
  flt->value = fma(self->value,self2->value,self3->value);
  retmethod( (OBJ)flt );
endmethod
#endif


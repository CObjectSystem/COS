/**
 * C Object System
 * COS Vector template - numerics
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

#include <cos/FltVector.h>
#include <cos/CpxVector.h>
#include <cos/Number.h>
#include <cos/Function.h>

#include <cos/gen/object.h>
#include <cos/gen/floatop.h>
#include <cos/gen/numop.h>
#include <cos/gen/vectop.h>
#include <cos/gen/value.h>

#include <math.h>
#include <complex.h>

// ----- sum (Kahan formula)

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
  retmethod(gautoRelease(O(s))); \
endmethod

DEFMETHOD(FltVector, F64, aFloat  )
DEFMETHOD(CpxVector, C64, aComplex)

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
  retmethod(gautoRelease(O(p))); \
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

// ----- math methods

#undef  DEFMETHOD
#define DEFMETHOD(mth,gen) \
\
defmethod(OBJ, mth, FloatingVector) \
  retmethod(gen(gautoRelease(gclone(_1)))); \
endmethod

DEFMETHOD(gconj , gconjugate  )
DEFMETHOD(gabs  , gabsolute   )
DEFMETHOD(garg  , gargument   )

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


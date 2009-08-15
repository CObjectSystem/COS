/*
 o---------------------------------------------------------------------o
 |
 | COS Number -- floating operators
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
 | $Id: Number_flt.c,v 1.1 2009/08/15 14:56:10 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/operator.h>
#include <cos/gen/floatop.h>
#include <cos/gen/new.h>

#include <math.h>
#include <complex.h>

// -----

useclass(Float, Complex);

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

defmethod(OBJ, gpower, Float, Complex)
  self->value = cpow(self->value, self2->value);
  retmethod(_1);
endmethod

defmethod(OBJ, gpower, Complex, Complex)
  self->value = cpow(self->value, self2->value);
  retmethod(_1);
endmethod

// ----- conj

defmethod(OBJ, gconj, Complex)
  retmethod(gautoDelete( gconjugate(gclone(_1)) ));
endmethod

// ----- abs

defmethod(OBJ, gabs, Complex)
  struct Float *flt = STATIC_CAST(struct Float*, galloc(Float));
  flt->value = cabs(self->value);
  retmethod(gautoDelete( (OBJ)flt ));
endmethod

// ----- arg

defmethod(OBJ, garg, Complex)
  struct Float *flt = STATIC_CAST(struct Float*, galloc(Float));
  flt->value = carg(self->value);
  retmethod(gautoDelete( (OBJ)flt ));
endmethod

// ----- math methods

#undef  DEFMETHOD
#define DEFMETHOD(M1,M2) \
\
defmethod(OBJ, M1, Float) \
  retmethod(gautoDelete( M2(gclone(_1)) )); \
endmethod \
\
defmethod(OBJ, M1, Complex) \
  retmethod(gautoDelete( M2(gclone(_1)) )); \
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

// ----- subSqr

defmethod(OBJ, gsubSqr, Floating, Floating)
  OBJ tmp = gsubTo(gclone(_1),_2);
  retmethod(gautoDelete( gmulBy(tmp,tmp) ));
endmethod

// avoid subTo(Float,Complex)
defmethod(OBJ, gsubSqr, Float, Complex)
  struct Complex *cpx = STATIC_CAST(struct Complex*, gclone(_2));
  cpx->value  = self->value - cpx->value;
  cpx->value *= cpx->value;
  retmethod(gautoDelete( (OBJ)cpx ));
endmethod

// ----- mulAdd

defmethod(OBJ, gmulAdd, Floating, Floating, Floating)
  retmethod(gautoDelete( gaddTo(gmulBy(gclone(_1),_2),_3) ));
endmethod

// avoid mulBy(Float,Complex)
defmethod(OBJ, gmulAdd, Float, Complex, Floating)
  retmethod(gautoDelete( gaddTo(gmulBy(gclone(_2),_1),_3) ));
endmethod

// avoid addTo(Float,Complex)
defmethod(OBJ, gmulAdd, Float, Float, Complex)
  retmethod(gautoDelete( gaddTo(gmulBy(gnewWithCpx(Complex,self->value),_2),_3) ));
endmethod



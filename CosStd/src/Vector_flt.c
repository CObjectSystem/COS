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
 | $Id: Vector_flt.c,v 1.1 2009/09/02 12:09:49 ldeniau Exp $
 |
*/

#include <cos/FltVector.h>
#include <cos/CpxVector.h>
#include <cos/Number.h>

#include <cos/gen/object.h>
#include <cos/gen/operator.h>
#include <cos/gen/floatop.h>
#include <cos/gen/value.h>

#include <math.h>
#include <complex.h>

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

defmethod(OBJ, ginv, CpxVector)
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


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
 | $Id: Number.c,v 1.20 2009/12/30 01:00:45 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/TrueFalse.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/init.h>
#include <cos/gen/new.h>
#include <cos/gen/object.h>
#include <cos/gen/operator.h>
#include <cos/gen/value.h>

makclass(Number  , Value);
makclass(Integral, Number);
makclass(Floating, Number);

makclass(Int     , Integral);
makclass(Long    , Integral);
makclass(Float   , Floating);
makclass(Complex , Floating);

makclass(Char    , Int);
makclass(Short   , Int);

// -----

useclass(Char, Short, Int, Long, Float, Complex);

// ----- allocator (cluster)

defmethod(OBJ, galloc, pmNumber) // lazy alloc
  retmethod(_1);
endmethod

// ----- constructors (cluster), optimized ginitWith(galloc(_2),_2)

#undef  DEFMETHOD
#define DEFMETHOD(T,P) \
\
defalias (OBJ, (ginitWith)gnewWith, pmNumber, T); \
defmethod(OBJ,  ginitWith         , pmNumber, T) \
  struct T *new = STATIC_CAST(struct T*, galloc(T)); \
  new->P value = self2->P value; \
  retmethod( (OBJ)new ); \
endmethod

DEFMETHOD(Char   , Int.)
DEFMETHOD(Short  , Int.)
DEFMETHOD(Int    ,     )
DEFMETHOD(Long   ,     )
DEFMETHOD(Float  ,     )
DEFMETHOD(Complex,     )

// ----- clones (cluster), optimized ginitWith(galloc(gclass(_1)),_1)

#undef  DEFMETHOD
#define DEFMETHOD(T,P) \
\
defmethod(OBJ, gclone, T) \
  struct T *new = STATIC_CAST(struct T*, galloc(T)); \
  new->P value = self->P value; \
  retmethod( (OBJ)new ); \
endmethod

DEFMETHOD(Char   , Int.)
DEFMETHOD(Short  , Int.)
DEFMETHOD(Int    ,     )
DEFMETHOD(Long   ,     )
DEFMETHOD(Float  ,     )
DEFMETHOD(Complex,     )

// ----- constructors

#undef  DEFMETHOD
#define DEFMETHOD(T) \
\
defalias (OBJ, (ginit)gclear, T); \
defmethod(OBJ,  ginit       , T)  \
  self->value = 0; \
  retmethod(_1); \
endmethod

DEFMETHOD(Int    )
DEFMETHOD(Long   )
DEFMETHOD(Float  )
DEFMETHOD(Complex)

#undef DEFMETHOD

// ----- copy constructors

#undef  DEFMETHOD
#define DEFMETHOD(T1,T2) \
\
defalias (OBJ, (ginitWith)gcopy, T1, T2); \
defmethod(OBJ,  ginitWith      , T1, T2) \
  self->value = self2->value; \
  retmethod(_1); \
endmethod

DEFMETHOD(Int    , Int    )
DEFMETHOD(Long   , Int    )
DEFMETHOD(Long   , Long   )
DEFMETHOD(Float  , Int    )
DEFMETHOD(Float  , Long   )
DEFMETHOD(Float  , Float  )
DEFMETHOD(Complex, Int    )
DEFMETHOD(Complex, Long   )
DEFMETHOD(Complex, Float  )
DEFMETHOD(Complex, Complex)

defmethod(OBJ, ginitWith2, Complex, Float, Float)
  self->value = complex_make(self2->value, self3->value);
  retmethod(_1);
endmethod

// ----- value constructors

defmethod(OBJ, ginitWithChr, Char, (I32)val)
  self->Int.value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithSht, Short, (I32)val)
  self->Int.value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithInt, Int, (I32)val)
  self->value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithLng, Long, (I64)val)
  self->value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithFlt, Float, (F64)val)
  self->value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithCpx, Complex, (C64)val)
  self->value = val;
  retmethod(_1);
endmethod

// ----- value getters

defmethod(I32, gchr, Char)
  retmethod(self->Int.value);
endmethod

defmethod(I32, gsht, Short)
  retmethod(self->Int.value);
endmethod

defmethod(I32, gint, Int)
  retmethod(self->value);
endmethod

defmethod(I64, glng, Int)
  retmethod(self->value);
endmethod

defmethod(I64, glng, Long)
  retmethod(self->value);
endmethod

defmethod(F64, gflt, Int)
  retmethod(self->value);
endmethod

defmethod(F64, gflt, Long)
  retmethod(self->value);
endmethod

defmethod(F64, gflt, Float)
  retmethod(self->value);
endmethod

defmethod(C64, gcpx, Int)
  retmethod(self->value);
endmethod

defmethod(C64, gcpx, Long)
  retmethod(self->value);
endmethod

defmethod(C64, gcpx, Float)
  retmethod(self->value);
endmethod

defmethod(C64, gcpx, Complex)
  retmethod(self->value);
endmethod

// ----- absolute

#undef  DEFMETHOD
#define DEFMETHOD(T) \
\
defmethod(OBJ, gabsolute, T) \
  if (self->value < 0) \
    self->value = -self->value; \
  retmethod(_1); \
endmethod

DEFMETHOD(Int    )
DEFMETHOD(Long   )
DEFMETHOD(Float  )

// ----- negate

#undef  DEFMETHOD
#define DEFMETHOD(T) \
\
defmethod(OBJ, gnegate, T) \
  self->value = -self->value; \
  retmethod(_1); \
endmethod

DEFMETHOD(Int    )
DEFMETHOD(Long   )
DEFMETHOD(Float  )
DEFMETHOD(Complex)

// ----- invert

defmethod(OBJ, ginvert, Float)
  self->value = 1/self->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginvert, Complex)
  self->value = 1/self->value;
  retmethod(_1);
endmethod

// ----- addTo, subTo, mulTo, divTo, modulo

#undef  DEFMETHOD
#define DEFMETHOD(MTH,T1,OP,T2) \
\
defmethod(OBJ, MTH, T1, T2) \
  self->value OP self2->value; \
  retmethod(_1); \
endmethod

DEFMETHOD(gaddTo, Int    , +=, Int    )
DEFMETHOD(gaddTo, Long   , +=, Int    )
DEFMETHOD(gaddTo, Long   , +=, Long   )
DEFMETHOD(gaddTo, Float  , +=, Int    )
DEFMETHOD(gaddTo, Float  , +=, Long   )
DEFMETHOD(gaddTo, Float  , +=, Float  )
DEFMETHOD(gaddTo, Complex, +=, Int    )
DEFMETHOD(gaddTo, Complex, +=, Long   )
DEFMETHOD(gaddTo, Complex, +=, Float  )
DEFMETHOD(gaddTo, Complex, +=, Complex)

DEFMETHOD(gsubTo, Int    , -=, Int    )
DEFMETHOD(gsubTo, Long   , -=, Int    )
DEFMETHOD(gsubTo, Long   , -=, Long   )
DEFMETHOD(gsubTo, Float  , -=, Int    )
DEFMETHOD(gsubTo, Float  , -=, Long   )
DEFMETHOD(gsubTo, Float  , -=, Float  )
DEFMETHOD(gsubTo, Complex, -=, Int    )
DEFMETHOD(gsubTo, Complex, -=, Long   )
DEFMETHOD(gsubTo, Complex, -=, Float  )
DEFMETHOD(gsubTo, Complex, -=, Complex)

DEFMETHOD(gmulBy, Int    , *=, Int    )
DEFMETHOD(gmulBy, Long   , *=, Int    )
DEFMETHOD(gmulBy, Long   , *=, Long   )
DEFMETHOD(gmulBy, Float  , *=, Int    )
DEFMETHOD(gmulBy, Float  , *=, Long   )
DEFMETHOD(gmulBy, Float  , *=, Float  )
DEFMETHOD(gmulBy, Complex, *=, Int    )
DEFMETHOD(gmulBy, Complex, *=, Long   )
DEFMETHOD(gmulBy, Complex, *=, Float  )
DEFMETHOD(gmulBy, Complex, *=, Complex)

DEFMETHOD(gdivBy, Int    , /=, Int    )
DEFMETHOD(gdivBy, Long   , /=, Int    )
DEFMETHOD(gdivBy, Long   , /=, Long   )
DEFMETHOD(gdivBy, Float  , /=, Int    )
DEFMETHOD(gdivBy, Float  , /=, Long   )
DEFMETHOD(gdivBy, Float  , /=, Float  )
DEFMETHOD(gdivBy, Complex, /=, Int    )
DEFMETHOD(gdivBy, Complex, /=, Long   )
DEFMETHOD(gdivBy, Complex, /=, Float  )
DEFMETHOD(gdivBy, Complex, /=, Complex)

DEFMETHOD(gmodulo, Int   , %=, Int    )
DEFMETHOD(gmodulo, Long  , %=, Int    )
DEFMETHOD(gmodulo, Long  , %=, Long   )

// ----- power

defmethod(OBJ, gpower, Float, Int)
  self->value = float_ipow(self->value, self2->value);
  retmethod(_1);
endmethod

defmethod(OBJ, gpower, Complex, Int)
  self->value = complex_ipow(self->value, self2->value);
  retmethod(_1);
endmethod

// ----- abs

defmethod(OBJ, gabs, Number)
  retmethod(gabsolute(gautoDelete(gclone(_1))));
endmethod

// ----- neg

defmethod(OBJ, gneg, Number)
  retmethod(gnegate(gautoDelete(gclone(_1))));
endmethod

// ----- sqr

defmethod(OBJ, gsqr, Number)
  retmethod(gmulBy(gautoDelete(gclone(_1)),_1));
endmethod

// ----- inv

defmethod(OBJ, ginv, Floating)
  retmethod(ginvert(gautoDelete(gclone(_1))));
endmethod

// ----- add

defmethod(OBJ, gadd, Number, Number)
  retmethod(gaddTo(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gadd, Integral, Long)
  retmethod(gaddTo(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, Integral, Floating)
  retmethod(gaddTo(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, Floating, Complex)
  retmethod(gaddTo(gautoDelete(gclone(_2)),_1));
endmethod

// ----- sub

defmethod(OBJ, gsub, Number, Number)
  retmethod(gsubTo(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gsub, Integral, Long)
  retmethod(gnegate(gsubTo(gautoDelete(gclone(_2)),_1)));
endmethod

defmethod(OBJ, gsub, Integral, Floating)
  retmethod(gnegate(gsubTo(gautoDelete(gclone(_2)),_1)));
endmethod

defmethod(OBJ, gsub, Floating, Complex)
  retmethod(gnegate(gsubTo(gautoDelete(gclone(_2)),_1)));
endmethod

// ----- mul

defmethod(OBJ, gmul, Number, Number)
  retmethod(gmulBy(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gmul, Integral, Long)
  retmethod(gmulBy(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, Integral, Floating)
  retmethod(gmulBy(gautoDelete(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, Floating, Complex)
  retmethod(gmulBy(gautoDelete(gclone(_2)),_1));
endmethod

// ----- div

defmethod(OBJ, gdiv, Number, Number)
  retmethod(gdivBy(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gdiv, Integral, Long)
  retmethod(gmulBy(ginvert(gautoDelete(gclone(_2))),_1));
endmethod

defmethod(OBJ, gdiv, Integral, Floating)
  retmethod(gmulBy(ginvert(gautoDelete(gclone(_2))),_1));
endmethod

defmethod(OBJ, gdiv, Floating, Complex)
  retmethod(gmulBy(ginvert(gautoDelete(gclone(_2))),_1));
endmethod

// ----- pow

defmethod(OBJ, gpow, Floating, Int)
  retmethod(gpower(gautoDelete(gclone(_1)),_2));
endmethod

defmethod(OBJ, gpow, Floating, Floating)
  retmethod(gpower(gautoDelete(gclone(_1)),_2));
endmethod

// ----- mod

defmethod(OBJ, gmod, Integral, Integral)
  retmethod(gmodulo(gautoDelete(gclone(_1)),_2));
endmethod

// ----- compare

useclass(Lesser,Equal,Greater);

#undef  DEFMETHOD
#define DEFMETHOD(T1,T2) \
\
defmethod(OBJ, gcompare, T1, T2) \
  retmethod(self->value < self2->value ? Lesser  : \
            self->value > self2->value ? Greater : Equal); \
endmethod

DEFMETHOD(Int  , Int  )
DEFMETHOD(Int  , Long )
DEFMETHOD(Int  , Float)
DEFMETHOD(Long , Int  )
DEFMETHOD(Long , Long )
DEFMETHOD(Long , Float)
DEFMETHOD(Float, Int  )
DEFMETHOD(Float, Long )
DEFMETHOD(Float, Float)

// ----- isEqual

#undef  DEFMETHOD
#define DEFMETHOD(EQ,T1,T2) \
\
defmethod(OBJ, gisEqual, T1, T2) \
  retmethod(EQ(self->value,self2->value) ? True : False); \
endmethod

#define EQ(A,B) A == B

DEFMETHOD(EQ           , Int    , Int    )
DEFMETHOD(EQ           , Int    , Long   )
DEFMETHOD(float_equal  , Int    , Float  )
DEFMETHOD(complex_equal, Int    , Complex)
DEFMETHOD(EQ           , Long   , Int    )
DEFMETHOD(EQ           , Long   , Long   )
DEFMETHOD(float_equal  , Long   , Float  )
DEFMETHOD(complex_equal, Long   , Complex)
DEFMETHOD(float_equal  , Float  , Int    )
DEFMETHOD(float_equal  , Float  , Long   )
DEFMETHOD(float_equal  , Float  , Float  )
DEFMETHOD(complex_equal, Float  , Complex)
DEFMETHOD(complex_equal, Complex, Int    )
DEFMETHOD(complex_equal, Complex, Long   )
DEFMETHOD(complex_equal, Complex, Float  )
DEFMETHOD(complex_equal, Complex, Complex)

// ----- isNotEqual

defmethod(OBJ, gisNotEqual, Number, Number)
  retmethod( gisEqual(_1,_2) == False ? True : False );
endmethod

// ----- Other comparison

defmethod(OBJ, gisLesser, Number, Number)
  retmethod( gcompare(_1,_2) == Lesser  ? True : False );
endmethod

defmethod(OBJ, gisGreater, Number, Number)
  retmethod( gcompare(_1,_2) == Greater ? True : False );
endmethod

defmethod(OBJ, gisLesserOrEqual, Number, Number)
  retmethod( gcompare(_1,_2) == Greater ? False : True );
endmethod

defmethod(OBJ, gisGreaterOrEqual, Number, Number)
  retmethod( gcompare(_1,_2) == Lesser  ? False : True );
endmethod

// ----- min, max

defmethod(OBJ, gmin, Number, Number)
  retmethod( gcompare(_1,_2) == Lesser  ? _1 : _2 );
endmethod

defmethod(OBJ, gmax, Number, Number)
  retmethod( gcompare(_1,_2) == Greater ? _1 : _2 );
endmethod


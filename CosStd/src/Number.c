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
 | $Id: Number.c,v 1.12 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/TrueFalse.h>

#include <cos/gen/compare.h>
#include <cos/gen/init.h>
#include <cos/gen/logic.h>
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

// ----- copy constructor

defmethod(OBJ, ginitWith, Int, Int)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Long, Int)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Long, Long)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Float, Int)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Float, Long)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Float, Float)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Int)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Long)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Float)
  self1->value = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, Complex, Float, Float)
  self1->value = complex_make(self2->value, self3->value);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Complex)
  self1->value = self2->value;
  retmethod(_1);
endmethod

// ----- value constructor

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

// ----- value

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

// ----- negate

defmethod(OBJ, gnegate, Int)
  self1->value = -self1->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Long)
  self1->value = -self1->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Float)
  self1->value = -self1->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Complex)
  self1->value = -self1->value;
  retmethod(_1);
endmethod

// ----- invert

defmethod(OBJ, ginvert, Float)
  self1->value = 1/self1->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginvert, Complex)
  self1->value = 1/self1->value;
  retmethod(_1);
endmethod

// ----- addTo

defmethod(OBJ, gaddTo, Int, Int)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Long, Int)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Long, Long)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Float, Int)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Float, Long)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Float, Float)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Int)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Long)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Float)
  self1->value += self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Complex)
  self1->value += self2->value;
  retmethod(_1);
endmethod

// ----- subTo

defmethod(OBJ, gsubTo, Int, Int)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Long, Int)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Long, Long)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Float, Int)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Float, Long)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Float, Float)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Int)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Long)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Float)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Complex)
  self1->value -= self2->value;
  retmethod(_1);
endmethod

// ----- mulBy

defmethod(OBJ, gmulBy, Int, Int)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Long, Int)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Long, Long)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Float, Int)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Float, Long)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Float, Float)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Int)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Long)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Float)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Complex)
  self1->value *= self2->value;
  retmethod(_1);
endmethod

// ----- divBy

defmethod(OBJ, gdivBy, Int, Int)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Long, Int)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Long, Long)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Float, Int)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Float, Long)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Float, Float)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Int)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Long)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Float)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Complex)
  self1->value /= self2->value;
  retmethod(_1);
endmethod

// ----- modulo

defmethod(OBJ, gmodulo, Int, Int)
  self1->value %= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, Long, Int)
  self1->value %= self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, Long, Long)
  self1->value %= self2->value;
  retmethod(_1);
endmethod

// ----- conjugate

defmethod(OBJ, gconjugate, Complex)
  self->value = complex_make(complex_real(self->value),
                            -complex_imag(self->value));
  retmethod(_1);
endmethod

// ----- power

defmethod(OBJ, gpower, Float, Int)
  F64 v = self1->value;
  I32 n = self2->value;
  F64 a = 1.0;
  
  if (n < 0) {
    n = -n;
    v = 1.0/v;
  }

  for (;;) {
    if (n & 1)
      a *= v;

    if (n >>= 1)
      v *= v;
    else
      break;
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gpower, Complex, Int)
  C64 v = self1->value;
  I32 n = self2->value;
  C64 a = 1.0;
  
  if (n < 0) {
    n = -n;
    v = 1.0/v;
  }

  for (;;) {
    if (n & 1)
      a *= v;

    if (n >>= 1)
      v *= v;
    else
      break;
  }

  retmethod(_1);
endmethod

// ----- neg

defmethod(OBJ, gneg, Number)
  retmethod(gautoDelete( gnegate(gclone(_1)) ));
endmethod

// ----- inv

defmethod(OBJ, ginv, Floating)
  retmethod(gautoDelete( ginvert(gclone(_1)) ));
endmethod

// ----- conj

defmethod(OBJ, gconj, Complex)
  retmethod(gautoDelete( gconjugate(gclone(_1)) ));
endmethod

// ----- add

defmethod(OBJ, gadd, Number, Number)
  retmethod(gautoDelete( gaddTo(gclone(_1),_2) ));
endmethod

defmethod(OBJ, gadd, Integral, Long)
  retmethod(gautoDelete( gaddTo(gclone(_2),_1) ));
endmethod

defmethod(OBJ, gadd, Integral, Floating)
  retmethod(gautoDelete( gaddTo(gclone(_2),_1) ));
endmethod

defmethod(OBJ, gadd, Floating, Complex)
  retmethod(gautoDelete( gaddTo(gclone(_2),_1) ));
endmethod

// ----- sub

defmethod(OBJ, gsub, Number, Number)
  retmethod(gautoDelete( gsubTo(gclone(_1),_2) ));
endmethod

defmethod(OBJ, gsub, Integral, Long)
  retmethod(gautoDelete( gnegate(gsubTo(gclone(_2),_1)) ));
endmethod

defmethod(OBJ, gsub, Integral, Floating)
  retmethod(gautoDelete( gnegate(gsubTo(gclone(_2),_1)) ));
endmethod

defmethod(OBJ, gsub, Floating, Complex)
  retmethod(gautoDelete( gnegate(gsubTo(gclone(_2),_1)) ));
endmethod

// ----- mul

defmethod(OBJ, gmul, Number, Number)
  retmethod(gautoDelete( gmulBy(gclone(_1),_2) ));
endmethod

defmethod(OBJ, gmul, Integral, Long)
  retmethod(gautoDelete( gmulBy(gclone(_2),_1) ));
endmethod

defmethod(OBJ, gmul, Integral, Floating)
  retmethod(gautoDelete( gmulBy(gclone(_2),_1) ));
endmethod

defmethod(OBJ, gmul, Floating, Complex)
  retmethod(gautoDelete( gmulBy(gclone(_2),_1) ));
endmethod

// ----- div

defmethod(OBJ, gdiv, Number, Number)
  retmethod(gautoDelete( gdivBy(gclone(_1),_2) ));
endmethod

defmethod(OBJ, gdiv, Integral, Long)
  retmethod(gautoDelete( gmulBy(ginvert(gclone(_2)),_1) ));
endmethod

defmethod(OBJ, gdiv, Integral, Floating)
  retmethod(gautoDelete( gmulBy(ginvert(gclone(_2)),_1) ));
endmethod

defmethod(OBJ, gdiv, Floating, Complex)
  retmethod(gautoDelete( gmulBy(ginvert(gclone(_2)),_1) ));
endmethod

// ----- mod

defmethod(OBJ, gmod, Integral, Integral)
  retmethod(gautoDelete( gmodulo(gclone(_1),_2) ));
endmethod

// ----- compare

useclass(Lesser,Equal,Greater);

defmethod(OBJ, gcompare, Int, Int)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int, Long)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int, Float)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Long, Int)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Long, Long)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Long, Float)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Float, Int)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Float, Long)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Float, Float)
  retmethod(self1->value < self2->value ? Lesser  :
            self1->value > self2->value ? Greater : Equal);
endmethod

// ----- not

defmethod(OBJ, gnot, Int)
  retmethod(self->value ? False : True);
endmethod

defmethod(OBJ, gnot, Long)
  retmethod(self->value ? False : True);
endmethod

defmethod(OBJ, gnot, Float)
  retmethod(float_equal(self->value,0) ? False : True);
endmethod

defmethod(OBJ, gnot, Complex)
  retmethod(complex_equal(self->value,0) ? False : True);
endmethod

// ----- isEqual

defmethod(OBJ, gisEqual, Int, Int)
  retmethod(self1->value == self2->value ? True : False);
endmethod

defmethod(OBJ, gisEqual, Int, Long)
  retmethod(self1->value == self2->value ? True : False);
endmethod

defmethod(OBJ, gisEqual, Int, Float)
  retmethod(float_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Int, Complex)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Long, Int)
  retmethod(self1->value == self2->value ? True : False);
endmethod

defmethod(OBJ, gisEqual, Long, Long)
  retmethod(self1->value == self2->value ? True : False);
endmethod

defmethod(OBJ, gisEqual, Long, Float)
  retmethod(float_equal(self1->value,self1->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Long, Complex)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Float, Int)
  retmethod(float_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Float, Long)
  retmethod(float_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Float, Float)
  retmethod(float_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Float, Complex)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Complex, Int)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Complex, Long)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Complex, Float)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod

defmethod(OBJ, gisEqual, Complex, Complex)
  retmethod(complex_equal(self1->value,self2->value) ? True : False);
endmethod


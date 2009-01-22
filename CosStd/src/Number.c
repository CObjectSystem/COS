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
 | $Id: Number.c,v 1.9 2009/01/22 16:45:08 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/TrueFalse.h>
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

defmethod(OBJ, ginitWithInt, Int, (INT)val)
  self->value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithLng, Long, (LONG)val)
  self->value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithFlt, Float, (FLOAT)val)
  self->value = val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithCpx, Complex, (COMPLEX)val)
  self->value = val;
  retmethod(_1);
endmethod

// ----- value

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

defmethod(void, gnegate, Int)
  self1->value = -self1->value;
endmethod

defmethod(void, gnegate, Long)
  self1->value = -self1->value;
endmethod

defmethod(void, gnegate, Float)
  self1->value = -self1->value;
endmethod

defmethod(void, gnegate, Complex)
  self1->value = -self1->value;
endmethod

// ----- invert

defmethod(void, ginvert, Float)
  self1->value = 1/self1->value;
endmethod

defmethod(void, ginvert, Complex)
  self1->value = 1/self1->value;
endmethod

// ----- addTo

defmethod(void, gaddTo, Int, Int)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Long, Int)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Long, Long)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Float, Int)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Float, Long)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Float, Float)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Complex, Int)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Complex, Long)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Complex, Float)
  self1->value += self2->value;
endmethod

defmethod(void, gaddTo, Complex, Complex)
  self1->value += self2->value;
endmethod

// ----- subTo

defmethod(void, gsubTo, Int, Int)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Long, Int)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Long, Long)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Float, Int)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Float, Long)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Float, Float)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Complex, Int)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Complex, Long)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Complex, Float)
  self1->value -= self2->value;
endmethod

defmethod(void, gsubTo, Complex, Complex)
  self1->value -= self2->value;
endmethod

// ----- mulBy

defmethod(void, gmulBy, Int, Int)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Long, Int)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Long, Long)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Float, Int)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Float, Long)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Float, Float)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Complex, Int)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Complex, Long)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Complex, Float)
  self1->value *= self2->value;
endmethod

defmethod(void, gmulBy, Complex, Complex)
  self1->value *= self2->value;
endmethod

// ----- divBy

defmethod(void, gdivBy, Int, Int)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Long, Int)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Long, Long)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Float, Int)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Float, Long)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Float, Float)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Complex, Int)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Complex, Long)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Complex, Float)
  self1->value /= self2->value;
endmethod

defmethod(void, gdivBy, Complex, Complex)
  self1->value /= self2->value;
endmethod

// ----- modulo

defmethod(void, gmodulo, Int, Int)
  self1->value %= self2->value;
endmethod

defmethod(void, gmodulo, Long, Int)
  self1->value %= self2->value;
endmethod

defmethod(void, gmodulo, Long, Long)
  self1->value %= self2->value;
endmethod

// ----- conjugate

defmethod(void, gconjugate, Complex)
  self->value = complex_make(complex_real(self->value),
                            -complex_imag(self->value));
endmethod

// ----- power

defmethod(void, gpower, Float, Int)
  I32 n = self2->value;
  F64 a = 1.0;
  
  if (n < 0) {
    n = -n;
    self->value = 1.0/self->value;
  }

  for (;;) {
    if (n & 1)
      a *= self->value;

    if (n >>= 1)
      self->value *= self->value;
    else
      break;
  }
endmethod

defmethod(void, gpower, Complex, Int)
  I32 n = self2->value;
  C64 a = 1.0;
  
  if (n < 0) {
    n = -n;
    self->value = 1.0/self->value;
  }

  for (;;) {
    if (n & 1)
      a *= self->value;

    if (n >>= 1)
      self->value *= self->value;
    else
      break;
  }
endmethod

// ----- neg

defmethod(OBJ, gneg, Number)
  OBJ res = gclone(_1);
  gnegate(res);
  retmethod(gautoRelease(res));
endmethod

// ----- inv

defmethod(OBJ, ginv, Floating)
  OBJ res = gclone(_1);
  ginvert(res);
  retmethod(gautoRelease(res));
endmethod

// ----- conj

defmethod(OBJ, gconj, Complex)
  OBJ res = gclone(_1);
  gconjugate(res);
  retmethod(gautoRelease(res));
endmethod

// ----- add

defmethod(OBJ, gadd, Number, Number)
  OBJ res = gclone(_1);
  gaddTo(res,_2);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gadd, Integral, Long)
  OBJ res = gclone(_2);
  gaddTo(res,_1);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gadd, Integral, Floating)
  OBJ res = gclone(_2);
  gaddTo(res,_1);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gadd, Floating, Complex)
  OBJ res = gclone(_2);
  gaddTo(res,_1);
  retmethod(gautoRelease(res));
endmethod

// ----- sub

defmethod(OBJ, gsub, Number, Number)
  OBJ res = gclone(_1);
  gsubTo(res,_2);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gsub, Integral, Long)
  OBJ res = gclone(_2);
  gsubTo(res,_1);
  gnegate(res);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gsub, Integral, Floating)
  OBJ res = gclone(_2);
  gsubTo(res,_1);
  gnegate(res);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gsub, Floating, Complex)
  OBJ res = gclone(_2);
  gsubTo(res,_1);
  gnegate(res);
  retmethod(gautoRelease(res));
endmethod

// ----- mul

defmethod(OBJ, gmul, Number, Number)
  OBJ res = gclone(_1);
  gmulBy(res,_2);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gmul, Integral, Long)
  OBJ res = gclone(_2);
  gmulBy(res,_1);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gmul, Integral, Floating)
  OBJ res = gclone(_2);
  gmulBy(res,_1);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gmul, Floating, Complex)
  OBJ res = gclone(_2);
  gmulBy(res,_1);
  retmethod(gautoRelease(res));
endmethod

// ----- div

defmethod(OBJ, gdiv, Number, Number)
  OBJ res = gclone(_1);
  gdivBy(res,_2);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gdiv, Integral, Long)
  OBJ res = gclone(_2);
  ginvert(res);
  gmulBy(res,_1);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gdiv, Integral, Floating)
  OBJ res = gclone(_2);
  ginvert(res);
  gmulBy(res,_1);
  retmethod(gautoRelease(res));
endmethod

defmethod(OBJ, gdiv, Floating, Complex)
  OBJ res = gclone(_2);
  ginvert(res);
  gmulBy(res,_1);
  retmethod(gautoRelease(res));
endmethod

// ----- mod

defmethod(OBJ, gmod, Integral, Integral)
  OBJ res = gclone(_1);
  gmodulo(res,_2);
  retmethod(gautoRelease(res));
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


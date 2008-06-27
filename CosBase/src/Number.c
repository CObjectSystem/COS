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
 | $Id: Number.c,v 1.1 2008/06/27 16:17:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/TrueFalse.h>
#include <cos/gen/object.h>
#include <cos/stdgen.h>

makclass(Number  , Value);
makclass(Integral, Number);
makclass(Floating, Number);

makclass(Int32   , Integral);
makclass(Int64   , Integral);
makclass(Size    , Integral);

makclass(Char    , Int32);
makclass(Short   , Int32);
makclass(Int     , Int32);
makclass(Long    , Int64);

makclass(Double  , Floating);
makclass(Complex , Floating);

// ----- copy

defmethod(OBJ, ginitWith, Int32, Int32)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Int64, Int32)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Int64, Int64)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Size, Size)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Double, Int32)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Double, Int64)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Double, Double)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Int32)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Int64)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Double)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Complex)
  self1->val = self2->val;
  retmethod(_1);
endmethod

// ----- value

defmethod(char, gchar, Int32)
  PRE  TestAssert( self->val >= CHAR_MIN && self->val <= CHAR_MAX );
  BODY retmethod(self->val);
endmethod

defmethod(short, gshort, Int32)
  PRE  TestAssert( self->val >= SHRT_MIN && self->val <= SHRT_MAX );
  BODY retmethod(self->val);
endmethod

defmethod(S32, gint, Int32)
  retmethod(self->val);
endmethod

defmethod(S64, glong, Int32)
  retmethod(self->val);
endmethod

defmethod(S64, glong, Int64)
  retmethod(self->val);
endmethod

defmethod(size_t, gsize, Size)
  retmethod(self->val);
endmethod

defmethod(double, gdouble, Int32)
  retmethod(self->val);
endmethod

defmethod(double, gdouble, Int64)
  retmethod(self->val);
endmethod

defmethod(double, gdouble, Double)
  retmethod(self->val);
endmethod

defmethod(_Complex double, gcomplex, Int32)
  retmethod(self->val);
endmethod

defmethod(_Complex double, gcomplex, Int64)
  retmethod(self->val);
endmethod

defmethod(_Complex double, gcomplex, Double)
  retmethod(self->val);
endmethod

defmethod(_Complex double, gcomplex, Complex)
  retmethod(self->val);
endmethod

// ----- negate

defmethod(OBJ, gnegate, Int32)
  self1->val = -self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Int64)
  self1->val = -self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Double)
  self1->val = -self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Complex)
  self1->val = -self1->val;
  retmethod(_1);
endmethod

// ----- invert

defmethod(OBJ, ginvert, Int32)
  self1->val = 1/self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginvert, Int64)
  self1->val = 1/self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginvert, Double)
  self1->val = 1/self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginvert, Complex)
  self1->val = 1/self1->val;
  retmethod(_1);
endmethod

// ----- addTo

defmethod(OBJ, gaddTo, Int32, Int32)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Int64, Int32)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Int64, Int64)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Double, Int32)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Double, Int64)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Double, Double)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Int32)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Int64)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Double)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Complex)
  self1->val += self2->val;
  retmethod(_1);
endmethod

// ----- subTo

defmethod(OBJ, gsubTo, Int32, Int32)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Int64, Int32)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Int64, Int64)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Double, Int32)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Double, Int64)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Double, Double)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Int32)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Int64)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Double)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Complex)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

// ----- mulBy

defmethod(OBJ, gmulBy, Int32, Int32)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Int64, Int32)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Int64, Int64)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Double, Int32)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Double, Int64)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Double, Double)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Int32)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Int64)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Double)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Complex)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

// ----- divBy

defmethod(OBJ, gdivBy, Int32, Int32)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Int64, Int32)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Int64, Int64)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Double, Int32)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Double, Int64)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Double, Double)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Int32)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Int64)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Double)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Complex)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

// ----- modulo

defmethod(OBJ, gmodulo, Int32, Int32)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, Int64, Int32)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, Int64, Int64)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

/*
// ----- neg

defmethod(OBJ, gneg, Number)
  retmethod(gneg(gautoRelease(gclone(_1))));
endmethod

// ----- inv

defmethod(OBJ, ginv, Number)
  retmethod(ginv(gautoRelease(gclone(_1))));
endmethod

// ----- add

defmethod(OBJ, gadd, Number, Number)
  retmethod(gaddTo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gadd, Integral, Floating)
  retmethod(gaddTo(gautoRelease(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, Floating, Integral)
  retmethod(gaddTo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gadd, Integral, Int64)
  retmethod(gaddTo(gautoRelease(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, Int64, Integral)
  retmethod(gaddTo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gadd, Floating, Complex)
  retmethod(gaddTo(gautoRelease(gclone(_2)),_1));
endmethod

defmethod(OBJ, gadd, Complex, Floating)
  retmethod(gaddTo(gautoRelease(gclone(_1)),_2));
endmethod

// ----- sub

defmethod(OBJ, gsub, Number, Number)
  retmethod(gsubTo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gsub, Integral, Floating)
  retmethod(gsubTo(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gsub, Floating, Integral)
  retmethod(gsubTo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gsub, Integral, Int64)
  retmethod(gsubTo(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gsub, Int64, Integral)
  retmethod(gsubTo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gsub, Floating, Complex)
  retmethod(gsubTo(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gsub, Complex, Floating)
  retmethod(gsubTo(gautoRelease(gclone(_1)),_2));
endmethod

// ----- mul

defmethod(OBJ, gmul, Number, Number)
  retmethod(gmulBy(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gmul, Integral, Floating)
  retmethod(gmulBy(gautoRelease(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, Floating, Integral)
  retmethod(gmulBy(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gmul, Integral, Int64)
  retmethod(gmulBy(gautoRelease(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, Int64, Integral)
  retmethod(gmulBy(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gmul, Floating, Complex)
  retmethod(gmulBy(gautoRelease(gclone(_2)),_1));
endmethod

defmethod(OBJ, gmul, Complex, Floating)
  retmethod(gmulBy(gautoRelease(gclone(_1)),_2));
endmethod

// ----- div

defmethod(OBJ, gdiv, Number, Number)
  retmethod(gdivBy(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gdiv, Integral, Floating)
  retmethod(gdivBy(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gdiv, Floating, Integral)
  retmethod(gdivBy(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gdiv, Integral, Int64)
  retmethod(gdivBy(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gdiv, Int64, Integral)
  retmethod(gdivBy(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gdiv, Floating, Complex)
  retmethod(gdivBy(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gdiv, Complex, Floating)
  retmethod(gdivBy(gautoRelease(gclone(_1)),_2));
endmethod

// ----- mod

defmethod(OBJ, gmod, Integral, Integral)
  retmethod(gmodulo(gautoRelease(gclone(_1)),_2));
endmethod

defmethod(OBJ, gmod, Integral, Int64)
  retmethod(gmodulo(gcastTo(_1,gclass(_2)),_2));
endmethod

defmethod(OBJ, gmod, Int64, Integral)
  retmethod(gmodulo(gautoRelease(gclone(_1)),_2));
endmethod

*/

// ----- compare

useclass(Lesser,Equal,Greater);

defmethod(OBJ, gcompare, Int32, Int32)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int32, Int64)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int32, Double)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int64, Int32)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int64, Int64)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int64, Double)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Double, Int32)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Double, Int64)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Double, Double)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

// ----------

#include <complex.h>

#define d_is_eq(x,y)      ((x)<=(y)                   && (x)>=(y)                  )
#define z_is_eq(x,yr,yi)  (d_is_eq(creal(x),(yr))     && d_is_eq(cimag(x),(yi))    )
#define Z_is_eq(x,y)      (d_is_eq(creal(x),creal(y)) && d_is_eq(cimag(x),cimag(y)))
#define d_is_neq(x,y)     ((x)<(y)                    || (x)>(y)                   )
#define z_is_neq(x,yr,yi) (d_is_neq(creal(x),(yr))    || d_is_neq(cimag(x),(yi))   )

// ----- bool

defmethod(OBJ, gbool, Int32)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, Int64)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, Size)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, Double)
  retmethod(d_is_neq(self->val,0) ? True : False);
endmethod

defmethod(OBJ, gbool, Complex)
  retmethod(z_is_neq(self->val,0,0) ? True : False);
endmethod

// ----- not

defmethod(OBJ, gnot, Int32)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, Int64)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, Size)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, Double)
  retmethod(d_is_neq(self->val,0) ? False : True);
endmethod

defmethod(OBJ, gnot, Complex)
  retmethod(z_is_neq(self->val,0,0) ? False : True);
endmethod

// ----- equal

defmethod(OBJ, gequal, Int32, Int32)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Int32, Int64)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Int32, Double)
  retmethod(d_is_eq(self2->val,self1->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Int32, Complex)
  retmethod(z_is_eq(self2->val,self1->val,0) ? True : False);
endmethod

defmethod(OBJ, gequal, Int64, Int32)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Int64, Int64)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Int64, Double)
  retmethod(d_is_eq(self2->val,self1->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Int64, Complex)
  retmethod(z_is_eq(self2->val,self1->val,0) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Int32)
  retmethod(d_is_eq(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Int64)
  retmethod(d_is_eq(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Double)
  retmethod(d_is_eq(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Complex)
  retmethod(z_is_eq(self2->val,self1->val,0) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Int32)
  retmethod(z_is_eq(self1->val,self2->val,0) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Int64)
  retmethod(z_is_eq(self1->val,self2->val,0) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Double)
  retmethod(z_is_eq(self1->val,self2->val,0) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Complex)
  retmethod(Z_is_eq(self1->val,self2->val) ? True : False);
endmethod

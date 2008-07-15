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
 | $Id: Number.c,v 1.3 2008/07/15 08:00:46 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/TrueFalse.h>
#include <cos/stdgen.h>

makclass(Number  , Value);
makclass(Integral, Number);
makclass(Floating, Number);

makclass(Int     , Integral);
makclass(UInt    , Integral);
makclass(Long    , Integral);
makclass(ULong   , Integral);

makclass(Char    , Int);
makclass(Short   , Int);
makclass(UChar   , UInt);
makclass(UShort  , UInt);

makclass(Double  , Floating);
makclass(Complex , Floating);

// ----- copy constructor

defmethod(OBJ, ginitWith, Int, Int)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Long, Int)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Long, Long)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Double, Int)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Double, Long)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Double, Double)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Int)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Long)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Double)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, Complex, Double, Double)
  self1->val = cpx_make(self2->val, self3->val);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Complex, Complex)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, UInt, UInt)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, ULong, UInt)
  self1->val = self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, ULong, ULong)
  self1->val = self2->val;
  retmethod(_1);
endmethod

// ----- value

defmethod(S8, gchar, Char)
  retmethod(self->Int.val);
endmethod

defmethod(U8, guchar, UChar)
  retmethod(self->UInt.val);
endmethod

defmethod(S16, gshort, Short)
  retmethod(self->Int.val);
endmethod

defmethod(U16, gushort, UShort)
  retmethod(self->UInt.val);
endmethod

defmethod(S32, gint, Int)
  retmethod(self->val);
endmethod

defmethod(U32, guint, UInt)
  retmethod(self->val);
endmethod

defmethod(S64, glong, Int)
  retmethod(self->val);
endmethod

defmethod(U64, gulong, UInt)
  retmethod(self->val);
endmethod

defmethod(S64, glong, Long)
  retmethod(self->val);
endmethod

defmethod(U64, gulong, ULong)
  retmethod(self->val);
endmethod

defmethod(double, gdouble, Int)
  retmethod(self->val);
endmethod

defmethod(double, gdouble, Long)
  retmethod(self->val);
endmethod

defmethod(double, gdouble, Double)
  retmethod(self->val);
endmethod

defmethod(COMPLEX, gcomplex, Int)
  retmethod(self->val);
endmethod

defmethod(COMPLEX, gcomplex, Long)
  retmethod(self->val);
endmethod

defmethod(COMPLEX, gcomplex, Double)
  retmethod(self->val);
endmethod

defmethod(COMPLEX, gcomplex, Complex)
  retmethod(self->val);
endmethod

// ----- negate

defmethod(OBJ, gnegate, Int)
  self1->val = -self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gnegate, Long)
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

defmethod(OBJ, ginvert, Double)
  self1->val = 1/self1->val;
  retmethod(_1);
endmethod

defmethod(OBJ, ginvert, Complex)
  self1->val = 1/self1->val;
  retmethod(_1);
endmethod

// ----- addTo

defmethod(OBJ, gaddTo, Int, Int)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Long, Int)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Long, Long)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Double, Int)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Double, Long)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Double, Double)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Int)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, Complex, Long)
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

defmethod(OBJ, gaddTo, UInt, UInt)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, ULong, UInt)
  self1->val += self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gaddTo, ULong, ULong)
  self1->val += self2->val;
  retmethod(_1);
endmethod

// ----- subTo

defmethod(OBJ, gsubTo, Int, Int)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Long, Int)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Long, Long)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Double, Int)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Double, Long)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Double, Double)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Int)
  self1->val -= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gsubTo, Complex, Long)
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

defmethod(OBJ, gmulBy, Int, Int)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Long, Int)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Long, Long)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Double, Int)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Double, Long)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Double, Double)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Int)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, Complex, Long)
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

defmethod(OBJ, gmulBy, UInt, UInt)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, ULong, UInt)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmulBy, ULong, ULong)
  self1->val *= self2->val;
  retmethod(_1);
endmethod

// ----- divBy

defmethod(OBJ, gdivBy, Int, Int)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Long, Int)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Long, Long)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Double, Int)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Double, Long)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Double, Double)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Int)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, Complex, Long)
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

defmethod(OBJ, gdivBy, UInt, UInt)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, ULong, UInt)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gdivBy, ULong, ULong)
  self1->val /= self2->val;
  retmethod(_1);
endmethod

// ----- modulo

defmethod(OBJ, gmodulo, Int, Int)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, Long, Int)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, Long, Long)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, UInt, UInt)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, ULong, UInt)
  self1->val %= self2->val;
  retmethod(_1);
endmethod

defmethod(OBJ, gmodulo, ULong, ULong)
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

defmethod(OBJ, gcompare, Int, Int)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int, Long)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Int, Double)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Long, Int)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Long, Long)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Long, Double)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Double, Int)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Double, Long)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, Double, Double)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, UInt, UInt)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, UInt, ULong)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, ULong, UInt)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

defmethod(OBJ, gcompare, ULong, ULong)
  retmethod(self1->val < self2->val ? Lesser :
	    self1->val > self2->val ? Greater : Equal);
endmethod

// ----------

// ----- bool

defmethod(OBJ, gbool, Int)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, UInt)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, Long)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, ULong)
  retmethod(self->val ? True : False);
endmethod

defmethod(OBJ, gbool, Double)
  retmethod(dbl_equal(self->val,0) ? True : False);
endmethod

defmethod(OBJ, gbool, Complex)
  retmethod(cpx_equal(self->val,0) ? True : False);
endmethod

// ----- not

defmethod(OBJ, gnot, Int)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, UInt)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, Long)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, ULong)
  retmethod(self->val ? False : True);
endmethod

defmethod(OBJ, gnot, Double)
  retmethod(dbl_equal(self->val,0) ? False : True);
endmethod

defmethod(OBJ, gnot, Complex)
  retmethod(cpx_equal(self->val,0) ? False : True);
endmethod

// ----- equal

defmethod(OBJ, gequal, Int, Int)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Int, Long)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Int, Double)
  retmethod(dbl_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Int, Complex)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Long, Int)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Long, Long)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, Long, Double)
  retmethod(dbl_equal(self1->val,self1->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Long, Complex)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Int)
  retmethod(dbl_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Long)
  retmethod(dbl_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Double)
  retmethod(dbl_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Double, Complex)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Int)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Long)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Double)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, Complex, Complex)
  retmethod(cpx_equal(self1->val,self2->val) ? True : False);
endmethod

defmethod(OBJ, gequal, UInt, UInt)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, UInt, ULong)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, ULong, UInt)
  retmethod(self1->val == self2->val ? True : False);
endmethod

defmethod(OBJ, gequal, ULong, ULong)
  retmethod(self1->val == self2->val ? True : False);
endmethod


#ifndef COS_NUMBER_H
#define COS_NUMBER_H

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
 | $Id: Number.h,v 1.1 2008/06/27 16:17:14 ldeniau Exp $
 |
*/

#include <cos/Value.h>

// ----- number

defclass(Number,Value)
endclass

defclass(Integral,Number)
endclass

defclass(Floating,Number)
endclass

// ----- integral

defclass(Int32,Integral)
  S32 val;
endclass

defclass(Int64,Integral)
  S64 val;
endclass

defclass(Size,Integral)
  size_t val;
endclass

defclass(Char ,Int32) endclass
defclass(Short,Int32) endclass
defclass(Int  ,Int32) endclass
defclass(Long ,Int64) endclass

// ----- floating

defclass(Double,Floating)
  double val;
endclass

defclass(Complex,Floating)
  _Complex double val;
endclass

// ----- automatic constructors

#define aChar(val) ( (OBJ)&(struct Char) {{ \
        {{{{ COS_CLS_NAME(Char).Behavior.id, COS_RC_AUTO }}}}, \
         (char)(val) }} )

#define aShort(val) ( (OBJ)&(struct Short) {{ \
        {{{{ COS_CLS_NAME(Short).Behavior.id, COS_RC_AUTO }}}}, \
         (signed short)(val) }} )

#define aInt(val) ( (OBJ)&(struct Int) {{ \
        {{{{ COS_CLS_NAME(Int).Behavior.id, COS_RC_AUTO }}}}, \
         (val) }} )

#define aLong(val) ( (OBJ)&(struct Long) {{ \
        {{{{ COS_CLS_NAME(Long).Behavior.id, COS_RC_AUTO }}}}, \
         (val) }} )

#define aSize(val) ( (OBJ)&(struct Size) {{ \
        {{{{ COS_CLS_NAME(Size).Behavior.id, COS_RC_AUTO }}}}, \
         (val) }} )

#define aDouble(val) ( (OBJ)&(struct Double) { \
        {{{{ COS_CLS_NAME(Double).Behavior.id, COS_RC_AUTO }}}}, \
         (val) } )

#define aComplex(val) ( (OBJ)&(struct Complex) { \
        {{{{ COS_CLS_NAME(Complex).Behavior.id, COS_RC_AUTO }}}}, \
         (val) } )

#endif // COS_NUMBER_H

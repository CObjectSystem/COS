/*
 o---------------------------------------------------------------------o
 |
 | COS TrueFalse
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
 | $Id: TrueFalse.c,v 1.5 2009/08/08 16:36:10 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/TrueFalse.h>

#include <cos/gen/compare.h>
#include <cos/gen/logic.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// ----- Tristate boolean logic (with uncertain/indeterminate state)

useclass(TrueFalse);

// ----- conversion

defmethod(BOOL, gbool, mTrue)
  retmethod(YES);
endmethod

defmethod(BOOL, gbool, mTrueFalse)
  retmethod(NO);
endmethod

defmethod(I32, gint, mTrue)
  retmethod(1);
endmethod

defmethod(I32, gint, mFalse)
  retmethod(0);
endmethod

defmethod(I32, gint, mTrueFalse)
  retmethod(-1);
endmethod

// ----- tables

/*
 EQU | F | T | ?
 ----+---+---+---
   F | T | F | ?
   T | F | T | ?
   ? | ? | ? | ?
 */

defmethod(OBJ, gisEqual, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

defmethod(OBJ, gisEqual, mTrue, mTrueFalse)
  retmethod(_2);
endmethod

defmethod(OBJ, gisEqual, mTrueFalse, mTrue)
  retmethod(_1);
endmethod

defmethod(OBJ, gisEqual, mFalse, mFalse)
  retmethod(True);
endmethod

/*
 NEQ | F | T | ?
 ----+---+---+---
   F | F | T | ?
   T | T | F | ?
   ? | ? | ? | ?
 */

defmethod(OBJ, gisNotEqual, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

defmethod(OBJ, gisNotEqual, mFalse, mTrueFalse)
  retmethod(_2);
endmethod

defmethod(OBJ, gisNotEqual, mTrueFalse, mFalse)
  retmethod(_1);
endmethod

defmethod(OBJ, gisNotEqual, mTrue, mTrue)
  retmethod(False);
endmethod

/*
 NOT | F | T | ?
 ----+---+---+---
     | T | F | ?
 */

defmethod(OBJ, gnot, mFalse)
  retmethod(True);
endmethod

defmethod(OBJ, gnot, mTrue)
  retmethod(False);
endmethod

defmethod(OBJ, gnot, mTrueFalse)
  retmethod(TrueFalse);
endmethod

/*
 AND | F | T | ?
 ----+---+---+---
   F | F | F | F
   T | F | T | ?
   ? | F | ? | ?
*/

defmethod(OBJ, gand, mFalse, mTrueFalse)
  retmethod(False);
endmethod

defmethod(OBJ, gand, mTrueFalse, mFalse)
  retmethod(False);
endmethod

defmethod(OBJ, gand, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

defmethod(OBJ, gand, mTrue, mTrue)
  retmethod(True);
endmethod

/*
  OR | F | T | ?
 ----+---+---+---
   F | F | T | ?
   T | T | T | T
   ? | ? | T | ?
 */

defmethod(OBJ, gor, mTrue, mTrueFalse)
  retmethod(True);
endmethod

defmethod(OBJ, gor, mTrueFalse, mTrue)
  retmethod(True);
endmethod

defmethod(OBJ, gor, mFalse, mFalse)
  retmethod(False);
endmethod

defmethod(OBJ, gor, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

/*
 XOR | F | T | ?  { XOR = NOT (P EQU Q) }
 ----+---+---+---
   F | F | T | ?
   T | T | F | ?
   ? | ? | ? | ?
 */

defmethod(OBJ, gxor, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

defmethod(OBJ, gxor, mFalse, mTrueFalse)
  retmethod(_2);
endmethod

defmethod(OBJ, gxor, mTrueFalse, mFalse)
  retmethod(_1);
endmethod

defmethod(OBJ, gxor, mTrue, mTrue)
  retmethod(False);
endmethod

/*
  => | F | T | ?  { IMPLIES = NOT P OR Q }
 ----+---+---+---
   F | T | T | T
   T | F | T | ?
   ? | ? | T | ?
 */

defmethod(OBJ, gimplies, mFalse, mTrueFalse)
  retmethod(True);
endmethod

defmethod(OBJ, gimplies, mTrueFalse, mTrue)
  retmethod(True);
endmethod

defmethod(OBJ, gimplies, mTrue, mFalse)
  retmethod(False);
endmethod

defmethod(OBJ, gimplies, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod


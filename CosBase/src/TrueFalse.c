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
 | $Id: TrueFalse.c,v 1.2 2008/10/20 14:41:29 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/TrueFalse.h>
#include <cos/gen/object.h>
#include <cos/gen/logic.h>

// -----

makclass(TrueFalse,Nil);
makclass(True,TrueFalse);
makclass(False,TrueFalse);

// ----- Tristate boolean logic (with uncertain/indeterminate state)

useclass(TrueFalse);

/*
 ID  | F | T | ?
 ----+---+---+---
     | F | T | ?
 */

defmethod(OBJ, gbool, mTrueFalse)
  retmethod(_1);
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
 EQU | F | T | ?
 ----+---+---+---
   F | T | F | ?
   T | F | T | ?
   ? | ? | ? | ?
 */

defmethod(OBJ, gequal, mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

defmethod(OBJ, gequal, mTrue, mTrueFalse)
  retmethod(_2);
endmethod

defmethod(OBJ, gequal, mTrueFalse, mTrue)
  retmethod(_1);
endmethod

defmethod(OBJ, gequal, mFalse, mFalse)
  retmethod(True);
endmethod

/*
 AND | F | T | ?      ALL | F | T | ?
 ----+---+---+---     ----+---+---+---
   F | F | F | F        F | N | N | N
   T | F | T | ?        T | F | T | ?
   ? | F | ? | ?        ? | F | ? | ?
*/

defmethod(OBJ, gall, mFalse, mTrueFalse)
  retmethod(Nil);
endmethod

defmethod(OBJ, gand, mFalse, mTrueFalse)
  retmethod(False);
endmethod

defalias (OBJ, (gand)gall, mTrueFalse, mFalse);
defmethod(OBJ,  gand     , mTrueFalse, mFalse)
  retmethod(False);
endmethod

defalias (OBJ, (gand)gall, mTrueFalse, mTrueFalse);
defmethod(OBJ,  gand     , mTrueFalse, mTrueFalse)
  retmethod(TrueFalse);
endmethod

defalias (OBJ, (gand)gall, mTrue, mTrue);
defmethod(OBJ,  gand     , mTrue, mTrue)
  retmethod(True);
endmethod

/*
  OR | F | T | ?      ANY | F | T | ?
 ----+---+---+---     ----+---+---+---
   F | F | T | ?        F | F | T | ?
   T | T | T | T        T | N | N | N
   ? | ? | T | ?        ? | ? | T | ?
 */

defmethod(OBJ, gany, mTrue, mTrueFalse)
  retmethod(Nil);
endmethod

defmethod(OBJ, gor, mTrue, mTrueFalse)
  retmethod(True);
endmethod

defalias (OBJ, (gor)gany, mTrueFalse, mTrue);
defmethod(OBJ,  gor     , mTrueFalse, mTrue)
  retmethod(True);
endmethod

defalias (OBJ, (gor)gany, mFalse, mFalse);
defmethod(OBJ,  gor     , mFalse, mFalse)
  retmethod(False);
endmethod

defalias (OBJ, (gor)gany, mTrueFalse, mTrueFalse);
defmethod(OBJ,  gor     , mTrueFalse, mTrueFalse)
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


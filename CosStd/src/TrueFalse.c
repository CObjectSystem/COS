/**
 * C Object System
 * COS TrueFalse
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/Object.h>
#include <cos/TrueFalse.h>

#include <cos/gen/relop.h>
#include <cos/gen/logicop.h>
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


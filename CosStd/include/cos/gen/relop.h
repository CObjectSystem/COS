#ifndef COS_GEN_RELOP_H
#define COS_GEN_RELOP_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generic for relational operators
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
 | $Id: relop.h,v 1.1 2010/01/03 12:28:56 ldeniau Exp $
 |
*/

#include <cos/GRelOp.h>

/* NOTE-USER: object comparison

   gcompare(a,b)
     | a < b     = Lesser
     | a > b     = Geater
     | otherwise = Equal

   gisEqual(a,b)
     | a == b    = True
     | otherwise = False

   gisLesser(a,b)
     | a < b     = True
     | otherwise = False

   gisGreater(a,b)
     | a > b     = True
     | otherwise = False
*/

// comparison
defgeneric(OBJ, (GCompare       ) gcompare         , _1, _2);
defgeneric(OBJ, (GEqual         ) gisEqual         , _1, _2);
defgeneric(OBJ, (GLesser        ) gisLesser        , _1, _2);
defgeneric(OBJ, (GGreater       ) gisGreater       , _1, _2);
defgeneric(OBJ, (GLesserOrEqual ) gisLesserOrEqual , _1, _2);
defgeneric(OBJ, (GGreaterOrEqual) gisGreaterOrEqual, _1, _2);
defgeneric(OBJ, (GNotEqual      ) gisNotEqual      , _1, _2);

// hash
defgeneric(U32, (GHash          ) ghash, _1);

// min, max (fun should return Ordered or the min, max)
defgeneric(OBJ, (GMin           ) gmin, _1, _2 or fun);
defgeneric(OBJ, (GMax           ) gmax, _1, _2 or fun);
// note: gmin   (_1, gmin(__1,__2)) should work like
//       greduce(_1, gmin(__1,__2), maxVal)

#endif // COS_GEN_RELOP_H

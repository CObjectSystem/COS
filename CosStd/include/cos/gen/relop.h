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
 | $Id: relop.h,v 1.5 2010/05/25 15:33:39 ldeniau Exp $
 |
*/

#include <cos/gen/op/GRelOp.h>

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
defgeneric(OBJ, (G_compare         ) gcompare         , _1, _2);
defgeneric(OBJ, (G_isEqual         ) gisEqual         , _1, _2);
defgeneric(OBJ, (G_isLesser        ) gisLesser        , _1, _2);
defgeneric(OBJ, (G_isGreater       ) gisGreater       , _1, _2);
defgeneric(OBJ, (G_isLesserOrEqual ) gisLesserOrEqual , _1, _2);
defgeneric(OBJ, (G_isGreaterOrEqual) gisGreaterOrEqual, _1, _2);
defgeneric(OBJ, (G_isNotEqual      ) gisNotEqual      , _1, _2);

// hash
defgeneric(U64, (G_hash) ghash, _1);

// min, max (fun should return Ordered or the min, max)
defgeneric(OBJ, (G_min ) gmin, _1, _2 or fun);
defgeneric(OBJ, (G_max ) gmax, _1, _2 or fun);

#endif // COS_GEN_RELOP_H

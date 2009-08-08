#ifndef COS_GEN_COMPARE_H
#define COS_GEN_COMPARE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS comparison generics
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
 | $Id: compare.h,v 1.2 2009/08/08 16:36:09 ldeniau Exp $
 |
*/

#include <cos/Generic.h>

/* NOTE-USER: object comparison

   gcompare(a,b) =
     | a < b     -> Lesser
     | a > b     -> Geater
     | otherwise -> Equal

   gisEqual(a,b) =
     | a == b    -> True
     | otherwise -> False

   gisLesser(a,b) =
     | a < b     -> True
     | otherwise -> False

   gisGreater(a,b) =
     | a > b     -> True
     | otherwise -> False

   gmin(a,b) =
     | a > b     -> b
     | otherwise -> a

   gmax(a,b) =
     | a < b     -> b
     | otherwise -> a
*/

// comparison
defgeneric(OBJ, (GenComparator)gcompare         , _1, _2);
defgeneric(OBJ, (GenComparator)gisEqual         , _1, _2);
defgeneric(OBJ, (GenComparator)gisLesser        , _1, _2);
defgeneric(OBJ, (GenComparator)gisGreater       , _1, _2);
defgeneric(OBJ, (GenComparator)gisLesserOrEqual , _1, _2);
defgeneric(OBJ, (GenComparator)gisGreaterOrEqual, _1, _2);
defgeneric(OBJ, (GenComparator)gisNotEqual      , _1, _2);

// min, max
defgeneric(OBJ, gmin, _1, _2);
defgeneric(OBJ, gmax, _1, _2);

// hash
defgeneric(U32, (GenOperator)ghash, _1);

#endif // COS_GEN_COMPARE_H

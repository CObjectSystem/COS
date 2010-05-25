#ifndef COS_GEN_COLLECTION_H
#define COS_GEN_COLLECTION_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for collections
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
 | $Id: collection.h,v 1.4 2010/05/25 15:33:39 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// check for elements
defgeneric(OBJ, gisEmpty, _1);

// foreach (discard returned value)
defgeneric(void, gforeach     , _1, fun);
defgeneric(void, gforeach2    , _1, _2, fun);
defgeneric(void, gforeach3    , _1, _2, _3, fun);
defgeneric(void, gforeach4    , _1, _2, _3, _4, fun);
defgeneric(void, gforeachWhile, _1, fun); // stop if fun returns Nil

// apply (in-place map on _1, return _1)
defgeneric(OBJ, gapply     , fun, _1);
defgeneric(OBJ, gapply2    , fun, _1, _2);
defgeneric(OBJ, gapply3    , fun, _1, _2, _3);
defgeneric(OBJ, gapply4    , fun, _1, _2, _3, _4);
defgeneric(OBJ, gapplyIf   , fun, _1); // reject if fun returns Nil
defgeneric(OBJ, gapplyWhile, fun, _1); // stop   if fun returns Nil

// map
defgeneric(OBJ, gmap     , fun, _1);
defgeneric(OBJ, gmap2    , fun, _1, _2);
defgeneric(OBJ, gmap3    , fun, _1, _2, _3);
defgeneric(OBJ, gmap4    , fun, _1, _2, _3, _4);
defgeneric(OBJ, gmapIf   , fun, _1); // reject if fun returns Nil
defgeneric(OBJ, gmapWhile, fun, _1); // stop   if fun returns Nil

// filter
defgeneric(OBJ, gselect     , _1, fun); // select if    fun returns True
defgeneric(OBJ, gselectWhile, _1, fun); // select while fun returns True

// filter-out
defgeneric(OBJ, greject     , _1, fun); // reject if    fun returns True
defgeneric(OBJ, grejectWhile, _1, fun); // reject while fun returns True

// reduce
defgeneric(OBJ, greduce , _1, fun);                // foldl1
defgeneric(OBJ, greduce1, _1, fun, ini);           // foldl
defgeneric(OBJ, greduce2, _1, fun, ini, fin);      // foldl with lookahead

// accumulate
defgeneric(OBJ, gaccumulate , _1, fun);            // scanl1
defgeneric(OBJ, gaccumulate1, _1, fun, ini);       // scanl
defgeneric(OBJ, gaccumulate2, _1, fun, ini, fin);  // scanl with lookahead

#endif // COS_GEN_COLLECTION_H

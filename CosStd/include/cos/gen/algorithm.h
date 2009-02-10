#ifndef COS_GEN_ALGORITHM_H
#define COS_GEN_ALGORITHM_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for algorithms
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
 | $Id: algorithm.h,v 1.7 2009/02/10 16:57:09 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// in place (returned value is discarded if any)
defgeneric(void, gapply  , _1, fun);
defgeneric(void, greverse, _1);

// map
defgeneric(OBJ, gmap , fun, _1);
defgeneric(OBJ, gmap2, fun, _1, _2);
defgeneric(OBJ, gmap3, fun, _1, _2, _3);
defgeneric(OBJ, gmap4, fun, _1, _2, _3, _4);

// filter, reduce
defgeneric(OBJ, gfilter    , _1, fun);
defgeneric(OBJ, greduce    , _1, fun, res);
defgeneric(OBJ, gaccumulate, _1, fun, acc);

// zip
defgeneric(OBJ, gzip , _1, _2);
defgeneric(OBJ, gzip3, _1, _2, _3);
defgeneric(OBJ, gzip4, _1, _2, _3, _4);
defgeneric(OBJ, gzipn, _1);

// cat
defgeneric(OBJ, gcat , _1, _2);
defgeneric(OBJ, gcat3, _1, _2, _3);
defgeneric(OBJ, gcat4, _1, _2, _3, _4);
defgeneric(OBJ, gcatn, _1);

// all, any, min, max
defgeneric(OBJ, gall, _1, fun);
defgeneric(OBJ, gany, _1, fun);
defgeneric(OBJ, gmin, _1);
defgeneric(OBJ, gmax, _1);

// sorting (in place, fun must return Ordered)
defgeneric(void, gsort    , _1, fun);
defgeneric(OBJ , gisSorted, _1); // return True or False

// linear      find if fun returns TrueFalse
// logarithmic find if fun returns Ordered
defgeneric(OBJ, gfind, _1, obj, fun);

// bag-like algorithms
defgeneric(OBJ, gunique, _1, fun);
defgeneric(OBJ, ggroup , _1, fun);
defgeneric(OBJ, gsplit , _1, fun);

// set-like algorithms
defgeneric(OBJ, gdiff     , _1, _2, fun);
defgeneric(OBJ, gunion    , _1, _2, fun);
defgeneric(OBJ, gintersect, _1, _2, fun);

#endif // COS_GEN_ALGORITHM_H


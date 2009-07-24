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
 | $Id: algorithm.h,v 1.12 2009/07/24 20:49:58 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// in place (returned value of fun is discarded if any)
defgeneric(void, gforeach, _1, fun);
defgeneric(void, gpermute, _1, idx);
defgeneric(void, greverse, _1);

// map
defgeneric(OBJ , gmap , fun, _1);
defgeneric(OBJ , gmap2, fun, _1, _2);
defgeneric(OBJ , gmap3, fun, _1, _2, _3);
defgeneric(OBJ , gmap4, fun, _1, _2, _3, _4);
defgeneric(OBJ , gmapn, fun, _1);

// filter, fold, scan
defgeneric(OBJ , gfilter, _1, fun);
defgeneric(OBJ , gfoldl , _1, fun, ini);
defgeneric(OBJ , gfoldr , _1, fun, ini);
defgeneric(OBJ , gscanl , _1, fun, ini);
defgeneric(OBJ , gscanr , _1, fun, ini);

// zip
defgeneric(OBJ , gzip , _1, _2);
defgeneric(OBJ , gzip3, _1, _2, _3);
defgeneric(OBJ , gzip4, _1, _2, _3, _4);
defgeneric(OBJ , gzipn, _1);

// cat
defgeneric(OBJ , gcat , _1, _2);
defgeneric(OBJ , gcat3, _1, _2, _3);
defgeneric(OBJ , gcat4, _1, _2, _3, _4);
defgeneric(OBJ , gcatn, _1);

// all, any, min, max
defgeneric(OBJ , gall, _1, fun); // fun should return TrueFalse
defgeneric(OBJ , gany, _1, fun); // fun should return TrueFalse
defgeneric(OBJ , gmin, _1);
defgeneric(OBJ , gmax, _1);

// sorting (fun must return Ordered)
defgeneric(void, gsort    , _1, fun); // in place
defgeneric(OBJ , gisort   , _1, fun); // return an Array of indexes
defgeneric(OBJ , gisSorted, _1, fun); // return True or False

// linear search if fun returns TrueFalse
// binary search if fun returns Ordered
defgeneric(OBJ , gfind , _1, obj, fun);
defgeneric(OBJ , gifind, _1, obj, fun); // return an index or a key

// seq-like algorithms (fun must return TrueFalse)
defgeneric(OBJ , gunique, _1, fun); // remove contiguous equal elements
defgeneric(OBJ , ggroup , _1, fun);
defgeneric(OBJ , gsplit , _1, fun);

// set-like algorithms
defgeneric(OBJ , gdiff     , _1, _2);
defgeneric(OBJ , gunion    , _1, _2);
defgeneric(OBJ , gintersect, _1, _2);

#endif // COS_GEN_ALGORITHM_H


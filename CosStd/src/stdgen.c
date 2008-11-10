/*
 o---------------------------------------------------------------------o
 |
 | COS standard generics
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
 | $Id: stdgen.c,v 1.2 2008/11/10 08:00:42 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>

// -------------------------
#include <cos/gen/algorithm.h>

// in place (returned value is discarded if any)
makgeneric(OBJ, gapply  , fun, _1);
makgeneric(OBJ, greverse, _1);

// map
makgeneric(OBJ, gmap   , fun, _1);
makgeneric(OBJ, gmap2  , fun, _1, _2);
makgeneric(OBJ, gmap3  , fun, _1, _2, _3);
makgeneric(OBJ, gmap4  , fun, _1, _2, _3, _4);

// filter, reduce
makgeneric(OBJ, gfilter    , fun, _1);
makgeneric(OBJ, greduce    , fun, res, _1);
makgeneric(OBJ, gaccumulate, fun, acc, _1);

// zip
makgeneric(OBJ, gzip , _1, _2);
makgeneric(OBJ, gzip3, _1, _2, _3);
makgeneric(OBJ, gzip4, _1, _2, _3, _4);
makgeneric(OBJ, gzip5, _1, _2, _3, _4, _5);
makgeneric(OBJ, gzipn, _1);

// all, any, min, max
makgeneric(OBJ, gall, fun, _1);
makgeneric(OBJ, gany, fun, _1);
makgeneric(OBJ, gmin, _1);
makgeneric(OBJ, gmax, _1);

// sorting (in place, fun must return Ordered)
makgeneric(OBJ, gsort, fun, _1);

// linear      find if fun returns TrueFalse
// logarithmic find if fun returns Ordered
makgeneric(OBJ, gfind, fun, obj, _1);

// bag-like algorithms
makgeneric(OBJ, gunique, _1);
makgeneric(OBJ, group  , _1);
makgeneric(OBJ, gsplit , _1);

// set-like algorithms
makgeneric(OBJ, gdiff     , _1, _2);
makgeneric(OBJ, gunion    , _1, _2);
makgeneric(OBJ, gintersect, _1, _2);

// -------------------------
#include <cos/gen/container.h>

// generic accessors
makgeneric(OBJ, gput   , to, obj);
makgeneric(OBJ, gget   , from);
makgeneric(OBJ, gdrop  , from);
makgeneric(OBJ, gupdate, to, obj);

// generic accessors with location
makgeneric(OBJ, gputAt   , to, obj, at);
makgeneric(OBJ, ggetAt   , from, at);
makgeneric(OBJ, gdropAt  , from, at);
makgeneric(OBJ, gupdateAt, to, obj, at);

// stack-like accessors
makgeneric(OBJ, gpush, to, obj);     // alias for gput
makgeneric(OBJ, gtop , from);        // alias for gget
makgeneric(OBJ, gpop , from);        // alias for gdrop

// seq-like accessor
makgeneric(OBJ, gappend, to  , obj);
makgeneric(OBJ, ginsert, to  , obj);
makgeneric(OBJ, gremove, from, obj);
makgeneric(OBJ, gconcat, to  , obj);
makgeneric(OBJ, glast  , from);

// raw data (copy) accessors
makgeneric(void, ggetValue  , from, what);
makgeneric(void, ggetValueAt, from, what, at);

// -------------------------
#include <cos/gen/functor.h>

makgeneric(OBJ, geval , fun);
makgeneric(OBJ, geval1, fun, (OBJ)arg1);
makgeneric(OBJ, geval2, fun, (OBJ)arg1,(OBJ)arg2);
makgeneric(OBJ, geval3, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3);
makgeneric(OBJ, geval4, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4);
makgeneric(OBJ, geval5, fun, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4,(OBJ)arg5);

// -------------------------
#include <cos/gen/logic.h>

// return True, False or TrueFalse (= uncertain, undetermined)
makgeneric(OBJ, gnot    , _1);
makgeneric(OBJ, gand    , _1, _2);
makgeneric(OBJ, gor     , _1, _2);
makgeneric(OBJ, gxor    , _1, _2);
makgeneric(OBJ, gimplies, _1, _2);

// -------------------------
#include <cos/gen/operator.h>

// not in place
makgeneric(OBJ, gneg, _1);
makgeneric(OBJ, ginv, _1);
makgeneric(OBJ, gadd, _1, _2);
makgeneric(OBJ, gsub, _1, _2);
makgeneric(OBJ, gmul, _1, _2);
makgeneric(OBJ, gdiv, _1, _2);
makgeneric(OBJ, gmod, _1, _2);

// in place
makgeneric(OBJ, gnegate, _1);
makgeneric(OBJ, ginvert, _1);
makgeneric(OBJ, gaddTo , _1, _2);
makgeneric(OBJ, gsubTo , _1, _2);
makgeneric(OBJ, gmulBy , _1, _2);
makgeneric(OBJ, gdivBy , _1, _2);
makgeneric(OBJ, gmodulo, _1, _2);


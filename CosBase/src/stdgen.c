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
 | $Id: stdgen.c,v 1.19 2008/10/24 14:17:15 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// -------------------------
#include <cos/gen/access.h>

// generic accessors
makgeneric(OBJ, gput     , to, what);
makgeneric(OBJ, gget     , from);
makgeneric(OBJ, gdrop    , from);
makgeneric(OBJ, gupdate  , to, what);

// generic accessors with location
makgeneric(OBJ, gputAt   , to, what, at);
makgeneric(OBJ, ggetAt   , from, at);
makgeneric(OBJ, gdropAt  , from, at);
makgeneric(OBJ, gupdateAt, to, what, at);

// stack-like or queue-like accessors
makgeneric(OBJ, gpush    , to, what); // alias for gput
makgeneric(OBJ, gtop     , from);     // alias for gget
makgeneric(OBJ, gpop     , from);     // alias for gdrop

// string-like accessors
makgeneric(OBJ, gconcat  , to, what); // alias for gpush
makgeneric(OBJ, glast    , from);     // alias for gtop

// plain array accessors
makgeneric(void, ggetValue  , from, what);
makgeneric(void, ggetValueAt, from, what, at);

// -------------------------
#include <cos/gen/calc.h>

// not in place
makgeneric(OBJ, gneg   , _1);
makgeneric(OBJ, ginv   , _1);
makgeneric(OBJ, gadd   , _1, _2);
makgeneric(OBJ, gsub   , _1, _2);
makgeneric(OBJ, gmul   , _1, _2);
makgeneric(OBJ, gdiv   , _1, _2);
makgeneric(OBJ, gmod   , _1, _2);

// in place
makgeneric(OBJ, gnegate, _1);
makgeneric(OBJ, ginvert, _1);
makgeneric(OBJ, gaddTo , _1, _2);
makgeneric(OBJ, gsubTo , _1, _2);
makgeneric(OBJ, gmulBy , _1, _2);
makgeneric(OBJ, gdivBy , _1, _2);
makgeneric(OBJ, gmodulo, _1, _2);

// -------------------------
#include <cos/gen/functor.h>

makgeneric(OBJ, geval , _1);
makgeneric(OBJ, geval1, _1, (OBJ)arg1);
makgeneric(OBJ, geval2, _1, (OBJ)arg1,(OBJ)arg2);
makgeneric(OBJ, geval3, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3);
makgeneric(OBJ, geval4, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4);
makgeneric(OBJ, geval5, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4,(OBJ)arg5);

makgeneric(void, gapply , _1, fun);

makgeneric(OBJ , gmap   , _1, fun);
makgeneric(OBJ , gmap2  , _1, _2, fun);
makgeneric(OBJ , gmap3  , _1, _2, _3, fun);
makgeneric(OBJ , gscan  , _1, _2, fun);

makgeneric(OBJ , gfilter, _1, fun);
makgeneric(OBJ , gfold  , _1, _2, fun);
makgeneric(OBJ , gunfold, _1, fun);

makgeneric(OBJ , gsort  , _1, fun);
makgeneric(OBJ , gfind  , _1, obj, fun);

// -------------------------
#include <cos/gen/init.h>

makgeneric(OBJ , ginitWithObj  , _1, (OBJ)_2);
makgeneric(OBJ , ginitWithObj2 , _1, (OBJ)_2, (OBJ)_3);
makgeneric(OBJ , ginitWithObj3 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4);
makgeneric(OBJ , ginitWithObj4 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5);
makgeneric(OBJ , ginitWithObj5 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6);
makgeneric(OBJ , ginitWithObj6 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7);
makgeneric(OBJ , ginitWithObj7 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7, (OBJ)_8);
makgeneric(OBJ , ginitWithObj8 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7, (OBJ)_8, (OBJ)_9);
makgeneric(OBJ , ginitWithObj9 , _1, (OBJ)_2, (OBJ)_3, (OBJ)_4, (OBJ)_5, (OBJ)_6, (OBJ)_7, (OBJ)_8, (OBJ)_9, (OBJ)_10);

makgeneric(OBJ, ginitWithChr , _1, (I8 )val);
makgeneric(OBJ, ginitWithSht , _1, (I16)val);
makgeneric(OBJ, ginitWithInt , _1, (I32)val);
makgeneric(OBJ, ginitWithLng , _1, (I64)val);
makgeneric(OBJ, ginitWithFlt , _1, (R64)val);
makgeneric(OBJ, ginitWithCpx , _1, (C64)val);

makgeneric(OBJ, ginitWithChrPtr , _1, (U32)n, (I8 *)val);
makgeneric(OBJ, ginitWithShtPtr , _1, (U32)n, (I16*)val);
makgeneric(OBJ, ginitWithIntPtr , _1, (U32)n, (I32*)val);
makgeneric(OBJ, ginitWithLngPtr , _1, (U32)n, (I64*)val);
makgeneric(OBJ, ginitWithFltPtr , _1, (U32)n, (R64*)val);
makgeneric(OBJ, ginitWithCpxPtr , _1, (U32)n, (C64*)val);
makgeneric(OBJ, ginitWithObjPtr , _1, (U32)n, (OBJ*)obj);

// -------------------------
#include <cos/gen/logic.h>

makgeneric(OBJ, gbool   , _1);
makgeneric(OBJ, gnot    , _1);
makgeneric(OBJ, gand    , _1, _2);
makgeneric(OBJ, gor     , _1, _2);
makgeneric(OBJ, gxor    , _1, _2);
makgeneric(OBJ, gimplies, _1, _2);

makgeneric(OBJ, gall    , _1, _2);
makgeneric(OBJ, gany    , _1, _2);

// -------------------------
#include <cos/gen/message.h>

// errors and forwarding
makgeneric(void, gunrecognizedMessage1, _1);
makgeneric(void, gunrecognizedMessage2, _1, _2);
makgeneric(void, gunrecognizedMessage3, _1, _2, _3);
makgeneric(void, gunrecognizedMessage4, _1, _2, _3, _4);
makgeneric(void, gunrecognizedMessage5, _1, _2, _3, _4, _5);

// behavior, return True or False
makgeneric(OBJ, gunderstandMessage1, _1, (SEL)msg);
makgeneric(OBJ, gunderstandMessage2, _1, _2, (SEL)msg);
makgeneric(OBJ, gunderstandMessage3, _1, _2, _3, (SEL)msg);
makgeneric(OBJ, gunderstandMessage4, _1, _2, _3, _4, (SEL)msg);
makgeneric(OBJ, gunderstandMessage5, _1, _2, _3, _4, _5, (SEL)msg);

// class instance behavior, return True or False
makgeneric(OBJ, ginstancesUnderstandMessage1, _1, (SEL)msg);
makgeneric(OBJ, ginstancesUnderstandMessage2, _1, _2, (SEL)msg);
makgeneric(OBJ, ginstancesUnderstandMessage3, _1, _2, _3, (SEL)msg);
makgeneric(OBJ, ginstancesUnderstandMessage4, _1, _2, _3, _4, (SEL)msg);
makgeneric(OBJ, ginstancesUnderstandMessage5, _1, _2, _3, _4, _5, (SEL)msg);

// -------------------------
#include <cos/gen/object.h>

// allocator, deallocator
makgeneric(OBJ , galloc        , _1);
makgeneric(OBJ , gallocWithSize, _1, (SIZE)extra);
makgeneric(void, gdealloc      , _1);

// constructors, destructor
makgeneric(OBJ , ginit         , _1);
makgeneric(OBJ , ginitWith     , _1, _2);
makgeneric(OBJ , ginitWith2    , _1, _2, _3);
makgeneric(OBJ , ginitWith3    , _1, _2, _3, _4);
makgeneric(OBJ , ginitWith4    , _1, _2, _3, _4, _5);
makgeneric(OBJ , ginitWithLoc  , _1, _2, (STR)file, (int)line);
makgeneric(OBJ , ginitWithStr  , _1, (STR)str);
makgeneric(OBJ , gdeinit       , _1);

// ownership
makgeneric(OBJ , gretain       , _1);
makgeneric(OBJ , grelease      , _1);
makgeneric(OBJ , gdiscard      , _1);
makgeneric(OBJ , gautoRelease  , _1);
makgeneric(U32 , gretainCount  , _1);

// identity, conversion, coercion
makgeneric(OBJ , gisKindOf     , _1, _2);
makgeneric(OBJ , gisInstanceOf , _1, _2);
makgeneric(OBJ , gclass        , _1);
makgeneric(STR , gclassName    , _1);

// inheritance
makgeneric(OBJ , gsuperClass   , _1);

// comparison
makgeneric(OBJ , gequal        , _1, _2);
makgeneric(OBJ , gcompare      , _1, _2);
makgeneric(U32 , ghash         , _1);

// adjust object
makgeneric(OBJ , gadjust       , _1);

// exception
makgeneric(void, gthrow        , _1, (STR)file, (int)line);

// contract
makgeneric(void, ginvariant    , _1, (STR)file, (int)line);

// initialization
makgeneric(void, ginitialize  , _1);
makgeneric(void, gdeinitialize, _1);

// -------------------------
#include <cos/gen/value.h>

makgeneric(STR  , gstr , _1);
makgeneric(U32  , gsize, _1);
makgeneric(void*, gptr, _1);

makgeneric(I8   , gchr, _1);
makgeneric(I16  , gsht, _1);
makgeneric(I32  , gint, _1);
makgeneric(I64  , glng, _1);
makgeneric(R64  , gflt, _1);
makgeneric(C64  , gcpx, _1);

makgeneric(I8   , gchrAt, _1, at);
makgeneric(I16  , gshtAt, _1, at);
makgeneric(I32  , gintAt, _1, at);
makgeneric(I64  , glngAt, _1, at);
makgeneric(R64  , gfltAt, _1, at);
makgeneric(C64  , gcpxAt, _1, at);

makgeneric(I8*  , gchrPtr, _1);
makgeneric(I16* , gshtPtr, _1);
makgeneric(I32* , gintPtr, _1);
makgeneric(I64* , glngPtr, _1);
makgeneric(R64* , gfltPtr, _1);
makgeneric(C64* , gcpxPtr, _1);


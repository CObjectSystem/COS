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
 | $Id: stdgen.c,v 1.5 2008/07/15 08:00:46 ldeniau Exp $
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
#include <cos/gen/eval.h>

makgeneric(OBJ, geval , _1);
makgeneric(OBJ, geval1, _1, (OBJ)arg1);
makgeneric(OBJ, geval2, _1, (OBJ)arg1,(OBJ)arg2);
makgeneric(OBJ, geval3, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3);
makgeneric(OBJ, geval4, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4);
makgeneric(OBJ, geval5, _1, (OBJ)arg1,(OBJ)arg2,(OBJ)arg3,(OBJ)arg4,(OBJ)arg5);

// -------------------------
#include <cos/gen/init.h>

makgeneric(OBJ, ginitWithChr , _1, (S8 )val);
makgeneric(OBJ, ginitWithSht , _1, (S32)val);
makgeneric(OBJ, ginitWithInt , _1, (S32)val);
makgeneric(OBJ, ginitWithLng , _1, (S64)val);

makgeneric(OBJ, ginitWithUChr, _1, (U8 )val);
makgeneric(OBJ, ginitWithUSht, _1, (U16)val);
makgeneric(OBJ, ginitWithUInt, _1, (U32)val);
makgeneric(OBJ, ginitWithULng, _1, (U64)val);

makgeneric(OBJ, ginitWithDbl , _1, (double )val);
makgeneric(OBJ, ginitWithCpx , _1, (COMPLEX)val);

makgeneric(OBJ, ginitWithChrPtr , _1, (U32)n, (S8 *)val);
makgeneric(OBJ, ginitWithShtPtr , _1, (U32)n, (S16*)val);
makgeneric(OBJ, ginitWithIntPtr , _1, (U32)n, (S32*)val);
makgeneric(OBJ, ginitWithLngPtr , _1, (U32)n, (S64*)val);

makgeneric(OBJ, ginitWithUChrPtr, _1, (U32)n, (U8 *)val);
makgeneric(OBJ, ginitWithUShtPtr, _1, (U32)n, (U16*)val);
makgeneric(OBJ, ginitWithUIntPtr, _1, (U32)n, (U32*)val);
makgeneric(OBJ, ginitWithULngPtr, _1, (U32)n, (U64*)val);

makgeneric(OBJ, ginitWithDblPtr , _1, (U32)n, (double *)val);
makgeneric(OBJ, ginitWithCpxPtr , _1, (U32)n, (COMPLEX*)val);

// -------------------------
#include <cos/gen/logic.h>

makgeneric(OBJ, gbool   , _1);
makgeneric(OBJ, gnot    , _1);
makgeneric(OBJ, gand    , _1, _2);
makgeneric(OBJ, gor     , _1, _2);
makgeneric(OBJ, gxor    , _1, _2);
makgeneric(OBJ, gimplies, _1, _2);

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
makgeneric(OBJ , galloc       , _1);
makgeneric(OBJ , gallocWith   , _1, _2);
makgeneric(void, gdealloc     , _1);

// constructors, destructor
makgeneric(OBJ , ginit        , _1);
makgeneric(OBJ , ginitWith    , _1, _2);
makgeneric(OBJ , ginitWith2   , _1, _2, _3);
makgeneric(OBJ , ginitWith3   , _1, _2, _3, _4);
makgeneric(OBJ , ginitWith4   , _1, _2, _3, _4, _5);
makgeneric(OBJ , ginitWithLoc , _1, _2, (STR)file, (int)line);
makgeneric(OBJ , ginitWithStr , _1, (STR)str);
makgeneric(OBJ , gdeinit      , _1);

// ownership
makgeneric(OBJ , gretain      , _1);
makgeneric(OBJ , grelease     , _1);
makgeneric(U32 , gretainCount , _1);
makgeneric(OBJ , gautoRelease , _1);

// identity, conversion, coercion
makgeneric(OBJ , gisKindOf    , _1, _2);
makgeneric(OBJ , gisInstanceOf, _1, _2);
makgeneric(OBJ , gclass       , _1);
makgeneric(STR , gclassName   , _1);

// inheritance
makgeneric(OBJ , gsuperClass  , _1);

// comparison
makgeneric(OBJ , gequal       , _1, _2);
makgeneric(OBJ , gcompare     , _1, _2);
makgeneric(U32 , ghash        , _1);

// exception
makgeneric(void, gthrow       , _1, (STR)file, (int)line);

// contract
makgeneric(void, ginvariant   , _1, (STR)file, (int)line);

// initialization
makgeneric(void, ginitialize  , _1);
makgeneric(void, gdeinitialize, _1);

// -------------------------
#include <cos/gen/value.h>

makgeneric(STR    , gstr     , _1);
makgeneric(U32    , gsize    , _1);

makgeneric(S8     , gchar    , _1);
makgeneric(U8     , guchar   , _1);
makgeneric(S16    , gshort   , _1);
makgeneric(U16    , gushort  , _1);
makgeneric(S32    , gint     , _1);
makgeneric(U32    , guint    , _1);
makgeneric(S64    , glong    , _1);
makgeneric(U64    , gulong   , _1);
makgeneric(double , gdouble  , _1);
makgeneric(COMPLEX, gcomplex , _1);

makgeneric(void*  , gpointer , _1);
makgeneric(FUNC   , gfunction, _1);


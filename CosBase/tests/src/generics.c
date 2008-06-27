/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - generics definitions
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
 | $Id: generics.c,v 1.1 2008/06/27 16:17:18 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include "generics.h"

// --- testsuite ABCDE ---
makgeneric (void, gdoX, _, _);
makgeneric (void, gdoY, _, _);
makgeneric (void, gdoZ, _, _);

makgeneric (void, gdoC, _, (int)val);

makgeneric (void, gcatStr , _,    (STR)str);
makgeneric (void, gcat2Str, _, _, (STR)str);

makgenericv(void, gvputStr, _, (STR)fmt, ...);

// --- speed tests Counter/MilliCounter ---
makgeneric(OBJ, gincr   , _);
makgeneric(OBJ, gincrBy1, _, (U32)a);
makgeneric(OBJ, gincrBy2, _, (U32)a, (U32)b);
makgeneric(OBJ, gincrBy3, _, (U32)a, (U32)b, (U32)c);
makgeneric(OBJ, gincrBy4, _, (U32)a, (U32)b, (U32)c, (U32)d);
makgeneric(OBJ, gincrBy5, _, (U32)a, (U32)b, (U32)c, (U32)d, (U32)e);

makgeneric(OBJ, gaddTo1, _1, _2);
makgeneric(OBJ, gaddTo2, _1, _2, _3);
makgeneric(OBJ, gaddTo3, _1, _2, _3, _4);
makgeneric(OBJ, gaddTo4, _1, _2, _3, _4, _5);

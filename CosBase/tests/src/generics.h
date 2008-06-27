#ifndef COS_TESTS_GENERIC_H
#define COS_TESTS_GENERIC_H

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
 | $Id: generics.h,v 1.1 2008/06/27 16:17:18 ldeniau Exp $
 |
*/

// --- testsuite ABCDE ---
defgeneric (void, gdoX, _, _);
defgeneric (void, gdoY, _, _);
defgeneric (void, gdoZ, _, _);

defgeneric (void, gdoC, _, (int)val);

defgeneric (void, gcatStr , _,    (STR)str);
defgeneric (void, gcat2Str, _, _, (STR)str);

defgenericv(void, gvputStr, _, (STR)fmt, ...);

// --- speed tests Counter/MilliCounter ---
defgeneric(OBJ, gincr   , _);
defgeneric(OBJ, gincrBy1, _, (U32)a);
defgeneric(OBJ, gincrBy2, _, (U32)a, (U32)b);
defgeneric(OBJ, gincrBy3, _, (U32)a, (U32)b, (U32)c);
defgeneric(OBJ, gincrBy4, _, (U32)a, (U32)b, (U32)c, (U32)d);
defgeneric(OBJ, gincrBy5, _, (U32)a, (U32)b, (U32)c, (U32)d, (U32)e);

defgeneric(OBJ, gaddTo1, _1, _2);
defgeneric(OBJ, gaddTo2, _1, _2, _3);
defgeneric(OBJ, gaddTo3, _1, _2, _3, _4);
defgeneric(OBJ, gaddTo4, _1, _2, _3, _4, _5);

#endif // COS_TESTS_GENERIC_H

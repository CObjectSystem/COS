#ifndef COS_RANGE_H
#define COS_RANGE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Range
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
 | $Id: Range.h,v 1.7 2009/06/19 23:57:27 ldeniau Exp $
 |
*/

#include <cos/Value.h>

defclass(Range, Value)
  I32 start;
  I32 end;
  I32 stride;
endclass

// ----- automatic constructors

#define aRange(...)  ( (OBJ)atRange(__VA_ARGS__) )
#define atRange(...) COS_PP_CAT_NARG(atRange,__VA_ARGS__)(__VA_ARGS__)

// ----- automatic constructors shortcuts

#ifndef COS_NOSHORTCUT
#define aRng(...)  aRange(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation (private)
 */

#define atRange1(end) \
        atRange2(0,end)

#define atRange2(start,end) \
        atRange3(start,end,1)

#define atRange3(start,end,stride) \
  ( &(struct Range){ \
    {{ COS_CLS_NAME(Range).Behavior.id, COS_RC_AUTO }}, \
    start, end, stride })

#endif // COS_RANGE_H

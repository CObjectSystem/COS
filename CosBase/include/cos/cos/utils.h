#ifndef COS_COS_UTILS_H
#define COS_COS_UTILS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS utilities
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
 | $Id: utils.h,v 1.1 2008/09/29 10:42:41 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/utils.h>"
#endif 

// fast unrolled loop
#define COS_LOOP(N,...) \
  do { \
    U32 _n = (N); \
    U32 _n8 = _n / 8 + 1; \
    switch (_n % 8) \
      do {  __VA_ARGS__; \
    case 7: __VA_ARGS__; \
    case 6: __VA_ARGS__; \
    case 5: __VA_ARGS__; \
    case 4: __VA_ARGS__; \
    case 3: __VA_ARGS__; \
    case 2: __VA_ARGS__; \
    case 1: __VA_ARGS__; \
    case 0: ; \
      } while(--_n8); \
  } while (0)

#endif // COS_COS_UTILS_H

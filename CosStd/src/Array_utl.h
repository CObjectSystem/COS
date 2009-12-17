#ifndef COS_ARRAY_UTL_H
#define COS_ARRAY_UTL_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Array - utilities
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
 | $Id: Array_utl.h,v 1.2 2009/12/17 14:08:57 ldeniau Exp $
 |
*/

static inline void
swap(OBJ *val1, OBJ *val2)
{
  OBJ tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

static inline void
assign(OBJ *dst, OBJ val)
{
  OBJ tmp = *dst;
  *dst = gretain(val);
  grelease(tmp);
}

static inline OBJ*
copy(OBJ *dst, I32 dst_s, U32 *dst_n, OBJ *src, I32 src_s, U32 src_n)
{
  OBJ *end = src + src_s*src_n;

  while (src != end) {
    *dst = gretain(*src), ++*dst_n;
     dst += dst_s;
     src += src_s;
  }

  return dst;
}

#endif // COS_ARRAY_UTL_H

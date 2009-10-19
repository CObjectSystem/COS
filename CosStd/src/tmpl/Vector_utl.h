#ifndef COS_VECTOR_UTL_H
#define COS_VECTOR_UTL_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Vector - utilities
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
 | $Id: Vector_utl.h,v 1.1 2009/10/19 19:38:10 ldeniau Exp $
 |
*/

static inline void
swap(VAL *val1, VAL *val2)
{
  VAL tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

static inline VAL*
copy(VAL *dst, U32 *dst_n, VAL *src, I32 src_s, U32 src_n)
{
  VAL *end = dst + src_n;

  while (dst != end)
    *dst++ = *src, ++*dst_n, src += src_s;

  return dst;
}

#endif // COS_VECTOR_UTL_H

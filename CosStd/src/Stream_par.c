/*
 o---------------------------------------------------------------------o
 |
 | COS Number parser
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
 | $Id: Stream_par.c,v 1.1 2010/05/26 15:02:00 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/Stream.h>
#include <cos/gen/stream.h>

#include <ctype.h>
#include <float.h>
#include <errno.h>
#include <math.h>

U32 // integer: [+-]?[0-9]+
Stream_parseI16(OBJ strm, I32 *val, BOOL skipSpc)
{
  test_assert( val, "invalid argument" );

  U32 cnt = 0;                // char counter
  I32 chr;                    // character
  I32 sgn = 0;                // sign char
  I16 cur = 0, prv = -1;      // value

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(strm));

  // skip white spaces (nothing else)
  if (skipSpc)
    while (get(sel, strm, 0, &chr), chr == ' ') ;

  // sign (optional)
  if (chr == '-' || chr == '+') {
    sgn = chr, cnt++;
    get(sel, strm, 0, &cnt);
  }

  // significant digits
  while (cur > prv && isdigit(chr)) {
    prv = cur, cur = cur * 10 + ((U32)chr - '0'), cnt++;
    get(sel, strm, 0, &chr);
  }

  // extra digits (discarded)
  while (isdigit(chr))
    get(sel, strm, 0, &chr), cnt++;

  // restore lookahead
  if (chr != EndOfStream)
    gungetChr(strm, chr);
  if (cnt == 1 && sgn)
    gungetChr(strm, sgn), cnt--; // may fail

  // store result
  if (cur > prv)
    *val = sgn == '-' ? -cur : cur;
  else {
    // overflow
    errno = ERANGE;
    *val = sgn == '-' ? I16_MIN : I16_MAX;
  }

  return cnt;
}

U32 // integer: [+-]?[0-9]+
Stream_parseI32(OBJ strm, I32 *val, BOOL skipSpc)
{
  test_assert( val, "invalid argument" );

  U32 cnt = 0;                // char counter
  I32 chr;                    // character
  I32 sgn = 0;                // sign char
  I32 cur = 0, prv = -1;      // value

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(strm));

  // skip white spaces (nothing else)
  if (skipSpc)
    while (get(sel, strm, 0, &chr), chr == ' ') ;

  // sign (optional)
  if (chr == '-' || chr == '+') {
    sgn = chr, cnt++;
    get(sel, strm, 0, &cnt);
  }

  // significant digits
  while (cur > prv && isdigit(chr)) {
    prv = cur, cur = cur * 10 + ((U32)chr - '0'), cnt++;
    get(sel, strm, 0, &chr);
  }
  
  // extra digits (discarded)
  while (isdigit(chr))
    get(sel, strm, 0, &chr), cnt++;

  // restore lookahead
  if (chr != EndOfStream)
    gungetChr(strm, chr);
  if (cnt == 1 && sgn)
    gungetChr(strm, sgn), cnt--; // may fail

  // store result
  if (cur > prv)
    *val = sgn == '-' ? -cur : cur;
  else {
    // overflow
    errno = ERANGE;
    *val = sgn == '-' ? I32_MIN : I32_MAX;
  }

  return cnt;
}

U32 // integer: [+-]?[0-9]+
Stream_parseI64(OBJ strm, I64 *val, BOOL skipSpc)
{
  test_assert( val, "invalid argument" );

  U32 cnt = 0;                // char counter
  I32 chr;                    // character
  I32 sgn = 0;                // sign char
  I64 cur = 0, prv = -1;      // value

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(strm));

  // skip white spaces (nothing else)
  if (skipSpc)
    while (get(sel, strm, 0, &chr), chr == ' ') ;

  // sign (optional)
  if (chr == '-' || chr == '+') {
    sgn = chr, cnt++;
    get(sel, strm, 0, &cnt);
  }

  // significant digits
  while (cur > prv && isdigit(chr)) {
    prv = cur, cur = cur * 10 + ((U32)chr - '0'), cnt++;
    get(sel, strm, 0, &chr);
  }
  
  // extra digits (discarded)
  while (isdigit(chr))
    get(sel, strm, 0, &chr), cnt++;

  // restore lookahead
  if (chr != EndOfStream)
    gungetChr(strm, chr);
  if (cnt == 1 && sgn)
    gungetChr(strm, sgn), cnt--; // may fail

  // store result
  if (cur > prv)
    *val = sgn == '-' ? -cur : cur;
  else {
    // overflow
    errno = ERANGE;
    *val = sgn == '-' ? I64_MIN : I64_MAX;
  }

  return cnt;
}

U32 // floating: [+-]?[0-9]+(.[0-9]+)?([eE][+-]?[0-9]+)?
Stream_parseF64(OBJ strm, F64 *val, BOOL skipSpc)
{
  test_assert( val, "invalid argument" );

  U32 cnt = 0;                // char counter
  I32 chr;                    // character
  I32 sgn = 0;                // sign char
  F64 cur = 0;                // value

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(strm));

  // skip white spaces (nothing else)
  if (skipSpc)
    while (get(sel, strm, 0, &chr), chr == ' ') ;

  // sign (optional)
  if (chr == '-' || chr == '+') {
    sgn = chr, cnt++;
    get(sel, strm, 0, &cnt);
  }

  // significant digits
  while (isfinite(cur) && isdigit(chr)) {
    cur = cur * 10 + ((U32)chr - '0'), cnt++;
    get(sel, strm, 0, &chr);
  }
  
  // extra digits (discarded)
  while (isdigit(chr))
    get(sel, strm, 0, &chr), cnt++;

  // decimal part
  if (chr == '.' || chr == ',') {
    F64 fra = 0;
    I32 exp = 0;
  
    // significant digits
    while (exp >= -DECIMAL_DIG && isdigit(chr)) {
      fra = fra * 10 + ((U32)chr - '0'), cnt++, exp--;
      get(sel, strm, 0, &chr);
    }
    
    // extra digits (discarded)
    while (isdigit(chr))
      get(sel, strm, 0, &chr), cnt++;
      
    cur += fra * float_ipow(10, exp);
  }

  // exponent
  if (chr == 'E' || chr == 'e') {
    I32 exp = 0;
    U32 n = Stream_parseI16(strm, &exp, NO);

    if (n) {    
      cnt += n;
      if (exp) cur *= float_ipow(10, exp);
    }
  }

  // restore lookahead
  if (chr != EndOfStream)
    gungetChr(strm, chr);
  if (cnt == 1 && sgn)
    gungetChr(strm, sgn), cnt--; // may fail

  // store result
  *val = sgn == '-' ? -cur : cur;

  return cnt;
}


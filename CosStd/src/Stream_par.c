/**
 * C Object System
 * COS Stream number parser
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
  ensure( val, "invalid argument" );

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
  ensure( val, "invalid argument" );

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
  ensure( val, "invalid argument" );

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
  ensure( val, "invalid argument" );

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


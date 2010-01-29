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
 | $Id: Number_par.c,v 1.2 2010/01/29 13:38:40 ldeniau Exp $
 |
*/

#include <cos/Number.h>
#include <cos/gen/stream.h>

#include <ctype.h>
#include <errno.h>

U32 // integer: [+-]?[0-9]+
Number_parseI16(OBJ _1, I32 *val)
{
  test_assert( val, "invalid argument" );

  char  b[7];                   // buffer
  char* p = b;                  // cursor
  char* e = b + sizeof b - 1;   // marker
  U32   i = 0;                  // counter
  I32   c;                      // character

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));

  // skip white spaces (nothing else)
  while (get(sel, _1, 0, &c), c == ' ') ;

  // sign (optional)
  if (c == '-' || c == '+') {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }

  // significant digits
  while (isdigit(c) && p != e) {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }
  
  // extra digits (discarded)
  while (isdigit(c))
    get(sel, _1, 0, &c), i++;

  // convert
  *p = 0;
  long num = strtol(b, &e, 10);
  
  // overflow
  if (num < I16_MIN) {
    *val = I16_MIN;
    errno = ERANGE;
  } else
  if (num > I16_MAX) {
    *val = I16_MAX;    
    errno = ERANGE;
  } else
    *val = num;

  // restore lookahead
  if (p != e) {
    *p++ = (U32)c;
    gungetData(_1, (U8*)e, p-e);
  } else
    gungetChr(_1, c);

  // return number char read
  return i + (e-b);
}

U32 // integer: [+-]?[0-9]+
Number_parseI32(OBJ _1, I32 *val)
{
  test_assert( val, "invalid argument" );

  char  b[12];                  // buffer
  char* p = b;                  // cursor
  char* e = b + sizeof b - 1;   // marker
  U32   i = 0;                  // counter
  I32   c;                      // character

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));

  // skip white spaces (nothing else)
  while (get(sel, _1, 0, &c), c == ' ') ;

  // sign (optional)
  if (c == '-' || c == '+') {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }

  // significant digits
  while (isdigit(c) && p != e) {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }
  
  // extra digits (discarded)
  while (isdigit(c))
    get(sel, _1, 0, &c), i++;

  // convert
  *p = 0;
  long num = strtol(b, &e, 10);
  
  // overflow
  if (sizeof(I32) < sizeof(long)) {
    if (num < I32_MIN) {
      *val = I32_MIN;
      errno = ERANGE;
    } else
    if (num > I32_MAX) {
      *val = I32_MAX;    
      errno = ERANGE;
    } else
      *val = num;
  } else
    *val = num;

  // restore lookahead
  if (p != e) {
    *p++ = (U32)c;
    gungetData(_1, (U8*)e, p-e);
  } else
    gungetChr(_1, c);

  // return number char read
  return i + (e-b);
}

U32 // integer: [+-]?[0-9]+
Number_parseI64(OBJ _1, I64 *val)
{
  test_assert( val, "invalid argument" );

  char  b[22];                  // buffer
  char* p = b;                  // cursor
  char* e = b + sizeof b - 1;   // marker
  U32   i = 0;                  // counter
  I32   c;                      // character

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));

  // skip white spaces (nothing else)
  while (get(sel, _1, 0, &c), c == ' ') ;

  // sign (optional)
  if (c == '-' || c == '+') {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }

  // digits
  while (isdigit(c) && p != e) {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }
  
  // extra digits (discarded)
  while (isdigit(c))
    get(sel, _1, 0, &c), i++;

  // convert
  *p = 0;
  *val = strtoll(b, &e, 10);

  // restore lookahead
  if (p != e) {
    *p++ = (U32)c;
    gungetData(_1, (U8*)e, p-e);
  } else
    gungetChr(_1, c);

  // return number char read
  return i + (e-b);
}

U32 // floating: [+-]?[0-9]+(.[0-9]+)?([eE][+-]?[0-9]+)?
Number_parseF64(OBJ _1, F64 *val)
{
  test_assert( val, "invalid argument" );

  char  b[512];                 // buffer
  char* p = b;                  // cursor
  char* e = b + sizeof b - 12;  // marker
  U32   i = 0;                  // counter
  I32   c;                      // character

  SEL  sel = genericref(ggetChr);
  IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));

  // skip white spaces (nothing else)
  while (get(sel, _1, 0, &c), c == ' ') ;

  // sign
  if (c == '-' || c == '+') {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }

  // digits
  while (isdigit(c) && p != e) {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);
  }
  
  // decimal point
  if ((c == '.' || c == ',') && p != e) {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);

    // digits
    while (isdigit(c) && p != e) {
      *p++ = (U32)c;
      get(sel, _1, 0, &c);
    }
  }

  // extra digits (discarded)
  if (p == e) {
    while (isdigit(c))
      get(sel, _1, 0, &c), i++;
  }

  // restore the reserve
  e = b + sizeof b - 1;

  // exponent
  if ((c == 'e' || c == 'E') && p != e) {
    *p++ = (U32)c;
    get(sel, _1, 0, &c);

    // sign
    if ((c == '-' || c == '+') && p != e) {
      *p++ = (U32)c;
      get(sel, _1, 0, &c);
    }
    
    // digits
    while (isdigit(c) && p != e) {
      *p++ = (U32)c;
      get(sel, _1, 0, &c);
    }

    // extra digits (discarded)
    if (p == e) {
      while (isdigit(c))
        get(sel, _1, 0, &c), i++;
    }
  }
 
  // convert
  *p = 0;
  *val = strtod(b, &e);

  // restore lookahead
  if (p != e) {
    *p++ = (U32)c;
    gungetData(_1, (U8*)e, p-e);
  } else
    gungetChr(_1, c);

  // return number char read
  return i + (e-b);
}


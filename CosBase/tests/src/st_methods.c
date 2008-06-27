/*
 o---------------------------------------------------------------------o
 |
 | COS speed tests - methods
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
 | $Id: st_methods.c,v 1.1 2008/06/27 16:17:18 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include "utest.h"
#include "tests.h"
#include "generics.h"

enum { N = 20000000 };

void
st_methods(void)
{
  useclass(Counter);

  OBJ cnt = gnew(Counter);

  STEST( "method (0 argument )", N, N, gincr(cnt) );
  STEST( "method (1 argument )", N, N, gincrBy1(cnt,1) );
  STEST( "method (2 arguments)", N, N, gincrBy2(cnt,1,1) );
  STEST( "method (3 arguments)", N, N, gincrBy3(cnt,1,1,1) );
  STEST( "method (4 arguments)", N, N, gincrBy4(cnt,1,1,1,1) );
  STEST( "method (5 arguments)", N, N, gincrBy5(cnt,1,1,1,1,1) );
  
  TestAssert( gint(cnt) == N+N+2*N+3*N+4*N+5*N );

  grelease(cnt);
}

void
st_nextmethods(void)
{
  useclass(MilliCounter);

  OBJ cnt = gnew(MilliCounter);

  STEST( "next method (0 argument )", N, N, gincr(cnt) );
  STEST( "next method (1 argument )", N, N, gincrBy1(cnt,1) );
  STEST( "next method (2 arguments)", N, N, gincrBy2(cnt,1,1) );
  STEST( "next method (3 arguments)", N, N, gincrBy3(cnt,1,1,1) );
  STEST( "next method (4 arguments)", N, N, gincrBy4(cnt,1,1,1,1) );
  STEST( "next method (5 arguments)", N, N, gincrBy5(cnt,1,1,1,1,1) );
  
  TestAssert( gint(cnt) == N+N+2*N+3*N+4*N+5*N );
  grelease(cnt);
}

void
st_multimethods(void)
{
  useclass(Counter);

  OBJ cnt = gnew(Counter);
  OBJ one = gincr(gnew(Counter));

  STEST( "multimethod (rank 2)", N, N, gaddTo1(cnt,one) );
  STEST( "multimethod (rank 3)", N, N, gaddTo2(cnt,one,one) );
  STEST( "multimethod (rank 4)", N, N, gaddTo3(cnt,one,one,one) );
  STEST( "multimethod (rank 5)", N, N, gaddTo4(cnt,one,one,one,one) );
  
  TestAssert( gint(cnt) == N+2*N+3*N+4*N );
  grelease(cnt);
  grelease(one);
}

void
st_memory(void)
{
  enum { P = N/2 };
  static OBJ arr[P];
  useclass(Counter, AutoRelease);
  OBJ ar = gnew(AutoRelease);
  size_t i;
  
  i = 0;
  STEST( "new (galloc+ginit)", P, P, arr[i++] = gnew(Counter) );

  i = 0;
  STEST( "retain", P, P, gretain(arr[i++]) );

  i = 0;
  STEST( "release", P, P, grelease(arr[i++]) );

  i = 0;
  cos_logmsg_setLevel(cos_msg_warn);
  STEST( "autoRelease", P, P, gautoRelease(arr[i++]) );
  cos_logmsg_setLevel(cos_msg_trace);

  STEST( "release (gdeinit+dealloc)", P, 1, grelease(ar) );
}

void
st_exception(void)
{
  STEST( "try-endtry", N/10, N/10, TRY ENDTRY );
}

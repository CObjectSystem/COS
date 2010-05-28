/*
 o---------------------------------------------------------------------o
 |
 | COS speed tests - methods through proxy
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
 | $Id: st_proxy.c,v 1.8 2010/05/28 12:25:10 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Proxy.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>
#include <cos/gen/value.h>
#include <cos/utest.h>

#include "tests.h"
#include "generics.h"

enum { N = 5000000 * sizeof(void*) };

void
st_pxymethods(void)
{
  useclass(Counter, Proxy);

  OBJ cnt = gnew(Counter);
  OBJ pxy = gnewWith(Proxy,cnt);

  grelease(cnt);

  STEST( "method through proxy (0 argument )", N, gincr(pxy) );
  STEST( "method through proxy (1 argument )", N, gincrBy1(pxy,1) );
  STEST( "method through proxy (2 arguments)", N, gincrBy2(pxy,1,1) );
  STEST( "method through proxy (3 arguments)", N, gincrBy3(pxy,1,1,1) );
  STEST( "method through proxy (4 arguments)", N, gincrBy4(pxy,1,1,1,1) );
  STEST( "method through proxy (5 arguments)", N, gincrBy5(pxy,1,1,1,1,1) );

  test_assert( gint(pxy) == N + N+2*N+3*N+4*N+5*N );
  
  grelease(pxy);
}


defclass(ProxyCounter,Proxy) endclass
makclass(ProxyCounter,Proxy);

defmethod(void, gunrecognizedMessage1, ProxyCounter)
  next_method(self);
endmethod

void
st_pxynextmethods(void)
{
  useclass(Counter, ProxyCounter);

  OBJ cnt = gnew(Counter);
  OBJ pxy = gnewWith(ProxyCounter,cnt);

  grelease(cnt);

  STEST( "method + next method through proxy (0 argument )", N, gincr(pxy) );
  STEST( "method + next method through proxy (1 argument )", N, gincrBy1(pxy,1) );
  STEST( "method + next method through proxy (2 arguments)", N, gincrBy2(pxy,1,1) );
  STEST( "method + next method through proxy (3 arguments)", N, gincrBy3(pxy,1,1,1) );
  STEST( "method + next method through proxy (4 arguments)", N, gincrBy4(pxy,1,1,1,1) );
  STEST( "method + next method through proxy (5 arguments)", N, gincrBy5(pxy,1,1,1,1,1) );

  test_assert( gint(pxy) == N + N+2*N+3*N+4*N+5*N );
  
  grelease(pxy);
}

void
st_pxymultimethods(void)
{
  useclass(Counter, Proxy);

  OBJ cnt = gnew(Counter);
  OBJ pxy = gnewWith(Proxy,cnt);
  OBJ one = gincr(gnew(Counter));

  grelease(cnt);

  STEST( "multimethod through proxy (rank 2)", N, gaddTo1(pxy,one) );
  STEST( "multimethod through proxy (rank 3)", N, gaddTo2(pxy,one,one) );
  STEST( "multimethod through proxy (rank 4)", N, gaddTo3(pxy,one,one,one) );
  STEST( "multimethod through proxy (rank 5)", N, gaddTo4(pxy,one,one,one,one) );
  
  test_assert( gint(pxy) == N+2*N+3*N+4*N );
  grelease(pxy);
  grelease(one);
}

/**
 * C Object System
 * COS speed tests - methods through proxy
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

  ensure( gint(pxy) == N + N+2*N+3*N+4*N+5*N );
  
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

  ensure( gint(pxy) == N + N+2*N+3*N+4*N+5*N );
  
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
  
  ensure( gint(pxy) == N+2*N+3*N+4*N );
  grelease(pxy);
  grelease(one);
}

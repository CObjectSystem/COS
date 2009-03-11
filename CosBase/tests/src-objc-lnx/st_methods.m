/*
 o---------------------------------------------------------------------o
 |
 | COS speed tests - Objective-C methods
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
 | $Id: st_methods.m,v 1.2 2009/03/11 12:35:06 ldeniau Exp $
 |
*/

#include <stdlib.h>
#include <assert.h>
#include "utest.h"
#include "tests.h"
#include "Counter.h"

enum { N = 15000000 * sizeof(void*) };

void
st_methods()
{
  id cnt = [Counter new];

  STEST( "method (0 argument )", N, [cnt incr] );
  STEST( "method (1 argument )", N, [cnt incrBy: 1] );
  STEST( "method (2 arguments)", N, [cnt incrBy: 1 :1] );
  STEST( "method (3 arguments)", N, [cnt incrBy: 1 :1 :1] );
  STEST( "method (4 arguments)", N, [cnt incrBy: 1 :1 :1 :1] );
  STEST( "method (5 arguments)", N, [cnt incrBy: 1 :1 :1 :1 :1] );
  
  assert( (U32)[cnt value] == (U32)(N+N+2*N+3*N+4*N+5*N) );

  [cnt free];
}

void
st_multimethods()
{
  id cnt = [Counter new];
  id one = [[Counter new] incr];

  STEST( "method & visitor pattern (rank 2)", N, [cnt addTo1: one] );
  STEST( "method & visitor pattern (rank 3)", N, [cnt addTo2: one :one] );
  STEST( "method & visitor pattern (rank 4)", N, [cnt addTo3: one :one :one] );
  STEST( "method & visitor pattern (rank 5)", N, [cnt addTo4: one :one :one :one] );

  assert( (U32)[cnt value] == (U32)(N+2*N+3*N+4*N) );

  [cnt free];
  [one free];
}

void
st_memory(void)
{
  enum { P = N/2/sizeof(void*) };
  static id arr[P];
  U32 i;

  i = 0;
  STEST( "alloc+init", P, arr[i++] = [[Counter alloc] init] );

  i = 0;
  STEST( "dealloc", P, [arr[i++] free] );
}

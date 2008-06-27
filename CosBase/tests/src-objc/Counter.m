/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - C++ Counter class definition
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
 | $Id: Counter.m,v 1.1 2008/06/27 16:17:25 ldeniau Exp $
 |
*/

#include "Counter.h"

@implementation Counter

- (Counter*) init {
  self = [super init];
  if (self)
    _val = 0;
  return self;
}

- (U32) value {
  return _val;
}
  
// IncrBy interface

- (id<Incr>) incr {
  _val += 1;
  return self;
}

- (id<Incr>) incrBy: (U32)a {
  _val += a;
  return self;
}

- (id<Incr>) incrBy: (U32)a :(U32)b {
  _val += a + b;
  return self;
}

- (id<Incr>) incrBy: (U32)a :(U32)b :(U32)c {
  _val += a + b + c;
  return self;
}

- (id<Incr>) incrBy: (U32)a :(U32)b :(U32)c :(U32)d {
  _val += a + b + c + d;
  return self;
}

- (id<Incr>) incrBy: (U32)a :(U32)b :(U32)c :(U32)d :(U32)e {
  _val += a + b + c + d + e;
  return self;
}

// AddTo1 interface

- (id<AddTo1>) addTo1: (const id<AddTo1>)a {
  [a addTo11: self];
  return self;
}

- (const id<AddTo1>) addTo11: (Counter*)cnt {
  [cnt incrBy: _val];
  return cnt;
}

// AddTo2 interface

- (id<AddTo2>) addTo2: (const id<AddTo2>)a :(const id<AddTo2>)b {
  [a addTo21: self :b];
  return self;
}

- (const id<AddTo2>) addTo21: (Counter*)cnt :(const id<AddTo2>)b {
  [b addTo22: cnt :self];
  return cnt;
}

- (const id<AddTo2>) addTo22: (Counter*)cnt :(const Counter*)a {
  [cnt incrBy: [a value] :_val];
  return cnt;
}

// AddTo3 interface

- (id<AddTo3>) addTo3: (const id<AddTo3>)a :(const id<AddTo3>)b :(const id<AddTo3>)c {
  [a addTo31: self :b :c];
  return self;
}

- (const id<AddTo3>) addTo31: (Counter*)cnt :(const id<AddTo3>)b :(const id<AddTo3>)c {
  [b addTo32: cnt :self :c];
  return cnt;
}

- (const id<AddTo3>) addTo32: (Counter*)cnt :(const Counter*)a :(const id<AddTo3>)c {
  [c addTo33: cnt :a :self];
  return cnt;
}

- (const id<AddTo3>) addTo33: (Counter*)cnt :(const Counter*)a :(const Counter*)b {
  [cnt incrBy: [a value] :[b value] :_val];
  return cnt;
}

// AddTo4 interface

- (id<AddTo4>) addTo4: (const id<AddTo4>)a :(const id<AddTo4>)b :(const id<AddTo4>)c :(const id<AddTo4>)d {
  [a addTo41: self :b :c :d];
  return self;
}
 
- (const id<AddTo4>) addTo41: (Counter*)cnt :(const id<AddTo4>)b :(const id<AddTo4>)c :(const id<AddTo4>)d {
  [b addTo42: cnt :self :c :d];
  return cnt;
}

- (const id<AddTo4>) addTo42: (Counter*)cnt :(const Counter*)a :(const id<AddTo4>)c :(const id<AddTo4>)d {
  [c addTo43: cnt :a :self :d];
  return cnt;
}

- (const id<AddTo4>) addTo43: (Counter*)cnt :(const Counter*)a :(const Counter*)b :(const id<AddTo4>)d {
  [d addTo44: cnt :a :b :self];
  return cnt;
}

- (const id<AddTo4>) addTo44: (Counter*)cnt :(const Counter*)a :(const Counter*)b :(const Counter*)c {
  [cnt incrBy: [a value] :[b value] :[c value] :_val];
  return cnt;
}

@end

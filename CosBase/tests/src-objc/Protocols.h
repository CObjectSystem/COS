#ifndef COS_TESTS_PROTOCOLS_H
#define COS_TESTS_PROTOCOLS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - Objective-C protocols for Counter
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
 | $Id: Protocols.h,v 1.1 2008/06/27 16:17:25 ldeniau Exp $
 |
*/

typedef unsigned U32;

@class Counter;

@protocol Incr
  - (id<Incr>) incr;
  - (id<Incr>) incrBy: (U32)a;
  - (id<Incr>) incrBy: (U32)a :(U32)b;
  - (id<Incr>) incrBy: (U32)a :(U32)b :(U32)c;
  - (id<Incr>) incrBy: (U32)a :(U32)b :(U32)c :(U32)d;
  - (id<Incr>) incrBy: (U32)a :(U32)b :(U32)c :(U32)d :(U32)e;
@end

@protocol AddTo1
  - (      id<AddTo1>) addTo1:  (const id<AddTo1>)a;
  - (const id<AddTo1>) addTo11: (Counter*)cnt;
@end

@protocol AddTo2
  - (      id<AddTo2>) addTo2:  (const id<AddTo2>)a :(const id<AddTo2>)b;
  - (const id<AddTo2>) addTo21: (Counter*)cnt       :(const id<AddTo2>)b;
  - (const id<AddTo2>) addTo22: (Counter*)cnt       :(const Counter*)a;
@end

@protocol AddTo3
  - (      id<AddTo3>) addTo3:  (const id<AddTo3>)a :(const id<AddTo3>)b :(const id<AddTo3>)c;
  - (const id<AddTo3>) addTo31: (Counter*)cnt       :(const id<AddTo3>)b :(const id<AddTo3>)c;
  - (const id<AddTo3>) addTo32: (Counter*)cnt       :(const Counter*)a   :(const id<AddTo3>)c;
  - (const id<AddTo3>) addTo33: (Counter*)cnt       :(const Counter*)a   :(const Counter*)b;
@end

@protocol AddTo4
  - (      id<AddTo4>) addTo4:  (const id<AddTo4>)a :(const id<AddTo4>)b :(const id<AddTo4>)c :(const id<AddTo4>)d;
  - (const id<AddTo4>) addTo41: (Counter*)cnt       :(const id<AddTo4>)b :(const id<AddTo4>)c :(const id<AddTo4>)d;
  - (const id<AddTo4>) addTo42: (Counter*)cnt       :(const Counter*)a   :(const id<AddTo4>)c :(const id<AddTo4>)d;
  - (const id<AddTo4>) addTo43: (Counter*)cnt       :(const Counter*)a   :(const Counter*)b   :(const id<AddTo4>)d;
  - (const id<AddTo4>) addTo44: (Counter*)cnt       :(const Counter*)a   :(const Counter*)b   :(const Counter*)c;
@end

#endif // COS_TESTS_PROTOCOLS_H

#ifndef COS_TESTS_PROTOCOLS_H
#define COS_TESTS_PROTOCOLS_H

/**
 * C Object System
 * COS testsuites - Objective-C protocols for Counter
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

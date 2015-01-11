#ifndef COS_TESTS_GENERIC_H
#define COS_TESTS_GENERIC_H

/**
 * C Object System
 * COS testsuites - generics definitions
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

// --- testsuite ABCDE ---
defgeneric (void, gdoX, _, _);
defgeneric (void, gdoY, _, _);
defgeneric (void, gdoZ, _, _);

defgeneric (void, gdoC, _, (int)val);

defgeneric (void, gcatStr , _,    (STR)str);
defgeneric (void, gcat2Str, _, _, (STR)str);

defgenericv(void, gvputStr, _, (STR)fmt, ...);

// --- speed tests Counter/MilliCounter ---
defgeneric(OBJ, gincr   , _);
defgeneric(OBJ, gincrBy1, _, (U32)a);
defgeneric(OBJ, gincrBy2, _, (U32)a, (U32)b);
defgeneric(OBJ, gincrBy3, _, (U32)a, (U32)b, (U32)c);
defgeneric(OBJ, gincrBy4, _, (U32)a, (U32)b, (U32)c, (U32)d);
defgeneric(OBJ, gincrBy5, _, (U32)a, (U32)b, (U32)c, (U32)d, (U32)e);

defgeneric(OBJ, gaddTo1, _1, _2);
defgeneric(OBJ, gaddTo2, _1, _2, _3);
defgeneric(OBJ, gaddTo3, _1, _2, _3, _4);
defgeneric(OBJ, gaddTo4, _1, _2, _3, _4, _5);

defgeneric(OBJ, gaddToPlus, _1, _2, (U32)a);

#endif // COS_TESTS_GENERIC_H

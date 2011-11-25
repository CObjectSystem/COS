#ifndef COS_TESTS_TESTS_H
#define COS_TESTS_TESTS_H

/**
 * C Object System
 * COS testsuites - tests suite
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

void ut_slice(void);
void ut_range(void);
void ut_xrange(void);
void ut_string(void);
void ut_array_basics(void);
void ut_array_functor(void);

defgeneric(OBJ, gprint, _1);

#endif // COS_TESTS_TESTS_H

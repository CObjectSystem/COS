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

void ut_methods(void);
void ut_classes(void);
void ut_properties(void);
//void ut_predlogic(void);
void ut_nextmethod(void);
void ut_unrecognized(void);
void ut_forwardmessage(void);
void ut_variadics(void);
void ut_proxy(void);
void ut_exception(void);
void ut_contract(void);
void ut_autorelease(void);
//void ut_autoconst(void);
//void ut_autovector(void);

void st_methods(void);
void st_methods_ptr(void);
void st_nextmethods(void);
void st_multimethods(void);
void st_multimethods_ptr(void);

void st_pxymethods(void);
void st_pxynextmethods(void);
void st_pxymultimethods(void);

void st_memory(void);
void st_exception(void);

#endif // COS_TESTS_TESTS_H

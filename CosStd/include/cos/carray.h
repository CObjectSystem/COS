// multiple inclusion allowed

/**
 * C Object System
 * COS C Array, C array utils
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

#ifndef COS_CARRAY_H
#define COS_CARRAY_H

#include <cos/Object.h>

#include <stdlib.h>

/* NOTE-INFO: low level C array
   the array is allocated on the stack if its size <= CARRAY_LIMIT
   otherwise it is allocated on the heap.

   {
     CARRAY_CREATE(OBJ, buf, 1000);

     buf[100] = gnew(Object);
     grelease(buf[100]);

     CARRAY_DESTROY(buf);
   }
*/

#define CARRAY_CREATE(T,name,nelem) \
        CARRAY_CREATE_(T,name,nelem, \
    /* local pointer */  COS_PP_CAT(_cos_tmp_carray_p_,name), \
    /* local array   */  COS_PP_CAT(_cos_tmp_carray_a_,name), \
    /* local size    */  COS_PP_CAT(_cos_tmp_carray_s_,name))

#define CARRAY_CREATE_(T,name,N,P,A,S) \
  U32 S = N; T *P, \
    A[S*sizeof(T) <= CARRAY_LIMIT ? S : 0]; \
  if (S*sizeof(T) <= CARRAY_LIMIT) P = A; \
  else { \
    useclass(ExBadAlloc); \
    if ( !(P = malloc(S * sizeof(T))) ) THROW(ExBadAlloc); \
  } \
  T *const name = P

#define CARRAY_DESTROY(name) \
  if (name != COS_PP_CAT(_cos_tmp_carray_a_,name)) \
    free(name)

#endif // COS_CARRAY_H

// can be redefined between inclusion
#ifndef CARRAY_LIMIT
#define CARRAY_LIMIT (1024 * sizeof(void*))
#endif

// multiple inclusion allowed


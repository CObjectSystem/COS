#ifndef COS_COS_COSMEM_H
#define COS_COS_COSMEM_H

/**
 * C Object System
 * COS memory allocator
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

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosmem.h>"
#endif

/* NOTE-TODO: to clean for better use of COS framework...
*/

/* NOTE-USER: memory allocator front-end

  Purpose:
    provide fast memory allocator per-thread.
    allocated memory can be used-by/moved-to any thread (global allocator).

  Information:
  - parameters ending with an underscope can be null.
  - cos_free does not free the memory, it just returns it to the pool.
  - cos_mem_collect does free the unused memory of the thread specific pool.

  Errors:
  - cos_free on objects not allocated by cos_malloc is undefined.

  Compilation:
  - set COS_MEM_STD to 1 to use the standard C allocator instead.

 */

#include <stdio.h>

// --- interface ---------------------------------------------------------------

// local buffer (macros)
#define cos_alloc_tmp(type,name,nslot)
#define cos_free_tmp(      name)

// allocator
void*   cos_malloc  (size_t size);
void*   cos_calloc  (size_t count, size_t size);
void*   cos_realloc (void  *ptr_ , size_t size_);
void    cos_free    (void  *ptr_);

// utils
size_t  cos_mem_collect (void);
size_t  cos_mem_cached  (void);
void    cos_mem_mdump   (FILE*);

// --- configuration -----------------------------------------------------------

// set COS_MEM_STD to 1 to use the standard C allocator instead.
#ifndef COS_MEM_STD
#define COS_MEM_STD 0
#endif

// --- inline implementation ---------------------------------------------------

#undef  cos_alloc_tmp
#define cos_alloc_tmp(T,NAME,N) \
  T NAME##_local_tmp__[sizeof(T)*(N) < 8192 ? (N) : 1]; \
  T *NAME = (sizeof(T)*(N) < 8192 ? \
             NAME##_local_tmp__ : cos_malloc(sizeof(T)*(N)) )

#undef  cos_free_tmp
#define cos_free_tmp(NAME) \
  (NAME != NAME##_local_tmp__ ? cos_free(NAME) : (void)0)

// --- global redefinition -----------------------------------------------------

#if COS_MEM_STD

#define cos_malloc( sz       ) malloc (sz)
#define cos_calloc( cnt , sz ) calloc (cnt , sz )
#define cos_realloc(ptr_, sz_) realloc(ptr_, sz_)
#define cos_free(   ptr_     ) free   (ptr_)

#define cos_mem_collect() 0
#define cos_mem_cached()  0
#define cos_mem_mdump(f)

#else

void* cos_malloc (size_t)        __attribute__((hot,malloc(cos_free,1),malloc,returns_nonnull));
void* cos_calloc (size_t,size_t) __attribute__((hot,malloc(cos_free,1),malloc,returns_nonnull));
void* cos_realloc(void* ,size_t) __attribute__((hot,malloc(cos_free,1)));
void  cos_free   (void* )        __attribute__((hot));

#endif

// -----------------------------------------------------------------------------
#endif // COS_COS_COSMEM_H

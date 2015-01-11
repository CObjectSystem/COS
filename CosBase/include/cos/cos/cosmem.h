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
  - cos_mem_free does not free the memory, it just returns it to the pool.
  - cos_mem_xxx_n are ~50% faster, but objects must have the SAME cos_mem_size.
  - cos_mem_alloc_n returns the number of objects effectively allocated.
  - cos_mem_collect does free the unused memory of the thread specific pool.
  - cos_mem_collect and cos_mem_unused can be called for a specific cos_mem_size.

  Errors:
  - cos_mem_free_n on objects of different cos_mem_size is undefined.
  - cos_mem_free[_n] on objects not allocated by cos_mem_alloc[_n] is undefined.

  Compilation:
  - set cos_mem_AS_DEFAULT to 1 to activate it for the standard allocator.

 */

// --- interface --------------------------------------------------------------

// allocator
static void*  cos_mem_alloc    (size_t size);
static void*  cos_mem_calloc   (size_t count, size_t size);
static void*  cos_mem_realloc  (void  *ptr_, size_t new_size);
static void   cos_mem_free     (void  *ptr_);
static size_t cos_mem_size     (void  *ptr_);

// allocator, array versions
static int    cos_mem_alloc_n  (void *ptr_[], int n, size_t size);
static void   cos_mem_free_n   (void *ptr_[], int n);

// tuning
extern size_t cos_mem_unused   (int *count_,   size_t *only_);
extern size_t cos_mem_collect  (int *percent_, size_t *only_);

// --- configuration -----------------------------------------------------------

// set COS_MEM_AS_DEFAULT to 1 to activate this front-end for the standard allocator.
#ifndef COS_MEM_AS_DEFAULT
#define COS_MEM_AS_DEFAULT 1
#endif

// --- inline implementation ---------------------------------------------------

#include <string.h>
#include <assert.h>

// memory node
union cos_mem_node_ {
  struct {
    union cos_mem_node_ *next;
  } free;

  struct {
    unsigned slot;
    union {
      long   n, *np;
      size_t s, *sp;
      double d, *dp;
      void     (*fp)(void);
    } data[1];
  } used;
};

struct cos_mem_slot_ {
  union cos_mem_node_ *list;
};

// pool size
enum {
  cos_mem_node_size_ = offsetof(union cos_mem_node_, used.data),
  cos_mem_slot_size_ = sizeof(struct cos_mem_slot_),
  cos_mem_slot_max_  = (1<<16)/cos_mem_slot_size_, // max pool size:     ~64kB/thread                  
};

// memory pool
struct cos_mem_pool_ {
  size_t size;
  struct cos_mem_slot_ slot[cos_mem_slot_max_];
};

// pool (per thread)
extern struct cos_mem_pool_ cos_mem_pool_;
// max unused memory (per thread), default ~32MB
extern size_t cos_mem_pool_max_;

#ifdef _OPENMP
#pragma omp threadprivate (cos_mem_pool_)
#endif

#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(a)
#endif

#ifdef __cplusplus
#  define restrict
#  define ATT __attribute__((always_inline)) inline
#else
#  define ATT __attribute__((always_inline)) static inline
#endif

// -- utils

ATT __attribute__((pure))
union cos_mem_node_* cos_mem_get_base_ (void *ptr)
{
  return (union cos_mem_node_*)((char*)ptr - cos_mem_node_size_);
}

ATT __attribute__((pure))
unsigned cos_mem_get_slot_ (size_t size)
{
  return (size + cos_mem_node_size_-1) / cos_mem_node_size_;
}

ATT __attribute__((pure))
void* cos_mem_node_init_ (union cos_mem_node_ *ptr, unsigned slot)
{
    ptr->used.slot = slot;
    return ptr->used.data;
}

// -- allocator

ATT __attribute__((malloc))
void* cos_mem_alloc (size_t size)
{
  unsigned slot = cos_mem_get_slot_(size);
  struct cos_mem_pool_ *restrict pool = &cos_mem_pool_;
  struct cos_mem_slot_ *restrict pptr = pool->slot+slot;
  union  cos_mem_node_ *ptr;

  if (slot < cos_mem_slot_max_ && pptr->list) {
    pool->size -= slot*cos_mem_node_size_;
    ptr = pptr->list, pptr->list = ptr->free.next;
  }
  else {
    if (pool->size > cos_mem_pool_max_) cos_mem_collect(0,0);
    ptr = (union cos_mem_node_*)malloc((slot+1) * cos_mem_node_size_);
    if (!ptr) return 0;
  }
  return cos_mem_node_init_(ptr, slot);
}

ATT __attribute__((malloc))
void* cos_mem_calloc (size_t count, size_t size)
{
  size_t sz = count*size;
  assert(count < 2 || size < 2 || (sz > count && sz > size));

  void *ptr = cos_mem_alloc(sz);
  if (ptr) memset(ptr, 0, sz);

  return ptr;
}

ATT __attribute__((malloc))
void* cos_mem_realloc (void* ptr_, size_t size)
{
  unsigned slot = cos_mem_get_slot_(size);
  union cos_mem_node_ *ptr = ptr_ ? cos_mem_get_base_(ptr_) : (union cos_mem_node_*)ptr_;
  ptr = (union cos_mem_node_*)realloc(ptr, (slot+1) * cos_mem_node_size_);
  if (!ptr) return 0;

  ptr->used.slot = slot;
  return ptr->used.data;
}

ATT
void cos_mem_free (void* ptr_)
{
  if (!ptr_) return;

  union cos_mem_node_ *ptr = cos_mem_get_base_(ptr_);
  unsigned slot = ptr->used.slot;

  if (slot < cos_mem_slot_max_) {
    struct cos_mem_pool_ *restrict pool = &cos_mem_pool_;
    struct cos_mem_slot_ *restrict pptr = pool->slot+slot;
    pool->size += slot*cos_mem_node_size_;
    ptr->free.next = pptr->list, pptr->list = ptr;
  }
  else free(ptr);
}

// -- allocator, array versions

ATT
int cos_mem_alloc_n (void* ptr_[], int n, size_t size)
{
  unsigned slot = cos_mem_get_slot_(size);
  union cos_mem_node_ *ptr;
  int i = 0;

  if (slot < cos_mem_slot_max_) {
    struct cos_mem_pool_ *restrict pool = &cos_mem_pool_;
    struct cos_mem_slot_ *restrict pptr = pool->slot+slot;

    for (; i < n && pptr->list; i++) {
      ptr = pptr->list, pptr->list = ptr->free.next;
      ptr_[i] = cos_mem_node_init_(ptr, slot);
    }

    pool->size -= i*slot*cos_mem_node_size_;
    if (i < n && pool->size > cos_mem_pool_max_) cos_mem_collect(0,0);

    for (; i < n; i++) {
      ptr = (union cos_mem_node_*)malloc((slot+1) * cos_mem_node_size_);
      if (ptr) ptr_[i] = cos_mem_node_init_(ptr, slot);
      else break;
    }
  } else {
    for (; i < n; i++) {
      ptr = (union cos_mem_node_*)malloc((slot+1) * cos_mem_node_size_);
      if (ptr) ptr_[i] = cos_mem_node_init_(ptr, slot);
      else break;
    }
  }
  return i;
}

ATT
void cos_mem_free_n (void* ptr_[], int n)
{
  if (n > 0) {
    unsigned slot = cos_mem_get_base_(ptr_[n-1])->used.slot;
    
    if (slot < cos_mem_slot_max_) {
      struct cos_mem_pool_ *restrict pool = &cos_mem_pool_;
      struct cos_mem_slot_ *restrict pptr = pool->slot+slot;
      int i = n;

      while (n--) {
        union cos_mem_node_ *ptr = cos_mem_get_base_(ptr_[n]);
        ptr->free.next = pptr->list, pptr->list = ptr;
      }
      pool->size += i*slot*cos_mem_node_size_;
    }
    else
      while (n--) free(cos_mem_get_base_(ptr_[n]));
  }
}

// -- tuning

ATT __attribute__((pure))
size_t cos_mem_size (void* ptr_)
{
  return ptr_ ? cos_mem_get_base_(ptr_)->used.slot * cos_mem_node_size_ : 0;
}

#undef ATT

// --- global redefinition ----------------------------------------------------

#if COS_MEM_AS_DEFAULT

#define malloc(size)        cos_mem_alloc(size)
#define calloc(count,size)  cos_mem_calloc(count,size)
#define realloc(ptr,size)   cos_mem_realloc(ptr,size)
#define free(ptr)           cos_mem_free(ptr)

#endif

// ----------------------------------------------------------------------------
#endif // COS_COS_COSMEM_H

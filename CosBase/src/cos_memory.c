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

// --- declarations ------------------------------------------------------------

#include <cos/Object.h>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define COS_MEM_UTEST 0 // 1 -> run standalone unit tests in main().
#define DBGMEM(P)  // P // uncomment for verbose debugging output

// --- types & constants -------------------------------------------------------

// constant sizes
enum {
  stp_slot = sizeof(double), // memblk unit of size increment, don't touch
  max_slot = 8192,    // max 2^16-2, default 8192 slots -> max obj size is 64KB
  max_mblk = 2048,    // max 2^16-2, default 2048 slots
  max_mkch = 2097152, // max 2^32-1, default 2097152 stp_slot -> 16MB
};

// memory block
struct memblk {
  uint16_t slot; // slot index (i.e. rounded size).
  uint16_t next; // index of next memblk (i.e. linked list).
  uint32_t mark; // memory boundary marker
  union { // alignment of data
    ptrdiff_t s, *sp;
    size_t    u, *up;
    double    d, *dp;
    void         *vp;
    void        (*fp)(void);
  } data[1];
};

// memory pool
struct pool {
  uint32_t mkch;            // amount of cached memory in stp_slot unit
  uint16_t free;            // index of first free slot in mblk
  uint16_t _dum;            // for alignment
  uint16_t slot[max_slot];  // index+1 in mblk of first mbp for this size
  union {
    size_t         nxt;     // index in mblk of next free slot
    struct memblk *mbp;
  }        mblk[max_mblk];
  char     str[128];        // for debug, see pdump()
};

// macros
#define BASE(ptr) ((void*)((char*)(ptr)-stp_slot)) // ptr -> mbp
#define SIZE(idx) (((size_t)(idx)+2)*stp_slot)     // sizeof(*mbp)
#define CACHED(p) ((size_t)(p)->mkch*stp_slot)
#define IDXMAX    0xFFFF
#define SLTMAX    0xFFFFFFFF
#define MARK      0xACCEDEAD

// static sanity checks
enum {
//static_assert__max_slot_not_a_power_of_2 = 1/!(max_slot & (max_slot-1)),
//static_assert__max_mblk_not_a_power_of_2 = 1/!(max_mblk & (max_mblk-1)),
//static_assert__max_mkch_not_a_power_of_2 = 1/!(max_mkch & (max_mkch-1)),
  static_assert__stp_slot_not_a_power_of_2 = 1/!(stp_slot & (stp_slot-1)),
  static_assert__max_slot_not_lt_IDXMAX    = 1/ (max_slot < IDXMAX),
  static_assert__max_mblk_not_lt_IDXMAX    = 1/ (max_mblk < IDXMAX),
  static_assert__max_mkch_not_lt_SLTMAX    = 1/ (max_mkch < SLTMAX),
  static_assert__stp_slot_neq_sizeof       = 1/ (stp_slot == sizeof(double)),
  static_assert__stp_slot_neq_offsetof     = 1/ (stp_slot == offsetof(struct memblk,data)),
};

// --- locals ------------------------------------------------------------------

typedef int32_t idx_t;

static struct pool pool = {0,0,0,{0},{{0}},{0}};

#ifdef _OPENMP
#pragma omp threadprivate(pool)
#endif

static inline char*
pdump(struct memblk *mbp)
{
  struct pool *p = &pool;
  snprintf(p->str, sizeof(p->str), "%p {slot=%4d(%5td), next=%4d, mark=%x}%s",
         (void*)mbp, mbp->slot,
         mbp->slot == IDXMAX ? -1 : (ptrdiff_t)SIZE(mbp->slot),
         mbp->next-1, mbp->mark, mbp->mark == MARK ? "" : " (corrupted!)");
  return p->str;
}

// --- implementation ---------------------------------------------------------o

void*
(cos_malloc) (size_t size)
{
  struct pool *p = &pool;
  size_t idx = size ? (size-1) / stp_slot : 0;
  struct memblk *mbp; // mbp = mblk[slot[idx]-1]

  if (idx < max_slot && p->slot[idx]) {
    idx_t slt = p->slot[idx]-1;
    DBGMEM( printf("alloc: reuse mblk[[%d]=%d]", (int)idx, slt); )
    mbp = p->mblk[slt].mbp, p->mblk[slt].nxt = p->free;
    p->free = p->slot[idx], p->slot[idx] = mbp->next;
    p->mkch -= idx+2;
  } else {
    DBGMEM( printf("alloc: malloc(%2zu)", size); )
    mbp = malloc(SIZE(idx));
    mbp->slot = idx < max_slot ? idx : IDXMAX;
    mbp->mark = MARK;
    ensure((size_t)mbp > IDXMAX, "unexpected very low address"); // see collect
  }

  DBGMEM( printf(" at %s\n", pdump(mbp)); )
  return mbp->data;
}

void
(cos_free) (void *ptr)
{
  if (!ptr) return;

  struct memblk *mbp = BASE(ptr);
  idx_t idx = mbp->slot;

  ensure(mbp->mark == MARK, "invalid or corrupted allocated memory");

  if (idx == IDXMAX) {
    DBGMEM( printf("free : free mblk at %s\n", pdump(mbp)); )
    free(mbp); return;
  }

  struct pool *p = &pool;
  if (!p->free || p->mkch >= max_mkch) // no free slot (or init) or max cache
    cos_mem_collect();

  idx_t slt = p->free-1;
  DBGMEM( printf("free : cache mblk[[%d]=%d]", idx, slt); )
  mbp->next = p->slot[idx], p->slot[idx] = p->free;   // update slot
  p->free = p->mblk[slt].nxt, p->mblk[slt].mbp = mbp; // store  mblk
  p->mkch += idx+2;

  DBGMEM( printf(" at %s\n", pdump(mbp)); )
}

void*
(cos_calloc) (size_t ecount, size_t esize)
{
  size_t size = ecount * esize;
  void  *ptr  = (cos_malloc)(size);
  return memset(ptr, 0, size);
}

void*
(cos_realloc) (void *ptr, size_t size)
{
  if (!size) return (cos_free)(ptr), NULL;
  if (!ptr ) return (cos_malloc)(size);

  DBGMEM( printf("alloc: realloc(%2zu)", size); )
  struct memblk *mbp = BASE(ptr);

  ensure(mbp->mark == MARK, "invalid or corrupted allocated memory");

  size_t idx = (size-1) / stp_slot;
  mbp = realloc(mbp, SIZE(idx));
  mbp->slot = idx < max_slot ? idx : IDXMAX;

  DBGMEM( printf(" at %s\n", pdump(mbp)); )
  return mbp->data;
}

// -- utils

size_t
cos_mem_cached (void)
{
  struct pool *p = &pool;
  size_t ccached = 0, cached = CACHED(p);

  for (idx_t i=0; i < max_mblk; i++)
    if (p->mblk[i].nxt > IDXMAX) // ptr
      ccached += SIZE(p->mblk[i].mbp->slot);

  ensure(ccached == cached, "corrupted cache, ccached == cached bytes");

  return cached;
}

size_t
cos_mem_collect (void)
{
  struct pool *p = &pool;
  size_t cached = CACHED(p);

  DBGMEM(printf("collect/clear/init cache\n");)
  DBGMEM(printf("collecting %zu bytes\n", cos_mem_cached()); cos_mem_mdump();)

  p->mkch = 0;
  p->free = 1;

  for (idx_t i=0; i < max_slot; i++)
    p->slot[i] = 0;

  for (idx_t i=0; i < max_mblk; i++) {
    if (p->mblk[i].nxt > IDXMAX) // ptr
      free(p->mblk[i].mbp);
    p->mblk[i].nxt = i+2;
  }
  p->mblk[max_mblk-1].nxt = 0; // close linked list

  DBGMEM( printf("status after collect\n"); cos_mem_mdump(); )
  return cached;
}

// -- debug

void
cos_mem_mdump (FILE *fp)
{
  struct pool *p = &pool;

  if (!fp) fp = stdout;

  fprintf(fp, "mdump: %zu bytes\n", CACHED(p));

  // display content of slot[] when used, i.e. link to mblk[] + linked list.
  for (idx_t i=0; i < max_slot; i++) {
    idx_t slt = p->slot[i];
    if (slt) { // from slot (size) to memblk (object)
      fprintf(fp, "  slot[%4d] -> mblk[%d]", i, slt-1);
      struct memblk *mbp = p->mblk[slt-1].mbp;
      while (mbp->next) { // linked list
        fprintf(fp, "->[%d]", mbp->next-1);
        mbp = p->mblk[mbp->next-1].mbp;
      }
      fprintf(fp, "\n");
    }
  }

  // display content of mblk[], i.e. object or not trivial link into mblk[]
  for (idx_t i=0; i < max_mblk; i++)
    if (p->mblk[i].nxt > IDXMAX)         // ptr
      fprintf(fp, "  mblk[%4d] -> %s\n", i, pdump(p->mblk[i].mbp));
    else if (i+1 == p->free)  // free
      fprintf(fp, "->mblk[%4d] -> [%d]\n", i, (int)p->mblk[i].nxt-1);
    else if (i+2 != (int)p->mblk[i].nxt) // idx
      fprintf(fp, "  mblk[%4d] -> [%d]\n", i, (int)p->mblk[i].nxt-1);
}

// --- end ---------------------------------------------------------------------

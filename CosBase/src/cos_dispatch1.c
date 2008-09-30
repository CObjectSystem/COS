/*
 o---------------------------------------------------------------------o
 |
 | COS cache for method1
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
 | $Id: cos_dispatch1.c,v 1.2 2008/09/30 08:18:23 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/message.h>

#include <stdlib.h>

/* NOTE-CONF: Method dispatcher cache max slots (Method lookup)
 * The slots specifies the maximum number of entries for each cache.
 * This number must be of the form 2^n > 512.
 * Number of slots increase upon collision until maxslot is reached.
 * The maxdepth (e.g. memory) of each slot is fixed to 3.
 */

#ifndef COS_METHOD_MAXSLOT1
#define COS_METHOD_MAXSLOT1 262144
#endif

// test for 2^n > 512
STATIC_ASSERT(COS_METHOD_MAXSLOT1_must_be_a_pow2_greater_than_512,
              COS_METHOD_MAXSLOT1 > 512 &&
              (COS_METHOD_MAXSLOT1 & (COS_METHOD_MAXSLOT1-1)) == 0);

static void init(SEL,OBJ,void*,void*);

static struct cos_method_slot1 sentinel = { &sentinel,init,0,0 };
static struct cos_method_slot1 *cache_empty = &sentinel;

#if COS_TLS
__thread struct cos_method_cache1 cos_method_cache1 = { &cache_empty, 0 };
#elif COS_POSIX
         struct cos_method_cache1 cos_method_cache1 = { &cache_empty, 0 };
#else
         struct cos_method_cache1 cos_method_cache1 = { &cache_empty, 0 };
#endif

static void
init(SEL _sel, OBJ _1, void *_arg, void *_ret)
{
  cos_init();
  forward_message(_1);
}

static inline U32
first_cell(struct cos_method_slot1 **slot)
{
  struct cos_method_slot1 *sl = *slot;
  U32 n = 0;

  while (sl != &sentinel) {
    if (sl < *slot) *slot = sl;
    sl = sl->nxt, ++n;
  }

  return n;
}

static void
enlarge_slot(struct cos_method_slot1 **slot)
{
  U32 i, n = first_cell(slot);

  *slot = realloc(n ? *slot : 0, (n+1) * sizeof **slot);
  if (!*slot)
    cos_abort("method1_lookup: out of memory");

  for (i = 0; i < (n+1); i++) {
    (*slot)[i].nxt = *slot+i+1; // Ok: see C99 6.5.6-8
    (*slot)[i].fct = 0;
    (*slot)[i].idg = 0;
    (*slot)[i].id1 = 0;
  }

  (*slot)[n].nxt = &sentinel;
}

static void
enlarge_cache(void)
{
  U32 i, n;

  n = cos_method_cache1.msk ? (cos_method_cache1.msk+1)*2 : 512;
  cos_method_clearCache1();

  cos_method_cache1.slot = malloc(n * sizeof *cos_method_cache1.slot);
  if (!cos_method_cache1.slot)
    cos_abort("method1_lookup: out of memory");

  for (i = 0; i < n; i++)
    cos_method_cache1.slot[i] = &sentinel;

  cos_method_cache1.msk = n-1;
}

static struct cos_method_slot1**
load_method(SEL _sel, U32 id1, BOOL load)
{
  struct cos_method_slot1 **slot;
  IMP1 fct;
  U32 key;

  // search method
  fct = cos_method_get1(_sel,id1);
  if (!fct) {
    if (!load) return 0;
    fct = cos_method_get1(&COS_GEN_NAME(gunrecognizedMessage1),id1);
    if (!fct)
      cos_abort("method1_lookup: %s not found for class %s",
                "gunrecognizedMessage1", cos_class_get(id1)->name);
  }

  // get slot
  key  = cos_method_hkey1(_sel->Behavior.id,id1);
  slot = cos_method_cache1.slot + (key & cos_method_cache1.msk);

  // get cell
  if (cos_method_cache1.msk < COS_METHOD_MAXSLOT1-1) {
    if (*slot != &sentinel || slot == &cache_empty) {
      // try to ensure O(1) until MAXSLOT is reached
      enlarge_cache();
      slot = cos_method_cache1.slot + (key & cos_method_cache1.msk);
    }
    // allocate 1st cell
    enlarge_slot(slot);

  } else {
    // 1st cell is never free
    if ((*slot)->nxt->fct == 0) {
      // 2nd cell exists and is not used
      struct cos_method_slot1 *tmp = *slot;
      *slot = tmp->nxt, tmp->nxt = (*slot)->nxt, (*slot)->nxt = tmp;

    } else if ((*slot)->nxt->nxt != &sentinel) {
      // 3rd cell exists and may be used (and forget)
      struct cos_method_slot1 *tmp = *slot;
      *slot = tmp->nxt->nxt, tmp->nxt->nxt = (*slot)->nxt, (*slot)->nxt = tmp;

    } else
      // allocate one more cell
      enlarge_slot(slot);
  }

  // load fct in the cache
  (*slot)->fct = fct;
  (*slot)->idg = _sel->Behavior.id;
  (*slot)->id1 = id1;

  return slot;
}

#define CACHE_GET_SLOT() \
  U32 key = cos_method_hkey1(_sel->Behavior.id,id1); \
  struct cos_method_slot1 **slot = \
    cos_method_cache1.slot + (key & cos_method_cache1.msk);

#define CACHE_MTH_LOAD(LOAD) \
  slot = load_method(_sel,id1,LOAD);

#define CACHE_TST_LEVEL1() \
  if (_sel->Behavior.id  == (*slot)->idg && \
                     id1 == (*slot)->id1)   \
    goto ret;

#define CACHE_TST_LEVEL2() \
  if (_sel->Behavior.id  == (*slot)->nxt->idg && \
                     id1 == (*slot)->nxt->id1) { \
    struct cos_method_slot1 *tmp = *slot; \
    *slot = tmp->nxt, tmp->nxt = (*slot)->nxt, (*slot)->nxt = tmp; \
    goto ret; \
  }

#define CACHE_TST_LEVEL3() \
  if (_sel->Behavior.id  == (*slot)->nxt->nxt->idg && \
                     id1 == (*slot)->nxt->nxt->id1) { \
    struct cos_method_slot1 *tmp = *slot; \
    *slot = tmp->nxt->nxt, tmp->nxt->nxt = (*slot)->nxt, (*slot)->nxt = tmp; \
    goto ret; \
  }

IMP1
cos_method_lookup1(SEL _sel, U32 id1)
{
  CACHE_GET_SLOT();
  CACHE_TST_LEVEL1();
  CACHE_TST_LEVEL2();
  CACHE_TST_LEVEL3();
  CACHE_MTH_LOAD(YES);

 ret:
  return (*slot)->fct;
}

IMP1
cos_method_fastLookup1_(struct cos_method_slot1 **slot, SEL _sel, U32 id1)
{
  CACHE_TST_LEVEL2();
  CACHE_TST_LEVEL3();
  CACHE_MTH_LOAD(YES);

 ret:
  return (*slot)->fct;
}

BOOL
cos_method_understand1_(struct cos_method_slot1 **slot, SEL _sel, U32 id1)
{
  CACHE_TST_LEVEL2();
  CACHE_TST_LEVEL3();
  CACHE_MTH_LOAD(NO);

 ret:
  return slot != 0;
}

void
cos_method_clearCache1(void)
{
  U32 i;

  if (cos_method_cache1.slot != &cache_empty) {
    for (i = 0; i <= cos_method_cache1.msk; i++) {
      struct cos_method_slot1 **slot = cos_method_cache1.slot+i;

      if (*slot != &sentinel)
        first_cell(slot), free(*slot);
    }

    free(cos_method_cache1.slot);
    cos_method_cache1.slot = &cache_empty;
    cos_method_cache1.msk = 0;
  }
}

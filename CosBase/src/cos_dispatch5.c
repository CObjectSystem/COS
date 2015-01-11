/**
 * C Object System
 * COS cache for method5
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

#include <cos/Object.h>
#include <cos/gen/message.h>

#include <stdlib.h>

/* NOTE-CONF: Method dispatcher cache max slots (Method lookup)
 * The slots specifies the maximum number of entries for each cache.
 * This number must be of the form 2^n > 512.
 * Number of slots increase upon collision until maxslot is reached.
 * The maxdepth (e.g. memory) of each slot is fixed to 3.
 */

#ifndef COS_METHOD_MAXSLOT5
#define COS_METHOD_MAXSLOT5 8192
#endif

// test for 2^n > 512
STATIC_ASSERT(COS_METHOD_MAXSLOT5_must_be_a_pow2_greater_than_512,
              COS_METHOD_MAXSLOT5 > 512 &&
              (COS_METHOD_MAXSLOT5 & (COS_METHOD_MAXSLOT5-1)) == 0);

STATIC_ASSERT(COS_METHOD_CACHE5_must_have_a_size_of_64_bytes,
              sizeof(struct cos_method_cache5) == 64);

static void init(SEL,OBJ,OBJ,OBJ,OBJ,OBJ,void*,void*);

static struct cos_method_slot5 sentinel = { 0,0,0,0,0,0,init,&sentinel };
static struct cos_method_slot5 *cache_empty = &sentinel;

#if defined(_OPENMP) || COS_HAS_TLS || !COS_HAS_POSIX // --------------------

__thread struct cos_method_cache5 cos_method_cache5_
  __attribute__((aligned(64))) = { &cache_empty, 0, 0, 0, {0} };

#else // !defined(_OPENMP) && !COS_HAS_TLS && COS_HAS_POSIX -----------------

       int            cos_method_cache5_key_init = 0;
       pthread_key_t  cos_method_cache5_key;
static pthread_once_t cos_method_cache5_key_once = PTHREAD_ONCE_INIT;

static void
make_key(void)
{
  if ( pthread_key_create(&cos_method_cache5_key, free) )
    cos_abort("unable to initialize dispatcher cache5");
}

struct cos_method_cache5*
cos_method_cache5_init(void)
{
  struct cos_method_cache5 *cache;
  
  pthread_once(&cos_method_cache5_key_once, make_key);
  cos_method_cache5_key_init = 1;

  if (!(cache = malloc(sizeof *cache)))
	  cos_abort("out of memory while creating dispatcher cache5");

	cache->slot = &cache_empty;
	cache->msk  = 0;
	cache->mis  = 0;
	cache->mis2 = 0;

  if ( pthread_setspecific(cos_method_cache5_key, cache) )
	  cos_abort("unable to initialize dispatcher cache5");

  return cache;
}

#endif // ------------------------------------------------

static void
init(SEL _sel, OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, void *_arg, void *_ret)
{
  cos_init();
  forward_message(_1,_2,_3,_4,_5);
}

static inline U32
first_cell(struct cos_method_slot5 **slot)
{
  struct cos_method_slot5 *sl = *slot;
  U32 n = 0;

  while (sl != &sentinel) {
    if (sl < *slot) *slot = sl;
    sl = sl->nxt, ++n;
  }

  return n;
}

static void
enlarge_slot(struct cos_method_slot5 **slot)
{
  U32 i, n = first_cell(slot);

  *slot = realloc(n ? *slot : 0, (n+1) * sizeof **slot);
  if (!*slot)
    cos_abort("method5_lookup: out of memory");

  for (i = 0; i < n+1; i++) {
    (*slot)[i].nxt = *slot+i+1; // Ok: see C99 6.5.6-8
    (*slot)[i].fct = init;
    (*slot)[i].idg = 0;
    (*slot)[i].id1 = 0;
    (*slot)[i].id2 = 0;
    (*slot)[i].id3 = 0;
    (*slot)[i].id4 = 0;
    (*slot)[i].id5 = 0;
  }

  (*slot)[n].nxt = &sentinel;
}

static void
enlarge_cache(void)
{
	struct cos_method_cache5 *cache = cos_method_cache5();
  U32 i, n;

  n = cache->msk ? (cache->msk+1)*2 : 512;
  cos_method_clearCache5();

  cache->slot = malloc(n * sizeof *cache->slot);
  if (!cache->slot)
    cos_abort("method5_lookup: out of memory");

  for (i = 0; i < n; i++)
    cache->slot[i] = &sentinel;

  cache->msk = n-1;
}

static struct cos_method_slot5**
load_method(SEL _sel, U32 id1, U32 id2, U32 id3, U32 id4, U32 id5, BOOL load)
{
	struct cos_method_cache5 *cache;
  struct cos_method_slot5 **slot;
  IMP5 fct;
  U32 key;

  fct = cos_method_get5(_sel, id1, id2, id3, id4, id5);
  if (!fct) {
    if (!load) return 0;
    fct = cos_method_get5(genericref(gunrecognizedMessage5),
                          id1, id2, id3, id4, id5);
    if (!fct)
      cos_abort("method5_lookup: %s not found for classes (%s,%s,%s,%s,%s)",
                "gunrecognizedMessage5",
                cos_class_get(id1)->str, cos_class_get(id2)->str,
                cos_class_get(id3)->str, cos_class_get(id4)->str,
                cos_class_get(id5)->str);
  }

  // get slot
  key   = cos_method_hkey5(_sel->Behavior.id,id1,id2,id3,id4,id5);
	cache = cos_method_cache5();
  slot  = cache->slot + (key & cache->msk);

  // get cell
  if (cache->msk < COS_METHOD_MAXSLOT5-1) {
    if (*slot != &sentinel || slot == &cache_empty) {
      // try to ensure O(1) until MAXSLOT is reached
      enlarge_cache();
      slot = cache->slot + (key & cache->msk);
    }
    // allocate 1st cell
    enlarge_slot(slot);

  } else {
    // 1st cell is never free
    if ((*slot)->nxt->fct == 0) {
      // 2nd cell exists and is not used
      struct cos_method_slot5 *tmp = *slot;
      *slot = tmp->nxt, tmp->nxt = (*slot)->nxt, (*slot)->nxt = tmp;

    } else if ((*slot)->nxt->nxt != &sentinel) {
      // 3rd cell exists and may be used (then forget)
      struct cos_method_slot5 *tmp = *slot;
      *slot = tmp->nxt->nxt, tmp->nxt->nxt = (*slot)->nxt, (*slot)->nxt = tmp;
      if (!++cache->mis) cache->mis2++;

    } else
      // allocate one more cell
      enlarge_slot(slot);
  }

  // load fct in the cache
  (*slot)->fct = fct;
  (*slot)->idg = _sel->Behavior.id;
  (*slot)->id1 = id1;
  (*slot)->id2 = id2;
  (*slot)->id3 = id3;
  (*slot)->id4 = id4;
  (*slot)->id5 = id5;

  return slot;
}

#define CACHE_GET_SLOT() \
  U32 key = cos_method_hkey5(_sel->Behavior.id,id1,id2,id3,id4,id5); \
	struct cos_method_cache5 *restrict cache = cos_method_cache5(); \
  struct cos_method_slot5 *restrict*restrict slot = cache->slot + (key & cache->msk);


#define CACHE_MTH_LOAD(load) \
  slot = load_method(_sel,id1,id2,id3,id4,id5,load);

#define CACHE_TST_LEVEL1() \
  if (_sel->Behavior.id  == (*slot)->idg && \
                     id1 == (*slot)->id1 && \
                     id2 == (*slot)->id2 && \
                     id3 == (*slot)->id3 && \
                     id4 == (*slot)->id4 && \
                     id5 == (*slot)->id5)   \
    goto ret;

#define CACHE_TST_LEVEL2() \
  if (_sel->Behavior.id  == (*slot)->nxt->idg && \
                     id1 == (*slot)->nxt->id1 && \
                     id2 == (*slot)->nxt->id2 && \
                     id3 == (*slot)->nxt->id3 && \
                     id4 == (*slot)->nxt->id4 && \
                     id5 == (*slot)->nxt->id5) { \
    struct cos_method_slot5 *tmp = *slot; \
    *slot = tmp->nxt, tmp->nxt = (*slot)->nxt, (*slot)->nxt = tmp; \
    goto ret; \
  }

#define CACHE_TST_LEVEL3() \
  if (_sel->Behavior.id  == (*slot)->nxt->nxt->idg && \
                     id1 == (*slot)->nxt->nxt->id1 && \
                     id2 == (*slot)->nxt->nxt->id2 && \
                     id3 == (*slot)->nxt->nxt->id3 && \
                     id4 == (*slot)->nxt->nxt->id4 && \
                     id5 == (*slot)->nxt->nxt->id5) { \
    struct cos_method_slot5 *tmp = *slot; \
    *slot = tmp->nxt->nxt, tmp->nxt->nxt = (*slot)->nxt, (*slot)->nxt = tmp; \
    goto ret; \
  }

IMP5
cos_method_lookup5(SEL restrict _sel,
                   U32 id1, U32 id2, U32 id3, U32 id4, U32 id5)
{
  CACHE_GET_SLOT();
  CACHE_TST_LEVEL1();
  CACHE_TST_LEVEL2();
  CACHE_TST_LEVEL3();
  CACHE_MTH_LOAD(YES);

 ret:
  return (*slot)->fct;
}

IMP5
cos_method_fastLookup5_(struct cos_method_slot5 *restrict*restrict slot,
                        SEL restrict _sel,
			                  U32 id1, U32 id2, U32 id3, U32 id4, U32 id5)
{
  CACHE_TST_LEVEL2();
  CACHE_TST_LEVEL3();
  CACHE_MTH_LOAD(YES);

 ret:
  return (*slot)->fct;
}

BOOL
cos_method_understand5_(struct cos_method_slot5 *restrict*restrict slot,
                        SEL restrict _sel,
			                  U32 id1, U32 id2, U32 id3, U32 id4, U32 id5)
{
  CACHE_TST_LEVEL2();
  CACHE_TST_LEVEL3();
  CACHE_MTH_LOAD(NO);

 ret:
  return slot != 0;
}

void
cos_method_clearCache5(void)
{
	struct cos_method_cache5 *cache = cos_method_cache5();
  U32 i;

  if (cache->slot != &cache_empty) {
    for (i = 0; i <= cache->msk; i++) {
      struct cos_method_slot5 **slot = cache->slot+i;

      if (*slot != &sentinel)
        first_cell(slot), free(*slot);
    }

    free(cache->slot);
    cache->slot = &cache_empty;
    cache->msk  = 0;
    cache->mis  = 0;
    cache->mis2 = 0;
  }
}

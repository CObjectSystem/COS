/*
 o---------------------------------------------------------------------o
 |
 | COS core
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
 | $Id: cos_symbol.c,v 1.10 2008/10/16 12:50:11 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Class.h>
#include <cos/MetaClass.h>
#include <cos/Method.h>
#include <cos/gen/object.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum { MAX_TBL = 50 };

static struct Object **tbl[MAX_TBL];

static struct {
  struct Behavior **bhv; // sorted by id % msk
  struct Class    **cls; // sorted by str
  struct Generic  **gen; // sorted by str
  struct Method   **mth; // sorted by gen then rnk
  FUNC            **nxt; // not sorted
  U32 msk, n_cls, n_gen, n_mth, n_nxt, m_nxt;
} sym;

static inline U32
toPow2(U32 val)
{
  U32 i = 1;

  while(i < val)
    i *= 2;

  return i;
}

static inline U32
bhv_msk(U32 sz)
{
  return toPow2(sz)-1;
}

static inline U32
bhv_tag(void)
{
  static U32 x = 1;
  U32 tag;

  x = x * 2621124293u + 1;       // generator of \frac{\set{N}}{2^{32}\set{N}}
  tag = x & COS_ID_TAGMSK;

  if (!tag) cos_abort("too many behavior tags");

  return tag;
}

static inline void
bhv_setTag(struct Behavior *bhv)
{
  if (bhv->Object.Any.id) {  // generics case
    if (bhv->id) cos_abort("behavior has already an id");

    bhv->id = bhv->Object.Any.id | bhv_tag();
    bhv->Object.Any.id = 0;
  } else                    // classes case
    bhv->id |= bhv_tag();
}

static int // qsort
cls_cmp(const void *_cls1, const void *_cls2)
{
  struct Class *cls1 = *(struct Class* const*)_cls1;
  struct Class *cls2 = *(struct Class* const*)_cls2;

  return strcmp(cls1->name, cls2->name);
}

static int // qsort
gen_cmp(const void *_gen1, const void *_gen2)
{
  struct Generic *gen1 = *(struct Generic* const*)_gen1;
  struct Generic *gen2 = *(struct Generic* const*)_gen2;

  return strcmp(gen1->name, gen2->name);
}

static int // qsort
mth_cmp(const void *_mth1, const void *_mth2)
{
  struct Method *mth1 = *(struct Method* const*)_mth1;
  struct Method *mth2 = *(struct Method* const*)_mth2;
  int res;

  // ascending generic name
  if (mth1->gen != mth2->gen && (res=strcmp(mth1->gen->name,mth2->gen->name)))
    return res;

  // descending rank order
  return (mth1->info < mth2->info) - (mth1->info > mth2->info);
}

static int // qsort
cls_strcmp(const void *str, const void *_cls)
{
  struct Class *cls = *(struct Class* const*)_cls;

  return strcmp(str,cls->name);
}

static int // qsort
gen_strcmp(const void *str, const void *_gen)
{
  struct Generic *gen = *(struct Generic* const*)_gen;

  return strcmp(str,gen->name);
}

static inline BOOL
cls_isMeta(struct Class *cls)
{
  return cls->Behavior.Object.Any.id == COS_CLS_NAME(MetaClass).Behavior.id;
}

static inline BOOL
cls_isProp(struct Class *cls)
{
  return cls->Behavior.Object.Any.id == COS_CLS_NAME(PropMetaClass).Behavior.id;
}

static inline void
mth_initAlias(struct Method1 *ali)
{
  // hack: retrieve aliased method stored in cls[0]
  struct Method1 *mth = STATIC_CAST(struct Method1*, ali->cls[0]);

  ali->fct = mth->fct;
  ali->cls[0] = mth->cls[0];
  ali->Method.info = mth->Method.info;
  ali->Method.Object.Any.rc = cos_tag_method; // convert alias to method
}

static inline void
gen_incMth(struct Generic *gen)
{
  if (COS_GEN_NMTH(gen) == COS_GEN_MAXMTH)
    cos_abort("too many specializations for generic %s", gen->name);

  ++gen->info;
}

static inline void
bhv_enlarge(U32 msk)
{
  struct Behavior **bhv = calloc(msk+1, sizeof *bhv);
  U32 i;

  if (!bhv)
    cos_abort("out of memory while storing symbols");

  if (sym.bhv) {
    for (i = 0; i <= sym.msk; i++) {
      struct Behavior *b = sym.bhv[i];
      if (b) bhv[b->id & msk] = b;
    }
    free(sym.bhv);
  }

  sym.bhv = bhv, sym.msk = msk;
}

static inline void
gen_setMth(void)
{
  U32 i, n = 0;

  for (i = 0; i < sym.n_gen; i++) {
    struct Generic *gen = sym.gen[i];
    gen->mth = n;
    n += COS_GEN_NMTH(gen);
  }

  // if missing generics, methods might have been loaded before generics
  if (n != sym.n_mth)
    cos_abort("some methods have been loaded before their generics (?)");
}

static inline void
nxt_enlarge(void)
{
  U32 m = sym.m_nxt < 128 ? 128 : sym.m_nxt*2;
  FUNC **nxt = realloc(sym.nxt, m * sizeof *sym.nxt);

  if (!nxt)
    cos_abort("out of memory while storing next methods");

  sym.nxt = nxt;
  sym.m_nxt = m;
}

static inline void
nxt_add(FUNC *fct)
{
  if (sym.n_nxt == sym.m_nxt)
    nxt_enlarge();

  sym.nxt[sym.n_nxt++] = fct;
}

static inline void
nxt_clear(void)
{
  while (sym.n_nxt)
    *sym.nxt[--sym.n_nxt] = (FUNC)YES;
}

static inline BOOL
mth_isSubOf(struct Class* const*cls, struct Class* const* ref, U32 n_cls)
{
  BOOL yes = YES;

  switch(n_cls) {
   case 5: yes = yes && cos_class_isSubclassOf(cls[4],ref[4]);
   case 4: yes = yes && cos_class_isSubclassOf(cls[3],ref[3]);
   case 3: yes = yes && cos_class_isSubclassOf(cls[2],ref[2]);
   case 2: yes = yes && cos_class_isSubclassOf(cls[1],ref[1]);
   case 1: yes = yes && cos_class_isSubclassOf(cls[0],ref[0]);
  }
  return yes;
}

static inline void
nxt_init(FUNC *fct, SEL gen, U32 info, struct Class *const *cls)
{
  struct Method5 **mth = STATIC_CAST(struct Method5**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 n_cls = COS_GEN_RNK (gen);
  U32 i = 0;

  for (; i < n_mth; i++)
    if (info > mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, n_cls)) {
      *fct = (FUNC)mth[i]->fct;
      nxt_add(fct);
      return;
    }

  *fct = 0;
}

static void
sym_prepStorage(U32 n_cls, U32 n_gen, U32 n_mth)
{
  U32 n_bhv, msk;

  if (n_cls) sym.cls = realloc(sym.cls, (n_cls+=sym.n_cls) * sizeof *sym.cls);
  if (n_gen) sym.gen = realloc(sym.gen, (n_gen+=sym.n_gen) * sizeof *sym.gen);
  if (n_mth) sym.mth = realloc(sym.mth, (n_mth+=sym.n_mth) * sizeof *sym.mth);

  if ((!sym.cls && n_cls) || (!sym.gen && n_gen) || (!sym.mth && n_mth))
    cos_abort("out of memory while storing symbols");

  n_bhv = n_gen + 3*n_cls;

  if (n_bhv) {
    msk = bhv_msk(n_bhv);
    if (msk > sym.msk)
      bhv_enlarge(msk);
  }
}

static void
sym_init(void)
{
  U32 n_cls=0, n_mcl=0, n_pcl=0, n_gen=0, n_mth=0;
  U32 t, s;

  // count symbols
  for (t = 0; t < MAX_TBL && tbl[t]; t++) {
    for (s = 0; tbl[t][s]; s++) {

      // count symbols
      switch(tbl[t][s]->Any.rc) {
      case cos_tag_class  : ++n_cls; break;
      case cos_tag_mclass : ++n_mcl; break;
      case cos_tag_pclass : ++n_pcl; break;
      case cos_tag_generic: ++n_gen; break;
      case cos_tag_alias  : mth_initAlias(STATIC_CAST(struct Method1*, tbl[t][s]));
      case cos_tag_method : ++n_mth; break;
      default: cos_abort("invalid COS symbol");
      }

      // set behavior tag
      if (tbl[t][s]->Any.rc != cos_tag_method)
        bhv_setTag(STATIC_CAST(struct Behavior*, tbl[t][s]));
    }
  }

  // check consistency between Class, MetaClass and PropMetaClass
  if (n_cls != n_mcl || n_cls != n_pcl)
    cos_abort("invalid number of (property) meta classes vs classes");

  // prepare storage for new symbols
  sym_prepStorage(n_cls,n_gen,n_mth);

  // copy & prepare symbols
  for (t = 0; t < MAX_TBL && tbl[t]; t++) {
    for (s = 0; tbl[t][s]; s++) {

      // add behavior symbol to behavior table
      if (tbl[t][s]->Any.rc != cos_tag_method) {
        struct Behavior *bhv = STATIC_CAST(struct Behavior*, tbl[t][s]);
        U32 i = bhv->id & sym.msk;
        if (sym.bhv[i]) cos_abort("behavior slot %u already assigned", i);
        sym.bhv[i] = bhv;
      }

      // finalize symbol information and store it
      switch(tbl[t][s]->Any.rc) {
      case cos_tag_class: {
        struct Class *cls = STATIC_CAST(struct Class*, tbl[t][s]);
        const struct Class *pcl = STATIC_CAST(const struct Class*, cls->name);
        sym.cls[sym.n_cls++] = cls;                            // hack: meta-link
        cls->name = pcl->name+2; // hack: name is shared
        cls->Behavior.Object.Any.id = pcl->Behavior.id;
        cls->Behavior.Object.Any.rc = COS_RC_STATIC;
      } break;

      case cos_tag_pclass: {
        struct Class *pcl = STATIC_CAST(struct Class*, tbl[t][s]);
        pcl->spr->name = pcl->name+1; // hack: name is shared
        pcl->Behavior.Object.Any.id = COS_CLS_NAME(PropMetaClass).Behavior.id;
        pcl->Behavior.Object.Any.rc = COS_RC_STATIC;
      } break;

      case cos_tag_mclass: {
        struct Class *mcl = STATIC_CAST(struct Class*, tbl[t][s]);
        mcl->Behavior.Object.Any.id = COS_CLS_NAME(MetaClass).Behavior.id;
        mcl->Behavior.Object.Any.rc = COS_RC_STATIC;
      } break;

      case cos_tag_generic: {
        struct Generic *gen = STATIC_CAST(struct Generic*, tbl[t][s]);
        sym.gen[sym.n_gen++] = gen;
        gen->Behavior.Object.Any.id = COS_CLS_NAME(Generic).Behavior.id;
        gen->Behavior.Object.Any.rc = COS_RC_STATIC;
      } break;

      case cos_tag_method: {
        struct Method *mth = STATIC_CAST(struct Method*, tbl[t][s]);
        gen_incMth(mth->gen);
        sym.mth[sym.n_mth++] = mth;
        mth->Object.Any.rc = COS_RC_STATIC;
        switch(COS_GEN_RNK(mth->gen)) {
        case 1: mth->Object.Any.id = COS_CLS_NAME(Method1).Behavior.id; break;
        case 2: mth->Object.Any.id = COS_CLS_NAME(Method2).Behavior.id; break;
        case 3: mth->Object.Any.id = COS_CLS_NAME(Method3).Behavior.id; break;
        case 4: mth->Object.Any.id = COS_CLS_NAME(Method4).Behavior.id; break;
        case 5: mth->Object.Any.id = COS_CLS_NAME(Method5).Behavior.id; break;
        }
      }}
    }
  }

  // sort symbols
  qsort(sym.cls, sym.n_cls, sizeof *sym.cls, cls_cmp);
  qsort(sym.gen, sym.n_gen, sizeof *sym.gen, gen_cmp);
  qsort(sym.mth, sym.n_mth, sizeof *sym.mth, mth_cmp);

  // set generics' methods indexes
  gen_setMth();
}

static void
sym_deinit(void)
{
  free(sym.bhv), sym.bhv = 0, sym.  msk = 0;
  free(sym.cls), sym.cls = 0, sym.n_cls = 0;
  free(sym.gen), sym.gen = 0, sym.n_gen = 0;
  free(sym.mth), sym.mth = 0, sym.n_mth = 0;
  free(sym.nxt), sym.nxt = 0, sym.n_nxt = 0, sym.m_nxt = 0;
}

static void
cls_init(void)
{
  struct Generic *gen = &COS_GEN_NAME(ginitialize);
  struct Method1 **ini = STATIC_CAST(struct Method1**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i;

  // invoke (prop)meta class ginitialize starting from super classes
  for (i = n_mth; i-- > 0; ) {
    struct Class *cls = ini[i]->cls[0];

    if (cls_isMeta(cls)) {
      cls = cos_class_getWithStr(cls->name+1);
      ginitialize((OBJ)cls);
    } else

    if (cls_isProp(cls)) {
      cls = cos_class_getWithStr(cls->name+2);
      ginitialize((OBJ)cls);
    }
  }
}

static void
cls_deinit(void)
{
  struct Generic *gen = &COS_GEN_NAME(gdeinitialize);
  struct Method1 **dei = STATIC_CAST(struct Method1**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i;

  // invoke (prop)meta class gdeinitialize starting from subclasses
  for (i = 0; i < n_mth; i++) {
    struct Class *cls = dei[i]->cls[0];

    if (cls_isMeta(cls)) {
      cls = cos_class_getWithStr(cls->name+1);
      gdeinitialize((OBJ)cls);
    } else

    if (cls_isProp(cls)) {
      cls = cos_class_getWithStr(cls->name+2);
      gdeinitialize((OBJ)cls);
    }
  }
}

/*
 * ----------------------------------------------------------------------------
 *  Global Functions
 * ----------------------------------------------------------------------------
 */

// ----- general

static BOOL init_done = NO;
static double init_duration = 0.0;
static double deinit_duration = 0.0;

void
cos_init(void)
{
  if (init_done == NO) {
    double t0, t1;

    init_done = YES;
    cos_symbol_init();
    // cos_trace("cos_init");

    t0 = clock();
    sym_init();
    cls_init();
    t1 = clock();
    init_duration = (t1-t0)/CLOCKS_PER_SEC;

    if (atexit(cos_deinit))
      cos_warn("unable to register COS cleaning at exit");
  }
}

void
cos_deinit(void)
{
  if (init_done == YES) {
    double t0, t1;

    init_done = NO;
    // cos_trace("cos_deinit");

    t0 = clock();
    cls_deinit();
    sym_deinit();
    t1 = clock();
    deinit_duration = (t1-t0)/CLOCKS_PER_SEC;

    cos_method_clearCaches();
  }
}

double
cos_initDuration(void)
{
  return init_duration;
}

double
cos_deinitDuration(void)
{
  return deinit_duration;
}

//  ----- symbol

void
cos_symbol_register(struct Object* sym[])
{
  U32 i;

  if (!sym) cos_abort("null symbol table");

  for (i=0; i < MAX_TBL && tbl[i]; i++)
    if (tbl[i] == sym)
      return;

  if (i == MAX_TBL)
    cos_abort("too many COS symbols tables registered");

  tbl[i++] = sym;
}

// ----- generic

struct Generic*
cos_generic_get(U32 id)
{
  struct Generic *gen = STATIC_CAST(struct Generic*, sym.bhv[id & sym.msk]);

  if (!gen
    || gen->Behavior.id != id
    || gen->Behavior.Object.Any.id != COS_CLS_NAME(Generic).Behavior.id)
    cos_abort("invalid generic id %d", id);

  return gen;
}

struct Generic*
cos_generic_getWithStr(STR str)
{
  struct Generic *gen;

  gen = bsearch(str, sym.gen, sym.n_gen, sizeof *sym.gen, gen_strcmp);

  return gen ? *(struct Generic**)gen : 0;
}

// ----- class

struct Class*
cos_class_get(U32 id)
{
  struct Class *cls = STATIC_CAST(struct Class*, sym.bhv[id & sym.msk]);

  if (!cls
    || cls->Behavior.id != id
    || cls->Behavior.Object.Any.id == COS_CLS_NAME(Generic).Behavior.id)
    cos_abort("invalid class id %d", id);

  return cls;
}

struct Class*
cos_class_getWithStr(STR str)
{
  struct Class *cls;
  STR p;

  p = str + (str[0] == 'm') + (str[0] == 'p') + (str[1] == 'm');

  cls = bsearch(p, sym.cls, sym.n_cls, sizeof *sym.cls, cls_strcmp);

  if (!cls) return 0;
  cls = *(struct Class**)cls;

  switch(p-str) {
  case 1:
    cls = cos_class_get(cls->Behavior.id)->spr;
    test_assert( cls_isMeta(cls) );
    break;

  case 2:
    cls = cos_class_get(cls->Behavior.id);
    test_assert( cls_isProp(cls) );
    break;

  default:
    test_assert( !cls_isMeta(cls) && !cls_isProp(cls) );
  }

  return cls;
}

BOOL
cos_class_isSubclassOf(const struct Class *cls, const struct Class *ref)
{
  U32 rnk = COS_ID_URK(ref->Behavior.id);

  while (cls->Behavior.id > rnk)
    cls = cls->spr;

  return cls == ref;
}

// ----- any

BOOL
cos_any_isKindOf(OBJ _1, const struct Class *ref)
{
  return cos_class_isSubclassOf(cos_class_get(cos_any_id(_1)),ref);
}

BOOL
cos_any_changeClass(OBJ _1, const struct Class *new)
{
  struct Any *obj = STATIC_CAST(struct Any*, _1);
  struct Class *cls = cos_class_get(obj->id);

  if (cls->isz != new->isz || !cos_class_isSubclassOf(cls,new))
    return NO;

  obj->id = new->Behavior.id;
  return YES;
}

BOOL
cos_any_unsafeChangeClass(OBJ _1, const struct Class *new,
                                  const struct Class *base)
{
  struct Any *obj = STATIC_CAST(struct Any*, _1);
  struct Class *cls = cos_class_get(obj->id);

  if (cls->isz < new->isz || !cos_class_isSubclassOf(cls,base)
                          || !cos_class_isSubclassOf(new,base))
    return NO;

  obj->id = new->Behavior.id;
  return YES;
}

// ----- method

IMP1
cos_method_get1(SEL gen, U32 id1)
{
  struct Method1 **mth = STATIC_CAST(struct Method1**, sym.mth)+gen->mth;
  struct Class *cls[1];
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i = 0;
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),0,0,0,0,0);

  cls[0] = cos_class_get(id1);

  for (; i < n_mth; i++)
    if (info >= mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, 1))
      return mth[i]->fct;

  return 0;
}

IMP2
cos_method_get2(SEL gen, U32 id1, U32 id2)
{
  struct Method2 **mth = STATIC_CAST(struct Method2**, sym.mth)+gen->mth;
  struct Class *cls[2];
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i = 0;
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),COS_ID_RNK(id2),0,0,0,0);

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);

  for (; i < n_mth; i++)
    if (info >= mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, 2))
      return mth[i]->fct;

  return 0;
}

IMP3
cos_method_get3(SEL gen, U32 id1, U32 id2, U32 id3)
{
  struct Method3 **mth = STATIC_CAST(struct Method3**, sym.mth)+gen->mth;
  struct Class *cls[3];
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i = 0;
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),
                          COS_ID_RNK(id2),
                          COS_ID_RNK(id3),0,0,0);

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);
  cls[2] = cos_class_get(id3);

  for (; i < n_mth; i++)
    if (info >= mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, 3))
      return mth[i]->fct;

  return 0;
}

IMP4
cos_method_get4(SEL gen, U32 id1, U32 id2, U32 id3, U32 id4)
{
  struct Method4 **mth = STATIC_CAST(struct Method4**, sym.mth)+gen->mth;
  struct Class *cls[4];
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i = 0;
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),
                          COS_ID_RNK(id2),
                          COS_ID_RNK(id3),
                          COS_ID_RNK(id4),0,0);

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);
  cls[2] = cos_class_get(id3);
  cls[3] = cos_class_get(id4);

  for (; i < n_mth; i++)
    if (info >= mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, 4))
      return mth[i]->fct;

  return 0;
}

IMP5
cos_method_get5(SEL gen, U32 id1, U32 id2, U32 id3, U32 id4, U32 id5)
{
  struct Method5 **mth = STATIC_CAST(struct Method5**, sym.mth)+gen->mth;
  struct Class *cls[5];
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i = 0;
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),
                          COS_ID_RNK(id2),
                          COS_ID_RNK(id3),
                          COS_ID_RNK(id4),
                          COS_ID_RNK(id5),0);

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);
  cls[2] = cos_class_get(id3);
  cls[3] = cos_class_get(id4);
  cls[4] = cos_class_get(id5);

  for (; i < n_mth; i++)
    if (info >= mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, 5))
      return mth[i]->fct;

  return 0;
}

char*
cos_method_name(const struct Method *mth, char *str, U32 sz)
{
  struct Class* const *cls = STATIC_CAST(const struct Method5*, mth)->cls;

  switch( COS_GEN_RNK(mth->gen) ) {
  case 1: snprintf(str, sz, "%s<%s>", mth->gen->name,
                   cls[0]->name); break;
  case 2: snprintf(str, sz, "%s<%s,%s>", mth->gen->name,
                   cls[0]->name, cls[1]->name); break;
  case 3: snprintf(str, sz, "%s<%s,%s,%s>", mth->gen->name,
                   cls[0]->name, cls[1]->name, cls[2]->name); break;
  case 4: snprintf(str, sz, "%s<%s,%s,%s,%s>", mth->gen->name,
                   cls[0]->name, cls[1]->name, cls[2]->name, cls[3]->name); break;
  case 5: snprintf(str, sz, "%s<%s,%s,%s,%s,%s>", mth->gen->name,
                   cls[0]->name, cls[1]->name, cls[2]->name, cls[3]->name, cls[4]->name); break;
  }
  
  return str;
}

char*
cos_method_call(SEL gen, OBJ obj[], char *str, U32 sz)
{
  switch( COS_GEN_RNK(gen) ) {
  case 1: snprintf(str, sz, "%s(%s)", gen->name,
                   cos_any_className(obj[0])); break;
  case 2: snprintf(str, sz, "%s(%s,%s)", gen->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1])); break;
  case 3: snprintf(str, sz, "%s(%s,%s,%s)", gen->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1]),
                   cos_any_className(obj[2])); break;
  case 4: snprintf(str, sz, "%s(%s,%s,%s,%s)", gen->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1]),
                   cos_any_className(obj[2]), cos_any_className(obj[3])); break;
  case 5: snprintf(str, sz, "%s(%s,%s,%s,%s,%s)", gen->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1]),
                   cos_any_className(obj[2]), cos_any_className(obj[3]),
                   cos_any_className(obj[4])); break;
  }
  
  return str;
}

char*
cos_method_callName(const struct Method *mth, OBJ obj[], char *str, U32 sz)
{
  struct Class* const *cls = STATIC_CAST(const struct Method5*, mth)->cls;

  switch( COS_GEN_RNK(mth->gen) ) {
  case 1: snprintf(str, sz, "%s<%s>(%s)", mth->gen->name,
                   cls[0]->name,
                   cos_any_className(obj[0])); break;
  case 2: snprintf(str, sz, "%s<%s,%s>(%s,%s)", mth->gen->name,
                   cls[0]->name, cls[1]->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1])); break;
  case 3: snprintf(str, sz, "%s<%s,%s,%s>(%s,%s,%s)", mth->gen->name,
                   cls[0]->name, cls[1]->name, cls[2]->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1]),
                   cos_any_className(obj[2])); break;
  case 4: snprintf(str, sz, "%s<%s,%s,%s,%s>(%s,%s,%s,%s)", mth->gen->name,
                   cls[0]->name, cls[1]->name, cls[2]->name, cls[3]->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1]),
                   cos_any_className(obj[2]), cos_any_className(obj[3])); break;
  case 5: snprintf(str, sz, "%s<%s,%s,%s,%s,%s>(%s,%s,%s,%s,%s)", mth->gen->name,
                   cls[0]->name, cls[1]->name, cls[2]->name, cls[3]->name, cls[4]->name,
                   cos_any_className(obj[0]), cos_any_className(obj[1]),
                   cos_any_className(obj[2]), cos_any_className(obj[3]),
                   cos_any_className(obj[4])); break;
  }
  
  return str;
}

/*
 * ----------------------------------------------------------------------------
 *  Threaded functions
 * ----------------------------------------------------------------------------
 */

#if COS_POSIX

#include <pthread.h>

static pthread_mutex_t nxt_lock = PTHREAD_MUTEX_INITIALIZER;

void
cos_method_nextInit(FUNC *fct, SEL gen, U32 rnk, struct Class* const* cls)
{
  pthread_mutex_lock(&nxt_lock);
  if (*fct == (FUNC)YES) nxt_init(fct,gen,rnk,cls);
  pthread_mutex_unlock(&nxt_lock);
}

void
cos_method_nextClear(void)
{
  pthread_mutex_lock(&nxt_lock);
  nxt_clear();
  pthread_mutex_unlock(&nxt_lock);
}

#else

void
cos_method_nextInit(FUNC *fct, SEL gen, U32 rnk, struct Class* const* cls)
{
  if (*fct == (FUNC)YES) nxt_init(fct,gen,rnk,cls);
}

void
cos_method_nextClear(void)
{
  nxt_clear();
}

#endif

/*
 * ----------------------------------------------------------------------------
 *  Debug functions
 * ----------------------------------------------------------------------------
 */

#include <cos/cos/debug.h>

static void
mth_trace(STR file, int line, BOOL enter, const struct Method *mth, OBJ *obj)
{
  char buf[128];
    
  if (enter)
    cos_logmsg(COS_LOGMSG_TRACE,file,line,"-> %s",cos_method_callName(mth,obj,buf,sizeof buf));
  else
    cos_logmsg(COS_LOGMSG_TRACE,file,line,"<- %s",cos_method_name    (mth,    buf,sizeof buf));
}

void (*cos_method_trace)(STR,int,BOOL,const struct Method*,OBJ*) = mth_trace;

void
cos_symbol_showSummary(FILE *fp)
{
  if (!fp) fp = stderr;

  fprintf(fp, "classes  : %4u\n"     , sym.n_cls);
  fprintf(fp, "generics : %4u\n"     , sym.n_gen);
  fprintf(fp, "methods  : %4u\n"     , sym.n_mth);
  fprintf(fp, "behaviors: %4u / %u\n", sym.n_cls*3+sym.n_gen, sym.msk+!!sym.msk);
}

void
cos_symbol_showClasses(FILE *fp)
{
  U32 i,j;

  if (!fp) fp = stderr;

  fprintf(fp, "classes  : %4u\n", sym.n_cls);

  for (i = 0; i < sym.n_cls; i++) {
    j = sym.cls[i]->Behavior.id & sym.msk;

    fprintf(fp, "cls[%3u] = %-40s : %-40s [%2u,%9u->%3u]%c\n",
            i,
            sym.cls[i]->name,
            sym.cls[i]->spr ? sym.cls[i]->spr->name : "NIL",
            COS_CLS_RNK(sym.cls[i]),
            COS_CLS_TAG(sym.cls[i]),
            j,
            (OBJ)sym.bhv[j] == (OBJ)sym.cls[i] ? '=' : 'x');
  }
}

void
cos_symbol_showGenerics(FILE *fp)
{
  U32 i,j;

  if (!fp) fp = stderr;

  fprintf(fp, "generics : %4u\n", sym.n_gen);

  for (i = 0; i < sym.n_gen; i++) {
    j = sym.gen[i]->Behavior.id & sym.msk;

    fprintf(fp, "gen[%3u] = %-40s (%3u,%3u,%2u,%c%c%c)"
            "                           [%2u,%9u->%3u]%c\n",
            i,
            sym.gen[i]->name,
            sym.gen[i]->mth,
            COS_GEN_NMTH(sym.gen[i]),
            COS_GEN_NARG(sym.gen[i]),
            COS_GEN_ORET(sym.gen[i]) ? 'o' :
            COS_GEN_VRET(sym.gen[i]) ? 'v' : '?',
            COS_GEN_OARG(sym.gen[i]) ? 'o' : '?',
            COS_GEN_VARG(sym.gen[i]) ? 'v' : 'g',
            COS_GEN_RNK(sym.gen[i]),
            COS_GEN_TAG(sym.gen[i]),
            j,
            (OBJ)sym.bhv[j] == (OBJ)sym.gen[i] ? '=' : 'x');
  }
}

void
cos_symbol_showMethods(FILE *fp)
{
  char buf[128];
  U32 i;

  if (!fp) fp = stderr;

  fprintf(fp,"methods  : %4u\n", sym.n_mth);

  for (i = 0; i < sym.n_mth; i++) {
    fprintf(fp,"mth[%3u] =", i);

    cos_method_name(sym.mth[i],buf,sizeof buf);
    fprintf(fp," %-83s", buf);

    fprintf(fp," (%3u,%2u,%2u,%2u,%2u,%2u)\n",
            COS_MTH_RNK(sym.mth[i]),
            COS_MTH_RK1(sym.mth[i]),
            COS_MTH_RK2(sym.mth[i]),
            COS_MTH_RK3(sym.mth[i]),
            COS_MTH_RK4(sym.mth[i]),
            COS_MTH_RK5(sym.mth[i]));
  }
}

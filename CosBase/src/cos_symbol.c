/**
 * C Object System
 * COS core
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
#include <cos/Class.h>
#include <cos/MetaClass.h>
#include <cos/Property.h>
#include <cos/Method.h>
#include <cos/gen/object.h>

#include <string.h>
#include <stdlib.h>
#include <time.h>

#if COS_HAS_POSIX && COS_HAS_DLINK
#include <dlfcn.h>
#include <stdio.h>
#endif

enum { MAX_TBL = 100 }; // maximum number of modules (& plug-in)

static U32          tbl_ini = 0; // index of first table not yet initialized
static struct Any **tbl_sym[MAX_TBL];
static void        *tbl_mod[MAX_TBL];
static STR          tbl_tag[MAX_TBL];

static struct {
  struct Behavior   **bhv; // indexed by id % msk
  struct Class      **cls; // sorted  by name
  struct Class      **prp; // sorted  by name
  struct Generic    **gen; // sorted  by name
  struct Method     **mth; // sorted  by gen-name,mth-rank,rnd-rank,cls-name
  struct MetaDocStr **doc; // sorted  by obj-type,obj-name,name
  FCT               **nxt; // not sorted
  U32 msk, n_cls, n_prp, n_gen, n_mth, n_doc, n_nxt, m_nxt;
} sym;

// forward decl
static void mod_clear(void);

// -- component name/location management

static inline STR
cls_file(const struct Class *cls)
{
  return cls->Behavior.Object.Any._rc == COS_RC_STATIC
    ?              cls->Behavior.file
    : *(const STR*)cls->Behavior.file;
}

static inline int
cls_line(const struct Class *cls)
{
  return cls->Behavior.line;
}

static inline STR
cls_name(const struct Class *cls)
{
  switch (cls->Behavior.Object.Any._rc) {
  case COS_RC_STATIC:
  case cos_tag_pclass:
    return cls->str;

  case cos_tag_class :
    return CAST(const struct Class*, cls->str)->str+2;

  case cos_tag_mclass:
    return CAST(const struct Class*, cls->cls->str)->str+1;

  default:
    return "unknown";
  }
}

static inline STR
gen_file(const struct Generic *gen)
{
  return gen->Behavior.Object.Any._rc == COS_RC_STATIC
    ?              gen->Behavior.file
    : *(const STR*)gen->Behavior.file;
}

static inline int
gen_line(const struct Generic *gen)
{
  return gen->Behavior.line;
}

static inline STR
gen_name(const struct Generic *gen)
{
  return gen->str;
}

// -- tag management

static inline U32
toPow2(U32 val)
{
  U32 i = 1;

  while (i < val)
    i *= 2;

  return i;
}

static inline U32
bhv_msk(U32 sz)
{
  return toPow2(sz)-1;
}

/* NOTE-INFO: COS_ID_INVALID

   COS_ID_INVALID appears only after 1371141289 iterations of the generator
   while only 134217727 ids are available (~10x less), before applying the mask.
   The limit of 10000000 static ids = 2500000 defclasses+defgeneric is far beyond
   any project size (and anyway it's easy to rise it).
*/

static inline U32
bhv_tag(void)
{
  static U32 x = 1;

  x = x * 2621124293u + 1;  // group generator for any \frac{\setN}{2^k\setN}, k=1..32

  if (x == COS_ID_TENMEGA) // keep the rest for dynamic behaviors (dynamic classes)
    cos_abort("too many static behaviors (>10000000)");

  return x & COS_ID_TAGMSK;  // use only the 27 lower bits (134217727 ids)
}

static void
bhv_setTag(struct Behavior *bhv)
{
  if (bhv->Object.Any._id) { // generics case
    struct Generic *gen = CAST(struct Generic*, bhv);

    if (bhv->id)
      cos_abort("generic '%s' at (%s,%d) has already an id",
                gen_name(gen), gen_file(gen), gen_line(gen));

    if ( (bhv->Object.Any._id & COS_ID_TAGMSK) )
      cos_abort("generic '%s' at (%s,%d) has invalid initialization",
                gen_name(gen), gen_file(gen), gen_line(gen));

    bhv->id = bhv->Object.Any._id | bhv_tag();
    bhv->Object.Any._id = 0;

  } else {              // classes case
    struct Class *cls = CAST(struct Class*, bhv);

    if (bhv->Object.Any._id)
      cos_abort("class '%s' at (%s,%d) has already an id",
                cls_name(cls), cls_file(cls), cls_line(cls));

    if ( (bhv->id & COS_ID_TAGMSK) )
      cos_abort("class '%s' at (%s,%u) has invalid initialization (multiple generics?)",
                cls_name(cls), cls_file(cls), cls_line(cls));

    bhv->id |= bhv_tag();
  }
}

// -- comparison

static int // qsort
cls_cmp(const void *_cls1, const void *_cls2)
{
  struct Class *cls1 = *(struct Class* const*)_cls1;
  struct Class *cls2 = *(struct Class* const*)_cls2;

  return strcmp(cls1->str, cls2->str);
}

static int // qsort
gen_cmp(const void *_gen1, const void *_gen2)
{
  struct Generic *gen1 = *(struct Generic* const*)_gen1;
  struct Generic *gen2 = *(struct Generic* const*)_gen2;

  return strcmp(gen1->str, gen2->str);
}

static int // qsort
mth_cmp(const void *_mth1, const void *_mth2)
{
  struct Method5 *mth1 = *(struct Method5* const*)_mth1;
  struct Method5 *mth2 = *(struct Method5* const*)_mth2;
  int i, n, res;

  // ascending generic name
  if (mth1->Method.gen != mth2->Method.gen)
    return strcmp(mth1->Method.gen->str, mth2->Method.gen->str);

  // descending method rank order
  if ((res = (mth1->Method.info < mth2->Method.info) -
             (mth1->Method.info > mth2->Method.info)))
    return res;

  // ascending classes name
  n = COS_GEN_RNK(mth1->Method.gen);
  
  for (i = 0; i < n; i++)
    if (mth1->cls[i] != mth2->cls[i])
      return strcmp(mth1->cls[i]->str, mth2->cls[i]->str);

  // descending around rank order
  return (mth1->Method.arnd < mth2->Method.arnd) -
         (mth1->Method.arnd > mth2->Method.arnd);
}

static int // qsort
doc_cmp(const void *_doc1, const void *_doc2)
{
  struct MetaDocStr *doc1 = *(struct MetaDocStr* const*)_doc1;
  struct MetaDocStr *doc2 = *(struct MetaDocStr* const*)_doc2;

  return doc1-doc2;
}

static int // qsort
cls_strcmp(const void *str, const void *_cls)
{
  struct Class *cls = *(struct Class* const*)_cls;

  return strcmp(str,cls->str);
}

static int // qsort
prp_strcmp(const void *str, const void *_prp)
{
  struct Class *prp = *(struct Class* const*)_prp;

  return strcmp(str,prp->str+2); // skip P_
}

static int // qsort
gen_strcmp(const void *str, const void *_gen)
{
  struct Generic *gen = *(struct Generic* const*)_gen;

  return strcmp(str,gen->str);
}

// -- predicates

static inline BOOL
cls_isSubOf(const struct Class *cls, const struct Class *ref)
{
  U32 ref_id = COS_ID_URK(cos_class_id(ref));
  
  // a class is a subclass of itself
  while (cos_class_id(cls) > ref_id)
    cls = cls->spr;

  return cls == ref;
}

static inline BOOL
cls_isMeta(const struct Class *cls)
{
  return cls->Behavior.Object.Any._id == classref(MetaClass)->Behavior.id;
}

static inline BOOL
cls_isPropMeta(const struct Class *cls)
{
  return cls->Behavior.Object.Any._id == classref(PropMetaClass)->Behavior.id;
}

static inline BOOL
cls_isMetaClass(const struct Class *cls)
{
  return cls_isMeta(cls) || cls_isPropMeta(cls);
}

static inline BOOL
cls_isClass(const struct Class *cls)
{
  return !cls_isMetaClass(cls);
}

static inline BOOL
cls_isProperty(const struct Class *cls)
{
  return cls_isSubOf(cls, classref(Property));
}

// -- component initialization (update from static)

static void
cls_stinit(struct Class *cls) { (void)cls; }

static void
pcl_stinit(struct Class *pcl) { (void)pcl; }

static void
mcl_stinit(struct Class *mcl) { (void)mcl; }

static void
gen_stinit(struct Generic *gen) { (void)gen; }

static void
als_stinit(struct Method1 *ali)
{
  // hack: retrieve aliased method stored in cls[0]
  struct Method1 *mth = CAST(struct Method1*, ali->cls[0]);
  
  if (mth->Method.Object.Any._rc == cos_tag_alias) { // alias of alias
    ali->Method.Object.Any._rc = cos_tag_invalid; // temporally invalid
    als_stinit(mth);
  }

  if (mth->Method.Object.Any._rc != cos_tag_method) // not alias of method
    cos_abort("invalid alias of '%s' at (%s,%d), cross reference between aliases?",
              gen_name(ali->Method.gen), ali->Method.file, ali->Method.line);
  
  ali->fct = mth->fct;
  ali->cls[0] = mth->cls[0];
  ali->Method.info = mth->Method.info;
  ali->Method.Object.Any._rc = cos_tag_method; // convert alias to method
}

// -- generics management

static inline void
gen_incMth(struct Generic *gen)
{
  if (COS_GEN_NMTH(gen) == COS_GEN_MTHMSK)
    cos_abort("too many specializations for generic '%s' at (%s,%d)",
              gen_name(gen), gen_file(gen), gen_line(gen));

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

  // missing generics
  if (n != sym.n_mth)
    cos_abort("incomplete or missing symbols table");
}

// -- properties management

static inline void
cls_setProp(void)
{
  struct Class **cls = sym.cls;
  U32 n = sym.n_cls;
  
  while (n && !cls_isProperty(*cls))
    --n, ++cls;

  sym.prp = cls;

  while (n &&  cls_isProperty(*cls))
    --n, ++cls;

  sym.n_prp = cls - sym.prp;
}

static inline U32
cls_encodeProp(U32 i, U32 n)
{
  // encoding: p = 0..2^4-1, n = 0..2^6-1, i = 0..2^22-1
  U32 p = 0;
  
  while (n >= (1 << 6))
    ++p, ++n, n /= 2;

  if (i > COS_GEN_MTHMSK || p >= (1 << 4))
    cos_abort("invalid class properties index and counts");

  return (p << 6 | n) << COS_GEN_MTHSHT | i;
}

static inline U32
cls_decodePropIdx(U32 prp)
{
  return prp & COS_GEN_MTHMSK;
}

static inline U32
cls_decodePropCnt(U32 prp, BOOL floor)
{
  // decoding: cnt = n * 2^p
  U32 n = prp >> COS_GEN_MTHSHT;
  U32 p = 0, r = 0;
  
  if (n >= (1 << 6)) {
    p  = (n >> 6);
    n &= (1 << 6) - 1;
    if (floor) r = (1 << p) - 1;
  }

  return (n << p) - r;
}

static U32
cls_classPropCnt(const struct Generic *gen, const struct Class *cls, I32 rnk)
{
  U32 n=0, p=0;
  I32 r = COS_CLS_RNK(cls);
  enum { get, put };

       if (gen == genericref(ggetAt)) p = get;
  else if (gen == genericref(gputAt)) p = put;
  else cos_abort("invalid generic '%s' at (%s,%d) for properties",
                 gen_name(gen), gen_file(gen), gen_line(gen));

  if ((U32)rnk > (U32)r) rnk = r;

  while (r >= rnk && cls_isMetaClass(cls))
    --r, cls = cls->spr;

  while (r >= rnk) {
    n += cls_decodePropCnt(cls->prp[p], NO);
    --r, cls = cls->spr;
  }

  return n;
}

static U32
cls_classPropLst(const struct Generic *gen,
                 const struct Class   *cls, I32 rnk,
                 const struct Class  **prp, U32 n_prp)
{
  struct Method5 **mth = CAST(struct Method5**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i=0, p=0;
  I32 r = COS_CLS_RNK(cls);
  enum { get, put };

       if (gen == genericref(ggetAt)) p = get;
  else if (gen == genericref(gputAt)) p = put;
  else cos_abort("invalid generic '%s' at (%s,%d) for properties",
                 gen_name(gen), gen_file(gen), gen_line(gen));

  if ((U32)rnk > (U32)r) rnk = r;

  while (r >= rnk && cls_isMetaClass(cls))
    --r, cls = cls->spr;

  while (r >= rnk) {
    if (cls->prp[p]) {
      U32 j = cls_decodePropIdx(cls->prp[p]);
      U32 n = cls_decodePropCnt(cls->prp[p], YES)+j;

      for (; i < n_prp && j < n    ; i++, j++)
        prp[i] = mth[j]->cls[1]->cls;

      for (; i < n_prp && j < n_mth; i++, j++) {
        if (cls !=          mth[j]->cls[0]  ||
           !cls_isMetaClass(mth[j]->cls[1]) || 
           !cls_isProperty (mth[j]->cls[1]->cls))
          break;

        prp[i] = mth[j]->cls[1]->cls;
      }
    }

    --r, cls = cls->spr;
  }

  return i;
}

static void
cls_setClassProp(const struct Generic *gen)
{
  struct Method5 **mth = CAST(struct Method5**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i, j, p=0;
  enum { get, put };

       if (gen == genericref(ggetAt)) p = get;
  else if (gen == genericref(gputAt)) p = put;
  else cos_abort("invalid generic '%s' at (%s,%d) for properties",
                 gen_name(gen), gen_file(gen), gen_line(gen));

  for (i = 0; i < n_mth;) {

    if (!cls_isMetaClass(mth[i]->cls[1]) ||
        !cls_isProperty (mth[i]->cls[1]->cls)) {
        ++i; continue;
    } 

    for (j = i++; i < n_mth; i++)
      if (mth[j]->cls[0] != mth[i]->cls[0]  ||
          !cls_isMetaClass (mth[i]->cls[1]) || 
          !cls_isProperty  (mth[i]->cls[1]->cls))
        break;

    mth[j]->cls[0]->prp[p] = cls_encodeProp(j, i-j);
  }
}

// -- next_method management

static inline void
nxt_enlarge(void)
{
  U32 m = sym.m_nxt < 128 ? 128 : sym.m_nxt*2;
  FCT **nxt = realloc(sym.nxt, m * sizeof *sym.nxt);

  if (!nxt)
    cos_abort("out of memory during next_method registration");

  sym.nxt = nxt;
  sym.m_nxt = m;
}

static inline void
nxt_add(FCT *fct)
{
  if (sym.n_nxt == sym.m_nxt)
    nxt_enlarge();

  sym.nxt[sym.n_nxt++] = fct;
}

static inline void
nxt_clear(void)
{
  while (sym.n_nxt)
    *sym.nxt[--sym.n_nxt] = (FCT)YES;
}

static inline BOOL
mth_isSubOf(struct Class* const*cls, struct Class* const* ref, U32 n)
{
  while (--n && cls_isSubOf(cls[n],ref[n])) ;

  return  !n && cls_isSubOf(cls[0],ref[0]);
}

static inline FCT
nxt_init(SEL gen, U32 info, U32 arnd, struct Class *const *cls)
{
  struct Method5 **mth = CAST(struct Method5**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 n_cls = COS_GEN_RNK (gen);
  enum { n = 5 };
  U32 i = 0;

  if (arnd) {
    for (; i < n_mth; i += n)
      if (info >= mth[i]->Method.info)
        break;

    if (i) i -= n-1;

    for (; i < n_mth; i++)
      if (arnd == mth[i]->Method.arnd)
        break;
        
    ++i;
  }
  else {
    for (; i < n_mth; i += n)
      if (info > mth[i]->Method.info)
        break;

    if (i) i -= n-1;
    
    for (; i < n_mth; i++)
      if (info > mth[i]->Method.info)
        break;
  }

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, n_cls))
      return (FCT)mth[i]->fct;

  return 0;
}

// -- memory management

static void
sym_prepStorage(U32 n_cls, U32 n_gen, U32 n_mth, U32 n_doc)
{
  U32 n_bhv, msk;

  if (n_cls) sym.cls = realloc(sym.cls, (n_cls+=sym.n_cls) * sizeof *sym.cls);
  if (n_gen) sym.gen = realloc(sym.gen, (n_gen+=sym.n_gen) * sizeof *sym.gen);
  if (n_mth) sym.mth = realloc(sym.mth, (n_mth+=sym.n_mth) * sizeof *sym.mth);
  if (n_doc) sym.doc = realloc(sym.doc, (n_doc+=sym.n_doc) * sizeof *sym.doc);

  if ((!sym.cls && n_cls) || (!sym.gen && n_gen) ||
      (!sym.mth && n_mth) || (!sym.doc && n_doc))
    cos_abort("out of memory during symbols registration");

  n_bhv = n_gen + 3*n_cls;

  if (n_bhv) {
    msk = bhv_msk(n_bhv);
    if (msk > sym.msk)
      bhv_enlarge(msk);
  }
}

// -- symbols management

static void
sym_init(void)
{
  static U32 arnd = 0;
  U32 n_cls=0, n_mcl=0, n_pcl=0, n_gen=0, n_mth=0, n_doc=0;
  U32 t, s;

  // count symbols
  for (t = tbl_ini; t < MAX_TBL && tbl_sym[t]; t++) {
    for (s = 0; tbl_sym[t][s]; s++) {

      // count symbols
      switch (tbl_sym[t][s]->_rc) {
      case cos_tag_class  : ++n_cls; cls_stinit((void*)tbl_sym[t][s]); break;
      case cos_tag_mclass : ++n_mcl; mcl_stinit((void*)tbl_sym[t][s]); break;
      case cos_tag_pclass : ++n_pcl; pcl_stinit((void*)tbl_sym[t][s]); break;
      case cos_tag_generic: ++n_gen; gen_stinit((void*)tbl_sym[t][s]); break;
      case cos_tag_alias  :          als_stinit((void*)tbl_sym[t][s]);
      case cos_tag_method : ++n_mth; break;
      case cos_tag_docstr : ++n_doc; break;
      default: cos_abort("invalid COS symbol");
      }

      // set behavior tag
      if (tbl_sym[t][s]->_rc & 0x1) {
        struct Behavior *bhv = CAST(struct Behavior*, tbl_sym[t][s]);
        bhv_setTag(bhv);
      }
    }
  }

  // check consistency between Class, MetaClass and PropMetaClass
  if (n_cls != n_mcl || n_cls != n_pcl)
    cos_abort("invalid number of (property) meta classes vs classes");

  // prepare storage for new symbols
  sym_prepStorage(n_cls,n_gen,n_mth,n_doc);

  // copy & prepare symbols
  for (t = tbl_ini; t < MAX_TBL && tbl_sym[t]; t++) {
    for (s = 0; tbl_sym[t][s]; s++) {

      // add behavior symbol to behavior table
      if (tbl_sym[t][s]->_rc & 0x1) {
        struct Behavior *bhv = CAST(struct Behavior*, tbl_sym[t][s]);
        U32 i = bhv->id & sym.msk;

        if (sym.bhv[i]) {
          switch (bhv->Object.Any._rc) {
          case cos_tag_class :
          case cos_tag_pclass:
          case cos_tag_mclass: {
            struct Class *cls = CAST(struct Class*, bhv);
            cos_abort("class '%s' at (%s,%d) slot %u already assigned",
                      cls_name(cls), cls_file(cls), cls_line(cls), i);
          }
          case cos_tag_generic: {
            struct Generic *gen = CAST(struct Generic*, bhv);
            cos_abort("generic '%s' at (%s,%d) slot %u already assigned",
                      gen_name(gen), gen_file(gen), gen_line(gen), i);
          }}
        }

        sym.bhv[i] = bhv;
      }

      // finalize symbol information and store it
      switch (tbl_sym[t][s]->_rc) {
      case cos_tag_class: {
        struct Class *cls = CAST(struct Class*, tbl_sym[t][s]);
        const struct Class *pcl = CAST(const struct Class*, cls->str);
        sym.cls[sym.n_cls++] = cls;             // hack: meta-link
        cls->str = pcl->str+2;                  // hack: name is shared
        cls->Behavior.file = cls_file(cls);     // hack: file is indirect
        cls->Behavior.Object.Any._id = cos_class_id(pcl);
        cls->Behavior.Object.Any._rc = COS_RC_STATIC;
      } break;

      case cos_tag_pclass: {
        struct Class *pcl = CAST(struct Class*, tbl_sym[t][s]);
        pcl->spr->str = pcl->str+1;             // hack: name is shared
        pcl->Behavior.file = cls_file(pcl);     // hack: file is indirect
        pcl->Behavior.Object.Any._id = cos_class_id(classref(PropMetaClass));
        pcl->Behavior.Object.Any._rc = COS_RC_STATIC;
      } break;

      case cos_tag_mclass: {
        struct Class *mcl = CAST(struct Class*, tbl_sym[t][s]);
        mcl->Behavior.file = cls_file(mcl);    // hack: file is indirect
        mcl->Behavior.Object.Any._id = cos_class_id(classref(MetaClass));
        mcl->Behavior.Object.Any._rc = COS_RC_STATIC;
      } break;

      case cos_tag_generic: {
        struct Generic *gen = CAST(struct Generic*, tbl_sym[t][s]);
        const struct Class *cls = CAST(const struct Class*, gen->sig);
        sym.gen[sym.n_gen++] = gen;
        gen->sig = gen->str + strlen(gen->str) + 1; // hack: sig follows name
        gen->Behavior.file = gen_file(gen);         // hack: file is indirect
        gen->Behavior.Object.Any._id = cos_class_id(cls);
        gen->Behavior.Object.Any._rc = COS_RC_STATIC;
      } break;

      case cos_tag_method: {
        struct Method *mth = CAST(struct Method*, tbl_sym[t][s]);
        gen_incMth(mth->gen);
        sym.mth[sym.n_mth++] = mth;
        mth->Object.Any._rc = COS_RC_STATIC;
        if (mth->arnd) mth->arnd = --arnd;
        switch (COS_GEN_RNK(mth->gen)) {
        case 1: mth->Object.Any._id = cos_class_id(classref(Method1)); break;
        case 2: mth->Object.Any._id = cos_class_id(classref(Method2)); break;
        case 3: mth->Object.Any._id = cos_class_id(classref(Method3)); break;
        case 4: mth->Object.Any._id = cos_class_id(classref(Method4)); break;
        case 5: mth->Object.Any._id = cos_class_id(classref(Method5)); break;
        }
      } break;
      
      case cos_tag_docstr: {
        struct MetaDocStr *doc = CAST(struct MetaDocStr*, tbl_sym[t][s]);
        sym.doc[sym.n_doc++] = doc;
        doc->Object.Any._id = cos_class_id(classref(MetaDocStr));
        doc->Object.Any._rc = COS_RC_STATIC;
      } break;
    }}
  }

  // sort symbols
  qsort(sym.cls, sym.n_cls, sizeof *sym.cls, cls_cmp);
  qsort(sym.gen, sym.n_gen, sizeof *sym.gen, gen_cmp);
  qsort(sym.mth, sym.n_mth, sizeof *sym.mth, mth_cmp);
  qsort(sym.doc, sym.n_doc, sizeof *sym.doc, doc_cmp);

  // set generics' methods indexes
  gen_setMth();

  // set property classes
  cls_setProp();

  // set class properties
  cls_setClassProp(genericref(ggetAt));
  cls_setClassProp(genericref(gputAt));
  
  // clear next-method
  nxt_clear();
  
  // end of module(s) init
  tbl_ini = t;
}

static void
sym_deinit(void)
{
  nxt_clear();
  mod_clear();

  if (sym.bhv) free(sym.bhv), sym.bhv = 0, sym.  msk = 0;
  if (sym.cls) free(sym.cls), sym.cls = 0, sym.n_cls = 0,
                              sym.prp = 0, sym.n_prp = 0;
  if (sym.gen) free(sym.gen), sym.gen = 0, sym.n_gen = 0;
  if (sym.mth) free(sym.mth), sym.mth = 0, sym.n_mth = 0;
  if (sym.doc) free(sym.doc), sym.doc = 0, sym.n_doc = 0;
  if (sym.nxt) free(sym.nxt), sym.nxt = 0, sym.n_nxt = 0, sym.m_nxt = 0;
  
  tbl_ini = 0;
}

// -- classes initialize

static void
cls_init(void)
{
  struct Generic *gen = genericref(ginitialize);
  struct Method1 **ini = CAST(struct Method1**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i;

  // invoke (prop)meta class ginitialize starting from super classes
  for (i = n_mth; i-- > 0; ) {
    struct Class *cls = ini[i]->cls[0];

    if (cls_isMetaClass(cls))
      ginitialize((OBJ)cls->cls);
  }
}

// -- classes deinitialize

static void
cls_deinit(void)
{
  struct Generic *gen = genericref(gdeinitialize);
  struct Method1 **dei = CAST(struct Method1**, sym.mth)+gen->mth;
  U32 n_mth = COS_GEN_NMTH(gen);
  U32 i;

  // invoke (prop)meta class gdeinitialize starting from subclasses
  for (i = 0; i < n_mth; i++) {
    struct Class *cls = dei[i]->cls[0];

    if (cls_isMetaClass(cls))
      gdeinitialize((OBJ)cls->cls);
  }
}

/*
 * ----------------------------------------------------------------------------
 *  Global Functions
 * ----------------------------------------------------------------------------
 */

// ----- general

static BOOL   init_done       = NO;
static double init_duration   = 0.0;
static double deinit_duration = 0.0;

void
cos_init(void)
{
  if (init_done == NO) {
    double t0, t1;

    init_done = YES;
    cos_symbol_init();

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
cos_symbol_register(struct Any* sym[], STR tag)
{
  U32 i;

  if (!sym)
    cos_abort("null symbol table");

  if (!tag || !*tag)
    cos_abort("null module/project name");

  for (i = 0; i < MAX_TBL && tbl_sym[i]; i++) {
    if (tbl_sym[i] == sym)
      return;
    if (!strcmp(tbl_tag[i], tag))
      cos_abort("module/project name already in use");
  }

  if (i == MAX_TBL)
    cos_abort("too many COS symbols tables registered (%u tables)", i);

  tbl_sym[i] = sym;
  tbl_tag[i] = tag;
}

// ----- generic

struct Generic*
cos_generic_get(U32 id)
{
  struct Generic *gen = CAST(struct Generic*, sym.bhv[id & sym.msk]);

  if (!gen || cos_generic_id(gen) != id)
    cos_abort("invalid generic id %d", id);

  return gen;
}

struct Generic*
cos_generic_getWithStr(STR str)
{
  struct Generic *gen;

  if (!str || !*str)
    cos_abort("null generic name");

  gen = bsearch(str, sym.gen, sym.n_gen, sizeof *sym.gen, gen_strcmp);

  return gen ? *(struct Generic**)gen : 0;
}

// ----- class

struct Class*
cos_class_get(U32 id)
{
  struct Class *cls = CAST(struct Class*, sym.bhv[id & sym.msk]);

  if (!COS_ID_TAG(id))
    cos_abort("invalid class id %d - dynamic object already destroyed or "
              "automatic object used *before* COS initialization", id);

  if (!cls || cos_class_id(cls) != id)
    cos_abort("invalid class id %d", id);

  return cls;
}

struct Class*
cos_class_getWithStr(STR str)
{
  struct Class *cls;
  STR p;

  if (!str || !*str)
    cos_abort("null class name");

  p = str + (str[0] == 'm') + (str[0] == 'p') + (str[1] == 'm');

  cls = bsearch(p, sym.cls, sym.n_cls, sizeof *sym.cls, cls_strcmp);

  if (!cls) return 0;
  
  cls = *(struct Class**)cls;

  switch (p-str) {
  case 0: // normal class
    ensure( cls_isClass(cls),
                 "classes not starting by 'm' or 'pm' should be instance of Class" );
    break;

  case 1: // meta class
    cls = cos_object_superClass((OBJ)cls);
    ensure( cls_isMeta(cls),
                 "class starting by 'm' should be instance of MetaClass" );
    break;

  case 2: // property meta class
    cls = cos_object_class((OBJ)cls);
    ensure( cls_isPropMeta(cls),
                 "class starting by 'pm' should be instance of PropMetaClass" );
    break;
  }

  return cls;
}

BOOL
cos_class_isSubclassOf(const struct Class *cls, const struct Class *ref)
{
  // TODO check ?
  return cls_isSubOf(cls, ref);
}

// ----- properties

struct Class*
cos_property_getWithStr(STR str)
{
  struct Class *prp;

  if (!str || !*str)
    cos_abort("null property name");

  prp = bsearch(str, sym.prp, sym.n_prp, sizeof *sym.prp, prp_strcmp);

  return prp ? *(struct Class**)prp : 0;
}

U32
cos_class_readProperties(const struct Class  *cls, U32 rnk,
                         const struct Class **prp, U32 n_prp)
{
  return prp
    ? cls_classPropLst(genericref(ggetAt),cls,rnk,prp,n_prp)
    : cls_classPropCnt(genericref(ggetAt),cls,rnk);
}

U32
cos_class_writeProperties(const struct Class  *cls, U32 rnk,
                          const struct Class **prp, U32 n_prp)
{
  return prp
    ? cls_classPropLst(genericref(gputAt),cls,rnk,prp,n_prp)
    : cls_classPropCnt(genericref(gputAt),cls,rnk);
}

// ----- object

BOOL
cos_object_isKindOf(OBJ _1, const struct Class *ref)
{
  return cls_isSubOf(cos_object_class(_1),ref);
}

BOOL
cos_object_changeClass(OBJ _1, const struct Class *new)
{
  struct Class *cls = cos_object_class(_1);

  if (!cls_isSubOf(cls,new))
    return NO;

  cos_object_setId(_1, cos_class_id(new));
  
  return YES;
}

BOOL
cos_object_unsafeChangeClass(OBJ _1, const struct Class *new,
                                     const struct Class *base)
{
  struct Class *cls = cos_object_class(_1);

  if (cls->isz < new->isz || !cls_isSubOf(cls,base) || !cls_isSubOf(new,base))
    return NO;

  cos_object_setId(_1, cos_class_id(new));
  
  return YES;
}

// ----- method

IMP1
cos_method_get1(SEL gen, U32 id1)
{
  struct Method1 **mth = CAST(struct Method1**, sym.mth)+gen->mth;
  struct Class *cls[1];
  U32 i, n_mth = COS_GEN_NMTH(gen);
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),0,0,0,0,0);
  enum { n = 5 };

  cls[0] = cos_class_get(id1);

  for (i = 0; i < n_mth; i += n)
    if (info >= mth[i]->Method.info)
      break;

  if (i)
  for (i -= n-1; i < n_mth; i++)
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
  struct Method2 **mth = CAST(struct Method2**, sym.mth)+gen->mth;
  struct Class *cls[2];
  U32 i, n_mth = COS_GEN_NMTH(gen);
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),COS_ID_RNK(id2),0,0,0,0);
  enum { n = 5 };

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);

  for (i = 0; i < n_mth; i += n)
    if (info >= mth[i]->Method.info)
      break;

  if (i)
  for (i -= n-1; i < n_mth; i++)
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
  struct Method3 **mth = CAST(struct Method3**, sym.mth)+gen->mth;
  struct Class *cls[3];
  U32 i, n_mth = COS_GEN_NMTH(gen);
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),
                          COS_ID_RNK(id2),
                          COS_ID_RNK(id3),0,0,0);
  enum { n = 5 };

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);
  cls[2] = cos_class_get(id3);

  for (i = 0; i < n_mth; i += n)
    if (info >= mth[i]->Method.info)
      break;

  if (i)
  for (i -= n-1; i < n_mth; i++)
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
  struct Method4 **mth = CAST(struct Method4**, sym.mth)+gen->mth;
  struct Class *cls[4];
  U32 i, n_mth = COS_GEN_NMTH(gen);
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),
                          COS_ID_RNK(id2),
                          COS_ID_RNK(id3),
                          COS_ID_RNK(id4),0,0);
  enum { n = 5 };

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);
  cls[2] = cos_class_get(id3);
  cls[3] = cos_class_get(id4);

  for (i = 0; i < n_mth; i += n)
    if (info >= mth[i]->Method.info)
      break;

  if (i)
  for (i -= n-1; i < n_mth; i++)
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
  struct Method5 **mth = CAST(struct Method5**, sym.mth)+gen->mth;
  struct Class *cls[5];
  U32 i, n_mth = COS_GEN_NMTH(gen);
  U32 info = COS_MTH_INFO(COS_ID_RNK(id1),
                          COS_ID_RNK(id2),
                          COS_ID_RNK(id3),
                          COS_ID_RNK(id4),
                          COS_ID_RNK(id5),0);
  enum { n = 5 };

  cls[0] = cos_class_get(id1);
  cls[1] = cos_class_get(id2);
  cls[2] = cos_class_get(id3);
  cls[3] = cos_class_get(id4);
  cls[4] = cos_class_get(id5);

  for (i = 0; i < n_mth; i += n)
    if (info >= mth[i]->Method.info)
      break;

  if (i)
  for (i -= n-1; i < n_mth; i++)
    if (info >= mth[i]->Method.info)
      break;

  for (; i < n_mth; i++)
    if (mth_isSubOf(cls, mth[i]->cls, 5))
      return mth[i]->fct;

  return 0;
}

/*
 * ----------------------------------------------------------------------------
 *  Threaded functions
 * ----------------------------------------------------------------------------
 */

// ----- next-method

#if COS_HAS_POSIX

#include <pthread.h>

static pthread_mutex_t nxt_lock = PTHREAD_MUTEX_INITIALIZER;

void
cos_method_nextInit(FCT *fct, SEL gen, U32 rnk, U32 rnd, struct Class* const* cls)
{
  pthread_mutex_lock(&nxt_lock);
  if (*fct == (FCT)YES) {
    *fct = nxt_init(gen,rnk,rnd,cls);
    nxt_add(fct);
  }
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
cos_method_nextInit(FCT *fct, SEL gen, U32 rnk, U32 rnd, struct Class* const* cls)
{
  *fct = nxt_init(gen,rnk,rnd,cls);
  nxt_add(fct);
}

void
cos_method_nextClear(void)
{
  nxt_clear();
}

#endif

// ----- module

#if COS_HAS_POSIX && COS_HAS_DLINK

static void
mod_clear(void)
{
  int i;

  for (i = 0; i < MAX_TBL && tbl_mod[i]; i++) {
    cos_trace("unloading module #%d", i);
    dlclose(tbl_mod[i]);
  }
}

void
cos_module_load(STR *mod)
{
  void (*symbol)(void);
  void  *handle;
  char   buf[256];
  STR    ext, err;
  int    i, j;

#if   defined(COS_DEBUG)
  ext = "_d";
#elif defined(COS_PROFILE)
  ext = "_p";
#else
  ext = "";
#endif

  if (!mod)
    cos_abort("null module table");

  if (!*mod)
    cos_abort("empty module table");

  for (j = 0; j < MAX_TBL && tbl_mod[j]; j++)
    ;

  for (i = 0; mod[i]; i++) {
    if (j == MAX_TBL)
      cos_abort("too many COS modules loaded (%u loaded)", j);

    if (!*mod[i])
      cos_abort("null module name");

    // load module
    sprintf(buf, COS_LIB_PREFIX "%200s%s" COS_LIB_SHEXT, ext, mod[i]);
    buf[sizeof(buf)-1] = 0;

    handle = dlopen(buf, RTLD_LAZY);
    if (!handle)
      cos_abort("unable to load module %s%s: %s", ext, mod[i], dlerror());

    // search registration service
    sprintf(buf, "cos_symbol_init%200s", mod[i]);
    buf[sizeof(buf)-1] = 0;
    
    { // avoid compiler warning on type-punning
      union { void (*fun)(void); void *sym; } alias;
      
      STATIC_ASSERT(function_ptr_are_incompatible_with_void_ptr,
        sizeof(void(*)(void)) == sizeof(alias) && sizeof(void*) == sizeof(alias));

      alias.sym = dlsym(handle, buf);
      symbol = alias.fun;
    }

    if ((err = dlerror()) != NULL)
      cos_abort("unable to initialize module %s: %s", mod[i], err);

    // register symbols
    symbol();
    tbl_mod[j] = handle;
  }

  // init loaded tables and classes
  if (init_done == NO)
    cos_init();
  else {
    double t0, t1;

    t0 = clock();
    sym_init();
    cls_init();
    t1 = clock();
    
    init_duration += (t1-t0)/CLOCKS_PER_SEC;
  }
}

#else

static void
mod_clear(void)
{
  COS_UNUSED(tbl_mod);
}

void
cos_module_load(STR *mod)
{
  if (!mod)
    cos_abort("null module table");

  if (!*mod)
    cos_abort("empty module table");

  cos_abort("dynamic linking loader not supported (module %s)", *mod);
}

#endif

/*
 * ----------------------------------------------------------------------------
 *  Debug functions
 * ----------------------------------------------------------------------------
 */

#include <cos/debug.h>

static inline char*
cpyStr(char *dst, char *end, const char *src)
{
  while (dst < end && *src)
    *dst++ = *src++;
    
  return dst;
}

static inline char*
cpyGenName(char *dst, char *end, const struct Method *mth)
{
  if (dst < end && mth->arnd) *dst++ = '(';

  dst = cpyStr(dst, end, mth->gen->str);
  
  if (dst < end && mth->arnd) *dst++ = ')';
  if (dst < end             ) *dst   =  0 ;

  return dst;
}

static inline char*
cpyClsName(char *dst, char *end, struct Class *const *cls, U32 ncls)
{
  U32 i;
  
  if (dst < end) *dst++ = '<';

  for (i = 0; i < ncls && dst < end; i++) {
    dst = cpyStr(dst, end, cls[i]->str);
    if (i < ncls-1 && dst < end) *dst++ = ',';
  }
  
  if (dst < end) *dst++ = '>';
  if (dst < end) *dst   =  0 ;

  return dst;
}

static inline char*
cpyObjClsName(char *dst, char *end, OBJ obj[], U32 nobj)
{
  U32 i;
  
  if (dst < end) *dst++ = '(';

  for (i = 0; i < nobj && dst < end; i++) {
    dst = cpyStr(dst, end, cos_object_className(obj[i]));
    if (i < nobj-1 && dst < end) *dst++ = ',';
  }

  if (dst < end) *dst++ = ')';
  if (dst < end) *dst   =  0 ;
  
  return dst;
}

char*
cos_method_name(const struct Method *mth, char *str, U32 sz)
{
  struct Class* const *cls = CAST(const struct Method5*, mth)->cls;
  U32  ncls = COS_GEN_RNK(mth->gen);
  char *end = str+sz;

  cpyClsName(cpyGenName(str,end,mth), end,cls,ncls);

  if (sz > 0) str[sz-1] = 0;
  
  return str;
}

char*
cos_method_call(SEL gen, OBJ obj[], char *str, U32 sz)
{
  U32  ncls = COS_GEN_RNK(gen);
  char *end = str+sz;

  cpyObjClsName(cpyStr(str,end,gen->str), end,obj,ncls);

  if (sz > 0) str[sz-1] = 0;

  return str;
}

char*
cos_method_callName(const struct Method *mth, OBJ obj[], char *str, U32 sz)
{
  struct Class* const *cls = CAST(const struct Method5*, mth)->cls;
  U32  ncls = COS_GEN_RNK(mth->gen);
  char *end = str+sz;

  cpyObjClsName(cpyClsName(cpyGenName(str,end,mth), end,cls,ncls), end,obj,ncls);

  if (sz > 0) str[sz-1] = 0;

  return str;
}

static void
mth_trace(STR file, int line, BOOL enter, const struct Method *mth, OBJ *obj)
{
  char buf[256];

  if (enter)
    cos_logmsg(COS_LOGMSG_TRALL,file,line,"-> %s",cos_method_callName(mth,obj,buf,sizeof buf));
  else
    cos_logmsg(COS_LOGMSG_TRALL,file,line,"<- %s",cos_method_name    (mth,    buf,sizeof buf));
}

void (*cos_method_trace)(STR,int,BOOL,const struct Method*,OBJ*) = mth_trace;

void
cos_symbol_showSummary(FILE *fp)
{
  if (!fp) fp = stderr;

  fprintf(fp, "classes   : %4u\n"     , sym.n_cls);
  fprintf(fp, "properties: %4u\n"     , sym.n_prp);
  fprintf(fp, "generics  : %4u\n"     , sym.n_gen);
  fprintf(fp, "methods   : %4u\n"     , sym.n_mth);
  fprintf(fp, "behaviors : %4u / %u\n", sym.n_cls*3+sym.n_gen, sym.msk+!!sym.msk);
}

void
cos_symbol_showClasses(FILE *fp)
{
  U32 i,j;

  if (!fp) fp = stderr;

  fprintf(fp, "classes   : %4u\n", sym.n_cls);

  for (i = 0; i < sym.n_cls; i++) {
    j = sym.cls[i]->Behavior.id & sym.msk;

    fprintf(fp, "cls[%3u] = %-40s : %-40s [%2u,%9u->%3u]%c\n",
            i,
            sym.cls[i]->str,
            sym.cls[i]->spr ? sym.cls[i]->spr->str : "-",
            COS_CLS_RNK(sym.cls[i]),
            COS_CLS_TAG(sym.cls[i]),
            j,
            (OBJ)sym.bhv[j] == (OBJ)sym.cls[i] ? '=' : 'x');
  }
}

void
cos_symbol_showProperties(FILE *fp)
{
  U32 i,j;

  if (!fp) fp = stderr;

  fprintf(fp, "properties: %4u\n", sym.n_prp);

  for (i = 0; i < sym.n_prp; i++) {
    j = sym.prp[i]->Behavior.id & sym.msk;

    fprintf(fp, "prp[%3u] = %-40s : %-40s [%2u,%9u->%3u]%c\n",
            i,
            sym.prp[i]->str+2,
            sym.prp[i]->spr ? sym.prp[i]->spr->str : "NIL",
            COS_CLS_RNK(sym.prp[i]),
            COS_CLS_TAG(sym.prp[i]),
            j,
            (OBJ)sym.bhv[j] == (OBJ)sym.prp[i] ? '=' : 'x');
  }
}

void
cos_symbol_showClassProperties(FILE *fp, int spr)
{
  const struct Class *r_prp[256];
  const struct Class *w_prp[256];
  U32 i, j, k, r, w, n_prp = COS_ARRLEN(r_prp);
  enum { get, put };

  if (!fp) fp = stderr;

  fprintf(fp, "classes properties:\n");

  for (i = 0; i < sym.n_cls; i++) {
    if (!sym.cls[i]->cls) continue;
    
    k = spr ? 0 : COS_CLS_RNK(sym.cls[i]);
    r = cos_class_readProperties (sym.cls[i],k,r_prp,n_prp);
    w = cos_class_writeProperties(sym.cls[i],k,w_prp,n_prp);

    fprintf(fp, "cls[%3u] = %-25s (%5u,%3u) / (%5u,%3u)\n",
            i,
            sym.cls[i]->str,
            cls_decodePropIdx(sym.cls[i]->prp[get]), r,
            cls_decodePropIdx(sym.cls[i]->prp[put]), w);

    for (j = 0; j < r || j < w; j++)
      fprintf(fp, "           prp[%3u] : %-26s / %-26s\n",
              j,
              j >= r ? "-" : r_prp[j]->str+2,
              j >= w ? "-" : w_prp[j]->str+2);
  }
}

void
cos_symbol_showGenerics(FILE *fp)
{
  U32 i,j;

  if (!fp) fp = stderr;

  fprintf(fp, "generics  : %4u\n", sym.n_gen);

  for (i = 0; i < sym.n_gen; i++) {
    j = sym.gen[i]->Behavior.id & sym.msk;

    fprintf(fp, "gen[%3u] = %-40s (%5u,%5u,%2u,%c%c%c)"
            "                       [%2u,%9u->%3u]%c\n",
            i,
            sym.gen[i]->str,
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

  fprintf(fp,"methods   : %4u\n", sym.n_mth);

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

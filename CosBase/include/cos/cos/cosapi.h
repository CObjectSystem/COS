#ifndef COS_COS_COSAPI_H
#define COS_COS_COSAPI_H

/**
 * C Object System
 * COS api
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
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosapi.h>"
#endif

// low-level API

void   cos_init(void);
void   cos_deinit(void);
double cos_initDuration(void);   // in second.
double cos_deinitDuration(void); // in second.

BOOL cos_object_isKindOf(OBJ,const struct Class*);
BOOL cos_object_changeClass(OBJ,const struct Class*);
BOOL cos_object_unsafeChangeClass(OBJ,const struct Class*,const struct Class*);

struct Generic* cos_generic_get(U32);
struct Generic* cos_generic_getWithStr(STR);
struct Class*   cos_class_get(U32);
struct Class*   cos_class_getWithStr(STR);
struct Class*   cos_property_getWithStr(STR);

BOOL cos_class_isSubclassOf   (const struct Class*,    const struct Class*);
U32  cos_class_readProperties (const struct Class*,U32,const struct Class**,U32);
U32  cos_class_writeProperties(const struct Class*,U32,const struct Class**,U32);

IMP1   cos_method_get1(SEL,U32);
IMP2   cos_method_get2(SEL,U32,U32);
IMP3   cos_method_get3(SEL,U32,U32,U32);
IMP4   cos_method_get4(SEL,U32,U32,U32,U32);
IMP5   cos_method_get5(SEL,U32,U32,U32,U32,U32);
IMP1   cos_method_lookup1(SEL,U32);
IMP2   cos_method_lookup2(SEL,U32,U32);
IMP3   cos_method_lookup3(SEL,U32,U32,U32);
IMP4   cos_method_lookup4(SEL,U32,U32,U32,U32);
IMP5   cos_method_lookup5(SEL,U32,U32,U32,U32,U32);
/* inlined functions (see cos/cos/dispatch.h)
IMP1   cos_method_fastLookup1(SEL,U32);
IMP2   cos_method_fastLookup2(SEL,U32,U32);
IMP3   cos_method_fastLookup3(SEL,U32,U32,U32);
IMP4   cos_method_fastLookup4(SEL,U32,U32,U32,U32);
IMP5   cos_method_fastLookup5(SEL,U32,U32,U32,U32,U32);
BOOL   cos_method_understand1(SEL,U32);
BOOL   cos_method_understand2(SEL,U32,U32);
BOOL   cos_method_understand3(SEL,U32,U32,U32);
BOOL   cos_method_understand4(SEL,U32,U32,U32,U32);
BOOL   cos_method_understand5(SEL,U32,U32,U32,U32,U32);
*/
char*  cos_method_name(const struct Method*,char*,U32);
char*  cos_method_call(SEL,OBJ*,char*,U32);
char*  cos_method_callName(const struct Method*,OBJ*,char*,U32);
void (*cos_method_trace)(STR,int,BOOL,const struct Method*,OBJ*);
void   cos_method_clearCache1(void);
void   cos_method_clearCache2(void);
void   cos_method_clearCache3(void);
void   cos_method_clearCache4(void);
void   cos_method_clearCache5(void);
void   cos_method_clearCaches(void);

void   cos_contract_invariant1(OBJ,STR,int);
void   cos_contract_invariant2(OBJ,OBJ,STR,int);
void   cos_contract_invariant3(OBJ,OBJ,OBJ,STR,int);
void   cos_contract_invariant4(OBJ,OBJ,OBJ,OBJ,STR,int);
void   cos_contract_invariant5(OBJ,OBJ,OBJ,OBJ,OBJ,STR,int);
int    cos_contract_setLevel  (int lvl); // return previous level

void   cos_exception_assert (STR,STR,int) __attribute__((__noreturn__));
void   cos_exception_errno  (int,STR,int) __attribute__((__noreturn__));
void   cos_exception_badcast(OBJ,const struct Class*,STR,int)
                                          __attribute__((__noreturn__));
void   cos_exception_throw  (OBJ,STR,int) __attribute__((__noreturn__));
BOOL   cos_exception_catch  (OBJ,OBJ);
BOOL   cos_exception_uncaught(void);
void   cos_exception_initContext(struct cos_exception_context*);
void   cos_exception_deinitContext(struct cos_exception_context*);

cos_exception_handler cos_exception_setTerminate(cos_exception_handler);

void   cos_functor_overflow(void);
void   cos_functor_underflow(void) __attribute__((__noreturn__));
void   cos_functor_clearContext(void);

void   cos_module_load(STR*); // null terminated array of module names

/* NOTE-INFO: loggers
   - prototype: void cos_xxx(STR fmt, ...);
   - a '\n' is automatically added to the end
   - they can be turned on/off with cos_logmsg_set.
   - all these handlers display on cos_logmsg_out [default=stderr]
   - to access to cos_logmsg_out, you must include cos/cos/debug.h
*/
#define cos_trace(...) \
        cos_logmsg(COS_LOGMSG_TRACE,__FILE__,__LINE__,__VA_ARGS__)

#define cos_debug(...) \
        cos_logmsg(COS_LOGMSG_DEBUG,__FILE__,__LINE__,__VA_ARGS__)

#define cos_info(...) \
        cos_logmsg(COS_LOGMSG_INFO ,__FILE__,__LINE__,__VA_ARGS__)

#define cos_warn( ...) \
        cos_logmsg(COS_LOGMSG_WARN ,__FILE__,__LINE__,__VA_ARGS__)

#define cos_error(...) \
        cos_logmsg(COS_LOGMSG_ERROR,__FILE__,__LINE__,__VA_ARGS__)

#define cos_abort(...) \
        cos_logmsg(COS_LOGMSG_ABORT,__FILE__,__LINE__,__VA_ARGS__)

#define cos_logmsg(lvl,file,line,...) \
((void)(cos_logmsg_level_ <= (lvl) && (cos_logmsg_(lvl,file,line,__VA_ARGS__),0)))

// topic-specific debug
#define COS_DEBUG_IF(topic,...) \
        ((void)(COS_PP_CAT(DEBUG_,topic) && (cos_debug(__VA_ARGS__),0)))

void cos_logmsg_(int,STR,int,STR,...) __attribute__((__format__(__printf__,4,5)));
int  cos_logmsg_setLevel(int lvl); // return previous level

/* NOTE-INFO: auto ctor
   the following function-like macro is useful to define automatic ctor
   for classes deriving from Object (or at equivalent level)
*/
#define cos_object_auto(cls) \
  {{ COS_CLS_NAME(cls).Behavior.id, COS_RC_AUTO }}

/***********************************************************
 * Implementation
 */

// COS symbols init
void cos_symbol_init(void);
void cos_symbol_register(struct Any**, STR tag);

// next-method
void cos_method_nextClear(void);
void cos_method_nextInit(FCT*,SEL,U32,U32,struct Class* const*);

// 2nd and 3rd levels dispatch
IMP1 cos_method_fastLookup1_(struct cos_method_slot1*restrict*restrict,SEL,U32);
IMP2 cos_method_fastLookup2_(struct cos_method_slot2*restrict*restrict,SEL,U32,U32);
IMP3 cos_method_fastLookup3_(struct cos_method_slot3*restrict*restrict,SEL,U32,U32,U32);
IMP4 cos_method_fastLookup4_(struct cos_method_slot4*restrict*restrict,SEL,U32,U32,U32,U32);
IMP5 cos_method_fastLookup5_(struct cos_method_slot5*restrict*restrict,SEL,U32,U32,U32,U32,U32);

BOOL cos_method_understand1_(struct cos_method_slot1*restrict*restrict,SEL,U32);
BOOL cos_method_understand2_(struct cos_method_slot2*restrict*restrict,SEL,U32,U32);
BOOL cos_method_understand3_(struct cos_method_slot3*restrict*restrict,SEL,U32,U32,U32);
BOOL cos_method_understand4_(struct cos_method_slot4*restrict*restrict,SEL,U32,U32,U32,U32);
BOOL cos_method_understand5_(struct cos_method_slot5*restrict*restrict,SEL,U32,U32,U32,U32,U32);

// logger message level (not thread safe)
extern int cos_logmsg_level_;

/***********************************************************
 * Inlined functions
 */

#if defined(_OPENMP) || COS_HAS_TLS || !COS_HAS_POSIX // --------------------

#ifdef _OPENMP
#include <omp.h>
#endif

static cos_inline struct cos_functor_context*
cos_functor_context(void)
{
  extern __thread struct cos_functor_context cos_functor_context_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_functor_context_)
#endif
  return &cos_functor_context_;
  COS_UNUSED(cos_functor_context);
}

static cos_inline struct cos_method_cache1*
cos_method_cache1(void)
{
  extern __thread struct cos_method_cache1 cos_method_cache1_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_method_cache1_)
#endif
  return &cos_method_cache1_;
  COS_UNUSED(cos_method_cache1);
}

static cos_inline struct cos_method_cache2*
cos_method_cache2(void)
{
  extern __thread struct cos_method_cache2 cos_method_cache2_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_method_cache2_)
#endif
  return &cos_method_cache2_;
  COS_UNUSED(cos_method_cache2);
}

static cos_inline struct cos_method_cache3*
cos_method_cache3(void)
{
  extern __thread struct cos_method_cache3 cos_method_cache3_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_method_cache3_)
#endif
  return &cos_method_cache3_;
  COS_UNUSED(cos_method_cache3);
}

static cos_inline struct cos_method_cache4*
cos_method_cache4(void)
{
  extern __thread struct cos_method_cache4 cos_method_cache4_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_method_cache4_)
#endif
  return &cos_method_cache4_;
  COS_UNUSED(cos_method_cache4);
}

static cos_inline struct cos_method_cache5*
cos_method_cache5(void)
{
  extern __thread struct cos_method_cache5 cos_method_cache5_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_method_cache5_)
#endif
  return &cos_method_cache5_;
  COS_UNUSED(cos_method_cache5);
}

static cos_inline struct cos_exception_context*
cos_exception_context(void)
{
  extern __thread struct cos_exception_context *cos_exception_cxt_;
#ifdef _OPENMP
#pragma omp threadprivate(cos_exception_cxt_)
#endif
  return cos_exception_cxt_;
  COS_UNUSED(cos_exception_context);
}

#else // !defined(_OPENMP) && !COS_HAS_TLS && COS_HAS_POSIX -----------------

#if COS_HAS_POSIX
#include <pthread.h>
#endif

struct cos_exception_context* cos_exception_context   (void);
struct cos_functor_context*   cos_functor_context_init(void);
struct cos_method_cache1*     cos_method_cache1_init  (void);
struct cos_method_cache2*     cos_method_cache2_init  (void);
struct cos_method_cache3*     cos_method_cache3_init  (void);
struct cos_method_cache4*     cos_method_cache4_init  (void);
struct cos_method_cache5*     cos_method_cache5_init  (void);

static cos_inline struct cos_functor_context*
cos_functor_context(void)
{
  struct cos_functor_context *context;
  extern int cos_functor_context_key_init;
  extern pthread_key_t cos_functor_context_key;
  
  if (! cos_functor_context_key_init ||
      !(context = pthread_getspecific(cos_functor_context_key)))
    context = cos_functor_context_init();

  return context;
  COS_UNUSED(cos_functor_context);
}

static cos_inline struct cos_method_cache1*
cos_method_cache1(void)
{
  struct cos_method_cache1 *cache;
  extern int cos_method_cache1_key_init;
  extern pthread_key_t cos_method_cache1_key;

  if (! cos_method_cache1_key_init ||
      !(cache = pthread_getspecific(cos_method_cache1_key)))
    cache = cos_method_cache1_init();

  return cache;
  COS_UNUSED(cos_method_cache1);
}

static cos_inline struct cos_method_cache2*
cos_method_cache2(void)
{
  struct cos_method_cache2 *cache;
  extern int cos_method_cache2_key_init;
  extern pthread_key_t cos_method_cache2_key;
  
  if (! cos_method_cache2_key_init ||
      !(cache = pthread_getspecific(cos_method_cache2_key)))
    cache = cos_method_cache2_init();

  return cache;
  COS_UNUSED(cos_method_cache2);
}

static cos_inline struct cos_method_cache3*
cos_method_cache3(void)
{
  struct cos_method_cache3 *cache;
  extern int cos_method_cache3_key_init;
  extern pthread_key_t cos_method_cache3_key;

  if (! cos_method_cache3_key_init ||
      !(cache = pthread_getspecific(cos_method_cache3_key)))
    cache = cos_method_cache3_init();

  return cache;
  COS_UNUSED(cos_method_cache3);
}

static cos_inline struct cos_method_cache4*
cos_method_cache4(void)
{
  struct cos_method_cache4 *cache;
  extern int cos_method_cache4_key_init;
  extern pthread_key_t cos_method_cache4_key;
  
  if (! cos_method_cache4_key_init ||
      !(cache = pthread_getspecific(cos_method_cache4_key)))
    cache = cos_method_cache4_init();

  return cache;
  COS_UNUSED(cos_method_cache4);
}

static cos_inline struct cos_method_cache5*
cos_method_cache5(void)
{
  struct cos_method_cache5 *cache;
  extern int cos_method_cache5_key_init;
  extern pthread_key_t cos_method_cache5_key;

  if (! cos_method_cache5_key_init ||
      !(cache = pthread_getspecific(cos_method_cache5_key)))
    cache = cos_method_cache5_init();

  return cache;
  COS_UNUSED(cos_method_cache5);
}

#endif // ------------------------------------------------

static cos_inline OBJ
cos_ident(OBJ obj)
{
  return obj;
  COS_UNUSED(cos_ident);
}

static cos_inline U32
cos_object_id(OBJ obj)
{
  return ((struct Any*)obj)->_id;
  COS_UNUSED(cos_object_id);
}

static cos_inline OBJ
cos_object_setId(OBJ obj, U32 id)
{
  return ((struct Any*)obj)->_id = id, obj;
  COS_UNUSED(cos_object_setId);
}

static cos_inline OBJ
cos_object_setIdAuto(OBJ res, OBJ obj)
{
  ((struct Any*)res)->_id = ((struct Any*)obj)->_id;
  ((struct Any*)res)->_rc = COS_RC_AUTO;
  return res;
  COS_UNUSED(cos_object_setIdAuto);
}

static cos_inline I32
cos_object_rc(OBJ obj)
{
  return ((struct Any*)obj)->_rc;
  COS_UNUSED(cos_object_rc);
}

static cos_inline OBJ
cos_object_setRc(OBJ obj, I32 rc)
{
  return ((struct Any*)obj)->_rc = rc, obj;
  COS_UNUSED(cos_object_setRc);
}

static cos_inline OBJ
cos_object_incRc(OBJ obj)
{
  return ((struct Any*)obj)->_rc++, obj;
  COS_UNUSED(cos_object_incRc);
}

static cos_inline OBJ
cos_object_decRc(OBJ obj)
{
  return ((struct Any*)obj)->_rc--, obj;
  COS_UNUSED(cos_object_decRc);
}

static cos_inline struct Class*
cos_object_class(OBJ obj)
{
  return cos_class_get(cos_object_id(obj));
  COS_UNUSED(cos_object_class);
}

static cos_inline struct Class*
cos_object_superClass(OBJ obj)
{
  return cos_object_class(obj)->spr;
  COS_UNUSED(cos_object_superClass);
}

static cos_inline STR
cos_object_className(OBJ obj)
{
  return cos_object_class(obj)->str;
  COS_UNUSED(cos_object_className);
}

static cos_inline U32
cos_class_id(const struct Class *cls)
{
  return cls->Behavior.id;
  COS_UNUSED(cos_class_id);
}

static cos_inline U32
cos_generic_id(SEL sel)
{
  return sel->Behavior.id;
  COS_UNUSED(cos_generic_id);
}

static cos_inline BOOL
cos_object_isa(OBJ obj, const struct Class *cls)
{
  return cos_object_id(obj) == cos_class_id(cls);
  COS_UNUSED(cos_object_isa);
}

static cos_inline void*
cos_object_cast(OBJ obj, const struct Class *cls)
{
  return obj && cos_object_isa(obj, cls) ? obj : 0;
  COS_UNUSED(cos_object_cast);
}

static cos_inline void*
cos_object_ecast(OBJ obj, const struct Class *cls, STR file, int line)
{
  if (obj && cos_object_isa(obj, cls))
    return obj;

  cos_exception_badcast(obj, cls, file, line);
  COS_UNUSED(cos_object_ecast);
}

static cos_inline void*
cos_object_dyncast(OBJ obj, const struct Class *cls)
{
  return obj && (cos_object_isa(obj, cls) || cos_object_isKindOf(obj, cls)) ? obj : 0;

  COS_UNUSED(cos_object_dyncast);
}

static cos_inline void*
cos_object_edyncast(OBJ obj, const struct Class *cls, STR file, int line)
{
  if (obj && (
      cos_object_isa     (obj, cls) ||
      cos_object_isKindOf(obj, cls)))
    return obj;

  cos_exception_badcast(obj, cls, file, line);
  COS_UNUSED(cos_object_edyncast);
}

static cos_inline BOOL
cos_arginfo_isObject(struct cos_generic_arginfo *info)
{
  return !info->size;
  COS_UNUSED(cos_arginfo_isObject);
}

static cos_inline U32
cos_arginfo_size(struct cos_generic_arginfo *info)
{
  return info->size ? info->size : sizeof(OBJ);
  COS_UNUSED(cos_arginfo_size);
}

static cos_inline struct cos_functor_context*
cos_functor_ensure(int n)
{
  struct cos_functor_context *cxt = cos_functor_context();
  
  if (cxt->top + n > cxt->end)
    cos_functor_overflow();

  return cxt;
  COS_UNUSED(cos_functor_ensure);
}

static cos_inline struct cos_functor_context*
cos_functor_require(int n)
{
  struct cos_functor_context *cxt = cos_functor_context();
  
  if (cxt->stk + n > cxt->top)
    cos_functor_underflow();

  return cxt;
  COS_UNUSED(cos_functor_require);
}

static cos_inline struct cos_exception_protect
cos_exception_protect(struct cos_exception_protect *ptr, OBJ const *obj)
{
  struct cos_exception_context *cxt = cos_exception_context();

  ptr->prv = cxt->stk;
  ptr->obj = obj;
  cxt->stk = ptr;

  return *ptr;
  COS_UNUSED(cos_exception_protect);
}

static cos_inline struct cos_exception_extendedProtect
cos_exception_objectProtect(struct cos_exception_extendedProtect *ptr,
                            OBJ const *alt, FCT1 fct)
{
  struct cos_exception_context *cxt = cos_exception_context();

  ptr->prv = cxt->stk;
  ptr->obj = (OBJ*)COS_YES;
  ptr->alt = (void *const*)alt;
  ptr->fct = (FCTV)fct;
  cxt->stk = (void*)ptr;

  return *ptr;
  COS_UNUSED(cos_exception_objectProtect);
}

static cos_inline struct cos_exception_extendedProtect
cos_exception_extendedProtect(struct cos_exception_extendedProtect *ptr,
                              void *const *alt, FCTV fct)
{
  struct cos_exception_context *cxt = cos_exception_context();

  ptr->prv = cxt->stk;
  ptr->obj = (OBJ*)COS_YES;
  ptr->alt = alt;
  ptr->fct = fct;
  cxt->stk = (void*)ptr;

  return *ptr;
  COS_UNUSED(cos_exception_extendedProtect);
}

#endif // COS_COS_COSAPI_H

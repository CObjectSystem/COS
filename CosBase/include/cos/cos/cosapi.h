#ifndef COS_COS_COSAPI_H
#define COS_COS_COSAPI_H

/*
 o---------------------------------------------------------------------o
 |
 | COS api
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
 | $Id: cosapi.h,v 1.48 2010/05/20 15:48:16 ldeniau Exp $
 |
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

void   cos_contract_invariant1(OBJ,STR,STR,int);
void   cos_contract_invariant2(OBJ,OBJ,STR,STR,int);
void   cos_contract_invariant3(OBJ,OBJ,OBJ,STR,STR,int);
void   cos_contract_invariant4(OBJ,OBJ,OBJ,OBJ,STR,STR,int);
void   cos_contract_invariant5(OBJ,OBJ,OBJ,OBJ,OBJ,STR,STR,int);
int    cos_contract_setLevel  (int lvl); // return previous level

void   cos_exception_assert (STR,STR,STR,int)  __attribute__((__noreturn__));
void   cos_exception_errno  (int,STR,STR,int)  __attribute__((__noreturn__));
void   cos_exception_badcast(OBJ,const struct Class*,STR,STR,int)
                                               __attribute__((__noreturn__));
void   cos_exception_throw  (OBJ,STR,STR,int)  __attribute__((__noreturn__));
BOOL   cos_exception_catch  (OBJ,OBJ);
BOOL   cos_exception_uncaught(void);
void   cos_exception_initContext(struct cos_exception_context*);
void   cos_exception_deinitContext(struct cos_exception_context*);

cos_exception_handler cos_exception_setTerminate(cos_exception_handler);

void   cos_module_load(STR*); // null terminated array of module names

/* NOTE-INFO: loggers
   - prototype: void cos_xxx(STR fmt, ...);
   - a '\n' is automatically added to the end
   - they can be turned on/off with cos_logmsg_set.
   - all these handlers display on cos_logmsg_out [default=stderr]
   - to access to cos_logmsg_out, you must include cos/cos/debug.h
*/
#define cos_trace(...) \
        cos_logmsg(COS_LOGMSG_TRACE,__FUNC__,__FILE__,__LINE__,__VA_ARGS__)

#define cos_debug(...) \
        cos_logmsg(COS_LOGMSG_DEBUG,__FUNC__,__FILE__,__LINE__,__VA_ARGS__)

#define cos_info(...) \
        cos_logmsg(COS_LOGMSG_INFO ,__FUNC__,__FILE__,__LINE__,__VA_ARGS__)

#define cos_warn( ...) \
        cos_logmsg(COS_LOGMSG_WARN ,__FUNC__,__FILE__,__LINE__,__VA_ARGS__)

#define cos_error(...) \
        cos_logmsg(COS_LOGMSG_ERROR,__FUNC__,__FILE__,__LINE__,__VA_ARGS__)

#define cos_abort(...) \
        cos_logmsg(COS_LOGMSG_ABORT,__FUNC__,__FILE__,__LINE__,__VA_ARGS__)

#define cos_logmsg(lvl,func,file,line,...) \
((void)(cos_logmsg_level_ <= (lvl) && (cos_logmsg_(lvl,func,file,line,__VA_ARGS__),0)))

void cos_logmsg_(int,STR,STR,int,STR,...) __attribute__((__format__(__printf__,5,6)));
int  cos_logmsg_setLevel(int lvl); // return previous level

/* NOTE-INFO: memory tracer
*/
void* cos_mem_malloc (size_t, STR,STR,int);
void* cos_mem_calloc (size_t, size_t, STR,STR,int);
void* cos_mem_realloc(void*, size_t, STR,STR,int);
void  cos_mem_free   (void*, STR,STR,int);
BOOL  cos_mem_trace  (BOOL); // on/off memory trace
U32   cos_mem_nalloc (void); // number of alloc modulo 2^32
U32   cos_mem_nfree  (void); // number of free  modulo 2^32

#ifndef COS_NOTRACEMEM
#if COS_LOGMSG <= COS_LOGMSG_DEBUG

#undef  malloc
#define malloc(s)    cos_mem_malloc (s  , __FUNC__, __FILE__, __LINE__)
#undef  calloc
#define calloc(n,s)  cos_mem_calloc (n,s, __FUNC__, __FILE__, __LINE__)
#undef  realloc
#define realloc(p,s) cos_mem_realloc(p,s, __FUNC__, __FILE__, __LINE__)
#undef  free
#define free(p)      cos_mem_free   (p  , __FUNC__, __FILE__, __LINE__)

#endif
#endif

/* NOTE-INFO: auto ctor
   the following function-like macro is useful to define automatic ctor
   for classes deriving from Object (or at equivalent level)
*/
#define cos_object_auto(cls) \
  {{ COS_CLS_NAME(cls).Behavior.id, COS_RC_AUTO }}

/***********************************************************
 * Implementation
 */

// topic-specific debug
#define COS_IF_DEBUG(topic,...) \
        ((void)(COS_PP_CAT(COS_DEBUG_,topic) && (cos_debug(__VA_ARGS__),0)))

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

#if COS_HAVE_TLS || !COS_HAVE_POSIX // -----------------------------

static cos_inline struct cos_method_cache1*
cos_method_cache1(void)
{
  extern __thread struct cos_method_cache1 cos_method_cache1_;
  return &cos_method_cache1_;
  COS_UNUSED(cos_method_cache1);
}

static cos_inline struct cos_method_cache2*
cos_method_cache2(void)
{
  extern __thread struct cos_method_cache2 cos_method_cache2_;
  return &cos_method_cache2_;
  COS_UNUSED(cos_method_cache2);
}

static cos_inline struct cos_method_cache3*
cos_method_cache3(void)
{
  extern __thread struct cos_method_cache3 cos_method_cache3_;
  return &cos_method_cache3_;
  COS_UNUSED(cos_method_cache3);
}

static cos_inline struct cos_method_cache4*
cos_method_cache4(void)
{
  extern __thread struct cos_method_cache4 cos_method_cache4_;
  return &cos_method_cache4_;
  COS_UNUSED(cos_method_cache4);
}

static cos_inline struct cos_method_cache5*
cos_method_cache5(void)
{
  extern __thread struct cos_method_cache5 cos_method_cache5_;
  return &cos_method_cache5_;
  COS_UNUSED(cos_method_cache5);
}

static cos_inline struct cos_exception_context*
cos_exception_context(void)
{
  extern __thread struct cos_exception_context *cos_exception_cxt_;
  return cos_exception_cxt_;
  COS_UNUSED(cos_exception_context);
}

#else // COS_HAVE_POSIX && !COS_HAVE_TLS ---------------------------

#include <pthread.h>

struct cos_exception_context* cos_exception_context(void);

struct cos_method_cache1* cos_method_cache1_init(void);
struct cos_method_cache2* cos_method_cache2_init(void);
struct cos_method_cache3* cos_method_cache3_init(void);
struct cos_method_cache4* cos_method_cache4_init(void);
struct cos_method_cache5* cos_method_cache5_init(void);

static cos_inline struct cos_method_cache1*
cos_method_cache1(void)
{
  extern pthread_key_t cos_method_cache1_key;
  struct cos_method_cache1 *cache = pthread_getspecific(cos_method_cache1_key);
  return cache ? cache : cos_method_cache1_init();
  COS_UNUSED(cos_method_cache1);
}

static cos_inline struct cos_method_cache2*
cos_method_cache2(void)
{
  extern pthread_key_t cos_method_cache2_key;
  struct cos_method_cache2 *cache = pthread_getspecific(cos_method_cache2_key);
  return cache ? cache : cos_method_cache2_init();
  COS_UNUSED(cos_method_cache2);
}

static cos_inline struct cos_method_cache3*
cos_method_cache3(void)
{
  extern pthread_key_t cos_method_cache3_key;
  struct cos_method_cache3 *cache = pthread_getspecific(cos_method_cache3_key);
  return cache ? cache : cos_method_cache3_init();
  COS_UNUSED(cos_method_cache3);
}

static cos_inline struct cos_method_cache4*
cos_method_cache4(void)
{
  extern pthread_key_t cos_method_cache4_key;
  struct cos_method_cache4 *cache = pthread_getspecific(cos_method_cache4_key);
  return cache ? cache : cos_method_cache4_init();
  COS_UNUSED(cos_method_cache4);
}

static cos_inline struct cos_method_cache5*
cos_method_cache5(void)
{
  extern pthread_key_t cos_method_cache5_key;
  struct cos_method_cache5 *cache = pthread_getspecific(cos_method_cache5_key);
  return cache ? cache : cos_method_cache5_init();
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
cos_object_cast(OBJ obj, const struct Class *cls, STR func,STR file,int line)
{
  if (cos_object_isa(obj, cls))
    return obj;

  cos_exception_badcast(obj, cls, func, file, line);
  COS_UNUSED(cos_object_cast);
}

static cos_inline void*
cos_object_dcast(OBJ obj, const struct Class *cls, STR func,STR file,int line)
{
  if (cos_object_isa     (obj, cls) ||
      cos_object_isKindOf(obj, cls))
    return obj;

  cos_exception_badcast(obj, cls, func, file, line);
  COS_UNUSED(cos_object_dcast);
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
                              void * const*alt, FCTV fct)
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

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
 | $Id: cosapi.h,v 1.3 2008/09/30 08:18:23 ldeniau Exp $
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

BOOL   cos_any_isKindOf(OBJ,const struct Class*);
BOOL   cos_any_changeClass(OBJ,const struct Class*);
BOOL   cos_any_unsafeChangeClass(OBJ,const struct Class *new,
                                     const struct Class *base);

struct Class* cos_class_get(U32);
struct Class* cos_class_getWithStr(STR);
BOOL          cos_class_isSubclassOf(const struct Class*,const struct Class*);

struct Generic* cos_generic_get(U32);
struct Generic* cos_generic_getWithStr(STR);

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
char*  cos_method_fullName(SEL,OBJ*,char*,U32);
void   cos_method_clearCache1(void);
void   cos_method_clearCache2(void);
void   cos_method_clearCache3(void);
void   cos_method_clearCache4(void);
void   cos_method_clearCache5(void);
void   cos_method_clearCaches(void);

void   cos_contract_invariantLoc(OBJ _1, STR file, int line);

void   cos_exception_assertLoc(STR as, STR file, int line);
void   cos_exception_errnoLoc(int err, STR file, int line);
void   cos_exception_throwLoc(OBJ ex, STR file, int line);
BOOL   cos_exception_catch(OBJ ex, OBJ cls);
BOOL   cos_exception_uncaught(void);

cos_exception_handler cos_exception_setTerminate(cos_exception_handler);

/* NOTE-INFO: loggers
   - prototype: void cos_xxx(STR fmt, ...);
   - all these handlers display on stderr
   - if fmt is ending by ':', the errno string is added
   - a '\n' is automatically added to the end
   - they can be turned on/off with setLevel.
*/
#define cos_debug(...) \
        cos_logmsg(cos_msg_debug,__FILE__,__LINE__,__VA_ARGS__)

#define cos_trace(...) \
        cos_logmsg(cos_msg_trace,__FILE__,__LINE__,__VA_ARGS__)

#define cos_warn( ...) \
        cos_logmsg(cos_msg_warn,__FILE__,__LINE__,__VA_ARGS__)

#define cos_error(...) \
        cos_logmsg(cos_msg_error,__FILE__,__LINE__,__VA_ARGS__)

#define cos_abort(...) \
        cos_logmsg(cos_msg_abort,__FILE__,__LINE__,__VA_ARGS__)

#define cos_logmsg(lvl,file,line,...) \
((void)(cos_logmsg_level[lvl] && (cos_logmsg(lvl,file,line,__VA_ARGS__) ,0)))

void (cos_logmsg)(int lvl, STR file, int line, STR fmt, ...)
                  __attribute__((__format__(__printf__,4,5)));

void cos_logmsg_setLevel(int lvl);

/***********************************************************
 * Implementation
 */

// topic-specific debug
#define COS_IF_DEBUG(topic,...) \
        ((void)(COS_PP_CAT(COS_DEBUG_,topic) && (cos_debug(__VA_ARGS__),0)))

// COS symbols init
void COS_SYMBOL(void);
void cos_symbol_register(struct Object**);

// next-method
void cos_method_nextClear(void);
void cos_method_nextInit(FUNC*,SEL,U32,struct Class* const*);

// 2nd and 3rd levels dispatch
IMP1 cos_method_fastLookup1_(struct cos_method_slot1**,SEL,U32);
IMP2 cos_method_fastLookup2_(struct cos_method_slot2**,SEL,U32,U32);
IMP3 cos_method_fastLookup3_(struct cos_method_slot3**,SEL,U32,U32,U32);
IMP4 cos_method_fastLookup4_(struct cos_method_slot4**,SEL,U32,U32,U32,U32);
IMP5 cos_method_fastLookup5_(struct cos_method_slot5**,SEL,U32,U32,U32,U32,U32);

BOOL cos_method_understand1_(struct cos_method_slot1**,SEL,U32);
BOOL cos_method_understand2_(struct cos_method_slot2**,SEL,U32,U32);
BOOL cos_method_understand3_(struct cos_method_slot3**,SEL,U32,U32,U32);
BOOL cos_method_understand4_(struct cos_method_slot4**,SEL,U32,U32,U32,U32);
BOOL cos_method_understand5_(struct cos_method_slot5**,SEL,U32,U32,U32,U32,U32);

// global variables (per thread)
#if COS_TLS
extern __thread struct cos_exception_context* cos_exception_cxt;
extern __thread struct cos_method_cache1 cos_method_cache1;
extern __thread struct cos_method_cache2 cos_method_cache2;
extern __thread struct cos_method_cache3 cos_method_cache3;
extern __thread struct cos_method_cache4 cos_method_cache4;
extern __thread struct cos_method_cache5 cos_method_cache5;
#else
extern          struct cos_exception_context* cos_exception_cxt;
extern          struct cos_method_cache1 cos_method_cache1;
extern          struct cos_method_cache2 cos_method_cache2;
extern          struct cos_method_cache3 cos_method_cache3;
extern          struct cos_method_cache4 cos_method_cache4;
extern          struct cos_method_cache5 cos_method_cache5;
#endif

// components tags
enum {
  cos_tag_invalid,
  cos_tag_class,
  cos_tag_mclass,
  cos_tag_pclass,
  cos_tag_generic,
  cos_tag_method,
  cos_tag_alias,
  cos_tag_last
};

// messages levels
enum {
  cos_msg_invalid,
  cos_msg_debug,
  cos_msg_trace,
  cos_msg_warn,
  cos_msg_error,
  cos_msg_abort,
  cos_msg_last
};

extern BOOL cos_logmsg_level[cos_msg_last];

/***********************************************************
 * Inlined functions
 */

static inline U32
cos_any_id(OBJ obj)
{
  return COS_STATIC_CAST(struct Any*, obj)->id;
  COS_UNUSED(cos_any_id);
}

static inline struct cos_exception_protect
cos_exception_protect(struct cos_exception_protect *ptr, OBJ const *obj)
{
  struct cos_exception_context *cxt = cos_exception_cxt;

  ptr->nxt = cxt->stk;
  ptr->obj = obj;
  cxt->stk = ptr;

  return *ptr;
  COS_UNUSED(cos_exception_protect);
}

#endif // COS_COS_COSAPI_H

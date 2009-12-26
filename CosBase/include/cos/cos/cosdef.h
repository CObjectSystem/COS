#ifndef COS_COS_COSDEF_H
#define COS_COS_COSDEF_H

/*
 o---------------------------------------------------------------------o
 |
 | COS typedefs and structs
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
 | $Id: cosdef.h,v 1.24 2009/12/26 15:02:44 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosdef.h>"
#endif

#if __STDC_VERSION__ >= 199901L
typedef _Bool                BOOL;
#else
typedef unsigned char        BOOL;
#endif

typedef signed   char        I8;
typedef unsigned char        U8;

typedef signed   short       I16;
typedef unsigned short       U16;

#if UINT_MAX >= 4294967295UL
typedef signed   int         I32;
typedef unsigned int         U32;
#else
typedef signed   long        I32;
typedef unsigned long        U32;
#endif

#if ULONG_MAX >= 18446744073709551615ULL
typedef signed   long        I64;
typedef unsigned long        U64;
#elif ULLONG_MAX >= 18446744073709551615ULL
typedef signed   long long   I64;
typedef unsigned long long   U64;
#elif defined(_LongLong)
typedef  _LongLong           I64;
typedef _ULongLong           U64;
#else
typedef struct { U32 _[2]; } I64;
typedef struct { U32 _[2]; } U64;
#endif

typedef double               F64;

#if __STDC_VERSION__ >= 199901L
typedef _Complex double      C64;
#elif defined(_ComplexDouble)
typedef _ComplexDouble       C64;
#else
typedef struct { F64 _[2]; } C64;
#endif

typedef const char*           STR;  // string literal
typedef struct OBJ*           OBJ;  // object ADT
typedef const struct Generic* SEL;  // message selector
typedef struct { OBJ _1,_2; } PAIR; // return by value

// function signatures
typedef void (*FCT )(void);
typedef void (*FCTV)(void*);
typedef void (*FCT1)(OBJ);
typedef void (*FCT2)(OBJ,OBJ);
typedef void (*FCT3)(OBJ,OBJ,OBJ);
typedef void (*FCT4)(OBJ,OBJ,OBJ,OBJ);
typedef void (*FCT5)(OBJ,OBJ,OBJ,OBJ,OBJ);
typedef void (*FCT6)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef void (*FCT7)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef void (*FCT8)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef void (*FCT9)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef void (*FCTN)(OBJ*,U32);

// functor signatures
typedef OBJ  (*FUN0)(void);
typedef OBJ  (*FUN1)(OBJ);
typedef OBJ  (*FUN2)(OBJ,OBJ);
typedef OBJ  (*FUN3)(OBJ,OBJ,OBJ);
typedef OBJ  (*FUN4)(OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FUN5)(OBJ,OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FUN6)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FUN7)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FUN8)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FUN9)(OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FUNN)(OBJ*,U32);

// method signatures
typedef void (*IMP1)(SEL,OBJ,                void*,void*);
typedef void (*IMP2)(SEL,OBJ,OBJ,            void*,void*);
typedef void (*IMP3)(SEL,OBJ,OBJ,OBJ,        void*,void*);
typedef void (*IMP4)(SEL,OBJ,OBJ,OBJ,OBJ,    void*,void*);
typedef void (*IMP5)(SEL,OBJ,OBJ,OBJ,OBJ,OBJ,void*,void*);

typedef void (*cos_exception_handler)(OBJ,STR,STR,int);

// limits

#define I8_MAX (U8_MAX/2)
#define U8_MAX ((U8)-1U)

#define I16_MAX (U16_MAX/2)
#define U16_MAX ((U16)-1U)

#define I32_MAX (U32_MAX/2)
#define U32_MAX ((U32)-1UL)

#define I64_MAX (U64_MAX/2)
#define U64_MAX ((U64)-1ULL)


/***********************************************************
 * Implementation
 */

// components tags
enum {
  cos_tag_invalid = 0,
  cos_tag_class,
  cos_tag_mclass,
  cos_tag_pclass,
  cos_tag_generic,
  cos_tag_method,
  cos_tag_alias,
  cos_tag_last
};

// try-endtry tags
enum {
  cos_tag_try     = 0,
  cos_tag_throw   = 1,
  cos_tag_catch   = 2,
  cos_tag_finally = 4
};

// contract-tags
enum {
  cos_tag_pre  = 0,
  cos_tag_redo = 1,
  cos_tag_post = 2
};

// compile-time checks of OBJ as selectors
typedef struct OBJ_as_SEL* OBJ_as_SEL;

// compile-time checks of OBJ vs void*
struct OBJ { char isOBJ; };

// generic arguments
struct cos_generic_arginfo {
  U16 size;
  U16 offset;
};

// exception context
struct cos_exception_context {
  struct cos_exception_context *prv;
  struct cos_exception_protect *stk;
  BOOL unstk;
  volatile OBJ ex;
  volatile STR func;
  volatile STR file;
  volatile int line;
  volatile int tag;
  cos_exception_jmpbuf buf;
};

// exception protection
struct cos_exception_protect {
  struct cos_exception_protect *prv;
  OBJ const *obj;
};

struct cos_exception_extendedProtect {
  struct cos_exception_protect *prv;
  OBJ   const *obj;
  void *const *alt;
  FCTV         fct;
};

// dispatch caches
struct cos_method_cache1 {
  struct cos_method_slot1 **slot;
  U32 msk;
};

struct cos_method_cache2 {
  struct cos_method_slot2 **slot;
  U32 msk;
};

struct cos_method_cache3 {
  struct cos_method_slot3 **slot;
  U32 msk;
};

struct cos_method_cache4 {
  struct cos_method_slot4 **slot;
  U32 msk;
};

struct cos_method_cache5 {
  struct cos_method_slot5 **slot;
  U32 msk;
};

// dispatch slots
struct cos_method_slot1 {
  struct cos_method_slot1 *nxt;
  IMP1 fct;
  U32 idg, id1;
};

struct cos_method_slot2 {
  struct cos_method_slot2 *nxt;
  IMP2 fct;
  U32 idg, id1, id2;
};

struct cos_method_slot3 {
  struct cos_method_slot3 *nxt;
  IMP3 fct;
  U32 idg, id1, id2, id3;
};

struct cos_method_slot4 {
  struct cos_method_slot4 *nxt;
  IMP4 fct;
  U32 idg, id1, id2, id3, id4;
};

struct cos_method_slot5 {
  struct cos_method_slot5 *nxt;
  IMP5 fct;
  U32 idg, id1, id2, id3, id4, id5;
};

#endif // COS_COS_COSDEF_H

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
 | $Id: cosdef.h,v 1.33 2010/01/31 12:03:53 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosdef.h>"
#endif

#if __STDC_VERSION__ >= 199901L
typedef _Bool                 BOOL;
#else
typedef unsigned char         BOOL;
#endif

typedef signed   char         I8;
typedef unsigned char         U8;

typedef signed   short        I16;
typedef unsigned short        U16;

#if UINT_MAX >= 4294967295UL
typedef signed   int          I32;
typedef unsigned int          U32;
#else
typedef signed   long         I32;
typedef unsigned long         U32;
#endif

#if ULONG_MAX >= 18446744073709551615ULL
typedef signed   long         I64;
typedef unsigned long         U64;
#elif ULLONG_MAX >= 18446744073709551615ULL
typedef signed   long long    I64;
typedef unsigned long long    U64;
#elif defined(_LongLong)
typedef  _LongLong            I64;
typedef _ULongLong            U64;
#else
typedef struct { U32 _[2]; }  I64;
typedef struct { U32 _[2]; }  U64;
#endif

typedef double                F64;

#if __STDC_VERSION__ >= 199901L
typedef _Complex double       C64;
#elif defined(_ComplexDouble)
typedef _ComplexDouble        C64;
#else
typedef struct { F64 _[2]; }  C64;
#endif

typedef const char*           STR;  // string literal
typedef struct OBJ*           OBJ;  // object ADT
typedef const struct Generic* SEL;  // message selector
typedef struct { OBJ _[2]; }  PAIR; // return by value

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

#define I8_MIN SCHAR_MIN
#define I8_MAX SCHAR_MAX
#define U8_MAX UCHAR_MAX

#define I16_MIN  SHRT_MIN
#define I16_MAX  SHRT_MAX
#define U16_MAX USHRT_MAX

#if UINT_MAX >= 4294967295UL
#define I32_MIN INT_MIN
#define I32_MAX INT_MAX
#define U32_MAX UINT_MAX
#else
#define I32_MIN LONG_MIN
#define I32_MAX LONG_MAX
#define U32_MAX ULONG_MAX
#endif

#if ULONG_MAX >= 18446744073709551615ULL
#define I64_MIN LONG_MIN
#define I64_MAX LONG_MAX
#define U64_MAX ULONG_MAX
#else
#define I64_MIN LLONG_MIN
#define I64_MAX LLONG_MAX
#define U64_MAX ULLONG_MAX
#endif

// universal alignment
struct cos_mem_alignment {
  union {
  BOOL  u1,   *pu1;
  U8    u8,   *pu8;
  U16   u16,  *pu16;
  U32   u32,  *pu32;
  U64   u64,  *pu64;
  F64   f64,  *pf64;
  STR   str,  *pstr;
  void *ptr, **pptr;
  OBJ   obj,  *pobj;
  FCT   fct,  *pfct;
  } _;
};

/***********************************************************
 * Implementation
 */

// components tags
enum {
  cos_tag_invalid,
  // must be odd (behavior)
  cos_tag_class   = 0x11,
  cos_tag_mclass  = 0x21,
  cos_tag_pclass  = 0x31,
  cos_tag_generic = 0x41,
  // must be even (non-behavior)
  cos_tag_method  = 0x50,
  cos_tag_alias   = 0x60,
  cos_tag_docstr  = 0x70,
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

// compile-time checks of OBJ as receivers
typedef struct OBJ_as_RCV* OBJ_as_RCV;

// compile-time checks of OBJ vs void*
struct OBJ { char isOBJ; };

// generic receivers info
struct cos_generic_rcvinfo {
  U8 index;   // index as parameter
  U8 objidx;  // index as object
};

// generic arguments info
struct cos_generic_arginfo {
  U16 size;   // OBJects have "zero" size
  U16 offset;
  U8  index;  // index as parameter
  U8  objidx; // index as object
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
  U32 msk, mis, mis2;
};

struct cos_method_cache2 {
  struct cos_method_slot2 **slot;
  U32 msk, mis, mis2;
};

struct cos_method_cache3 {
  struct cos_method_slot3 **slot;
  U32 msk, mis, mis2;
};

struct cos_method_cache4 {
  struct cos_method_slot4 **slot;
  U32 msk, mis, mis2;
};

struct cos_method_cache5 {
  struct cos_method_slot5 **slot;
  U32 msk, mis, mis2;
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

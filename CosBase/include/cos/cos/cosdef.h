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
 | $Id: cosdef.h,v 1.10 2008/10/31 15:19:44 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosdef.h>"
#endif

typedef _Bool                   BOOL;

typedef signed   char      I8 , BYTE;
typedef unsigned char      U8 , UBYTE;

typedef signed   short     I16, SHORT;
typedef unsigned short     U16, USHORT;

#if UINT_MAX >= 4294967295UL
typedef signed   int       I32, INT;
typedef unsigned int       U32, UINT;
#else
typedef signed   long      I32, INT;
typedef unsigned long      U32, UINT;
#endif

#if ULONG_MAX >= 18446744073709551615ULL
typedef signed   long      I64, LONG;
typedef unsigned long      U64, ULONG;
#elif ULLONG_MAX >= 18446744073709551615ULL
typedef signed   long long I64, LONG;
typedef unsigned long long U64, ULONG;
#elif defined(_LongLong)
typedef _LongLong          I64, LONG;
typedef _ULongLong         U64, ULONG;
#else
#error "COS: 64 bits integers not supported"
#endif

typedef double             R64, FLOAT;

#if __STDC_VERSION__ >= 199901L
typedef _Complex double    C64, COMPLEX;
#elif defined(_ComplexDouble)
typedef _ComplexDouble     C64, COMPLEX;
#else
#error "COS: complex not supported"
#endif

typedef ptrdiff_t               INDEX;
typedef size_t                  SIZE;

typedef const char*             STR; // string literal
typedef struct OBJ*             OBJ; // object ADT, never defined
typedef const struct Generic*   SEL; // message selector

typedef void (*FUNC)(void);

typedef void (*IMP1)(SEL,OBJ,                void*,void*);
typedef void (*IMP2)(SEL,OBJ,OBJ,            void*,void*);
typedef void (*IMP3)(SEL,OBJ,OBJ,OBJ,        void*,void*);
typedef void (*IMP4)(SEL,OBJ,OBJ,OBJ,OBJ,    void*,void*);
typedef void (*IMP5)(SEL,OBJ,OBJ,OBJ,OBJ,OBJ,void*,void*);

typedef OBJ  (*OBJFCT1)(OBJ);
typedef I32  (*I32FCT1)(I32);
typedef I64  (*I64FCT1)(I64);
typedef R64  (*R64FCT1)(R64);
typedef C64  (*C64FCT1)(C64);

typedef OBJ  (*OBJFCT2)(OBJ,OBJ);
typedef I32  (*I32FCT2)(I32,I32);
typedef I64  (*I64FCT2)(I64,I64);
typedef R64  (*R64FCT2)(R64,R64);
typedef C64  (*C64FCT2)(C64,C64);

typedef OBJ  (*OBJFCT3)(OBJ,OBJ,OBJ);
typedef I32  (*I32FCT3)(I32,I32,I32);
typedef I64  (*I64FCT3)(I64,I64,I64);
typedef R64  (*R64FCT3)(R64,R64,R64);
typedef C64  (*C64FCT3)(C64,C64,C64);

typedef OBJ  (*OBJFCT4)(OBJ,OBJ,OBJ,OBJ);
typedef I32  (*I32FCT4)(I32,I32,I32,I32);
typedef I64  (*I64FCT4)(I64,I64,I64,I64);
typedef R64  (*R64FCT4)(R64,R64,R64,R64);
typedef C64  (*C64FCT4)(C64,C64,C64,C64);

typedef OBJ  (*OBJFCT5)(OBJ,OBJ,OBJ,OBJ,OBJ);
typedef I32  (*I32FCT5)(I32,I32,I32,I32,I32);
typedef I64  (*I64FCT5)(I64,I64,I64,I64,I64);
typedef R64  (*R64FCT5)(R64,R64,R64,R64,R64);
typedef C64  (*C64FCT5)(C64,C64,C64,C64,C64);

typedef void (*cos_exception_handler)(OBJ,STR,STR,int);

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

// selector types for compile-time checks
typedef struct OBJ_as_SEL* OBJ_as_SEL; // ADT, never defined

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

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
 | $Id: cosdef.h,v 1.7 2008/10/15 19:18:06 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosdef.h>"
#endif

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
typedef signed   _LongLong I64, LONG;
typedef unsigned _LongLong U64, ULONG;
#else
#error "COS: 64 bits integers not supported"
#endif

typedef _Bool                   BOOL;
typedef          double    R64, FLOAT;
typedef _Complex double    C64, COMPLEX;

typedef ptrdiff_t               INDEX;
typedef size_t                  SIZE;

typedef const char*             STR; // string literal
typedef struct OBJ*             OBJ; // object ADT, never defined
typedef const struct Generic*   SEL; // message selector

typedef void (*FUNC)(void);
typedef OBJ  (*FCT0)(void);
typedef OBJ  (*FCT1)(OBJ);
typedef OBJ  (*FCT2)(OBJ,OBJ);
typedef OBJ  (*FCT3)(OBJ,OBJ,OBJ);
typedef OBJ  (*FCT4)(OBJ,OBJ,OBJ,OBJ);
typedef OBJ  (*FCT5)(OBJ,OBJ,OBJ,OBJ,OBJ);

typedef void (*IMP1)(SEL,OBJ,                void*,void*);
typedef void (*IMP2)(SEL,OBJ,OBJ,            void*,void*);
typedef void (*IMP3)(SEL,OBJ,OBJ,OBJ,        void*,void*);
typedef void (*IMP4)(SEL,OBJ,OBJ,OBJ,OBJ,    void*,void*);
typedef void (*IMP5)(SEL,OBJ,OBJ,OBJ,OBJ,OBJ,void*,void*);

typedef void (*cos_exception_handler)(OBJ,STR,int);

/***********************************************************
 * Implementation
 */

// selector compile-time checks
typedef struct OBJ_as_SEL* OBJ_as_SEL; // ADT, never defined

// exception context
struct cos_exception_context {
  struct cos_exception_context *prv;
  struct cos_exception_protect *stk;
  BOOL unstk;
  volatile OBJ ex;
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

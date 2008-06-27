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
 | $Id: cosdef.h,v 1.2 2008/06/27 16:45:54 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosdef.h>"
#endif

#if UINT_MAX >= 4294967295UL
typedef signed   int S32;
typedef unsigned int U32;
#else
typedef signed   long S32;
typedef unsigned long U32;
#endif

#if ULONG_MAX >= 18446744073709551615ULL
typedef signed   long S64;
typedef unsigned long U64;
#elif ULLONG_MAX >= 18446744073709551615ULL
typedef signed   long long S64;
typedef unsigned long long U64;
#elif defined(_LongLong)
typedef signed   _LongLong S64;
typedef unsigned _LongLong U64;
#else
#error "COS: 64 bits integers not supported"
#endif

typedef _Bool BOOL;
typedef const char* STR; // string literal
typedef struct OBJ* OBJ; // ADT, never defined
typedef const struct Generic* SEL;

typedef void (*FUNC)(void);
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
  struct cos_exception_context *nxt;
  struct cos_exception_protect *stk;
  BOOL unstk;
  volatile OBJ ex;
  volatile STR file;
  volatile int line;
  volatile int st;
  cos_exception_jmpbuf buf;
};

// exception protection
struct cos_exception_protect {
  struct cos_exception_protect *nxt;
  OBJ const *obj;
};

// dispatch caches
struct cos_method_cache1 {
  struct cos_method_slot1 **slot;
  size_t msk;
};

struct cos_method_cache2 {
  struct cos_method_slot2 **slot;
  size_t msk;
};

struct cos_method_cache3 {
  struct cos_method_slot3 **slot;
  size_t msk;
};

struct cos_method_cache4 {
  struct cos_method_slot4 **slot;
  size_t msk;
};

struct cos_method_cache5 {
  struct cos_method_slot5 **slot;
  size_t msk;
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

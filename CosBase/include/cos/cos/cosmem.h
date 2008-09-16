#ifndef COS_COS_COSMEM_H
#define COS_COS_COSMEM_H

/*
 o---------------------------------------------------------------------o
 |
 | COS memory utility macros
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
 | $Id: cosmem.h,v 1.1 2008/09/16 08:07:35 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosmem.h>"
#endif 

// fast memset

#define COS_MEM_SET(...) \
        COS_PP_CAT_NARG(COS_MEM_SET_, __VA_ARGS__)(__VA_ARGS__)

#define COS_MEM_SET_3(DST,VAL,N) \
        COS_MEM_SET_4(DST,VAL,N,=)

#define COS_MEM_SET_4(DST,VAL,N,OP) \
  do { \
    size_t n   = (N); \
    size_t cnt = n / 8 + 1; \
    switch (n % 8) \
      do {  *(DST)++ OP (VAL); \
    case 7: *(DST)++ OP (VAL); \
    case 6: *(DST)++ OP (VAL); \
    case 5: *(DST)++ OP (VAL); \
    case 4: *(DST)++ OP (VAL); \
    case 3: *(DST)++ OP (VAL); \
    case 2: *(DST)++ OP (VAL); \
    case 1: *(DST)++ OP (VAL); \
    case 0: ; \
      } while(--cnt); \
  } while (0)

// fast memcopy

#define COS_MEM_COPY(...) \
        COS_PP_CAT_NARG(COS_MEM_COPY_, __VA_ARGS__)(__VA_ARGS__)

#define COS_MEM_COPY_3(DST,SRC,N) \
        COS_MEM_COPY_4(DST,SRC,N,=)

#define COS_MEM_COPY_4(DST,SRC,N,OP) \
  do { \
    size_t n   = (N); \
    size_t cnt = n / 8 + 1; \
    switch (n % 8) \
      do {  *(DST)++ OP *(SRC)++; \
    case 7: *(DST)++ OP *(SRC)++; \
    case 6: *(DST)++ OP *(SRC)++; \
    case 5: *(DST)++ OP *(SRC)++; \
    case 4: *(DST)++ OP *(SRC)++; \
    case 3: *(DST)++ OP *(SRC)++; \
    case 2: *(DST)++ OP *(SRC)++; \
    case 1: *(DST)++ OP *(SRC)++; \
    case 0: ; \
      } while(--cnt); \
  } while (0)

// fast reverse memcopy

#define COS_MEM_RCOPY(...) \
        COS_PP_CAT_NARG(COS_MEM_RCOPY_, __VA_ARGS__)(__VA_ARGS__)

#define COS_MEM_RCOPY_3(DST,SRC,N) \
        COS_MEM_RCOPY_4(DST,SRC,N,=)

#define COS_MEM_RCOPY_4(DST,SRC,N,OP) \
  do { \
    size_t n   = (N); \
    size_t cnt = n / 8 + 1; \
    (SRC) += n, (DST) += n; \
    switch (n % 8) \
      do {  *--(DST) OP *--(SRC); \
    case 7: *--(DST) OP *--(SRC); \
    case 6: *--(DST) OP *--(SRC); \
    case 5: *--(DST) OP *--(SRC); \
    case 4: *--(DST) OP *--(SRC); \
    case 3: *--(DST) OP *--(SRC); \
    case 2: *--(DST) OP *--(SRC); \
    case 1: *--(DST) OP *--(SRC); \
    case 0: ; \
      } while(--cnt); \
  } while (0)

// fast reverse memswap

#define COS_MEM_RSWAP(...) \
        COS_PP_CAT_NARG(COS_MEM_RSWAP_, __VA_ARGS__)(__VA_ARGS__)

#define COS_MEM_RSWAP_4(PTR1,PTR2,TMP,N) \
        COS_MEM_RSWAP_5(PTR1,PTR2,TMP,N,=)

#define COS_MEM_RSWAP_5(PTR1,PTR2,TMP,N,OP) \
  do { \
    size_t n   = (N); \
    size_t cnt = n / 8 + 1; \
    (PTR1) += n, (PTR2) += n; \
    switch (n % 8) \
      do {  (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 7: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 6: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 5: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 4: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 3: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 2: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 1: (TMP) = *--(PTR1), *(PTR1) OP *--(PTR2), *(PTR2) OP (TMP); \
    case 0: ; \
      } while(--cnt); \
  } while (0)

#endif // COS_COS_COSMEM_H

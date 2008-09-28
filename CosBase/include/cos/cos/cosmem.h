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
 | $Id: cosmem.h,v 1.2 2008/09/28 19:48:21 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cosmem.h>"
#endif 

// unrolled loop
#define COS_LOOP(N,...) \
  do { \
    U32 _n = (N); \
    U32 _cnt = _n / 8 + 1; \
    switch (_n % 8) \
      do {  __VA_ARGS__; \
    case 7: __VA_ARGS__; \
    case 6: __VA_ARGS__; \
    case 5: __VA_ARGS__; \
    case 4: __VA_ARGS__; \
    case 3: __VA_ARGS__; \
    case 2: __VA_ARGS__; \
    case 1: __VA_ARGS__; \
    case 0: ; \
      } while(--_cnt); \
  } while (0)

// memset
#define COS_MEM_SET(...) \
        COS_PP_CAT_NARG(COS_MEM_DO_,__VA_ARGS__) \
          (COS_MEM_SET_5,=,COS_PP_ID, __VA_ARGS__)

#define COS_MEM_SET_5(DST,SRC,N,OP,FUN) \
        COS_LOOP(N, *(DST)++ OP FUN(SRC) )

// memfold
#define COS_MEM_FOLD(...) \
        COS_PP_CAT_NARG(COS_MEM_DO_, __VA_ARGS__) \
          (COS_MEM_FOLD_5,+=,COS_PP_ID, __VA_ARGS__)

#define COS_MEM_FOLD_5(DST,SRC,N,OP,FUN) \
        COS_LOOP(N, (DST) OP FUN(*(SRC)++) )

// memmap (memcpy)
#define COS_MEM_MAP(...) \
        COS_PP_CAT_NARG(COS_MEM_DO_, __VA_ARGS__) \
          (COS_MEM_MAP_5,=,COS_PP_ID, __VA_ARGS__)

#define COS_MEM_MAP_5(DST,SRC,N,OP,FUN) \
        COS_LOOP(N, *(DST)++ OP FUN(*(SRC)++) )

// memmap reversed
#define COS_MEM_RMAP(...) \
        COS_PP_CAT_NARG(COS_MEM_DO_, __VA_ARGS__) \
          (COS_MEM_RMAP_5,=,COS_PP_ID, __VA_ARGS__)

#define COS_MEM_RMAP_5(DST,SRC,N,OP,FUN) \
        do { \
          U32 _rn = (N); (SRC) += _rn, (DST) += _rn; \
          COS_LOOP(_rn, *--(DST) OP FUN(*--(SRC)) ); \
        } while(0)

// memswap
#define COS_MEM_SWAP(...) \
        COS_PP_CAT_NARG(COS_MEM_DOT_,__VA_ARGS__) \
          (COS_MEM_SWAP_6,=,COS_PP_ID, __VA_ARGS__)

#define COS_MEM_SWAP_6(PTR1,PTR2,TMP,N,OP,FUN) \
        COS_LOOP(N, (TMP) = FUN(*(PTR1)), *(PTR1)++ OP FUN(*(PTR2)), *(PTR2)++ OP (TMP) )

// reverse memswap
#define COS_MEM_RSWAP(...) \
        COS_PP_CAT_NARG(COS_MEM_DOT_, __VA_ARGS__) \
          (COS_MEM_RSWAP_6,=,COS_PP_ID, __VA_ARGS__)

#define COS_MEM_RSWAP_6(PTR1,PTR2,TMP,N,OP,FUN) \
        do { \
          U32 _rn = (N); (PTR1) += _rn, (PTR2) += _rn; \
          COS_LOOP(_rn, (TMP) = FUN(*--(PTR1)), *(PTR1) OP FUN(*--(PTR2)), *(PTR2) OP (TMP) ); \
        } while (0)

/***********************************************************
 * Implementation
 */

// memdo (set default args)
#define COS_MEM_DO_3(DO,OP0,FUN0, DST,SRC,N) \
        COS_MEM_DO_4(DO,OP0,FUN0, DST,SRC,N,OP0)

#define COS_MEM_DO_4(DO,OP0,FUN0, DST,SRC,N,OP) \
        COS_MEM_DO_5(DO,OP0,FUN0, DST,SRC,N,OP,FUN0)

#define COS_MEM_DO_5(DO,OP0,FUN0, DST,SRC,N,OP,FUN) \
                     DO          (DST,SRC,N,OP,FUN)

// memdot (set default args)
#define COS_MEM_DOT_4(DO,OP0,FUN0, DST,SRC,TMP,N) \
        COS_MEM_DOT_5(DO,OP0,FUN0, DST,SRC,TMP,N,OP0)

#define COS_MEM_DOT_5(DO,OP0,FUN0, DST,SRC,TMP,N,OP) \
        COS_MEM_DOT_6(DO,OP0,FUN0, DST,SRC,TMP,N,OP,FUN0)

#define COS_MEM_DOT_6(DO,OP0,FUN0, DST,SRC,TMP,N,OP,FUN) \
                      DO          (DST,SRC,TMP,N,OP,FUN)

#endif // COS_COS_COSMEM_H

#ifndef COS_CPP_ALGOS_H
#define COS_CPP_ALGOS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS preprocessor algos
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
 | $Id: algos.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cpp/algos.h>"
#endif

// fold left elements of tuple using function F(a,b)
#define COS_PP_FOLDL(T,a0,F) \
        COS_PP_1ST(COS_PP_EVAL(COS_PP_LEN(T), \
          (a0,(COS_PP_ID T,),F),COS_PP_FOLDL_0))

// fold right elements of tuple using function F(a,b)
#define COS_PP_FOLDR(T,a0,F) \
        COS_PP_1ST(COS_PP_EVAL(COS_PP_LEN(T), \
          (a0,(COS_PP_SEQ(COS_PP_REV(T)),),F),COS_PP_FOLDR_0))

// scan left elements of tuple using function F(a,b)
#define COS_PP_SCANL(T,a0,F) \
        COS_PP_RRES_(COS_PP_EVAL(COS_PP_LEN(T), \
          ((a0,),(COS_PP_ID T,),F),COS_PP_SCANL_0))

// scan right elements of tuple using function F(a,b)
#define COS_PP_SCANR(T,a0,F) \
        COS_PP_REV(COS_PP_RRES_(COS_PP_EVAL(COS_PP_LEN(T), \
          ((a0,),(COS_PP_SEQ(COS_PP_REV(T)),),F),COS_PP_SCANR_0)))

// filter elements of tuple using the predicate function PF(A)
#define COS_PP_FILTER(T,PF) \
        COS_PP_RES1_(COS_PP_EVAL(COS_PP_LEN(T), \
          ((),(COS_PP_ID T,),PF),COS_PP_FILTER_0))

// map function F(a) on elements of tuple T
#define COS_PP_MAP(T,F) \
        COS_PP_RES_(COS_PP_EVAL(COS_PP_LEN(T), \
          ((),(COS_PP_ID T,),F),COS_PP_MAP_0))

// map function F(a1,a2) on elements of tuples T1,T2 up to length(T1)
#define COS_PP_MAP2(T1,T2,F) \
        COS_PP_RES_(COS_PP_EVAL(COS_PP_LEN(T1), \
          ((),(COS_PP_ID T1,),(COS_PP_ID T2,),F),COS_PP_MAP2_0))

// map function F(a1,a2,a3) on elements of tuples T1,T2,T3 up to length(T1)
#define COS_PP_MAP3(T1,T2,T3,F) \
        COS_PP_RES_(COS_PP_EVAL(COS_PP_LEN(T1), \
          ((),(COS_PP_ID T1,),(COS_PP_ID T2,),(COS_PP_ID T3,),F),COS_PP_MAP3_0))

// flatten tuple T to sequence using s as separator, i.e. (a,b,c) -> a b c
#define COS_PP_SEP(T) \
        COS_PP_FOLDL(T,,COS_PP_PAIR)

// flatten tuple T to sequence using s as separator, i.e. (a,b,c),; -> a ; b ; c
#define COS_PP_SEPWITH(T,s) \
        COS_PP_IF(COS_PP_2ARGS(COS_PP_ID T))( \
          COS_PP_ARG1 T COS_PP_SEP( \
            COS_PP_MAP2((COS_PP_REST T),(COS_PP_DUPSEQ_N(s)),COS_PP_SWAP)), \
          COS_PP_ID T)

/***********************************************************
 * Implementation
 */

#define COS_PP_RES1_(T) \
        COS_PP_RES1__ T
#define COS_PP_RES1__(R,...) \
        COS_PP_IF(COS_PP_2ARGS(COS_PP_ID R))((COS_PP_REST R),R)

#define COS_PP_RES_(T) \
        COS_PP_RES__ T
#define COS_PP_RES__(R,...) \
        (COS_PP_PAIR(COS_PP_REST,R))

#define COS_PP_RRES_(T) \
        COS_PP_RRES__ T
#define COS_PP_RRES__(R,...) \
        (COS_PP_PAIR(COS_PP_REST,COS_PP_REV(R)))

#define COS_PP_FOLDL_0(T) \
        COS_PP_FOLDL_1 T
#define COS_PP_FOLDL_1(R,T,F) \
        (F(R,COS_PP_ARG1 T),(COS_PP_REST T),F)

#define COS_PP_FOLDR_0(T) \
        COS_PP_FOLDR_1 T
#define COS_PP_FOLDR_1(R,T,F) \
        (F(COS_PP_ARG1 T,R),(COS_PP_REST T),F)

#define COS_PP_SCANL_0(T) \
        COS_PP_SCANL_1 T
#define COS_PP_SCANL_1(R,T,F) \
        ((F(COS_PP_ARG1 R,COS_PP_ARG1 T),COS_PP_ID R),(COS_PP_REST T),F)

#define COS_PP_SCANR_0(T) \
        COS_PP_SCANR_1 T
#define COS_PP_SCANR_1(R,T,F) \
        ((F(COS_PP_ARG1 T,COS_PP_ARG1 R),COS_PP_ID R),(COS_PP_REST T),F)

#define COS_PP_FILTER_0(T) \
        COS_PP_FILTER_1 T
#define COS_PP_FILTER_1(R,T,PF) \
        (COS_PP_IF(PF(COS_PP_ARG1 T))((COS_PP_ID R,COS_PP_ARG1 T),R),(COS_PP_REST T),PF)

#define COS_PP_MAP_0(T) \
        COS_PP_MAP_1 T
#define COS_PP_MAP_1(R,T,F) \
        ((COS_PP_ID R,F(COS_PP_ARG1 T)),(COS_PP_REST T),F)

#define COS_PP_MAP2_0(T) \
        COS_PP_MAP2_1 T
#define COS_PP_MAP2_1(R,T1,T2,F) \
        ((COS_PP_ID R,F(COS_PP_ARG1 T1,COS_PP_ARG1 T2)),(COS_PP_REST T1),(COS_PP_REST T2),F)

#define COS_PP_MAP3_0(T) \
        COS_PP_MAP3_1 T
#define COS_PP_MAP3_1(R,T1,T2,T3,F) \
        ((COS_PP_ID R,F(COS_PP_ARG1 T1,COS_PP_ARG1 T2,COS_PP_ARG1 T3)), \
          (COS_PP_REST T1),(COS_PP_REST T2),(COS_PP_REST T3),F)

#endif // COS_CPP_ALGOS_H

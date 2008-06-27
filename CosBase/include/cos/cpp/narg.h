#ifndef COS_CPP_NARG_H
#define COS_CPP_NARG_H

/*
 o---------------------------------------------------------------------o
 |
 | COS preprocessor arguments count
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
 | $Id: narg.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cpp/narg.h>"
#endif

#define COS_PP_MAX_N 63

#define COS_PP_NARG(...) \
        COS_PP_NARG_(__VA_ARGS__,COS_PP_REVSEQ_N(),)

#define COS_PP_DUPSEQ_N(...) \
        COS_PP_DUPSEQ_N_(__VA_ARGS__)

#define COS_PP_NUMSEQ_N(...) \
        COS_PP_NUMSEQ_N_(__VA_ARGS__)

#define COS_PP_REVSEQ_N(...) \
        COS_PP_REVSEQ_N_(__VA_ARGS__)

/***********************************************************
 * Implementation
 */

#define COS_PP_NARG_(...) \
        COS_PP_NARG_N_(__VA_ARGS__)

#define COS_PP_NARG_N_( \
 _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
_61,_62,_63,N,...) N

#define COS_PP_DUPSEQ_N_(...) \
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,__VA_ARGS__,\
__VA_ARGS__,__VA_ARGS__,__VA_ARGS__

#define COS_PP_NUMSEQ_N_(...) \
__VA_ARGS__## 1,__VA_ARGS__## 2,__VA_ARGS__## 3,__VA_ARGS__## 4,__VA_ARGS__## 5,\
__VA_ARGS__## 6,__VA_ARGS__## 7,__VA_ARGS__## 8,__VA_ARGS__## 9,__VA_ARGS__##10,\
__VA_ARGS__##11,__VA_ARGS__##12,__VA_ARGS__##13,__VA_ARGS__##14,__VA_ARGS__##15,\
__VA_ARGS__##16,__VA_ARGS__##17,__VA_ARGS__##18,__VA_ARGS__##19,__VA_ARGS__##20,\
__VA_ARGS__##21,__VA_ARGS__##22,__VA_ARGS__##23,__VA_ARGS__##24,__VA_ARGS__##25,\
__VA_ARGS__##26,__VA_ARGS__##27,__VA_ARGS__##28,__VA_ARGS__##29,__VA_ARGS__##30,\
__VA_ARGS__##31,__VA_ARGS__##32,__VA_ARGS__##33,__VA_ARGS__##34,__VA_ARGS__##35,\
__VA_ARGS__##36,__VA_ARGS__##37,__VA_ARGS__##38,__VA_ARGS__##39,__VA_ARGS__##40,\
__VA_ARGS__##41,__VA_ARGS__##42,__VA_ARGS__##43,__VA_ARGS__##44,__VA_ARGS__##45,\
__VA_ARGS__##46,__VA_ARGS__##47,__VA_ARGS__##48,__VA_ARGS__##49,__VA_ARGS__##50,\
__VA_ARGS__##51,__VA_ARGS__##52,__VA_ARGS__##53,__VA_ARGS__##54,__VA_ARGS__##55,\
__VA_ARGS__##56,__VA_ARGS__##57,__VA_ARGS__##58,__VA_ARGS__##59,__VA_ARGS__##60,\
__VA_ARGS__##61,__VA_ARGS__##62,__VA_ARGS__##63

#define COS_PP_REVSEQ_N_(...) \
__VA_ARGS__##63,__VA_ARGS__##62,__VA_ARGS__##61,\
__VA_ARGS__##60,__VA_ARGS__##59,__VA_ARGS__##58,__VA_ARGS__##57,__VA_ARGS__##56,\
__VA_ARGS__##55,__VA_ARGS__##54,__VA_ARGS__##53,__VA_ARGS__##52,__VA_ARGS__##51,\
__VA_ARGS__##50,__VA_ARGS__##49,__VA_ARGS__##48,__VA_ARGS__##47,__VA_ARGS__##46,\
__VA_ARGS__##45,__VA_ARGS__##44,__VA_ARGS__##43,__VA_ARGS__##42,__VA_ARGS__##41,\
__VA_ARGS__##40,__VA_ARGS__##39,__VA_ARGS__##38,__VA_ARGS__##37,__VA_ARGS__##36,\
__VA_ARGS__##35,__VA_ARGS__##34,__VA_ARGS__##33,__VA_ARGS__##32,__VA_ARGS__##31,\
__VA_ARGS__##30,__VA_ARGS__##29,__VA_ARGS__##28,__VA_ARGS__##27,__VA_ARGS__##26,\
__VA_ARGS__##25,__VA_ARGS__##24,__VA_ARGS__##23,__VA_ARGS__##22,__VA_ARGS__##21,\
__VA_ARGS__##20,__VA_ARGS__##19,__VA_ARGS__##18,__VA_ARGS__##17,__VA_ARGS__##16,\
__VA_ARGS__##15,__VA_ARGS__##14,__VA_ARGS__##13,__VA_ARGS__##12,__VA_ARGS__##11,\
__VA_ARGS__##10,__VA_ARGS__## 9,__VA_ARGS__## 8,__VA_ARGS__## 7,__VA_ARGS__## 6,\
__VA_ARGS__## 5,__VA_ARGS__## 4,__VA_ARGS__## 3,__VA_ARGS__## 2,__VA_ARGS__## 1

#endif // COS_CPP_NARG_H

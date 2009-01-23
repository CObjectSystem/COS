#ifndef COS_CPP_UTILS_H
#define COS_CPP_UTILS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS preprocessor utility macros
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
 | $Id: utils.h,v 1.2 2009/01/23 15:12:28 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cpp/utils.h>"
#endif 

#define COS_PP_ID(...)       __VA_ARGS__
#define COS_PP_EAT(...)      /* nothing */
#define COS_PP_PART(...)     __VA_ARGS__,
#define COS_PP_PPART(...)   (__VA_ARGS__),
#define COS_PP_PAIR(a,...) a __VA_ARGS__
#define COS_PP_SWAP(a,...)   __VA_ARGS__ a
#define COS_PP_REST(a,...)   __VA_ARGS__
#define COS_PP_EMPTY()       /* empty */
#define COS_PP_COMMA()       ,
#define COS_PP_LPAR()        (
#define COS_PP_RPAR()        )

#define COS_PP_ARG1(a,                ...)  a
#define COS_PP_ARG2(a,b,              ...)  b
#define COS_PP_ARG3(a,b,c,            ...)  c
#define COS_PP_ARG4(a,b,c,d,          ...)  d
#define COS_PP_ARG5(a,b,c,d,e,        ...)  e
#define COS_PP_ARG6(a,b,c,d,e,f,      ...)  f
#define COS_PP_ARG7(a,b,c,d,e,f,g,    ...)  g
#define COS_PP_ARG8(a,b,c,d,e,f,g,h,  ...)  h
#define COS_PP_ARG9(a,b,c,d,e,f,g,h,i,...)  i

#define COS_PP_STR(...)        COS_PP_STR_ (      __VA_ARGS__)
#define COS_PP_CAT(a,...)      COS_PP_CAT_ (a,    __VA_ARGS__)
#define COS_PP_CAT3(a,b,...)   COS_PP_CAT3_(a,b,  __VA_ARGS__)
#define COS_PP_CAT4(a,b,c,...) COS_PP_CAT4_(a,b,c,__VA_ARGS__)
#define COS_PP_CAT_NARG(a,...) COS_PP_CAT  (a,COS_PP_NARG(__VA_ARGS__))

#define COS_PP_DUP(n,...)      COS_PP_CAT_(COS_PP_DUP_,n)(__VA_ARGS__)

/***********************************************************
 * Implementation
 */

#define COS_PP_STR_(...)        #__VA_ARGS__
#define COS_PP_CAT_(a,...)      a##__VA_ARGS__
#define COS_PP_CAT3_(a,b,...)   a##b##__VA_ARGS__
#define COS_PP_CAT4_(a,b,c,...) a##b##c##__VA_ARGS__

#define COS_PP_DUP_0( ...)
#define COS_PP_DUP_1( ...) __VA_ARGS__
#define COS_PP_DUP_2( ...) COS_PP_DUP_1 (__VA_ARGS__)COS_PP_DUP_1 (__VA_ARGS__)
#define COS_PP_DUP_3( ...) COS_PP_DUP_1 (__VA_ARGS__)COS_PP_DUP_1 (__VA_ARGS__)COS_PP_DUP_1 (__VA_ARGS__)
#define COS_PP_DUP_4( ...) COS_PP_DUP_1 (__VA_ARGS__)COS_PP_DUP_1 (__VA_ARGS__)COS_PP_DUP_2 (__VA_ARGS__)
#define COS_PP_DUP_5( ...) COS_PP_DUP_1 (__VA_ARGS__)COS_PP_DUP_2 (__VA_ARGS__)COS_PP_DUP_2 (__VA_ARGS__)
#define COS_PP_DUP_6( ...) COS_PP_DUP_2 (__VA_ARGS__)COS_PP_DUP_2 (__VA_ARGS__)COS_PP_DUP_2 (__VA_ARGS__)
#define COS_PP_DUP_7( ...) COS_PP_DUP_2 (__VA_ARGS__)COS_PP_DUP_2 (__VA_ARGS__)COS_PP_DUP_3 (__VA_ARGS__)
#define COS_PP_DUP_8( ...) COS_PP_DUP_2 (__VA_ARGS__)COS_PP_DUP_3 (__VA_ARGS__)COS_PP_DUP_3 (__VA_ARGS__)
#define COS_PP_DUP_9( ...) COS_PP_DUP_3 (__VA_ARGS__)COS_PP_DUP_3 (__VA_ARGS__)COS_PP_DUP_3 (__VA_ARGS__)
#define COS_PP_DUP_10(...) COS_PP_DUP_3 (__VA_ARGS__)COS_PP_DUP_3 (__VA_ARGS__)COS_PP_DUP_4 (__VA_ARGS__)
#define COS_PP_DUP_11(...) COS_PP_DUP_3 (__VA_ARGS__)COS_PP_DUP_4 (__VA_ARGS__)COS_PP_DUP_4 (__VA_ARGS__)
#define COS_PP_DUP_12(...) COS_PP_DUP_4 (__VA_ARGS__)COS_PP_DUP_4 (__VA_ARGS__)COS_PP_DUP_4 (__VA_ARGS__)
#define COS_PP_DUP_13(...) COS_PP_DUP_4 (__VA_ARGS__)COS_PP_DUP_4 (__VA_ARGS__)COS_PP_DUP_5 (__VA_ARGS__)
#define COS_PP_DUP_14(...) COS_PP_DUP_4 (__VA_ARGS__)COS_PP_DUP_5 (__VA_ARGS__)COS_PP_DUP_5 (__VA_ARGS__)
#define COS_PP_DUP_15(...) COS_PP_DUP_5 (__VA_ARGS__)COS_PP_DUP_5 (__VA_ARGS__)COS_PP_DUP_5 (__VA_ARGS__)
#define COS_PP_DUP_16(...) COS_PP_DUP_5 (__VA_ARGS__)COS_PP_DUP_5 (__VA_ARGS__)COS_PP_DUP_6 (__VA_ARGS__)
#define COS_PP_DUP_17(...) COS_PP_DUP_5 (__VA_ARGS__)COS_PP_DUP_6 (__VA_ARGS__)COS_PP_DUP_6 (__VA_ARGS__)
#define COS_PP_DUP_18(...) COS_PP_DUP_6 (__VA_ARGS__)COS_PP_DUP_6 (__VA_ARGS__)COS_PP_DUP_6 (__VA_ARGS__)
#define COS_PP_DUP_19(...) COS_PP_DUP_6 (__VA_ARGS__)COS_PP_DUP_6 (__VA_ARGS__)COS_PP_DUP_7 (__VA_ARGS__)
#define COS_PP_DUP_20(...) COS_PP_DUP_6 (__VA_ARGS__)COS_PP_DUP_7 (__VA_ARGS__)COS_PP_DUP_7 (__VA_ARGS__)
#define COS_PP_DUP_21(...) COS_PP_DUP_7 (__VA_ARGS__)COS_PP_DUP_7 (__VA_ARGS__)COS_PP_DUP_7 (__VA_ARGS__)
#define COS_PP_DUP_22(...) COS_PP_DUP_7 (__VA_ARGS__)COS_PP_DUP_7 (__VA_ARGS__)COS_PP_DUP_8 (__VA_ARGS__)
#define COS_PP_DUP_23(...) COS_PP_DUP_7 (__VA_ARGS__)COS_PP_DUP_8 (__VA_ARGS__)COS_PP_DUP_8 (__VA_ARGS__)
#define COS_PP_DUP_24(...) COS_PP_DUP_8 (__VA_ARGS__)COS_PP_DUP_8 (__VA_ARGS__)COS_PP_DUP_8 (__VA_ARGS__)
#define COS_PP_DUP_25(...) COS_PP_DUP_8 (__VA_ARGS__)COS_PP_DUP_8 (__VA_ARGS__)COS_PP_DUP_9 (__VA_ARGS__)
#define COS_PP_DUP_26(...) COS_PP_DUP_8 (__VA_ARGS__)COS_PP_DUP_9 (__VA_ARGS__)COS_PP_DUP_9 (__VA_ARGS__)
#define COS_PP_DUP_27(...) COS_PP_DUP_9 (__VA_ARGS__)COS_PP_DUP_9 (__VA_ARGS__)COS_PP_DUP_9 (__VA_ARGS__)
#define COS_PP_DUP_28(...) COS_PP_DUP_9 (__VA_ARGS__)COS_PP_DUP_9 (__VA_ARGS__)COS_PP_DUP_10(__VA_ARGS__)
#define COS_PP_DUP_29(...) COS_PP_DUP_9 (__VA_ARGS__)COS_PP_DUP_10(__VA_ARGS__)COS_PP_DUP_10(__VA_ARGS__)
#define COS_PP_DUP_30(...) COS_PP_DUP_10(__VA_ARGS__)COS_PP_DUP_10(__VA_ARGS__)COS_PP_DUP_10(__VA_ARGS__)
#define COS_PP_DUP_31(...) COS_PP_DUP_10(__VA_ARGS__)COS_PP_DUP_10(__VA_ARGS__)COS_PP_DUP_11(__VA_ARGS__)
#define COS_PP_DUP_32(...) COS_PP_DUP_10(__VA_ARGS__)COS_PP_DUP_11(__VA_ARGS__)COS_PP_DUP_11(__VA_ARGS__)
#define COS_PP_DUP_33(...) COS_PP_DUP_11(__VA_ARGS__)COS_PP_DUP_11(__VA_ARGS__)COS_PP_DUP_11(__VA_ARGS__)
#define COS_PP_DUP_34(...) COS_PP_DUP_11(__VA_ARGS__)COS_PP_DUP_11(__VA_ARGS__)COS_PP_DUP_12(__VA_ARGS__)
#define COS_PP_DUP_35(...) COS_PP_DUP_11(__VA_ARGS__)COS_PP_DUP_12(__VA_ARGS__)COS_PP_DUP_12(__VA_ARGS__)
#define COS_PP_DUP_36(...) COS_PP_DUP_12(__VA_ARGS__)COS_PP_DUP_12(__VA_ARGS__)COS_PP_DUP_12(__VA_ARGS__)
#define COS_PP_DUP_37(...) COS_PP_DUP_12(__VA_ARGS__)COS_PP_DUP_12(__VA_ARGS__)COS_PP_DUP_13(__VA_ARGS__)
#define COS_PP_DUP_38(...) COS_PP_DUP_12(__VA_ARGS__)COS_PP_DUP_13(__VA_ARGS__)COS_PP_DUP_13(__VA_ARGS__)
#define COS_PP_DUP_39(...) COS_PP_DUP_13(__VA_ARGS__)COS_PP_DUP_13(__VA_ARGS__)COS_PP_DUP_13(__VA_ARGS__)
#define COS_PP_DUP_40(...) COS_PP_DUP_13(__VA_ARGS__)COS_PP_DUP_13(__VA_ARGS__)COS_PP_DUP_14(__VA_ARGS__)
#define COS_PP_DUP_41(...) COS_PP_DUP_13(__VA_ARGS__)COS_PP_DUP_14(__VA_ARGS__)COS_PP_DUP_14(__VA_ARGS__)
#define COS_PP_DUP_42(...) COS_PP_DUP_14(__VA_ARGS__)COS_PP_DUP_14(__VA_ARGS__)COS_PP_DUP_14(__VA_ARGS__)
#define COS_PP_DUP_43(...) COS_PP_DUP_14(__VA_ARGS__)COS_PP_DUP_14(__VA_ARGS__)COS_PP_DUP_15(__VA_ARGS__)
#define COS_PP_DUP_44(...) COS_PP_DUP_14(__VA_ARGS__)COS_PP_DUP_15(__VA_ARGS__)COS_PP_DUP_15(__VA_ARGS__)
#define COS_PP_DUP_45(...) COS_PP_DUP_15(__VA_ARGS__)COS_PP_DUP_15(__VA_ARGS__)COS_PP_DUP_15(__VA_ARGS__)
#define COS_PP_DUP_46(...) COS_PP_DUP_15(__VA_ARGS__)COS_PP_DUP_15(__VA_ARGS__)COS_PP_DUP_16(__VA_ARGS__)
#define COS_PP_DUP_47(...) COS_PP_DUP_15(__VA_ARGS__)COS_PP_DUP_16(__VA_ARGS__)COS_PP_DUP_16(__VA_ARGS__)
#define COS_PP_DUP_48(...) COS_PP_DUP_16(__VA_ARGS__)COS_PP_DUP_16(__VA_ARGS__)COS_PP_DUP_16(__VA_ARGS__)
#define COS_PP_DUP_49(...) COS_PP_DUP_16(__VA_ARGS__)COS_PP_DUP_16(__VA_ARGS__)COS_PP_DUP_17(__VA_ARGS__)
#define COS_PP_DUP_50(...) COS_PP_DUP_16(__VA_ARGS__)COS_PP_DUP_17(__VA_ARGS__)COS_PP_DUP_17(__VA_ARGS__)
#define COS_PP_DUP_51(...) COS_PP_DUP_17(__VA_ARGS__)COS_PP_DUP_17(__VA_ARGS__)COS_PP_DUP_17(__VA_ARGS__)
#define COS_PP_DUP_52(...) COS_PP_DUP_17(__VA_ARGS__)COS_PP_DUP_17(__VA_ARGS__)COS_PP_DUP_18(__VA_ARGS__)
#define COS_PP_DUP_53(...) COS_PP_DUP_17(__VA_ARGS__)COS_PP_DUP_18(__VA_ARGS__)COS_PP_DUP_18(__VA_ARGS__)
#define COS_PP_DUP_54(...) COS_PP_DUP_18(__VA_ARGS__)COS_PP_DUP_18(__VA_ARGS__)COS_PP_DUP_18(__VA_ARGS__)
#define COS_PP_DUP_55(...) COS_PP_DUP_18(__VA_ARGS__)COS_PP_DUP_18(__VA_ARGS__)COS_PP_DUP_19(__VA_ARGS__)
#define COS_PP_DUP_56(...) COS_PP_DUP_18(__VA_ARGS__)COS_PP_DUP_19(__VA_ARGS__)COS_PP_DUP_19(__VA_ARGS__)
#define COS_PP_DUP_57(...) COS_PP_DUP_19(__VA_ARGS__)COS_PP_DUP_19(__VA_ARGS__)COS_PP_DUP_19(__VA_ARGS__)
#define COS_PP_DUP_58(...) COS_PP_DUP_19(__VA_ARGS__)COS_PP_DUP_19(__VA_ARGS__)COS_PP_DUP_20(__VA_ARGS__)
#define COS_PP_DUP_59(...) COS_PP_DUP_19(__VA_ARGS__)COS_PP_DUP_20(__VA_ARGS__)COS_PP_DUP_20(__VA_ARGS__)
#define COS_PP_DUP_60(...) COS_PP_DUP_20(__VA_ARGS__)COS_PP_DUP_20(__VA_ARGS__)COS_PP_DUP_20(__VA_ARGS__)
#define COS_PP_DUP_61(...) COS_PP_DUP_20(__VA_ARGS__)COS_PP_DUP_20(__VA_ARGS__)COS_PP_DUP_21(__VA_ARGS__)
#define COS_PP_DUP_62(...) COS_PP_DUP_20(__VA_ARGS__)COS_PP_DUP_21(__VA_ARGS__)COS_PP_DUP_21(__VA_ARGS__)
#define COS_PP_DUP_63(...) COS_PP_DUP_21(__VA_ARGS__)COS_PP_DUP_21(__VA_ARGS__)COS_PP_DUP_21(__VA_ARGS__)
#define COS_PP_DUP_N( ...) COS_PP_DUP_63(__VA_ARGS__)

#endif // COS_CPP_UTILS_H

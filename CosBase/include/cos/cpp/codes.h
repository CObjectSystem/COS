#ifndef COS_CPP_CODES_H
#define COS_CPP_CODES_H

/*
 o---------------------------------------------------------------------o
 |
 | COS preprocessor coding/decoding macros
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
 | $Id: codes.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: <cos/cpp/codes.h> requires <cos/cos/cos.h>"
#endif 

// predicates
#define COS_PP_ISCODE(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_ISDIGIT(a) \
        COS_PP_1ST(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_ISXDIGIT(a) \
        COS_PP_2ND(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_ISUPPER(a) \
        COS_PP_3RD(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_ISLOWER(a) \
        COS_PP_4TH(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_ISALPHA(a) \
        COS_PP_OR(COS_PP_ISUPPER(a),COS_PP_ISLOWER(a))

#define COS_PP_ISALNUM(a) \
        COS_PP_OR(COS_PP_ISALPHA(a),COS_PP_ISDIGIT(a))

#define COS_PP_ISUNDERSCORE(a) \
        COS_PP_EQ(COS_PP_ORD(a),62)

#define COS_PP_ISSPACE(a) \
        COS_PP_EQ(COS_PP_ORD(a),63)

// conversions
#define COS_PP_ORD(a) \
        COS_PP_5TH(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_TOUPPER(a) \
        COS_PP_6TH(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_TOLOWER(a) \
        COS_PP_7TH(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_SPELL(a) \
        COS_PP_8TH(COS_PP_CAT_(COS_PP_CODE_,a))

#define COS_PP_MORSE(a) \
        COS_PP_9TH(COS_PP_CAT_(COS_PP_CODE_,a))

/***********************************************************
 * Implementation
 */

/* NOTE-DEV: data structure
   isdigit, isxdigit, isupper, islower, ord, upper, lower, NATO, Morse
 */
#define COS_PP_CODE_0 (1, 1, 0, 0,  0, 0, 0, Zero    , .____, )
#define COS_PP_CODE_1 (1, 1, 0, 0,  1, 1, 1, One     , ..___, )
#define COS_PP_CODE_2 (1, 1, 0, 0,  2, 2, 2, Two     , ...__, )
#define COS_PP_CODE_3 (1, 1, 0, 0,  3, 3, 3, Three   , ...._, )
#define COS_PP_CODE_4 (1, 1, 0, 0,  4, 4, 4, Four    , ....., )
#define COS_PP_CODE_5 (1, 1, 0, 0,  5, 5, 5, Five    , _...., )
#define COS_PP_CODE_6 (1, 1, 0, 0,  6, 6, 6, Six     , __..., )
#define COS_PP_CODE_7 (1, 1, 0, 0,  7, 7, 7, Seven   , ___.., )
#define COS_PP_CODE_8 (1, 1, 0, 0,  8, 8, 8, Eight   , ____., )
#define COS_PP_CODE_9 (1, 1, 0, 0,  9, 9, 9, Nine    , _____, )
#define COS_PP_CODE_A (0, 1, 1, 0, 10, A, a, Alfa    , ._   , )
#define COS_PP_CODE_B (0, 1, 1, 0, 11, B, b, Bravo   , _... , )
#define COS_PP_CODE_C (0, 1, 1, 0, 12, C, c, Charlie , _._. , )
#define COS_PP_CODE_D (0, 1, 1, 0, 13, D, d, Delta   , _..  , )
#define COS_PP_CODE_E (0, 1, 1, 0, 14, E, e, Echo    , .    , )
#define COS_PP_CODE_F (0, 1, 1, 0, 15, F, f, Foxtrot , .._. , )
#define COS_PP_CODE_G (0, 0, 1, 0, 16, G, g, Golf    , __.  , )
#define COS_PP_CODE_H (0, 0, 1, 0, 17, H, h, Hotel   , .... , )
#define COS_PP_CODE_I (0, 0, 1, 0, 18, I, i, India   , ..   , )
#define COS_PP_CODE_J (0, 0, 1, 0, 19, J, j, Juliett , .___ , )
#define COS_PP_CODE_K (0, 0, 1, 0, 20, K, k, Kilo    , _._  , )
#define COS_PP_CODE_L (0, 0, 1, 0, 21, L, l, Lima    , ._.. , )
#define COS_PP_CODE_M (0, 0, 1, 0, 22, M, m, Mike    , __   , )
#define COS_PP_CODE_N (0, 0, 1, 0, 23, N, n, November, _.   , )
#define COS_PP_CODE_O (0, 0, 1, 0, 24, O, o, Oscar   , ___  , )
#define COS_PP_CODE_P (0, 0, 1, 0, 25, P, p, Papa    , .__. , )
#define COS_PP_CODE_Q (0, 0, 1, 0, 26, Q, q, Quebec  , __._ , )
#define COS_PP_CODE_R (0, 0, 1, 0, 27, R, r, Romeo   , ._.  , )
#define COS_PP_CODE_S (0, 0, 1, 0, 28, S, s, Sierra  , ...  , )
#define COS_PP_CODE_T (0, 0, 1, 0, 29, T, t, Tango   , _    , )
#define COS_PP_CODE_U (0, 0, 1, 0, 30, U, u, Uniform , .._  , )
#define COS_PP_CODE_V (0, 0, 1, 0, 31, V, v, Victor  , ..._ , )
#define COS_PP_CODE_W (0, 0, 1, 0, 32, W, w, Whiskey , .__  , )
#define COS_PP_CODE_X (0, 0, 1, 0, 33, X, x, Xray    , _.._ , )
#define COS_PP_CODE_Y (0, 0, 1, 0, 34, Y, y, Yankee  , _.__ , )
#define COS_PP_CODE_Z (0, 0, 1, 0, 35, Z, z, Zulu    , __.. , )
#define COS_PP_CODE_a (0, 1, 0, 1, 36, A, a, Alfa    , ._   , )
#define COS_PP_CODE_b (0, 1, 0, 1, 37, B, b, Bravo   , _... , )
#define COS_PP_CODE_c (0, 1, 0, 1, 38, C, c, Charlie , _._. , )
#define COS_PP_CODE_d (0, 1, 0, 1, 39, D, d, Delta   , _..  , )
#define COS_PP_CODE_e (0, 1, 0, 1, 40, E, e, Echo    , .    , )
#define COS_PP_CODE_f (0, 1, 0, 1, 41, F, f, Foxtrot , .._. , )
#define COS_PP_CODE_g (0, 0, 0, 1, 42, G, g, Golf    , __.  , )
#define COS_PP_CODE_h (0, 0, 0, 1, 43, H, h, Hotel   , .... , )
#define COS_PP_CODE_i (0, 0, 0, 1, 44, I, i, India   , ..   , )
#define COS_PP_CODE_j (0, 0, 0, 1, 45, J, j, Juliett , .___ , )
#define COS_PP_CODE_k (0, 0, 0, 1, 46, K, k, Kilo    , _._  , )
#define COS_PP_CODE_l (0, 0, 0, 1, 47, L, l, Lima    , ._.. , )
#define COS_PP_CODE_m (0, 0, 0, 1, 48, M, m, Mike    , __   , )
#define COS_PP_CODE_n (0, 0, 0, 1, 49, N, n, November, _.   , )
#define COS_PP_CODE_o (0, 0, 0, 1, 50, O, o, Oscar   , ___  , )
#define COS_PP_CODE_p (0, 0, 0, 1, 51, P, p, Papa    , .__. , )
#define COS_PP_CODE_q (0, 0, 0, 1, 52, Q, q, Quebec  , __._ , )
#define COS_PP_CODE_r (0, 0, 0, 1, 53, R, r, Romeo   , ._.  , )
#define COS_PP_CODE_s (0, 0, 0, 1, 54, S, s, Sierra  , ...  , )
#define COS_PP_CODE_t (0, 0, 0, 1, 55, T, t, Tango   , _    , )
#define COS_PP_CODE_u (0, 0, 0, 1, 56, U, u, Uniform , .._  , )
#define COS_PP_CODE_v (0, 0, 0, 1, 57, V, v, Victor  , ..._ , )
#define COS_PP_CODE_w (0, 0, 0, 1, 58, W, w, Whiskey , .__  , )
#define COS_PP_CODE_x (0, 0, 0, 1, 59, X, x, Xray    , _.._ , )
#define COS_PP_CODE_y (0, 0, 0, 1, 60, Y, y, Yankee  , _.__ , )
#define COS_PP_CODE_z (0, 0, 0, 1, 61, Z, z, Zulu    , __.. , )
#define COS_PP_CODE__ (0, 0, 0, 0, 62, _, _, Stop    , /    , )
#define COS_PP_CODE_  (0, 0, 0, 0, 63,  ,  , Space   ,      , )

#endif // COS_CPP_CODES_H

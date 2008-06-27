#ifndef COS_CPP_LOGIC_H
#define COS_CPP_LOGIC_H

/*
 o---------------------------------------------------------------------o
 |
 | COS preprocessor logic/relational/predicate macros
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
 | $Id: logic.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cpp/logic.h>"
#endif

// the following macros expect b{1,2} to be 0 or 1
// see COS_PP_BOOL for conversion

// evaluate first element of the following tuple, otherwise evaluate the rest
#define COS_PP_IF(b) \
        COS_PP_CAT_(COS_PP_IF_,b)

#define COS_PP_NOT(b) \
        COS_PP_CAT_(COS_PP_NOT_,b)()

#define COS_PP_AND(b1,b2) \
        COS_PP_CAT3_(COS_PP_AND_,b1,b2)()

#define COS_PP_OR(b1,b2) \
        COS_PP_CAT3_(COS_PP_OR_,b1,b2)()

#define COS_PP_XOR(b1,b2) \
        COS_PP_CAT3_(COS_PP_XOR_,b1,b2)()

// the following macros expect 0 <= m,n <= 63

// m >= n
#define COS_PP_GE(m,n) \
        COS_PP_ISTUPLE(COS_PP_1ST(COS_PP_2ND( \
          COS_PP_SPLIT(n,((),COS_PP_DUPSEQ(m,()),COS_PP_DUPSEQ_N())) )))

// m <= n
#define COS_PP_LE(m,n) \
        COS_PP_GE(n,m)

// m > n
#define COS_PP_GT(m,n) \
        COS_PP_NOT(COS_PP_GE(n,m))

// m < n
#define COS_PP_LT(m,n) \
        COS_PP_NOT(COS_PP_GE(m,n))

// m == n
#define COS_PP_EQ(m,n) \
        COS_PP_AND(COS_PP_GE(m,n),COS_PP_GE(n,m))

// min(m,n)
#define COS_PP_MIN(m,n) \
        COS_PP_IF(COS_PP_GE(m,n))(n,m)

// max(m,n)
#define COS_PP_MAX(m,n) \
        COS_PP_IF(COS_PP_GE(m,n))(m,n)

// the following macros expect 'a' to be concatenable (not a symbol)

// return 1 if 'a' is non-zero, including numbers and tokens, 0 otherwise
#define COS_PP_BOOL(a) \
        COS_PP_NOT(COS_PP_OR(COS_PP_ISZERO(a),COS_PP_ISBLANK(a)))

// return 1 if 'a' is 0 or 1, 0 otherwise
#define COS_PP_ISBOOL(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_ISBOOL_,a))

// return 1 if 'a' is blank (empty), 0 otherwise
#define COS_PP_ISBLANK(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_ISBLANK_,a))

#define COS_PP_ISNTBLANK(a) \
        COS_PP_NOT(COS_PP_ISBLANK(a))

// return 1 if 'a' is 0, 0 otherwise
#define COS_PP_ISZERO(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_ISZERO_,a))

// return 1 if 'a' is 1, 0 otherwise
#define COS_PP_ISONE(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_ISONE_,a))

// return 1 if 'a' is 2, 0 otherwise
#define COS_PP_ISTWO(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_ISTWO_,a))

// return 1 if the token 'a' is a recognized token, 0 otherwise
// the '#define COS_PP_TOKEN_tok ()' define the set of recognized tokens
#define COS_PP_ISTOKEN(a) \
        COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_TOKEN_,a))

// return 1 if its *first* argument is/starts-with a tuple, 0 otherwise
#define COS_PP_ISTUPLE(...) \
        COS_PP_PAIR(COS_PP_ARG1, \
          (COS_PP_CAT(COS_PP_ISTUPLE_RET_,COS_PP_ISTUPLE_TST_ __VA_ARGS__)))

#define COS_PP_ISNTUPLE(...) \
        COS_PP_NOT(COS_PP_ISTUPLE(__VA_ARGS__))

// return 1 if it has no 'effective' argument, 0 otherwise
// WARNING: if the last argument is the name of a function-like macro,
//          the latter will be evaluated
#define COS_PP_NOARG(...) \
        COS_PP_AND(COS_PP_ISTUPLE(__VA_ARGS__ /* Warning macro-eval */ ()), \
                   COS_PP_NOT(COS_PP_ISTUPLE(__VA_ARGS__)))

// return 1 if at least one 'effective' argument is present, 0 otherwise
// WARNING: uses COS_PP_NOARG()
#define COS_PP_1ARG(...) \
        COS_PP_NOT(COS_PP_NOARG(__VA_ARGS__))

// return 1 if at least two arguments are present, 0 otherwise
#define COS_PP_2ARGS(...) \
        COS_PP_NOT(COS_PP_ISONE(COS_PP_NARG(__VA_ARGS__)))

/***********************************************************
 * Implementation
 */

#define COS_PP_IF_0(t, ...) __VA_ARGS__
#define COS_PP_IF_1(t, ...) t

#define COS_PP_NOT_0() 1
#define COS_PP_NOT_1() 0

#define COS_PP_AND_00() 0
#define COS_PP_AND_01() 0
#define COS_PP_AND_10() 0
#define COS_PP_AND_11() 1

#define COS_PP_OR_00() 0
#define COS_PP_OR_01() 1
#define COS_PP_OR_10() 1
#define COS_PP_OR_11() 1

#define COS_PP_XOR_00() 0
#define COS_PP_XOR_01() 1
#define COS_PP_XOR_10() 1
#define COS_PP_XOR_11() 0

#define COS_PP_ISBOOL_0 ()
#define COS_PP_ISBOOL_1 ()
#define COS_PP_ISBLANK_ ()
#define COS_PP_ISZERO_0 ()
#define COS_PP_ISONE_1  ()
#define COS_PP_ISTWO_2  ()

#define COS_PP_ISTUPLE_TST_(...) 1
#define COS_PP_ISTUPLE_RET_COS_PP_ISTUPLE_TST_ 0,
#define COS_PP_ISTUPLE_RET_1 1,

#endif // COS_CPP_LOGIC_H

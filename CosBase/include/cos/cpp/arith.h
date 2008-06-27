#ifndef COS_CPP_ARITH_H
#define COS_CPP_ARITH_H

/*
 o---------------------------------------------------------------------o
 |
 | COS preprocessor arithmetic macros
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
 | $Id: arith.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
 o
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cpp/arith.h>"
#endif 

// increment integer 0 <= n <= COS_PP_MAX_N, saturates at COS_PP_MAX_N
#define COS_PP_INCR(n) \
        COS_PP_1ST(COS_PP_2ND(COS_PP_SPLIT(n,(COS_PP_NUMSEQ_N(),COS_PP_MAX_N))))

// decrement integer 0 <= n <= COS_PP_MAX_N, saturates at zero
#define COS_PP_DECR(n) \
        COS_PP_1ST(COS_PP_2ND(COS_PP_SPLIT(n,(0,0,COS_PP_NUMSEQ_N()))))

// add two integers m >= 0, n >= 0, m+n <= COS_PP_MAX_N
#define COS_PP_ADD(m,n) \
        COS_PP_1ST(COS_PP_2ND(COS_PP_SPLIT(n, \
          COS_PP_2ND(COS_PP_SPLIT(m,(0,COS_PP_NUMSEQ_N()))))))

// substract two integers m >= 0, n >= 0, , m <= n <= COS_PP_MAX_N
#define COS_PP_SUB(m,n) \
        COS_PP_IF(COS_PP_ISZERO(m))(0, \
          COS_PP_1ST(COS_PP_2ND(COS_PP_SPLIT(n,COS_PP_RCONS(COS_PP_REV( \
            COS_PP_1ST(COS_PP_SPLIT(m,(COS_PP_NUMSEQ_N(),)))),0)))))

// multiply two integers m >= 0, n >= 0, (m,n,m*n)<=COS_PP_MAX_N
#define COS_PP_MUL(m,n) \
        COS_PP_IF(COS_PP_OR(COS_PP_ISZERO(m),COS_PP_ISZERO(n)))(0, \
          COS_PP_NARG(COS_PP_PAIR(COS_PP_REST,(COS_PP_DUP(m,COS_PP_DUP(n,,))))))

#endif // COS_CPP_ARITH_H

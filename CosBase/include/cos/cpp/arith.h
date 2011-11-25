#ifndef COS_CPP_ARITH_H
#define COS_CPP_ARITH_H

/**
 * C Object System
 * COS preprocessor arithmetic macros
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

// substract two integers m >= 0, n >= 0, (m,n,m-n) <= COS_PP_MAX_N
#define COS_PP_SUB(m,n) \
        COS_PP_IF(COS_PP_ISZERO(m))(0, \
          COS_PP_1ST(COS_PP_2ND(COS_PP_SPLIT(n,COS_PP_RCONS(COS_PP_REV( \
            COS_PP_1ST(COS_PP_SPLIT(m,(COS_PP_NUMSEQ_N(),)))),0)))))

// multiply two integers m >= 0, n >= 0, (m,n,m*n)<=COS_PP_MAX_N
#define COS_PP_MUL(m,n) \
        COS_PP_IF(COS_PP_OR(COS_PP_ISZERO(m),COS_PP_ISZERO(n)))(0, \
          COS_PP_NARG(COS_PP_PAIR(COS_PP_REST,(COS_PP_DUP(m,COS_PP_DUP(n,,))))))

#endif // COS_CPP_ARITH_H

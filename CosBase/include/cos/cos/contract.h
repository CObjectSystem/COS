#ifndef COS_COS_CONTRACT_H
#define COS_COS_CONTRACT_H

/**
 * C Object System
 * COS contract (macros)
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
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/contract.h>"
#endif

/* NOTE-USER: contract handling

  contract-definition: (function only)
    defcontract( return-type )
      statement-with-contract
    endcontract

  statement-with-contract:
    pre-stmt_opt post-stmt_opt body-stmt

  pre-stmt:
    PRE statement

  post-stmt:
    POST statement

  body-stmt:
    BODY statement

  ensure-invariant-stmt:
    ensure_invariant( object-expr );
    ensure_invariant( object-expr , file , line );

  ensure-stmt:
    ensure( boolean-expr );
    ensure( boolean-expr , string-literal );
    ensure( boolean-expr , file , line );
    ensure( boolean-expr , string-literal , file , line );

  example1:

    defmethod(..)
      PRE
        ensure(pre-cond [, str] [, file, line]);

      POST
        ensure(post-cond [, str] [, file, line]);

      BODY
        // ...
        retmethod(..);

    endmethod

  example2:

    long foo(..) {
      defcontract(long)
      PRE
        ensure(pre-cond [, str] [, file, line]);

      POST
        ensure(post-cond [, str] [, file, line]);

      BODY
        // ...
        retcontract(..);

      endcontract
    }

  where:
  - Contracts are defined in methods by PRE and/or POST sections followed by
    a BODY section as above (i.e. following the D language convention).
  - If BODY returns (i.e. retmethod), the POST section is *still* executed.
  - If BODY throws an exception     , the POST section is *not*   executed.
  - PRE and POST conditions are always ANDed (i.e. conjunction) with inherited
    contracts. This rule differs from the one used in Eiffel
    (see "Behavioral Contracts and Behavioral Subtyping" for motivation)
    Invariants in methods (only) are automatically checked (if activated) after
    the POST section
  - ensure_invariant allows to ensure an invariant explicitely by sending the
    message ginvariant to its argument.

  contract precedences:
  - COS_CONTRACT_PRE  enables PRE sections
  - COS_CONTRACT_POST enables PRE and POST sections
  - COS_CONTRACT_ALL  enables PRE and POST sections plus invariants
*/

/* contract keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_defcontract
#define COS_DISABLE_endcontract
#define COS_DISABLE_retcontract
#define COS_DISABLE_PRE
#define COS_DISABLE_POST
#define COS_DISABLE_BODY
#define COS_DISABLE_ensure
#define COS_DISABLE_ensure_invariant
#endif

#ifndef COS_DISABLE_defcontract
#define defcontract(RET) COS_CTR_DEF(RET)
#endif

#ifndef COS_DISABLE_endcontract
#define endcontract COS_CTR_END
#endif

#ifndef COS_DISABLE_retcontract
#define retcontract(...) COS_CTR_RET(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_PRE
#define PRE COS_CTR_PRE
#endif

#ifndef COS_DISABLE_POST
#define POST COS_CTR_POST
#endif

#ifndef COS_DISABLE_BODY
#define BODY COS_CTR_BODY
#endif

#ifndef COS_DISABLE_ensure_invariant
#define ensure_invariant(...) COS_CTR_INV(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_ensure
#define ensure(...) COS_CTR_ASS_(#__VA_ARGS__,__VA_ARGS__)
#else
#define COS_CTR_ASS(...) COS_CTR_ASS_(#__VA_ARGS__,__VA_ARGS__)
#endif

/***********************************************************
 * Implementation
 */

// contract level
#define COS_CONTRACT_NO   0
#define COS_CONTRACT_PRE  1
#define COS_CONTRACT_POST 2
#define COS_CONTRACT_ALL  3

// contract definition
#define COS_CTR_DEF(RET) \
  { COS_PP_IF(COS_TOK_ISVOID(RET))(,RET _ret;) \
    if (0) { \
      _cos_ctr_exit: \
      return COS_PP_IF(COS_TOK_ISVOID(RET))(,_ret); \
    } \
    COS_CTR_DCL \
    COS_CTR_BEGCTR

// contract end
#define COS_CTR_END \
    COS_CTR_ENDCTR \
    goto _cos_ctr_exit; \
  }

// decl contract
#define COS_CTR_DCL \
  int _cos_ctr_st;
  
// begin contract
#define COS_CTR_BEGCTR \
  _cos_ctr_st = cos_tag_pre; \
  _cos_ctr_beg: {

// end contract
#define COS_CTR_ENDCTR \
  } \
  goto _cos_ctr_end; \
  _cos_ctr_end: \
  if (COS_CONTRACT >= COS_CONTRACT_POST && _cos_ctr_st == cos_tag_redo) { \
    _cos_ctr_st = cos_tag_post; \
    goto _cos_ctr_beg; \
  }

// contract return
#define COS_CTR_RET(...) \
  do { \
    COS_PP_IF(COS_PP_NOARG(__VA_ARGS__))(,_ret = (__VA_ARGS__);) \
    goto _cos_ctr_end; \
  } while (0)

// contract pre
#define COS_CTR_PRE \
    if (COS_CONTRACT >= COS_CONTRACT_PRE && _cos_ctr_st == cos_tag_pre) {

// contract post
#define COS_CTR_POST \
    } \
    if (COS_CONTRACT >= COS_CONTRACT_POST && (_cos_ctr_st == cos_tag_post \
        || (_cos_ctr_st = cos_tag_redo,0))) {

// contract invariant
#define COS_CTR_INVARIANT(C) \
    if (COS_CONTRACT >= COS_CONTRACT_ALL && _cos_ctr_st == cos_tag_post) \
      COS_PP_CAT(cos_contract_invariant,C)(COS_PP_SEQ(COS_SEL_NAME(C)), \
                                           __FILE__,__LINE__);

// contract body
#define COS_CTR_BODY \
      if (_cos_ctr_st == cos_tag_post) goto _cos_ctr_end; \
    }

// test assert
#define COS_CTR_ASS_(...) \
        COS_PP_CAT_NARG(COS_CTR_ASS_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CTR_ASS_2(CS,C) \
        COS_CTR_ASS_3(CS,C,CS)

#define COS_CTR_ASS_3(CS,C,S) \
        COS_CTR_ASS_5(CS,C,S,__FILE__,__LINE__)

#define COS_CTR_ASS_4(CS,C,F,L) \
        COS_CTR_ASS_5(CS,C,#C,F,L) // cannot avoid macro expansion in #C

#define COS_CTR_ASS_5(CS,C,S,F,L) \
        ((void)((C) || (cos_exception_assert(S,F,L),0)))

// test invariant
#define COS_CTR_INV(...) \
        COS_PP_CAT_NARG(COS_CTR_INV_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CTR_INV_1(O) \
        COS_CTR_INV_3(O,__FILE__,__LINE__)

#define COS_CTR_INV_3(O,F,L) \
        ((void)(COS_CONTRACT >= COS_CONTRACT_ALL && \
         (cos_contract_invariant1(O,F,L),0)))

#endif // COS_COS_CONTRACT_H

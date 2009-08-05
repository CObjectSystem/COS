#ifndef COS_COS_CONTRACT_H
#define COS_COS_CONTRACT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS contract (macros)
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
 | $Id: contract.h,v 1.11 2009/08/05 10:54:45 ldeniau Exp $
 |
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

  test-invariant-stmt:
    test_invariant( object-expr );
    test_invariant( object-expr , func, file , line );

  test-assert-stmt:
    test_assert( boolean-expr );
    test_assert( boolean-expr , string-literal );
    test_assert( boolean-expr , func, file , line );
    test_assert( boolean-expr , string-literal , func, file , line );

  example1:

    defmethod(..)
      PRE
        test_assert(pre-cond [, str] [, func, file, line]);

      POST
        test_assert(post-cond [, str] [, func, file, line]);

      BODY
        // ...
        retmethod(..);

    endmethod

  example2:

    long foo(..) {
      defcontract(long)
      PRE
        test_assert(pre-cond [, str] [, func, file, line]);

      POST
        test_assert(post-cond [, str] [, func, file, line]);

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
  - test_invariant allows to test an invariant explicitely by sending the
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
#define COS_DISABLE_test_assert
#define COS_DISABLE_test_invariant
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

#ifndef COS_DISABLE_test_assert
#define test_assert(...) COS_CTR_ASS(#__VA_ARGS__,__VA_ARGS__)
#endif

#ifndef COS_DISABLE_test_invariant
#define test_invariant(...) COS_CTR_INV(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation
 */

// contract level
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
                                           __FUNC__,__FILE__,__LINE__);

// contract body
#define COS_CTR_BODY \
      if (_cos_ctr_st == cos_tag_post) goto _cos_ctr_end; \
    }

// test assert
#define COS_CTR_ASS(...) \
  COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__))( \
        COS_PP_CAT_NARG(COS_CTR_ASS_,__VA_ARGS__)(__VA_ARGS__), \
        COS_CTR_ASS_2(#__VA_ARGS__,__VA_ARGS__))

#define COS_CTR_ASS_2(CS,C) \
        COS_CTR_ASS_3(CS,C,CS)

#define COS_CTR_ASS_3(CS,C,S) \
        COS_CTR_ASS_6(CS,C,S,__FUNC__,__FILE__,__LINE__)

#define COS_CTR_ASS_5(CS,C,M,F,L) \
        COS_CTR_ASS_6(CS,C,#C,M,F,L) // cannot avoid macro expansion in #C

#define COS_CTR_ASS_6(CS,C,S,M,F,L) \
        ((void)((C) || (cos_exception_assert(S,M,F,L),0)))

// test invariant
#define COS_CTR_INV(...) \
        COS_PP_CAT_NARG(COS_CTR_INV_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CTR_INV_1(O) \
        COS_CTR_INV_4(O,__FUNC__,__FILE__,__LINE__)

#define COS_CTR_INV_4(O,M,F,L) \
        ((void)(COS_CONTRACT >= COS_CONTRACT_ALL && \
         (cos_contract_invariant1(O,M,F,L),0)))

#endif // COS_COS_CONTRACT_H

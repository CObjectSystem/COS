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
 | $Id: contract.h,v 1.2 2008/06/29 14:48:28 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/contract.h>"
#endif

/* NOTE-USER: contract handling

  contract-definition:
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
    TestInvariant( object-expr );
    TestInvariant( object-expr , file , line );

  test-assert-stmt:
    TestAssert( boolean-expr );
    TestAssert( boolean-expr , file , line );
    TestAssert( boolean-expr , string-literal );
    TestAssert( boolean-expr , string-literal , file , line );

  test-type-stmt:
    TestType( object-expr , class-name );
    TestType( object-expr , class-name , file , line );
    TestType( object-expr , class-name , string-literal );
    TestType( object-expr , class-name , string-literal , file , line );

  example1:

    defmethod(..)
      PRE {
        TestInvariant(_1 [, file, line]);
        TestAssert(pre-cond [, str] [, file, line]);
      }
      POST {
        TestInvariant(_1 [, file, line]);
        TestAssert(post-cond [, str] [, file, line]);
      }
      BODY {
        // ...
        retmethod(..);
      }
    endmethod

  example2:

    long foo(..) {
      defcontract(long)
      PRE {
        TestAssert(pre-cond [, str] [, file, line]);
      }
      POST {
        TestAssert(post-cond [, str] [, file, line]);
      }
      BODY {
        // ...
        retcontract(..);
      }
      endcontract
    }

  where:
  - Contracts are defined in methods by PRE and/or POST sections followed by
    a BODY section as above (i.e. follow the D language convention).
  - If BODY returns (i.e. retmethod), the POST section is *still* executed.
  - If BODY throws an exception     , the POST section is *not*   executed.
  - PRE and POST conditions are always ANDed (i.e. conjunction) with inherited
    contracts. This rule differs from the one used in Eiffel
    (see "Behavioral Contracts and Behavioral Subtyping" for motivation)
  - TestInvariant sends the message ginvariant to its argument.

  contract precedences:
  - COS_CONTRACT_PRE  enables PRE sections
  - COS_CONTRACT_POST enables PRE and POST sections
  - COS_CONTRACT_ALL  enables PRE and POST sections plus TestInvariant
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
#define COS_DISABLE_TestType
#define COS_DISABLE_TestAssert
#define COS_DISABLE_TestInvariant
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

#ifndef COS_DISABLE_TestType
#define TestType(...) COS_CTR_TYP(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_TestAssert
#define TestAssert(...) COS_CTR_ASS(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_TestInvariant
#define TestInvariant(...) COS_CTR_INV(__VA_ARGS__)
#endif

/* contract precedences:
   ALL (INVARIANT) => POST => PRE
 */
enum { COS_CONTRACT_PRE=1, COS_CONTRACT_POST, COS_CONTRACT_ALL };

/***********************************************************
 * Implementation
 */

// contract states
enum {
  cos_contract_pre_st,
  cos_contract_redo_st,
  cos_contract_post_st
};

// contract definition
#define COS_CTR_DEF(RET) \
  { COS_PP_IF(COS_TOK_ISVOID(RET))(,RET _ret;) \
    if (0) { \
      _cos_ctr_exit: \
      return COS_PP_IF(COS_TOK_ISVOID(RET))(,_ret); \
    } \
    COS_CTR_BEGCTR

// contract end
#define COS_CTR_END \
    COS_CTR_ENDCTR \
    goto _cos_ctr_exit; \
  }

// begin contract
#define COS_CTR_BEGCTR \
  { int _cos_ctr_st = cos_contract_pre_st; \
    _cos_ctr_beg: {

// end contract
#define COS_CTR_ENDCTR \
    } \
    goto _cos_ctr_end; \
    _cos_ctr_end: \
    if (COS_CONTRACT >= COS_CONTRACT_POST && _cos_ctr_st == cos_contract_redo_st) {\
      _cos_ctr_st = cos_contract_post_st; \
      goto _cos_ctr_beg; \
    } \
  }

// contract return
#define COS_CTR_RET(...) \
  do { \
    COS_PP_IF(COS_PP_NOARG(__VA_ARGS__))(,_ret = (__VA_ARGS__);) \
    goto _cos_ctr_end; \
  } while(0)

// contract pre
#define COS_CTR_PRE \
    if (COS_CONTRACT >= COS_CONTRACT_PRE  && _cos_ctr_st == cos_contract_pre_st)

// contract post
#define COS_CTR_POST \
    if (COS_CONTRACT >= COS_CONTRACT_POST && (_cos_ctr_st == cos_contract_post_st \
        || (_cos_ctr_st = cos_contract_redo_st,0)))

// contract body
#define COS_CTR_BODY \
    if (_cos_ctr_st != cos_contract_post_st)

// test type
#define COS_CTR_TYP(...) \
        COS_PP_CAT_NARG(COS_CTR_TYP_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CTR_TYP_2(O,C) \
        COS_CTR_TYP_5(O,C,COS_PP_STR(O is not a C),__FILE__,__LINE__)

#define COS_CTR_TYP_3(O,C,S) \
        COS_CTR_TYP_5(O,C,S,__FILE__,__LINE__)

#define COS_CTR_TYP_4(O,C,F,L) \
        COS_CTR_TYP_5(O,C,COS_PP_STR(O is not a C),F,L)

#define COS_CTR_TYP_5(O,C,S,F,L) \
        COS_CTR_ASS_4(cos_any_id(O) == COS_CLS_NAME(C).Behavior.id,S,F,L)

// test assert
#define COS_CTR_ASS(...) \
        COS_PP_CAT_NARG(COS_CTR_ASS_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CTR_ASS_1(C) \
        COS_CTR_ASS_4(C,COS_PP_STR(C),__FILE__,__LINE__)

#define COS_CTR_ASS_2(C,S) \
        COS_CTR_ASS_4(C,S,__FILE__,__LINE__)

#define COS_CTR_ASS_3(C,F,L) \
        COS_CTR_ASS_4(C,COS_PP_STR(C),F,L)

#define COS_CTR_ASS_4(C,S,F,L) \
        ((void)((C) || (cos_exception_assertLoc(S,F,L),0)))

// test invariant
#define COS_CTR_INV(...) \
        COS_PP_CAT_NARG(COS_CTR_INV_,__VA_ARGS__)(__VA_ARGS__)

#define COS_CTR_INV_1(O) \
        COS_CTR_INV_3(O,__FILE__,__LINE__)

#define COS_CTR_INV_3(O,F,L) \
        ((void)(COS_CONTRACT >= COS_CONTRACT_ALL && \
         (cos_contract_invariantLoc(O,F,L),0)))

#endif // COS_COS_CONTRACT_H

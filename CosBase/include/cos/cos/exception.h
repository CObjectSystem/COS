#ifndef COS_COS_EXCEPTION_H
#define COS_COS_EXCEPTION_H

/*
 o---------------------------------------------------------------------o
 |
 | COS exception (macros)
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
 | $Id: exception.h,v 1.1 2008/06/27 16:17:15 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/exception.h>"
#endif

/* NOTE-USER: exception handling

  try-statement:
    TRY
      statement catch-stmt-list_opt catch-any-stmt_opt finally-stmt_opt
    ENDTRY

  catch-stmt-list:
    catch-stmt
    catch-stmt-list catch-stmt

  catch-stmt:
    CATCH( class-name ) statement
    CATCH( class-name , exception-name_opt ) statement

  catch-any-stmt:
    CATCH_ANY( exception-name_opt ) statement

  finally-stmt:
    FINALLY( exception-name_opt ) statement

  rethrow-statement:
    RETHROW( exception-name_opt );

  throw-statement:
    THROW( object-expr );
    THROW( object-expr , file , line );

  exception-name:
    identifier                                     // C99 6.4.2.1

  example:
    useclass(ExBadType, mExBadAlloc, String);

    TRY
      code which may throw an exception
    CATCH(String [,ex])
      code optionally using local ex, ex_file and ex_line where ex is an
      *instance* of a subclass of String.
        e.g. raised by THROW(gnewWithStr(String, "message"));
    CATCH(mExBadAlloc [,ex])
      code optionally using local ex, ex_file and ex_line where ex is a
      *subclass* of the class ExBadAlloc.
        e.g. raised by THROW(ExBadAlloc)
    CATCH_ANY([ex])
      equivalent to CATCH(Object [,ex]) but slightly more efficient.
    FINALLY([ex])
      cleanup code (always executed) optionally using local ex, ex_file and
      ex_line where ex would be the thrown/rethrown exception object *or* NIL
      if try succeeded. If ex is an instance not already released in a catch
      block, it should be either released or rethrown here.
        e.g. if (ex != NIL) grelease(ex);
    ENDTRY

  where:
  - The semantic of TRY-CATCH-FINALLY blocks is the same as in Java and C#,
    *except* that the use of return (or retmethod), break, continue, goto or
    longjump to jump *inside/outside* of these blocks is *FORBIDDEN*
    (unchecked error!).
  - Throwing exceptions within CATCH and FINALLY blocks is valid. As a matter
    of fact, combining both CATCH and FINALLY blocks in the same TRY-ENDTRY
    scope is equivalent to:

      TRY                     TRY
                                TRY
        ..                        ..
      CATCH(C1)                 CATCH(C1)
        ..                        ..
      CATCH(C2)                 CATCH(C2)
        ..                        ..
      CATCH_ANY()               CATCH_ANY()
        ..                        ..
                                ENDTRY
      FINALLY(E)              FINALLY(E)
        ..                      ..
      ENDTRY                  ENDTRY

    except that:
    - left case is more efficient.
    - right case FINALLY(E) doesn't have access to the inner TRY-ENDTRY
      exception unless it is rethrown.

  - CATCH and FINALLY blocks are optional, but it makes sense to have
    at least one CATCH block. Within these blocks, THROW(E) and RETHROW([E])
    can be freely used.
  - If an uncaught exception reaches ENDTRY, it will be automatically rethrown.
  - If an uncaught exception reaches the end of the program, ex_terminate()
    will be called.
  - THROW() can specify its location (automatic by default) after the
    exception argument (i.e. THROW(ex,file,line)). If the thrown exception is
    NIL, it will be automatically converted into Nil.
*/

/* NOTE-USER: exception protection

  protection-decl:
    PRT( object-name-list );

  unprotection-decl:
    UNPRT( object-name );

  object-name-list:
    object-name
    object-name-list , object-name

  object-name:
    identifier                                     // C99 6.4.2.1

  example1:
    useclass(String);

    OBJ str = gnewWithStr(String,"hello"); PRT(str);
    STR p   = malloc(10);
    OBJ ap  = aAllocPointer(ap); PRT(ap);

    // code using str and s;

    grelease(ap), ap = NIL;
    grelease(str), str = NIL;
    UNPRT(str); // unprotect str and all objects protected after

  example2:
    useclass(String);

    OBJ str = NIL;
    OBJ ap  = NIL;
    STR p   = NULL;
    PRT(str,ap); // protect str *then* ap
    str = gnewWithStr(String,"hello");
    ap  = aAllocPointer(p=malloc(10),free);
    // same as example1

  where:
  - PRT(o,..) protects the object pointer o (not the object pointed) against
    raised exceptions, therefore if the object pointed by o changes before
    UNPRT(), the new object will be automatically protected. If o is not nul,
    grelease(o) will be invoked during stack unwinding. During stack unwinding,
    cos_exception_uncaught() returns a non-zero value, 0 otherwise.
  - UNPRT(o) unprotects o and all objects protected after.
  - PRT()/UNPRT() work like a stack PUSH()/POP() of protected objects.
*/

/* exception keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_TRY
#define COS_DISABLE_CATCH
#define COS_DISABLE_CATCH_ANY
#define COS_DISABLE_FINALLY
#define COS_DISABLE_ENDTRY
#define COS_DISABLE_THROW
#define COS_DISABLE_RETHROW
#define COS_DISABLE_PRT
#define COS_DISABLE_UNPRT
#endif

#ifndef COS_DISABLE_TRY
#define TRY COS_EX_TRY
#endif

#ifndef COS_DISABLE_CATCH
#define CATCH(...) COS_EX_CATCH(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_CATCH_ANY
#define CATCH_ANY(E) COS_EX_CATCH_ANY(E)
#endif

#ifndef COS_DISABLE_FINALLY
#define FINALLY(E) COS_EX_FINALLY(E)
#endif

#ifndef COS_DISABLE_ENDTRY
#define ENDTRY COS_EX_ENDTRY
#endif

#ifndef COS_DISABLE_THROW
#define THROW(...) COS_EX_THROW(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_RETHROW
#define RETHROW(E) COS_EX_RETHROW(E)
#endif

#ifndef COS_DISABLE_PRT
#define PRT(...) COS_EX_PRT(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_UNPRT
#define UNPRT(O) COS_EX_UNPRT(O)
#endif

/***********************************************************
 * Implementation
 */

// try states
enum {
  cos_exception_try_st,
  cos_exception_throw_st,
  cos_exception_catch_st
};

// blocks
#define COS_EX_TRY \
  { \
    /* local exception context */ \
    struct cos_exception_context _ex_lcxt; \
    _ex_lcxt.nxt   = cos_exception_cxt; \
    _ex_lcxt.stk   = 0; \
    _ex_lcxt.unstk = COS_NO; \
    _ex_lcxt.ex    = COS_NIL; \
    /* gobal context updated */ \
    cos_exception_cxt = &_ex_lcxt; \
    /* save jump location */ \
    _ex_lcxt.st = cos_exception_setjmp(_ex_lcxt.buf); \
    if (_ex_lcxt.st == cos_exception_try_st) {

#define COS_EX_CATCH(...) \
        COS_PP_CAT_NARG(COS_EX_CATCH_,__VA_ARGS__)(__VA_ARGS__)

#define COS_EX_CATCH_1(C) \
        COS_EX_CATCH_2(C,)

#define COS_EX_CATCH_2(C,E) \
    } else if (_ex_lcxt.st == cos_exception_throw_st && \
               cos_exception_catch(_ex_lcxt.ex,C)) { \
      COS_PP_IF(COS_PP_ISBLANK(E))(,COS_EX_MAK(E);) \
      int _ex_st_ = (_ex_lcxt.st = cos_exception_catch_st, (void)_ex_st_, 0);

#define COS_EX_CATCH_ANY(E) \
    } else if (_ex_lcxt.st == cos_exception_throw_st) { \
      COS_PP_IF(COS_PP_ISBLANK(E))(,COS_EX_MAK(E);) \
      int _ex_st_ = (_ex_lcxt.st = cos_exception_catch_st, (void)_ex_st_, 0);

#define COS_EX_FINALLY(E) \
    } { \
      COS_PP_IF(COS_PP_ISBLANK(E))(,COS_EX_MAK(E);) \
      /* gobal context updated */ \
      int _ex_cxt_ = (cos_exception_cxt = _ex_lcxt.nxt, (void)_ex_cxt_, 0);

#define COS_EX_ENDTRY \
    } \
    if (cos_exception_cxt == &_ex_lcxt) \
      /* gobal context updated */ \
      cos_exception_cxt = _ex_lcxt.nxt; \
    if ((_ex_lcxt.st & cos_exception_throw_st) != 0) \
      COS_EX_RETHROW(); \
  }

// exception local binding
#define COS_EX_MAK(E) \
  OBJ E = _ex_lcxt.ex; \
  STR COS_PP_CAT(E,_file) = (COS_UNUSED(COS_PP_CAT(E,_file)), _ex_lcxt.file); \
  int COS_PP_CAT(E,_line) = (COS_UNUSED(COS_PP_CAT(E,_line)), _ex_lcxt.line)

// throwing exception
#define COS_EX_THROW(...) \
        COS_PP_CAT_NARG(COS_EX_THROW_,__VA_ARGS__)(__VA_ARGS__)

#define COS_EX_THROW_1(E) \
        COS_EX_THROW_3(E,__FILE__,__LINE__)

#define COS_EX_THROW_3(E,F,L) \
        cos_exception_throwLoc(E,F,L)

#define COS_EX_RETHROW(E) \
        COS_EX_THROW(COS_PP_IF(COS_PP_ISBLANK(E))(_ex_lcxt.ex,E), \
                     _ex_lcxt.file,_ex_lcxt.line)

// pointer protection
#define COS_EX_PRT(...) \
        COS_PP_SEPWITH(COS_PP_MAP((__VA_ARGS__),COS_EX_PRT_1),;)

#define COS_EX_PRT_1(O) \
        struct cos_exception_protect COS_PP_CAT3(_ex_prt_,O,_) = \
          cos_exception_protect(&COS_PP_CAT3(_ex_prt_,O,_), &O)

#define COS_EX_UNPRT(O) \
        (cos_exception_cxt->stk = COS_PP_CAT3(_ex_prt_,O,_).nxt)

// context saving
#ifdef sigsetjmp
#define cos_exception_jmpbuf         sigjmp_buf
#define cos_exception_setjmp(buf)    sigsetjmp (buf,1)
#define cos_exception_lngjmp(buf,st) siglongjmp(buf,st)
#else
#define cos_exception_jmpbuf         jmp_buf
#define cos_exception_setjmp(buf)    setjmp (buf)
#define cos_exception_lngjmp(buf,st) longjmp(buf,st)
#endif

#endif // COS_COS_EXCEPTION_H

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
 | $Id: exception.h,v 1.9 2009/02/25 23:06:39 ldeniau Exp $
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
    FINALLY statement

  rethrow-statement:
    RETHROW();

  throw-statement:
    THROW( object-expr );
    THROW( object-expr , func, file , line );

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
      almost equivalent to CATCH(Object [, ex]).

    FINALLY
      cleanup code (always executed)

    ENDTRY

  where:
  - The semantic of TRY-CATCH-FINALLY blocks is the same as in Java and C#,
    *except* that the use of return (or retmethod), break, continue, goto or
    longjump to jump *inside/outside* of these blocks is *FORBIDDEN*
    (unchecked error!).
  - Throwing exceptions within a TRY-ENDTRY block is valid.

  - CATCH and FINALLY blocks are optional, but it makes sense to have
    at least one CATCH block. Within these blocks, THROW(E) and RETHROW()
    can be freely used.
  - If an uncaught exception reaches ENDTRY, it will be automatically rethrown.
  - If an uncaught exception reaches the end of the program, ex_terminate()
    will be called.
  - THROW() can specify its location (automatic by default) after the
    exception argument (i.e. THROW(ex,file,line)) as well as the reason which
    must be a literal string (i.e. THROW(ex,"out of range")). If the thrown
    exception is NIL, it will be automatically converted into Nil.
*/

/* NOTE-USER: exception protection

  protection-decl:
    PRT( object-name-list );

  extended-protection-decl:
    EPRT( object-name , function );

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
    EPTR(file, gclose); // file allocated somewhere else

    file = gopen(file, "here.txt");
    // code using str and s;

    grelease(ap), ap = 0;
    grelease(str), str = 0;
    UNPRT(str); // unprotect str and all objects protected after

  example2:
    useclass(String);

    OBJ str = 0;
    OBJ ap  = 0;
    STR p   = 0;
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
  - EPRT(o,f) works like PRT but specifies the function to call instead of
    grelease as in PRT if an exception is raised.
  - UNPRT(o) unprotects o and all objects protected after.
  - (E)PRT()/UNPRT() work like a stack PUSH()/POP() of protected objects.
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
#define COS_DISABLE_EPRT
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
#define FINALLY COS_EX_FINALLY
#endif

#ifndef COS_DISABLE_ENDTRY
#define ENDTRY COS_EX_ENDTRY
#endif

#ifndef COS_DISABLE_THROW
#define THROW(...) COS_EX_THROW(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_RETHROW
#define RETHROW() COS_EX_RETHROW()
#endif

#ifndef COS_DISABLE_PRT
#define PRT(...) COS_EX_PRT(__VA_ARGS__)
#endif

#ifndef COS_DISABLE_EPRT
#define EPRT(O,F) COS_EX_EPRT(O,F)
#endif

#ifndef COS_DISABLE_UNPRT
#define UNPRT(O) COS_EX_UNPRT(O)
#endif

/***********************************************************
 * Implementation
 */

// blocks
#define COS_EX_TRY \
  { \
    struct cos_exception_context _cos_ex_lcxt; \
    cos_exception_initContext(&_cos_ex_lcxt); \
    _cos_ex_lcxt.tag = cos_exception_setjmp(_cos_ex_lcxt.buf); \
    if (_cos_ex_lcxt.tag == cos_tag_try) {

#define COS_EX_CATCH(...) \
        COS_PP_CAT_NARG(COS_EX_CATCH_,__VA_ARGS__)(__VA_ARGS__)

#define COS_EX_CATCH_1(C) \
        COS_EX_CATCH_2(C,)

#define COS_EX_CATCH_2(C,E) \
    } else if (_cos_ex_lcxt.tag == cos_tag_throw && \
               cos_exception_catch(_cos_ex_lcxt.ex,C)) { \
      COS_PP_IF(COS_PP_ISBLANK(E))(,COS_EX_MAK(E);) \
      int _cos_ex_tag_ = (_cos_ex_lcxt.tag = cos_tag_catch, (void)_cos_ex_tag_, 0);

#define COS_EX_CATCH_ANY(E) \
    } else if (_cos_ex_lcxt.tag == cos_tag_throw) { \
      COS_PP_IF(COS_PP_ISBLANK(E))(,COS_EX_MAK(E);) \
      int _cos_ex_tag_ = (_cos_ex_lcxt.tag = cos_tag_catch, (void)_cos_ex_tag_, 0);

#define COS_EX_FINALLY \
    } if ( !(_cos_ex_lcxt.tag & cos_tag_finally) ) { \
      int _cos_ex_tag_ = (_cos_ex_lcxt.tag |= cos_tag_finally, (void)_cos_ex_tag_, 0);

#define COS_EX_ENDTRY \
    } \
    cos_exception_deinitContext(&_cos_ex_lcxt); \
  }

// exception local binding
#define COS_EX_MAK(E) \
  OBJ E = _cos_ex_lcxt.ex; \
  STR COS_PP_CAT(E,_func) = (COS_UNUSED(COS_PP_CAT(E,_func)), _cos_ex_lcxt.func); \
  STR COS_PP_CAT(E,_file) = (COS_UNUSED(COS_PP_CAT(E,_file)), _cos_ex_lcxt.file); \
  int COS_PP_CAT(E,_line) = (COS_UNUSED(COS_PP_CAT(E,_line)), _cos_ex_lcxt.line)

// throwing exception
#define COS_EX_THROW(...) \
        COS_PP_CAT_NARG(COS_EX_THROW_,__VA_ARGS__)(__VA_ARGS__)

#define COS_EX_THROW_1(E) \
        COS_EX_THROW_4(E,__FUNC__,__FILE__,__LINE__)

#define COS_EX_THROW_4(E,M,F,L) \
        cos_exception_throw(E,M,F,L)

#define COS_EX_RETHROW() \
        COS_EX_THROW(_cos_ex_lcxt.ex,_cos_ex_lcxt.func,_cos_ex_lcxt.file,_cos_ex_lcxt.line)

// pointer protection
#define COS_EX_PRT(...) \
        COS_PP_SEPWITH(COS_PP_MAP((__VA_ARGS__),COS_EX_PRT_1),;)

#define COS_EX_PRT_1(O) \
        struct cos_exception_protect COS_PP_CAT3(_cos_ex_prt_,O,_) = \
          cos_exception_protect(&COS_PP_CAT3(_cos_ex_prt_,O,_), &O)

#define COS_EX_EPRT(O,F) \
        struct cos_exception_extendedProtect COS_PP_CAT3(_cos_ex_prt_,O,_) = \
          cos_exception_extendedProtect(&COS_PP_CAT3(_cos_ex_prt_,O,_), &O, F)

#define COS_EX_UNPRT(O) \
        ((void)(cos_exception_context()->stk = COS_PP_CAT3(_cos_ex_prt_,O,_).prv))

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

#ifndef COS_FUNCTOR_H
#define COS_FUNCTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (closure and expression)
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
 | $Id: Functor.h,v 1.25 2010/01/07 14:53:51 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// ----- Functor/Expression class cluster

defclass(Expression)
endclass

defclass(Functor, Expression)
  U32 msk;
endclass

defclass(PlaceHolder, Expression)
endclass

// ----- Functor placeholder

defclass(FunArg, PlaceHolder)
  U32 idx;
  FINAL_CLASS
endclass

defclass(FunVar, PlaceHolder)
  OBJ var;
  FINAL_CLASS
endclass

defclass(FunLzy, PlaceHolder)
  OBJ fun;
  U32 cnt;
  FINAL_CLASS
endclass

// ----- Functor expression

defclass(FunExpr, Functor)
  STR str;
endclass

defclass(FunExpr1, FunExpr)
  FUN1 fct;
  OBJ  arg[1];
endclass

defclass(FunExpr2, FunExpr)
  FUN2 fct;
  OBJ  arg[2];
endclass

defclass(FunExpr3, FunExpr)
  FUN3 fct;
  OBJ  arg[3];
endclass

defclass(FunExpr4, FunExpr)
  FUN4 fct;
  OBJ  arg[4];
endclass

defclass(FunExpr5, FunExpr)
  FUN5 fct;
  OBJ  arg[5];
endclass

defclass(FunExpr6, FunExpr)
  FUN6 fct;
  OBJ  arg[6];
endclass

defclass(FunExpr7, FunExpr)
  FUN7 fct;
  OBJ  arg[7];
endclass

defclass(FunExpr8, FunExpr)
  FUN8 fct;
  OBJ  arg[8];
endclass

defclass(FunExpr9, FunExpr)
  FUN9 fct;
  OBJ  arg[9];
endclass

// ----- Functor as function (lightweight optimization)

defclass(Function0, FunExpr)
  FUN0 fct;
endclass

defclass(Function1, FunExpr)
  FUN1 fct;
endclass

defclass(Function2, FunExpr)
  FUN2 fct;
endclass

defclass(Function3, FunExpr)
  FUN3 fct;
endclass

defclass(Function4, FunExpr)
  FUN4 fct;
endclass

defclass(Function5, FunExpr)
  FUN5 fct;
endclass

defclass(Function6, FunExpr)
  FUN6 fct;
endclass

defclass(Function7, FunExpr)
  FUN7 fct;
endclass

defclass(Function8, FunExpr)
  FUN8 fct;
endclass

defclass(Function9, FunExpr)
  FUN9 fct;
endclass

// ----- Composition of functors

defclass(ComposeFun, Functor)
  U32 size;
  OBJ fun[];
endclass

// ----- Iteration of functor

defclass(IterateFun, Functor)
  U32  num;
  OBJ  fun;
  FUN1 fct;
endclass

// ----- automatic constructor

#define aFunctor(...)  ( (OBJ)atFunctor(__VA_ARGS__) )
#define aFunArg(...)   ( (OBJ)atFunArg (__VA_ARGS__) )
#define aFunVar(...)   ( (OBJ)atFunVar (__VA_ARGS__) )
#define aFunLzy(...)   ( (OBJ)atFunLzy (__VA_ARGS__) )
#define aFunLzyN(...)  ( (OBJ)atFunLzyN(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT
#define aFun(...)  aFunctor(__VA_ARGS__)
#define aArg(...)  aFunArg (__VA_ARGS__)
#define aVar(...)  aFunVar (__VA_ARGS__)
#define aLzy(...)  aFunLzy (__VA_ARGS__)

#define aLzy2(...) aFunLzyN(2,__VA_ARGS__)
#define aLzy3(...) aFunLzyN(3,__VA_ARGS__)
#define aLzy4(...) aFunLzyN(4,__VA_ARGS__)
#define aLzy5(...) aFunLzyN(5,__VA_ARGS__)
#define aLzyN(...) aFunLzyN(  __VA_ARGS__)
#endif

// --- placeholders

#ifndef COS_NOPLACEHOLDER
#define __1  aFunArg(0)
#define __2  aFunArg(1)
#define __3  aFunArg(2)
#define __4  aFunArg(3)
#define __5  aFunArg(4)
#define __6  aFunArg(5)
#define __7  aFunArg(6)
#define __8  aFunArg(7)
#define __9  aFunArg(8)
#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Functors

#define atFunctor(...) \
  COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__)) \
    (atFunctorF(__VA_ARGS__),atFunctor0(__VA_ARGS__))

#define atFunctor0(F) \
  ( (struct Functor*)&(struct Function0) { \
    {{ cos_object_auto(Function0), 0 }, COS_PP_STR(F) }, F })

#define atFunctorF(F,...) \
  atFunctorN(COS_PP_NARG(__VA_ARGS__), F, __VA_ARGS__)

#define atFunctorN(N,F,...) \
  COS_PP_CAT(FunExpr_init,N)( &(struct COS_PP_CAT(FunExpr,N)) { \
    {{{ cos_object_auto(COS_PP_CAT(FunExpr,N)) }, 0 }, COS_PP_STR(F) }, \
    F, {__VA_ARGS__} }, __FILE__, __LINE__)

// ----- PlaceHolders

#define atFunArg(IDX) \
  ( &(struct FunArg){ {{ cos_object_auto(FunArg) }}, (IDX) } )

#define atFunVar(VAR) \
  ( &(struct FunVar){ {{ cos_object_auto(FunVar) }}, (VAR) } )

#define atFunLzy(FUN) \
        atFunLzyN(1,FUN)

#define atFunLzyN(N,FUN) \
  ( &(struct FunLzy){ {{ cos_object_auto(FunLzy) }}, (FUN), (N) } )

// ----- initializers

struct Functor* FunExpr_init1(struct FunExpr1*, STR file, int line);
struct Functor* FunExpr_init2(struct FunExpr2*, STR file, int line);
struct Functor* FunExpr_init3(struct FunExpr3*, STR file, int line);
struct Functor* FunExpr_init4(struct FunExpr4*, STR file, int line);
struct Functor* FunExpr_init5(struct FunExpr5*, STR file, int line);
struct Functor* FunExpr_init6(struct FunExpr6*, STR file, int line);
struct Functor* FunExpr_init7(struct FunExpr7*, STR file, int line);
struct Functor* FunExpr_init8(struct FunExpr8*, STR file, int line);
struct Functor* FunExpr_init9(struct FunExpr9*, STR file, int line);

#endif // COS_FUNCTOR_H

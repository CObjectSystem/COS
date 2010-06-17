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
 | $Id: Functor.h,v 1.37 2010/06/17 09:28:25 ldeniau Exp $
 |
*/

#include <cos/Object.h>

/* NOTE-USER: Expression (root class)
   Functor makes the difference between:
    - Variable expression
    - Function expression
    - Message  expression
   An important point is that Functor are _not_ Objects.
*/

// ----- Expression

defclass(Expression, Any)
endclass

// ----- Functor expression

defclass(Functor, Expression)
endclass

defclass(FunExpr, Functor)
  STR str;
  U32 msk;
  I32 max;
endclass

defclass(MsgExpr, Functor)
  SEL sel;
  U32 msk;
  I32 max;
endclass

// ----- Variable expression

defclass(VarExpr, Expression)
endclass

defclass(FunArg, VarExpr)
  I32 idx;
  FINAL_CLASS
endclass

// ----- Function expression

union cos_functor_arg { OBJ obj; I32 idx; };

defclass(FunExpr0, FunExpr)
  FUN0 fct;
endclass

defclass(FunExpr1, FunExpr)
  FUN1 fct;
  union cos_functor_arg arg[1];
endclass

defclass(FunExpr2, FunExpr)
  FUN2 fct;
  union cos_functor_arg arg[2];
endclass

defclass(FunExpr3, FunExpr)
  FUN3 fct;
  union cos_functor_arg arg[3];
endclass

defclass(FunExpr4, FunExpr)
  FUN4 fct;
  union cos_functor_arg arg[4];
endclass

defclass(FunExpr5, FunExpr)
  FUN5 fct;
  union cos_functor_arg arg[5];
endclass

defclass(FunExpr6, FunExpr)
  FUN6 fct;
  union cos_functor_arg arg[6];
endclass

defclass(FunExpr7, FunExpr)
  FUN7 fct;
  union cos_functor_arg arg[7];
endclass

defclass(FunExpr8, FunExpr)
  FUN8 fct;
  union cos_functor_arg arg[8];
endclass

defclass(FunExpr9, FunExpr)
  FUN9 fct;
  union cos_functor_arg arg[9];
endclass

// ----- specializations

defclass(FunExpr11, FunExpr1) endclass
defclass(FunExpr12, FunExpr1) endclass

defclass(FunExpr21, FunExpr2) endclass
defclass(FunExpr22, FunExpr2) endclass
defclass(FunExpr23, FunExpr2) endclass
defclass(FunExpr24, FunExpr2) endclass

defclass(FunExpr31, FunExpr3) endclass
defclass(FunExpr32, FunExpr3) endclass
defclass(FunExpr33, FunExpr3) endclass
defclass(FunExpr34, FunExpr3) endclass
defclass(FunExpr35, FunExpr3) endclass
defclass(FunExpr36, FunExpr3) endclass
defclass(FunExpr37, FunExpr3) endclass
defclass(FunExpr38, FunExpr3) endclass

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

#define aFunctor(...)   ( (OBJ)atFunctor   (__VA_ARGS__) )
#define aFunArg(A)      ( (OBJ)atFunArg    (A)           )

// --- shortcuts

#ifndef COS_NOSHORTCUT
#define aFun(...)   aFunctor(__VA_ARGS__)
#define aArg(A)     aFunArg (A)
#endif

// --- placeholders

#ifndef COS_NOPLACEHOLDER
#define __1  aFunArg(-1)
#define __2  aFunArg(-2)
#define __3  aFunArg(-3)
#define __4  aFunArg(-4)
#define __5  aFunArg(-5)
#define __6  aFunArg(-6)
#define __7  aFunArg(-7)
#define __8  aFunArg(-8)
#define __9  aFunArg(-9)
#endif

/***********************************************************
 * Implementation (private)
 */

// ----- Functors

#define atFunctor(...) \
  COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__)) \
    (atFunctorF(__VA_ARGS__),atFunctor0(__VA_ARGS__))

#define atFunctor0(F) \
  ( (struct Functor*)&(struct FunExpr0) { \
    {{ cos_object_auto(FunExpr0) }, COS_PP_STR(F), 0, 0 }, F })

#define atFunctorF(F,...) \
  atFunctorN(COS_PP_NARG(__VA_ARGS__), F, __VA_ARGS__)

#define atFunctorN(N,F,...) COS_PP_CAT(FunExpr_init,N)( \
   &(struct COS_PP_CAT(FunExpr,N)) { \
    {{ cos_object_auto(COS_PP_CAT(FunExpr,N)) }, COS_PP_STR(F), 0, 0 }, \
      F, { COS_PP_SEQ(COS_PP_MAP((__VA_ARGS__), COS_PP_BRACE)) } })

#define atFunArg(IDX) \
  ( &(struct FunArg){ { cos_object_auto(FunArg) }, (IDX) } )

// ----- initializers

struct Functor* FunExpr_init1(struct FunExpr1*);
struct Functor* FunExpr_init2(struct FunExpr2*);
struct Functor* FunExpr_init3(struct FunExpr3*);
struct Functor* FunExpr_init4(struct FunExpr4*);
struct Functor* FunExpr_init5(struct FunExpr5*);
struct Functor* FunExpr_init6(struct FunExpr6*);
struct Functor* FunExpr_init7(struct FunExpr7*);
struct Functor* FunExpr_init8(struct FunExpr8*);
struct Functor* FunExpr_init9(struct FunExpr9*);

#endif // COS_FUNCTOR_H

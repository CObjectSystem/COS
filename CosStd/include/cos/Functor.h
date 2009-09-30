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
 | $Id: Functor.h,v 1.18 2009/09/30 12:09:54 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// ----- Functor class cluster

defclass(Functor)
endclass

// ----- Functor with non-zero arity

defclass(Functor0,Functor)
  OBJFCT0 fct;
  I32     arity;
endclass

defclass(Functor1,Functor)
  OBJFCT1 fct;
  I32     arity;
  OBJ     arg;
endclass

defclass(Functor2,Functor)
  OBJFCT2 fct;
  I32     arity;
  OBJ     arg[2];
endclass

defclass(Functor3,Functor)
  OBJFCT3 fct;
  I32     arity;
  OBJ     arg[3];
endclass

defclass(Functor4,Functor)
  OBJFCT4 fct;
  I32     arity;
  OBJ     arg[4];
endclass

defclass(Functor5,Functor)
  OBJFCT5 fct;
  I32     arity;
  OBJ     arg[5];
endclass

// ----- Functor with zero arity

defclass(Function, Functor)
endclass

defclass(Function0, Function)
  OBJFCT0 fct;
endclass

defclass(Function1, Function)
  OBJFCT1 fct;
endclass

defclass(Function2, Function)
  OBJFCT2 fct;
endclass

defclass(Function3, Function)
  OBJFCT3 fct;
endclass

defclass(Function4, Function)
  OBJFCT4 fct;
endclass

defclass(Function5, Function)
  OBJFCT5 fct;
endclass

// ----- Composition of functors

defclass(ComposeFun, Functor)
  U32 size;
  OBJ functor[];
endclass

// ----- Iteration of functor

defclass(IterateFun, Functor)
  U32     num;
  OBJ     fun;
  OBJFCT1 fct;
endclass

// ----- automatic constructor

#define aFunctor(...) ( (OBJ)atFunctor(__VA_ARGS__) )

// --- shortcuts

#ifndef COS_NOSHORTCUT

#define aFun(...)  aFunctor(__VA_ARGS__)

#endif

/***********************************************************
 * Implementation (private)
 */

#define atFunctor(...) \
  COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__)) \
    (atFunctorF(__VA_ARGS__),atFunctor0(__VA_ARGS__))

#define atFunctor0(F,...) \
  Functor0_init( &(struct Functor0) { \
    { cos_object_auto(Functor0) }, F, 0 })

#define atFunctorF(F,...) \
  atFunctorN(COS_PP_NARG(__VA_ARGS__),F,__VA_ARGS__)

#define atFunctorN(N,F,...) \
  COS_PP_CAT3(Functor,N,_init)( &(struct COS_PP_CAT(Functor,N)) { \
    { cos_object_auto(COS_PP_CAT(Functor,N)) }, F, -1, \
      COS_PP_IF(COS_PP_ISONE(N))((__VA_ARGS__), { __VA_ARGS__ }) })

// ----- initializers

struct Functor* Functor0_init(struct Functor0*);
struct Functor* Functor1_init(struct Functor1*);
struct Functor* Functor2_init(struct Functor2*);
struct Functor* Functor3_init(struct Functor3*);
struct Functor* Functor4_init(struct Functor4*);
struct Functor* Functor5_init(struct Functor5*);

#endif // COS_FUNCTOR_H

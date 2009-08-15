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
 | $Id: Functor.h,v 1.17 2009/08/15 14:54:57 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// ----- definitions

defclass(Functor)
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

#define atFunctor(F,...) \
  atFunctorN(COS_PP_NARG(__VA_ARGS__),F,__VA_ARGS__)

#define atFunctorN(N,F,...) \
  COS_PP_CAT3(Functor,N,_init)( &(struct COS_PP_CAT(Functor,N)) { \
    { cos_object_auto(COS_PP_CAT(Functor,N)) }, \
    F, -1, COS_PP_IF(COS_PP_ISONE(N))((__VA_ARGS__), { __VA_ARGS__ }) })

// ----- initializers

static inline struct Functor1*
Functor1_init(struct Functor1* fun)
{
  fun->arity = fun->arg != 0;

  if (!fun->arity) // change type to function
    fun->Functor.Object.id = cos_class_id(classref(Function1));

  return fun;
}

static inline struct Functor2*
Functor2_init(struct Functor2* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1);

  if (!fun->arity) // change type to function
    fun->Functor.Object.id = cos_class_id(classref(Function2));

  return fun;
}

static inline struct Functor3*
Functor3_init(struct Functor3* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1)
            | ((fun->arg[2] != 0) << 2);

  if (!fun->arity) // change type to function
    fun->Functor.Object.id = cos_class_id(classref(Function3));

  return fun;
}

static inline struct Functor4*
Functor4_init(struct Functor4* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1)
            | ((fun->arg[2] != 0) << 2)
            | ((fun->arg[3] != 0) << 3);

  if (!fun->arity) // change type to function
    fun->Functor.Object.id = cos_class_id(classref(Function4));

  return fun;
}

static inline struct Functor5*
Functor5_init(struct Functor5* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1)
            | ((fun->arg[2] != 0) << 2)
            | ((fun->arg[3] != 0) << 3)
            | ((fun->arg[4] != 0) << 4);

  if (!fun->arity) // change type to function
    fun->Functor.Object.id = cos_class_id(classref(Function5));

  return fun;
}

#endif // COS_FUNCTOR_H

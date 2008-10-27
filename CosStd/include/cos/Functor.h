#ifndef COS_FUNCTOR_H
#define COS_FUNCTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (closure)
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
 | $Id: Functor.h,v 1.6 2008/10/27 08:31:45 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// ----- definitions

defclass(Functor) endclass

defclass(Functor1,Functor)
  OBJFCT1 fct;
  int     arity;
  OBJ     arg;
endclass

defclass(Functor2,Functor)
  OBJFCT2 fct;
  int     arity;
  OBJ     arg[2];
endclass

defclass(Functor3,Functor)
  OBJFCT3 fct;
  int     arity;
  OBJ     arg[3];
endclass

defclass(Functor4,Functor)
  OBJFCT4 fct;
  int     arity;
  OBJ     arg[4];
endclass

defclass(Functor5,Functor)
  OBJFCT5 fct;
  int     arity;
  OBJ     arg[5];
endclass

// ----- Functor with zero arity

defclass(Function1,Functor) OBJFCT1 fct; endclass
defclass(Function2,Functor) OBJFCT2 fct; endclass
defclass(Function3,Functor) OBJFCT3 fct; endclass
defclass(Function4,Functor) OBJFCT4 fct; endclass
defclass(Function5,Functor) OBJFCT5 fct; endclass

// ----- Sequence of functors (composition)

defclass(Compose,Functor)
  U32  size;
  OBJ *functor;
  OBJ _functor[];
endclass

// ----- Parallel functors

defclass(MultiFunctor2,Functor) // BiFunctor
  OBJ functor[2];
endclass

defclass(MultiFunctor3,Functor)
  OBJ functor[3];
endclass

// ----- automatic constructor

#define aFunctor(F,...) \
  ((OBJ)aFunctorN(COS_PP_NARG(__VA_ARGS__),F,__VA_ARGS__))

#define aMultiFunctor(...) \
  ((OBJ)aMultiFunctorN(COS_PP_NARG(__VA_ARGS__),__VA_ARGS__))

#define aCompose(...) \
  ((OBJ)aComposeN(COS_PP_NARG(__VA_ARGS__),__VA_ARGS__))

#define aFunctorN(N,F,...) \
        COS_PP_CAT3(Functor,N,_init)(&(struct COS_PP_CAT(Functor,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(Functor,N)).Behavior.id, COS_RC_AUTO }}}}, \
         F, -1, COS_PP_IF(COS_PP_ISONE(N))((__VA_ARGS__), { __VA_ARGS__ }) })

#define aComposeN(N,...) \
        (&(struct Compose) { \
        {{{{ COS_CLS_NAME(Compose).Behavior.id, COS_RC_AUTO }}}}, \
         N, (OBJ[]){ COS_PP_SEQ(COS_PP_REV(__VA_ARGS__)) } })

#define aMultiFunctorN(N,...) \
        (&(struct COS_PP_CAT(MultiFunctor,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(MultiFunctor,N)).Behavior.id, COS_RC_AUTO }}}}, \
         { __VA_ARGS__ } })

// ----- automatic constructor initializers

static inline struct Functor1*
Functor1_init(struct Functor1* fun)
{
  fun->arity = fun->arg != 0;

  if (!fun->arity)
    fun->Functor.Object.Any.id = cos_class_id(classref(Function1));

  return fun;
}

static inline struct Functor2*
Functor2_init(struct Functor2* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1);

  if (!fun->arity)
    fun->Functor.Object.Any.id = cos_class_id(classref(Function2));

  return fun;
}

static inline struct Functor3*
Functor3_init(struct Functor3* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1)
            | ((fun->arg[2] != 0) << 2);

  if (!fun->arity)
    fun->Functor.Object.Any.id = cos_class_id(classref(Function3));

  return fun;
}

static inline struct Functor4*
Functor4_init(struct Functor4* fun)
{
  fun->arity = (fun->arg[0] != 0)
            | ((fun->arg[1] != 0) << 1)
            | ((fun->arg[2] != 0) << 2)
            | ((fun->arg[3] != 0) << 3);

  if (!fun->arity)
    fun->Functor.Object.Any.id = cos_class_id(classref(Function4));

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

  if (!fun->arity)
    fun->Functor.Object.Any.id = cos_class_id(classref(Function5));

  return fun;
}

#endif // COS_FUNCTOR_H

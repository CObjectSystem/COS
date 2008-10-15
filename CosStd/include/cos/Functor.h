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
 | $Id: Functor.h,v 1.3 2008/10/15 19:18:06 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// ----- definitions

defclass(Functor)
endclass

defclass(Functor1,Functor)
  int arity;
  FCT1 fct;
  OBJ  arg;
endclass

defclass(Functor2,Functor)
  int arity;
  FCT2 fct;
  OBJ  arg[2];
endclass

defclass(Functor3,Functor)
  int arity;
  FCT3 fct;
  OBJ  arg[3];
endclass

defclass(Functor4,Functor)
  int arity;
  FCT4 fct;
  OBJ  arg[4];
endclass

defclass(Functor5,Functor)
  int arity;
  FCT5 fct;
  OBJ  arg[5];
endclass

// ----- automatic constructor

#define aFunctor(F,...)  ( (OBJ)atFunctor(F,__VA_ARGS__) )
#define atFunctor(F,...) atFunctorN(COS_PP_NARG(__VA_ARGS__),F,__VA_ARGS__)

#define atFunctorN(N,F,...) \
        COS_PP_CAT3(Functor,N,_init)(&(struct COS_PP_CAT(Functor,N)) { \
        {{{ COS_CLS_NAME(COS_PP_CAT(Functor,N)).Behavior.id, COS_RC_AUTO }}}, \
         -1, F, COS_PP_IF(COS_PP_ISONE(N))((__VA_ARGS__), { __VA_ARGS__ }) })

// ----- automatic constructor initializers

static inline struct Functor1*
Functor1_init(struct Functor1* fun) {
  fun->arity = fun->arg != 0;
  return fun;
}

static inline struct Functor2*
Functor2_init(struct Functor2* fun) {
   fun->arity = (fun->arg[0] != 0)
             | ((fun->arg[1] != 0) << 1);
  return fun;
}

static inline struct Functor3*
Functor3_init(struct Functor3* fun) {
   fun->arity = (fun->arg[0] != 0)
             | ((fun->arg[1] != 0) << 1)
             | ((fun->arg[2] != 0) << 2);
  return fun;
}

static inline struct Functor4*
Functor4_init(struct Functor4* fun) {
   fun->arity = (fun->arg[0] != 0)
             | ((fun->arg[1] != 0) << 1)
             | ((fun->arg[2] != 0) << 2)
             | ((fun->arg[3] != 0) << 3);
  return fun;
}

static inline struct Functor5*
Functor5_init(struct Functor5* fun) {
   fun->arity = (fun->arg[0] != 0)
             | ((fun->arg[1] != 0) << 1)
             | ((fun->arg[2] != 0) << 2)
             | ((fun->arg[3] != 0) << 3)
             | ((fun->arg[4] != 0) << 4);
  return fun;
}

#endif // COS_FUNCTOR_H

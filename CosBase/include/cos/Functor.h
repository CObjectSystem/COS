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
 | $Id: Functor.h,v 1.1 2008/06/27 16:17:14 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// ----- definitions

defclass(Functor,Object)
  int arity;
endclass

defclass(Functor1,Functor)
  OBJ (*fct)(OBJ);
  OBJ arg;
endclass

defclass(Functor2,Functor)
  OBJ (*fct)(OBJ,OBJ);
  OBJ arg[2];
endclass

defclass(Functor3,Functor)
  OBJ (*fct)(OBJ,OBJ,OBJ);
  OBJ arg[3];
endclass

defclass(Functor4,Functor)
  OBJ (*fct)(OBJ,OBJ,OBJ,OBJ);
  OBJ arg[4];
endclass

defclass(Functor5,Functor)
  OBJ (*fct)(OBJ,OBJ,OBJ,OBJ,OBJ);
  OBJ arg[5];
endclass

// ----- automatic constructor

#define aFunctor(F,...) \
        aFunctor_(COS_PP_NARG(__VA_ARGS__),F,__VA_ARGS__)

#define aFunctor_(N,F,...) ( (OBJ)&(struct COS_PP_CAT(Functor,N)) {{ \
        {{ COS_CLS_NAME(COS_PP_CAT(Functor,N)).Behavior.id, COS_RC_AUTO }}, \
         -1 }, F, COS_PP_IF(COS_PP_ISONE(N))(__VA_ARGS__, { __VA_ARGS__ }) } )

#endif // COS_FUNCTOR_H

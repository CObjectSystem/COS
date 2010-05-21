#ifndef COS_GEN_FUNCTOR_H
#define COS_GEN_FUNCTOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for functors
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
 | $Id: functor.h,v 1.12 2010/05/21 14:59:09 ldeniau Exp $
 |
*/

#include <cos/Array.h>

defgeneric(OBJ, gnewWithFun0, Functor, (FUN0)fct);
defgeneric(OBJ, gnewWithFun1, Functor, (FUN1)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun2, Functor, (FUN2)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun3, Functor, (FUN3)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun4, Functor, (FUN4)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun5, Functor, (FUN5)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun6, Functor, (FUN6)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun7, Functor, (FUN7)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun8, Functor, (FUN8)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithFun9, Functor, (FUN9)fct, (OBJ*)arg);
defgeneric(OBJ, gnewWithMth , Functor, (SEL )sel, (OBJ*)rcv, (void*)arg);

defgeneric(OBJ, ginitWithFun0, Functor, (FUN0)fct);
defgeneric(OBJ, ginitWithFun1, Functor, (FUN1)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun2, Functor, (FUN2)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun3, Functor, (FUN3)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun4, Functor, (FUN4)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun5, Functor, (FUN5)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun6, Functor, (FUN6)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun7, Functor, (FUN7)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun8, Functor, (FUN8)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithFun9, Functor, (FUN9)fct, (OBJ*)arg);
defgeneric(OBJ, ginitWithMth , Functor, (SEL )sel, (OBJ*)rcv, (void*)arg);

defgeneric(OBJ, gevalEnv, fun, env); // functor evaluation (e.g Lisp funcall)
defgeneric(OBJ, giterate, fun, num); // compose num times functor
defgeneric(OBJ, gcompose, _1);       // compose Array of functors

// ----- eval wrapper

#define geval(...) \
   COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__)) \
     (gevalEnv_N(__VA_ARGS__), gevalEnv_0(__VA_ARGS__))
   
#define gevalEnv_0(fun) \
        gevalEnv(fun, aArray0())

#define gevalEnv_N(fun,...) \
        gevalEnv(fun, aArray(__VA_ARGS__))

// ----- eval inliners

static cos_inline OBJ
geval0(OBJ fun) {
  return gevalEnv(fun, aArray0());
}

static cos_inline OBJ
geval1(OBJ fun, OBJ arg1) {
  return gevalEnv(fun, aArray(arg1));
}

static cos_inline OBJ
geval2(OBJ fun, OBJ arg1, OBJ arg2) {
  return gevalEnv(fun, aArray(arg1, arg2));
}

static cos_inline OBJ
geval3(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3));
}

static cos_inline OBJ
geval4(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4));
}

static cos_inline OBJ
geval5(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5));
}

static cos_inline OBJ
geval6(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5, OBJ arg6) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5, arg6));
}

static cos_inline OBJ
geval7(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
}

static cos_inline OBJ
geval8(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7, OBJ arg8) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
}

static cos_inline OBJ
geval9(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7, OBJ arg8, OBJ arg9) {
  return gevalEnv(fun, aArray(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9));
}

static cos_inline OBJ
gevaln(OBJ fun, OBJ args[], U32 narg) {
  return gevalEnv(fun, aArrayRef(args, narg));
}

#endif // COS_GEN_FUNCTOR_H


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
 | $Id: functor.h,v 1.15 2010/06/13 20:24:46 ldeniau Exp $
 |
*/

#include <cos/Array.h>

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

defgeneric(OBJ, gevalFun , fun);      // functor evaluation (e.g Lisp funcall)
defgeneric(OBJ, giterate , fun, num); // compose num times functor
defgeneric(OBJ, gcompose , _1, _2);   // compose two functors
defgeneric(OBJ, gcomposen, _1);       // compose Array of functors

// ----- eval wrapper

#define geval(...) \
   COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__)) \
     (gevalFun_N(__VA_ARGS__), gevalFun_0(__VA_ARGS__))
   
#define gevalFun_0(fun) \
        gevalFun(fun)

#define gevalFun_N(fun,...) \
        COS_PP_CAT_NARG(geval, __VA_ARGS__)(fun, __VA_ARGS__)

// ----- eval inliners

static cos_inline OBJ
geval0(OBJ fun) {
  return gevalFun(fun);
}

static cos_inline OBJ
geval1(OBJ fun, OBJ arg1) {
  struct cos_functor_context *cxt = cos_functor_ensure(1);
  
  cxt->top[0] = arg1;
  cxt->top += 1;
  OBJ res = gevalFun(fun);
  cxt->top -= 1;
  
  return res;
}

static cos_inline OBJ
geval2(OBJ fun, OBJ arg1, OBJ arg2) {
  struct cos_functor_context *cxt = cos_functor_ensure(2);
  
  cxt->top[0] = arg2;
  cxt->top[1] = arg1;
  cxt->top += 2;
  OBJ res = gevalFun(fun);
  cxt->top -= 2;
  
  return res;
}

static cos_inline OBJ
geval3(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3) {
  struct cos_functor_context *cxt = cos_functor_ensure(3);
  
  cxt->top[0] = arg3;
  cxt->top[1] = arg2;
  cxt->top[2] = arg1;
  cxt->top += 3;
  OBJ res = gevalFun(fun);
  cxt->top -= 3;
  
  return res;
}

static cos_inline OBJ
geval4(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4) {
  struct cos_functor_context *cxt = cos_functor_ensure(4);
  
  cxt->top[0] = arg4;
  cxt->top[1] = arg3;
  cxt->top[2] = arg2;
  cxt->top[3] = arg1;
  cxt->top += 4;
  OBJ res = gevalFun(fun);
  cxt->top -= 4;
  
  return res;
}

static cos_inline OBJ
geval5(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5) {
  struct cos_functor_context *cxt = cos_functor_ensure(5);
  
  cxt->top[0] = arg5;
  cxt->top[1] = arg4;
  cxt->top[2] = arg3;
  cxt->top[3] = arg2;
  cxt->top[4] = arg1;
  cxt->top += 5;
  OBJ res = gevalFun(fun);
  cxt->top -= 5;
  
  return res;
}

static cos_inline OBJ
geval6(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5, OBJ arg6) {
  struct cos_functor_context *cxt = cos_functor_ensure(6);
  
  cxt->top[0] = arg6;
  cxt->top[1] = arg5;
  cxt->top[2] = arg4;
  cxt->top[3] = arg3;
  cxt->top[4] = arg2;
  cxt->top[5] = arg1;
  cxt->top += 6;
  OBJ res = gevalFun(fun);
  cxt->top -= 6;
  
  return res;
}

static cos_inline OBJ
geval7(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7) {
  struct cos_functor_context *cxt = cos_functor_ensure(7);
  
  cxt->top[0] = arg7;
  cxt->top[1] = arg6;
  cxt->top[2] = arg5;
  cxt->top[3] = arg4;
  cxt->top[4] = arg3;
  cxt->top[5] = arg2;
  cxt->top[6] = arg1;
  cxt->top += 7;
  OBJ res = gevalFun(fun);
  cxt->top -= 7;
  
  return res;
}

static cos_inline OBJ
geval8(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7, OBJ arg8) {
  struct cos_functor_context *cxt = cos_functor_ensure(8);
  
  cxt->top[0] = arg8;
  cxt->top[1] = arg7;
  cxt->top[2] = arg6;
  cxt->top[3] = arg5;
  cxt->top[4] = arg4;
  cxt->top[5] = arg3;
  cxt->top[6] = arg2;
  cxt->top[7] = arg1;
  cxt->top += 8;
  OBJ res = gevalFun(fun);
  cxt->top -= 8;
  
  return res;
}

static cos_inline OBJ
geval9(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7, OBJ arg8, OBJ arg9) {
  struct cos_functor_context *cxt = cos_functor_ensure(9);
  
  cxt->top[0] = arg9;
  cxt->top[1] = arg8;
  cxt->top[2] = arg7;
  cxt->top[3] = arg6;
  cxt->top[4] = arg5;
  cxt->top[5] = arg4;
  cxt->top[6] = arg3;
  cxt->top[7] = arg2;
  cxt->top[8] = arg1;
  cxt->top += 9;
  OBJ res = gevalFun(fun);
  cxt->top -= 9;
  
  return res;
}

static cos_inline OBJ
gevaln(OBJ fun, OBJ args[], U32 narg) {
  struct cos_functor_context *cxt = cos_functor_ensure(narg);
  
  for (U32 n = narg; n--;)
    *cxt->top++ = args[n];
  OBJ res = gevalFun(fun);
  cxt->top -= narg;
  
  return res;
}


#endif // COS_GEN_FUNCTOR_H


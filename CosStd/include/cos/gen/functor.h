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
 | $Id: functor.h,v 1.9 2009/12/28 00:18:54 ldeniau Exp $
 |
*/

#include <cos/Array.h>

defgeneric(OBJ, gevalEnv, fun, env); // rank 2
defgeneric(OBJ, gcompose, _1);       // compose Array of functors
defgeneric(OBJ, giterate, fun, num); // compose num times functor
defgeneric(I32, garity  , fun);

// ----- wrapper

#define geval(...) \
   COS_PP_IF(COS_PP_2ARGS(__VA_ARGS__)) \
     (gevalEnv_N(__VA_ARGS__), gevalEnv_0(__VA_ARGS__))
   
#define gevalEnv_0(fun) \
        gevalEnv(fun, aArray0())

#define gevalEnv_N(fun,...) \
        gevalEnv(fun, aArray(__VA_ARGS__))

// ----- inliners

static COS_ALWAYS_INLINE OBJ
geval0(OBJ fun) {
  return gevalEnv(fun, aArray0());
}

static COS_ALWAYS_INLINE OBJ
geval1(OBJ fun, OBJ arg1) {
  return gevalEnv(fun, aArray(arg1));
}

static COS_ALWAYS_INLINE OBJ
geval2(OBJ fun, OBJ arg1, OBJ arg2) {
  return gevalEnv(fun, aArray(arg1, arg2));
}

static COS_ALWAYS_INLINE OBJ
geval3(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3));
}

static COS_ALWAYS_INLINE OBJ
geval4(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4));
}

static COS_ALWAYS_INLINE OBJ
geval5(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5));
}

static COS_ALWAYS_INLINE OBJ
geval6(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5, OBJ arg6) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5, arg6));
}

static COS_ALWAYS_INLINE OBJ
geval7(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
}

static COS_ALWAYS_INLINE OBJ
geval8(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7, OBJ arg8) {
  return gevalEnv(fun, aArray(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
}

static COS_ALWAYS_INLINE OBJ
geval9(OBJ fun, OBJ arg1, OBJ arg2, OBJ arg3, OBJ arg4, OBJ arg5,
                OBJ arg6, OBJ arg7, OBJ arg8, OBJ arg9) {
  return gevalEnv(fun, aArray(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9));
}

static COS_ALWAYS_INLINE OBJ
gevaln(OBJ fun, OBJ args[], U32 narg) {
  return gevalEnv(fun, aArrayRef(args, narg));
}

#endif // COS_GEN_FUNCTOR_H


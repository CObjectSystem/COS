#ifndef COS_FUNCTOR_UTL_H
#define COS_FUNCTOR_UTL_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Functor - utilities
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
 | $Id: Functor_utl.h,v 1.1 2009/12/28 00:18:54 ldeniau Exp $
 |
*/

// mask convention
// 01 -> argument
// 10 -> placeholder
// 00 -> expression

// ----- helper

static COS_ALWAYS_INLINE BOOL
isArg(U32 msk, U32 idx)
{
  return msk & (1 << 2*idx);
}

static COS_ALWAYS_INLINE BOOL
isVar(U32 msk, U32 idx)
{
  return msk & (1 << (2*idx+1));
}

static COS_ALWAYS_INLINE BOOL
isFunc(U32 msk, OBJ arg[], U32 n)
{
  U32 idx;
  
  for (idx = 0; idx < n; idx++)
    if (!(isVar(msk, idx) && idx == (size_t)arg[idx]))
      break;
      
  return idx == n;
}

// ----- "array-like" environment

static COS_ALWAYS_INLINE OBJ
getArg(U32 idx, U32 msk, OBJ *arg, OBJ *var, U32 size, OBJ env)
{
  if (isArg(msk, idx))            // simple argument (free variable)
    return arg[idx];

  if (isVar(msk, idx)) {          // environment index (eval argument)
    size_t i = (size_t)arg[idx];
    test_assert( i < size, "invalid placeholder index" );
    return  var[ i ];
  }

  return gevalEnv(arg[idx], env); // other (expression)
}

// ----- "dictionnary-like" environment

static COS_ALWAYS_INLINE OBJ
getVar(U32 idx, U32 msk, OBJ *arg, OBJ env)
{
  if (isArg(msk, idx))            // simple argument (free variable)
    return arg[idx];

  if (isVar(msk, idx)) {          // environment key (eval argument)
    size_t i = (size_t)arg[idx];
    test_assert( i >= 32, "invalid placeholder key" );
    return ggetAt(env, arg[idx]);
  }

  return gevalEnv(arg[idx], env); // other (expression)
}

// ----- build context mask and compute arity

U32 Functor_getMask (OBJ arg[], U32 n, STR file, int line);
I32 Functor_getArity(OBJ arg[], U32 n, U32 msk);

#endif // COS_FUNCTOR_UTL_H

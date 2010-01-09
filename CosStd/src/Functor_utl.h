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
 | $Id: Functor_utl.h,v 1.8 2010/01/09 16:18:39 ldeniau Exp $
 |
*/

// mask convention
// 001 -> variable free
// 010 -> variable index (placeholder)
// 100 -> variable key   (placeholder)
// 000 -> expression

// ----- helper

#define PAR_UNIT ((U32) 1 << 27)
#define PAR_MASK ((U32)31 << 27)

static inline U32
getPar(U32 msk)
{
  return msk & PAR_MASK;
}

static inline U32
getIdx(OBJ arg)
{
  return (size_t)arg;
}

static inline OBJ
getVar(OBJ arg)
{
  return arg;
}

static inline void
setArg(U32 *msk, U32 idx)
{
  *msk |= 1 << 3*idx;
}

static inline void
setIdx(U32 *msk, U32 idx)
{
  *msk |= 2 << 3*idx;
}

static inline void
setVar(U32 *msk, U32 idx)
{
  *msk |= 4 << 3*idx;
}

static inline BOOL
isArg(U32 msk, U32 idx)
{
  return msk & (1 << 3*idx);
}

static inline BOOL
isIdx(U32 msk, U32 idx)
{
  return msk & (2 << 3*idx);
}

static inline BOOL
isVar(U32 msk, U32 idx)
{
  return msk & (4 << 3*idx);
}

// ----- "array-like" environment

static COS_ALWAYS_INLINE OBJ
getArg(U32 idx, U32 msk, OBJ arg, OBJ var[], U32 size, OBJ env)
{
  if (isArg(msk, idx))        // argument (free variable)
    return arg;

  if (isIdx(msk, idx)) {      // environment index (placeholder)
    U32 i = getIdx(arg);
    test_assert( i < size, "invalid placeholder index" );
    return  var[ i ];
  }

  return gevalEnv(arg, env);  // other (expression)
}

// ----- "dictionnary-like" environment

static COS_ALWAYS_INLINE OBJ
getArgVar(U32 idx, U32 msk, OBJ arg, OBJ env)
{
  if (isArg(msk, idx))        // simple argument (free variable)
    return arg;

  if (isVar(msk, idx))        // environment key (placeholder)
    return ggetAt(env, getVar(arg));

  if (isIdx(msk, idx))        // environment index (placeholder)
    return ggetAtInt(env, getIdx(arg));

  return gevalEnv(arg, env);  // other (expression)
}

// ----- build context mask

void Functor_setMask(U32 *msk, U32 i, OBJ *arg, STR file, int line);

#endif // COS_FUNCTOR_UTL_H

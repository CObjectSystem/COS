/*
 o---------------------------------------------------------------------o
 |
 | COS Functor (Function Expression)
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
 | $Id: Functor_utl.c,v 1.2 2009/12/28 00:43:18 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>

#include "Functor_utl.h"

U32
Functor_getMask(OBJ arg[], U32 n, STR file, int line)
{
  U32 idx, msk = 0;

  for (idx = 0; idx < n; idx++) {

    test_assert( arg[idx], "invalid (null) argument", file, line );

          // environment index (eval argument)
    if (cos_object_isa(arg[idx], classref(Argument))) {
      msk |= 1 << (2*idx+1);
      arg[idx] = (OBJ)(size_t)STATIC_CAST(struct Argument*, arg[idx])->idx;
    }
    
    else  // environment key (eval argument)
    if (cos_object_isa(arg[idx], classref(Variable))) {
      msk |= 1 << (2*idx+1);
      arg[idx] = STATIC_CAST(struct Variable*, arg[idx])->var;
    }

    else  // lazy functor
    if (cos_object_isa(arg[idx], classref(LazyFun))) {
      msk |= 1 << (2*idx);
      arg[idx] = STATIC_CAST(struct LazyFun*, arg[idx])->fun;
    }
    
    else  // simple argument (not a functor)
    if (!cos_object_isKindOf(arg[idx], classref(Functor))) {
      msk |= 1 << (2*idx);
    }
  }

  return msk;
}

I32
Functor_getArity(OBJ arg[], U32 n, U32 msk)
{
  U32 arity = 0;
  
  for (U32 idx = 0; idx < n; idx++) {
    if (isVar(msk, idx)) {
      U32 i = (size_t)arg[idx];
      if (arity < i && i < 32)
        arity = i;
    }

    else
    if (!isArg(msk, idx)) {
      U32 i = garity(arg[idx]);
      if (arity < i && i < 32)
        arity = i;
    }
  }

  return arity;
}



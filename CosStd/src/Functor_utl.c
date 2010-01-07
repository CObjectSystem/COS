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
 | $Id: Functor_utl.c,v 1.6 2010/01/07 00:46:26 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>

#include "Functor_utl.h"

static inline void
setPar(U32 *msk, U32 par)
{
  *msk = (*msk & ~PAR_MASK) | par;
}

U32
Functor_getMask(OBJ arg[], U32 n, STR file, int line)
{
  U32 idx, msk = 0;

  for (idx = 0; idx < n; idx++) {

    test_assert( arg[idx], "invalid (null) argument", file, line );

            // environment index (placeholder)
    if (cos_object_isa(arg[idx], classref(FunArg)))
      setIdx(&msk, idx);
    
    else    // environment key (placeholder)
    if (cos_object_isa(arg[idx], classref(FunVar)))
      setVar(&msk, idx);

    else    // lazy expression (placeholder)
    if (cos_object_isa(arg[idx], classref(FunLzy))) {
      U32 par = STATIC_CAST(struct FunLzy*, arg[idx])->cnt*PAR_UNIT;
      if (par > msk) setPar(&msk, par);
    }
    
    else    // argument (free variable)
    if (!cos_object_isKindOf(arg[idx], classref(Functor)))
      setArg(&msk, idx);
      
    else {  // functor (!)
      U32 par = getPar(getMsk(arg[idx]));
      if (par > msk + PAR_UNIT) setPar(&msk, par - PAR_UNIT);
    }
  }

  return msk;
}


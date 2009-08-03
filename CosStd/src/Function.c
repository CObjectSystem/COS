/*
 o---------------------------------------------------------------------o
 |
 | COS Functions (not closure)
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
 | $Id: Function.c,v 1.3 2009/08/03 12:12:32 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Function.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(GenFunction ,Functor);

makclass(IntFunction ,Functor);
makclass(IntFunction1,IntFunction);
makclass(IntFunction2,IntFunction);
makclass(IntFunction3,IntFunction);
makclass(IntFunction4,IntFunction);
makclass(IntFunction5,IntFunction);

makclass(LngFunction ,Functor    );
makclass(LngFunction1,LngFunction);
makclass(LngFunction2,LngFunction);
makclass(LngFunction3,LngFunction);
makclass(LngFunction4,LngFunction);
makclass(LngFunction5,LngFunction);

makclass(FltFunction ,Functor    );
makclass(FltFunction1,FltFunction);
makclass(FltFunction2,FltFunction);
makclass(FltFunction3,FltFunction);
makclass(FltFunction4,FltFunction);
makclass(FltFunction5,FltFunction);

makclass(CpxFunction ,Functor    );
makclass(CpxFunction1,CpxFunction);
makclass(CpxFunction2,CpxFunction);
makclass(CpxFunction3,CpxFunction);
makclass(CpxFunction4,CpxFunction);
makclass(CpxFunction5,CpxFunction);


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
 | $Id: Function.c,v 1.1 2008/10/27 08:31:45 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Function.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(Function);

makclass(IntFunction1,Function);
makclass(IntFunction2,Function);
makclass(IntFunction3,Function);
makclass(IntFunction4,Function);
makclass(IntFunction5,Function);

makclass(LngFunction1,Function);
makclass(LngFunction2,Function);
makclass(LngFunction3,Function);
makclass(LngFunction4,Function);
makclass(LngFunction5,Function);

makclass(FltFunction1,Function);
makclass(FltFunction2,Function);
makclass(FltFunction3,Function);
makclass(FltFunction4,Function);
makclass(FltFunction5,Function);

makclass(CpxFunction1,Function);
makclass(CpxFunction2,Function);
makclass(CpxFunction3,Function);
makclass(CpxFunction4,Function);
makclass(CpxFunction5,Function);


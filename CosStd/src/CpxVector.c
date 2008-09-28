/*
 o---------------------------------------------------------------------o
 |
 | COS CpxVector
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
 | $Id: CpxVector.c,v 1.1 2008/09/28 22:12:30 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(CpxVector    , Vector);
makclass(CpxVector0   , CpxVector);
makclass(CpxVector1   , CpxVector);
makclass(CpxVector2   , CpxVector);
makclass(CpxVector3   , CpxVector);
makclass(CpxVector4   , CpxVector);
makclass(CpxVector5   , CpxVector);
makclass(CpxVector6   , CpxVector);
makclass(CpxVector7   , CpxVector);
makclass(CpxVector8   , CpxVector);
makclass(CpxVector9   , CpxVector);
makclass(CpxVectorN   , CpxVector);
makclass(CpxSubVector , CpxVector);
makclass(CpxDynVectorN, CpxVector);
makclass(CpxDynVector , CpxDynVectorN);


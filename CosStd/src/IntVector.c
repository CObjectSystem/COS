/*
 o---------------------------------------------------------------------o
 |
 | COS IntVector
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
 | $Id: IntVector.c,v 1.1 2008/09/28 22:12:30 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Vector.h>
#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(IntVector    , Vector);
makclass(IntVector0   , IntVector);
makclass(IntVector1   , IntVector);
makclass(IntVector2   , IntVector);
makclass(IntVector3   , IntVector);
makclass(IntVector4   , IntVector);
makclass(IntVector5   , IntVector);
makclass(IntVector6   , IntVector);
makclass(IntVector7   , IntVector);
makclass(IntVector8   , IntVector);
makclass(IntVector9   , IntVector);
makclass(IntVectorN   , IntVector);
makclass(IntSubVector , IntVector);
makclass(IntDynVectorN, IntVector);
makclass(IntDynVector , IntDynVectorN);


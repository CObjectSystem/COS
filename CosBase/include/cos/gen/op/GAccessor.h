#ifndef COS_GEN_OP_GACCESSOR_H
#define COS_GEN_OP_GACCESSOR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Generic classes for accessors
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
 | $Id: GAccessor.h,v 1.3 2010/05/20 15:48:16 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#include <cos/Object.h>
#endif 

// Generic is a core class, see cos/cos/coscls.h

defclass(G_Accessor, Generic   ) endclass
defclass(G_getAt   , G_Accessor) endclass
defclass(G_putAt   , G_Accessor) endclass
defclass(G_getAtIdx, G_Accessor) endclass
defclass(G_putAtIdx, G_Accessor) endclass
defclass(G_getAtKey, G_Accessor) endclass
defclass(G_putAtKey, G_Accessor) endclass

#endif // COS_GEN_OP_GACCESSOR_H

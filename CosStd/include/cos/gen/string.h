#ifndef COS_GEN_STRING_H
#define COS_GEN_STRING_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for strings
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau*cern.ch
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
 | $Id: string.h,v 1.3 2010/01/15 23:50:13 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// return True or False
defgeneric(OBJ, gisAlnum , _1);
defgeneric(OBJ, gisAlpha , _1);
defgeneric(OBJ, gisBlank , _1);
defgeneric(OBJ, gisCntrl , _1);
defgeneric(OBJ, gisDigit , _1);
defgeneric(OBJ, gisGraph , _1);
defgeneric(OBJ, gisLower , _1);
defgeneric(OBJ, gisPrint , _1);
defgeneric(OBJ, gisPunct , _1);
defgeneric(OBJ, gisSpace , _1);
defgeneric(OBJ, gisUpper , _1);
defgeneric(OBJ, gisXDigit, _1);

// in place
defgeneric(OBJ, gtoLower , _1);
defgeneric(OBJ, gtoUpper , _1);

// remove heading and trailing white spaces
defgeneric(OBJ, gstrip   , _1);

#endif // COS_GEN_STRING_H

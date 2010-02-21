/*
 o---------------------------------------------------------------------o
 |
 | COS Expression (root class)
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
 | $Id: Expression.c,v 1.1 2010/02/21 00:46:24 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/object.h>

// ----- root of most common classes

makclass(Expression, Any);

// ----- new, clone

defmethod(OBJ, gclone, Expression)
  retmethod( ginitWith(galloc(gclass(_1)),_1) );
endmethod

defmethod(OBJ, gnewWith, mExpression, Expression)
  retmethod( ginitWith(galloc(_1),_2) );
endmethod


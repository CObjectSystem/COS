#ifndef COS_NIL_H
#define COS_NIL_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Nil (root class)
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
 | $Id: Nil.h,v 1.1 2008/06/27 16:17:14 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif

/* NOTE-USER: Nil behavior

   Nil is a class-object which aims to be as 'absorbant' as possible,
   that is any message sent to it is absorbed and nothing is executed.
   Nil can also be used as class-predicate to select specific behaviors.
   This 'absorbant' behavior is inherited by other class-predicates.

   Use Nil instead of NIL to set an object reference to a no-object
   state. This will save your application from crash and trace the
   actions performed on Nil. But this may also delay the rise of bugs.

   Remember, message cannot be sent to NIL, but it can to Nil.
*/

defclass(Nil,Any)
endclass

#endif // COS_NIL_H

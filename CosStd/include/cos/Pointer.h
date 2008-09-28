#ifndef COS_POINTER_H
#define COS_POINTER_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Pointer
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
 | $Id: Pointer.h,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Value.h>

// ----- definitions

defclass(Pointer,Value)
  void *ptr;
endclass

defclass(AutoPointer,Pointer)
  void (*pfree)(void*);
endclass

defclass(Function,Value)
  FUNC fct;
endclass

// ----- automatic constructors

#define aPointer(ptr)  ( (OBJ)atPointer(ptr) )
#define atPointer(ptr) ( &(struct Pointer) { \
        {{ COS_CLS_NAME(Pointer).Behavior.id, COS_RC_AUTO }}, \
         (ptr) } )

#define aAutoPointer(ptr, pfree)  ( (OBJ)atAutoPointer(ptr, pfree) )
#define atAutoPointer(ptr, pfree) ( &(struct AutoPointer) {{ \
        {{ COS_CLS_NAME(AutoPointer).Behavior.id, COS_RC_AUTO }}, \
         (ptr) }, (pfree) } )

#define aFunction(fct)  ( (OBJ)atFunction(fct) )
#define atFunction(fct) ( &(struct Function) { \
        {{ COS_CLS_NAME(Function).Behavior.id, COS_RC_AUTO }}, \
         (fct) })

#endif // COS_POINTER_H

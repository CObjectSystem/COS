#ifndef COS_SIZE_H
#define COS_SIZE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Size
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
 | $Id: Size.h,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Value.h>

defclass(Size,Value)
endclass

defclass(Size1,Size)
  U32 size;
endclass

defclass(Size2,Size)
  U32 size[2];
endclass

defclass(Size3,Size)
  U32 size[3];
endclass

defclass(Size4,Size)
  U32 size[4];
endclass

defclass(Size5,Size)
  U32 size[5];
endclass

// ----- automatic constructor

#define aSize(...)  ( (OBJ)atSize(__VA_ARGS__) )
#define atSize(...) atSizeN(COS_PP_NARG(__VA_ARGS__),__VA_ARGS__)

#define atSizeN(N,...) ( &(struct COS_PP_CAT(Size,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(Size,N)).Behavior.id, COS_RC_AUTO }}}}, \
         COS_PP_IF(COS_PP_ISONE(N))((__VA_ARGS__), { __VA_ARGS__ }) } )

#endif // COS_SIZE_H

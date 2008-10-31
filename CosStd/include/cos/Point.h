#ifndef COS_POINT_H
#define COS_POINT_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Point
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
 | $Id: Point.h,v 1.3 2008/10/31 15:19:44 ldeniau Exp $
 |
*/

#define ONLY__COS_VALUE_H
#include <cos/Value.h>

// ----- definitions

defclass(Point, Value)
endclass

defclass(Point1, Point)
  R64 coord;
endclass

defclass(Point2, Point)
  R64 coord[2];
endclass

defclass(Point3, Point)
  R64 coord[3];
endclass

defclass(Point4, Point)
  R64 coord[4];
endclass

defclass(Point5, Point)
  R64 coord[5];
endclass

// ----- automatic constructor

#define aPoint(...)  ( (OBJ)atPoint(__VA_ARGS__) )
#define atPoint(...) atPointN(COS_PP_NARG(__VA_ARGS__),__VA_ARGS__)

#define atPointN(N,...) ( &(struct COS_PP_CAT(Point,N)) { \
        {{{{ COS_CLS_NAME(COS_PP_CAT(Point,N)).Behavior.id, COS_RC_AUTO }}}}, \
         COS_PP_IF(COS_PP_ISONE(N))((__VA_ARGS__), { __VA_ARGS__ }) } )

#endif // COS_POINT_H

#ifndef COS_SEQUENCE_H
#define COS_SEQUENCE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Sequence
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
 | $Id: Sequence.h,v 1.9 2009/06/30 07:59:34 ldeniau Exp $
 |
*/

#include <cos/Container.h>

defclass(Sequence, Container)
endclass

defclass(ValueSequence, Sequence)
endclass

/***********************************************************
 * Implementation (private)
 */

#define Sequence_FSName(NAME,SIZE,...) \
        COS_PP_IF(COS_PP_GE(COS_PP_NARG(__VA_ARGS__),SIZE)) \
                  (COS_PP_CAT(NAME,N), COS_PP_CAT_NARG(NAME,__VA_ARGS__))

#endif // COS_SEQUENCE_H


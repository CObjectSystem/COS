#ifndef COS_GEN_MESSAGE_H
#define COS_GEN_MESSAGE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for messages
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
 | $Id: message.h,v 1.2 2008/12/02 17:32:21 ldeniau Exp $
 |
*/

#include <cos/Object.h>

// errors and forwarding
defgeneric(void, gunrecognizedMessage1, _1);
defgeneric(void, gunrecognizedMessage2, _1, _2);
defgeneric(void, gunrecognizedMessage3, _1, _2, _3);
defgeneric(void, gunrecognizedMessage4, _1, _2, _3, _4);
defgeneric(void, gunrecognizedMessage5, _1, _2, _3, _4, _5);

// behavior, return True or False
defgeneric(OBJ , gunderstandMessage1, _1, (SEL)msg);
defgeneric(OBJ , gunderstandMessage2, _1, _2, (SEL)msg);
defgeneric(OBJ , gunderstandMessage3, _1, _2, _3, (SEL)msg);
defgeneric(OBJ , gunderstandMessage4, _1, _2, _3, _4, (SEL)msg);
defgeneric(OBJ , gunderstandMessage5, _1, _2, _3, _4, _5, (SEL)msg);

// behavior of class instances, return True or False
defgeneric(OBJ , ginstancesUnderstandMessage1, _1, (SEL)msg);
defgeneric(OBJ , ginstancesUnderstandMessage2, _1, _2, (SEL)msg);
defgeneric(OBJ , ginstancesUnderstandMessage3, _1, _2, _3, (SEL)msg);
defgeneric(OBJ , ginstancesUnderstandMessage4, _1, _2, _3, _4, (SEL)msg);
defgeneric(OBJ , ginstancesUnderstandMessage5, _1, _2, _3, _4, _5, (SEL)msg);

#endif // COS_GEN_MESSAGE_H

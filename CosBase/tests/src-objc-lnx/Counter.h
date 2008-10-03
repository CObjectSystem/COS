#ifndef COS_TESTS_COUNTER_H
#define COS_TESTS_COUNTER_H

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - Objective-C Counter class
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
 | $Id: Counter.h,v 1.1 2008/10/03 07:37:31 ldeniau Exp $
 |
*/

#include <objc/Object.h>
#include "Protocols.h"

@interface Counter : Object <Incr,AddTo1,AddTo2,AddTo3,AddTo4> {
@private // states
  U32 _val;
}
- (Counter*) init;
- (U32)      value;
@end

#endif // COS_TESTS_COUNTER_H

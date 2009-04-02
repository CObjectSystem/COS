/*
 o---------------------------------------------------------------------o
 |
 | COS example03 -- main
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
 | $Id: main.c,v 1.1 2009/04/02 23:33:13 ldeniau Exp $
 |
*/

#include "String.h"
#include "generics.h"

#include <stdio.h>
#include <stdlib.h>

useclass(String, AutoRelease);

/*
  NOTE-USER: Garbage Collector
  Modifications to allow AutoRelease pools to behave like manual
  garbage collector, see the paper for OOPSLA'09
*/
defmethod(OBJ, (galloc), mObject)   // around method
  next_method(self);                // allocate
  if (_1 != AutoRelease)            // do not auto-release pools
    cos_object_autoRelease(RETVAL); // auto-release
endmethod

defmethod(void, (grelease), Object)
  if (self->rc > COS_RC_UNIT) self->rc--;
endmethod

defmethod(OBJ, (gautoRelease), Object)
  BOOL is_auto = self->rc == COS_RC_AUTO;
  retmethod( is_auto ? gclone(_1) : _1 );
endmethod

/*
  NOTE-USER: Extend String
  Trace string init/deinit
*/
defmethod(OBJ, (gdeinit), String)
  printf("string deinit '%s'\n", self->str); 
  next_method(self); // deinit
endmethod

defmethod(OBJ, (ginitWithStr), String, (STR)str)
  next_method(self, str); // init
  printf("string init '%s'\n", self->str); 
endmethod

/*
 NOTE-USER: Example 02

 test-I:
   run with valgrind or equivalent to check for memory leaks

 test-II:
   remove the pool (gnew, gsize, grelease) to "see" the default pool in action
   run with valgrind or equivalent to check for memory leaks

 test-III:
   uncomment the cos_logmsg_set to understand what is done
*/

int main(void)
{
  // cos_logmsg_set(COS_LOGMSG_TRACE); // trace ALL messages

  OBJ pool = gnew(AutoRelease);
  OBJ obj;
  int i;

  for(i = 0; i < 10; i++) {
    char buf[128];

    sprintf(buf, "string no %d", i);
    obj = gnewWithStr(String, buf); // autoreleased
    grelease(obj); // not destroyed (do nothing)
  }

  printf("pool size = %u\n", gsize(pool));
  
  grelease(pool); // pool specialization, collect the strings

  return EXIT_SUCCESS;
}

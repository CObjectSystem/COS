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
 | $Id: main.c,v 1.4 2010/03/22 20:53:24 ldeniau Exp $
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
  Note: the class Any has been added (resurrected) after the paper
*/
defmethod(OBJ, (galloc), mAny)   // around method
  next_method(self);             // allocate
  gautoRelease(method_retval);   // auto-release
endmethod

defmethod(void, (gdelete), Any)
endmethod

defmethod(OBJ, (gautoDelete), Any)
  retmethod( self->_rc == COS_RC_AUTO ? gclone(_1) : _1 );
endmethod

defmethod(OBJ, (gretain), Any)
  next_method(self);
  if (self->_rc == COS_RC_AUTO)
    method_retval = gretain(method_retval); // once more for auto objects
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
   remove the pool (gnew, gsize, gdelete) to "see" the default pool in action
   run with valgrind or equivalent to check for memory leaks

 test-III:
   uncomment the cos_logmsg_set to understand what is done
*/

int main(void)
{
  // cos_logmsg_setLevel(COS_LOGMSG_TRACE); // trace ALL messages

  OBJ pool = gnew(AutoRelease);
  OBJ obj;
  int i;

  for(i = 0; i < 10; i++) {
    char buf[128];

    sprintf(buf, "string no %d", i);
    obj = gnewWithStr(String, buf); // autoReleased
    gdelete(obj);                   // do nothing
  }

  printf("pool size = %u\n", gsize(pool));
  
  gdelete(pool); // pool specialization, collect the strings

  return EXIT_SUCCESS;
}

/*
 o---------------------------------------------------------------------o
 |
 | COS Functor as Function
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
 | $Id: Functor_fct.c,v 1.3 2009/09/30 12:09:58 ldeniau Exp $
 |
*/

#include <cos/Functor.h>
#include <cos/gen/object.h>
#include <cos/gen/functor.h>

makclass(Function , Functor);
makclass(Function0, Function);
makclass(Function1, Function);
makclass(Function2, Function);
makclass(Function3, Function);
makclass(Function4, Function);
makclass(Function5, Function);

// ----- type compatibility within the class cluster

STATIC_ASSERT(functor0_to_function0_compatibility,
              COS_FIELD_COMPATIBILITY(Function0,Functor0,fct));

STATIC_ASSERT(functor1_to_function1_compatibility,
              COS_FIELD_COMPATIBILITY(Function1,Functor1,fct));

STATIC_ASSERT(functor2_to_function2_compatibility,
              COS_FIELD_COMPATIBILITY(Function2,Functor2,fct));

STATIC_ASSERT(functor3_to_function3_compatibility,
              COS_FIELD_COMPATIBILITY(Function3,Functor3,fct));

STATIC_ASSERT(functor4_to_function4_compatibility,
              COS_FIELD_COMPATIBILITY(Function4,Functor4,fct));

STATIC_ASSERT(functor5_to_function5_compatibility,
              COS_FIELD_COMPATIBILITY(Function5,Functor5,fct));

// ----- ctors

defmethod(OBJ, ginitWith, Function0, Function0)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function1, Function1)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function2, Function2)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function3, Function3)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function4, Function4)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Function5, Function5)
  self->fct = self2->fct;
  retmethod(_1);
endmethod

// ----- arity

defmethod(I32, garity, Function0)
  retmethod(0);
endmethod

defmethod(I32, garity, Function1)
  retmethod(1);
endmethod

defmethod(I32, garity, Function2)
  retmethod(2);
endmethod

defmethod(I32, garity, Function3)
  retmethod(3);
endmethod

defmethod(I32, garity, Function4)
  retmethod(4);
endmethod

defmethod(I32, garity, Function5)
  retmethod(5);
endmethod

// ----- eval

defmethod(OBJ, geval0, Function0)
  retmethod(self->fct());
endmethod

defmethod(OBJ, geval1, Function1, (OBJ)arg1)
  retmethod(self->fct(arg1));
endmethod

defmethod(OBJ, geval2, Function2, (OBJ)arg1, (OBJ)arg2)
  retmethod(self->fct(arg1,arg2));
endmethod

defmethod(OBJ, geval3, Function3, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3)
  retmethod(self->fct(arg1,arg2,arg3));
endmethod

defmethod(OBJ, geval4, Function4, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4)
  retmethod(self->fct(arg1,arg2,arg3,arg4));
endmethod

defmethod(OBJ, geval5, Function5, (OBJ)arg1, (OBJ)arg2, (OBJ)arg3, (OBJ)arg4, (OBJ)arg5)
  retmethod(self->fct(arg1,arg2,arg3,arg4,arg5));
endmethod



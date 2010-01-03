/*
 o---------------------------------------------------------------------o
 |
 | COS Class
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
 | $Id: Class.c,v 1.7 2010/01/03 11:02:39 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Class.h>
#include <cos/prp/object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>
#include <cos/gen/value.h>

// -----

makclass(Class, Behavior);

// ----- properties (read-only)

defproperty(Class, (spr)superClass, (OBJ));

// ----- direct getters

defmethod(STR, gstr, Class)
  retmethod( self->str );
endmethod

defmethod(U32, gsize, Class)
  retmethod( self->isz );
endmethod

defmethod(OBJ, gsuperClass, Class)
  retmethod( (OBJ)self->spr );
endmethod

// ----- behavior

// ----- rank 1

defmethod(OBJ, ginstancesUnderstandMessage1, Class, (SEL)msg)
  retmethod(cos_method_understand1(msg,
                                   self1->Behavior.id) ? True : False);
endmethod

// ----- rank 2

defmethod(OBJ, ginstancesUnderstandMessage2, Class, Class, (SEL)msg)
  retmethod(cos_method_understand2(msg,
                                   self1->Behavior.id,
                                   self2->Behavior.id) ? True : False);
endmethod

// ----- rank 3

defmethod(OBJ, ginstancesUnderstandMessage3, Class, Class, Class, (SEL)msg)
  retmethod(cos_method_understand3(msg,
                                   self1->Behavior.id,
                                   self2->Behavior.id,
                                   self3->Behavior.id) ? True : False);
endmethod

// ----- rank 4

defmethod(OBJ, ginstancesUnderstandMessage4, Class, Class, Class, Class,
                                             (SEL)msg)
  retmethod(cos_method_understand4(msg,
                                   self1->Behavior.id,
                                   self2->Behavior.id,
                                   self3->Behavior.id,
                                   self4->Behavior.id) ? True : False);
endmethod

// ----- rank 5

defmethod(OBJ, ginstancesUnderstandMessage5, Class, Class, Class, Class, Class,
                                             (SEL)msg)
  retmethod(cos_method_understand5(msg,
                                   self1->Behavior.id,
                                   self2->Behavior.id,
                                   self3->Behavior.id,
                                   self4->Behavior.id,
                                   self5->Behavior.id) ? True : False);
endmethod

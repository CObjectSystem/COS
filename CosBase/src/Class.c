/**
 * C Object System
 * COS Class
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

defmethod(OBJ, ginstancesUnderstandMessage1, Class, (SEL)sel)
  retmethod(cos_method_understand1(sel,
                                   self1->Behavior.id) ? True : False);
endmethod

// ----- rank 2

defmethod(OBJ, ginstancesUnderstandMessage2, Class, Class, (SEL)sel)
  retmethod(cos_method_understand2(sel,
                                   self1->Behavior.id,
                                   self2->Behavior.id) ? True : False);
endmethod

// ----- rank 3

defmethod(OBJ, ginstancesUnderstandMessage3, Class, Class, Class, (SEL)sel)
  retmethod(cos_method_understand3(sel,
                                   self1->Behavior.id,
                                   self2->Behavior.id,
                                   self3->Behavior.id) ? True : False);
endmethod

// ----- rank 4

defmethod(OBJ, ginstancesUnderstandMessage4, Class, Class, Class, Class,
                                             (SEL)sel)
  retmethod(cos_method_understand4(sel,
                                   self1->Behavior.id,
                                   self2->Behavior.id,
                                   self3->Behavior.id,
                                   self4->Behavior.id) ? True : False);
endmethod

// ----- rank 5

defmethod(OBJ, ginstancesUnderstandMessage5, Class, Class, Class, Class, Class,
                                             (SEL)sel)
  retmethod(cos_method_understand5(sel,
                                   self1->Behavior.id,
                                   self2->Behavior.id,
                                   self3->Behavior.id,
                                   self4->Behavior.id,
                                   self5->Behavior.id) ? True : False);
endmethod

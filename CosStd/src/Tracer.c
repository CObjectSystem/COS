/*
 o---------------------------------------------------------------------o
 |
 | COS Tracer (proxy)
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
 | $Id: Tracer.c,v 1.9 2009/09/21 09:51:05 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Tracer.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>
#include <cos/gen/init.h>

// -----

makclass(Tracer,Proxy);

// -----

static void
trace(struct Tracer *self, SEL sel, OBJ obj[], int pos)
{
  char buf[128];
  cos_trace("<Tracer:%s:%d> sending message %s to self%d (%p)",
            self->file, self->line,
            cos_method_call(sel,obj,buf,sizeof buf),
            pos, (void*)self->Proxy.obj);
}

// ----- constructor

defmethod(OBJ, ginitWithLoc, Tracer, Object, (STR)func, (STR)file, (int)line)
  defnext(OBJ, ginitWith, Tracer, Object);
  
  next_method(self, self2);
  self->func = func ? func : "";
  self->file = file ? file : "";
  self->line = line;
endmethod

// ----- behavior

// ----- rank 1

defmethod(void, gunrecognizedMessage1, Tracer)
  trace(self, _sel, (OBJ[]){self->Proxy.obj}, 1);
  next_method(self);
endmethod

// ----- rank 2

defmethod(void, gunrecognizedMessage2, Tracer, Object)
  trace(self, _sel, (OBJ[]){self->Proxy.obj, _2}, 1);
  next_method(self,self2);
endmethod

defmethod(void, gunrecognizedMessage2, Object, Tracer)
  trace(self2, _sel, (OBJ[]){_1, self2->Proxy.obj}, 2);
  next_method(self,self2);
endmethod

// ----- rank 3

defmethod(void, gunrecognizedMessage3, Tracer, Object, Object)
  trace(self, _sel, (OBJ[]){self->Proxy.obj, _2, _3}, 1);
  next_method(self,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Tracer, Object)
  trace(self2, _sel, (OBJ[]){_1, self2->Proxy.obj, _3}, 2);
  next_method(self,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Tracer)
  trace(self3, _sel, (OBJ[]){_1, _2, self3->Proxy.obj}, 3);
  next_method(self,self2,self3);
endmethod

// ----- rank 4

defmethod(void, gunrecognizedMessage4, Tracer, Object, Object, Object)
  trace(self, _sel, (OBJ[]){self->Proxy.obj, _2, _3, _4}, 1);
  next_method(self,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Tracer, Object, Object)
  trace(self2, _sel, (OBJ[]){_1, self2->Proxy.obj, _3, _4}, 2);
  next_method(self,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Tracer, Object)
  trace(self3, _sel, (OBJ[]){_1, _2, self3->Proxy.obj, _4}, 3);
  next_method(self,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Tracer)
  trace(self4, _sel, (OBJ[]){_1, _2, _3, self4->Proxy.obj}, 4);
  next_method(self,self2,self3,self4);
endmethod

// ----- rank 5

defmethod(void, gunrecognizedMessage5, Tracer, Object, Object, Object, Object)
  trace(self, _sel, (OBJ[]){self->Proxy.obj, _2, _3, _4, _5}, 1);
  next_method(self,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Tracer, Object, Object, Object)
  trace(self2, _sel, (OBJ[]){_1, self2->Proxy.obj, _3, _4, _5}, 2);
  next_method(self,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Tracer, Object, Object)
  trace(self3, _sel, (OBJ[]){_1, _2, self3->Proxy.obj, _4, _5}, 3);
  next_method(self,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Tracer, Object)
  trace(self4, _sel, (OBJ[]){_1, _2, _3, self4->Proxy.obj, _5}, 4);
  next_method(self,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Tracer)
  trace(self5, _sel, (OBJ[]){_1, _2, _3, _4, self5->Proxy.obj}, 5);
  next_method(self,self2,self3,self4,self5);
endmethod

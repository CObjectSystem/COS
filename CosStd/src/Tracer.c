/**
 * C Object System
 * COS Tracer (proxy)
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

defmethod(OBJ, ginitWithLoc, Tracer, Object, (STR)file, (int)line)
  defnext(OBJ, ginitWith, Tracer, Object);
  
  next_method(self, self2);
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

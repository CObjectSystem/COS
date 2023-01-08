/**
 * C Object System
 * COS Vector template - Lazy dynamic vector
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

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// -----

makclass(TL, TD);

// -----

useclass(TL);

// ----- constructors

defalias (OBJ, (ginitWith)gnewWith, TP, Functor);
defmethod(OBJ,  ginitWith         , TP, Functor) // generator
  retmethod(ginitWith3(galloc(TL),_2,aTRef(0,0),aInt(0)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Functor, T);
defmethod(OBJ,  ginitWith2          , TP, Functor, T) // generator
  retmethod(ginitWith3(galloc(TL),_2,_3,aInt(self3->size*2)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, TP, Functor, Int);
defmethod(OBJ,  ginitWith2          , TP, Functor, Int) // generator
  retmethod(ginitWith3(galloc(TL),_2,aTRef(0,0),_3));
endmethod

defalias (OBJ, (ginitWith3)gnewWith3, TP, Functor, T, Int);
defmethod(OBJ,  ginitWith3          , TP, Functor, T, Int) // generator
  retmethod(ginitWith3(galloc(TL),_2,_3,_4));
endmethod

defmethod(OBJ,  ginitWith3, TL, Functor, T, Int) // generator
  defnext(OBJ,  ginitWith , TL, Int); // forward to dynamic array
  
  next_method(self, self4);

  PRT(_1);
  self->generator = gretain(_2);

  if (self3->size > 0)
    gappend(_1,_3);

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, TL)
  if (self->generator)          // take care of protection cases
    grelease(self->generator);
  next_method(self);
  retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, TL)
  if (self->generator)
    grelease(self->generator);
  next_method(self);
endmethod

// ----- getter

defmethod(OBJ, ggetAt, TL, Int)
  struct T *vec = &self->TD.TF.T;
  U32 i = Range_index(self2->value, vec->size);

  while (vec->size <= i)
    gappend(_1, geval(self->generator));

  retmethod( gautoRelease(VALOBJ(vec->value[i*vec->stride])) );
endmethod

// NOTE-TODO: other getters?


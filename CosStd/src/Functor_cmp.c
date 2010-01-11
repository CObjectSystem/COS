/*
 o---------------------------------------------------------------------o
 |
 | COS Functor composition
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
 | $Id: Functor_cmp.c,v 1.7 2010/01/11 14:22:11 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include "Array_utl.h"

// -----

useclass(ComposeFun);

// ----- ctors

static inline struct ComposeFun*
ComposeFun_alloc(U32 size)
{
  OBJ _cmp = gallocWithSize(ComposeFun, size * sizeof(OBJ));
  struct ComposeFun *cmp = STATIC_CAST(struct ComposeFun*, _cmp);

  cmp->size = 0;
  
  return cmp;
}

defmethod(OBJ, galloc, pmComposeFun)
  retmethod(_1); // lazy alloc
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmComposeFun, ComposeFun);
defmethod(OBJ,  ginitWith         , pmComposeFun, ComposeFun) // clone
  struct ComposeFun* cpy = ComposeFun_alloc(self2->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);
  
  cpy->Functor.msk = self2->Functor.msk;
  copy(cpy->fun,1,&cpy->size,self2->fun,1,self2->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmComposeFun, Array);
defmethod(OBJ,  ginitWith         , pmComposeFun, Array) // copy
  struct ComposeFun* cpy = ComposeFun_alloc(self2->size);
  OBJ _cpy = (OBJ)cpy; PRT(_cpy);

  test_assert( self2->size > 0, "zero length array");
  
  cpy->Functor.msk = OBJECT_EDYNCAST(Functor, self2->object[0])->msk;  
  copy(cpy->fun,1,&cpy->size,self2->object,self2->stride,self2->size);

  UNPRT(_cpy);
  retmethod(_cpy);
endmethod

// ----- dtor

defmethod(OBJ, gdeinit, ComposeFun)
  U32 *val_n = &self->size;
  OBJ *val   = self->fun;
  OBJ *end   = val + *val_n;

  while (val != end)
    grelease(*--end), --*val_n;

  retmethod(_1);
endmethod

// ----- str

defmethod(STR, gstr, ComposeFun)
  retmethod(gstr(self->fun[0]));
endmethod

// ----- compose

defmethod(OBJ, gcompose, Functor)
  retmethod(_1);
endmethod

defmethod(OBJ, gcompose, Array)
  retmethod(gautoDelete(gnewWith(ComposeFun,_1)));
endmethod

// ----- eval

defmethod(OBJ, gevalEnv, ComposeFun, Container)
  OBJ *fun = self->fun;
  OBJ *end = self->fun + self->size;
  struct Array *env = atArray(0);
  OBJ *arg = env->object;
  
  forward_message(*fun++, _2);

  while (fun != end) {
    *arg = RETVAL;
    RETVAL = gevalEnv(*fun++, (OBJ)env);
  }

endmethod


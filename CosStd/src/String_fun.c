/*
 o---------------------------------------------------------------------o
 |
 | COS String - algorithms using functors
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_fun.c,v 1.1 2009/08/15 22:29:49 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// ----- 

useclass(String);

// ----- foreach (in place, discard fun returned value)

defmethod(void, gforeach, String, Functor)
  char *val = self->value;
  char *end = self->value + self->size;

  while (val != end)
    geval1(_2, aChar(*val++));
endmethod

// ----- apply (in place map)

defmethod(void, gapply, Functor, String)
  char *val = self2->value;
  char *end = self2->value + self2->size;

  while (val != end)
    *val++ = gchr(geval1(_1, aChar(*val)));
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, String)
  struct String* str = String_alloc(self2->size);
  OBJ _str = (OBJ)str; PRT(_str);

  char *dst = str->value;
  char *end = str->value + str->size;
  char *src = self2->value;

  while (dst != end)
    *dst++ = gchr(geval1(_1,aChar(*src++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap2, Functor, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  char *dst  = str->value;
  char *end  = str->value + str->size;
  char *src1 = self2->value;
  char *src2 = self3->value;

  while (dst != end)
    *dst++ = gchr(geval2(_1,aChar(*src1++),aChar(*src2++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap3, Functor, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  char *dst  = str->value;
  char *end  = str->value + str->size;
  char *src1 = self2->value;
  char *src2 = self3->value;
  char *src3 = self4->value;

  while (dst != end)
    *dst++ = gchr(geval3(_1,aChr(*src1++),aChr(*src2++),aChr(*src3++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap4, Functor, String, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  char *dst    = str->value;
  char *end    = str->value + str->size;
  char *src1   = self2->value;
  char *src2   = self3->value;
  char *src3   = self4->value;
  char *src4   = self5->value;

  while (dst != end)
    *dst++ = gchr(geval4(_1,aChr(*src1++),aChr(*src2++),
                            aChr(*src3++),aChr(*src4++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

// ----- all, any

defmethod(OBJ, gall, String, Functor)
  char *val = self->value;
  char *end = self->value + self->size;

  while (val != end)
    if (geval1(_2, aChar(*val++)) != True)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, String, Functor)
  char *val = self->value;
  char *end = self->value + self->size;

  while (val != end)
    if (geval1(_2, aChar(*val++)) == True)
      retmethod(True);

  retmethod(False);
endmethod

// ----- filter, filterOut fold, scan

defmethod(OBJ, gfilter, String, Functor)
  OBJ _str = gnewWith(String,aInt(self->size)); PRT(_str);
  struct String* str = STATIC_CAST(struct String*, _str);

  char *dst = str ->value;
  char *src = self->value;
  char *end = self->value + self->size;

  while (src != end) {
    if (geval1(_2, aChar(*src)) == True)
      *dst++ = *src, ++str->size;
    src++;
  }

  gadjust(_str);
  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gfilterOut, String, Functor)
  OBJ _str = gnewWith(String,aInt(self->size)); PRT(_str);
  struct String* str = STATIC_CAST(struct String*, _str);

  char *dst = str ->value;
  char *src = self->value;
  char *end = self->value + self->size;

  while (src != end) {
    if (geval1(_2, aChar(*src)) == False)
      *dst++ = *src, ++str->size;
    src++;
  }

  gadjust(_str);
  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gfoldl, String, Functor, Object)
  char *src = self->value;
  char *end = self->value + self->size;
  OBJ  res  = _3;
  
  while (src != end)
    res = geval2(_2, res, aChar(*src++));

  retmethod(res);
endmethod

defmethod(OBJ, gfoldr, String, Functor, Object)
  char *src = self->value + self->size;
  char *end = self->value;
  OBJ res   = _3;
  
  while (src != end)
    res = geval2(_2, aChar(*--src), res);

  retmethod(res);
endmethod

defmethod(OBJ, gscanl, String, Functor, Object)
  struct String* str = String_alloc(self->size+1);
  OBJ _str = (OBJ)str; PRT(_str);

  char *dst = str->value;
  char *end = str->value + str->size;
  char *src = self->value;

  *dst++ = gchr(_3);
  
  while (dst != end) {
    *dst = gchr( geval2(_2, aChar(dst[-1]), aChar(*src++)) );
    dst++;
  }

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gscanr, String, Functor, Object)
  struct String* str = String_alloc(self->size+1);
  OBJ _str = (OBJ)str; PRT(_str);

  char *dst = str->value + str->size;
  char *end = str->value;
  char *src = self->value + self->size;

  *--dst = gchr(_3);

  while (dst != end) {
    dst--;
    *dst = gchr( geval2(_2, aChar(*--src), aChar(dst[1])) );
  }

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, String, Functor)
  if (self->size < 1)
    retmethod( gautoDelete(gclone(_1)) );

  OBJ _str = gnewWith(String,aInt(self->size)); PRT(_str);
  struct String* str = STATIC_CAST(struct String*, _str);

  char *dst = str ->value;
  char *src = self->value;
  char *end = self->value + (self->size-1);

  while (src != end)
    if (geval2(_2, aChar(src[0]), aChar(src[1])) != True)
      *dst++ = *src++, ++str->size;
  *dst++ = *src++;

  gadjust(_str);
  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod


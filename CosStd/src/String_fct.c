/*
 o---------------------------------------------------------------------o
 |
 | COS String - algorithms using functions
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
 | $Id: String_fct.c,v 1.3 2009/08/17 12:57:13 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/Functor.h>
#include <cos/Function.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

useclass(String);

// ----- foreach (in place)

defmethod(void, gforeach, String, IntFunction1)
  U8* val = self->value;
  U8* end = self->value + self->size;
  I32FCT1 fct = self2->fct;

  while (val != end)
    fct(*val++);
endmethod

defmethod(void, gforeach, String, Function1)
  U8* val = self->value;
  U8* end = self->value + self->size;
  OBJFCT1 fct = self2->fct;

  while (val != end)
    fct(aChar(*val++));
endmethod

// ----- apply (in place map)

defmethod(void, gapply, IntFunction1, String)
  U8* val = self2->value;
  U8* end = self2->value + self2->size;
  I32FCT1 fct = self->fct;

  while (val != end)
    *val = fct(*val), val++;
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, IntFunction1, String)
  struct String* str = String_alloc(self2->size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst = str->value;
  U8* end = str->value + str->size;
  U8* src = self2->value;
  I32FCT1 fct = self->fct;

  while (dst != end)
    *dst++ = fct(*src++);

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap2, IntFunction2, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self2->value;
  U8* src2 = self3->value;
  I32FCT2 fct = self->fct;

  while (dst != end)
    *dst++ = fct(*src1++,*src2++);

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap3, IntFunction3, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self2->value;
  U8* src2 = self3->value;
  U8* src3 = self4->value;
  I32FCT3 fct = self->fct;

  while (dst != end)
    *dst++ = fct(*src1++,*src2++,*src3++);

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap4, IntFunction4, String, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self2->value;
  U8* src2 = self3->value;
  U8* src3 = self4->value;
  U8* src4 = self5->value;
  I32FCT4 fct = self->fct;

  while (dst != end)
    *dst++ = fct(*src1++,*src2++,*src3++,*src4++);

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

// ----- all, any

defmethod(OBJ, gall, String, Function1)
  U8* val = self->value;
  U8* end = self->value + self->size;
  OBJFCT1 fct = self2->fct;

  while (val != end)
    if (fct(aChar(*val++)) != True)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, String, Function1)
  U8* val = self->value;
  U8* end = self->value + self->size;
  OBJFCT1 fct = self2->fct;

  while (val != end)
    if (fct(aChar(*val++)) == True)
      retmethod(True);
      
  retmethod(False);
endmethod

// ----- filter, filterOut, fold, scan

defmethod(OBJ, gfilter, String, Function1)
  OBJ _str = gnewWith(String,aInt(self->size)); PRT(_str);
  struct String* str = STATIC_CAST(struct String*, _str);

  U8* dst = str->value;
  U8* src = self->value;
  U8* end = self->value + self->size;
  OBJFCT1 fct = self2->fct;

  while (src != end) {
    if (fct(aChar(*src)) == True)
      *dst++ = *src, ++str->size;
    src++;
  }

  gadjust(_str);
  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gfilterOut, String, Function1)
  OBJ _str = gnewWith(String,aInt(self->size)); PRT(_str);
  struct String* str = STATIC_CAST(struct String*, _str);

  U8* dst = str->value;
  U8* src = self->value;
  U8* end = self->value + self->size;
  OBJFCT1 fct = self2->fct;

  while (src != end) {
    if (fct(aChar(*src)) == False)
      *dst++ = *src, ++str->size;
    src++;
  }

  gadjust(_str);
  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gfoldl, String, Function2, Object)
  U8* src = self->value;
  U8* end = self->value + self->size;
  OBJ res = _3;
  OBJFCT2 fct = self2->fct;
  
  while (src != end)
    res = fct(res, aChar(*src++));

  retmethod(res);
endmethod

defmethod(OBJ, gfoldr, String, Function2, Object)
  U8* src = self->value + self->size;
  U8* end = self->value;
  OBJ res = _3;
  OBJFCT2 fct = self2->fct;

  while (src != end)
    res = fct(aChar(*--src), res);

  retmethod(res);
endmethod

defmethod(OBJ, gscanl, String, IntFunction2, Object)
  struct String* str = String_alloc(self->size+1);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst = str->value;
  U8* end = str->value + str->size;
  U8* src = self->value;
  I32FCT2 fct = self2->fct;

  *dst++ = gchr(_3);
  
  while (dst != end) {
    *dst = fct(dst[-1], *src++);
     dst++;
  }

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gscanr, String, IntFunction2, Object)
  struct String* str = String_alloc(self->size+1);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst = str->value + str->size;
  U8* end = str->value;
  U8* src = self->value + self->size;
  I32FCT2 fct = self2->fct;

  *--dst = gchr(_3);

  while (dst != end) {
     dst--;
    *dst = fct(*src++, dst[1]);
  }

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, String, Function2)
  if (self->size < 1)
    retmethod( gautoDelete(gclone(_1)) );

  OBJ _str = gnewWith(String,aInt(self->size)); PRT(_str);
  struct String* str = STATIC_CAST(struct String*, _str);

  U8* dst = str ->value;
  U8* src = self->value;
  U8* end = self->value + (self->size-1);
  OBJFCT2 fct = self2->fct;

  while (src != end)
    if (fct(aChar(src[0]), aChar(src[1])) != True)
      *dst++ = *src++, ++str->size;
  *dst++ = *src++;

  gadjust(_str);
  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

// ----- search (function)

static I32
ifind(struct String *self, OBJFCT1 fct)
{
  useclass(Lesser, Equal, Greater);

  if (self->size == 0)
    return(-1);

  U8* val = self->value;
  OBJ res = fct(aChar(*val)); // bsearch order

  if (res == True || res == Equal) // found
    return(0);

  // linear search
  if (res == False) {
    U8* end = self->value + self->size;
    
    val++;
    while (val != end) {
      if (fct(aChar(*val)) == True) // found
        return(val-self->value);
      val++;
    }

    return(-1);
  }

  // binary search
  if (res == Lesser)
    return(-1);

  test_assert( res == Greater,
    "find expects functor returning TrueFalse or Ordered predicates" );

  U32 lo = 1, hi = self->size-1;

  while (lo <= hi) {
    U32 i = (lo + hi) / 2;
    res = fct(aChar(val[i]));

    if (res == Equal)
      return(i); // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

  return(-1);
}

// ---

defmethod(OBJ, gfind, String, Function1)
  I32 i = ifind(self,self2->fct);
  
  retmethod(i >= 0 ? gautoDelete(aChar(self->value[i])) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Function1)
  I32 i = ifind(self,self2->fct);

  retmethod(i >= 0 ? gautoDelete( aInt(i) ) : Nil);
endmethod



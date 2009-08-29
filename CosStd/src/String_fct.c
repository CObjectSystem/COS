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
 | $Id: String_fct.c,v 1.4 2009/08/29 21:33:40 ldeniau Exp $
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
useclass(Lesser,Equal,Greater);

// ----- foreach (in place)

defmethod(void, gforeach, String, Function1)
  U8* val = self->value;
  U8* end = self->value + self->size;
  OBJFCT1 fct = self2->fct;

  while (val != end)
    fct(aChar(*val++));
endmethod

// ----- apply (in place map)

defmethod(void, gapply, Function1, String)
  U8* val = self2->value;
  U8* end = self2->value + self2->size;
  OBJFCT1 fct = self->fct;

  while (val != end)
    *val = gchr(fct(aChar(*val))), val++;
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Function1, String)
  struct String* str = String_alloc(self2->size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst = str->value;
  U8* end = str->value + str->size;
  U8* src = self2->value;
  OBJFCT1 fct = self->fct;

  while (dst != end)
    *dst++ = gchr(fct(aChar(*src++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap2, Function2, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self2->value;
  U8* src2 = self3->value;
  OBJFCT2 fct = self->fct;

  while (dst != end)
    *dst++ = gchr(fct(aChar(*src1++),aChar(*src2++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap3, Function3, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;

  struct String* str = String_alloc(size);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self2->value;
  U8* src2 = self3->value;
  U8* src3 = self4->value;
  OBJFCT3 fct = self->fct;

  while (dst != end)
    *dst++ = gchr(fct(aChar(*src1++),aChar(*src2++),aChar(*src3++)));

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, gmap4, Function4, String, String, String, String)
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
  OBJFCT4 fct = self->fct;

  while (dst != end)
    *dst++ = gchr(fct(aChar(*src1++),aChar(*src2++),aChar(*src3++),aChar(*src4++)));

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

// ----- filter, fold, scan

defmethod(OBJ, gselect, String, Function1)
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

defmethod(OBJ, greject, String, Function1)
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

defmethod(OBJ, greduce, String, Function2, Object)
  U8* src = self->value;
  U8* end = self->value + self->size;
  OBJ res = _3;
  OBJFCT2 fct = self2->fct;
  
  while (src != end)
    res = fct(res, aChar(*src++));

  retmethod(res);
endmethod

defmethod(OBJ, grreduce, String, Function2, Object)
  U8* src = self->value + self->size;
  U8* end = self->value;
  OBJ res = _3;
  OBJFCT2 fct = self2->fct;

  while (src != end)
    res = fct(aChar(*--src), res);

  retmethod(res);
endmethod

defmethod(OBJ, gaccumulate, String, Function2, Object)
  struct String* str = String_alloc(self->size+1);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst = str->value;
  U8* end = str->value + str->size;
  U8* src = self->value;
  OBJFCT2 fct = self2->fct;

  *dst++ = gchr(_3);
  
  while (dst != end) {
    *dst = gchr(fct(aChar(dst[-1]), aChar(*src++)));
     dst++;
  }

  UNPRT(_str);
  retmethod(gautoDelete(_str));
endmethod

defmethod(OBJ, graccumulate, String, Function2, Object)
  struct String* str = String_alloc(self->size+1);
  OBJ _str = (OBJ)str; PRT(_str);

  U8* dst = str->value + str->size;
  U8* end = str->value;
  U8* src = self->value + self->size;
  OBJFCT2 fct = self2->fct;

  *--dst = gchr(_3);

  while (dst != end) {
     dst--;
    *dst = gchr(fct(aChar(*src++), aChar(dst[1])));
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

// ----- finding

static U8*
findFct(U8 *val, U32 val_n, OBJFCT1 fct)
{
  if (!val_n) return 0;

  OBJ res = fct(aChar(*val)); // bsearch order

  if (res == True || res == Equal) // found
    return val;

  // linear search
  if (res == False) {
    U8* end = val + val_n;
    
    val++;
    while (val != end) {
      if (fct(aChar(*val)) == True) // found
        return val;
      val++;
    }

    return 0;
  }

  // binary search
  if (res == Lesser)
    return 0;

  test_assert( res == Greater,
    "find expects functor returning TrueFalse or Ordered predicates" );

  U32 lo = 1, hi = val_n-1;

  while (lo <= hi) {
    U32 i = (lo + hi) / 2;
    res = fct(aChar(val[i]));

    if (res == Equal)
      return val + i; // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

  return 0;
}

// ---

defmethod(OBJ, gfind, String, Function1)
  U8* val   = self->value;
  U32 val_n = self->size;

  U8* p = findFct(val,val_n,self2->fct);
  
  retmethod(p ? gautoDelete(aChar(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Function1)
  U8* val   = self->value;
  U32 val_n = self->size;

  U8* p = findFct(val,val_n,self2->fct);
  
  retmethod(p ? gautoDelete(aInt(p-val)) : Nil);  
endmethod



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
 | $Id: String_fun.c,v 1.7 2009/09/18 16:42:30 ldeniau Exp $
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
useclass(Lesser,Equal,Greater);

// ----- apply (in-place map with returned value discarded)

defmethod(void, gapply, Functor, String)
  U32 size = self2->size;
  U8* val  = self2->value;
  U8* end  = val + size;

  while (val != end)
    geval(_1, aChar(*val++));
endmethod

defmethod(void, gapply2, Functor, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* end  = val + size;

  while (val != end)
    geval(_1, aChr(*val++, *val2++));
endmethod

defmethod(void, gapply3, Functor, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* end  = val + size;

  while (val != end)
    geval(_1, aChr(*val++, *val2++, *val3++));
endmethod

defmethod(void, gapply4, Functor, String, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* val4 = self5->value;
  U8* end  = val + size;

  while (val != end)
    geval(_1, aChr(*val++, *val2++, *val3++, *val4++));
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, String)
  U32 size = self2->size;
  struct String* str = String_alloc(size);
  OBJ _str = gautoDelete( (OBJ)str );

  U8* val = self2->value;
  U8* dst = str->value;
  U8* end = dst + size;
  
  while (dst != end)
    *dst++ = (U32)gchr(geval(_1,aChar(*val++)));

  retmethod(_str);
endmethod

defmethod(OBJ, gmap2, Functor, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  struct String* str = String_alloc(size);
  OBJ _str = gautoDelete( (OBJ)str );

  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* dst  = str->value;
  U8* end  = dst + size;

  while (dst != end)
    *dst++ = (U32)gchr(geval(_1,aChar(*val++),aChar(*val2++)));

  retmethod(_str);
endmethod

defmethod(OBJ, gmap3, Functor, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
  struct String* str = String_alloc(size);
  OBJ _str = gautoDelete( (OBJ)str );

  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* dst  = str->value;
  U8* end  = dst + size;

  while (dst != end)
    *dst++ = (U32)gchr(geval(_1,aChr(*val++),aChr(*val2++),aChr(*val3++)));

  retmethod(_str);
endmethod

defmethod(OBJ, gmap4, Functor, String, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  struct String* str = String_alloc(size);
  OBJ _str = gautoDelete( (OBJ)str );

  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* val4 = self5->value;
  U8* dst  = str->value;
  U8* end  = dst + size;

  while (dst != end)
    *dst++ = (U32)gchr(geval(_1,aChr(*val ++),aChr(*val2++),
                                aChr(*val3++),aChr(*val4++)));

  retmethod(_str);
endmethod

// ----- all, any

defmethod(OBJ, gall, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;

  while (val != end)
    if (geval(_2, aChar(*val++)) != True)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;

  while (val != end)
    if (geval(_2, aChar(*val++)) == True)
      retmethod(True);

  retmethod(False);
endmethod

defmethod(U32, gcount, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  U32 cnt  = 0;

  while (val != end)
    if (geval(_2, aChar(*val++)) == True)
      ++cnt;

  retmethod(cnt);
endmethod

// ----- reduce

defmethod(OBJ, greduce, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  OBJ res  = Nil;
  
  if (val != end) {
    res = gautoDelete(gclone(aChar(*val++)));
    
    while (val != end)
      res = geval(_2, res, aChar(*val++));
  }

  retmethod(res);
endmethod

defmethod(OBJ, grreduce, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  OBJ res  = Nil;
  
  if (val != end) {
    res = gautoDelete(gclone(aChar(*--end)));
    
    while (val != end)
      res = geval(_2, aChar(*--end), res);
  }

  retmethod(res);
endmethod

defmethod(OBJ, greduce1, String, Functor, Object)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  OBJ res  = _3;
  
  while (val != end)
    res = geval(_2, res, aChar(*val++));

  retmethod(res);
endmethod

defmethod(OBJ, grreduce1, String, Functor, Object)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  OBJ res  = _3;
  
  while (val != end)
    res = geval(_2, aChar(*--end), res);

  retmethod(res);
endmethod

defmethod(OBJ, greduce2, String, String, Functor, Object)
  U32 size = self->size < self2->size ? self->size : self2->size;
  U8* val  = self->value;
  U8* val2 = self2->value;
  U8* end  = val + size;
  OBJ res  = _4;
  
  while (val != end)
    res = geval(_3, res, aChar(*val++), aChar(*val2++));

  retmethod(res);
endmethod

defmethod(OBJ, grreduce2, String, String, Functor, Object)
  U32 size = self->size < self2->size ? self->size : self2->size;
  U8* end  = self->value + self->size;
  U8* end2 = self2->value + self2->size;
  U8* val  = end - size;
  OBJ res  = _4;
  
  while (val != end)
    res = geval(_2, aChar(*--end), aChar(*--end2), res);

  retmethod(res);
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, String, Functor)
  U32 size = self->size;
  OBJ _str = gautoDelete(gnewWith(String,aInt(size)));
  struct String* str = STATIC_CAST(struct String*, _str);

  U8* val = self->value;
  U8* dst = str ->value;
  U8* end = val + size;

  if (val != end) {
    *dst = *val++;

    while (val != end) {
      if (geval(_2, aChar(*dst), aChar(*val)) != True)
        *++dst = *val;
      val++;
    }
  }
  
  retmethod(gadjust(_str));
endmethod

// ----- search (functor)

static U8*
findFun(U8* val, U32 val_n, OBJ _2)
{
  if (!val_n) return 0;

  OBJ res = geval(_2, aChar(*val)); // compare first element

  if (res == True || res == Equal) // found
    return val;

  // linear search
  if (res == False) {
    U8* end = val + val_n;

    for (val++; val != end; val++)
      if (geval(_2, aChar(*val)) == True) // found
        return val;

    return 0; // not found
  }

  // binary search
  if (res == Greater) {
    U32 lo = 1, hi = val_n-1;

    while (lo <= hi) {
      U32 i = (lo + hi) / 2;
      res = geval(_2, aChar(val[i]));

      if (res == Equal)
        return val + i; // found

      if (res == Lesser)
        hi = i-1;
      else
        lo = i+1;
    }
  }
  
  return 0; // not found
}

// ---

defmethod(OBJ, gfind, String, Functor)
  U32 val_n = self->size;
  U8* val   = self->value;

  U8* p = findFun(val,val_n,_2);

  retmethod(p ? gautoDelete(aChar(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Functor)
  U32 val_n = self->size;
  U8* val   = self->value;

  U8* p = findFun(val,val_n,_2);

  retmethod(p ? gautoDelete(aInt(p-val)) : Nil);  
endmethod


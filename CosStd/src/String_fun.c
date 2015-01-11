/**
 * C Object System
 * COS String - algorithms using functors
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

#include <cos/String.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/collection.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// ----- 

useclass(String);
useclass(Lesser,Equal,Greater);

// ----- applyWhile, applyIf, apply (in-place map)

defmethod(OBJ, gapplyWhile, Functor, String)
  U32 size = self2->size;
  U8* val  = self2->value;
  U8* end  = val + size;
  OBJ res, old;

  while (val != end && (res = geval(_1, old = aChar(*val))) != Nil) {
    if (res != old) *val = (U32)gchr(res);
    val++;
  }

  retmethod(_2);
endmethod

defmethod(OBJ, gapply, Functor, String)
  U32 size = self2->size;
  U8* val  = self2->value;
  U8* end  = val + size;
  OBJ res, old;

  while (val != end) {
    res = geval(_1, old = aChar(*val));
    if (res != old) *val = (U32)gchr(res);
    val++;
  }
  retmethod(_2);
endmethod

defmethod(OBJ, gapply2, Functor, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* end  = val + size;
  OBJ res, old;

  while (val != end) {
    res = geval(_1, old = aChr(*val, *val2++));
    if (res != old) *val = (U32)gchr(res);
    val++;
  }

  retmethod(_2);
endmethod

defmethod(OBJ, gapply3, Functor, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* end  = val + size;
  OBJ res, old;

  while (val != end) {
    res = geval(_1, old = aChr(*val, *val2++, *val3++));
    if (res != old) *val = (U32)gchr(res);
    val++;
  }

  retmethod(_2);
endmethod

defmethod(OBJ, gapply4, Functor, String, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* val4 = self5->value;
  U8* end  = val + size;
  OBJ res, old;

  while (val != end) {
    res = geval(_1, old = aChr(*val, *val2++, *val3++, *val4++));
    if (res != old) *val = (U32)gchr(res);
    val++;
  }

  retmethod(_2);
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmapWhile, Functor, String)
  U32 size = self2->size;
  U8* val  = self2->value;
  U8* end  = val + size;
  OBJ res;

  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);
  
  U32 *dst_n = &str->size;
  U8*  dst   = str->value;

  while (val != end && (res = geval(_1, aChar(*val))) != Nil) {
    *dst++ = (U32)gchr(res), ++*dst_n;
    val++;
  }

  retmethod(_str);
endmethod

defmethod(OBJ, gmapIf, Functor, String)
  U32 size = self2->size;
  U8* val  = self2->value;
  U8* end  = val + size;
  OBJ res;

  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);
  
  U32 *dst_n = &str->size;
  U8*  dst   = str->value;

  while (val != end) {
   if ((res = geval(_1, aChar(*val))) != Nil)
     *dst++ = (U32)gchr(res), ++*dst_n;
   val++;
  }

  retmethod(_str);
endmethod

defmethod(OBJ, gmap, Functor, String)
  U32 size = self2->size;
  U8* val  = self2->value;
  U8* end  = val + size;

  struct String* str = String_alloc(size);
  OBJ _str = gautoRelease( (OBJ)str );

  U8* dst = str->value;

  while (val != end)
    *dst++ = (U32)gchr(geval(_1,aChar(*val++)));

  retmethod(_str);
endmethod

defmethod(OBJ, gmap2, Functor, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* end  = val + size;

  struct String* str = String_alloc(size);
  OBJ _str = gautoRelease( (OBJ)str );

  U8* dst = str->value;

  while (val != end)
    *dst++ = (U32)gchr(geval(_1,aChar(*val++),aChar(*val2++)));

  retmethod(_str);
endmethod

defmethod(OBJ, gmap3, Functor, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* end  = val + size;

  struct String* str = String_alloc(size);
  OBJ _str = gautoRelease( (OBJ)str );

  U8* dst = str->value;

  while (dst != end)
    *dst++ = (U32)gchr(geval(_1,aChr(*val++),aChr(*val2++),aChr(*val3++)));

  retmethod(_str);
endmethod

defmethod(OBJ, gmap4, Functor, String, String, String, String)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  U8* val  = self2->value;
  U8* val2 = self3->value;
  U8* val3 = self4->value;
  U8* val4 = self5->value;
  U8* end  = val + size;

  struct String* str = String_alloc(size);
  OBJ _str = gautoRelease( (OBJ)str );

  U8* dst = str->value;

  while (val != end)
    *dst++ = (U32)gchr(geval(_1,aChr(*val ++),aChr(*val2++),
                                aChr(*val3++),aChr(*val4++)));

  retmethod(_str);
endmethod

// ----- select, reject

defmethod(OBJ, gselect, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;

  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);

  U32 *dst_n = &str->size;
  U8*  dst   = str ->value;

  while (val != end) {
    if (geval(_2, aChar(*val)) == True)
      *dst++ = *val, ++*dst_n;
    val++;
  }

  retmethod(_str);
endmethod

defmethod(OBJ, greject, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;

  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);

  U32 *dst_n = &str->size;
  U8*  dst   = str ->value;

  while (val != end) {
    if (geval(_2, aChar(*val)) != True)
      *dst++ = *val, ++*dst_n;
    val++;
  }

  retmethod(_str);
endmethod

defmethod(OBJ, gselectWhile, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;

  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);

  U32 *dst_n = &str->size;
  U8*  dst   = str->value;

  // select
  while (val != end && geval(_2, aChar(*val)) == True) {
    *dst++ = *val, ++*dst_n;
    val++;
  }
  // reject the rest

  retmethod(_str);
endmethod

defmethod(OBJ, grejectWhile, String, Functor)
  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;

  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);

  U32 *dst_n = &str->size;
  U8*  dst   = str->value;

  // reject
  while (val != end && geval(_2, aChar(*val)) == True)
    val++;

  // select
  while (val != end) {
    *dst++ = *val, ++*dst_n;
    val++;
  }

  retmethod(_str);
endmethod

// ----- reduce

defmethod(OBJ, greduce, String, Functor)
  ensure( self->size > 0, "empty string" );

  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  OBJ res  = gautoRelease(gclone(aChar(*val++)));

  while (val != end)
    res = geval(_2, res, aChar(*val++));

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

/*
defmethod(OBJ, grreduce, String, Functor)
  ensure( self->size > 0, "empty string" );

  U32 size = self->size;
  U8* val  = self->value;
  U8* end  = val + size;
  OBJ  res   = gautoRelease(gclone(aChar(*(--end))));
  
  while (val != end)
    res = geval(_2, aChar(*--end), res);

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
*/

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

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, String, Functor)
  U32 size = self->size;
  OBJ _str = gautoRelease(gnewWith(String,aInt(size)));
  struct String* str = CAST(struct String*, _str);

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
  
  retmethod(_str);
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

  retmethod(p ? gautoRelease(aChar(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Functor)
  U32 val_n = self->size;
  U8* val   = self->value;

  U8* p = findFun(val,val_n,_2);

  retmethod(p ? gautoRelease(aInt(p-val)) : Nil);  
endmethod


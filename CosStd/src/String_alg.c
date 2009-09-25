/*
 o---------------------------------------------------------------------o
 |
 | COS String - algorithms not using functor
 |
 o---------------------------------------------------------------------o
 |
 | C value System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C value System framework.
 |
 | The C value System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C value System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_alg.c,v 1.12 2009/09/25 08:58:59 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/IntVector.h>
#include <cos/Number.h>
#include <cos/Slice.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/carray.h>

// -----

useclass(String, View, Array, ExBadAlloc);
useclass(Lesser,Equal,Greater);

// ----- equality

defmethod(OBJ, gisEqual, String, String)
  if (self == self2)
    retmethod(True);

  if (self->size != self2->size)
    retmethod(False);

  retmethod( memcmp(self->value,self2->value,self->size) ? False : True );
endmethod

// ----- comparison

defmethod(OBJ, gcompare, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;

  int res = memcmp(self->value,self2->value,size);
  
  retmethod( res < 0 ? Lesser : res > 0 ? Greater : Equal );
endmethod

// ----- in place

defmethod(void, greverse, String)
  if (self->size < 2)
    retmethod();

  U32 size = self->size;
  U8* val = self->value;
  U8* end = val + (size-1);
  U8  tmp;

  while (val != end)
    tmp = *val, *val++ = *end, *end++ = tmp;

endmethod

// ----- zip, zip3

defmethod(OBJ, gzip, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;
  struct String* str = String_alloc(2*size);

  U8* src  = self->value; 
  U8* src2 = self2->value;
  U8* dst  = str->value;
  U8* end  = dst + 2*size;

  while (dst != end) {
    *dst++ = *src ++;
    *dst++ = *src2++;
  }

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gzip3, String, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;
      size = self3->size < size ? self3->size : size;
  struct String* str = String_alloc(3*size);

  U8* src  = self->value; 
  U8* src2 = self2->value;
  U8* src3 = self3->value;
  U8* dst  = str->value;
  U8* end  = dst + 3*size;

  while (dst != end) {
    *dst++ = *src ++;
    *dst++ = *src2++;
    *dst++ = *src3++;
  }

  retmethod(gautoDelete( (OBJ)str ));
endmethod

// ----- cat, cat3, cat4, cat5

defmethod(OBJ, gcat, String, String)
  U32 size = self->size + self2->size;
  struct String *str = String_alloc(size);

  U8* dst = str->value;

  memcpy(dst,self ->value,self ->size); dst += self->size;
  memcpy(dst,self2->value,self2->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat3, String, String, String)
  U32 size = self->size + self2->size + self3->size;
  struct String *str = String_alloc(size);

  U8* dst = str->value;

  memcpy(dst,self ->value,self ->size); dst += self ->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat4, String, String, String, String)
  U32 size = self->size + self2->size + self3->size + self4->size;
  struct String *str = String_alloc(size);

  U8* dst = str->value;

  memcpy(dst,self ->value,self ->size); dst += self ->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size); dst += self3->size;
  memcpy(dst,self4->value,self4->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat5, String, String, String, String, String)
  U32 size = self->size + self2->size +
             self3->size + self4->size + self5->size;
  struct String *str = String_alloc(size);

  U8* dst = str->value;

  memcpy(dst,self ->value,self ->size); dst += self ->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size); dst += self3->size;
  memcpy(dst,self4->value,self4->size); dst += self4->size;
  memcpy(dst,self5->value,self5->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

// ----- split (object)

defmethod(OBJ, gsplit, String, Object)
  U32 size = self->size;
  U8* src  = self->value;
  U8  val  = (U32)gchr(_2);
  OBJ strs = gautoDelete(gnew(Array));
  OBJ str  = 0; PRT(str);

  while(size) {
    U8* end = memchr(src, val, size);
    U32 beg = src-self->value;
    U32 len = end ? end-src : size;
    
    str = gnewWith2(View, _1, aSlice(beg,len));
    gpush(strs, str);
    gdelete(str);
    str = 0;

    if (!end) break;

    src   = end+1;
    size -= len+1;
  }
  
  UNPRT(str);
  retmethod(gadjust(strs));
endmethod

// ----- search (object)

defmethod(OBJ, gfind, String, Object)
  U8 val = (U32)gchr(_2);
  U8*  p = memchr(self->value, val, self->size);
  
  retmethod(p ? gautoDelete(aChar(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Object)
  U8 val = (U32)gchr(_2);
  U8*  p = memchr(self->value, val, self->size);

  retmethod(p ? gautoDelete(aInt(p-self->value)) : Nil);
endmethod

// ----- search (char)

defmethod(OBJ, gfind, String, Char)
  U8* p = memchr(self->value, self2->Int.value, self->size);
  
  retmethod(p ? gautoDelete(aChar(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Char)
  U8* p = memchr(self->value, self2->Int.value, self->size);

  retmethod(p ? gautoDelete(aInt(p-self->value)) : Nil);
endmethod

// ----- search (string)

// -- BruteForce (quadratic to linear)

static inline U8*
BruteForce2(U8 *str, U32 str_n, U8 *pat)
{
  while((str = memchr(str, *pat, str_n-2+1)) != 0) {
    if (str[1] == pat[1])
      return str;
    str++;  
  }
  
  return 0;
}

static inline U8*
BruteForce3(U8 *str, U32 str_n, U8 *pat)
{
  while((str = memchr(str, *pat, str_n-3+1)) != 0) {
    if (str[1] == pat[1] && str[2] == pat[2])
      return str;
    str++;  
  }
  
  return 0;
}

static inline U8*
BruteForce4(U8 *str, U32 str_n, U8 *pat)
{
  while((str = memchr(str, *pat, str_n-4+1)) != 0) {
    if (str[1] == pat[1] && str[2] == pat[2] && str[3] == pat[3])
      return str;
    str++;  
  }
  
  return 0;
}

static inline U8*
BruteForce(U8 *str, U32 str_n, U8 *pat, I32 pat_n)
{
  while((str = memchr(str, *pat, str_n-pat_n+1)) != 0) {
    if (memcmp(str+1,pat+1,pat_n-1) == 0)
      return str;
    str++;  
  }
  
  return 0;
}

// -- QuickSearch (quadratic to sublinear)

// alphabet size
enum { ASIZE = 1 << CHAR_BIT };

static void
preQsBc(U8 *pat, U32 pat_n, U32 qsBc[]) {
   U32 i;

   for (i = 0; i < ASIZE; ++i)
      qsBc[i] = pat_n + 1;
   for (i = 0; i < pat_n; ++i)
      qsBc[pat[i]] = pat_n - i;
}

static U8*
QuickSearch2(U8 *str, U32 str_n, U8 *pat) {
   U32 j = 0, qsBc[ASIZE];

   preQsBc(pat, 2, qsBc);

   while (j <= str_n-2) {
      if (pat[1] == str[j+1])
         return str + j;
      j += qsBc[str[j+2]];
   }

   return 0;
}

static U8*
QuickSearch3(U8 *str, U32 str_n, U8 *pat) {
   U32 j = 0, qsBc[ASIZE];

   preQsBc(pat, 3, qsBc);
 
   while (j <= str_n-3) {
      if (pat[1] == str[j+1] && pat[2] == str[j+2])
         return str + j;
      j += qsBc[str[j+3]];
   }

   return 0;
}

static U8*
QuickSearch4(U8 *str, U32 str_n, U8 *pat) {
   U32 j = 0, qsBc[ASIZE];

   preQsBc(pat, 4, qsBc);
 
   while (j <= str_n-4) {
      if (pat[1] == str[j+1] && pat[2] == str[j+2] && pat[3] == str[j+3])
         return str + j;
      j += qsBc[str[j+4]];
   }

   return 0;
}

static U8*
QuickSearch(U8 *str, U32 str_n, U8 *pat, U32 pat_n) {
   U32 j = 0, qsBc[ASIZE];

   preQsBc(pat, pat_n, qsBc);
 
   j = 0;
   while (j <= str_n - pat_n) {
      if (memcmp(pat, str + j, pat_n) == 0)
         return str + j;
      j += qsBc[str[j + pat_n]];
   }

   return 0;
}

// -- TurboBoyerMoore (linear to sublinear)

static inline I32
min(I32 a, I32 b) {
  return a <= b ? a : b;
}

static inline I32
max(I32 a, I32 b) {
  return a >= b ? a : b;
}

static void
preBmBc(U8 *pat, I32 pat_n, I32 bmBc[]) {
   I32 i;
 
   for (i = 0; i < ASIZE; ++i)
      bmBc[i] = pat_n;
   for (i = 0; i < pat_n - 1; ++i)
      bmBc[pat[i]] = pat_n - i - 1;
}

static void
preBmGs(U8* pat, I32 pat_n, I32 bmGs[], I32 suff[])
{
  I32 i, j, f, g;

   suff[pat_n-1] = pat_n;
   f = g = pat_n-1;
   for (i = pat_n-2; i >= 0; --i) {
      if (i > g && suff[i + pat_n-1 - f] < i - g)
         suff[i] = suff[i + pat_n-1 - f];
      else {
         if (i < g) g = i;
         f = i;
         while (g >= 0 && pat[g] == pat[g + pat_n-1 - f])
            --g;
         suff[i] = f - g;
      }
   }

  j = 0;
  for (i = 0; i < pat_n; ++i)
    bmGs[i] = pat_n;
  for (i = pat_n-1; i >= 0; --i)
    if (suff[i] == i + 1)
      for (; j < pat_n-1 - i; ++j)
        if (bmGs[j] == pat_n)
          bmGs[j] = pat_n-1 - i;
  for (i = 0; i <= pat_n-2; ++i)
    bmGs[pat_n-1 - suff[i]] = pat_n-1 - i;
}
 
static U8*
TurboBoyerMoore(U8 *str, U32 str_n, U8 *pat, I32 pat_n)
{
  I32 i, u, v, shift, bcShift, turboShift, bmBc[ASIZE];
  U32 j;

  TMPARRAY_CREATE(I32,bmGs,2*pat_n);
  I32 *const suff = bmGs + pat_n;

  // preprocessing
  preBmGs(pat, pat_n, bmGs, suff);
  preBmBc(pat, pat_n, bmBc);

  // searching
  j = u = 0;
  shift = pat_n;
  while (j <= str_n - pat_n) {
    i = pat_n - 1;
    while (i >= 0 && pat[i] == str[i + j]) {
      --i;
      if (u != 0 && i == pat_n - 1 - shift)
        i -= u;
    }
    if (i < 0) { // found
      TMPARRAY_DESTROY(bmGs);
      return str + j;
    }
    else {
      v = pat_n - 1 - i;
      turboShift = u - v;
      bcShift = bmBc[str[i + j]] - pat_n + 1 + i;
      shift = max(turboShift, bcShift);
      shift = max(shift, bmGs[i]);
      if (shift == bmGs[i])
        u = min(pat_n - shift, v);
      else {
        if (turboShift < bcShift)
          shift = max(shift, u + 1);
        u = 0;
      }
    }
    j += shift;
  }
  
  TMPARRAY_DESTROY(bmGs);
  return 0;
}

// -- KnuthMorrisPratt (linear)

static U8*
KnuthMorrisPratt(U8 *str, U32 str_n, U8 *pat, I32 pat_n)
{
  TMPARRAY_CREATE(I32,kmpNext,pat_n);

  { // preprocessing
    I32 i = 0, j = kmpNext[0] = -1;

    while (i < pat_n) {
      while (j > -1 && pat[i] != pat[j])
        j = kmpNext[j];
      i++;
      j++;
      if (pat[i] == pat[j])
        kmpNext[i] = kmpNext[j];
      else
        kmpNext[i] = j;
    }
  }
 
  { // searching
    I32 i = 0;
    U32 j = 0;

    while (j < str_n) {
      while (i > -1 && pat[i] != str[j])
        i = kmpNext[i];
      i++;
      j++;
      if (i >= pat_n) { // found
        TMPARRAY_DESTROY(kmpNext);
        return str + (j - i);
      }
    }
  }

  TMPARRAY_DESTROY(kmpNext);
  return 0;
}

// -- find front-end

static U8*
findSub(U8 *str, U32 str_n, U8 *pat, U32 pat_n)
{
  // string too short
  if (str_n < pat_n) return 0;

  // empty pattern
  if (!pat_n) return str;

  // single character pattern
  if (pat_n == 1)
    return memchr(str, *pat, str_n-1+1);

  // very short string or pattern
  if (str_n * pat_n < 2*ASIZE) {
    switch(pat_n) {
    case  2: return BruteForce2(str, str_n, pat);
    case  3: return BruteForce3(str, str_n, pat);
    case  4: return BruteForce4(str, str_n, pat);
    default: return BruteForce (str, str_n, pat, pat_n);
    }
  }

  if (CHAR_BIT <= 10) {
    switch (pat_n) {    
  // short pattern
    case  2: return QuickSearch2   (str, str_n, pat);
    case  3: return QuickSearch3   (str, str_n, pat);
    case  4: return QuickSearch4   (str, str_n, pat);
    case  5: case 6: case 7: case 8:
             return QuickSearch    (str, str_n, pat, pat_n);
  // long pattern
    default: return TurboBoyerMoore(str, str_n, pat, pat_n);
    }
  }
  
  if (CHAR_BIT > 10) {
  // large alphabet
    U8 *p = memchr(str, *pat, str_n-pat_n+1);
    if (!p) return 0;
    return KnuthMorrisPratt(p, str_n-(p-str), pat, pat_n);
  }
}

// -- find methods

defmethod(OBJ, gfind, String, String)
  U8* p;
  
  PRE
  POST
    self->value[self->size] = self2->value[self2->size] = '\0';
    U8 *q = (U8*)strstr((STR)self->value, (STR)self2->value);
    test_assert( p == q, "bug in substring searching");

  BODY
    p = findSub(self->value, self->size, self2->value, self2->size);
    if (!p) retmethod(Nil);
    
    OBJ svw = aStringView(self, atSlice(p-self->value,self2->size,1) );
    retmethod(gautoDelete( svw ));
endmethod

defmethod(OBJ, gifind, String, String)
  U8* p;
  
  PRE
  POST
    self->value[self->size] = self2->value[self2->size] = '\0';
    U8 *q = (U8*)strstr((STR)self->value, (STR)self2->value);
    test_assert( p == q, "bug in substring searching");

  BODY
    p = findSub(self->value, self->size, self2->value, self2->size);
    if (!p) retmethod(Nil);
    
    OBJ slc = aSlice(p-self->value,self2->size,1);
    retmethod(gautoDelete( slc ));  
endmethod


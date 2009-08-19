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
 | $Id: String_alg.c,v 1.5 2009/08/19 10:14:22 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/carray.h>

// -----

useclass(String, ExBadAlloc);
useclass(Lesser,Equal,Greater);

// ----- equality

defmethod(OBJ, gisEqual, String, String)
  if (self == self2)
    retmethod(True);

  if (self->size != self2->size)
    retmethod(False);

  retmethod( memcmp(self->value,self2->value,self->size) ? True : False );
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

  U8* val = self->value;
  U8* end = self->value + (self->size-1);
  U8  tmp;

  while (val != end)
    tmp = *val, *val++ = *end, *end++ = tmp;

endmethod

// ----- zip, zip3

defmethod(OBJ, gzip, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;

  struct String* str = String_alloc(2*size);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self->value; 
  U8* src2 = self2->value;

  while (dst != end) {
    *dst++ = *src1++;
    *dst++ = *src2++;
  }

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gzip3, String, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;
  if (size > self3->size) size = self3->size;

  struct String* str = String_alloc(3*size);

  U8* dst  = str->value;
  U8* end  = str->value + str->size;
  U8* src1 = self->value; 
  U8* src2 = self2->value;
  U8* src3 = self3->value;

  while (dst != end) {
    *dst++ = *src1++;
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

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat3, String, String, String)
  U32 size = self->size + self2->size + self3->size;

  struct String *str = String_alloc(size);
  U8* dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat4, String, String, String, String)
  U32 size = self->size + self2->size + self3->size + self4->size;

  struct String *str = String_alloc(size);
  U8* dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size); dst += self3->size;
  memcpy(dst,self4->value,self4->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat5, String, String, String, String, String)
  U32 size = self1->size + self2->size +
             self3->size + self4->size + self5->size;

  struct String *str = String_alloc(size);
  U8* dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size); dst += self3->size;
  memcpy(dst,self4->value,self4->size); dst += self4->size;
  memcpy(dst,self5->value,self5->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

// ----- search (char)

defmethod(OBJ, gfind, String, Char)
  U8* p = memchr(self->value, self2->Int.value, self->size);
  
  retmethod(p ? gautoDelete(aChar(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, String, Char)
  U8* p = memchr(self->value, self2->Int.value, self->size);

  retmethod(p ? gautoDelete(aInt(self->value-p)) : Nil);
endmethod

// ----- search (string)

// -- BruteForce

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
BruteForce(U8 *str, U32 str_n, U8 *pat, I32 pat_n)
{
  while((str = memchr(str, *pat, str_n-pat_n+1)) != 0) {
    if (memcmp(str+1,pat+1,pat_n-1) == 0)
      return str;
    str++;  
  }
  
  return 0;
}

// -- KnuthMorrisPratt

static U8*
KnuthMorrisPratt(U8 *str, U32 str_n, U8 *pat, I32 pat_n)
{
  I32 kmpNext[pat_n];

  // preprocessing
  {
    I32 i = 0;
    I32 j = kmpNext[0] = -1;

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

  // searching
  {
    I32 i = 0;
    U32 j = 0;

    while (j < str_n) {
      while (i > -1 && pat[i] != str[j])
        i = kmpNext[i];
      i++;
      j++;
      if (i >= pat_n) // found
        return str + (j - i);
    }
  }

  return 0;
}

// -- TurboBoyerMoore

// alphabet size
enum { ASIZE = 1 << CHAR_BIT };

static inline I32
min(I32 a, I32 b) {
  return a <= b ? a : b;
}

static inline I32
max(I32 a, I32 b) {
  return a >= b ? a : b;
}

static inline void
preBmBc(U8 *pat, I32 pat_n, I32 bmBc[]) {
   I32 i;
 
   for (i = 0; i < ASIZE; ++i)
      bmBc[i] = pat_n;
   for (i = 0; i < pat_n - 1; ++i)
      bmBc[pat[i]] = pat_n - i - 1;
}
 
static inline void
preBmGs(U8* pat, I32 pat_n, I32 bmGs[], I32 suff[])
{
  I32 i, j, f, g;

   suff[pat_n-1] = pat_n;
   g = pat_n-1;
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

// -- find front-end

static U8*
find(U8 *str, U32 str_n, U8 *pat, U32 pat_n)
{
  if (!pat_n || str_n < pat_n) return 0;

  // very short string or pattern: brute force
  if (str_n <= 32 || pat_n < 4)
    switch(pat_n) {
    case  0: return str;
    case  1: return memchr(str, *pat, str_n-pat_n+1);
    case  2: BruteForce2(str, str_n, pat);
    case  3: BruteForce3(str, str_n, pat);
    default: BruteForce (str, str_n, pat, pat_n);
    }

  // short string or pattern or large alphabet: linear
  if (str_n <= 5*ASIZE || pat_n <= 16 || CHAR_BIT > 10) {
    U8 *p = memchr(str, *pat, str_n-pat_n+1);
    if (!p) return 0;
    return KnuthMorrisPratt(p, str_n-(p-str), pat, pat_n);
  }

  // long string and long pattern: linear to sublinear
  return TurboBoyerMoore(str, str_n, pat, pat_n);
}

// -- find methods

defmethod(OBJ, gfind, String, String)
  U8* p = find(self->value, self->size, self2->value, self2->size);
  
  if (!p) retmethod(Nil);
    
  OBJ svw = aStringView(self, atSlice(p-self->value,self2->size,1) );

  retmethod(gautoDelete( svw ));  
endmethod

defmethod(OBJ, gifind, String, String)
  U8* p = find(self->value, self->size, self2->value, self2->size);

  if (!p) retmethod(Nil);
  
  OBJ slc = aSlice(p-self->value,self2->size,1);

  retmethod(gautoDelete( slc ));  
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - algorithms not using functor
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
 | $Id: Vector_alg.c,v 1.7 2009/09/08 00:49:44 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// ----- equality

defmethod(OBJ, gisEqual, T, T)
  if (self == self2)
    retmethod(True);

  if (self->size != self2->size)
    retmethod(False);

  VAL *val1   = self->valref;
  I32  val1_s = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  VAL *val2   = self2->valref;
  I32  val2_s = self2->stride;
  
  while (val1 != end) {
    if (EQUAL(*val1,*val2) != True)
      retmethod(False);
    val1 += val1_s;
    val2 += val2_s;
  }

  retmethod(True);
endmethod

// ----- in place

defmethod(void, greverse, T)
  if (self->size < 2)
    retmethod();

  VAL *val   = self->valref;
  I32  val_s = self->stride;
  VAL *end   = self->valref + (self->size-1)*self->stride;

  if (val_s > 0)
    while (val < end) {
      SWAP(*val,*end);
      val += val_s;
      end -= val_s;
    }
  else
    while (val > end) {
      SWAP(*val,*end);
      val += val_s;
      end -= val_s;
    }
endmethod

defmethod(void, gpermute, T, IntVector)
  PRE
    test_assert( self->size == self2->size, "incompatible " TS " sizes" );

  BODY
    if (self->size < 2)
      retmethod();

    VAL *val   = self->valref;
    U32  val_n = self->size;
    I32  val_s = self->stride;
    I32 *idx   = self2->value;
    I32  idx_s = self2->stride;

    TMPARRAY_CREATE(VAL,buf,val_n); // VAL buf[val_n];
    TMPARRAY_CREATE(U8 ,flg,val_n); // U8  flg[val_n];

    memset(flg,1,val_n);

    VAL *cur, *end = buf + val_n;
    U32  i = 0;

    // permute
    for (cur = buf; cur != end; cur++) {
      i = Range_index(*idx, val_n);
      if ( !(i < val_n && flg[i]) ) break;
      *cur = val[i*val_s], flg[i] = 0;
       idx += idx_s;
    }

    if (cur == end) {
      // copy back
      for (cur = buf; cur != end; cur++)
        *val = *cur, val += val_s;

      TMPARRAY_DESTROY(buf);
      TMPARRAY_DESTROY(flg);
    } else {
      // rollback (error)
      BOOL iiir = i < val_n; // last index-is-in-range flag

      while (cur != buf) {
        idx -= idx_s;
        i = Range_index(*idx, val_n);
        val[i*val_s] = *--cur;
      }

      TMPARRAY_DESTROY(buf);
      TMPARRAY_DESTROY(flg);
      test_assert( iiir, "index out of range" );
      test_assert(    0, "invalid cyclic permutation" );
    }
endmethod

// ----- repeat

defmethod(OBJ, grepeat, TE, Int)
  retmethod(gautoDelete( gnewWith2(T,_2,_1) ));
endmethod

// ----- zip, zip3, zip4

defmethod(OBJ, gzip, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;

  struct T* vec = T_alloc(2*size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self->valref; 
  I32  src1_s = self->stride;
  VAL *src2   = self2->valref;
  I32  src2_s = self2->stride;

  while (dst != end) {
    *dst++ = RETAIN(*src1), src1 += src1_s;
    *dst++ = RETAIN(*src2), src2 += src2_s;
  }

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gzip3, T, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
  if (size > self3->size) size = self3->size;

  struct T* vec = T_alloc(3*size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self->valref; 
  I32  src1_s = self->stride;
  VAL *src2   = self2->valref;
  I32  src2_s = self2->stride;
  VAL *src3   = self3->valref;
  I32  src3_s = self3->stride;

  while (dst != end) {
    *dst++ = RETAIN(*src1), src1 += src1_s;
    *dst++ = RETAIN(*src2), src2 += src2_s;
    *dst++ = RETAIN(*src3), src3 += src3_s;
  }

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gzip4, T, T, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
  if (size > self3->size) size = self3->size;
  if (size > self4->size) size = self4->size;

  struct T* vec = T_alloc(4*size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self->valref; 
  I32  src1_s = self->stride;
  VAL *src2   = self2->valref;
  I32  src2_s = self2->stride;
  VAL *src3   = self3->valref;
  I32  src3_s = self3->stride;
  VAL *src4   = self4->valref;
  I32  src4_s = self4->stride;

  while (dst != end) {
    *dst++ = RETAIN(*src1), src1 += src1_s;
    *dst++ = RETAIN(*src2), src2 += src2_s;
    *dst++ = RETAIN(*src3), src3 += src3_s;
    *dst++ = RETAIN(*src4), src4 += src4_s;
  }

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gzip5, T, T, T, T, T)
  U32 size = self->size < self2->size ? self->size : self2->size;
  if (size > self3->size) size = self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;

  struct T* vec = T_alloc(5*size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self->valref; 
  I32  src1_s = self->stride;
  VAL *src2   = self2->valref;
  I32  src2_s = self2->stride;
  VAL *src3   = self3->valref;
  I32  src3_s = self3->stride;
  VAL *src4   = self4->valref;
  I32  src4_s = self4->stride;
  VAL *src5   = self5->valref;
  I32  src5_s = self5->stride;

  while (dst != end) {
    *dst++ = RETAIN(*src1), src1 += src1_s;
    *dst++ = RETAIN(*src2), src2 += src2_s;
    *dst++ = RETAIN(*src3), src3 += src3_s;
    *dst++ = RETAIN(*src4), src4 += src4_s;
    *dst++ = RETAIN(*src5), src5 += src5_s;
  }

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- cat, cat3, cat4, cat5

defmethod(OBJ, gcat, T, T)
  U32 size = self->size + self2->size;

  struct T *vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + self->size;
  VAL *src   = self->valref;
  I32  src_s = self->stride;

  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->valref;
  src_s = self2->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gcat3, T, T, T)
  U32 size = self->size + self2->size + self3->size;

  struct T *vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + self->size;
  VAL *src   = self->valref;
  I32  src_s = self->stride;

  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->valref;
  src_s = self2->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  end  += self3->size;
  src   = self3->valref;
  src_s = self3->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gcat4, T, T, T, T)
  U32 size = self->size + self2->size + self3->size + self4->size;

  struct T *vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + self->size;
  VAL *src   = self->valref;
  I32  src_s = self->stride;

  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->valref;
  src_s = self2->stride;

  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  end  += self3->size;
  src   = self3->valref;
  src_s = self3->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  end  += self4->size;
  src   = self4->valref;
  src_s = self4->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gcat5, T, T, T, T, T)
  U32 size = self->size + self2->size +
             self3->size + self4->size + self5->size;

  struct T *vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PROTECT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + self->size;
  VAL *src   = self->valref;
  I32  src_s = self->stride;

  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;
  
  end  += self2->size;
  src   = self2->valref;
  src_s = self2->stride;

  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  end  += self3->size;
  src   = self3->valref;
  src_s = self3->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  end  += self4->size;
  src   = self4->valref;
  src_s = self4->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  end  += self5->size;
  src   = self5->valref;
  src_s = self5->stride;
  
  while (dst != end)
    *dst++ = RETAIN(*src), src += src_s;

  UNPROTECT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- search (object)

static VAL*
findVal(VAL *val, U32 val_n, I32 val_s, VAL _2)
{
  if (!val_n) return 0;

  VAL *end = val + val_n*val_s;

  while (val != end) {
    if (EQUAL(*val, _2) == True)
      return val;
    val += val_s;
  }

  return 0;  
}

defmethod(OBJ, gfind, T, Object)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findVal(val,val_n,val_s,TOVAL(_2));

  retmethod( p ? AUTODELETE(VALOBJ(*p)) : Nil );  
endmethod

defmethod(OBJ, gifind, T, Object)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findVal(val,val_n,val_s,TOVAL(_2));

  retmethod(p ? gautoDelete( aInt((p-val)/val_s) ) : Nil);
endmethod

// ----- search (array)

// -- KnuthMorrisPratt (linear)

static VAL*
KnuthMorrisPratt(VAL *val, U32 val_n, I32 val_s, VAL *pat, I32 pat_n, I32 pat_s)
{
  TMPARRAY_CREATE(I32,kmpNext,pat_n);

  { // preprocessing
    I32 i = 0, j = kmpNext[0] = -1;

    while (i < pat_n) {
      while (j > -1 && EQUAL(pat[i*pat_s],pat[j*pat_s]) == False)
        j = kmpNext[j];
      i++;
      j++;
      if (EQUAL(pat[i*pat_s],pat[j*pat_s]) == True)
        kmpNext[i] = kmpNext[j];
      else
        kmpNext[i] = j;
    }
  }
 
  { // searching
    I32 i = 0;
    U32 j = 0;

    while (j < val_n) {
      while (i > -1 && EQUAL(pat[i*pat_s],val[j*val_s]) == False)
        i = kmpNext[i];
      i++;
      j++;
      if (i >= pat_n) { // found
        TMPARRAY_DESTROY(kmpNext);
        return val + (j - i)*val_s;
      }
    }
  }

  TMPARRAY_DESTROY(kmpNext);
  return 0;
}

// -- find front-end

static VAL*
findSub(VAL *val, U32 val_n, I32 val_s, VAL *pat, U32 pat_n, I32 pat_s)
{
  // string too short
  if (val_n < pat_n) return 0;

  // empty pattern
  if (!pat_n) return val;

  // find first
  VAL *p = findVal(val, val_n, val_s, *pat);
  if (!p) return 0;

  // single object pattern
  if (pat_n == 1) return p;

  // linear search
  return KnuthMorrisPratt(p, val_n-(p-val)*val_s, val_s, pat, pat_n, pat_s);
}

// -- find methods

defmethod(OBJ, gfind, T, T)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findSub(val,val_n,val_s,self2->valref,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ avw = aTView(self, atSlice((p-val)/val_s,self2->size,val_s) );
  retmethod(gautoDelete( avw ));
endmethod

defmethod(OBJ, gifind, T, T)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findSub(val,val_n,val_s,self2->valref,self2->size,self2->stride);
  if (!p) retmethod(Nil);

  OBJ slc = aSlice((p-val)/val_s,self2->size,val_s);
  retmethod(gautoDelete( slc ));  
endmethod


/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - algorithms using functors
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
 | $Id: Vector_fun.c,v 1.4 2009/09/14 13:35:15 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// ----- apply (in-place map with returned value discarded)

defmethod(void, gapply, Functor, T)
  U32  size  = self2->size;
  I32  val_s = self2->stride;
  VAL *val   = self2->valref;
  VAL *end   = val + val_s*size;

  while (val != end) {
    geval1(_1, VALOBJ(*val));
    val += val_s;
  }
endmethod

defmethod(void, gapply2, Functor, T, T)
  U32  size   = self2->size < self3->size ? self2->size : self3->size;
  I32  val_s  = self2->stride;
  VAL *val    = self2->valref;
  I32  val2_s = self3->stride;
  VAL *val2   = self3->valref;
  VAL *end    = val + val_s*size;

  while (val != end) {
    geval2(_1, VALOBJ(*val), VALOBJ(*val2));
    val  += val_s;
    val2 += val2_s;
  }
endmethod

defmethod(void, gapply3, Functor, T, T, T)
  U32  size   = self2->size < self3->size ? self2->size : self3->size;
       size   = self4->size < size ? self4->size : size;
  I32  val_s  = self2->stride;
  VAL *val    = self2->valref;
  I32  val2_s = self3->stride;
  VAL *val2   = self3->valref;
  I32  val3_s = self4->stride;
  VAL *val3   = self4->valref;
  VAL *end    = val + val_s*size;

  while (val != end) {
    geval3(_1, VALOBJ(*val), VALOBJ(*val2), VALOBJ(*val3));
    val  += val_s;
    val2 += val2_s;
    val3 += val3_s;
  }
endmethod

defmethod(void, gapply4, Functor, T, T, T, T)
  U32  size   = self2->size < self3->size ? self2->size : self3->size;
       size   = self4->size < size ? self4->size : size;
       size   = self5->size < size ? self5->size : size;
  I32  val_s  = self2->stride;
  VAL *val    = self2->valref;
  I32  val2_s = self3->stride;
  VAL *val2   = self3->valref;
  I32  val3_s = self4->stride;
  VAL *val3   = self4->valref;
  I32  val4_s = self5->stride;
  VAL *val4   = self5->valref;
  VAL *end    = val + val_s*size;

  while (val != end) {
    geval4(_1, VALOBJ(*val), VALOBJ(*val2), VALOBJ(*val3), VALOBJ(*val4));
    val  += val_s;
    val2 += val2_s;
    val3 += val3_s;
    val4 += val4_s;
  }
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, T)
  U32 size = self2->size;
  struct T* vec = T_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s = self2->stride;
  VAL *val   = self2->valref;
  U32 *dst_n = &vec->size;
  VAL *dst   = vec->valref;
  VAL *end   = dst + size;
  OBJ  res;

  while (dst != end) {
    res = geval1(_1, VALOBJ(*val));
    *dst++ = RETAIN(TOVAL(res)), ++*dst_n;
    val += val_s;
  }

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap2, Functor, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  struct T* vec = T_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s  = self2->stride;
  VAL *val    = self2->valref;
  I32  val2_s = self3->stride;
  VAL *val2   = self3->valref;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->valref;
  VAL *end    = dst + size;
  OBJ  res;

  while (dst != end) {
    res = geval2(_1, VALOBJ(*val), VALOBJ(*val2));
    *dst++ = RETAIN(TOVAL(res)), ++*dst_n;
    val  += val_s;
    val2 += val2_s;
  }

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap3, Functor, T, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
  struct T* vec = T_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s  = self2->stride;
  VAL *val    = self2->valref;
  I32  val2_s = self3->stride;
  VAL *val2   = self3->valref;
  I32  val3_s = self4->stride;
  VAL *val3   = self4->valref;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->valref;
  VAL *end    = dst + size;
  OBJ  res;

  while (dst != end) {
    res = geval3(_1, VALOBJ(*val), VALOBJ(*val2), VALOBJ(*val3));
    *dst++ = RETAIN(TOVAL(res)), ++*dst_n;
    val  += val_s;
    val2 += val2_s;
    val3 += val3_s;
  }

  retmethod(_vec);
endmethod

defmethod(OBJ, gmap4, Functor, T, T, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
      size = self4->size < size ? self4->size : size;
      size = self5->size < size ? self5->size : size;
  struct T* vec = T_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s  = self2->stride;
  VAL *val    = self2->valref;
  I32  val2_s = self3->stride;
  VAL *val2   = self3->valref;
  I32  val3_s = self4->stride;
  VAL *val3   = self4->valref;
  I32  val4_s = self5->stride;
  VAL *val4   = self5->valref;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->valref;
  VAL *end    = dst + size;
  OBJ  res;

  while (dst != end) {
    res = geval4(_1, VALOBJ(*val), VALOBJ(*val2), VALOBJ(*val3), VALOBJ(*val4));
    *dst++ = RETAIN(TOVAL(res)), ++*dst_n;
    val  += val_s;
    val2 += val2_s;
    val3 += val3_s;
    val4 += val4_s;
  }

  retmethod(_vec);
endmethod

// ----- all, any, count

defmethod(OBJ, gall, T, Functor)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;

  while (val != end) {
    if (geval1(_2, VALOBJ(*val)) != True)
      retmethod(False);
    val += val_s;
  }
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, T, Functor)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;

  while (val != end) {
    if (geval1(_2, VALOBJ(*val)) == True)
      retmethod(True);
    val += val_s;
  }
      
  retmethod(False);
endmethod

defmethod(U32, gcount, T, Functor)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;
  U32  cnt   = 0;

  while (val != end) {
    if (geval1(_2, VALOBJ(*val)) == True)
      ++cnt;
    val += val_s;
  }
      
  retmethod(cnt);
endmethod

// ----- select, reject

defmethod(OBJ, gselect, T, Functor)
  U32 size = self->size;
  OBJ _vec = gautoDelete(gnewWith(T,aInt(size)));
  struct T* vec = STATIC_CAST(struct T*, _vec);

  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *dst   = vec ->valref;
  VAL *end   = dst + size;

  while (dst != end) {
    if (geval1(_2, VALOBJ(*val)) == True)
      *dst++ = RETAIN(*val), vec->size++;
    val += val_s;
  }

  gadjust(_vec);
  retmethod(_vec);
endmethod

defmethod(OBJ, greject, T, Functor)
  U32 size = self->size;
  OBJ _vec = gautoDelete(gnewWith(T,aInt(size)));
  struct T* vec = STATIC_CAST(struct T*, _vec);

  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *dst   = vec ->valref;
  VAL *end   = dst + size;

  while (dst != end) {
    if (geval1(_2, VALOBJ(*val)) != True)
      *dst++ = RETAIN(*val), vec->size++;
    val += val_s;
  }

  gadjust(_vec);
  retmethod(_vec);
endmethod

// ----- reduce

defmethod(OBJ, greduce, T, Functor)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;
  OBJ  res   = Nil;

  if (val != end) {
    res  = gautoDelete(gclone(VALOBJ(*val)));
    val += val_s;
    
    while (val != end) {
      res = geval2(_2, res, VALOBJ(*val));
      val += val_s;
    }
  }

  retmethod(res);
endmethod

defmethod(OBJ, grreduce, T, Functor)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;
  OBJ  res   = Nil;

  if (val != end) {
    end -= val_s;
    res = gautoDelete(gclone(VALOBJ(*end)));

    while (val != end) {
      end -= val_s;
      res = geval2(_2, VALOBJ(*end), res);
    }
  }

  retmethod(res);
endmethod

defmethod(OBJ, greduce1, T, Functor, Object)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;
  OBJ  res   = _3;
  
  while (val != end) {
    res = geval2(_2, res, VALOBJ(*val));
    val += val_s;
  }

  retmethod(res);
endmethod

defmethod(OBJ, grreduce1, T, Functor, Object)
  U32  size  = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*size;
  OBJ  res   = _3;
  
  while (val != end) {
    end -= val_s;
    res = geval2(_2, VALOBJ(*end), res);
  }

  retmethod(res);
endmethod

defmethod(OBJ, greduce2, T, T, Functor, Object)
  U32  size   = self->size < self2->size ? self->size : self2->size;
  I32  val_s  = self->stride;
  VAL *val    = self->valref;
  I32  val2_s = self2->stride;
  VAL *val2   = self2->valref;
  VAL *end    = val + val_s*size;
  OBJ  res    = _4;

  while (val != end) {
    res = geval3(_3, res, VALOBJ(*val), VALOBJ(*val2));
    val  += val_s;
    val2 += val2_s;
  }

  retmethod(res);
endmethod

defmethod(OBJ, grreduce2, T, T, Functor, Object)
  U32  size   = self->size < self2->size ? self->size : self2->size;
  I32  val_s  = self->stride;
  VAL *end    = self->valref  + val_s*self->size;
  I32  val2_s = self2->stride;
  VAL *end2   = self2->valref + val2_s*self2->size;
  VAL *val    = end - val_s*size;
  OBJ  res    = _4;

  while (val != end) {
    end  -= val_s;
    end2 -= val2_s;
    res = geval3(_3, VALOBJ(*end), VALOBJ(*end2), res);
  }
  
  retmethod(res);
endmethod

// ----- accumulate

defmethod(OBJ, gaccumulate, T, Functor)
  U32 size = self->size;
  struct T* vec = T_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s = self->stride;
  VAL *val   = self->valref;
  U32 *dst_n  = &vec->size;
  VAL *dst   = vec->valref;
  VAL *end   = dst + size;
  OBJ  res;

  if (dst != end) {
    *dst = RETAIN(*val), ++*dst_n;
    val += val_s, --end;
    
    while (dst != end) {
      res = geval2(_2, VALOBJ(*dst), VALOBJ(*val));
      *++dst = RETAIN(TOVAL(res)), ++*dst_n;
      val += val_s;
    }
  }
  
  retmethod(_vec);
endmethod

defmethod(OBJ, graccumulate, T, Functor)
  U32 size = self->size;
  struct T* vec = T_alloc(size);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s = self->stride;
  VAL *val   = self->valref + val_s*size;
  U32 *dst_n  = &vec->size;
  VAL *dst   = vec->valref;
  VAL *end   = dst + size;
  OBJ  res;

  if (dst != end) {
    val -= val_s;
    *--end = RETAIN(*val), ++*dst_n;

    while (dst != end) {
      val -= val_s;
      res = geval2(_2, VALOBJ(*val), VALOBJ(*end));
      *--end = RETAIN(TOVAL(res)), ++*dst_n;
    }
  }
  
  retmethod(_vec);
endmethod

defmethod(OBJ, gaccumulate1, T, Functor, Object)
  U32 size = self->size;
  struct T* vec = T_alloc(size+1);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s = self->stride;
  VAL *val   = self->valref;
  U32 *dst_n  = &vec->size;
  VAL *dst   = vec->valref;
  VAL *end   = dst + size;
  OBJ  res;

  *dst = RETAIN(TOVAL(_3)), ++*dst_n;
  
  while (dst != end) {
    res = geval2(_2, VALOBJ(*dst), VALOBJ(*val));
    *++dst = RETAIN(TOVAL(res)), ++*dst_n;
    val += val_s;
  }

  retmethod(_vec);
endmethod

defmethod(OBJ, graccumulate1, T, Functor, Object)
  U32 size = self->size;
  struct T* vec = T_alloc(size+1);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s = self->stride;
  VAL *val   = self->valref + val_s*self->size;
  U32 *dst_n  = &vec->size;
  VAL *dst   = vec->valref;
  VAL *end   = dst + size;
  OBJ  res;

  *end = RETAIN(TOVAL(_3)), ++*dst_n;

  while (dst != end) {
    val -= val_s,
    res = geval2(_2, VALOBJ(*val), VALOBJ(*end));
    *--end = RETAIN(TOVAL(res)), ++*dst_n;
  }

  retmethod(_vec);
endmethod

defmethod(OBJ, gaccumulate2, T, T, Functor, Object)
  U32 size = self->size < self2->size ? self->size : self2->size;
  struct T* vec = T_alloc(size+1);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s  = self->stride;
  VAL *val    = self->valref;
  I32  val2_s = self2->stride;
  VAL *val2   = self2->valref;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->valref;
  VAL *end    = dst + size;
  OBJ  res;

  *dst = RETAIN(TOVAL(_4)), ++*dst_n;
  
  while (dst != end) {
    res = geval3(_3, VALOBJ(*dst), VALOBJ(*val), VALOBJ(*val2));
    *++dst = RETAIN(TOVAL(res)), ++*dst_n;
    val  += val_s;
    val2 += val2_s;
  }

  retmethod(_vec);
endmethod

defmethod(OBJ, graccumulate2, T, T, Functor, Object)
  U32 size = self->size < self2->size ? self->size : self2->size;
  struct T* vec = T_alloc(size+1);
  OBJ _vec = gautoDelete( (OBJ)vec );

  I32  val_s  = self->stride;
  VAL *val    = self->valref + val_s*self->size;
  I32  val2_s = self2->stride;
  VAL *val2   = self2->valref + val2_s*self2->size;
  U32 *dst_n  = &vec->size;
  VAL *dst    = vec->valref;
  VAL *end    = dst + size;
  OBJ  res;

  *end = RETAIN(TOVAL(_4)), ++*dst_n;

  while (dst != end) {
    val  -= val_s,
    val2 -= val2_s,
    res = geval3(_3, VALOBJ(*val), VALOBJ(*val2), VALOBJ(*end));
    *--end = RETAIN(TOVAL(res)), ++*dst_n;
  }

  retmethod(_vec);
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, T, Functor)
  U32 size = self->size;
  OBJ _vec = gautoDelete(gnewWith(T,aInt(size)));
  struct T* vec = STATIC_CAST(struct T*, _vec);

  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *dst   = vec ->valref;
  VAL *end   = val + val_s*size;

  if (val != end) {
    *dst = RETAIN(*val);
    val += val_s;

    while (val != end) {
      if (geval2(_2, VALOBJ(*dst), VALOBJ(*val)) != True)
        *++dst = RETAIN(*val), vec->size++;
      val += val_s;
    }
  }
  
  gadjust(_vec);
  retmethod(_vec);
endmethod

// ----- finding

static VAL*
findFun(VAL *val, U32 val_n, I32 val_s, OBJ _2)
{
  if (!val_n) return 0;

  OBJ res = geval1(_2, VALOBJ(*val)); // compare first element

  if (res == True || res == Equal) // found
    return val;

  // linear search
  if (res == False) {
    VAL *end = val + val_s*val_n;

    val += val_s;
    while (val != end) {
      if (geval1(_2, VALOBJ(*val)) == True) // found
        return val;
      val += val_s;
    }

    return 0; // not found
  }

  // binary search
  if (res == Greater) {
    U32 lo = 1, hi = val_n-1;

    while (lo <= hi) {
      U32 i = (lo + hi) / 2;
      res = geval1(_2, VALOBJ(val[i*val_s]));

      if (res == Equal)
        return val + i*val_s; // found

      if (res == Lesser)
        hi = i-1;
      else
        lo = i+1;
    }
  }
  
  return 0; // not found
}

// ---

defmethod(OBJ, gfind, T, Functor)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;

  VAL *p = findFun(val,val_n,val_s,_2);

  retmethod(p ? AUTODELETE(VALOBJ(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, T, Functor)
  U32  val_n = self->size;
  I32  val_s = self->stride;
  VAL *val   = self->valref;

  VAL *p = findFun(val,val_n,val_s,_2);

  retmethod(p ? gautoDelete( aInt((p-val)/val_s) ) : Nil);
endmethod

// ----- sorting (in place)

#undef  NETSORT
#define NETSORT(a,s,r,ret) \
  do { \
    switch (r) { \
    case 1: \
      SORT(a[0*s],a[1*s]); \
      ret; \
    \
    case 2: \
      SORT(a[0*s],a[1*s]); \
      SORT(a[0*s],a[2*s]); \
      SORT(a[1*s],a[2*s]); \
      ret; \
    \
    case 3: \
      SORT(a[0*s],a[2*s]); SORT(a[1*s],a[3*s]); \
      SORT(a[0*s],a[1*s]); SORT(a[2*s],a[3*s]); \
      SORT(a[1*s],a[2*s]); \
      ret; \
    \
    case 4: \
      SORT(a[0*s],a[4*s]); SORT(a[1*s],a[3*s]); \
      SORT(a[0*s],a[2*s]); \
      SORT(a[2*s],a[4*s]); SORT(a[0*s],a[1*s]); \
      SORT(a[2*s],a[3*s]); SORT(a[1*s],a[4*s]); \
      SORT(a[1*s],a[2*s]); SORT(a[3*s],a[4*s]); \
      ret; \
    \
    case 5: \
      SORT(a[0*s],a[4*s]); SORT(a[1*s],a[5*s]); \
      SORT(a[0*s],a[2*s]); SORT(a[1*s],a[3*s]); \
      SORT(a[2*s],a[4*s]); SORT(a[3*s],a[5*s]); \
      SORT(a[0*s],a[1*s]); SORT(a[4*s],a[5*s]); \
      SORT(a[1*s],a[4*s]); SORT(a[2*s],a[3*s]); \
      SORT(a[1*s],a[2*s]); SORT(a[3*s],a[4*s]); \
      ret; \
    } \
  } while (0)

#undef  EXCH
#undef  SORT
#define EXCH(a,b) (t=(a),(a)=(b),(b)=t)
#define SORT(a,b) if (GCMP(b,a) == Lesser) EXCH(a,b)

static inline U32
pivot(void)
{
  static U32 x = 1; // no need to be thread safe
  
  return x = x * 2621124293u + 1;
}

/* from "Quicksort Is Optimal", R. Sedgwick & J. Bentley, 2002
   plus some practical improvements.
 */

#undef  GCMP
#define GCMP(a,b) geval2(fun,VALOBJ(a),VALOBJ(b))

static void
qsortFun(VAL a[], I32 r, OBJ fun)
{
  I32 i, j, p, q;
  OBJ ri, rj;
  VAL t;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,1,r,return);

  // select pivot as the median-of-three taken pseudo-randomly
  i = pivot() % (r+1) + 0, EXCH(a[i],a[0  ]);
  i = pivot() % (r  ) + 1, EXCH(a[i],a[r  ]);
  i = pivot() % (r-1) + 1, EXCH(a[i],a[r-1]);
  SORT(a[0],a[r-1]);
  if ((ri = GCMP(a[r  ],a[0])) == Lesser) EXCH(a[r],a[0  ]);
  if ((rj = GCMP(a[r-1],a[r])) == Lesser) EXCH(a[r],a[r-1]);

  // partitioning initialization
  i = 0, j = r-1;
  p = ri == Equal ? i : -1;
  q = rj == Equal ? j :  r;

  // three-way partitioning
  for (;;) {
    while ((rj = GCMP(a[++i],a[  r])) == Lesser     ) ;
    while ((ri = GCMP(a[  r],a[--j])) == Lesser && j) ;

    if (i >= j) break;

    EXCH(a[i], a[j]);
    if (ri == Equal) ++p, EXCH(a[p],a[i]);
    if (rj == Equal) --q, EXCH(a[q],a[j]);
  }

  // move pivot to center
  EXCH(a[i], a[r]);

  // move equal partition from borders to center
  for (j = i-1; p-- > 0; j--) EXCH(a[p],a[j]);
  for (i = i+1; ++q < r; i++) EXCH(a[q],a[i]);

  // divide & conquer (small first)
  VAL *small, *large;
  
  if (j < r-i)
    small = a, large = a+i, p = j, q = r-i;
  else
    large = a, small = a+i, q = j, p = r-i;

  qsortFun(small,p,fun);
  qsortFun(large,q,fun); // tail recursion
}

static void
qsortSFun(VAL a[], I32 r, I32 s, OBJ fun)
{
  I32 i, j, p, q;
  OBJ ri, rj;
  VAL t;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,s,r,return);

  // select pivot as the median-of-three taken pseudo-randomly
  i = pivot() % (r+1) + 0, EXCH(a[i*s],a[ 0   *s]);
  i = pivot() % (r  ) + 1, EXCH(a[i*s],a[ r   *s]);
  i = pivot() % (r-1) + 1, EXCH(a[i*s],a[(r-1)*s]);
  SORT(a[0*s],a[(r-1)*s]);
  if ((ri = GCMP(a[ r   *s],a[0*s])) == Lesser) EXCH(a[r*s],a[ 0   *s]);
  if ((rj = GCMP(a[(r-1)*s],a[r*s])) == Lesser) EXCH(a[r*s],a[(r-1)*s]);

  // partitioning initialization
  i = 0, j = r-1;
  p = ri == Equal ? i : -1;
  q = rj == Equal ? j :  r;

  // three-way partitioning
  for (;;) {
    while ((rj = GCMP(a[++i*s],a[  r*s])) == Lesser     ) ;
    while ((ri = GCMP(a[  r*s],a[--j*s])) == Lesser && j) ;

    if (i >= j) break;

    EXCH(a[i*s], a[j*s]);
    if (ri == Equal) ++p, EXCH(a[p*s],a[i*s]);
    if (rj == Equal) --q, EXCH(a[q*s],a[j*s]);
  }

  // move pivot to center
  EXCH(a[i*s], a[r*s]);

  // move equal partition from borders to center
  for (j = i-1; p-- > 0; j--) EXCH(a[p*s],a[j*s]);
  for (i = i+1; ++q < r; i++) EXCH(a[q*s],a[i*s]);

  // divide & conquer (small first)
  VAL *small, *large;
  
  if (j < r-i)
    small = a, large = a+i*s, p = j, q = r-i;
  else
    large = a, small = a+i*s, q = j, p = r-i;

  qsortSFun(small,p,s,fun);
  qsortSFun(large,q,s,fun); // tail recursion
}

// ----- indirect sorting (return permutation)

#undef  GCMP
#define GCMP(a,b) geval2(fun,VALOBJ(o[a*s]),VALOBJ(o[b*s]))

static void
iqsortSFun(I32 a[], I32 r, VAL o[], I32 s, OBJ fun)
{
  I32 i, j, p, q, t;
  OBJ ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,1,r,return);

  // select pivot as the median-of-three taken pseudo-randomly
  i = pivot() % (r+1) + 0, EXCH(a[i],a[0  ]);
  i = pivot() % (r  ) + 1, EXCH(a[i],a[r  ]);
  i = pivot() % (r-1) + 1, EXCH(a[i],a[r-1]);
  SORT(a[0],a[r-1]);
  if ((ri = GCMP(a[r  ],a[0])) == Lesser) EXCH(a[r],a[0  ]);
  if ((rj = GCMP(a[r-1],a[r])) == Lesser) EXCH(a[r],a[r-1]);

  // partitioning initialization
  i = 0, j = r-1;
  p = ri == Equal ? i : -1;
  q = rj == Equal ? j :  r;

  // three-way partitioning
  for (;;) {
    while ((rj = GCMP(a[++i],a[  r])) == Lesser     ) ;
    while ((ri = GCMP(a[  r],a[--j])) == Lesser && j) ;

    if (i >= j) break;

    EXCH(a[i], a[j]);
    if (ri == Equal) ++p, EXCH(a[p],a[i]);
    if (rj == Equal) --q, EXCH(a[q],a[j]);
  }

  // move pivot to center
  EXCH(a[i], a[r]);

  // move equal partition from borders to center
  for (j = i-1; p-- > 0; j--) EXCH(a[p],a[j]);
  for (i = i+1; ++q < r; i++) EXCH(a[q],a[i]);

  // divide & conquer (small first)
  I32 *small, *large;
  
  if (j < r-i)
    small = a, large = a+i, p = j, q = r-i;
  else
    large = a, small = a+i, q = j, p = r-i;

  iqsortSFun(small,p,o,s,fun);
  iqsortSFun(large,q,o,s,fun); // tail recursion
}

// ----- sorting methods

defmethod(void, gsort, T, Functor)
  qsortFun(self->valref, self->size-1, _2);
endmethod

defmethod(void, gsort, TV, Functor)
  struct T *vec = &self->T;

  if (vec->stride == 1) {
    qsortFun(vec->valref, vec->size-1, _2);
    return;
  }

  if (vec->stride == -1) { // should be faster than strided sort
    qsortFun(vec->valref-vec->size+1, vec->size-1, _2);
    greverse(_1);
    return;
  }

  qsortSFun(vec->valref, vec->size-1, vec->stride, _2);
endmethod

defmethod(OBJ, gisort, T, Functor)
  useclass(IntVector);

  OBJ _vec = gautoDelete(gnewWith(IntVector, aSlice(0,self->size,1)));
  struct IntVector *vec = STATIC_CAST(struct IntVector*, _vec);

  iqsortSFun(vec->value, vec->size-1, self->valref, self->stride, _2);

  retmethod(_vec);
endmethod

// ----- is sorted predicate

defmethod(OBJ, gisSorted, T, Functor)
  U32 size = self->size;
  if (size < 2) retmethod(True);

  I32  val_s = self->stride;
  VAL *val   = self->valref;
  VAL *end   = val + val_s*(size-1);

  while (val != end) {
    if (geval2(_2, VALOBJ(*val), VALOBJ(val[val_s])) == Greater)
      retmethod(False);
    val += val_s;
  }

  retmethod(True);
endmethod


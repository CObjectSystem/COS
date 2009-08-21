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
 | $Id: Vector_fun.c,v 1.1 2009/08/21 12:10:00 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// ----- foreach (in place, discard fun returned value)

defmethod(void, gforeach, T, Functor)
  VAL *val   = self->valref;
  I32  val_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;

  while (val != end) {
    geval1(_2, VALOBJ(*val));
    val += val_s;
  }
endmethod

// ----- apply (in place map)

defmethod(void, gapply, Functor, T)
  VAL *val   = self2->valref;
  I32  val_s = self2->stride;
  VAL *end   = self2->valref + self2->size*self2->stride;

  while (val != end) {
    OBJ new = geval1(_1, VALOBJ(*val));
    ASSIGN(*val, TOVAL(new));
    val += val_s;
  }
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, T)
  struct T* vec = T_alloc(self2->size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + vec->size;
  VAL *src   = self2->valref;
  I32  src_s = self2->stride;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( geval1(_1,VALOBJ(*src)) ));
    src += src_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap2, Functor, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( geval2(_1,VALOBJ(*src1),VALOBJ(*src2)) ));
    src1 += src1_s;
    src2 += src2_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap3, Functor, T, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;
  VAL *src3   = self4->valref;
  I32  src3_s = self4->stride;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( geval3(_1,VALOBJ(*src1),VALOBJ(*src2),
                                     VALOBJ(*src3)) ));
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap4, Functor, T, T, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;
  VAL *src3   = self4->valref;
  I32  src3_s = self4->stride;
  VAL *src4   = self5->valref;
  I32  src4_s = self5->stride;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( geval4(_1,VALOBJ(*src1),VALOBJ(*src2),
                                     VALOBJ(*src3),VALOBJ(*src4)) ));
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
    src4 += src4_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- all, any

defmethod(OBJ, gall, T, Functor)
  VAL *val   = self->valref;
  I32  val_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;

  while (val != end) {
    if (geval1(_2, VALOBJ(*val)) != True)
      retmethod(False);
    val += val_s;
  }
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, T, Functor)
  VAL *val   = self->valref;
  I32  val_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;

  while (val != end) {
    if (geval1(_2, VALOBJ(*val)) == True)
      retmethod(True);
    val += val_s;
  }
      
  retmethod(False);
endmethod

// ----- filter, filterOut fold, scan

defmethod(OBJ, gfilter, T, Functor)
  OBJ _vec = gnewWith(T,aInt(self->size)); PRT(_vec);
  struct T* vec = STATIC_CAST(struct T*, _vec);

  VAL *dst   = vec ->valref;
  VAL *src   = self->valref;
  I32  src_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;

  while (src != end) {
    if (geval1(_2, VALOBJ(*src)) == True)
      *dst++ = RETAIN(*src), ++vec->size;
    src += src_s;
  }

  gadjust(_vec);
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gfilterOut, T, Functor)
  OBJ _vec = gnewWith(T,aInt(self->size)); PRT(_vec);
  struct T* vec = STATIC_CAST(struct T*, _vec);

  VAL *dst   = vec ->valref;
  VAL *src   = self->valref;
  I32  src_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;

  while (src != end) {
    if (geval1(_2, VALOBJ(*src)) == False)
      *dst++ = RETAIN(*src), ++vec->size;
    src += src_s;
  }

  gadjust(_vec);
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gfoldl, T, Functor, Object)
  VAL *src   = self->valref;
  I32  src_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;
  OBJ  res   = _3;
  
  while (src != end) {
    res = geval2(_2, res, VALOBJ(*src));
    src += src_s;
  }

  retmethod(res);
endmethod

defmethod(OBJ, gfoldr, T, Functor, Object)
  VAL *src   = self->valref + self->size*self->stride;
  I32  src_s = self->stride;
  VAL *end   = self->valref;
  OBJ res    = _3;
  
  while (src != end) {
    src -= src_s;
    res = geval2(_2, VALOBJ(*src), res);
  }

  retmethod(res);
endmethod

defmethod(OBJ, gscanl, T, Functor, Object)
  struct T* vec = T_alloc(self->size+1);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + vec->size;
  VAL *src   = self->valref;
  I32  src_s = self->stride;

  *dst++ = RETAIN(TOVAL(_3));
  
  while (dst != end) {
    *dst = RETAIN(TOVAL( geval2(_2, VALOBJ(dst[-1]), VALOBJ(*src)) ));
    src += src_s, dst++;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gscanr, T, Functor, Object)
  struct T* vec = T_alloc(self->size+1);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst   = vec->valref + vec->size;
  VAL *end   = vec->valref;
  VAL *src   = self->valref + self->size*self->stride;
  I32  src_s = self->stride;

  *--dst = RETAIN(TOVAL(_3));

  while (dst != end) {
    src -= src_s, dst--;
    *dst = RETAIN(TOVAL( geval2(_2, VALOBJ(*src), VALOBJ(dst[1])) ));
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, T, Functor)
  if (self->size < 1)
    retmethod( gautoDelete(gclone(_1)) );

  OBJ _vec = gnewWith(T,aInt(self->size)); PRT(_vec);
  struct T* vec = STATIC_CAST(struct T*, _vec);

  VAL *dst   = vec ->valref;
  VAL *src   = self->valref;
  I32  src_s = self->stride;
  VAL *end   = self->valref + (self->size-1)*self->stride;

  while (src != end) {
    if (geval2(_2, VALOBJ(*src), VALOBJ(src[src_s])) != True)
      *dst++ = RETAIN(*src), ++vec->size;
    src += src_s;
  }
  *dst++ = RETAIN(*src);

  gadjust(_vec);
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- finding

static VAL*
findFun(VAL *val, U32 val_n, I32 val_s, OBJ _2)
{
  if (!val_n) return 0;

  OBJ res = geval1(_2, VALOBJ(*val)); // bsearch order

  if (res == True || res == Equal) // found
    return val;

  // linear search
  if (res == False) {
    VAL *end = val + val_n*val_s;

    val += val_s;
    while (val != end) {
      if (geval1(_2, VALOBJ(*val)) == True) // found
        return val;
      val += val_s;
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
    res = geval1(_2, VALOBJ(val[i*val_s]));

    if (res == Equal)
      return val + i*val_s; // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

  return 0;  
}

// ---

defmethod(OBJ, gfind, T, Functor)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findFun(val,val_n,val_s,_2);

  retmethod(p ? AUTODELETE(VALOBJ(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, T, Functor)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findFun(val,val_n,val_s,_2);

  retmethod(p ? gautoDelete( aInt((p-val)/val_s) ) : Nil);
endmethod

// ----- sorting (in place)

#undef  NETSORT
#define NETSORT(a,r,ret) \
  do { \
    switch (r) { \
    case 1: \
      SORT(a[0],a[1]); \
      ret; \
    \
    case 2: \
      SORT(a[0],a[1]); \
      SORT(a[0],a[2]); \
      SORT(a[1],a[2]); \
      ret; \
    \
    case 3: \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[0],a[1]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); \
      ret; \
    \
    case 4: \
      SORT(a[0],a[4]); SORT(a[1],a[3]); \
      SORT(a[0],a[2]); \
      SORT(a[2],a[4]); SORT(a[0],a[1]); \
      SORT(a[2],a[3]); SORT(a[1],a[4]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      ret; \
    \
    case 5: \
      SORT(a[0],a[4]); SORT(a[1],a[5]); \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[2],a[4]); SORT(a[3],a[5]); \
      SORT(a[0],a[1]); SORT(a[4],a[5]); \
      SORT(a[1],a[4]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
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
  NETSORT(a,r,return);

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
  VAL *s, *l;
  
  if (j < r-i)
    s = a, l = a+i, p = j, q = r-i;
  else
    l = a, s = a+i, q = j, p = r-i;

  qsortFun(s,p,fun);
  qsortFun(l,q,fun); // tail recursion
}

// -----

defmethod(void, gsort, T, Functor)
  if (self->stride == 1) {
    qsortFun(self->valref, self->size-1, _2);
    return;
  }

  if (self->stride == -1) {
    qsortFun(self->valref-self->size+1, self->size-1, _2);
    greverse(_1);
    return;
  }

  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  TMPARRAY_CREATE(VAL,buf,val_n); // VAL buf[val_n];

  VAL *cur, *end = buf + val_n;

  // forward copy
  for (cur = buf; cur != end; cur++)
    *cur = *val, val += val_s;

  qsortFun(buf, self->size-1, _2);

  // backward copy
  for (cur = buf; cur != end; cur++)
    *val = *cur, val += val_s;

  TMPARRAY_DESTROY(buf);
endmethod

// ----- indirect sorting (return permutation)

#undef  GCMP
#define GCMP(a,b) geval2(fun,VALOBJ(o[a]),VALOBJ(o[b]))

static void
iqsortFun(I32 a[], VAL o[], I32 r, OBJ fun)
{
  I32 i, j, p, q, t;
  OBJ ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,r,return);

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
  I32 *s, *l;
  
  if (j < r-i)
    s = a, l = a+i, p = j, q = r-i;
  else
    l = a, s = a+i, q = j, p = r-i;

  iqsortFun(s,o,p,fun);
  iqsortFun(l,o,q,fun); // tail recursion
}

defmethod(OBJ, gisort, T, Functor)
  useclass(IntVector);

  OBJ _vec = gnewWith(IntVector, aSlice(0,self->size,1)); PRT(_vec);
  struct IntVector *vec = STATIC_CAST(struct IntVector*, _vec);

  iqsortFun(vec->value, self->valref, self->size-1, _2);
  
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- is sorted predicate

defmethod(OBJ, gisSorted, T, Functor)
  if (self->size < 2)
    retmethod(True);

  VAL *val   = self->valref;
  I32  val_s = self->stride;
  VAL *end   = self->valref + (self->size-1)*self->stride;

  while (val != end) {
    if (geval2(_2, VALOBJ(*val), VALOBJ(val[val_s])) == False)
      retmethod(False);
    val += val_s;
  }

  retmethod(True);
endmethod


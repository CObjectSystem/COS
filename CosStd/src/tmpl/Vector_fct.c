/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - algorithms using functions
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
 | $Id: Vector_fct.c,v 1.1 2009/08/21 12:10:00 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// ----- foreach (in place, discard fun returned value)

defmethod(void, gforeach, T, Function1)
  VAL *val    = self->valref;
  I32  val_s  = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  OBJFCT1 fct = self2->fct;

  while (val != end) {
    fct(VALOBJ(*val));
    val += val_s;
  }
endmethod

// ---
static inline void
foreach(VAL *val, OBJFCT1 fct, int n) {
  for (int i = 0; i != n; i++)
    fct(VALOBJ(val[i]));
}

defmethod(void, gforeach, COS_PP_CAT(T,0), Function1)
  foreach(self->T.valref, self2->fct, 0);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,1), Function1)
  foreach(self->T.valref, self2->fct, 1);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,2), Function1)
  foreach(self->T.valref, self2->fct, 2);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,3), Function1)
  foreach(self->T.valref, self2->fct, 3);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,4), Function1)
  foreach(self->T.valref, self2->fct, 4);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,5), Function1)
  foreach(self->T.valref, self2->fct, 5);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,6), Function1)
  foreach(self->T.valref, self2->fct, 6);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,7), Function1)
  foreach(self->T.valref, self2->fct, 7);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,8), Function1)
  foreach(self->T.valref, self2->fct, 8);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,9), Function1)
  foreach(self->T.valref, self2->fct, 9);
endmethod

// ----- apply (in place map)

defmethod(void, gapply, Function1, T)
  VAL *val    = self2->valref;
  I32  val_s  = self2->stride;
  VAL *end    = self2->valref + self2->size*self2->stride;
  OBJFCT1 fct = self->fct;

  while (val != end) {
    OBJ new = fct(VALOBJ(*val));
    ASSIGN(*val, TOVAL(new));
    val += val_s;
  }
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Function1, T)
  struct T* vec = T_alloc(self2->size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src    = self2->valref;
  I32  src_s  = self2->stride;
  OBJFCT1 fct = self->fct;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( fct(VALOBJ(*src)) ));
    src += src_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap2, Function2, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;
  OBJFCT2 fct = self->fct;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( fct(VALOBJ(*src1),VALOBJ(*src2)) ));
    src1 += src1_s;
    src2 += src2_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap3, Function3, T, T, T)
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
  OBJFCT3 fct = self->fct;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( fct(VALOBJ(*src1),VALOBJ(*src2),VALOBJ(*src3)) ));
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap4, Function4, T, T, T, T)
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
  OBJFCT4 fct = self->fct;

  while (dst != end) {
    *dst++ = RETAIN(TOVAL( fct(VALOBJ(*src1),VALOBJ(*src2),
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

defmethod(OBJ, gall, T, Function1)
  VAL *val    = self->valref;
  I32  val_s  = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  OBJFCT1 fct = self2->fct;

  while (val != end) {
    if (fct(VALOBJ(*val)) != True)
      retmethod(False);
    val += val_s;
  }
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, T, Function1)
  VAL *val    = self->valref;
  I32  val_s  = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  OBJFCT1 fct = self2->fct;

  while (val != end) {
    if (fct(VALOBJ(*val)) == True)
      retmethod(True);
    val += val_s;
  }
      
  retmethod(False);
endmethod

// ----- filter, filterOut, fold, scan

defmethod(OBJ, gfilter, T, Function1)
  OBJ _vec = gnewWith(T,aInt(self->size)); PRT(_vec);
  struct T* vec = STATIC_CAST(struct T*, _vec);

  VAL *dst    = vec->valref;
  VAL *src    = self->valref;
  I32  src_s  = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  OBJFCT1 fct = self2->fct;

  while (src != end) {
    if (fct(VALOBJ(*src)) == True)
      *dst++ = RETAIN(*src), ++vec->size;
    src += src_s;
  }

  gadjust(_vec);
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gfilterOut, T, Function1)
  OBJ _vec = gnewWith(T,aInt(self->size)); PRT(_vec);
  struct T* vec = STATIC_CAST(struct T*, _vec);

  VAL *dst    = vec ->valref;
  VAL *src    = self->valref;
  I32  src_s  = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  OBJFCT1 fct = self2->fct;

  while (src != end) {
    if (fct(VALOBJ(*src)) == False)
      *dst++ = RETAIN(*src), ++vec->size;
    src += src_s;
  }

  gadjust(_vec);
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gfoldl, T, Function2, Object)
  VAL *src    = self->valref;
  I32  src_s  = self->stride;
  VAL *end    = self->valref + self->size*self->stride;
  OBJFCT2 fct = self2->fct;
  OBJ  res    = _3;
  
  while (src != end) {
    res = fct(res, VALOBJ(*src));
    src += src_s;
  }

  retmethod(res);
endmethod

defmethod(OBJ, gfoldr, T, Function2, Object)
  VAL *src    = self->valref + self->size*self->stride;
  I32  src_s  = self->stride;
  VAL *end    = self->valref;
  OBJFCT2 fct = self2->fct;
  OBJ res     = _3;
  
  while (src != end) {
    src -= src_s;
    res = fct(VALOBJ(*src), res);
  }

  retmethod(res);
endmethod

defmethod(OBJ, gscanl, T, Function2, Object)
  struct T* vec = T_alloc(self->size+1);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src    = self->valref;
  I32  src_s  = self->stride;
  OBJFCT2 fct = self2->fct;

  *dst++ = RETAIN(TOVAL(_3));
  
  while (dst != end) {
    *dst = RETAIN(TOVAL( fct(VALOBJ(dst[-1]), VALOBJ(*src)) ));
    src += src_s, dst++;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gscanr, T, Function2, Object)
  struct T* vec = T_alloc(self->size+1);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref + vec->size;
  VAL *end    = vec->valref;
  VAL *src    = self->valref + self->size*self->stride;
  I32  src_s  = self->stride;
  OBJFCT2 fct = self2->fct;

  *--dst = RETAIN(TOVAL(_3));

  while (dst != end) {
    src -= src_s, dst--;
    *dst = RETAIN(TOVAL( fct(VALOBJ(*src), VALOBJ(dst[1])) ));
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, T, Function2)
  if (self->size < 1)
    retmethod( gautoDelete(gclone(_1)) );

  OBJ _vec = gnewWith(T,aInt(self->size)); PRT(_vec);
  struct T* vec = STATIC_CAST(struct T*, _vec);

  VAL *dst    = vec ->valref;
  VAL *src    = self->valref;
  I32  src_s  = self->stride;
  VAL *end    = self->valref + (self->size-1)*self->stride;
  OBJFCT2 fct = self2->fct;

  while (src != end) {
    if (fct(VALOBJ(*src), VALOBJ(src[src_s])) != True)
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
findFct(VAL *val, U32 val_n, I32 val_s, OBJFCT1 fct)
{
  if (!val_n) return 0;

  OBJ res = fct(VALOBJ(*val)); // bsearch order

  if (res == True || res == Equal) // found
    return val;

  // linear search
  if (res == False) {
    VAL *end = val + val_n*val_s;

    val += val_s;
    while (val != end) {
      if (fct(VALOBJ(*val)) == True) // found
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
    res = fct(VALOBJ(val[i*val_s]));

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

defmethod(OBJ, gfind, T, Function1)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findFct(val,val_n,val_s,self2->fct);

  retmethod(p ? AUTODELETE(VALOBJ(*p)) : Nil);  
endmethod

defmethod(OBJ, gifind, T, Function1)
  VAL *val   = self->valref;
  U32  val_n = self->size;
  I32  val_s = self->stride;

  VAL *p = findFct(val,val_n,val_s,self2->fct);

  retmethod(p ? gautoDelete( aInt((p-val)/val_s) ) : Nil);
endmethod

// ----- sorting (in place)

#ifndef NETSORT
#error "this template file requires tmpl/Vector_fun.c"
#endif

/* from "quicksort Is Optimal", R. Sedgwick & J. Bentley, 2002
   plus some practical improvements.
 */

#undef  GCMP
#define GCMP(a,b) fct(VALOBJ(a),VALOBJ(b))

static void
qsortFct(VAL a[], I32 r, OBJFCT2 fct)
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

  qsortFct(s,p,fct);
  qsortFct(l,q,fct); // tail recursion
}

// -----

defmethod(void, gsort, T, Function2)
  if (self->stride == 1) {
    qsortFct(self->valref, self->size-1, self2->fct);
    return;
  }

  if (self->stride == -1) {
    qsortFct(self->valref, self->size-1, self2->fct);
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

  qsortFct(buf, self->size-1, self2->fct);

  // backward copy
  for (cur = buf; cur != end; cur++)
    *val = *cur, val += val_s;

  TMPARRAY_DESTROY(buf);
endmethod

defmethod(void, gsort, COS_PP_CAT(T,0), Function2)
endmethod

defmethod(void, gsort, COS_PP_CAT(T,1), Function2)
endmethod

defmethod(void, gsort, COS_PP_CAT(T,2), Function2)
  VAL t, *val = self->T.valref;
  OBJFCT2 fct = self2->fct;
  NETSORT(val,2-1,retmethod());
endmethod

defmethod(void, gsort, COS_PP_CAT(T,3), Function2)
  VAL t, *val = self->T.valref;
  OBJFCT2 fct = self2->fct;
  NETSORT(val,3-1,retmethod());
endmethod

defmethod(void, gsort, COS_PP_CAT(T,4), Function2)
  VAL t, *val = self->T.valref;
  OBJFCT2 fct = self2->fct;
  NETSORT(val,4-1,retmethod());
endmethod

defmethod(void, gsort, COS_PP_CAT(T,5), Function2)
  VAL t, *val = self->T.valref;
  OBJFCT2 fct = self2->fct;
  NETSORT(val,5-1,retmethod());
endmethod

defmethod(void, gsort, COS_PP_CAT(T,6), Function2)
  VAL t, *val = self->T.valref;
  OBJFCT2 fct = self2->fct;
  NETSORT(val,6-1,retmethod());
endmethod

// ----- indirect sorting (return permutation)

#undef  GCMP
#define GCMP(a,b) fct(VALOBJ(o[a]),VALOBJ(o[b]))

static void
iqsortFct(I32 a[], VAL o[], I32 r, OBJFCT2 fct)
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

  iqsortFct(s,o,p,fct);
  iqsortFct(l,o,q,fct); // tail recursion
}

defmethod(OBJ, gisort, T, Function2)
  useclass(IntVector);

  OBJ _vec = gnewWith(IntVector, aSlice(0,self->size,1)); PRT(_vec);
  struct IntVector *vec = STATIC_CAST(struct IntVector*, _vec);
  
  iqsortFct(vec->value, self->valref, self->size-1, self2->fct);
  
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- is sorted predicate

defmethod(OBJ, gisSorted, T, Function2)
  if (self->size < 2)
    retmethod(True);

  VAL *val    = self->valref;
  I32  val_s  = self->stride;
  VAL *end    = self->valref + (self->size-1)*self->stride;
  OBJFCT2 fct = self2->fct;

  while (val != end) {
    if (fct(VALOBJ(*val), VALOBJ(val[val_s])) == False)
      retmethod(False);
    val += val_s;
  }

  retmethod(True);
endmethod


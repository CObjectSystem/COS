/*
 o---------------------------------------------------------------------o
 |
 | COS Array - algorithms using functors
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
 | $Id: Array_fun.c,v 1.10 2009/08/10 21:02:15 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Functor.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>

#include <cos/carray.h>

// ----- 

useclass(Array);

// ----- foreach (in place, discard fun returned value)

defmethod(void, gforeach, Array, Functor)
  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;

  while (obj != end) {
    geval1(_2, *obj);
    obj += obj_s;
  }
endmethod

// ----- apply (in place map)

defmethod(void, gapply, Functor, Array)
  OBJ *obj   = self2->object;
  I32  obj_s = self2->stride;
  OBJ *end   = self2->object + self2->size*self2->stride;

  while (obj != end) {
    OBJ new = geval1(_1, *obj);
    if (new != *obj) {
      OBJ old = *obj;
      *obj = gretain(new);
      grelease(old);
    }
    obj += obj_s;
  }
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, Array)
  struct Array* arr = Array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + arr->size;
  OBJ *src   = self2->object;
  I32  src_s = self2->stride;

  while (dst != end) {
    *dst++ = gretain( geval1(_1,*src) );
    src += src_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gmap2, Functor, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst    = arr->object;
  OBJ *end    = arr->object + arr->size;
  OBJ *src1   = self2->object;
  I32  src1_s = self2->stride;
  OBJ *src2   = self3->object;
  I32  src2_s = self3->stride;

  while (dst != end) {
    *dst++ = gretain( geval2(_1,*src1,*src2) );
    src1 += src1_s;
    src2 += src2_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gmap3, Functor, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;

  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst    = arr->object;
  OBJ *end    = arr->object + arr->size;
  OBJ *src1   = self2->object;
  I32  src1_s = self2->stride;
  OBJ *src2   = self3->object;
  I32  src2_s = self3->stride;
  OBJ *src3   = self4->object;
  I32  src3_s = self4->stride;

  while (dst != end) {
    *dst++ = gretain( geval3(_1,*src1,*src2,*src3) );
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gmap4, Functor, Array, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;

  struct Array* arr = Array_alloc(size);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst    = arr->object;
  OBJ *end    = arr->object + arr->size;
  OBJ *src1   = self2->object;
  I32  src1_s = self2->stride;
  OBJ *src2   = self3->object;
  I32  src2_s = self3->stride;
  OBJ *src3   = self4->object;
  I32  src3_s = self4->stride;
  OBJ *src4   = self5->object;
  I32  src4_s = self5->stride;

  while (dst != end) {
    *dst++ = gretain( geval4(_1,*src1,*src2,*src3,*src4) );
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
    src4 += src4_s;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

// ----- all, any

defmethod(OBJ, gall, Array, Functor)
  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;

  while (obj != end) {
    if (geval1(_2, *obj) != True)
      retmethod(False);
    obj += obj_s;
  }
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, Array, Functor)
  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;

  while (obj != end) {
    if (geval1(_2, *obj) == True)
      retmethod(True);
    obj += obj_s;
  }
      
  retmethod(False);
endmethod

// ----- filter, filterOut fold, scan

defmethod(OBJ, gfilter, Array, Functor)
  OBJ _arr = gnewWith(Array,aInt(self->size)); PRT(_arr);
  struct Array* arr = STATIC_CAST(struct Array*, _arr);

  OBJ *dst   = arr ->object;
  OBJ *src   = self->object;
  I32  src_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;

  while (src != end) {
    if (geval1(_2, *src) == True)
      *dst++ = gretain(*src), ++arr->size;
    src += src_s;
  }

  gadjust(_arr);
  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gfilterOut, Array, Functor)
  OBJ _arr = gnewWith(Array,aInt(self->size)); PRT(_arr);
  struct Array* arr = STATIC_CAST(struct Array*, _arr);

  OBJ *dst   = arr ->object;
  OBJ *src   = self->object;
  I32  src_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;

  while (src != end) {
    if (geval1(_2, *src) == False)
      *dst++ = gretain(*src), ++arr->size;
    src += src_s;
  }

  gadjust(_arr);
  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gfoldl, Array, Functor, Object)
  OBJ *src   = self->object;
  I32  src_s = self->stride;
  OBJ *end   = self->object + self->size*self->stride;
  OBJ  res   = _3;
  
  while (src != end) {
    res = geval2(_2, res, *src);
    src += src_s;
  }

  retmethod(res);
endmethod

defmethod(OBJ, gfoldr, Array, Functor, Object)
  OBJ *src   = self->object + self->size*self->stride;
  I32  src_s = self->stride;
  OBJ *end   = self->object;
  OBJ res    = _3;
  
  while (src != end) {
    src -= src_s;
    res = geval2(_2, *src, res);
  }

  retmethod(res);
endmethod

defmethod(OBJ, gscanl, Array, Functor, Object)
  struct Array* arr = Array_alloc(self->size+1);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object;
  OBJ *end   = arr->object + arr->size;
  OBJ *src   = self->object;
  I32  src_s = self->stride;

  *dst++ = gretain(_3);
  
  while (dst != end) {
    *dst = gretain( geval2(_2, *(dst-1), *src) );
    src += src_s, dst++;
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

defmethod(OBJ, gscanr, Array, Functor, Object)
  struct Array* arr = Array_alloc(self->size+1);
  OBJ _arr = (OBJ)arr; PRT(_arr);

  OBJ *dst   = arr->object + arr->size;
  OBJ *end   = arr->object;
  OBJ *src   = self->object + self->size*self->stride;
  I32  src_s = self->stride;

  *--dst = gretain(_3);

  while (dst != end) {
    src -= src_s, dst--;
    *dst = gretain( geval2(_2, *src, *(dst+1)) );
  }

  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod

// ----- finding

defmethod(OBJ, gfind, Array, Object, Functor)
  useclass(Lesser, Equal, Greater);

  if (self->size == 0)
    retmethod(Nil);

  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ  res   = geval2(_3, _2, *obj); // bsearch order

  if (res == True || res == Equal) // found
    retmethod(*obj);

  // linear search
  if (res == False) {
    OBJ *end = self->object + self->size*self->stride;

    obj += obj_s;
    while (obj != end) {
      if (geval2(_3, _2, *obj) == True) // found
        retmethod(*obj);
      obj += obj_s;
    }

    retmethod(Nil);
  }

  // binary search
  if (res == Lesser)
    retmethod(Nil);
  
  test_assert( res == Greater,
    "gfind expects functor returning TrueFalse or Ordered predicates" );

  U32 lo = 1, hi = self->size-1;

  while (lo <= hi) {
    U32 i = (lo + hi) / 2;
    res = geval2(_3, _2, obj[i*obj_s]);

    if (res == Equal)
      retmethod(obj[i*obj_s]); // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

  retmethod(Nil);  
endmethod

// ----- sorting (in place)

#define NETSORT(a,r) \
  do { \
    switch (r) { \
    case 1: \
      SORT(a[0],a[1]); \
      return; \
    \
    case 2: \
      SORT(a[0],a[1]); \
      SORT(a[0],a[2]); \
      SORT(a[1],a[2]); \
      return; \
    \
    case 3: \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[0],a[1]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); \
      return; \
    \
    case 4: \
      SORT(a[0],a[4]); SORT(a[1],a[3]); \
      SORT(a[0],a[2]); \
      SORT(a[2],a[4]); SORT(a[0],a[1]); \
      SORT(a[2],a[3]); SORT(a[1],a[4]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      return; \
    \
    case 5: \
      SORT(a[0],a[4]); SORT(a[1],a[5]); \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[2],a[4]); SORT(a[3],a[5]); \
      SORT(a[0],a[1]); SORT(a[4],a[5]); \
      SORT(a[1],a[4]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      return; \
    } \
  } while (0)

/* from "Quicksort Is Optimal", R. Sedgwick & J. Bentley, 2002
   plus some practical improvements.
 */

#define EXCH(a,b) (t=(a),(a)=(b),(b)=t)
#define SORT(a,b) if (GCMP(b,a) == Lesser) EXCH(a,b)
#define GCMP(a,b) geval2(fun,a,b)

static inline U32
pivot(void)
{
  static U32 x = 1; // no need to be thread safe
  
  return x = x * 2621124293u + 1;
}

static void
quicksort(OBJ a[], I32 r, OBJ fun)
{
  useclass(Lesser, Equal);
  I32 i, j, p, q;
  OBJ t, ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,r);

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
  OBJ *s, *l;
  
  if (j < r-i)
    s = a, l = a+i, p = j, q = r-i;
  else
    l = a, s = a+i, q = j, p = r-i;

  quicksort(s,p,fun);
  quicksort(l,q,fun); // tail recursion
}

// -----

defmethod(void, gsort, Array, Functor)
  if (self->stride == 1) {
    quicksort(self->object, self->size-1, _2);
    return;
  }

  if (self->stride == -1) {
    quicksort(self->object-self->size+1, self->size-1, _2);
    greverse(_1);
    return;
  }

  OBJ *obj   = self->object;
  U32  obj_z = self->size;
  I32  obj_s = self->stride;

  TMPARRAY_CREATE(OBJ,buf,obj_z); // OBJ buf[obj_z];

  OBJ *cur, *end = buf + obj_z;

  // forward copy
  for (cur = buf; cur != end; cur++)
    *cur = *obj, obj += obj_s;

  quicksort(buf, self->size-1, _2);

  // backward copy
  for (cur = buf; cur != end; cur++)
    *obj = *cur, obj += obj_s;

  TMPARRAY_DESTROY(buf);
endmethod

// ----- indirect sorting (permutation)

#undef  GCMP
#define GCMP(a,b) geval2(fun,o[a],o[b])

static void
iquicksort(I32 a[], OBJ o[], I32 r, OBJ fun)
{
  useclass(Lesser, Equal);
  I32 i, j, p, q, t;
  OBJ ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,r);

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

  iquicksort(s,o,p,fun);
  iquicksort(l,o,q,fun); // tail recursion
}

defmethod(OBJ, gisort, Array, Functor)
  useclass(IntVector);

  OBJ _vec = gnewWith(IntVector, aSlice(0,self->size,1)); PRT(_vec);
  struct IntVector *vec = STATIC_CAST(struct IntVector*, _vec);

  iquicksort(vec->value, self->object, self->size-1, _2);
  
  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- is sorted predicate

defmethod(OBJ, gisSorted, Array, Functor)
  if (self->size < 2)
    retmethod(True);

  OBJ *obj   = self->object;
  I32  obj_s = self->stride;
  OBJ *end   = self->object + (self->size-1)*self->stride;

  while (obj != end) {
    if (geval2(_2, *obj, *(obj+obj_s)) == False)
      retmethod(False);
    obj += obj_s;
  }

  retmethod(True);
endmethod

// ----- unique (remove contiguous duplicates)

defmethod(OBJ, gunique, Array, Functor)
  if (self->size < 1)
    retmethod( gautoDelete(gclone(_1)) );

  OBJ _arr = gnewWith(Array,aInt(self->size)); PRT(_arr);
  struct Array* arr = STATIC_CAST(struct Array*, _arr);

  OBJ *dst   = arr ->object;
  OBJ *src   = self->object;
  I32  src_s = self->stride;
  OBJ *end   = self->object + (self->size-1)*self->stride;

  while (src != end) {
    if (geval2(_2, *src, *(src+src_s)) != True)
      *dst++ = gretain(*src), ++arr->size;
    src += src_s;
  }
  *dst++ = gretain(*src);

  gadjust(_arr);
  UNPRT(_arr);
  retmethod(gautoDelete(_arr));
endmethod


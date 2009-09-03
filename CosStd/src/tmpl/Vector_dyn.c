/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - Dynamic vector
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
 | $Id: Vector_dyn.c,v 1.8 2009/09/03 23:21:42 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// -----

makclass(TF,T);
makclass(TD,TF);

// -----

useclass(TD);

// -----

#define VECTOR_GROWTH_RATE 1.618034 // golden ratio

STATIC_ASSERT(vector_growth_rate_is_too_small, VECTOR_GROWTH_RATE >= 1.5);

// ----- constructors

defalias (OBJ, (ginit)gnew, TP);
defmethod(OBJ,  ginit     , TP) // Dynamic vector
  OBJ vec = galloc(TD); PRT(vec);

  vec = ginitWith(vec,aInt(0));

  UNPRT(vec);
  retmethod(vec);
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Int);
defmethod(OBJ,  ginitWith         , TP, Int) // Dynamic vector with capacity
  OBJ vec = galloc(TD); PRT(vec);

  vec = ginitWith(vec,_2);

  UNPRT(vec);
  retmethod(vec);
endmethod

defmethod(OBJ, ginitWith, TD, Int)
  PRE
    test_assert(self2->value >= 0, "negative " TS " capacity");
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (self2->value > 0) {
      vec->valref = malloc(self2->value * sizeof *vec->valref);
      if (!vec->valref) THROW(ExBadAlloc);
    } else
      vec->valref = 0;

    vec->size      = 0;
    vec->stride    = 1;
    vecf->_valref  = vec->valref;
    vecf->capacity = self2->value;

    retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, TF)
  next_method(self);

  if (self->_valref)            // take care of protection cases
    free(self->_valref);

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, TD, (STR)func, (STR)file, (int)line)
  test_assert( self->TF.capacity >= self->TF.T.size,
               "dynamic " TS " has capacity < size", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod

// ----- memory management

defmethod(void, genlarge, TD, Float) // negative factor means enlarge front
  PRE
    test_assert(self2->value < -1 ||
                self2->value >  1, "invalid growing factor");
  POST
  BODY
    F64 factor   = self2->value;
    U32 capacity = self->TF.capacity;

    if (factor > 1)
      genlarge(_1, aInt(capacity * (factor-1)));
    else if (factor < 1)
      genlarge(_1, aInt(capacity * (factor+1)));
endmethod

defmethod(void, genlarge, TD, Int) // negative size means enlarge front
  enum { MIN_SIZE = 1024 };
  
  struct TF*  vecf = &self->TF;
  struct T*    vec = &vecf->T;
  U32     capacity = vecf->capacity;
  ptrdiff_t offset = vec->valref - vecf->_valref;
  BOOL       front = self2->value < 0;
  U32         size = front ? -self2->value : self2->value;

  if (size < MIN_SIZE)
    size = MIN_SIZE;

  capacity += size;
  
  VAL *_valref = realloc(vecf->_valref, capacity*sizeof(VAL));
  if (!_valref) THROW(ExBadAlloc);

  vec -> valref  = _valref + offset;
  vecf->_valref  = _valref;
  vecf->capacity = capacity;
  
  if (front) // move data to book the new space front
    vec->valref = memmove(vec->valref+size, _valref+offset, vec->size*sizeof(VAL));
endmethod

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, TD)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  // move data to base
  if (vec->valref != vecf->_valref)
    vec->valref = memmove(vecf->_valref, vec->valref, vec->size*sizeof(VAL));

  // shrink storage
  if (vec->size != vecf->capacity) {
    VAL *_valref = realloc(vecf->_valref, vec->size*sizeof(VAL));
    if (!_valref) THROW(ExBadAlloc);

    vec ->valref   = _valref;
    vecf->_valref  = _valref;
    vecf->capacity = vec->size;
  }

  test_assert( cos_object_changeClass(_1, classref(TF)),
               "unable to change from dynamic to fixed size " TS );
endmethod

// ----- clear (size -> 0)

defmethod(void, gclear, TD)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

#ifdef ARRAY_ONLY
  VAL *val = vec->valref + vec->size;
  VAL *end = vec->valref;

  while (val != end)
    --val, RELEASE(*val), *val = 0;
#endif

  vec->size = 0;
endmethod

// ----- dropFirst, dropLast, drop

defmethod(void, gdropFirst, TD)
  struct T *vec = &self->TF.T;

  if (vec->size) {
    --vec->size;
    ++vec->valref;
   RELEASE(vec->valref[-1]);
  }
endmethod

defmethod(void, gdropLast, TD)
  struct T *vec = &self->TF.T;

  if (vec->size) {
    --vec->size;
    RELEASE(vec->valref[vec->size]);
  }
endmethod

defmethod(void, gdrop, TD, Int)
  struct T *vec = &self->TF.T;
  BOOL front = self2->value < 0;
  U32 n = front ? -self2->value : self2->value;

  if (n > vec->size)
    n = vec->size;

#ifdef VECTOR_ONLY
  vec->size -= n;
  if (front)
    vec->valref += n;
#else // ARRAY_ONLY
  if (front)
    while (n-- > 0) {
      --vec->size;
      ++vec->valref;
      RELEASE(vec->valref[-1]);
    }
  else
    while (n-- > 0) {
      --vec->size;
      RELEASE(vec->valref[vec->size]);
    }
#endif
endmethod

// ----- prepend, append object

static inline I32
extra_size(U32 capacity, U32 size)
{
  F64 factor = VECTOR_GROWTH_RATE;

  while (capacity*(factor - 1.0) < size)
    factor *= VECTOR_GROWTH_RATE;

  I32 extra = capacity*(factor - 1.0);
  
  test_assert(extra > 0 && (U32)extra > size, TS "size overflow");

  return extra;
}

defmethod(void, gprepend, TD, Object)
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (vec->valref == vecf->_valref)
      genlarge(_1, aInt(-extra_size(vecf->capacity, 1)));

    vec->valref[-1] = RETAIN(TOVAL(_2));
    vec->valref--;
    vec->size++;
endmethod

defmethod(void, gappend, TD, Object)
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (vec->size == vecf->capacity)
      genlarge(_1, aInt(extra_size(vecf->capacity, 1)));
      
    vec->valref[vec->size] = RETAIN(TOVAL(_2));
    vec->size++;
endmethod

// ----- prepend, append vector

defmethod(void, gprepend, TD, T)
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (vec->valref-vecf->_valref < self2->size)
      genlarge(_1, aInt(-extra_size(vecf->capacity, self2->size)));

    VAL *src   = self2->valref;
    U32  src_n = self2->size;
    I32  src_s = self2->stride;
    VAL *end   = src + src_n*src_s;

    while (src != end) {
      vec->valref[-1] = RETAIN(*src);
      vec->valref--;
      vec->size++;
      src += src_s;
    }
endmethod

defmethod(void, gappend, TD, T)
  PRE
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (vecf->capacity-vec->size < self2->size)
      genlarge(_1, aInt(extra_size(vecf->capacity, self2->size)));

    VAL *src   = self2->valref;
    U32  src_n = self2->size;
    I32  src_s = self2->stride;
    VAL *end   = src + src_n*src_s;

    while (src != end) {
      vec->valref[vec->size] = RETAIN(*src);
      vec->size++;
      src += src_s;
    }
endmethod

// --- insertAt object (index, slice, range, intvector)

static BOOL
prepareRandomInsert(struct T *vec, struct IntVector *self2)
{
  U32  dst_n = vec->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  U32  fst   = dst_n;
  U32  lst   = 0;

  TMPARRAY_CREATE(U8,flg,dst_n);
  memset(flg,0,dst_n);

  // mark insertion slots
  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    if (i >= dst_n) break;
    if (i < fst) fst = i;
    if (i > lst) lst = i;
    flg[i] = 1;
    idx += idx_s;
  }
  
  // range error
  if (idx != end) {
    TMPARRAY_DESTROY(flg);
    return NO;
  }

  // shift post data to the end
  VAL *dst = lst + vec->valref;
  memmove(dst+idx_n, dst, (vec->size - (dst-vec->valref))*sizeof(VAL));
  vec->size += idx_n;

  // prepare insertion slots (start from the end)
  {
    VAL *end = fst + vec->valref;
    U8  *slt = lst + flg;
    U32  sht = idx_n;

    for (; dst != end; --dst, --slt)
      if (*slt)
        sht--;
      else
        dst[sht] = *dst;
  }
  
  TMPARRAY_DESTROY(flg);
  return YES;
}

defmethod(void, ginsertAt, TD, Int, Object)
  U32 i;

  PRE
    i = Range_index(self2->value, self->TF.T.size);
    test_assert( i <= self->TF.T.size, "index out of range" );
 
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (vec->size == vecf->capacity)
      genlarge(_1, aInt(extra_size(vecf->capacity, 1)));

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, vec->size);
 
    VAL *dst = vec->valref+i;

    memmove(dst+1, dst, (vec->size-i)*sizeof(VAL));
    *dst = RETAIN(TOVAL(_3));
    vec->size++;
endmethod

defmethod(void, ginsertAt, TD, Slice, Object)
  PRE
    test_assert( Slice_first(self2) <= self->TF.T.size &&
                 Slice_last (self2) <= self->TF.T.size, "slice out of range" );
  POST
    // automatically trigger ginvariant
 
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    VAL *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    if (vec->size + dst_n > vecf->capacity)
      genlarge(_1, aInt(extra_size(vecf->capacity, dst_n)));

    // always start from the end (reverse fill with positive stride)
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_last  (self2) + vec->valref;
      dst_s =  Slice_stride(self2);
    } else {
      dst   =  Slice_first (self2) + vec->valref;
      dst_s = -Slice_stride(self2);
    }

    // shift post data to the end
    memmove(dst+dst_n, dst, (vec->size - (dst-vec->valref))*sizeof(VAL));
    vec->size += dst_n;

    VAL *end = dst - dst_s*dst_n;
    VAL *nxt = dst - dst_s;
    VAL  val = TOVAL(_3);
    U32  sht = dst_n;

    // double level fill-move
    while (dst != end) {
      ASSIGN(dst[sht],val);
 
      for (dst--; dst != nxt; dst--)
        dst[sht] = *dst;

      nxt -= dst_s;
      sht -= 1; 
    }
endmethod

defmethod(void, ginsertAt, TD, Range, Object)
  struct Range range = Range_normalize(self2,self->TF.T.size);
  struct Slice slice = Slice_fromRange(&range);
  
  ginsertAt(_1,(OBJ)&slice,_3);
endmethod

defmethod(void, ginsertAt, TD, IntVector, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  // enlarge
  if (vec->size + self2->size > vecf->capacity)
    genlarge(_1, aInt(extra_size(vecf->capacity, self2->size)));

  test_assert( prepareRandomInsert(vec,self2), "index out of range" );

  // insert data
  VAL *dst   = vec->valref;
  U32  dst_n = vec->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  VAL  val   = TOVAL(_3);
  
  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    dst[i] = RETAIN(val);
    idx += idx_s;
  }
endmethod

// --- insertAt object (slice, range, intvector)

defmethod(void, ginsertAt, TD, Slice, T)
  PRE
    test_assert( Slice_first(self2) <= self->TF.T.size &&
                 Slice_last (self2) <= self->TF.T.size, "slice out of range" );
    test_assert( Slice_size (self2) <= self3->size, "source " TS " is too small" );
  POST
    // automatically trigger ginvariant
 
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    VAL *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    if (vec->size + dst_n > vecf->capacity)
      genlarge(_1, aInt(extra_size(vecf->capacity, dst_n)));

    // always start from the end (reverse fill with positive stride)
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_last  (self2) + vec->valref;
      dst_s =  Slice_stride(self2);    
    } else {
      dst   =  Slice_first (self2) + vec->valref;
      dst_s = -Slice_stride(self2);
    }

    // shift post data to the end
    memmove(dst+dst_n, dst, (vec->size - (dst-vec->valref))*sizeof(VAL));
    vec->size += dst_n;

    VAL *end   = dst - dst_s*dst_n;
    VAL *nxt   = dst - dst_s;
    VAL *src   = (self3->size-1)*self3->stride + self3->valref;
    I32  src_s =  self3->stride;
    U32  sht   = dst_n;

    while (dst != end) {
      ASSIGN(dst[sht],*src);
 
      for (dst--; dst != nxt; dst--)
        dst[sht] = *dst;

      src -= src_s;
      nxt -= dst_s;
      sht -= 1; 
    }
endmethod

defmethod(void, ginsertAt, TD, IntVector, T)
  PRE
    test_assert( self2->size <= self3->size, "source " TS " is too small" );
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    // enlarge
    if (vec->size + self2->size > vecf->capacity)
      genlarge(_1, aInt(extra_size(vecf->capacity, self2->size)));

    test_assert( prepareRandomInsert(vec,self2), "index out of range" );

    // insert data
    VAL *dst   = vec->valref;
    U32  dst_n = vec->size;
    I32 *idx   = self2->value;
    U32  idx_n = self2->size;
    I32  idx_s = self2->stride;
    VAL *src   = self3->valref;
    I32  src_s = self3->stride;
    I32 *end   = idx + idx_n*idx_s;
    
    while (idx != end) {
      U32 i = Range_index(*idx, dst_n);
      dst[i] = RETAIN(*src);
      src += src_s;
      idx += idx_s;
    }
endmethod

// --- removeAt

defmethod(void, gremoveAt, TD, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->TF.T.size);
    test_assert( i <= self->TF.T.size, "index out of range" );
 
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->TF.T.size);
 
    VAL *dst = vec->valref+i;

    vec->size--;
    RELEASE(*dst);
    memmove(dst, dst+1, (vec->size-i)*sizeof(VAL));
endmethod

defmethod(void, gremoveAt, TD, Slice)
  PRE
    test_assert( Slice_first(self2) <= self->TF.T.size &&
                 Slice_last (self2) <= self->TF.T.size, "slice out of range" );
  POST
    // automatically trigger ginvariant
 
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    VAL *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    // always start from the beginning
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_first (self2) + vec->valref;
      dst_s =  Slice_stride(self2);
    } else {
      dst   =  Slice_last  (self2) + vec->valref;
      dst_s = -Slice_stride(self2);
    }

    VAL *end = dst + dst_s*dst_n;
    VAL *nxt = dst + dst_s;
    U32  sht = 1;

    // double level clear-move
    while (dst != end) {
      RELEASE(*dst);
 
      for (; dst != nxt; dst++)
        *dst = dst[sht];

      nxt += dst_s;
      sht += 1; 
    }

    // shift post data to the beginning
    memmove(dst, dst+dst_n, (vec->size - (dst-vec->valref))*sizeof(VAL));
    vec->size -= dst_n;
endmethod

defmethod(void, gremoveAt, TD, Range)
  struct Range range = Range_normalize(self2,self->TF.T.size);
  struct Slice slice = Slice_fromRange(&range);
  
  gremoveAt(_1,(OBJ)&slice);
endmethod

defmethod(void, gremoveAt, TD, IntVector)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  VAL *dst   = vec->valref;
  U32  dst_n = vec->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  U32  fst   = dst_n;
  U32  lst   = 0;

  TMPARRAY_CREATE(U8,flg,dst_n);
  memset(flg,0,dst_n);

  // release
  while (idx != end) {
    U32 i = Range_index(*idx, dst_n);
    if (i >= dst_n) break;
    if (i < fst) fst = i;
    if (i > lst) lst = i;
    flg[i] = 1; RELEASE(dst[i]);
    idx += idx_s;
  }
  
  if (idx != end) {
    TMPARRAY_DESTROY(flg);
    test_assert( 0, "index out of range" );
  }

  // shrink
  {
    VAL *end = lst + vec->valref;
    U8  *slt = fst + flg;
    U32  sht = 0;

    for (dst += fst; dst != end; ++dst, ++slt) {
      if (*slt) sht++;
      dst[sht] = *dst;
    }

    memmove(dst, dst+idx_n, (vec->size - (dst-vec->valref))*sizeof(VAL));
    vec->size -= idx_n;
  }

  TMPARRAY_DESTROY(flg);
endmethod

// --- dequeue aliases
defalias(void, (gprepend  )gpushFront, TD, Object);
defalias(void, (gappend   )gpushBack , TD, Object);
defalias(void, (gdropFirst)gpopFront , TD);
defalias(void, (gdropLast )gpopBack  , TD);
defalias(OBJ , (gfirst    )gfront    , T );
defalias(OBJ , (glast     )gback     , T );

// --- stack aliases
defalias(void, (gappend  )gpush, TD, Object);
defalias(void, (gdropLast)gpop , TD);
defalias(OBJ , (glast    )gtop , T );


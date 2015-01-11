/**
 * C Object System
 * COS Vector template - Dynamic vector
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

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// -----

makclass(TF,T);
makclass(TD,TF);

// -----

useclass(TD);

// -----

#ifndef VECTOR_GROWTH_RATE
#define VECTOR_GROWTH_RATE SEQUENCE_GROWTH_RATE
#endif

#ifndef VECTOR_MINSIZE
#define VECTOR_MINSIZE 1024
#endif

STATIC_ASSERT(vector_growth_rate_is_too_small , VECTOR_GROWTH_RATE >= 1500);
STATIC_ASSERT(vector_minimun_size_is_too_small, VECTOR_MINSIZE     >= 256);

// ----- constructors

defalias (OBJ, (ginit)gnew, TP);
defmethod(OBJ,  ginit     , TP) // Dynamic vector
  retmethod(ginitWith(galloc(TD),aInt(0)));
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Int);
defmethod(OBJ,  ginitWith         , TP, Int) // Dynamic vector with capacity
  retmethod(ginitWith(galloc(TD),_2));
endmethod

defmethod(OBJ, ginitWith, TD, Int)
  PRT(_1);
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;
  U32    capacity = self2->value;

  ensure(self2->value >= 0, "negative " TS " capacity");

  vecf->_value = malloc(capacity*sizeof *vec->value);
  if (!vecf->_value && capacity) THROW(ExBadAlloc);

  vec->size      = 0;
  vec->stride    = 1;
  vec->value     = vecf->_value;
  vecf->capacity = capacity;

  UNPRT(_1);
  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, TF)
  next_method(self);

  if (self->_value)            // take care of protection cases
    free(self->_value);

  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, TD, (STR)file, (int)line)
  ensure( self->TF.capacity >= self->TF.T.size,
               "dynamic " TS " has capacity < size", file, line);

  if (next_method_p)
    next_method(self, file, line);
endmethod

// ----- memory management

static I32
extra_size(U32 old_capacity, U32 size)
{
  U32 new_capacity = old_capacity < VECTOR_MINSIZE ? VECTOR_MINSIZE : old_capacity;
  
  while (new_capacity - old_capacity < size)
    new_capacity *= (VECTOR_GROWTH_RATE/1000.0);

  I32 extra = new_capacity - old_capacity;
  
  ensure(extra > 0 && (U32)extra > size, TS "size overflow");

  return extra;
}

defmethod(OBJ, genlarge, TD, Float) // negative factor means enlarge front
  PRE
    ensure(self2->value < -1 ||
                self2->value >  1, "invalid growing factor");
  BODY
    F64 factor   = self2->value;
    U32 capacity = self->TF.capacity;

    if (factor > 1)
      retmethod( genlarge(_1, aInt(capacity * (factor-1))) );
    else if (factor < 1)
      retmethod( genlarge(_1, aInt(capacity * (factor+1))) );
endmethod

defmethod(OBJ, genlarge, TD, Int) // negative size means enlarge front
  PRE
    ensure(self2->value, "invalid growing size");
  BODY
    struct TF*  vecf = &self->TF;
    struct T*   vec  = &vecf->T;
    U32     capacity = vecf->capacity;
    ptrdiff_t offset = vec->value - vecf->_value;
    BOOL       front = self2->value < 0;
    U32         size = front ? -self2->value : self2->value;

    capacity += size = extra_size(capacity, size);
    
    VAL *_value = realloc(vecf->_value, capacity*sizeof *vecf->_value);
    if (!_value && capacity) THROW(ExBadAlloc);

    vec -> value   = _value + offset;
    vecf->_value   = _value;
    vecf->capacity = capacity;
    
    if (front) // move data to book the new space front
      vec->value = memmove(vec->value+size, vec->value, vec->size*sizeof *vec->value);

    retmethod(_1);
endmethod

// ----- adjustment (capacity -> size)

defmethod(OBJ, gadjust, TD)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;
  U32        size = vec->size;

  // move data to base
  if (vec->value != vecf->_value)
    vec->value = memmove(vecf->_value, vec->value, size*sizeof *vecf->_value);

  // shrink storage
  if (size != vecf->capacity) {
    VAL *_value = realloc(vecf->_value, size*sizeof *vecf->_value);
    if (!_value && size) THROW(ExBadAlloc);

    vec -> value  = _value;
    vecf->_value  = _value;
    vecf->capacity = size;
  }

  BOOL ch_cls = cos_object_changeClass(_1, classref(TF));
  ensure( ch_cls, "unable to change from dynamic to fixed size " TS );
  
  retmethod(_1);
endmethod

// ----- clear (size -> 0)

defmethod(OBJ, gclear, TD)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  vec->size  = 0;
  vec->value = vecf->_value;

  retmethod(_1);
endmethod

// ----- popFront, popBack, drop

defmethod(OBJ, gpopFront, TD)
  struct T *vec = &self->TF.T;

  if (vec->size--)
    ++vec->value;

  retmethod(_1);
endmethod

defmethod(OBJ, gpopBack, TD)
  struct T *vec = &self->TF.T;

  if (vec->size--)
    {}

  retmethod(_1);
endmethod

defmethod(OBJ, gdrop, TD, Int)
  struct T *vec = &self->TF.T;
  BOOL     back = self2->value < 0;
  U32       cnt = back ? -self2->value : self2->value+1;

  if (cnt > vec->size)
    cnt = vec->size;

  vec->size -= cnt;
  if (!back) vec->value += cnt;

  retmethod(_1);
endmethod

// ----- prepend, append value

defmethod(OBJ, gprepend, TD, TE)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->value == vecf->_value)
    genlarge(_1, aInt(-1));

  *--vec->value = VALUE(self2), vec->size++;

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, TD, TE)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->value + vec->size == vecf->_value + vecf->capacity)
    genlarge(_1, aInt(1));
    
  vec->value[vec->size++] = VALUE(self2);

  retmethod(_1);
endmethod

// ----- prepend, append object

defmethod(OBJ, gprepend, TD, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->value == vecf->_value)
    genlarge(_1, aInt(-1));

  vec->value[-1] = TOVAL(_2), vec->value--, vec->size++;

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, TD, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->value + vec->size == vecf->_value + vecf->capacity)
    genlarge(_1, aInt(1));
    
  vec->value[vec->size++] = TOVAL(_2);

  retmethod(_1);
endmethod

// ----- prepend, append vector

defmethod(OBJ, gprepend, TD, T)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->value < vecf->_value + self2->size)
    genlarge(_1, aInt(-self2->size));

  VAL *src   = self2->value;
  U32  src_n = self2->size;
  I32  src_s = self2->stride;
  VAL *end   = src + src_n*src_s;

  while (src != end) {
    vec->value[-1] = *src, vec->value--, vec->size++;
    src += src_s;
  }

  retmethod(_1);
endmethod

defmethod(OBJ, gappend, TD, T)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->value + vec->size + self2->size > vecf->_value + vecf->capacity)
    genlarge(_1, aInt(self2->size));

  U32  src_n = self2->size;
  I32  src_s = self2->stride;
  VAL *src   = self2->value;
  VAL *end   = src + src_s*src_n;

  while (src != end) {
    vec->value[vec->size++] = *src;
    src += src_s;
  }

  retmethod(_1);
endmethod

/* TODO: unchecked code (certainly buggy)
*/

// --- insertAt object (index, slice, range, intvector)

defmethod(OBJ, ginsertAt, TD, Int, Object)
  U32 i;

  PRE
    i = Range_index(self2->value, self->TF.T.size);
    ensure( i <= self->TF.T.size, "index out of range" );
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (vec->size == vecf->capacity)
      genlarge(_1, aInt(1));

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, vec->size);
 
    VAL *dst = vec->value+i;

    memmove(dst+1, dst, (vec->size-i)*sizeof *dst);
    *dst = TOVAL(_3);
    vec->size++;

    retmethod(_1);
endmethod

defmethod(OBJ, ginsertAt, TD, Slice, Object)
  PRE
    ensure( Slice_first(self2) <= self->TF.T.size &&
                 Slice_last (self2) <= self->TF.T.size, "slice out of range" );
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    VAL *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    if (vec->size + dst_n > vecf->capacity)
      genlarge(_1, aInt(dst_n));

    // always start from the end (reverse fill with positive stride)
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_last  (self2) + vec->value;
      dst_s =  Slice_stride(self2);
    } else {
      dst   =  Slice_first (self2) + vec->value;
      dst_s = -Slice_stride(self2);
    }

    // shift post data to the end
    memmove(dst+dst_n, dst, (vec->size - (dst-vec->value))*sizeof *dst);
    vec->size += dst_n;

    VAL *end = dst - dst_s*dst_n;
    VAL *nxt = dst - dst_s;
    VAL  val = TOVAL(_3);
    U32  sht = dst_n;

    // double level fill-move
    while (dst != end) {
      dst[sht] = val;
 
      for (dst--; dst != nxt; dst--)
        dst[sht] = *dst;

      nxt -= dst_s;
      sht -= 1; 
    }

    retmethod(_1);
endmethod

defmethod(OBJ, ginsertAt, TD, Range, Object)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->TF.T.size);
  
  retmethod( ginsertAt(_1,(OBJ)slice,_3) );
endmethod

defmethod(OBJ, ginsertAt, TD, Slice, T)
  PRE
    ensure( Slice_first(self2) <= self->TF.T.size &&
                 Slice_last (self2) <= self->TF.T.size, "slice out of range" );
    ensure( Slice_size (self2) <= self3->size, "source " TS " is too small" );
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    VAL *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    if (vec->size + dst_n > vecf->capacity)
      genlarge(_1, aInt(dst_n));

    // always start from the end (reverse fill with positive stride)
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_last  (self2) + vec->value;
      dst_s =  Slice_stride(self2);    
    } else {
      dst   =  Slice_first (self2) + vec->value;
      dst_s = -Slice_stride(self2);
    }

    // shift post data to the end
    memmove(dst+dst_n, dst, (vec->size - (dst-vec->value))*sizeof *dst);
    vec->size += dst_n;

    VAL *end   = dst - dst_s*dst_n;
    VAL *nxt   = dst - dst_s;
    VAL *src   = (self3->size-1)*self3->stride + self3->value;
    I32  src_s =  self3->stride;
    U32  sht   = dst_n;

    while (dst != end) {
      dst[sht] = *src;
 
      for (dst--; dst != nxt; dst--)
        dst[sht] = *dst;

      src -= src_s;
      nxt -= dst_s;
      sht -= 1; 
    }

    retmethod(_1);
endmethod

// --- removeAt

defmethod(OBJ, gremoveAt, TD, Int)
  U32 i;

  PRE
    i = Range_index(self2->value, self->TF.T.size);
    ensure( i <= self->TF.T.size, "index out of range" );
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    if (!COS_CONTRACT) // no PRE
      i = Range_index(self2->value, self->TF.T.size);
 
    VAL *dst = vec->value+i;

    vec->size--;
    memmove(dst, dst+1, (vec->size-i)*sizeof *dst);

    retmethod(_1);
endmethod

defmethod(OBJ, gremoveAt, TD, Slice)
  PRE
    ensure( Slice_first(self2) <= self->TF.T.size &&
                 Slice_last (self2) <= self->TF.T.size, "slice out of range" );
  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    VAL *dst;
    I32  dst_s;
    U32  dst_n = Slice_size(self2);

    // always start from the beginning
    if (Slice_stride(self2) > 0) {
      dst   =  Slice_first (self2) + vec->value;
      dst_s =  Slice_stride(self2);
    } else {
      dst   =  Slice_last  (self2) + vec->value;
      dst_s = -Slice_stride(self2);
    }

    VAL *end = dst + dst_s*dst_n;
    VAL *nxt = dst + dst_s;
    U32  sht = 1;

    // double level clear-move
    while (dst != end) {
      for (; dst != nxt; dst++)
        *dst = dst[sht];

      nxt += dst_s;
      sht += 1; 
    }

    // shift post data to the beginning
    memmove(dst, dst+dst_n, (vec->size - (dst-vec->value))*sizeof *dst);
    vec->size -= dst_n;

    retmethod(_1);
endmethod

defmethod(OBJ, gremoveAt, TD, Range)
  struct Slice *slice = Slice_fromRange(atSlice(0), self2, &self->TF.T.size);
  
  retmethod( gremoveAt(_1,(OBJ)slice) );
endmethod

// --- dequeue aliases
defalias(OBJ, (gprepend  )gpushFront, TD, Object);
defalias(OBJ, (gappend   )gpushBack , TD, Object);
defalias(OBJ, (gprepend  )gpushFront, TD, TE);
defalias(OBJ, (gappend   )gpushBack , TD, TE);
defalias(OBJ, (gfirst    )gtopFront , T );
defalias(OBJ, (glast     )gtopBack  , T );

// --- stack aliases
defalias(OBJ, (gpushBack)gpush, TD, Object);
defalias(OBJ, (gpushBack)gpush, TD, TE);
defalias(OBJ, (gpopBack )gpop , TD);
defalias(OBJ, (gtopBack )gtop , T );


// --- random insert/remove (too complex? not tested!)

#if 0

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
  VAL *dst = lst + vec->value;
  memmove(dst+idx_n, dst, (vec->size - (dst-vec->value))*sizeof *dst);
  vec->size += idx_n;

  // prepare insertion slots (start from the end)
  {
    VAL *end = fst + vec->value;
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

defmethod(OBJ, ginsertAt, TD, IntVector, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  // enlarge
  if (vec->size + self2->size > vecf->capacity)
    genlarge(_1, aInt(self2->size));

  ensure( prepareRandomInsert(vec,self2), "index out of range" );

  // insert data
  VAL *dst   = vec->value;
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

defmethod(OBJ, ginsertAt, TD, IntVector, T)
  PRE
    ensure( self2->size <= self3->size, "source " TS " is too small" );
  POST
    // automatically trigger ginvariant

  BODY
    struct TF *vecf = &self->TF;
    struct T  *vec  = &vecf->T;

    // enlarge
    if (vec->size + self2->size > vecf->capacity)
      genlarge(_1, aInt(self2->size));

    ensure( prepareRandomInsert(vec,self2), "index out of range" );

    // insert data
    VAL *dst   = vec->value;
    U32  dst_n = vec->size;
    I32 *idx   = self2->value;
    U32  idx_n = self2->size;
    I32  idx_s = self2->stride;
    VAL *src   = self3->value;
    I32  src_s = self3->stride;
    I32 *end   = idx + idx_n*idx_s;
    
    while (idx != end) {
      U32 i = Range_index(*idx, dst_n);
      dst[i] = RETAIN(*src);
      src += src_s;
      idx += idx_s;
    }
endmethod

defmethod(OBJ, gremoveAt, TD, IntVector)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  VAL *dst   = vec->value;
  U32  dst_n = vec->size;
  I32 *idx   = self2->value;
  U32  idx_n = self2->size;
  I32  idx_s = self2->stride;
  I32 *end   = idx + idx_n*idx_s;
  U32  fst   = dst_n;
  U32  lst   = 0;

  TMPARRAY_CREATE(U8,flg,dst_n);
  memset(flg,0,dst_n*sizeof *flg);

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
    ensure( 0, "index out of range" );
  }

  // shrink
  {
    VAL *end = lst + vec->value;
    U8  *slt = fst + flg;
    U32  sht = 0;

    for (dst += fst; dst != end; ++dst, ++slt) {
      if (*slt) sht++;
      dst[sht] = *dst;
    }

    memmove(dst, dst+idx_n, (vec->size - (dst-vec->value))*sizeof *dst);
    vec->size -= idx_n;
  }

  TMPARRAY_DESTROY(flg);

  retmethod(_1);
endmethod

#endif



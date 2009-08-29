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
 | $Id: Vector_dyn.c,v 1.5 2009/08/29 23:54:17 ldeniau Exp $
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
#ifdef ARRAY_ONLY
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  VAL *val = vec->valref + vec->size;
  VAL *end = vec->valref;

  while (val != end)
    RELEASE(*--val), *val = 0;
#endif

  self->TF.T.size = 0;
endmethod

// ----- dropFirst, dropLast, dropn

defmethod(void, gdropFirst, TD)
  struct T *vec = &self->TF.T;

  if (vec->size) {
    --vec->size;
    ++vec->valref;
#ifdef ARRAY_ONLY
   RELEASE(vec->valref[-1]);
#endif
  }
endmethod

defmethod(void, gdropLast, TD)
  struct T *vec = &self->TF.T;

  if (vec->size) {
    --vec->size;
#ifdef ARRAY_ONLY
    RELEASE(vec->valref[vec->size]);
#endif
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
#endif
  
#ifdef ARRAY_ONLY
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
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->valref == vecf->_valref)
    genlarge(_1, aInt(-extra_size(vecf->capacity, 1)));

  vec->valref[-1] = RETAIN(TOVAL(_2));
  vec->valref--;
  vec->size++;
endmethod

defmethod(void, gappend, TD, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->size == vecf->capacity)
    genlarge(_1, aInt(extra_size(vecf->capacity, 1)));
    
  vec->valref[vec->size] = RETAIN(TOVAL(_2));
  vec->size++;
endmethod

// ----- prepend, append vector

defmethod(void, gprepend, TD, T)
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

// ----- Aliases

// --- dequeue
defalias(void, (gprepend  )gpushFront, TD, Object);
defalias(void, (gappend   )gpushBack , TD, Object);
defalias(void, (gdropFirst)gpopFront , TD);
defalias(void, (gdropLast )gpopBack  , TD);
defalias(OBJ , (gfirst    )gfront    , TD);
defalias(OBJ , (glast     )gback     , TD);

// --- stack
defalias(void, (gappend  )gpush, TD, Object);
defalias(void, (gdropLast)gpop , TD);
defalias(OBJ , (glast    )gtop , TD);


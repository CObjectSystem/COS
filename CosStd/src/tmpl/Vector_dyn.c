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
 | $Id: Vector_dyn.c,v 1.1 2009/08/21 12:10:00 ldeniau Exp $
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
  retmethod( ginit(galloc(TD)) );
endmethod

defmethod(OBJ, ginit, TD)
  retmethod( ginitWith(_1,aInt(0)) );
endmethod

defalias (OBJ, (ginitWith)gnewWith, TP, Int);
defmethod(OBJ,  ginitWith         , TP, Int) // Dynamic vector with capacity
  retmethod( ginitWith(galloc(TD),_2) );
endmethod

defmethod(OBJ, ginitWith, TD, Int)
  enum { MIN_SIZE = 1024 };
  
  I32 capacity = self2->value;

  test_assert(capacity >= 0, "negative " TS " capacity");
  if (capacity < MIN_SIZE) capacity = MIN_SIZE;

  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  vec->valref = malloc(capacity * sizeof *vec->valref);
  if (!vec->valref) THROW(ExBadAlloc);

  vec->size      = 0;
  vec->stride    = 1;
  vecf->_valref  = vec->valref;
  vecf->_cls     = 0;
  vecf->capacity = capacity;

  retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, TF)
  if (self->_valref)            // take care of protection cases
    free(self->_valref);
  next_method(self);
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, TD, (STR)func, (STR)file, (int)line)
  test_assert( self->TF.capacity >= self->TF.T.size,
               "dynamic " TS " has capacity < size", func, file, line);

  next_method(self, func, file, line);
endmethod

// ----- memory management

defmethod(void, genlarge, TD, Float)
  F64 factor   = self2->value;
  U32 capacity = self->TF.capacity;

  if (factor > 1.0)
    genlarge(_1, aInt(capacity * (factor-1)));
  else if (factor < 1.0)
    genlarge(_1, aInt(capacity * (1-factor)));
endmethod

defmethod(void, genlarge, TD, Int)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;
  U32     capacity = vecf->capacity;
  ptrdiff_t offset = vec->valref - vecf->_valref;
  BOOL       front = self2->value < 0;
  I32        addon = front ? -self2->value : self2->value;
  
  if (addon > 0) {
    U32 capacity = vecf->capacity + addon;
    VAL *_valref = realloc(vecf->_valref, capacity*sizeof *vecf->_valref);
    if (!_valref) THROW(ExBadAlloc);

    vec ->valref   = _valref + offset;
    vecf->_valref  = _valref;
    vecf->capacity = capacity;
  }
  if (front) { // move data to book the new space front
    vec->valref = vecf->_valref + (vecf->capacity - capacity);
    memmove(vec->valref, vecf->_valref + offset, vec->size*sizeof *vec->valref);
  }
endmethod

// ----- fix/unfix

defmethod(void, gfix, TD)
  PRE
    test_assert(!self->TF._cls, "corrupted dynamic " TS);

  BODY
    self->TF._cls = cos_object_id(_1);
    self->TF.T.VS.Container.Object.id = classref(TF)->Behavior.id;
endmethod

defmethod(void, gunfix, TF)
  PRE
    test_assert(self->_cls, "corrupted dynamic " TS " (already unfixed?)");

  BODY
    self->T.VS.Container.Object.id = self->_cls;
    self->_cls = 0;
endmethod

// ----- adjustment (capacity -> size)

defmethod(void, gadjust, TD)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  // move data to storage base
  if (vec->valref != vecf->_valref)
    vec->valref = memmove(vecf->_valref, vec->valref, vec->size * sizeof *vecf->_valref);

  // shrink storage
  if (vec->size != vecf->capacity) {
    VAL *_valref = realloc(vecf->_valref, vec->size * sizeof *vecf->_valref);
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

// ----- getters, setters

defalias (void, (gput)gappend, TD, Object);
defalias (void, (gput)gpush  , TD, Object);
defmethod(void,  gput        , TD, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->size == vecf->capacity)
    genlarge(_1, aFloat(VECTOR_GROWTH_RATE));
    
  vec->valref[vec->size] = RETAIN(TOVAL(_2));
  vec->size++;
endmethod

defalias (void, (gdrop)gpop, TD);
defmethod(void,  gdrop     , TD)
  struct T *vec = &self->TF.T;

  if (vec->size) {
    --vec->size;
#ifdef ARRAY_ONLY
    RELEASE(vec->valref[vec->size]);
#endif
  }
endmethod

// ----- prepend, append

defmethod(void, gprepend, TD, Object)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->valref == vecf->_valref)
    genlarge(_1, aFloat(-VECTOR_GROWTH_RATE));

  vec->valref[-1] = RETAIN(TOVAL(_2));
  vec->valref--;
  vec->size++;
endmethod

static void
enlarge(OBJ _1, U32 capacity, U32 size)
{
  F64 factor = 1.0;

  do
    factor *= VECTOR_GROWTH_RATE;
  while (capacity*(factor - 1.0) < size);

  genlarge(_1, aFloat(-factor));
}

defmethod(void, gprepend, TD, T)
  struct TF *vecf = &self->TF;
  struct T  *vec  = &vecf->T;

  if (vec->valref - vecf->_valref < self2->size)
    enlarge(_1, vecf->capacity, self2->size);

  VAL *src   = self2->valref;
  I32  src_s = self2->stride;
  VAL *end   = self2->valref + self2->size*self2->stride;

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

  if (vec->valref - vecf->_valref < self2->size)
    enlarge(_1, vecf->capacity, self2->size);

  VAL *src   = self2->valref;
  I32  src_s = self2->stride;
  VAL *end   = self2->valref + self2->size*self2->stride;

  while (src != end) {
    vec->valref[vec->size] = RETAIN(*src);
    vec->size++;
    src += src_s;
  }
endmethod


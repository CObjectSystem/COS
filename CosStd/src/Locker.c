/**
 * C Object System
 * COS Locker (proxy)
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

#include <cos/Object.h>
#include <cos/Locker.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

// -----

makclass(Locker,Proxy);

// -----

#if !COS_HAS_POSIX    // ----------------------------------------------

defmethod(OBJ, galloc, pmLocker)
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, pmLocker, Object)
  retmethod(_2);
endmethod

#else // if COS_HAS_POSIX ---------------------------------------------

// ----- ctor/dtor

defmethod(OBJ, ginitWith, Locker, Object)
  next_method(self,self2);
  pthread_mutex_init(&self->lock,0);
endmethod

defmethod(OBJ, gdeinit, Locker)
  pthread_mutex_destroy(&self->lock);
  next_method(self);
endmethod

#undef  SORT
#undef  LOCK
#define SORT(l1,l2) if (l1 >  l2) { struct Locker *tmp=l1; l1=l2, l2=tmp; }
#define LOCK(l1,l2) if (l1 != l2) { lock(l2); }

// ----- rank1-{lock,unlock,clear,chkret}

static inline void
lock(struct Locker *l)
{
  pthread_mutex_lock(&l->lock);
}

static inline void
unlock(struct Locker *l)
{
  pthread_mutex_unlock(&l->lock);
}

static inline void
clear(OBJ obj)
{
  unlock(CAST(struct Locker*, obj));
}

// ----- rank2-{lock,unlock,chkret}

static inline void
lock2(struct Locker *l1, struct Locker *l2)
{
  SORT(l1,l2);
  lock(l1);
  LOCK(l1,l2);
}

static inline void
unlock2(struct Locker *l1, struct Locker *l2)
{
  unlock(l1);
  if (l1 != l2) unlock(l2);
}

// ----- rank3-{lock,unlock,chkret}

static inline void
lock3(struct Locker *l1, struct Locker *l2, struct Locker *l3)
{
  SORT(l1,l2);
  SORT(l1,l3);
  SORT(l2,l3);
  lock(l1);
  LOCK(l1,l2);
  LOCK(l2,l3);
}

static inline void
unlock3(struct Locker *l1, struct Locker *l2, struct Locker *l3)
{
  unlock(l1);
  if (l1 != l2) unlock(l2);
  if (l1 != l3 && l2 != l3) unlock(l3);
}

// ----- rank4-{lock,unlock,chkret}

static inline void
lock4(struct Locker *l1, struct Locker *l2, struct Locker *l3,
      struct Locker *l4)
{ // Batcher's Merge-Exchange N=4 (5 compare, 3 parallel steps)
  SORT(l1,l3); SORT(l2,l4);
  SORT(l1,l2); SORT(l3,l4);
  SORT(l2,l3);
  lock(l1);
  LOCK(l1,l2); LOCK(l3,l4);
  LOCK(l2,l3);
}

static inline void
unlock4(struct Locker *l1, struct Locker *l2, struct Locker *l3,
        struct Locker *l4)
{
  unlock(l1);
  if (l1 != l2) unlock(l2);
  if (l1 != l3 && l2 != l3) unlock(l3);
  if (l1 != l4 && l2 != l4 && l3 != l4) unlock(l4);
}

// ----- rank5-{lock,unlock,chkret}

static inline void
lock5(struct Locker *l1, struct Locker *l2, struct Locker *l3,
      struct Locker *l4, struct Locker *l5)
{ // Batcher's Merge-Exchange N=5 (9 compare, 5 parallel steps)
  SORT(l1,l5); SORT(l2,l4);
  SORT(l1,l3);
  SORT(l3,l5); SORT(l1,l2);
  SORT(l3,l4); SORT(l2,l5);
  SORT(l2,l3); SORT(l4,l5);
  lock(l1);
  LOCK(l1,l2); LOCK(l3,l4);
  LOCK(l2,l3); LOCK(l4,l5);
}

static inline void
unlock5(struct Locker *l1, struct Locker *l2, struct Locker *l3,
        struct Locker *l4, struct Locker *l5)
{
  unlock(l1);
  if (l1 != l2) unlock(l2);
  if (l1 != l3 && l2 != l3) unlock(l3);
  if (l1 != l4 && l2 != l4 && l3 != l4) unlock(l4);
  if (l1 != l5 && l2 != l5 && l3 != l5 && l4 != l5) unlock(l5);
}
 
// ----- error/forward (1+3+7+15+31=57 cases)

// ----- rank 1 (2^1-1=1 case)

defmethod(void, gunrecognizedMessage1, Locker)
  OPRT(_1,clear);
  lock(self);
  next_method(self);
  unlock(self);
  UNPRT(_1);
endmethod

// ----- rank 2 (2^2-1=3 cases)

defmethod(void, gunrecognizedMessage2, Locker, Object)
  OPRT(_1,clear);
  lock(self);
  next_method(self,self2);
  unlock(self);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage2, Object, Locker)
  OPRT(_2,clear);
  lock(self2);
  next_method(self,self2);
  unlock(self2);
  UNPRT(_2);
endmethod


defmethod(void, gunrecognizedMessage2, Locker, Locker)
  OPRT(_1,clear); OPRT(_2,clear);
  lock2(self,self2);
  next_method(self,self2);
  unlock2(self,self2);
  UNPRT(_1);
endmethod

// ----- rank 3 (2^3-1=7 cases)

defmethod(void, gunrecognizedMessage3, Locker, Object, Object)
  OPRT(_1,clear);
  lock(self);
  next_method(self,self2,self3);
  unlock(self);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Locker, Object)
  OPRT(_2,clear);
  lock(self2);
  next_method(self,self2,self3);
  unlock(self2);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Locker)
  OPRT(_3,clear);
  lock(self3);
  next_method(self,self2,self3);
  unlock(self3);
  UNPRT(_3);
endmethod


defmethod(void, gunrecognizedMessage3, Locker, Locker, Object)
  OPRT(_1,clear); OPRT(_2,clear);
  lock2(self,self2);
  next_method(self,self2,self3);
  unlock2(self,self2);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage3, Locker, Object, Locker)
  OPRT(_1,clear); OPRT(_3,clear);
  lock2(self,self3);
  next_method(self,self2,self3);
  unlock2(self,self3);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Locker, Locker)
  OPRT(_2,clear); OPRT(_3,clear);
  lock2(self2,self3);
  next_method(self,self2,self3);
  unlock2(self2,self3);
  UNPRT(_2);
endmethod


defmethod(void, gunrecognizedMessage3, Locker, Locker, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear);
  lock3(self,self2,self3);
  next_method(self,self2,self3);
  unlock3(self,self2,self3);
  UNPRT(_1);
endmethod

// ----- rank 4 (2^4-1=15 cases)

defmethod(void, gunrecognizedMessage4, Locker, Object, Object, Object)
  OPRT(_1,clear);
  lock(self);
  next_method(self,self2,self3,self4);
  unlock(self);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Locker, Object, Object)
  OPRT(_2,clear);
  lock(self2);
  next_method(self,self2,self3,self4);
  unlock(self2);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Locker, Object)
  OPRT(_3,clear);
  lock(self3);
  next_method(self,self2,self3,self4);
  unlock(self3);
  UNPRT(_3);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Locker)
  OPRT(_4,clear);
  lock(self4);
  next_method(self,self2,self3,self4);
  unlock(self4);
  UNPRT(_4);
endmethod


defmethod(void, gunrecognizedMessage4, Locker, Locker, Object, Object)
  OPRT(_1,clear); OPRT(_2,clear);
  lock2(self,self2);
  next_method(self,self2,self3,self4);
  unlock2(self,self2);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Locker, Object, Locker, Object)
  OPRT(_1,clear); OPRT(_3,clear);
  lock2(self,self3);
  next_method(self,self2,self3,self4);
  unlock2(self,self3);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Locker, Object, Object, Locker)
  OPRT(_1,clear); OPRT(_4,clear);
  lock2(self,self4);
  next_method(self,self2,self3,self4);
  unlock2(self,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Locker, Locker, Object)
  OPRT(_2,clear); OPRT(_3,clear);
  lock2(self2,self3);
  next_method(self,self2,self3,self4);
  unlock2(self2,self3);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Locker, Object, Locker)
  OPRT(_2,clear); OPRT(_4,clear);
  lock2(self2,self4);
  next_method(self,self2,self3,self4);
  unlock2(self2,self4);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Locker, Locker)
  OPRT(_3,clear); OPRT(_4,clear);
  lock2(self3,self4);
  next_method(self,self2,self3,self4);
  unlock2(self3,self4);
  UNPRT(_3);
endmethod


defmethod(void, gunrecognizedMessage4, Locker, Locker, Locker, Object)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear);
  lock3(self,self2,self3);
  next_method(self,self2,self3,self4);
  unlock3(self,self2,self3);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Locker, Locker, Object, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_4,clear);
  lock3(self,self2,self4);
  next_method(self,self2,self3,self4);
  unlock3(self,self2,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Locker, Object, Locker, Locker)
  OPRT(_1,clear); OPRT(_3,clear); OPRT(_4,clear);
  lock3(self,self3,self4);
  next_method(self,self2,self3,self4);
  unlock3(self,self3,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Locker, Locker, Locker)
  OPRT(_2,clear); OPRT(_3,clear); OPRT(_4,clear);
  lock3(self2,self3,self4);
  next_method(self,self2,self3,self4);
  unlock3(self2,self3,self4);
  UNPRT(_2);
endmethod


defmethod(void, gunrecognizedMessage4, Locker, Locker, Locker, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear); OPRT(_4,clear);
  lock4(self,self2,self3,self4);
  next_method(self,self2,self3,self4);
  unlock4(self,self2,self3,self4);
  UNPRT(_1);
endmethod

// ----- rank 5 (2^5-1=31 cases)

defmethod(void, gunrecognizedMessage5, Locker, Object, Object, Object, Object)
  OPRT(_1,clear);
  lock(self);
  next_method(self,self2,self3,self4,self5);
  unlock(self);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Object, Object, Object)
  OPRT(_2,clear);
  lock(self2);
  next_method(self,self2,self3,self4,self5);
  unlock(self2);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Locker, Object, Object)
  OPRT(_3,clear);
  lock(self3);
  next_method(self,self2,self3,self4,self5);
  unlock(self3);
  UNPRT(_3);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Locker, Object)
  OPRT(_4,clear);
  lock(self4);
  next_method(self,self2,self3,self4,self5);
  unlock(self4);
  UNPRT(_4);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Locker)
  OPRT(_5,clear);
  lock(self5);
  next_method(self,self2,self3,self4,self5);
  unlock(self5);
  UNPRT(_5);
endmethod


defmethod(void, gunrecognizedMessage5, Locker, Locker, Object, Object, Object)
  OPRT(_1,clear); OPRT(_2,clear);
  lock2(self,self2);
  next_method(self,self2,self3,self4,self5);
  unlock2(self,self2);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Locker, Object, Object)
  OPRT(_1,clear); OPRT(_3,clear);
  lock2(self,self3);
  next_method(self,self2,self3,self4,self5);
  unlock2(self,self3);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Object, Locker, Object)
  OPRT(_1,clear); OPRT(_4,clear);
  lock2(self,self4);
  next_method(self,self2,self3,self4,self5);
  unlock2(self,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Object, Object, Locker)
  OPRT(_1,clear); OPRT(_5,clear);
  lock2(self,self5);
  next_method(self,self2,self3,self4,self5);
  unlock2(self,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Locker, Object, Object)
  OPRT(_2,clear); OPRT(_3,clear);
  lock2(self2,self3);
  next_method(self,self2,self3,self4,self5);
  unlock2(self2,self3);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Object, Locker, Object)
  OPRT(_2,clear); OPRT(_4,clear);
  lock2(self2,self4);
  next_method(self,self2,self3,self4,self5);
  unlock2(self2,self4);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Object, Object, Locker)
  OPRT(_2,clear); OPRT(_5,clear);
  lock2(self2,self5);
  next_method(self,self2,self3,self4,self5);
  unlock2(self2,self5);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Locker, Locker, Object)
  OPRT(_3,clear); OPRT(_4,clear);
  lock2(self3,self4);
  next_method(self,self2,self3,self4,self5);
  unlock2(self3,self4);
  UNPRT(_3);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Locker, Object, Locker)
  OPRT(_3,clear); OPRT(_5,clear);
  lock2(self3,self5);
  next_method(self,self2,self3,self4,self5);
  unlock2(self3,self5);
  UNPRT(_3);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Locker, Locker)
  OPRT(_4,clear); OPRT(_5,clear);
  lock2(self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock2(self4,self5);
  UNPRT(_4);
endmethod


defmethod(void, gunrecognizedMessage5, Locker, Locker, Locker, Object, Object)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear);
  lock3(self,self2,self3);
  next_method(self,self2,self3,self4,self5);
  unlock3(self,self2,self3);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Locker, Object, Locker, Object)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_4,clear);
  lock3(self,self2,self4);
  next_method(self,self2,self3,self4,self5);
  unlock3(self,self2,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Locker, Object, Object, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_5,clear);
  lock3(self,self2,self5);
  next_method(self,self2,self3,self4,self5);
  unlock3(self,self2,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Locker, Locker, Object)
  OPRT(_1,clear); OPRT(_3,clear); OPRT(_4,clear);
  lock3(self,self3,self4);
  next_method(self,self2,self3,self4,self5);
  unlock3(self,self3,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Locker, Object, Locker)
  OPRT(_1,clear); OPRT(_3,clear); OPRT(_5,clear);
  lock3(self,self3,self5);
  next_method(self,self2,self3,self4,self5);
  unlock3(self,self3,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Object, Locker, Locker)
  OPRT(_1,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock3(self,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock3(self,self4,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Locker, Locker, Object)
  OPRT(_2,clear); OPRT(_3,clear); OPRT(_4,clear);
  lock3(self2,self3,self4);
  next_method(self,self2,self3,self4,self5);
  unlock3(self2,self3,self4);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Locker, Object, Locker)
  OPRT(_2,clear); OPRT(_3,clear); OPRT(_5,clear);
  lock3(self2,self3,self5);
  next_method(self,self2,self3,self4,self5);
  unlock3(self2,self3,self5);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Object, Locker, Locker)
  OPRT(_2,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock3(self2,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock3(self2,self4,self5);
  UNPRT(_2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Locker, Locker, Locker)
  OPRT(_3,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock3(self3,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock3(self3,self4,self5);
  UNPRT(_3);
endmethod


defmethod(void, gunrecognizedMessage5, Locker, Locker, Locker, Locker, Object)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear); OPRT(_4,clear);
  lock4(self,self2,self3,self4);
  next_method(self,self2,self3,self4,self5);
  unlock4(self,self2,self3,self4);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Locker, Locker, Object, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear); OPRT(_5,clear);
  lock4(self,self2,self3,self5);
  next_method(self,self2,self3,self4,self5);
  unlock4(self,self2,self3,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Locker, Object, Locker, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock4(self,self2,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock4(self,self2,self4,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Locker, Object, Locker, Locker, Locker)
  OPRT(_1,clear); OPRT(_3,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock4(self,self3,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock4(self,self3,self4,self5);
  UNPRT(_1);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Locker, Locker, Locker, Locker)
  OPRT(_2,clear); OPRT(_3,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock4(self2,self3,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock4(self2,self3,self4,self5);
  UNPRT(_2);
endmethod


defmethod(void, gunrecognizedMessage5, Locker, Locker, Locker, Locker, Locker)
  OPRT(_1,clear); OPRT(_2,clear); OPRT(_3,clear); OPRT(_4,clear); OPRT(_5,clear);
  lock5(self,self2,self3,self4,self5);
  next_method(self,self2,self3,self4,self5);
  unlock5(self,self2,self3,self4,self5);
  UNPRT(_1);
endmethod

#endif // if COS_HAS_POSIX


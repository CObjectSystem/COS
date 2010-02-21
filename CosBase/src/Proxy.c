/*
 o---------------------------------------------------------------------o
 |
 | COS Proxy (root class of proxies)
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
 | $Id: Proxy.c,v 1.19 2010/02/21 16:27:25 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Proxy.h>

#include <cos/gen/message.h>
#include <cos/gen/object.h>

#include <stdlib.h>

// -----

makclass(Proxy);

// ----- constructor, destructor

defmethod(OBJ, ginitWith, Proxy, Object)
  PRT(_1);

  self->obj = 0;
  self->obj = gretain(_2);

  UNPRT(_1);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Proxy)
  if (self->obj)
    grelease(self->obj);

  retmethod(_1);
endmethod

// ----- understanding (1+3+7+15+31=57 cases)

// ----- rank 1 (2^1-1=1 case)

defmethod(OBJ, gunderstandMessage1, Proxy, (SEL)sel)
  next_method(self,sel);
  if (method_retval == False)
    forward_message(self->obj);
endmethod

// ----- rank 2 (2^2-1=3 cases)

defmethod(OBJ, gunderstandMessage2, Proxy, Object, (SEL)sel)
  next_method(self,self2,sel);
  if (method_retval == False)
    forward_message(self->obj,_2);
endmethod

defmethod(OBJ, gunderstandMessage2, Object, Proxy, (SEL)sel)
  next_method(self,self2,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj);
endmethod

defmethod(OBJ, gunderstandMessage2, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,sel);
  if (method_retval == False)
    forward_message(self2->obj,self2->obj);
endmethod

// ----- rank 3 (2^3-1=7 cases)

defmethod(OBJ, gunderstandMessage3, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3);
endmethod

defmethod(OBJ, gunderstandMessage3, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3);
endmethod

defmethod(OBJ, gunderstandMessage3, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj);
endmethod

defmethod(OBJ, gunderstandMessage3, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3);
endmethod

defmethod(OBJ, gunderstandMessage3, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj);
endmethod

defmethod(OBJ, gunderstandMessage3, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj);
endmethod

defmethod(OBJ, gunderstandMessage3, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj);
endmethod

// ----- rank 4 (2^4-1=15 cases)

defmethod(OBJ, gunderstandMessage4, Proxy, Object, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,_2,_3,self4->obj);
endmethod


defmethod(OBJ, gunderstandMessage4, Proxy, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Proxy, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Proxy, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3,self4->obj);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3,self4->obj);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj,self4->obj);
endmethod


defmethod(OBJ, gunderstandMessage4, Proxy, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Proxy, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3,self4->obj);
endmethod

defmethod(OBJ, gunderstandMessage4, Proxy, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj,self4->obj);
endmethod

defmethod(OBJ, gunderstandMessage4, Object, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj,self4->obj);
endmethod


defmethod(OBJ, gunderstandMessage4, Proxy, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj,self4->obj);
endmethod

// ----- rank 5 (2^5-1=31 cases)

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Object, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Object, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,_3,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,_3,_4,self5->obj);
endmethod


defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Object, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,_3,self4->obj,self5->obj);
endmethod


defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Proxy, Object, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Object, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Object, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,_3,self4->obj,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,_3,self4->obj,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Object, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,_2,self3->obj,self4->obj,self5->obj);
endmethod


defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Proxy, Proxy, Object, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Proxy, Object, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj,_4,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Object, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,_3,self4->obj,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Proxy, Object, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,_2,self3->obj,self4->obj,self5->obj);
endmethod

defmethod(OBJ, gunderstandMessage5, Object, Proxy, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(_1,self2->obj,self3->obj,self4->obj,self5->obj);
endmethod


defmethod(OBJ, gunderstandMessage5, Proxy, Proxy, Proxy, Proxy, Proxy, (SEL)sel)
  next_method(self,self2,self3,self4,self5,sel);
  if (method_retval == False)
    forward_message(self->obj,self2->obj,self3->obj,self4->obj,self5->obj);
endmethod

// ----- unrecognized (1+3+7+15+31=57 cases)

static COS_ALWAYS_INLINE void
chkret(SEL sel, OBJ* ret, struct Proxy* pxy)
{
  if (COS_GEN_ISOBJ(sel) && *ret == pxy->obj)
    *ret = (OBJ)pxy;
}

static COS_ALWAYS_INLINE void
chkret2(SEL sel, OBJ* ret, struct Proxy* pxy1, struct Proxy* pxy2)
{
  if (COS_GEN_ISOBJ(sel)) {
         if (*ret == pxy1->obj) *ret = (OBJ)pxy1;
    else if (*ret == pxy2->obj) *ret = (OBJ)pxy2;
  }
}

static COS_ALWAYS_INLINE void
chkret3(SEL sel, OBJ* ret, struct Proxy* pxy1, struct Proxy* pxy2, struct Proxy* pxy3)
{
  if (COS_GEN_ISOBJ(sel)) {
         if (*ret == pxy1->obj) *ret = (OBJ)pxy1;
    else if (*ret == pxy2->obj) *ret = (OBJ)pxy2;
    else if (*ret == pxy3->obj) *ret = (OBJ)pxy3;
  }
}

static COS_ALWAYS_INLINE void
chkret4(SEL sel, OBJ* ret, struct Proxy* pxy1, struct Proxy* pxy2, struct Proxy* pxy3,
                           struct Proxy* pxy4)
{
  if (COS_GEN_ISOBJ(sel)) {
         if (*ret == pxy1->obj) *ret = (OBJ)pxy1;
    else if (*ret == pxy2->obj) *ret = (OBJ)pxy2;
    else if (*ret == pxy3->obj) *ret = (OBJ)pxy3;
    else if (*ret == pxy4->obj) *ret = (OBJ)pxy4;
  }
}

static COS_ALWAYS_INLINE void
chkret5(SEL sel, OBJ* ret, struct Proxy* pxy1, struct Proxy* pxy2, struct Proxy* pxy3,
                           struct Proxy* pxy4, struct Proxy* pxy5)
{
  if (COS_GEN_ISOBJ(sel)) {
         if (*ret == pxy1->obj) *ret = (OBJ)pxy1;
    else if (*ret == pxy2->obj) *ret = (OBJ)pxy2;
    else if (*ret == pxy3->obj) *ret = (OBJ)pxy3;
    else if (*ret == pxy4->obj) *ret = (OBJ)pxy4;
    else if (*ret == pxy5->obj) *ret = (OBJ)pxy5;
  }
}

// ----- rank 1 (2^1-1=1 case)

defmethod(void, gunrecognizedMessage1, Proxy)
  forward_message(self->obj);
  chkret(_sel,_ret,self);
endmethod

// ----- rank 2 (2^2-1=3 cases)

defmethod(void, gunrecognizedMessage2, Proxy, Object)
  forward_message(self->obj,_2);
  chkret(_sel,_ret,self);
endmethod

defmethod(void, gunrecognizedMessage2, Object, Proxy)
  forward_message(_1,self2->obj);
  chkret(_sel,_ret,self2);
endmethod


defmethod(void, gunrecognizedMessage2, Proxy, Proxy)
  forward_message(self->obj,self2->obj);
  chkret2(_sel,_ret,self,self2);
endmethod

// ----- rank 3 (2^3-1=7 cases)

defmethod(void, gunrecognizedMessage3, Proxy, Object, Object)
  forward_message(self->obj,_2,_3);
  chkret(_sel,_ret,self);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Proxy, Object)
  forward_message(_1,self2->obj,_3);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Object, Proxy)
  forward_message(_1,_2,self3->obj);
  chkret(_sel,_ret,self3);
endmethod


defmethod(void, gunrecognizedMessage3, Proxy, Proxy, Object)
  forward_message(self->obj,self2->obj,_3);
  chkret2(_sel,_ret,self,self2);
endmethod

defmethod(void, gunrecognizedMessage3, Proxy, Object, Proxy)
  forward_message(self->obj,_2,self3->obj);
  chkret2(_sel,_ret,self,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Object, Proxy, Proxy)
  forward_message(_1,self2->obj,self3->obj);
  chkret2(_sel,_ret,self2,self3);
endmethod


defmethod(void, gunrecognizedMessage3, Proxy, Proxy, Proxy)
  forward_message(self->obj,self2->obj,self3->obj);
  chkret3(_sel,_ret,self,self2,self3);
endmethod

// ----- rank 4 (2^4-1=15 cases)

defmethod(void, gunrecognizedMessage4, Proxy, Object, Object, Object)
  forward_message(self->obj,_2,_3,_4);
  chkret(_sel,_ret,self);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Proxy, Object, Object)
  forward_message(_1,self2->obj,_3,_4);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Proxy, Object)
  forward_message(_1,_2,self3->obj,_4);
  chkret(_sel,_ret,self3);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Object, Proxy)
  forward_message(_1,_2,_3,self4->obj);
  chkret(_sel,_ret,self4);
endmethod


defmethod(void, gunrecognizedMessage4, Proxy, Proxy, Object, Object)
  forward_message(self->obj,self2->obj,_3,_4);
  chkret2(_sel,_ret,self,self2);
endmethod

defmethod(void, gunrecognizedMessage4, Proxy, Object, Proxy, Object)
  forward_message(self->obj,_2,self3->obj,_4);
  chkret2(_sel,_ret,self,self3);
endmethod

defmethod(void, gunrecognizedMessage4, Proxy, Object, Object, Proxy)
  forward_message(self->obj,_2,_3,self4->obj);
  chkret2(_sel,_ret,self,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Proxy, Proxy, Object)
  forward_message(_1,self2->obj,self3->obj,_4);
  chkret2(_sel,_ret,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Proxy, Object, Proxy)
  forward_message(_1,self2->obj,_3,self4->obj);
  chkret2(_sel,_ret,self2,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Object, Proxy, Proxy)
  forward_message(_1,_2,self3->obj,self4->obj);
  chkret2(_sel,_ret,self3,self4);
endmethod


defmethod(void, gunrecognizedMessage4, Proxy, Proxy, Proxy, Object)
  forward_message(self->obj,self2->obj,self3->obj,_4);
  chkret3(_sel,_ret,self,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage4, Proxy, Proxy, Object, Proxy)
  forward_message(self->obj,self2->obj,_3,self4->obj);
  chkret3(_sel,_ret,self,self2,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Proxy, Object, Proxy, Proxy)
  forward_message(self->obj,_2,self3->obj,self4->obj);
  chkret3(_sel,_ret,self,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Object, Proxy, Proxy, Proxy)
  forward_message(_1,self2->obj,self3->obj,self4->obj);
  chkret3(_sel,_ret,self2,self3,self4);
endmethod


defmethod(void, gunrecognizedMessage4, Proxy, Proxy, Proxy, Proxy)
  forward_message(self->obj,self2->obj,self3->obj,self4->obj);
  chkret4(_sel,_ret,self,self2,self3,self4);
endmethod

// ----- rank 5 (2^5-1=31 cases)

defmethod(void, gunrecognizedMessage5, Proxy, Object, Object, Object, Object)
  forward_message(self->obj,_2,_3,_4,_5);
  chkret(_sel,_ret,self);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Object, Object, Object)
  forward_message(_1,self2->obj,_3,_4,_5);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Proxy, Object, Object)
  forward_message(_1,_2,self3->obj,_4,_5);
  chkret(_sel,_ret,self3);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Proxy, Object)
  forward_message(_1,_2,_3,self4->obj,_5);
  chkret(_sel,_ret,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Object, Proxy)
  forward_message(_1,_2,_3,_4,self5->obj);
  chkret(_sel,_ret,self5);
endmethod


defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Object, Object, Object)
  forward_message(self->obj,self2->obj,_3,_4,_5);
  chkret2(_sel,_ret,self,self2);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Proxy, Object, Object)
  forward_message(self->obj,_2,self3->obj,_4,_5);
  chkret2(_sel,_ret,self,self3);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Object, Proxy, Object)
  forward_message(self->obj,_2,_3,self4->obj,_5);
  chkret2(_sel,_ret,self,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Object, Object, Proxy)
  forward_message(self->obj,_2,_3,_4,self5->obj);
  chkret2(_sel,_ret,self,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Proxy, Object, Object)
  forward_message(_1,self2->obj,self3->obj,_4,_5);
  chkret2(_sel,_ret,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Object, Proxy, Object)
  forward_message(_1,self2->obj,_3,self4->obj,_5);
  chkret2(_sel,_ret,self2,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Object, Object, Proxy)
  forward_message(_1,self2->obj,_3,_4,self5->obj);
  chkret2(_sel,_ret,self2,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Proxy, Proxy, Object)
  forward_message(_1,_2,self3->obj,self4->obj,_5);
  chkret2(_sel,_ret,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Proxy, Object, Proxy)
  forward_message(_1,_2,self3->obj,_4,self5->obj);
  chkret2(_sel,_ret,self3,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Object, Proxy, Proxy)
  forward_message(_1,_2,_3,self4->obj,self5->obj);
  chkret2(_sel,_ret,self4,self5);
endmethod


defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Proxy, Object, Object)
  forward_message(self->obj,self2->obj,self3->obj,_4,_5);
  chkret3(_sel,_ret,self,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Object, Proxy, Object)
  forward_message(self->obj,self2->obj,_3,self4->obj,_5);
  chkret3(_sel,_ret,self,self2,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Object, Object, Proxy)
  forward_message(self->obj,self2->obj,_3,_4,self5->obj);
  chkret3(_sel,_ret,self,self2,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Proxy, Proxy, Object)
  forward_message(self->obj,_2,self3->obj,self4->obj,_5);
  chkret3(_sel,_ret,self,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Proxy, Object, Proxy)
  forward_message(self->obj,_2,self3->obj,_4,self5->obj);
  chkret3(_sel,_ret,self,self3,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Object, Proxy, Proxy)
  forward_message(self->obj,_2,_3,self4->obj,self5->obj);
  chkret3(_sel,_ret,self,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Proxy, Proxy, Object)
  forward_message(_1,self2->obj,self3->obj,self4->obj,_5);
  chkret3(_sel,_ret,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Proxy, Object, Proxy)
  forward_message(_1,self2->obj,self3->obj,_4,self5->obj);
  chkret3(_sel,_ret,self2,self3,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Object, Proxy, Proxy)
  forward_message(_1,self2->obj,_2,self4->obj,self5->obj);
  chkret3(_sel,_ret,self2,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Object, Proxy, Proxy, Proxy)
  forward_message(_1,_2,self3->obj,self4->obj,self5->obj);
  chkret3(_sel,_ret,self3,self4,self5);
endmethod


defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Proxy, Proxy, Object)
  forward_message(self->obj,self2->obj,self3->obj,self4->obj,_5);
  chkret4(_sel,_ret,self,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Proxy, Object, Proxy)
  forward_message(self->obj,self2->obj,self3->obj,_4,self5->obj);
  chkret4(_sel,_ret,self,self2,self3,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Object, Proxy, Proxy)
  forward_message(self->obj,self2->obj,_3,self4->obj,self5->obj);
  chkret4(_sel,_ret,self,self2,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Proxy, Object, Proxy, Proxy, Proxy)
  forward_message(self->obj,_2,self3->obj,self4->obj,self5->obj);
  chkret4(_sel,_ret,self,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Object, Proxy, Proxy, Proxy, Proxy)
  forward_message(_1,self2->obj,self3->obj,self4->obj,self5->obj);
  chkret4(_sel,_ret,self2,self3,self4,self5);
endmethod


defmethod(void, gunrecognizedMessage5, Proxy, Proxy, Proxy, Proxy, Proxy)
  forward_message(self->obj,self2->obj,self3->obj,self4->obj,self5->obj);
  chkret5(_sel,_ret,self,self2,self3,self4,self5);
endmethod


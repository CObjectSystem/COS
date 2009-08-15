/*
 o---------------------------------------------------------------------o
 |
 | COS String - algorithms not using functor
 |
 o---------------------------------------------------------------------o
 |
 | C value System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C value System framework.
 |
 | The C value System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C value System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_alg.c,v 1.1 2009/08/15 22:29:49 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/IntVector.h>
#include <cos/Number.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/compare.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

// -----

useclass(String, ExBadAlloc);
useclass(Lesser,Equal,Greater);

// ----- equality

defmethod(OBJ, gisEqual, String, String)
  if (self == self2)
    retmethod(True);

  if (self->size != self2->size)
    retmethod(False);

  retmethod( memcmp(self->value,self2->value,self->size) ? True : False );
endmethod

// ----- comparison

defmethod(OBJ, gcompare, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;

  int res = memcmp(self->value,self2->value,size);
  
  retmethod( res < 0 ? Lesser : res > 0 ? Greater : Equal );
endmethod

// ----- in place

defmethod(void, greverse, String)
  if (self->size < 2)
    retmethod();

  char *val = self->value;
  char *end = self->value + (self->size-1);
  char  tmp;

  while (val != end)
    tmp = *val, *val++ = *end, *end++ = tmp;

endmethod

// ----- zip, zip3

defmethod(OBJ, gzip, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;

  struct String* str = String_alloc(2*size);

  char *dst  = str->value;
  char *end  = str->value + str->size;
  char *src1 = self->value; 
  char *src2 = self2->value;

  while (dst != end) {
    *dst++ = *src1++;
    *dst++ = *src2++;
  }

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gzip3, String, String, String)
  U32 size = self->size < self2->size ? self->size : self2->size;
  if (size > self3->size) size = self3->size;

  struct String* str = String_alloc(3*size);

  char *dst  = str->value;
  char *end  = str->value + str->size;
  char *src1 = self->value; 
  char *src2 = self2->value;
  char *src3 = self3->value;

  while (dst != end) {
    *dst++ = *src1++;
    *dst++ = *src2++;
    *dst++ = *src3++;
  }

  retmethod(gautoDelete( (OBJ)str ));
endmethod

// ----- cat, cat3, cat4, cat5

defmethod(OBJ, gcat, String, String)
  U32 size = self->size + self2->size;

  struct String *str = String_alloc(size);
  char *dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat3, String, String, String)
  U32 size = self->size + self2->size + self3->size;

  struct String *str = String_alloc(size);
  char *dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat4, String, String, String, String)
  U32 size = self->size + self2->size + self3->size + self4->size;

  struct String *str = String_alloc(size);
  char *dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size); dst += self3->size;
  memcpy(dst,self4->value,self4->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod

defmethod(OBJ, gcat5, String, String, String, String, String)
  U32 size = self1->size + self2->size +
             self3->size + self4->size + self5->size;

  struct String *str = String_alloc(size);
  char *dst = str->value;

  memcpy(dst,self1->value,self1->size); dst += self1->size;
  memcpy(dst,self2->value,self2->size); dst += self2->size;
  memcpy(dst,self3->value,self3->size); dst += self3->size;
  memcpy(dst,self4->value,self4->size); dst += self4->size;
  memcpy(dst,self5->value,self5->size);

  retmethod(gautoDelete( (OBJ)str ));
endmethod


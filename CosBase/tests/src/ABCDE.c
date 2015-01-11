/**
 * C Object System
 * COS testsuites - A, B, C, D and E classes definitions
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
#include <cos/Property.h>
#include <cos/Proxy.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/gen/message.h>

#include <stdio.h>
#include <string.h>
#include "generics.h"
#include "properties.h"

enum { MAX_LEN = 100 };

defclass(A,Object)
  char str[MAX_LEN];
endclass

defclass(B,A) endclass
defclass(C,A) endclass
defclass(D,C) endclass
defclass(E,D) endclass
defclass(PA,Proxy) endclass

makclass(A,Object);
makclass(B,A);
makclass(C,A);
makclass(D,C);
makclass(E,D);
makclass(PA,Proxy);

// properties

static OBJ get(char *str) {
  return Nil; COS_UNUSED(str);
}

defproperty(A, (str)p00, get);
defproperty(A, (str)p01, get);
defproperty(A, (str)p02, get);
defproperty(A, (str)p03, get);
defproperty(A, (str)p04, get);
defproperty(A, (str)p05, get);
defproperty(A, (str)p06, get);
defproperty(A, (str)p07, get);
defproperty(A, (str)p08, get);
defproperty(A, (str)p09, get);
defproperty(A, (str)p10, get);
defproperty(A, (str)p11, get);
defproperty(A, (str)p12, get);
defproperty(A, (str)p13, get);
defproperty(A, (str)p14, get);
defproperty(A, (str)p15, get);
defproperty(A, (str)p16, get);
defproperty(A, (str)p17, get);
defproperty(A, (str)p18, get);
defproperty(A, (str)p19, get);
defproperty(A, (str)p20, get);
defproperty(A, (str)p21, get);
defproperty(A, (str)p22, get);
defproperty(A, (str)p23, get);
defproperty(A, (str)p24, get);
defproperty(A, (str)p25, get);
defproperty(A, (str)p26, get);
defproperty(A, (str)p27, get);
defproperty(A, (str)p28, get);
defproperty(A, (str)p29, get);
defproperty(A, (str)p30, get);
defproperty(A, (str)p31, get);
defproperty(A, (str)p32, get);
defproperty(A, (str)p33, get);
defproperty(A, (str)p34, get);
defproperty(A, (str)p35, get);
defproperty(A, (str)p36, get);
defproperty(A, (str)p37, get);
defproperty(A, (str)p38, get);
defproperty(A, (str)p39, get);
defproperty(A, (str)p40, get);
defproperty(A, (str)p41, get);
defproperty(A, (str)p42, get);
defproperty(A, (str)p43, get);
defproperty(A, (str)p44, get);
defproperty(A, (str)p45, get);
defproperty(A, (str)p46, get);
defproperty(A, (str)p47, get);
defproperty(A, (str)p48, get);
defproperty(A, (str)p49, get);
defproperty(A, (str)p50, get);
defproperty(A, (str)p51, get);
defproperty(A, (str)p52, get);
defproperty(A, (str)p53, get);
defproperty(A, (str)p54, get);
defproperty(A, (str)p55, get);
defproperty(A, (str)p56, get);
defproperty(A, (str)p57, get);
defproperty(A, (str)p58, get);
defproperty(A, (str)p59, get);
defproperty(A, (str)p60, get);
defproperty(A, (str)p61, get);
defproperty(A, (str)p62, get);
defproperty(A, (str)p63, get);
//defproperty(A, (str)p64, get);

// ---- constructors

defmethod(OBJ, ginit, A)
  strcpy(self->str,"A");
  retmethod(_1);
endmethod

defmethod(OBJ, ginit, B)
  strcpy(self->A.str,"B");
  retmethod(_1);
endmethod

defmethod(OBJ, ginit, C)
  strcpy(self->A.str,"C");
  retmethod(_1);
endmethod

defmethod(OBJ, ginit, D)
  strcpy(self->C.A.str,"D");
  retmethod(_1);
endmethod

defmethod(OBJ, ginit, E)
  strcpy(self->D.C.A.str,"E");
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, A, A)
  strcpy(self1->str, self2->str);
  retmethod(_1);
endmethod

// ---- destructor

defmethod(OBJ, gdeinit, A)
  self->str[0] = 0;
  retmethod(_1);
endmethod

// ---- getter

defmethod(STR, gstr, A)
  retmethod(self->str);
endmethod

// ---- invariant

defmethod(void, ginvariant, A, (STR)file, (int)line)
  ensure(self->str[0] == 'A', file, line);
  gcatStr(_1,"-INV" );
endmethod

defmethod(void, ginvariant, B, (STR)file, (int)line)
  ensure(self->A.str[0] == 'B', file, line);
  gcatStr(_1,"-INV" );
endmethod

defmethod(void, ginvariant, C, (STR)file, (int)line)
  ensure(self->A.str[0] == 'C', file, line);
  gcatStr(_1,"-INV" );
endmethod

defmethod(void, ginvariant, D, (STR)file, (int)line)
  ensure(self->C.A.str[0] == 'D', file, line);
  gcatStr(_1,"-INV" );
endmethod

defmethod(void, ginvariant, E, (STR)file, (int)line)
  ensure(self->D.C.A.str[0] == 'E', file, line);
  gcatStr(_1,"-INV" );
endmethod

// ---- printf

defmethod(void, gvputStr, C, (STR)fmt, (va_list)va)
  vsnprintf(self->A.str, MAX_LEN, fmt, va);
endmethod

// ---- concat str

defmethod(void, gcatStr, A, (STR)str)
  strncat(self->str, str, MAX_LEN-strlen(self->str));
endmethod

defmethod(void, gcat2Str, A, A, (STR)str)
  strncat(self1->str, str, MAX_LEN-strlen(self1->str));
  strncat(self2->str, str, MAX_LEN-strlen(self2->str));
endmethod

// ---- message not understood

static inline void
chkret(SEL sel, OBJ* ret)
{
  if (COS_GEN_ISOBJ(sel))
    *ret = Nil;
}

defmethod(void, gunrecognizedMessage1, A)
  snprintf(self->str, MAX_LEN, "%s does not understand %s",
           gclassName(_1), _sel->str);
  chkret(_sel,_ret);
endmethod

// ---- proxy

defmethod(void, gunrecognizedMessage1, PA)
  usegeneric((gvputStr)gvputStr_sel,(gcatStr)gcatStr_sel);
  char buf[MAX_LEN];

  if (_sel == (SEL)gvputStr_sel) {
    gvputStr_arg_t *arg = _arg;
    snprintf(buf, sizeof buf, "%s (through proxy PA)", arg->fmt);
    arg->fmt = buf;
  } else

  if (_sel == (SEL)gcatStr_sel) {
    gcatStr_arg_t *arg = _arg;
    snprintf(buf, sizeof buf, "%s (through proxy PA)", arg->str);
    arg->str = buf;
  }

  next_method(self);
endmethod

// ---- doC

// activate maximum contract level
enum { COS_CONTRACT_SAVE = COS_CONTRACT };

#undef  COS_CONTRACT
#define COS_CONTRACT COS_CONTRACT_ALL

defmethod(void, gdoC, A, (int)val)
  PRE  ensure(val == 1), gcatStr(_1,"-PRE" );
  POST ensure(val == 1), gcatStr(_1,"-POST");
  BODY ensure(val == 1), gcatStr(_1,"-BODY");
endmethod

defmethod(void, gdoC, B, (int)val)
  PRE  ensure(val == 1), gcatStr(_1,"-PRE" );
  POST ensure(val == 0), gcatStr(_1,"-POST");
  BODY ensure(val == 1), gcatStr(_1,"-BODY");
endmethod

defmethod(void, gdoC, C, (int)val)
  PRE  ensure(val == 1), gcatStr(_1,"-PRE" );
  POST ensure(val == 0), gcatStr(_1,"-POST");
  BODY ensure(val == 0), gcatStr(_1,"-BODY");
endmethod

defmethod(void, gdoC, D, (int)val)
  PRE  ensure(val == 1), gcatStr(_1,"-PRE" );
  POST ensure(val == 1), gcatStr(_1,"-POST");
  BODY ensure(val == 1), gcatStr(_1,"-BODY");
       ensure(val == 0);

endmethod

defmethod(void, gdoC, E, (int)val)
  PRE  ensure(val == 1), gcatStr(_1,"-PRE" );
  POST ensure(val == 1), gcatStr(_1,"-POST");
  BODY ensure(val == 1), gcatStr(_1,"-BODY");
       retmethod();
endmethod

// restore contract level
#undef  COS_CONTRACT
#define COS_CONTRACT COS_CONTRACT_SAVE

// ---- doX

defmethod(void, gdoX, A, A)
  defnext(void, gdoZ, A, A);
  gcat2Str(_1,_2,"-AAX");
  if (next_method_p) next_method(self1,self2);
endmethod

defalias(void, (gdoZ)gdoX, B, B);

defalias(void, (gdoZ)gdoX, C, C);

defmethod(void, gdoX, D, D)
  gcat2Str(_1,_2,"-DDX");
  if (next_method_p) next_method(self1,self2);
endmethod

defalias(void, (gdoZ)gdoX, E, E);

// ---- doZ

defmethod(void, gdoZ, A, A)
  defnext(void, gdoY, A, A);
  gcat2Str(_1,_2,"-AAZ");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoZ, B, B)
  gcat2Str(_1,_2,"-BBZ");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoZ, C, C)
  gcat2Str(_1,_2,"-CCZ");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoZ, D, D)
  defnext(void, gdoY, D, D);
  gcat2Str(_1,_2,"-DDZ");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoZ, E, E)
  gcat2Str(_1,_2,"-EEZ");
  if (next_method_p) next_method(self1,self2);
endmethod

// ---- doY

// rnk 2
defmethod(void, gdoY, A, A)
  gcat2Str(_1,_2,"-AA");
  ensure( !next_method_p );
endmethod

// rnk 3
defmethod(void, gdoY, A, B)
  gcat2Str(_1,_2,"-AB");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, A, C)
  gcat2Str(_1,_2,"-AC");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, (gdoY), A, C) // around method
  gcat2Str(_1,_2,"-[AC");
  if (next_method_p) next_method(self1,self2);
  gcat2Str(_1,_2,"-AC]");
endmethod

defmethod(void, gdoY, B, A)
  gcat2Str(_1,_2,"-BA");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, (gdoY), B, A) // around method
  gcat2Str(_1,_2,"-[BA");
  if (next_method_p) next_method(self1,self2);
  gcat2Str(_1,_2,"-BA]");
endmethod

defmethod(void, (gdoY), B, A) // around method
  gcat2Str(_1,_2,"-[1BA");
  if (next_method_p) next_method(self1,self2);
  gcat2Str(_1,_2,"-BA1]");
endmethod

defmethod(void, (gdoY), B, A) // around method
  gcat2Str(_1,_2,"-[2BA");
  if (next_method_p) next_method(self1,self2);
  gcat2Str(_1,_2,"-BA2]");
endmethod

defmethod(void, gdoY, C, A)
  gcat2Str(_1,_2,"-CA");
  if (next_method_p) next_method(self1,self2);
endmethod

// rnk 4
defmethod(void, gdoY, A, D)
  gcat2Str(_1,_2,"-AD");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, B, B)
  gcat2Str(_1,_2,"-BB");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, B, C)
  gcat2Str(_1,_2,"-BC");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, (gdoY), B, C) // around method
  gcat2Str(_1,_2,"-[BC");
  if (next_method_p) next_method(self1,self2);
  gcat2Str(_1,_2,"-BC]");
endmethod

defmethod(void, gdoY, C, B)
  gcat2Str(_1,_2,"-CB");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, C, C)
  gcat2Str(_1,_2,"-CC");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, D, A)
  gcat2Str(_1,_2,"-DA");
  if (next_method_p) next_method(self1,self2);
endmethod

// rnk 5
defmethod(void, gdoY, A, E)
  gcat2Str(_1,_2,"-AE");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, B, D)
  gcat2Str(_1,_2,"-BD");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, C, D)
  gcat2Str(_1,_2,"-CD");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, D, B)
  gcat2Str(_1,_2,"-DB");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, D, C)
  gcat2Str(_1,_2,"-DC");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, E, A)
  gcat2Str(_1,_2,"-EA");
  if (next_method_p) next_method(self1,self2);
endmethod

// rnk 6
defmethod(void, gdoY, B, E)
  gcat2Str(_1,_2,"-BE");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, C, E)
  gcat2Str(_1,_2,"-CE");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, E, B)
  gcat2Str(_1,_2,"-EB");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, E, C)
  gcat2Str(_1,_2,"-EC");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, D, D)
  gcat2Str(_1,_2,"-DD");
  if (next_method_p) next_method(self1,self2);
endmethod

// rnk 7
defmethod(void, gdoY, D, E)
  gcat2Str(_1,_2,"-DE");
  if (next_method_p) next_method(self1,self2);
endmethod

defmethod(void, gdoY, E, D)
  gcat2Str(_1,_2,"-ED");
  if (next_method_p) next_method(self1,self2);
endmethod

// rnk 8
defmethod(void, gdoY, E, E)
  gcat2Str(_1,_2,"-EE");
  if (next_method_p) next_method(self1,self2);
endmethod

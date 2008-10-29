/*
 o---------------------------------------------------------------------o
 |
 | COS core exceptions
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
 | $Id: Exception.c,v 1.4 2008/10/29 15:43:10 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Exception.h>
#include <cos/errno.h>
#include <cos/signal.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/gen/init.h>
#include <cos/cos/debug.h>

#include <stdlib.h>
#include <string.h>

makclass(Exception       ,Object);
makclass(ExErrno         ,Exception);
makclass(ExSignal        ,Exception);

makclass(ExBadAlloc      ,Exception);
makclass(ExBadArity      ,Exception);
makclass(ExBadAssert     ,Exception);
makclass(ExBadCast       ,Exception);
makclass(ExBadDomain     ,Exception);
makclass(ExBadFormat     ,Exception);
makclass(ExBadMessage    ,Exception);
makclass(ExBadPredicate  ,Exception);
makclass(ExBadRange      ,Exception);
makclass(ExBadSize       ,Exception);
makclass(ExBadType       ,Exception);
makclass(ExBadValue      ,Exception);
makclass(ExNotFound      ,Exception);
makclass(ExNotImplemented,Exception);
makclass(ExNotSupported  ,Exception);
makclass(ExOverflow      ,Exception);
makclass(ExUnderflow     ,Exception);

// ----- exception

defmethod(OBJ, ginit, Exception)
  self->str = 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithStr, Exception, (STR)str)
  self->str = str;
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Exception)
  self->str = 0;
  retmethod(_1);
endmethod

defmethod(STR, gstr, Exception)
  retmethod(self->str);
endmethod

// ----- assert

void cos_exception_assertLoc(STR cond, STR file, int line)
{
  useclass(ExBadAssert);
  THROW(ginitWithStr(galloc(ExBadAssert),cond),file,line);
}

// ----- errno

void cos_exception_errnoLoc(int err, STR file, int line)
{
  useclass(ExErrno);
  THROW(ginitWithInt(galloc(ExErrno),err),file,line);
}

defmethod(OBJ, ginitWithInt, ExErrno, (int)val)
  defnext(OBJ, ginitWithStr, ExErrno, (STR)str);
  self->err = val;
  next_method(self, strerror(val));
endmethod

defmethod(int, gint, ExErrno)
  retmethod(self->err);
endmethod

// ----- signal

defmethod(OBJ, ginitWithInt, ExSignal, (int)val)
  defnext(OBJ, ginit, ExSignal);
  self->sig = val;
  next_method(self);
endmethod

defmethod(int, gint, ExSignal)
  retmethod(self->sig);
endmethod

static void
ex_signal(int sig)
{
  useclass(ExSignal);

  // reload handler
  if (cos_signal(sig) == SIG_ERR)
    test_errno();

  switch(sig) {
  case SIGABRT:
#if SIGBUS
  case SIGBUS:
#elif SIG_BUS 
  case SIG_BUS:
#endif
  case SIGFPE:
  case SIGILL:
  case SIGSEGV: cos_showCallStack(stderr);
  }

  THROW(ginitWithInt(galloc(ExSignal), sig));
}

void (*cos_signal(int sig))(int)
{
  void (*hdlr)(int);

  if ((hdlr = signal(sig, ex_signal)) == SIG_ERR)
    test_errno();

  return hdlr;
}

void cos_signal_std(void)
{
  cos_signal(SIGABRT);
  cos_signal(SIGALRM);
#if SIGBUS
  cos_signal(SIGBUS);
#elif SIG_BUS 
  cos_signal(SIG_BUS);
#endif
  cos_signal(SIGFPE);
  cos_signal(SIGILL);
  cos_signal(SIGINT);
  cos_signal(SIGQUIT);
  cos_signal(SIGSEGV);
  cos_signal(SIGTERM);
}

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
 | $Id: Exception.c,v 1.23 2010/06/03 09:03:49 ldeniau Exp $
 |
*/

#include <cos/Exception.h>

#include <cos/errno.h>
#include <cos/signal.h>

#include <cos/gen/init.h>
#include <cos/gen/message.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <stdlib.h>
#include <string.h>

makclass(Exception);

makclass(ExErrno         , Exception);
makclass(ExSignal        , Exception);

makclass(ExBadAlloc      , Exception);
makclass(ExBadArity      , Exception);
makclass(ExBadAssert     , Exception);
makclass(ExBadCast       , Exception);
makclass(ExBadDomain     , Exception);
makclass(ExBadFormat     , Exception);
makclass(ExBadMessage    , Exception);
makclass(ExBadMode       , Exception);
makclass(ExBadPredicate  , Exception);
makclass(ExBadProperty   , Exception);
makclass(ExBadRange      , Exception);
makclass(ExBadSize       , Exception);
makclass(ExBadType       , Exception);
makclass(ExBadValue      , Exception);
makclass(ExNotFound      , Exception);
makclass(ExNotImplemented, Exception);
makclass(ExNotSupported  , Exception);
makclass(ExOverflow      , Exception);
makclass(ExUnderflow     , Exception);

// ----- exception

static inline char*
str_dup(STR str)
{
  useclass(ExBadAlloc);
  
  char *cpy = malloc(strlen(str)+1);
  if (!cpy) THROW(ExBadAlloc);
  return strcpy(cpy, str);
}

defmethod(OBJ, ginit, Exception)
  self->obj = 0;
  self->str = 0;
  retmethod(_1);
endmethod
 
defmethod(OBJ, ginitWithObj, Exception, (OBJ)obj)
  self->obj = gretain(obj);
  self->str = 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithStr, Exception, (STR)str)
  self->obj = 0;
  self->str = str_dup(str);
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithObjStr, Exception, (OBJ)obj, (STR)str)
  self->obj = gretain(obj);
  self->str = str_dup(str);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Exception)
  if (self->str)
    free(self->str), self->str = 0;

  if (self->obj)
    grelease(self->obj), self->obj = 0;

  retmethod(_1);
endmethod

defmethod(STR, gstr, Exception)
  if (self->obj && gunderstandMessage1(_1, genericref(gstr)) == True)
    retmethod( gstr(self->obj) );
    
  if (self->str)
    retmethod(self->str);

  retmethod( "" );
endmethod

defmethod(OBJ, gobj, Exception)
  retmethod( self->obj ? self->obj : Nil );
endmethod

// ----- assert

void cos_exception_assert(STR reason, STR file, int line)
{
  useclass(ExBadAssert);
  
  if (cos_object_id(ExBadAssert) == 0)
    cos_logmsg(COS_LOGMSG_ABORT,file,line,"%s",reason);

  THROW( gnewWithStr(ExBadAssert,reason), file,line);
}

// ----- badcast

void cos_exception_badcast(OBJ obj, const struct Class *cls, STR file, int line)
{
  useclass(ExBadCast);
  
  if (cos_object_id(ExBadCast) == 0)
    cos_logmsg(COS_LOGMSG_ABORT,file,line,"invalid cast %s", cls->str);

  THROW( ginitWithObjStr(galloc(ExBadCast),obj,cls->str), file,line);
}

// ----- errno

void cos_exception_errno(int err, STR file, int line)
{
  useclass(ExErrno);

  if (cos_object_id(ExErrno) == 0)
    cos_logmsg(COS_LOGMSG_ABORT,file,line, "[%d] %s", err, strerror(err));

  THROW( ginitWithInt(galloc(ExErrno),err), file, line);
}

defmethod(OBJ, ginitWithInt, ExErrno, (int)val)
  defnext(OBJ, ginitWithStr, ExErrno, (STR)str);
  next_method(self, strerror(val));
  self->err = val;
endmethod

defmethod(int, gint, ExErrno)
  retmethod(self->err);
endmethod

// ----- signal

#ifdef __GLIBC__
extern const char* strsignal(int);
#else
static const char* strsignal(int sig)
{
  switch (sig) {
  case SIGABRT: return "Aborted";
  case SIGALRM: return "Alarm clock";
  case SIGBUS : return "Bus error";
  case SIGFPE : return "Floating point exception";
  case SIGILL : return "Illegal instruction";
  case SIGINT : return "Interrupt";
  case SIGQUIT: return "Quit";
  case SIGSEGV: return "Segmentation fault";
  case SIGTERM: return "Terminated";
  default     : return "Unknown signal";
  }
}
#endif // __GLIBC__

defmethod(OBJ, ginitWithInt, ExSignal, (int)val)
  defnext(OBJ, ginitWithStr, ExSignal, (STR)str);
  next_method(self, strsignal(val));
  self->sig = val;
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

  if (cos_object_id(ExSignal) == 0) {
    if (sig == SIGABRT) signal(sig, SIG_DFL);
    cos_abort("[%d] %s", sig, strsignal(sig));
  }

  THROW( ginitWithInt(galloc(ExSignal),sig) );
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
  cos_signal(SIGBUS );
  cos_signal(SIGFPE );
  cos_signal(SIGILL );
  cos_signal(SIGINT );
  cos_signal(SIGQUIT);
  cos_signal(SIGSEGV);
  cos_signal(SIGTERM);
}

/*
 o---------------------------------------------------------------------o
 |
 | COS exception
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
 | $Id: cos_exception.c,v 1.13 2009/02/25 23:06:39 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Exception.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>
#include <cos/gen/value.h>

#include <stdlib.h>

static struct cos_exception_context _cxt0;

#if COS_TLS || !COS_POSIX // -----------------------------

__thread struct cos_exception_context *cos_exception_cxt_ = &_cxt0;

static inline void
cxt_set(struct cos_exception_context *cxt)
{
  cos_exception_cxt_ = cxt;
}

#else // COS_POSIX && !COS_TLS ---------------------------

static pthread_key_t _cxt_key;

static inline void
cxt_set(struct cos_exception_context *cxt)
{
	 test_assert( pthread_setspecific(_cxt_key, cxt) == 0 );
}

struct cos_exception_context*
cos_exception_context(void)
{
  struct cos_exception_context *cxt = pthread_getspecific(_cxt_key);
	if (cxt) return cxt;
	 
	cxt_set(&_cxt0);
  return &_cxt0;
}

#ifndef __GNUC__
#error "COS: pthread requires either TLS or GCC constructor"
#endif

static void cxt_init(void) __attribute__((constructor));
static void cxt_init(void)
{
  if ( pthread_key_create(&_cxt_key, 0) )
	  cos_abort("unable to initialize exceptions");
}

#endif // ------------------------------------------------

static void
unwind_stack(struct cos_exception_context *cxt)
{
  struct cos_exception_protect *p = cxt->stk;

  cxt->unstk = YES;

  for (; p; p = p->prv) {
  
    if (p->obj == (OBJ*)YES) {
      struct cos_exception_extendedProtect *ep = (void*)p;
      
      if (*ep->alt && ep->fct)
        ep->fct(*ep->alt);

      continue;
    }
    
    if (*p->obj)
      grelease(*p->obj);
  }

  cxt->unstk = NO;
  cxt->stk   = 0;
}

static void
terminate_default(OBJ ex, STR func, STR file, int line)
{
  STR reason = cos_object_isKindOf(ex, classref(Exception)) ? gstr(ex) : ".";

  if (cos_exception_uncaught() == YES)
    cos_abort("exception %s (%s) thrown at (%s:%d:%s) during stack unwinding "
              "leading to an undefined behavior",
              cos_object_className(ex), reason, file, line, func);
  else
    cos_info ("exiting with uncaught exception %s (%s) thrown at (%s:%d:%s)",
              cos_object_className(ex), reason, file, line, func);
}

static cos_exception_handler handler = terminate_default;

static void
terminate(void)
{
  if (handler) {
    struct cos_exception_context *cxt = cos_exception_context();
    handler(cxt->ex, cxt->func, cxt->file, cxt->line);
  }
	
  exit(EXIT_FAILURE);
}

// ----- low-level API

BOOL
cos_exception_catch(OBJ ex, OBJ cls)
{
  return gisKindOf(ex,cls) == True;
}

void
cos_exception_throw(OBJ ex, STR func, STR file, int line)
{
  if (!ex) ex = Nil;
  
  gthrow(ex, func, file, line);

  terminate(); // safer if an overridden gthrow returns.
}

BOOL
cos_exception_uncaught(void)
{
  return cos_exception_context()->unstk;
}

void
cos_exception_initContext(struct cos_exception_context *cxt)
{
  cxt->prv   = cos_exception_context();
  cxt->stk   = 0;
  cxt->unstk = 0;
  cxt->ex    = 0;
  cxt_set(cxt);
}

void
cos_exception_deinitContext(struct cos_exception_context *cxt)
{
	cxt_set(cxt->prv);

	if ( (cxt->tag & cos_tag_throw) )
		cos_exception_throw(cxt->ex,cxt->func,cxt->file,cxt->line); // rethrow

	if (cxt->ex) grelease(cxt->ex);
}

// -----

cos_exception_handler
cos_exception_setTerminate(cos_exception_handler new)
{
  cos_exception_handler old = handler;
  handler = new;
  return old;
}

// ----- methods

defmethod(void, gthrow, Object, (STR)func, (STR)file, (int)line)

  struct cos_exception_context *cxt = cos_exception_context();

  if (cxt->ex != _1) {
	  if (cxt->ex) grelease(cxt->ex);

    cxt->ex   = self->rc == COS_RC_AUTO ? gclone(_1) : _1;
    cxt->func = func ? func : "";
    cxt->file = file ? file : "";
    cxt->line = line;
  }
	
  if (cxt->unstk == YES)
    terminate();

  unwind_stack(cxt);

  if (cxt == &_cxt0)
    terminate();

  cos_exception_lngjmp(cxt->buf, cxt->tag | cos_tag_throw);

endmethod

defmethod(void, gdeinitialize, pmException)
  struct cos_exception_context *cxt = cos_exception_context();
  
  if (cxt->ex != 0) grelease(cxt->ex);
endmethod

/*
 * ----------------------------------------------------------------------------
 *  Debug Functions
 * ----------------------------------------------------------------------------
 */

#include <cos/debug.h>

void
cos_exception_showStack(FILE *fp)
{
  struct cos_exception_protect *p = cos_exception_context()->stk;
  U32 i = 0;

  if (!fp) fp = stderr;

  while (p) {
    fprintf(fp, "prt[%4u] = %-25s\n",
            i, *p->obj ? cos_object_className(*p->obj) : "NIL");
    ++i, p = p->prv;
  }
}
